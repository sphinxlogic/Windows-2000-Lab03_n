// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// SWDist - Version 1.0
//
// SWDist demonstrates:
// IWbemLocator->ConnectServer
// IWbemClassObject->Put
// IWbemClassObject->SpawnInstance
// IWbemServices->PutInstance
// IWbemServices->GetObject
// IWbemCallResult->GetResultString
// After parsing the command line and connecting, SWDist calls
// IWbemServices->GetObject to get a SMS_Package class object.
// This class object is used to call SpawnInstance to return an
// instance object.  The Name property is stored with
// IWbemClassObject->Put and the instance is then stored with
// IWbemServices->PutInstance.  PutInstance returns an IWbemCallResult
// object, which is then used to call GetResultString.  This 
// returns the object path of the newly created package.
// This procedure is re-used to create instances of SMS_Program
// and SMS_Advertisement that correlate with the Package
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
WCHAR *gpwszUser = NULL;			// username to connect with
WCHAR *gpwszPassword = NULL;		// password for user
WCHAR *gpwszPackageID = NULL;		// package ID for the program & advert

bool gbPassAlloced = false;			// was password dynamically allocated?

IWbemServices *gpWbemServices = NULL;	// Global wbem services pointer

#define PACKAGE_NAME	L"SWDist_Package"
#define PROGRAM_NAME	L"SWDist_Program"
#define ADVERT_NAME		L"SWDist_Advert"
#define COLLECTION_ID	L"SMS00001"
#define PROGRAM_CMDLINE	L"RunMe.bat"

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
bool ParseCommandLine(int argc, WCHAR *argv[]) 
{

	int iArg;	// argument
	int iLoop;  // index
	bool bPassword = false;

	char password[255];

	for( iLoop = iArg = 1; iLoop < argc; iLoop++ ) 
	{
		if( (*argv[iLoop] != L'-') && (*argv[iLoop] != L'/') ) 
		{
			switch( iArg++ ) 
			{
			case 1:
				// Server
				gpwszServer = argv[iLoop];
				bPassword = false;
				break;
			default:
				if( bPassword ) 
				{
					gpwszPassword = argv[iLoop];
					bPassword = false;
					iArg--;
				} 
				else return false;
			}
		}
		else 
		{
			if( !wcsnicmp(argv[iLoop] + 1, L"U:", 2) ) 
			{
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
// CreatePackage : Creates a new package.
//
// * no parameters, uses global variables *
// Returns: int 
//		0 Success
//		1 GetObject SMS_Package failed.	
//		2 SpawnInstance Failed.
//		3 PutInstance failed.
//		4 SetInterfaceSecurity failed.
//		5 GetResultString failed.
//		6 GetObject on the new package failed
//		7 Get PackageID failed
// **************************************************************************
int CreatePackage() {

	IWbemClassObject *pClass = NULL;
	IWbemClassObject *pInstance = NULL;
	IWbemCallResult *pCallResult = NULL;
	IWbemClassObject *pPackageInstance = NULL;

	VARIANT vPackageName;
	VARIANT vPackageID;
	BSTR bstrObjPath = NULL;
	
	HRESULT hr;

	// Retrieve the SMS_Package CLASS and store it
	// in the pClass interface pointer.
	hr = gpWbemServices->GetObject(_bstr_t(L"SMS_Package"), 0, NULL, &pClass, NULL);
	if( FAILED(hr) ) {
		return 1;
	}

	// use IWbemClassObject::SpawnInstance to create
	// a new instance of SMS_Package from pClass and store
	// the instance in the pInstance pointer.
	hr = pClass->SpawnInstance(0, &pInstance);
	pClass->Release();
	if( FAILED(hr) ) {
		return 2;
	}

	// Prepare a variant to store the package name
	// property into our instance.
	VariantInit(&vPackageName);
	V_VT(&vPackageName) = VT_BSTR;
	V_BSTR(&vPackageName) = SysAllocString(PACKAGE_NAME);
	
	// Store the package name in the 'Name' property of the instance
	pInstance->Put(_bstr_t(L"Name"), 0, &vPackageName, NULL);
	VariantClear(&vPackageName);

	// Put the instance of the SMS_Package class we generated in the namespace. Include
	// the optional call result parameter in the call, so we can capture the object
	// path that was created for the instance.
	hr = gpWbemServices->PutInstance(pInstance, WBEM_FLAG_CREATE_ONLY, NULL, &pCallResult);
	pInstance->Release();
	if( FAILED(hr) ) {
		return 3;
	}

	// pCallResult didn't come from the WbemLocator, so we need to set security on it.
	// This call sets the authentication and impersonation levels to 
	// use with the pCallResult interface pointer.
	if( FAILED( SetInterfaceSecurity(pCallResult, NULL, gpwszUser, gpwszPassword, true) ) ) {
		pCallResult->Release();
		return 4;
	}

	// The PutInstance method returns the object path of the newly created instance.
	// Call IWbemCallResult::GetResultString to get the object path.
	hr = pCallResult->GetResultString(0, &bstrObjPath);
	pCallResult->Release();
	if( FAILED(hr) ) {
		return 5;
	}


	// Call IWbemServices::GetObject to retrieve the newly created package
	hr = gpWbemServices->GetObject(bstrObjPath, 0, NULL, &pPackageInstance, NULL);
	if( FAILED(hr) ) {
		return 6;
	}

	// Extract the PackageID variant from pInstance using
	// IWbemClassObject::Get and store it in vPackageID
	hr = pPackageInstance->Get(_bstr_t(L"PackageID"), 0, &vPackageID, NULL, NULL);
	pPackageInstance->Release();
	if( FAILED(hr) ) {
		return 7;
	}

	// Copy the contents of the variant to our PackageID global
	gpwszPackageID = SysAllocString(V_BSTR(&vPackageID));

	// Release the PackageID variant
	VariantClear(&vPackageID);

	// Print the path to the newly created instance of SMS_Package
	printf("New Package Created. ObjectPath = %wS\n", bstrObjPath);

	SysFreeString(bstrObjPath);

	return 0;

}

// **************************************************************************
// CreateProgram : Creates a new program that is attached to the package.
//
// * no parameters, uses global variables *
// Returns: int 
//		0 Success
//		1 GetObject SMS_Program failed.	
//		2 SpawnInstance Failed.
//		3 PutInstance failed.
//		4 SetInterfaceSecurity failed.
//		5 GetResultString failed.
// **************************************************************************
int CreateProgram() {

	IWbemClassObject *pClass = NULL;
	IWbemClassObject *pInstance = NULL;
	IWbemCallResult *pCallResult = NULL;

	VARIANT vProgramName;
	VARIANT vCommandLine;
	VARIANT vPackageID;
	BSTR bstrObjPath = NULL;
	
	HRESULT hr;

	// Retrieve SMS_Package CLASS
	hr = gpWbemServices->GetObject(_bstr_t(L"SMS_Program"), 0, NULL, &pClass, NULL);
	if( FAILED(hr) ) {
		return 1;
	}

	// use pClass to create a new instance
	hr = pClass->SpawnInstance(0, &pInstance);
	pClass->Release();
	if( FAILED(hr) ) {
		return 2;
	}

	// Prepare a variant to store the programname
	VariantInit(&vProgramName);
	V_VT(&vProgramName) = VT_BSTR;
	V_BSTR(&vProgramName) = SysAllocString(PROGRAM_NAME);
	
	// Store the program name in the ProgramName property of the instance
	hr = pInstance->Put(_bstr_t(L"ProgramName"), 0, &vProgramName, NULL);
	VariantClear(&vProgramName);

	// Prepare a variant to store the commandline
	VariantInit(&vCommandLine);
	V_VT(&vCommandLine) = VT_BSTR;
	V_BSTR(&vCommandLine) = SysAllocString(PROGRAM_CMDLINE);
	
	// Store the command line in the CommandLine property of the instance
	hr = pInstance->Put(_bstr_t(L"CommandLine"), 0, &vCommandLine, NULL);
	VariantClear(&vCommandLine);

	// Prepare a variant to store the packageid
	VariantInit(&vPackageID);
	V_VT(&vPackageID) = VT_BSTR;
	V_BSTR(&vPackageID) = SysAllocString(gpwszPackageID);
	
	// Store the package id in the PackageID property of the instance
	hr = pInstance->Put(_bstr_t(L"PackageID"), 0, &vPackageID, NULL);
	VariantClear(&vPackageID);

	// Store our instance, pCallResult will have our object path
	hr = gpWbemServices->PutInstance(pInstance, WBEM_FLAG_CREATE_ONLY, NULL, &pCallResult);
	pInstance->Release();
	if( FAILED(hr) ) {
		return 3;
	}

	// pCallResult didn't come from the WbemLocator, so we need to set security on it.
	if( FAILED( SetInterfaceSecurity(pCallResult, NULL, gpwszUser, gpwszPassword, true) ) ) {
		pCallResult->Release();
		return 4;
	}

	// Retrieve the ResultString (object path)
	hr = pCallResult->GetResultString(0, &bstrObjPath);
	pCallResult->Release();
	if( FAILED(hr) ) {
		return 5;
	}

	// print obj path
	printf("New Program Created. ObjectPath = %wS\n", bstrObjPath);

	SysFreeString(bstrObjPath);

	return 0;

}

// **************************************************************************
// CreateAdvertisement : Creates a new advertisement to advertise the package.
//
// * no parameters, uses global variables *
// Returns: int 
//		0 Success
//		1 GetObject SMS_Advertisement failed.	
//		2 SpawnInstance Failed.
//		3 PutInstance failed.
//		4 SetInterfaceSecurity failed.
//		5 GetResultString failed.
// **************************************************************************
int CreateAdvertisement() {

	IWbemClassObject *pClass = NULL;
	IWbemClassObject *pInstance = NULL;
	IWbemCallResult *pCallResult = NULL;

	VARIANT vProgramName;
	VARIANT vPackageID;
	VARIANT vAdvertisementName;
	VARIANT vCollectionID;
	BSTR bstrObjPath = NULL;
	
	HRESULT hr;

	// Retrieve SMS_Package CLASS
	hr = gpWbemServices->GetObject(_bstr_t(L"SMS_Advertisement"), 0, NULL, &pClass, NULL);
	if( FAILED(hr) ) {
		return 1;
	}

	// use pClass to create a new instance
	hr = pClass->SpawnInstance(0, &pInstance);
	pClass->Release();
	if( FAILED(hr) ) {
		return 2;
	}

	// Prepare a variant to store the programname
	VariantInit(&vProgramName);
	V_VT(&vProgramName) = VT_BSTR;
	V_BSTR(&vProgramName) = SysAllocString(PROGRAM_NAME);
	
	// Store the program name in the ProgramName property of the instance
	hr = pInstance->Put(_bstr_t(L"ProgramName"), 0, &vProgramName, NULL);
	VariantClear(&vProgramName);


	// Prepare a variant to store the packageid
	VariantInit(&vPackageID);
	V_VT(&vPackageID) = VT_BSTR;
	V_BSTR(&vPackageID) = SysAllocString(gpwszPackageID);
	
	// Store the package id in the PackageID property of the instance
	hr = pInstance->Put(_bstr_t(L"PackageID"), 0, &vPackageID, NULL);
	VariantClear(&vPackageID);


	// Prepare a variant to store the advertisementname
	VariantInit(&vAdvertisementName);
	V_VT(&vAdvertisementName) = VT_BSTR;
	V_BSTR(&vAdvertisementName) = SysAllocString(ADVERT_NAME);
	
	// Store the advertisement name in the AdvertisementName property of the instance
	hr = pInstance->Put(_bstr_t(L"AdvertisementName"), 0, &vAdvertisementName, NULL);
	VariantClear(&vAdvertisementName);


	// Prepare a variant to store the colletionid
	VariantInit(&vCollectionID);
	V_VT(&vCollectionID) = VT_BSTR;
	V_BSTR(&vCollectionID) = SysAllocString(COLLECTION_ID);
	
	// Store the collection id in the CollectionID property of the instance
	hr = pInstance->Put(_bstr_t(L"CollectionID"), 0, &vCollectionID, NULL);
	VariantClear(&vCollectionID);


	// Store our instance, pCallResult will have our object path
	hr = gpWbemServices->PutInstance(pInstance, WBEM_FLAG_CREATE_ONLY, NULL, &pCallResult);
	pInstance->Release();
	if( FAILED(hr) ) {
		return 3;
	}

	// pCallResult didn't come from the WbemLocator, so we need to set security on it.
	if( FAILED( SetInterfaceSecurity(pCallResult, NULL, gpwszUser, gpwszPassword, true) ) ) {
		pCallResult->Release();
		return 4;
	}

	// Retrieve the ResultString (object path)
	hr = pCallResult->GetResultString(0, &bstrObjPath);
	pCallResult->Release();
	if( FAILED(hr) ) {
		return 5;
	}

	// print obj path
	printf("New Advertisement Created. ObjectPath = %wS\n", bstrObjPath);

	SysFreeString(bstrObjPath);

	return 0;

}

// **************************************************************************
// wmain : Using wmain for the WCHAR *argv[]
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
			printf("error.\nERROR: Could not retrieve the namespace path.\n");
			if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
			return;
		case 4:
			printf("error.\nERROR: Could not connect to the provider location.\n");
			if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
			return;
		}

		// Call CreatePackage
		switch( CreatePackage() ) {
		case 1:
			printf("ERROR: GetObject SMS_Package failed.\n");
			break;
		case 2:
			printf("ERROR: SpawnInstance failed.\n");
			break;
		case 3:
			printf("ERROR: PutInstance failed.\n");
			break;
		case 4:
			printf("ERROR: SetInterfaceSecurity failed.\n");
			printf("NOTE : Specifing a userid in the form DOMAIN\\USER may help.\n");
			break;
		case 5:
			printf("ERROR: Couldn't retrieve object path.\n");
			break;
		case 6:
			printf("ERROR: GetObject on the new Package failed.\n");
			break;
		case 7:
			printf("ERROR: Couldn't Get the PackageID Property.\n");
			break;
		}

		// Call CreateProgram
		switch( CreateProgram() ) {
		case 1:
			printf("ERROR: GetObject SMS_Program failed.\n");
			break;
		case 2:
			printf("ERROR: SpawnInstance failed.\n");
			break;
		case 3:
			printf("ERROR: PutInstance failed.\n");
			break;
		case 4:
			printf("ERROR: SetInterfaceSecurity failed.\n");
			printf("NOTE : Specifing a userid in the form DOMAIN\\USER may help.\n");
			break;
		case 5:
			printf("ERROR: Couldn't retrieve object path.\n");
			break;

		}

		// Call CreateAdvertisement
		switch( CreateAdvertisement() ) {
		case 1:
			printf("ERROR: GetObject SMS_Advertisement failed.\n");
			break;
		case 2:
			printf("ERROR: SpawnInstance failed.\n");
			break;
		case 3:
			printf("ERROR: PutInstance failed.\n");
			break;
		case 4:
			printf("ERROR: SetInterfaceSecurity failed.\n");
			printf("NOTE : Specifing a userid in the form DOMAIN\\USER may help.\n");
			break;
		case 5:
			printf("ERROR: Couldn't retrieve object path.\n");
			break;
		
		}

		if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
		SysFreeString(gpwszPackageID);
		gpWbemServices->Release();
		CoUninitialize();
	}
	else {
		printf(
			"\nSWDist -- Creates a new package, program, and advertisement\n"
			"------------------------------------------------------------\n\n"
			"Usage:  swdist <server> [-U:<user> [<password> | *]]\n"
			"Where:\n"
			"   server      :  SMS Server\n"
			"   user        :  Userid for connection\n"
			"   password    :  Password for Userid\n"
		);
	}
}
