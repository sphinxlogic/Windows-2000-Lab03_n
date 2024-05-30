// *************************************************************
// Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// MakeDPG - Version 1.0
//
// makedpg Demonstrates:
//   IWbemLocator->ConnectServer
//   IWbemContext->SetValue
//   IWbemServices->GetObject
//   IWbemServices->ExecQuery
//   IWbemServices->PutInstance
//   IEnumWbemClassObject->Next
//   IWbemClassObject->Get
//   IWbemClassObject->Put
//   SetInterfaceSecurity
//   Working with VARIANT and SAFEARRAY
//
// Description:
//   makedpg creates instances of SMS_DistributionPointGroup.
//   Instances of SMS_DistributionPointGroup contain an array
//   defining which distribution points are included in the
//   group.  To populate this array, Makedpg reads entries from
//   a text file.  As each entry is read from the file, it is
//   checked against a list of available distribution points
//   in the site control file.  If the entry from the file is
//   a valid distribution point, it is added to the distribution
//   point group array.
//
// *************************************************************

#include <stdio.h>
#include <conio.h>
#include <comdef.h>
#include <wbemidl.h>
#include <winbase.h>  // for GetComputerName
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
					  WCHAR **ppwszFilename, WCHAR **ppwszGroupname, WCHAR **ppwszUser, 
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
				// filename
				*ppwszFilename = argv[iLoop];
				bPassword = false;
				break;

			case 2:
				// DistributionPointGroup name
				*ppwszGroupname = argv[iLoop];
				bPassword = false;
				break;
			
			case 3:
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
				*ppwszSitecode = argv[iLoop] + 3;				// SiteCode
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"?", 1) ) return false;	// help
		}
	}

	// Check for correct number of real arguments
	if( iArg != 4 ) return false;
	
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

	WCHAR *pwszServer = NULL;		// Server to connect to
	WCHAR *pwszSitecode = NULL;		// Sitecode
	WCHAR wszSitecode[4];
	WCHAR *pwszFilename = NULL;		// filename to read from
	WCHAR *pwszGroupname = NULL;	// name for new distribution point group
	WCHAR *pwszUser = NULL;			// username to connect with (can be null)
	WCHAR *pwszPassword = NULL;		// password to connect with (can be null)
	
	WCHAR *pwszNewline;
	WCHAR pwszQuery[96];
	WCHAR pwszLine[255];
	WCHAR pwszCmp[255];

	bool bPasswordAllocated = false;
	bool bDisplayHelp = false;
	bool bMatchFound = false;
	bool bContextResult;

	int iInitResult = 0;
	int iSuccessCount = 0;
	int iFailCount = 0;
	long lUBound = 0;
	long saindexes[1];

	HRESULT hr;

	FILE *fListfile;

	ULONG uReturned = 0;
	VARIANT vVar;
	SAFEARRAY *psa;
	SAFEARRAYBOUND sabound[1];


	IWbemServices *pWbemServices = NULL;
	IWbemContext *pWbemContext = NULL;
	IWbemClassObject *pClass = NULL;
	IWbemClassObject *pInst = NULL;
	IEnumWbemClassObject *pWbemEnum = NULL;


	// Read in the command line
	bDisplayHelp = ParseCommandLine(argc, argv, &pwszServer, &pwszSitecode, &pwszFilename, &pwszGroupname, &pwszUser, &pwszPassword, &bPasswordAllocated);

	printf("\nMakeDPG -- Make Distribution Point Group\n"
		   "----------------------------------------\n" );
	
	if( !bDisplayHelp ) {
		printf(
			"Usage:\n"
			"  MakeDPG <filename> <groupname> <server> [-S:<sitecode>] [-U:<user> [<password> | *]]\n"
			"\n"
			"Where:\n"
			"  Filename  : Textfile name\n"
			"  Groupname : Name for new Distribution Point Group\n"
			"  Server    : SMS provider location\n"
			"  Sitecode  : SMS Sitecode\n"
			"  User      : UserID for connection\n"
			"  Password  : Password for the UserID\n"
		);
		return 0;
	}

	// open file specified on the commandline 
	fListfile = _wfopen(pwszFilename, L"r");

	if( !fListfile ) {
		printf("ERROR: Could not open file: %wS\n", pwszFilename);
		return 1;
	}
	
	printf("Connecting...");

	// Connect
	iInitResult = Init(pwszServer, pwszUser, pwszPassword, wszSitecode, pWbemServices);

	if( iInitResult ) {
		printf("error.\nERROR: Could not connect.\n");
		fclose(fListfile);
		return 1;
	}

	if( pwszSitecode == NULL )
		pwszSitecode = wszSitecode;

	printf("done.\n");

	// Prepare a context object to be used in all subsequent WbemServices calls.
	bContextResult = PrepareContext(L"SMS MakeDPG", pWbemContext);

	if( !bContextResult ) {
		printf("An error occurred preparing a context object.\n");
		pWbemServices->Release();
		CoUninitialize();
		fclose(fListfile);
		return 1;
	}

	// Prepare a query string to retrieve all Distribution Points
	swprintf(pwszQuery, L"SELECT * FROM %s WHERE %s=\"%s\" AND %s=\"SMS Distribution Point\"", CLASS_SMS_SCI_SysResUse, SMS_SiteControlItem::PROP_SiteCode, pwszSitecode, SMS_SCI_SysResUse::PROP_RoleName);

	// Execute the query
	hr = pWbemServices->ExecQuery(_bstr_t(L"WQL"), _bstr_t(pwszQuery), 0, pWbemContext, &pWbemEnum);
	if( FAILED(hr) ) {
		pWbemContext->Release();
		pWbemServices->Release();
		CoUninitialize();
		fclose(fListfile);
		return 1;
	}

	// Set security on the enum
	if( FAILED( SetInterfaceSecurity(pWbemEnum, NULL, pwszUser, pwszPassword, true) ) ) {
		pWbemEnum->Release();
		pWbemContext->Release();
		pWbemServices->Release();
		CoUninitialize();
		fclose(fListfile);
		return 1;
	}

	VariantInit(&vVar);

	
	// Create a new safearray to hold our results.
	sabound[0].lLbound = 0;
	sabound[0].cElements = 0;
	psa = SafeArrayCreate(VT_BSTR, 1, sabound);
	if( !psa ) {
		pWbemEnum->Release();
		pWbemContext->Release();
		pWbemServices->Release();
		CoUninitialize();
		fclose(fListfile);
		return 1;
	}

	while( !feof(fListfile) ) {
		if( fgetws(pwszLine, 255, fListfile) ) {
			
			// terminate string at newline character, if necessary
			if( (pwszNewline = wcschr(pwszLine, L'\n')) ) *pwszNewline = L'\0';

			bMatchFound = false;
			
			while( 1 ) {
				hr = pWbemEnum->Next(WBEM_INFINITE, 1, &pInst, &uReturned);
				
				if( uReturned == 0 ) break;

				// Retrieve NetworkOSPath property from instance in the Enum
				hr = pInst->Get(_bstr_t(SMS_SCI_SysResUse::PROP_NetworkOSPath), 0, &vVar, 0, 0);
				if( FAILED(hr) ) {
					SafeArrayDestroy(psa);
					pInst->Release();
					pWbemEnum->Release();
					pWbemContext->Release();
					pWbemServices->Release();
					CoUninitialize();
					fclose(fListfile);
					return 1;
				}

				wcscpy(pwszCmp, L"\\\\");

				// If the path from the file matches, add it to the safearray
				if( !wcsicmp(wcscat(pwszCmp, pwszLine), V_BSTR(&vVar)) ) {					
					hr = SafeArrayGetUBound(psa, 1, &lUBound);
					if( FAILED(hr) ) {
						SafeArrayDestroy(psa);
						VariantClear(&vVar);
						pInst->Release();
						pWbemEnum->Release();
						pWbemContext->Release();
						pWbemServices->Release();
						CoUninitialize();
						fclose(fListfile);
						return 1;
					}
					sabound[0].lLbound = 0;
					sabound[0].cElements = lUBound + 2;
					saindexes[0] = lUBound + 1;
					SafeArrayRedim(psa, sabound);
					SafeArrayPutElement(psa, saindexes, SysAllocString(V_BSTR(&vVar)));
					bMatchFound = true;
					iSuccessCount++;
					VariantClear(&vVar);
					pInst->Release();
					break;
				}
				VariantClear(&vVar);
				pInst->Release();
			}
			if( !bMatchFound ) {
				printf("Warning: Entry \"%wS\" is not a registered distribution point\n", pwszLine);
				iFailCount++;
			}
			pWbemEnum->Reset();
		}
	}
	
	pWbemEnum->Release();
	fclose(fListfile);

	// Retrieve SMS_DistributionPointGroup class
	hr = pWbemServices->GetObject(_bstr_t(CLASS_SMS_DistributionPointGroup), 0, pWbemContext, &pClass, NULL);
	if( FAILED(hr) ) {
		SafeArrayDestroy(psa);
		pWbemContext->Release();
		pWbemServices->Release();
		CoUninitialize();
		return 1;
	}
	
	// Spawn an instance of SMS_DistributionPointGroup
	hr = pClass->SpawnInstance(0, &(pInst = NULL));
	pClass->Release();
	if( FAILED(hr) ) {
		SafeArrayDestroy(psa);
		pWbemContext->Release();
		pWbemServices->Release();
		CoUninitialize();
		return 1;
	}

	V_VT(&vVar) = VT_BSTR;
	V_BSTR(&vVar) = SysAllocString(pwszGroupname);
	
	// Set the groupname property
	hr = pInst->Put(_bstr_t(SMS_DistributionPointGroup::PROP_sGroupName), 0, &vVar, 0);
	VariantClear(&vVar);
	if( FAILED(hr) ) {		
		SafeArrayDestroy(psa);
		pInst->Release();
		pWbemContext->Release();
		pWbemServices->Release();
		CoUninitialize();
		return 1;
	}

	V_VT(&vVar) = VT_BSTR | VT_ARRAY;
	V_ARRAY(&vVar) = psa;

	// Set the arrNALPath property property
	hr = pInst->Put(_bstr_t(SMS_DistributionPointGroup::PROP_arrNALPath), 0, &vVar, 0);
	VariantClear(&vVar);
	if( FAILED(hr) ) {		
		pInst->Release();
		pWbemContext->Release();
		pWbemServices->Release();
		CoUninitialize();
		return 1;
	}

	// Commit the new instance
	hr = pWbemServices->PutInstance(pInst, WBEM_FLAG_CREATE_ONLY, pWbemContext, NULL);
	pInst->Release();
	
	// Clean up.
	pWbemContext->Release();
	pWbemServices->Release();
	CoUninitialize();

	if( hr == WBEM_E_ALREADY_EXISTS ) {
		printf("ERROR: A DistributionPointGroup of that name already exists.\n");
	}
	else if( FAILED(hr) ) {
		printf("ERROR: PutInstance failed. (0x%x) \n", hr);
	}

	printf("\n%d of %d entries successfully processed.\n", iSuccessCount, iSuccessCount + iFailCount);

	return 0;
}