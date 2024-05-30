// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// Siteboun - Version 1.0
//
// Siteboun Demonstrates:
//   IWbemLocator->ConnectServer
//   IWbemServices->GetObject
//   IWbemServices->ExecQuery
//   IWbemServices->ExecMethod
//   IWbemServices->PutInstance
//   IEnumWbemClassObject->Next
//   IWbemClassObject->Get
//   IWbemClassObject->Put
//   SetInterfaceSecurity
//   Working with VARIANT and SAFEARRAY
//
// Description:
//   SiteBoun performs operations on instances of SMS_SCI_SiteAssignment.
//   This class configures the boundaries of an SMS Site using a string 
//   array of IP subnets.  Siteboun allows the user to export the array 
//   of addresses to a text file, import a text file to replace the array, 
//   or append a text file to the end of the array.
//
// *************************************************************

#include <stdio.h>
#include <conio.h>
#include <comdef.h>
#include <wbemidl.h>
#include <wbemsec.h>

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
// ParseCommandLine : Parse the command-line arguments
//
// [in] int argc
// [in] WCHAR** argv
// [out] WCHAR** ppwszServer
// [out] WCHAR** ppwszSitecode
// [out] WCHAR** ppwszFilename
// [out] WCHAR** ppwszUser
// [out] WCHAR** ppwszPassword
// [out] int *iMode
// [out] bool *bPassAlloced
//
// Returns: bool
//      true  success
//      false Display Help
// **************************************************************************
bool ParseCommandLine(int argc, WCHAR *argv[], 
					  WCHAR **ppwszServer, WCHAR **ppwszSitecode,
					  WCHAR **ppwszFilename, WCHAR **ppwszUser, 
					  WCHAR **ppwszPassword, int *iMode, bool *bPassAlloced)
{

	int iArg;	// argument
	int iLoop;  // index
	bool bPassword = false;
	*bPassAlloced = false;

	char password[MAX_PASSWORD_LENGTH];

	for( iLoop = iArg = 1; iLoop < argc; iLoop++ ) {
		if( (*argv[iLoop] != L'-') && (*argv[iLoop] != L'/') ) {
			switch( iArg++ ) {
			case 1:
				// filename
				*ppwszFilename = argv[iLoop];
				bPassword = false;
				break;

			case 2:
				// server
				*ppwszServer = argv[iLoop];
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
				*ppwszSitecode = argv[iLoop] + 3;				// Sitecode
				bPassword = false;
			}
			else if( !wcsnicmp(argv[iLoop] + 1, L"A", 1) ) {
				*iMode = 1;			// Append mode
				bPassword = false;
			}
			else if( !wcsnicmp(argv[iLoop] + 1, L"E", 1) ) {
				*iMode = 2;			// Export mode
				bPassword = false;
			}
			else if( !wcsnicmp(argv[iLoop] + 1, L"I", 1) ) {
				*iMode = 0;			// Insert Mode
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
bool ReleaseSessionHandle(IWbemContext *pWbemContext, IWbemServices *pWbemServices) {
	
	IWbemClassObject *pSiteControlFile = NULL;
	IWbemClassObject *pMethParam = NULL;
	HRESULT hr;

	VARIANT vHandle;

	hr = pWbemContext->GetValue(_bstr_t(CONTEXTVALUE_SessionHandle), 0, &vHandle);

	// Grab sitecontrolfile class
	hr = pWbemServices->GetObject(_bstr_t(CLASS_SMS_SiteControlFile), 0, NULL, &pSiteControlFile, NULL);
	if( FAILED(hr) ) {
		printf("ERROR: GetObject SMS_SiteControlFile failed\n");
		VariantClear(&vHandle);
		return false;
	}

	// extract the releasesessionhandle inparameter template
	hr = pSiteControlFile->GetMethod(_bstr_t(SMS_SiteControlFile::METHOD_ReleaseSessionHandle), 0, &pMethParam, NULL);
	if( FAILED(hr) ) {
		printf("ERROR: ReleaseSessionHandle in-param retrieval failed\n");
		pSiteControlFile->Release();
		VariantClear(&vHandle);
		return false;
	}

	// store the sessionhandle in the inparam
	hr = pMethParam->Put(_bstr_t(SMS_SiteControlFile::ReleaseSessionHandle::In::PARAM_SessionHandle), 0, &vHandle, NULL);
	VariantClear(&vHandle);
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
// PrepareContext : Create context object, set ApplcationName and MachineName, and 
//                  get a session handle for editting the Site Control File
//
// [in] WCHAR *pwszApplication
// [out] IWbemContext **ppContext
// [in] IWbemServices *pWbemServices
//
// Returns: bool
//		true Success
//		false Failure
// **************************************************************************
bool PrepareContext(WCHAR *pwszApplication, IWbemContext** ppWbemContext, IWbemServices *pWbemServices) {
	
	char szComputerName[16];
	DWORD cReturned = 0;

	WCHAR *pwszComputerName;

	HRESULT hr;
	VARIANT vVar;
	BSTR bstrApplication;
	BSTR bstrMachineName;

	IWbemClassObject *pMethParam;
	VARIANT vSessionHandle;

	// Create an IWbemContext object
	hr = CoCreateInstance(CLSID_WbemContext, NULL, CLSCTX_INPROC_SERVER, IID_IWbemContext, (void**)ppWbemContext);
	if( FAILED(hr) ) 
	{
		printf("ERROR: Could not create IWbemContext.\n");
		return false;
	}
	
	bstrApplication = SysAllocString(pwszApplication);
	
	VariantInit(&vVar);
	V_VT(&vVar) = VT_BSTR;
	V_BSTR(&vVar) = bstrApplication;

	hr = (*ppWbemContext)->SetValue(_bstr_t(CONTEXTVALUE_ApplicationName), 0, &vVar);
	VariantClear(&vVar);
	if( FAILED(hr) ) {
		(*ppWbemContext)->Release();
		return false;
	}

	GetComputerName(szComputerName, &cReturned);

	AnsiToUnicode(szComputerName, &pwszComputerName);
	
	bstrMachineName = SysAllocString(pwszComputerName);

	V_VT(&vVar) = VT_BSTR;
	V_BSTR(&vVar) = bstrMachineName;

	hr = (*ppWbemContext)->SetValue(_bstr_t(CONTEXTVALUE_MachineName), 0, &vVar);
	VariantClear(&vVar);
	if( FAILED(hr) ) {
		(*ppWbemContext)->Release();
		return false;
	}

	// execute SMS_SiteControlFile::GetSessionHandle
	hr = pWbemServices->ExecMethod(_bstr_t(CLASS_SMS_SiteControlFile), _bstr_t(SMS_SiteControlFile::METHOD_GetSessionHandle), 0, NULL, NULL, &pMethParam, NULL);
	if( FAILED(hr) ) 
	{
		printf("ERROR: Could not GetSessionHandle\n");
		return false;
	}

	// Extract the SessionHandle from the method out-parameter instance
	hr = pMethParam->Get(_bstr_t(SMS_SiteControlFile::GetSessionHandle::Out::PARAM_SessionHandle), 0, &vSessionHandle, NULL, NULL);
	pMethParam->Release();
	if( FAILED(hr) ) 
	{
		(*ppWbemContext)->Release();
		printf("ERROR: Could not retrieve SessionHandle\n");
		ReleaseSessionHandle(*ppWbemContext, pWbemServices);		
		VariantClear(&vSessionHandle);
		return false;
	}
	
	// Store the sessionhandle in a generic context object
	hr = (*ppWbemContext)->SetValue(_bstr_t(CONTEXTVALUE_SessionHandle), 0, &vSessionHandle);
	if( FAILED(hr) ) 
	{
		(*ppWbemContext)->Release();
		printf("ERROR: Could not add SessionHandle to context object\n");
		ReleaseSessionHandle(*ppWbemContext, pWbemServices);		
		VariantClear(&vSessionHandle);
		return false;
	}

	return true;
}


// **************************************************************************
// Export : Reads Site Boundaries from specified Site, dumps to specified file.
//
// [in] WCHAR* pwszFilename
// [in] WCHAR* pwszServer
// [in] WCHAR* pwszSite
// [in] WCHAR* pwszUser
// [in] WCHAR* pwszPassword
// 
// Returns: bool
//      true  success
//      false failure
// **************************************************************************
bool Export(WCHAR *pwszFilename, WCHAR *pwszServer, WCHAR *pwszSite, WCHAR *pwszUser, WCHAR *pwszPassword) {
		
	FILE *fFile;
	IWbemServices *pWbemServices = NULL;
	IWbemClassObject *pInst = NULL;
	IWbemContext *pWbemContext = NULL;
	WCHAR pwszObjPath[256];
	WCHAR wszSitecode[4];

	VARIANT vDetails;
	VARIANT vTypes;
	BSTR bstrAssignDetail;
	BSTR bstrAssignType;
	long saindex[1];
	LONG lLBound;
	LONG lUBound;
	LONG i;

	HRESULT hr;

	if( fFile = _wfopen(pwszFilename, L"w") ) {
		if( Init(pwszServer, pwszUser, pwszPassword, wszSitecode, pWbemServices) ) {
			printf("ERROR: Could not connect.\n");
			fclose(fFile);
			return false;
		}

		if( pwszSite == NULL )
			pwszSite = wszSitecode;

		if( wcslen(pwszSite) != 3 ) {
			printf("ERROR: Sitecode must be 3 characters long.\n");
			return false;
		}

		if(!PrepareContext(L"SiteBoun Sample", &pWbemContext, pWbemServices))
		{
			printf("ERROR: Unable to Create the Context Object\n");
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		if(!RefreshSCF(pwszSite, pWbemContext, pWbemServices))
		{
			printf("ERROR: Unable to Refresh the Site Control File\n");
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		swprintf(pwszObjPath, L"%s.%s=2,%s=\"Site Assignment\",%s=\"Site Assignment\",%s=\"%s\"", CLASS_SMS_SCI_SiteAssignment, SMS_SiteControlItem::PROP_FileType, SMS_SiteControlItem::PROP_ItemName, SMS_SiteControlItem::PROP_ItemType, SMS_SiteControlItem::PROP_SiteCode, pwszSite);
		
		hr = pWbemServices->GetObject(_bstr_t(pwszObjPath), 0, pWbemContext, &pInst, NULL);
		if( FAILED(hr) ) {
			printf("ERROR: Could not retrieve SiteAssignments for %wS.\n", pwszSite);
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		VariantInit(&vDetails);		
		VariantInit(&vTypes);
		
		hr = pInst->Get(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignDetails), 0, &vDetails, 0, 0);
		if( FAILED(hr) ) {
			printf("ERROR: Could not retrieve \"AssignDetails\" array.\n", pwszSite);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		hr = pInst->Get(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignTypes), 0, &vTypes, 0, 0);
		pInst->Release();
		if( FAILED(hr) ) {
			VariantClear(&vDetails);
			printf("ERROR: Could not retrieve \"AssignTypes\" array.\n", pwszSite);
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		hr = SafeArrayGetLBound(V_ARRAY(&vDetails), 1, &lLBound);

		hr = SafeArrayGetUBound(V_ARRAY(&vDetails), 1, &lUBound);

		for(i = lLBound; i <= lUBound; i++) {
			saindex[0] = i;
			hr = SafeArrayGetElement(V_ARRAY(&vDetails), saindex, &bstrAssignDetail);
			hr = SafeArrayGetElement(V_ARRAY(&vTypes), saindex, &bstrAssignType);
			fprintf(fFile, "%wS,%wS\n", bstrAssignDetail, bstrAssignType);
			//printf("%wS,%wS\n", bstrAssignDetail, bstrAssignType);
			SysFreeString(bstrAssignDetail);
			SysFreeString(bstrAssignType);
		}

		VariantClear(&vDetails);
		VariantClear(&vTypes);

		ReleaseSessionHandle(pWbemContext, pWbemServices);

		pWbemServices->Release();
		CoUninitialize();
		fclose(fFile);
	}
	else {
		printf("ERROR: Could not open %wS for writing.\n", pwszFilename);
		return false;
	}
	return true;
}


// **************************************************************************
// EntryIsUnique : Searches psaArray for pwszEntry
//
// [in] SAFEARRAY* psaArray
// [in] WCHAR* pwszEntry
//
// 
// Returns: bool
//      true  The entry was not found (IsUnique)
//      false The entry was found
// **************************************************************************
bool EntryIsUnique(SAFEARRAY *psaArray, WCHAR *pwszEntry) {
	
	long lUBound;

	BSTR bstrArrayElement;
	long saIndex[1];
	
	HRESULT hr;
	
	hr = SafeArrayGetUBound(psaArray, 1, &lUBound);
	for( saIndex[0] = 0; saIndex[0] <= lUBound; saIndex[0]++ ) {
		SafeArrayGetElement(psaArray, saIndex, &bstrArrayElement);
		if( !wcscmp(bstrArrayElement, pwszEntry) ) {
			SysFreeString(bstrArrayElement);
			return false;
		}
		SysFreeString(bstrArrayElement);
	}

	return true;
}

// **************************************************************************
// Append : Extends site boundaries for specified site with entries from
//          specified file.
//
// [in] WCHAR* pwszFilename
// [in] WCHAR* pwszServer
// [in] WCHAR* pwszSite
// [in] WCHAR* pwszUser
// [in] WCHAR* pwszPassword
// 
// Returns: bool
//      true  success
//      false failure
// **************************************************************************
bool Append(WCHAR *pwszFilename, WCHAR *pwszServer, WCHAR *pwszSite,  WCHAR *pwszUser, WCHAR *pwszPassword) {
	
	FILE *fFile;
	IWbemServices *pWbemServices = NULL;
	IWbemClassObject *pInst = NULL;
	WCHAR pwszObjPath[256];
	WCHAR wszSitecode[4];
	WCHAR pwszLine[255];
	WCHAR *pwszNewline;
	WCHAR *pwszType;
	VARIANT vDetails;
	VARIANT vTypes;
	BSTR bstrTemp;
	IWbemContext *pWbemContext;

	int iterator = 0;
	long lUBound = 0;
	long saindexes[1];
	SAFEARRAYBOUND sabound[1];

	HRESULT hr;

	if( fFile = _wfopen(pwszFilename, L"r") ) {
		if( Init(pwszServer, pwszUser, pwszPassword, wszSitecode, pWbemServices) ) {
			printf("ERROR: Could not connect.\n");
			fclose(fFile);
			return false;
		}

		if( pwszSite == NULL )
			pwszSite = wszSitecode;

		if( wcslen(pwszSite) != 3 ) {
			printf("ERROR: Sitecode isn't 3 characters long.\n");
			return false;
		}

		if(!PrepareContext(L"SiteBoun Sample", &pWbemContext, pWbemServices))
		{
			printf("ERROR: Unable to Create the Context Object\n");
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		if(!RefreshSCF(pwszSite, pWbemContext, pWbemServices))
		{
			printf("ERROR: Unable to Refresh the Site Control File\n");
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		swprintf(pwszObjPath, L"%s.%s=2,%s=\"Site Assignment\",%s=\"Site Assignment\",%s=\"%s\"", CLASS_SMS_SCI_SiteAssignment, SMS_SiteControlItem::PROP_FileType, SMS_SiteControlItem::PROP_ItemName, SMS_SiteControlItem::PROP_ItemType, SMS_SiteControlItem::PROP_SiteCode, pwszSite);
		
		// Retrieve specific instance of SMS_SCI_SiteAssignment
		hr = pWbemServices->GetObject(_bstr_t(pwszObjPath), 0, pWbemContext, &pInst, NULL);
		if( FAILED(hr) ) {
			printf("ERROR: Could not retrieve SiteAssignments for %wS.\n", pwszSite);
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		VariantInit(&vDetails);
		VariantInit(&vTypes);

		// Retrieve AssignDetails array property
		hr = pInst->Get(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignDetails), 0, &vDetails, 0, 0);
		if( FAILED(hr) ) {
			printf("ERROR: Could not retrieve \"AssignDetails\" array.\n", pwszSite);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		// Retrieve AssignTypes array property
		hr = pInst->Get(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignTypes), 0, &vTypes, 0, 0);
		if( FAILED(hr) ) {
			VariantClear(&vDetails);
			pInst->Release();
			printf("ERROR: Could not retrieve \"AssignTypes\" array.\n", pwszSite);
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		printf("\nAppending Entry: ");
		
		// Read the file
		while( !feof(fFile) ) {

			// Get a line from the file
			if( fgetws(pwszLine, 255, fFile) ) {

				printf("%d", ++iterator);
								
				// Strip newline if necessary
				if( pwszNewline = wcschr(pwszLine, L'\n') ) *pwszNewline = L'\0';

				if( wcslen(pwszLine) > 3 ) {

					// If a type was not given, default to "IP Subnets"
					if( pwszType = wcschr(pwszLine, L',') ) {
						*pwszType = L'\0';
						pwszType++;
					}
					else pwszType = L"IP Subnets";
					
					// If the entry in the text file is not already in the AssignDetails array...
					if( EntryIsUnique(V_ARRAY(&vDetails), pwszLine) ) {
						
						// Increment the array upper bound
						hr = SafeArrayGetUBound(V_ARRAY(&vDetails), 1, &lUBound);
						sabound[0].lLbound = 0;
						sabound[0].cElements = lUBound + 2;
						saindexes[0] = lUBound + 1;
						SafeArrayRedim(V_ARRAY(&vDetails), sabound);
						SafeArrayRedim(V_ARRAY(&vTypes), sabound);

						// Store the entry from the file in the new array entry
						bstrTemp = SysAllocString(pwszLine);
						hr = SafeArrayPutElement(V_ARRAY(&vDetails), saindexes, bstrTemp);
						SysFreeString(bstrTemp);

						bstrTemp = SysAllocString(pwszType);
						hr = SafeArrayPutElement(V_ARRAY(&vTypes), saindexes, bstrTemp);
						SysFreeString(bstrTemp);

						printf("\b");
						if( ((long)(iterator / 10)) > 0 ) printf("\b");
						if( ((long)(iterator / 10)) >= 10 ) printf("\b");
						if( ((long)(iterator / 10)) >= 100 ) printf("\b");
						if( ((long)(iterator / 10)) >= 1000 ) printf("\b");
						if( ((long)(iterator / 10)) >= 10000 ) printf("\b");
						if( ((long)(iterator / 10)) >= 100000 ) printf("\b");

					} 
					else {
						
						printf("\n  **  Warning: Duplicate Entry Skipped (%wS)\nAppending Entry: ", pwszLine);

					}
				}
			}
		}

		printf("\nDone!\n");

		// Store our altered array back into the instance
		hr = pInst->Put(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignDetails), 0, &vDetails, 0);
		if( FAILED(hr) ) {
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		hr = pInst->Put(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignTypes), 0, &vTypes, 0);
		if( FAILED(hr) ) {
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		// Commit the instance
		hr = pWbemServices->PutInstance(pInst, WBEM_FLAG_CREATE_OR_UPDATE, pWbemContext, NULL);
		if( FAILED(hr) ) {
			printf("ERROR: PutInstance failed.  Changes may not have been stored.\n");
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		if(!CommitSCF(pwszSite, pWbemContext, pWbemServices))
		{
			printf("ERROR: CommitSCF failed.  Changes may not have been stored.\n");
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		ReleaseSessionHandle(pWbemContext, pWbemServices);

		VariantClear(&vDetails);
		VariantClear(&vTypes);
		pInst->Release();
		pWbemServices->Release();
		CoUninitialize();
		fclose(fFile);
	}
	else {
		printf("ERROR: Could not open %wS for writing.\n", pwszFilename);
		return false;
	}

	return true;
}


// **************************************************************************
// Import : Overwrites site boundaries for specified site with entries from
//          specified file.
//
// [in] WCHAR* pwszFilename
// [in] WCHAR* pwszServer
// [in] WCHAR* pwszSite
// [in] WCHAR* pwszUser
// [in] WCHAR* pwszPassword
// 
// Returns: bool
//      true  success
//      false failure
// **************************************************************************
bool Import(WCHAR *pwszFilename, WCHAR *pwszServer, WCHAR *pwszSite, WCHAR *pwszUser, WCHAR *pwszPassword) {
	FILE *fFile;
	IWbemServices *pWbemServices = NULL;
	IWbemClassObject *pInst = NULL;
	WCHAR pwszObjPath[256];
	WCHAR pwszLine[255];
	WCHAR wszSitecode[4];
	WCHAR *pwszNewline;
	WCHAR *pwszType;
	SAFEARRAY *psaDetails;
	SAFEARRAY *psaTypes;
	VARIANT vDetails;
	VARIANT vTypes;
	BSTR bstrTemp;
	IWbemContext *pWbemContext;

	int iterator = 0;
	long lUBound = 0;
	long saindexes[1];
	SAFEARRAYBOUND sabound[1];

	HRESULT hr;

	if( fFile = _wfopen(pwszFilename, L"r") ) {

		if( Init(pwszServer, pwszUser, pwszPassword, wszSitecode, pWbemServices) ) {
			printf("ERROR: Could not connect.\n");
			fclose(fFile);
			return false;
		}

		if( pwszSite == NULL )
			pwszSite = wszSitecode;

		if( wcslen(pwszSite) != 3 ) {
			printf("ERROR: Sitecode isn't 3 characters long.\n");
			return false;
		}

		if(!PrepareContext(L"SiteBoun Sample", &pWbemContext, pWbemServices))
		{
			printf("ERROR: Unable to Create the Context Object\n");
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		if(!RefreshSCF(pwszSite, pWbemContext, pWbemServices))
		{
			printf("ERROR: Unable to Refresh the Site Control File\n");
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		swprintf(pwszObjPath, L"%s.%s=2,%s=\"Site Assignment\",%s=\"Site Assignment\",%s=\"%s\"", CLASS_SMS_SCI_SiteAssignment, SMS_SiteControlItem::PROP_FileType, SMS_SiteControlItem::PROP_ItemName, SMS_SiteControlItem::PROP_ItemType, SMS_SiteControlItem::PROP_SiteCode, pwszSite);
		
		// Retrieve specific instance of SMS_SCI_SiteAssignment
		hr = pWbemServices->GetObject(_bstr_t(pwszObjPath), 0, pWbemContext, &pInst, NULL);
		if( FAILED(hr) ) {
			printf("ERROR: Could not retrieve SiteAssignments for %wS.\n", pwszSite);
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		VariantInit(&vDetails);
		VariantInit(&vTypes);

		sabound[0].lLbound = 0;
		sabound[0].cElements = 0;

		psaDetails = SafeArrayCreate(VT_BSTR, 1, sabound);

		psaTypes = SafeArrayCreate(VT_BSTR, 1, sabound);

		V_VT(&vDetails) = VT_BSTR | VT_ARRAY;
		V_VT(&vTypes) = VT_BSTR | VT_ARRAY;

		V_ARRAY(&vDetails) = psaDetails;
		V_ARRAY(&vTypes) = psaTypes;
		
		printf("\nImporting Entry: ");
		
		// Read the file
		while( !feof(fFile) ) {

			// Get a line from the file
			if( fgetws(pwszLine, 255, fFile) ) {

				printf("%d", ++iterator);

				// Strip newline if necessary
				if( pwszNewline = wcschr(pwszLine, L'\n') ) *pwszNewline = L'\0';

				if( wcslen(pwszLine) > 3 ) {

					// If a type was not given, default to "IP Subnets"
					if( pwszType = wcschr(pwszLine, L',') ) {
						*pwszType = L'\0';
						pwszType++;
					}
					else pwszType = L"IP Subnets";

					// Increment the array upper bound
					hr = SafeArrayGetUBound(V_ARRAY(&vDetails), 1, &lUBound);
					sabound[0].lLbound = 0;
					sabound[0].cElements = lUBound + 2;   // UBound is -1 if cElements is 0 (when lLbound is 0)
					saindexes[0] = lUBound + 1;
					SafeArrayRedim(V_ARRAY(&vDetails), sabound);
					SafeArrayRedim(V_ARRAY(&vTypes), sabound);

					// Store the entry from the file in the new array entry
					bstrTemp = SysAllocString(pwszLine);
					hr = SafeArrayPutElement(V_ARRAY(&vDetails), saindexes, bstrTemp);
					SysFreeString(bstrTemp);

					bstrTemp = SysAllocString(pwszType);
					hr = SafeArrayPutElement(V_ARRAY(&vTypes), saindexes, bstrTemp);
					SysFreeString(bstrTemp);
				}
				
				printf("\b");
				if( ((long)(iterator / 10)) > 0 ) printf("\b");
				if( ((long)(iterator / 10)) >= 10 ) printf("\b");
				if( ((long)(iterator / 10)) >= 100 ) printf("\b");
				if( ((long)(iterator / 10)) >= 1000 ) printf("\b");
				if( ((long)(iterator / 10)) >= 10000 ) printf("\b");
				if( ((long)(iterator / 10)) >= 100000 ) printf("\b");   // just in case
				
			}

		}

		printf("\nDone!\n");

		// Store our arrays in the AssignDetails and AssignTypes properties
		hr = pInst->Put(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignDetails), 0, &vDetails, 0);
		if( FAILED(hr) ) {
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		hr = pInst->Put(_bstr_t(SMS_SCI_SiteAssignment::PROP_AssignTypes), 0, &vTypes, 0);
		if( FAILED(hr) ) {
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		// Commit the instance
		hr = pWbemServices->PutInstance(pInst, WBEM_FLAG_CREATE_OR_UPDATE, pWbemContext, NULL);
		if( FAILED(hr) ) {
			printf("ERROR: PutInstance failed.  Changes may not have been stored.\n");
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}

		if(!CommitSCF(pwszSite, pWbemContext, pWbemServices))
		{
			printf("ERROR: CommitSCF failed.  Changes may not have been stored.\n");
			VariantClear(&vDetails);
			VariantClear(&vTypes);
			pInst->Release();
			pWbemServices->Release();
			CoUninitialize();
			fclose(fFile);
			return false;
		}
		
		VariantClear(&vDetails);
		VariantClear(&vTypes);
		pInst->Release();
		pWbemServices->Release();
		CoUninitialize();
		fclose(fFile);
	}
	else {
		printf("ERROR: Could not open %wS for writing.\n", pwszFilename);
		return false;
	}

	return true;
}

// **************************************************************************
// wmain : Using wmain to get WCHAR argv
// **************************************************************************
extern "C" int wmain(int argc, WCHAR *argv[]) {

	WCHAR *pwszServer = NULL;
	WCHAR *pwszSite = NULL;
	WCHAR *pwszFilename = NULL;
	WCHAR *pwszUser = NULL;
	WCHAR *pwszPassword = NULL;

	int iMode = 1;
	bool bPasswordAllocated = false;
	bool bDisplayHelp = false;

	bDisplayHelp = ParseCommandLine(argc, argv, &pwszServer, &pwszSite, &pwszFilename, &pwszUser, &pwszPassword, &iMode, &bPasswordAllocated);

	printf(
		"\nSiteBoun -- Site Boundary Import / Export\n"
		"-----------------------------------------\n"
		);
	
	if( !bDisplayHelp ) {
		printf(
			"Usage:\n"
			"  SiteBoun <filename> <server> [-S:<sitecode>] [-E | -I | -A] [-U:<user> [<password> | *]]\n"
			"\n"
			"Where:\n"
			"  Filename  : Textfile name\n"
			"  Server    : SMS provider location\n"
			"  -S        : Sitecode to process site boundaries (default: login sitecode)\n"
			"  -E        : Export existing site boundary addresses to specified file.\n"
			"  -I        : Import.  Overwrite existing site boundaries with specified file.\n"
			"  -A        : Append.  This is the default.\n"
		);
		return 0;
	}

	switch( iMode ) {
	case 2:
		if( Export(pwszFilename, pwszServer, pwszSite, pwszUser, pwszPassword) ) {
			if(bPasswordAllocated) CoTaskMemFree(pwszPassword);
			return 0;
		}
		else {
			if(bPasswordAllocated) CoTaskMemFree(pwszPassword);
			return 1;
		}

	case 1:
		if( Append(pwszFilename, pwszServer, pwszSite, pwszUser, pwszPassword) ) {
			if(bPasswordAllocated) CoTaskMemFree(pwszPassword);
			return 0;
		}
		else {
			if(bPasswordAllocated) CoTaskMemFree(pwszPassword);
			return 1;
		}

	case 0:
		if( Import(pwszFilename, pwszServer, pwszSite, pwszUser, pwszPassword) ) {
			if(bPasswordAllocated) CoTaskMemFree(pwszPassword);
			return 0;
		}
		else {
			if(bPasswordAllocated) CoTaskMemFree(pwszPassword);
			return 1;
		}
		return 0;

	default:
		return 1;

	}	
}

