// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// MakeDist - Version 1.0
//
// MakeDist Demonstrates:
//   IWbemLocator->ConnectServer
//   IWbemContext->SetValue
//   IWbemServices->GetObject
//   IWbemServices->ExecQuery
//   IWbemServices->ExecMethod
//   IWbemServices->PutInstance
//   IEnumWbemClassObject->Next
//   IWbemClassObject->Get
//   IWbemClassObject->Put
//   IWbemClassObject->GetMethod
//   IWbemClassObject->SpawnInstance
//   SetInterfaceSecurity
//   Working with VARIANT and SAFEARRAY
//   Site Control File operations
//
// Description:
//   MakeDist creates an instance of SMS_SCI_SysResUse.
//   Given the machine name provided on the command line, an
//   instance of SMS_SCI_SysResUse is spawned, it's itemtype is
//   set to "Distribution Point", and the NALPath property is set to
//   \\MachineName\.  This indicates to SMS that the specified
//   machine is now available to be used as a distribution point.
//
// This application is very similar to MakeCAP.
//
// *************************************************************

#include <stdio.h>
#include <conio.h>
#include <comdef.h>
#include <winbase.h>

#include <wbemidl.h>
#include "wbemsec.h"

#define MAX_PASSWORD_LENGTH 255

#define _USE_AUTOSYMBOLS  // must be defined before the include
#define _INIT_AUTOSYMBOLS // must be defined before the include in one and only one file
#include "smsprov.h"

using namespace SMSSDK;

// **************************************************************************
// Init : Connect to specified Server, Sitecode.
//
// [in] WCHAR *Server
// [in] WCHAR *User
// [in] WCHAR *Password
// [out] WCHAR *&Sitecode
// [out] IWbemServices* &rpWbemServices  (reference to pointer)
// Returns: int
//		0 Success
//		1 CoCreateInstance WbemLocator Failed
//		2 Specified Server was not found
//		3 Error retrieving SiteCode
//		4 Error retrieving NamespacePath
//		5 Could not connect to NamespacePath
// **************************************************************************
int Init(WCHAR *Server, WCHAR *User, WCHAR *Password, WCHAR *Sitecode, IWbemServices *&rpWbemServices) {
	
	HRESULT hr;
	VARIANT vNamespace;
	VARIANT vSitecode;
	_bstr_t bstrNamespace;
	_bstr_t bstrLocationPath;
	ULONG uReturned;
	IWbemLocator *pWbemLocator = NULL;
	IWbemClassObject *pWbemClass = NULL;
	IEnumWbemClassObject *pWbemEnum = NULL;

	// Release and Null pWbemServices
	if( rpWbemServices ) rpWbemServices->Release();
	rpWbemServices = NULL;

	// Store \\Server\root\sms
	bstrNamespace = _bstr_t(L"\\\\") + _bstr_t(Server) + "\\root\\sms";

	//Initialize COM
	CoInitialize(NULL);

	// Create an instance of IWbemLocator.
	hr = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (void**) &pWbemLocator);
	if( FAILED(hr) ) {
		CoUninitialize();
		return 1;
	}

	// Use the IWbemLocator instance to connect to the \\Server\root\sms 
	// namespace using User and Password as the connection credentials
	hr = pWbemLocator->ConnectServer(bstrNamespace, _bstr_t(User), _bstr_t(Password), NULL, 0, NULL, NULL, &rpWbemServices);
	if( FAILED(hr) ) {
		pWbemLocator->Release();
		CoUninitialize();
		return 2;
	}

	// Create a query for finding the SMS_ProviderLocation instance
	// that contains the site code for the local site.
	bstrLocationPath = _bstr_t(L"SELECT ") + _bstr_t(SMS_ProviderLocation::PROP_NamespacePath) +
		L", " + _bstr_t(SMS_ProviderLocation::PROP_SiteCode) + L" FROM " + _bstr_t(CLASS_SMS_ProviderLocation) +
		L" WHERE " + _bstr_t(SMS_ProviderLocation::PROP_ProviderForLocalSite) + L" = True";
		
	// Execute the query
	hr = rpWbemServices->ExecQuery(_bstr_t(L"WQL"), bstrLocationPath, WBEM_FLAG_FORWARD_ONLY, NULL, &pWbemEnum);
	if( FAILED(hr) )
	{
		rpWbemServices->Release();
		pWbemLocator->Release();
		CoUninitialize();
		return 4;
	}

	// pWbemEnum didn't come from the WbemLocator, so we need to set security on it.
	// This call sets the authentication and impersonation levels to 
	// use with the pWbemEnum interface pointer.
	hr = SetInterfaceSecurity(pWbemEnum, NULL, User, Password, true);
	if( FAILED(hr) )
	{
		pWbemEnum->Release();
		rpWbemServices->Release();
		pWbemLocator->Release();
		CoUninitialize();
		return 4;
	}

	// Retrieve next object from pWbemEnum. The next object
	// will be the first instance of SMS_ProviderLocation that
	// was returned from the query.
	hr = pWbemEnum->Next(WBEM_INFINITE, 1, &pWbemClass, &uReturned);
		
	pWbemEnum->Release();
	
	// We want the first returned object. If there were no
	// objects returned than we quit with an error.
	if( uReturned != 1 )
	{
		rpWbemServices->Release();
		pWbemLocator->Release();
		CoUninitialize();
		return 4;
	}

	VariantInit(&vSitecode);

	// Retrieve the Sitecode
	hr = pWbemClass->Get(_bstr_t(SMS_ProviderLocation::PROP_SiteCode), 0, &vSitecode, NULL, NULL);
	
	if( FAILED(hr) )
	{
		VariantClear(&vSitecode);
		pWbemLocator->Release();
		pWbemClass->Release();
		rpWbemServices->Release();
		return 3;
	}

	wcscpy(Sitecode, V_BSTR(&vSitecode));

	VariantClear(&vSitecode);

	// Initialize the vVar VARIANT structure.
	VariantInit( &vNamespace );
	
	// The actual SMS namespace path for the site is contained in the NamespacePath
	// property. Use the WMI Get method to get the value from the NamespacePath
	// property and assign it to the variant vNamespace.
	hr = pWbemClass->Get(_bstr_t(SMS_ProviderLocation::PROP_NamespacePath), 0, &vNamespace, NULL, NULL);
	pWbemClass->Release();
	rpWbemServices->Release();
	rpWbemServices = NULL;		// MUST be set to NULL
	if( FAILED(hr) )
	{
		VariantClear(&vNamespace);
		pWbemLocator->Release();
		CoUninitialize();
		return 4;
	}
	
	// Finally, connect to the true provider location
	// at \\<Server>\root\sms\site_<SiteCode>
	hr = pWbemLocator->ConnectServer(V_BSTR(&vNamespace), _bstr_t(User), _bstr_t(Password), NULL, 0, NULL, NULL, &rpWbemServices);
	VariantClear(&vNamespace);
	pWbemLocator->Release();
	if( FAILED(hr) ) {
		CoUninitialize();
		return 5;
	}	

	return 0;
}


// **************************************************************************
// PromptUserForPassword : Receive character input for password
//
// [out] char* szPassword
//
// Returns: bool
//		true  Success
//		false aborted
// **************************************************************************
bool PromptUserForPassword(char* szPassword) {
	char c;
	int i = 0;

	do {
		c = _getch();
		switch( c ) {

		case 8:						// backspace
			if( i-- > 0 ) {
				printf("\b \b");
			}
			break;

		case 13:					// enter
			printf("\n\n");
			szPassword[i] = 0;
			return true;

		case 3:						// ctrl-c
		case 27:					// esc
			printf(" (aborted)\n\n");
			return false;

		default:					// anything else
			if( i < MAX_PASSWORD_LENGTH ) {
				printf("*");
				szPassword[i++] = c;
			}
		}
		
	} while( 1 );
}

// **************************************************************************
// AnsiToUnicode : Convert ansi string to unicode
//
// [in] char* psz
// [out] WCHAR** ppwszOut
//
// Returns: HRESULT
// **************************************************************************
HRESULT AnsiToUnicode(char *psz, WCHAR **ppwszOut) {
	
	ULONG cch;
	
	if( psz == NULL ) {
		*ppwszOut = NULL;
		return NOERROR;
	}
	
	cch = strlen(psz) + 1;
	
	*ppwszOut = (WCHAR *)CoTaskMemAlloc(cch * 2);
	if( *ppwszOut == NULL )
		return E_OUTOFMEMORY;

	if( 0 == MultiByteToWideChar(CP_ACP, 0, psz, cch, *ppwszOut, cch) ) {
		CoTaskMemFree(*ppwszOut);
		*ppwszOut = NULL;
		return E_FAIL;
	}

	return NOERROR;
}

// **************************************************************************
// ParseCommandLine : Parses the command line.
//
// [in] int argc
// [in] WCHAR *argv[]
// Returns : 
//      true  = continue with execution.
//      false = stop.  An error was encountered, or the help info was displayed.
// Parsed commands are stored in global variables.
// **************************************************************************
bool ParseCommandLine(int argc, WCHAR *argv[], 
					  WCHAR **ppwszServer, WCHAR **ppwszSitecode, 
					  WCHAR **ppwszMachine, WCHAR **ppwszUser, 
					  WCHAR **ppwszPassword, bool *bPassAlloced)
{

	int iArg;	// argument
	int iLoop;  // index
	bool bPassword = false;
	*bPassAlloced = false;

	char password[255];

	for( iLoop = iArg = 1; iLoop < argc; iLoop++ ) {
		if( (*argv[iLoop] != L'-') && (*argv[iLoop] != L'/') ) {
			switch( iArg++ ) {
			case 1:
				// server
				*ppwszServer = argv[iLoop];
				bPassword = false;
				break;
			case 2:
				// machine
				*ppwszMachine = argv[iLoop];
				bPassword = false;
				break;
			default:
				if( bPassword ) {
					*ppwszPassword = argv[iLoop];
					bPassword = false;
					iArg--;
				} 
				else return false;
			}
		}
		else {
			if( !wcsnicmp(argv[iLoop] + 1, L"U:", 2) ) {
				*ppwszUser = argv[iLoop] + 3;				// User name
				bPassword = true;
			}
			else if( !wcsnicmp(argv[iLoop] + 1, L"S:", 2) ) {
				*ppwszSitecode = argv[iLoop] + 3;				// sitecode
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"?", 1) ) return false;	// help
		}
	}

	// Check for correct number of real arguments
	if( iArg != 3 ) return false;
	
	// Prompt user for password?
	if( !(*ppwszPassword) || wcscmp((*ppwszPassword), L"*") ) return true;

	// Display prompt
	printf("Enter Password for %S:", *ppwszUser);

	// If user did not abort password input...
	if( !PromptUserForPassword(password) ) return false;

	AnsiToUnicode(password, ppwszPassword);
	*bPassAlloced = true;

	return true;
}

// **************************************************************************
// RefreshSCF : Calls the RefreshSCF method of the SMS_SiteControlFile class
//
// [in] WCHAR* pwszSite
// [in] IWbemContext *pWbemContext
// [in] IWbemServices *pWbemServices
// 
// Returns: bool
//      true  success
//      false failure
// **************************************************************************
bool RefreshSCF(WCHAR *pwszSite, IWbemContext *pWbemContext, IWbemServices *pWbemServices)
{
	HRESULT hr;
	IWbemClassObject *pRefreshClass = NULL;
	IWbemClassObject *pOutInst = NULL;
	IWbemClassObject *pInParamClass = NULL;
	IWbemClassObject *pInParamInst = NULL;
    
	// Get the class object for the method definition
	hr = pWbemServices->GetObject(_bstr_t(CLASS_SMS_SiteControlFile), 0, pWbemContext, &pRefreshClass, NULL);
	if( FAILED(hr) )
	{
		return false;
	}

    // Get the input parameters class object
	hr = pRefreshClass->GetMethod(_bstr_t(SMS_SiteControlFile::METHOD_RefreshSCF), 0, &pInParamClass, NULL);
	pRefreshClass->Release();
	pRefreshClass = NULL;
    if( FAILED(hr) )
	{
		return false;
	}

	// Create an instance of the input parameters class object
	hr = pInParamClass->SpawnInstance(0, &pInParamInst);
	pInParamClass->Release();
	pInParamClass = NULL;
	if( FAILED(hr) )
	{
		return false;
	}

	// Set the properties of the input parameter instance
	VARIANT vSiteCode;				// SiteCode
	VariantInit(&vSiteCode);
	V_VT(&vSiteCode) = VT_BSTR;
	V_BSTR(&vSiteCode) = SysAllocString(pwszSite);

	hr = pInParamInst->Put(_bstr_t(SMS_SiteControlFile::RefreshSCF::In::PARAM_SiteCode), 0, &vSiteCode, 0);
	VariantClear(&vSiteCode);
	if( FAILED( hr) )
	{
		pInParamInst->Release();
		return false;
	}

	// Execute the Method
	hr = pWbemServices->ExecMethod(_bstr_t(CLASS_SMS_SiteControlFile), _bstr_t(SMS_SiteControlFile::METHOD_RefreshSCF),
									0, pWbemContext, pInParamInst, NULL, NULL);

	pInParamInst->Release();

	if( FAILED(hr) )
	{ 
		return false;
	}

	return true;
}

// **************************************************************************
// CommitSCF : Calls the CommitSCF method of the SMS_SiteControlFile class
//
// [in] WCHAR* pwszSite
// [in] IWbemContext *pWbemContext
// [in] IWbemServices *pWbemServices
// 
// Returns: bool
//      true  success
//      false failure
// **************************************************************************
bool CommitSCF(WCHAR *pwszSite, IWbemContext *pWbemContext, IWbemServices *pWbemServices)
{
	HRESULT hr;
	IWbemClassObject *pRefreshClass = NULL;
	IWbemClassObject *pOutInst = NULL;
	IWbemClassObject *pInParamClass = NULL;
	IWbemClassObject *pInParamInst = NULL;
    
	// Get the class object for the method definition
	hr = pWbemServices->GetObject(_bstr_t(CLASS_SMS_SiteControlFile), 0, pWbemContext, &pRefreshClass, NULL);
	if( FAILED(hr) )
	{
		return false;
	}

    // Get the input parameters class object
	hr = pRefreshClass->GetMethod(_bstr_t(SMS_SiteControlFile::METHOD_RefreshSCF), 0, &pInParamClass, NULL);
	pRefreshClass->Release();
	pRefreshClass = NULL;
    if( FAILED(hr) )
	{
		return false;
	}

	// Create an instance of the input parameters class object
	hr = pInParamClass->SpawnInstance(0, &pInParamInst);
	pInParamClass->Release();
	pInParamClass = NULL;
	if( FAILED(hr) )
	{
		return false;
	}

	// Set the properties of the input parameter instance
	VARIANT vSiteCode;				// SiteCode
	VariantInit(&vSiteCode);
	V_VT(&vSiteCode) = VT_BSTR;
	V_BSTR(&vSiteCode) = SysAllocString(pwszSite);

	hr = pInParamInst->Put(_bstr_t(SMS_SiteControlFile::CommitSCF::In::PARAM_SiteCode), 0, &vSiteCode, 0);
	VariantClear(&vSiteCode);
	if( FAILED(hr) )
	{
		pInParamInst->Release();
		return false;
	}

	// Execute the Method
	hr = pWbemServices->ExecMethod(_bstr_t(CLASS_SMS_SiteControlFile), _bstr_t(SMS_SiteControlFile::METHOD_CommitSCF),
									0, pWbemContext, pInParamInst, NULL, NULL);

	pInParamInst->Release();

	if( FAILED(hr) )
	{ 
		return false;
	}

	return true;
}

// **************************************************************************
// ReleaseSessionHandle : Release sessionhandle stored in bstr value in 
//   vHandle.
//
// [in] VARIANT* vHandle
// [in] IWbemServices* pWbemServices (reference to pointer)
// Returns: bool
//		true Success
//		false Failure
// **************************************************************************
bool ReleaseSessionHandle(VARIANT *vHandle, IWbemServices *pWbemServices) {
	
	IWbemClassObject *pSiteControlFile = NULL;
	IWbemClassObject *pMethParam = NULL;
	HRESULT hr;

	// Grab sitecontrolfile class
	hr = pWbemServices->GetObject(_bstr_t(CLASS_SMS_SiteControlFile), 0, NULL, &pSiteControlFile, NULL);
	if( FAILED(hr) ) {
		printf("ERROR: GetObject SMS_SiteControlFile failed\n");
		return false;
	}

	// extract the releasesessionhandle inparameter template
	hr = pSiteControlFile->GetMethod(_bstr_t(SMS_SiteControlFile::METHOD_ReleaseSessionHandle), 0, &pMethParam, NULL);
	if( FAILED(hr) ) {
		printf("ERROR: ReleaseSessionHandle in-param retrieval failed\n");
		pSiteControlFile->Release();
		return false;
	}

	// store the sessionhandle in the inparam
	hr = pMethParam->Put(_bstr_t(SMS_SiteControlFile::ReleaseSessionHandle::In::PARAM_SessionHandle), 0, vHandle, NULL);
	if( FAILED(hr) ) {
		printf("ERROR: Could not store sessionhandle in in-parameter object\n");
		pMethParam->Release();
		pSiteControlFile->Release();
		return false;
	}
	
	// execute
	hr = pWbemServices->ExecMethod(_bstr_t(CLASS_SMS_SiteControlFile), _bstr_t(SMS_SiteControlFile::METHOD_ReleaseSessionHandle), 0, NULL, pMethParam, NULL, NULL);
	pMethParam->Release();
	pSiteControlFile->Release();
	if( FAILED(hr) ) {
		printf("ERROR: ReleaseSessionHandle failed\n");
		return false;
	}

	return true;
}


// **************************************************************************
// PrepareContext : Create context object, set ApplcationName and MachineName
//
// [in] WCHAR *pwszApplication
// [out] IWbemContext* &rpContext (reference to pointer)
// Returns: bool
//		true Success
//		false Failure
// **************************************************************************
bool PrepareContext(WCHAR *pwszApplication, IWbemContext* &rpContext) {
	
	char szComputerName[16];
	DWORD cReturned = 0;

	WCHAR *pwszComputerName;

	HRESULT hr;
	VARIANT vVar;
	BSTR bstrApplication;
	BSTR bstrMachineName;

	if( rpContext == NULL ) {
		hr = CoCreateInstance(CLSID_WbemContext, NULL, CLSCTX_INPROC_SERVER, IID_IWbemContext, (void**)&rpContext);
		if( FAILED(hr) ) return false;
	}	
	
	bstrApplication = SysAllocString(pwszApplication);
	
	VariantInit(&vVar);
	V_VT(&vVar) = VT_BSTR;
	V_BSTR(&vVar) = bstrApplication;

	hr = rpContext->SetValue(_bstr_t(CONTEXTVALUE_ApplicationName), 0, &vVar);
	VariantClear(&vVar);
	if( FAILED(hr) ) {
		rpContext->Release();
		return false;
	}

	GetComputerName(szComputerName, &cReturned);

	AnsiToUnicode(szComputerName, &pwszComputerName);
	
	bstrMachineName = SysAllocString(pwszComputerName);

	V_VT(&vVar) = VT_BSTR;
	V_BSTR(&vVar) = bstrMachineName;

	hr = rpContext->SetValue(_bstr_t(CONTEXTVALUE_MachineName), 0, &vVar);
	VariantClear(&vVar);
	if( FAILED(hr) ) {
		rpContext->Release();
		return false;
	}

	return true;
}


// **************************************************************************
// wmain : Using wmain to get WCHAR argv
// **************************************************************************
extern "C" int wmain(int argc, WCHAR *argv[]) {
	bool bDisplayHelp;
	int iResult;
	WCHAR *pwszServer;
	WCHAR *pwszSitecode = NULL;
	WCHAR wszSitecode[4];
	WCHAR *pwszMachine;
	WCHAR *pwszUser = NULL;
	WCHAR *pwszPassword = NULL;

	WCHAR pwszNALPath[256];
	BSTR bstrPropname;
	BSTR bstrNALPath;
	
	IWbemServices *pWbemServices = NULL;
	IWbemContext *pWbemContext = NULL;
	IWbemClassObject *pMethParam = NULL;
	IWbemClassObject *pDistPointClass = NULL;
	IWbemClassObject *pDistPointInst = NULL;
	IWbemClassObject *pSiteSystemInst = NULL;
	IWbemClassObject *pSiteControlFile = NULL;

	VARIANT vSessionHandle;
	VARIANT vTemp;
	
	HRESULT hr;

	bool bPasswordAllocated = false;

	bDisplayHelp = ParseCommandLine(argc, argv, &pwszServer, &pwszSitecode, &pwszMachine, &pwszUser, &pwszPassword, &bPasswordAllocated);

	printf(
			"\nMakeDist - Make a computer a distribution point\n"
			"------------------------------------\n\n"
	);
	
	if( !bDisplayHelp ) {
		printf(
			"Usage:\n"
			"   makedist <server> <distribution point machine> [-s:<sitecode>]\n"
			"            [-u:<user> [<password> | *]]\n\n"
			"Where:\n"
			"   server: sms site computer name\n"
			"   sitecode: sms sitecode\n"
			"   distribution point machine: computer name of new distribution point\n"
			"   user: wbem userid\n"
			"   password: wbem password\n"
		);
		return 0;
	}

	iResult = Init(pwszServer, pwszUser, pwszPassword, wszSitecode, pWbemServices);

	if( iResult ) {
		printf("ERROR: Could not connect.\n");
		CoUninitialize();
		return 1;
	}

	if( pwszSitecode == NULL )
		pwszSitecode = wszSitecode;

	// get wbem locator
	hr = CoCreateInstance(CLSID_WbemContext, NULL, CLSCTX_INPROC_SERVER, IID_IWbemContext, (void**) &pWbemContext);
	if( FAILED(hr) ) {
		printf("ERROR: Could not create IWbemContext.\n");
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	// Set the ApplicationName and Machinename values in the context object
	if( !PrepareContext(L"SMS MakeDist", pWbemContext) ) {
		printf("ERROR: Could not prepare Wbem Context.\n");
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	// execute SMS_SiteControlFile::GetSessionHandle
	hr = pWbemServices->ExecMethod(_bstr_t(CLASS_SMS_SiteControlFile), _bstr_t(SMS_SiteControlFile::METHOD_GetSessionHandle), 0, NULL, NULL, &pMethParam, NULL);
	if( FAILED(hr) ) {
		printf("ERROR: ExecMethod GetSessionHandle failed.\n");
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	VariantInit(&vSessionHandle);

	// Extract the SessionHandle from the method out-parameter instance
	hr = pMethParam->Get(_bstr_t(SMS_SiteControlFile::GetSessionHandle::Out::PARAM_SessionHandle), 0, &vSessionHandle, NULL, NULL);
	pMethParam->Release();
	if( FAILED(hr) ) {
		printf("ERROR: Get Sessionhandle failed.\n");
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}
	
	// Store the sessionhandle in a generic context object
	hr = pWbemContext->SetValue(_bstr_t(CONTEXTVALUE_SessionHandle), 0, &vSessionHandle);
	if( FAILED(hr) ) {
		printf("ERROR: Context SetValue \"SessionHandle\" failed.\n");
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);		
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	// Refresh the SiteControlFile
	RefreshSCF(pwszSitecode, pWbemContext, pWbemServices);

	// Get a SMS_SCI_SysResUse Class
	hr = pWbemServices->GetObject(_bstr_t(CLASS_SMS_SCI_SysResUse), 0, pWbemContext, &pDistPointClass, NULL);
	if( FAILED(hr) ) {
		printf("ERROR: GetObject SMS_SCI_SysResUse\n");
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	// Tell wbem we're making an instance
	hr = pDistPointClass->SpawnInstance(0, &pDistPointInst);
	pDistPointClass->Release();
	if( FAILED(hr) ) {
		printf("ERROR: SMS_SCI_SysResUse SpawnInstance failed.\n");
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	// construct nalpath from cmdline params
	swprintf(pwszNALPath, L"[\"Display=\\\\%wS\\\"]MSWNET:[\"SMS_SITE=%wS\"]\\\\%wS\\", pwszMachine, pwszSitecode, pwszMachine);

	bstrNALPath = SysAllocString(pwszNALPath);
	if( !bstrNALPath ) {
		printf("ERROR: Could not allocate memory for bstr\n");
		pDistPointInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	V_VT(&vTemp) = VT_BSTR;
	V_BSTR(&vTemp) = bstrNALPath;

	// store nalpath in sysresuse instance
	hr = pDistPointInst->Put(_bstr_t(SMS_SCI_SysResUse::PROP_NALPath), 0, &vTemp, NULL);
	VariantClear(&vTemp);
	if( FAILED(hr) ) {
		printf("ERROR: DistPoint->Put NALPath failed\n");
		pDistPointInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	V_VT(&vTemp) = VT_BSTR;
	V_BSTR(&vTemp) = _bstr_t(L"Windows NT Server");

	// store nal type
	hr = pDistPointInst->Put(_bstr_t(SMS_SCI_SysResUse::PROP_NALType), 0, &vTemp, NULL);
	VariantClear(&vTemp);
	if( FAILED(hr) ) {
		printf("ERROR: DistPoint->Put NALType failed\n");
		pDistPointInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	V_VT(&vTemp) = VT_BSTR;
	V_BSTR(&vTemp) = _bstr_t(L"SMS Distribution Point");

	// store rolename
	hr = pDistPointInst->Put(_bstr_t(SMS_SCI_SysResUse::PROP_RoleName), 0, &vTemp, NULL);
	VariantClear(&vTemp);
	if( FAILED(hr) ) {
		printf("ERROR: DistPoint->Put RoleName failed\n");
		pDistPointInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	bstrPropname = SysAllocString(pwszSitecode);
	if( !bstrPropname) {
		printf("ERROR: SysAllocString failed\n");
		pDistPointInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	V_VT(&vTemp) = VT_BSTR;
	V_BSTR(&vTemp) = bstrPropname;

	// store sitecode
	hr = pDistPointInst->Put(_bstr_t(SMS_SiteControlItem::PROP_SiteCode), 0, &vTemp, NULL);
	VariantClear(&vTemp);
	if( FAILED(hr) ) {
		printf("ERROR: DistPoint->Put Sitecode failed\n");
		pDistPointInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	// clone this instance so we can use all the properties for another
	hr = pDistPointInst->Clone(&pSiteSystemInst);
	if( FAILED(hr) ) {
		printf("ERROR: DistPoint->Clone failed\n");
		pDistPointInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	// Commit this instance to winmgmt
	hr = pWbemServices->PutInstance(pDistPointInst, WBEM_FLAG_CREATE_ONLY, pWbemContext, NULL);
	pDistPointInst->Release();
	if( FAILED(hr) ) {
		printf("ERROR: Instance already exists\n");
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	V_VT(&vTemp) = VT_BSTR;
	V_BSTR(&vTemp) = _bstr_t(L"SMS Site System");

	// Alter the rolename for our cloned instance
	hr = pSiteSystemInst->Put(_bstr_t(SMS_SCI_SysResUse::PROP_RoleName), 0, &vTemp, NULL);
	VariantClear(&vTemp);
	if( FAILED(hr) ) {
		printf("ERROR: SiteSystem->Put Rolename failed.\n");
		pSiteSystemInst->Release();
		ReleaseSessionHandle(&vSessionHandle, pWbemServices);
		VariantClear(&vSessionHandle);
		pWbemContext->Release();
		pWbemServices->Release();
		if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
		CoUninitialize();
		return 1;
	}

	hr = pWbemServices->PutInstance(pSiteSystemInst, WBEM_FLAG_CREATE_ONLY, pWbemContext, NULL);
	pSiteSystemInst->Release();
	if( FAILED(hr) ) {
		// this isn't a problem at all.
	}

	// Commit the changes to the SiteControlFile
	CommitSCF(pwszSitecode, pWbemContext, pWbemServices);

	ReleaseSessionHandle(&vSessionHandle, pWbemServices);
	VariantClear(&vSessionHandle);
		
	pWbemContext->Release();
	pWbemServices->Release();

	if( bPasswordAllocated ) CoTaskMemFree(pwszPassword);
	
	CoUninitialize();

	return 0;
}