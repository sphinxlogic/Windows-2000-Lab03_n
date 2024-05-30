// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// Packlist - Version 1.0
//
// Packlist Demonstrates:
// IWbemLocator->ConnectServer
// IWbemServices->CreateInstanceEnum
// IWbemServices->ExecQuery
// IWbemClassObject->Get
// After parsing the command line and connecting, packlist enumerates instances of SMS_Package.
// For each instance, the PackageID and Name properties are extracted and displayed.  The PackageID
// is passed to EnumPrograms. EnumPrograms then constructs a query in the form 
// SELECT * FROM SMS_Program where PackageID="<packageid>".
// For each instance returned by the query, the ProgramName is displayed.
// ********************************************************


#define _WIN32_DCOM

#include <stdio.h>
#include <conio.h>
#include <comdef.h>
#include <wbemidl.h>
#include "wbemsec.h"

#define MAX_PASSWORD_LENGTH 255


// ********************************************************
// Global Variables:
// These will store command line parameters
// ********************************************************

WCHAR *gpwszServer = NULL;			// server to connect to
WCHAR *gpwszSitecode = NULL;		// sitecode on the server
WCHAR *gpwszUser = NULL;			// username to connect with
WCHAR *gpwszPassword = NULL;		// password for user

bool gbPassAlloced = false;			// was password dynamically allocated?

IWbemServices *gpWbemServices = NULL;	// Global wbem services pointer


// **************************************************************************
// Init : Connect to specified Server
//
// [in] WCHAR *Server
// [in] WCHAR *User     (can be null)
// [in] WCHAR *Password (can be null)
// [out] IWbemServices* &rpWbemServices  (reference to pointer)
// Returns: int
//		0 Success
//		1 CoCreateInstance WbemLocator Failed
//		2 Specified Server was not found
//		3 Error retrieving NamespacePath
//		4 Could not connect to NamespacePath
// **************************************************************************
int Init(WCHAR *Server, WCHAR *User, WCHAR *Password, IWbemServices *&rpWbemServices) {
	
	HRESULT hr;
	VARIANT vNamespace;
	_bstr_t bstrNamespace;
	_bstr_t bstrLocationPath;
	ULONG uReturned;
	IWbemLocator *pWbemLocator = NULL;
	IWbemClassObject *pWbemClass = NULL;
	IEnumWbemClassObject *pWbemEnum = NULL;

	// Release and Null pWbemServices
	if( rpWbemServices ) rpWbemServices->Release();
	rpWbemServices = NULL;

	// Store \\server\root\sms
	bstrNamespace = L"\\\\" + _bstr_t(Server) + L"\\root\\sms";

	// Initialize COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// Initialize COM Security
	InitializeSecurity(FALSE);

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
	bstrLocationPath = L"SELECT NamespacePath FROM SMS_ProviderLocation WHERE ProviderForLocalSite = True";
		
	// Execute the query
	hr = rpWbemServices->ExecQuery(_bstr_t(L"WQL"), bstrLocationPath, WBEM_FLAG_FORWARD_ONLY, NULL, &pWbemEnum);
	if( FAILED(hr) )
	{
		rpWbemServices->Release();
		pWbemLocator->Release();
		CoUninitialize();
		return 3;
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
		return 3;
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
		return 3;
	}

	// Initialize the vVar VARIANT structure.
	VariantInit( &vNamespace );
	
	// The actual SMS namespace path for the site is contained in the NamespacePath
	// property. Use the WMI Get method to get the value from the NamespacePath
	// property and assign it to the variant vNamespace.
	hr = pWbemClass->Get(_bstr_t(L"NamespacePath"), 0, &vNamespace, NULL, NULL);
	pWbemClass->Release();
	rpWbemServices->Release();
	rpWbemServices = NULL;		// MUST be set to NULL
	if( FAILED(hr) )
	{
		VariantClear(&vNamespace);
		pWbemLocator->Release();
		CoUninitialize();
		return 3;
	}
	
	// Finally, connect to the true provider location
	// at \\<Server>\root\sms\site_<SiteCode>
	hr = pWbemLocator->ConnectServer(V_BSTR(&vNamespace), _bstr_t(User), _bstr_t(Password), NULL, 0, NULL, NULL, &rpWbemServices);
	VariantClear(&vNamespace);
	pWbemLocator->Release();
	if( FAILED(hr) ) {
		CoUninitialize();
		return 4;
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

// ********************************************************
// AnsiToUnicode : Convert an ansi string to a unicode string via MultiByteToWideChar
//
// [in] char *psz
// [out] WCHAR **ppwszOut
//
// Returns: HRESULT
// ********************************************************
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
bool ParseCommandLine(int argc, WCHAR *argv[]) {

	int iArg;	// argument
	int iLoop;  // index
	bool bPassword = false;

	char password[255];

	for( iLoop = iArg = 1; iLoop < argc; iLoop++ ) {
		if( (*argv[iLoop] != L'-') && (*argv[iLoop] != L'/') ) {
			switch( iArg++ ) {
			case 1:
				// Server
				gpwszServer = argv[iLoop];
				bPassword = false;
				break;
			default:
				if( bPassword ) {
					gpwszPassword = argv[iLoop];
					bPassword = false;
					iArg--;
				} 
				else return false;
			}
		}
		else {
			if( !wcsnicmp(argv[iLoop] + 1, L"U:", 2) ) {
				gpwszUser = argv[iLoop] + 3;				// User name
				bPassword = true;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"?", 1) ) return false;	// help
		}
	}

	// Check for correct number of real arguments
	if( iArg != 2 ) return false;
	
	// Prompt user for password?
	if( !gpwszPassword || wcscmp(gpwszPassword, L"*") ) return true;

	// Display prompt
	printf("Enter Password for %S:", gpwszUser);

	// If user did not abort password input...
	if( !PromptUserForPassword(password) ) return false;

	AnsiToUnicode(password, &gpwszPassword);
	gbPassAlloced = true;

	return true;
}

// **************************************************************************
// EnumPrograms : Enumerate instances of SMS_Program
//
// [in] BSTR bstrPackageID
// Returns: int
//		0 success
//		3 ExecQuery failed.
//		4 SetInterfaceSecurity failed
// **************************************************************************
int EnumPrograms(BSTR bstrPackageID) {

	// WMI Enum and Class Objects.
	IEnumWbemClassObject *pEnum = NULL;
	IWbemClassObject *pInstance = NULL;
	
	VARIANT vProgramName;

	// ULONG needed for pEnum->Next
	ULONG uReturned;
	
	// Buffer for our query.
	WCHAR pwszQuery[255];

	// Construct a query to retrieve all the instances of SMS_Program
	// that have the PackageID specified in bstrPackageID
	swprintf(pwszQuery, L"SELECT * FROM SMS_Program WHERE PackageID = \"%s\"", bstrPackageID);

	// Execute the Query
	if( FAILED( gpWbemServices->ExecQuery(_bstr_t(L"WQL"), _bstr_t(pwszQuery), 0, NULL, &pEnum) ) ) {
		return 3;
	}

	// Use the WMI helper function to set the security levels for the out-of-process
	// interface pointer. The helper function calls the CoSetProxyBlanket function to
	// set the authentication and impersonation levels.
	if( FAILED( SetInterfaceSecurity(pEnum, NULL, gpwszUser, gpwszPassword, true) ) ) {
		pEnum->Release();
		return 4;
	}

	// Loop through the instances contained in the pEnum object
	while( pEnum->Next(WBEM_INFINITE, 1, &pInstance, &uReturned) == S_OK ) {
		
		// Retrieve programname property
		pInstance->Get(_bstr_t(L"ProgramName"), 0, &vProgramName, NULL, NULL);

		// Printf programname
		printf(" +- ProgramName = %wS\n", V_BSTR(&vProgramName));
		
		VariantClear(&vProgramName);
		pInstance->Release();
		pInstance = NULL;
	}

	return 0;
}


// **************************************************************************
// EnumPackages : Enumerate instances of SMS_Package
//
// *no parameters*
// Returns: int
//		0 success
//		1 CreateInstanceEnum SMS_Package failed
//		2 SetInterfaceSecurity failed
//     >2 Return value from EnumProgram
// **************************************************************************
int EnumPackages() {
	
	// WMI Enum and Class Objects.
	IEnumWbemClassObject *pEnum = NULL;
	IWbemClassObject *pInstance = NULL;

	VARIANT vPackageID;
	VARIANT vPackageName;

	// ULONG needed for pEnum->Next
	ULONG uReturned;

	// Return value from EnumPrograms
	int iEPRet;

	// Enumerate all the instances of SMS_Package
	if( FAILED( gpWbemServices->CreateInstanceEnum(_bstr_t(L"SMS_Package"), 0, NULL, &pEnum) ) ) {
		return 1;
	}
	
	// Use the WMI helper function to set the security levels for the out-of-process
	// interface pointer. The helper function calls the CoSetProxyBlanket function to
	// set the authentication and impersonation levels.
	if( FAILED( SetInterfaceSecurity(pEnum, NULL, gpwszUser, gpwszPassword, true) ) ) {
		pEnum->Release();
		return 2;
	}
	
	VariantInit(&vPackageID);
	VariantInit(&vPackageName);

	// Loop through all the instances contained in pEnum
	while( pEnum->Next(WBEM_INFINITE, 1, &pInstance, &uReturned) == S_OK ) {
		
		// Retrieve the PackageID and Name properties
		pInstance->Get(_bstr_t(L"PackageID"), 0, &vPackageID, NULL, NULL);
		pInstance->Get(_bstr_t(L"Name"), 0, &vPackageName, NULL, NULL);

		printf("Package: %wS (PackageID = %wS)\n", V_BSTR(&vPackageName), V_BSTR(&vPackageID));
		
		// Call EnumPrograms
		if( (iEPRet = EnumPrograms(V_BSTR(&vPackageID))) > 2 ) return iEPRet;

		VariantClear(&vPackageID);
		VariantClear(&vPackageName);
		pInstance->Release();
		pInstance = NULL;
	}

	return 0;
}

// **************************************************************************
// wmain : Using wmain for the WCHAR argv.
// Returns: void
// **************************************************************************
extern "C" void wmain(int argc, WCHAR *argv[]) {
	
	// Parse command line, print help if false is returned
	if( ParseCommandLine(argc, argv) ) {
		
		printf("Connecting...");
		
		// Connect
		switch( Init(gpwszServer, gpwszUser, gpwszPassword, gpWbemServices) ) {
		case 0:
			printf("done.\n");
			break;
		case 1:
			printf("error.\nERROR: CoCreateInstance WbemLocator Failed.\n");
			if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
			return;
		case 2:
			printf("error.\nERROR: Could not connect to the specified server.\n");
			if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
			return;
		case 3:
			printf("error.\nERROR: Specified sitecode was invalid.\n");
			if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
			return;
		case 4:
			printf("error.\nERROR: Could not retrieve the namespace path.\n");
			if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
			return;
		case 5:
			printf("error.\nERROR: Could not connect to the provider location.\n");
			if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
			return;
		}

		// Call EnumPackages
		switch( EnumPackages() ) {
		case 1:
			printf("ERROR: CreateInstanceEnum(\"SMS_Package\") has failed. \n");
			break;
		case 2:
			printf("ERROR: SetInterfaceSecurity(within EnumPackages) has failed. \n");
			printf("Note : Specifying your userid as domain\\user may fix this.\n");
			break;
		case 3:
			printf("ERROR: ExecQuery failed.\n");
			break;
		case 4:
			printf("ERROR: SetInterfaceSecurity(within ExecQuery) as failed.");
			printf("Note : Specifying your userid as domain\\user may fix this.\n");
			break;
		}

		if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
		gpWbemServices->Release();
		CoUninitialize();
	}
	else {
		printf(
			"\nPACKLIST -- Print SMS Packages and their Programs\n"
			"---------------------------------------------------------------\n\n"
			"Usage:  packlist <server> [-U:<user> [<password> | *]]\n"
			"Where:\n"
			"   server   :  SMS Server\n"
			"   user     :  Userid for connection\n"
			"   password :  Password for Userid\n"
		);
	}
}
