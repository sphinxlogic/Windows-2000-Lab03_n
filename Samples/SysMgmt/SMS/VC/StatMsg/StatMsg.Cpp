// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// StatMsg - Version 1.0
//
// StatMsg demonstrates:
// IWbemLocator->ConnectServer
// IWbemContext->SetValue
// IWbemClassObject->Get
// IWbemClassObject->Put
// IWbemClassObject->SpawnInstance
// IWbemServices->GetObject
// IWbemServices->ExecMethod
// After parsing the command line and connecting, StatMsg calls
// CoCreateInstance to create an instance of the IWbemContext class.
// IWbemContext->SetValue is then called to add the application name 
// and the machine name to the context object. Next, StatMsg calls
// IWbemServices->GetObject to get an SMS_StatusMessage class object.
// StatMsg next calls IWbemClassObject->GetMethod to get a class object
// representing the RaiseRawStatusMsg method's in-parameters
// Then IWbemClassObject->SpawnInstance is called to create an instance
// of the method input parameters.  Next, StatMsg calls
// IWbemClassObject->Put several times to set all the properties
// of the in-parameters instance.  Finally, StatMsg calls
// IWbemServices->ExecMethod on SMS_StatusMessage::RaiseRawStatusMsg
// passing in our in-parameters instance, and our context object
// ********************************************************

#define _WIN32_DCOM

#include <stdio.h>
#include <conio.h>
#include <comdef.h>
#include <wbemidl.h>
#include "wbemsec.h"

#define MAX_PASSWORD_LENGTH 255

#define _USE_AUTOSYMBOLS
#define _INIT_AUTOSYMBOLS
#include "smsprov.h"

using namespace SMSSDK;


// ********************************************************
// Global Variables:
// These will store command line parameters
// ********************************************************

WCHAR *gpwszServer = NULL;			// server to connect to
WCHAR *gpwszUser = NULL;			// username to connect with
WCHAR *gpwszPassword = NULL;		// password for user

WCHAR *gpwszMethod = NULL;			// The StatusMessage Method Name
WCHAR *gpwszMessageText = NULL;		// The Text of the Status Message
WCHAR *gpwszAppName;				// The Application raising the status message
WCHAR *gpwszMachName;				// The Machine raising the status message
unsigned long gulMessageType;		// Message Type (256=MileStone, 512=Detail, 768=Audit)
unsigned long gulProcessID;			// The ProcessID the process that is raising the status message
unsigned long gulThreadID;			// The ThreadID of the thread that is raising the status message

bool gbPassAlloced = false;

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
	InitializeSecurity(TRUE);

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
	
	int iArg;
	int iLoop;
	bool bPassword = false;

	char password[255];

	// Preset the numeric global variables
	gulMessageType = 0;
	gulProcessID = 0;
	gulThreadID = 0;

	for( iLoop = iArg = 1; iLoop < argc; iLoop++ ) 
	{
		if( (*argv[iLoop] != L'-') && (*argv[iLoop] != L'/') ) 
		{
			switch( iArg++ ) 
			{
			case 1:
				gpwszServer = argv[iLoop];		// Server
				bPassword = false;
				break;
			case 2:
				gulMessageType = _wtol(argv[iLoop]);	// Message Type
				bPassword = false;
				break;
			case 3:
				gpwszMessageText = argv[iLoop];
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
		else 
		{
			if( !wcsnicmp(argv[iLoop] + 1, L"U:", 2) ) 
			{
				gpwszUser = argv[iLoop] + 3;			// UserName
				bPassword = true;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"A:", 2) )
			{
				gpwszAppName = argv[iLoop] + 3;			// Application Name
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"M:", 2) )
			{
				gpwszMachName = argv[iLoop] + 3;		// Machine Name
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"PID:", 4) )
			{
				gulProcessID = _wtol(argv[iLoop] + 5);	// Process ID
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"TID:", 4) )
			{
				gulThreadID = _wtol(argv[iLoop] + 5);	// Thread ID
				bPassword = false;
			}
			else if ( !_wcsicmp(argv[iLoop], L"-I") && gpwszMethod == NULL )
			{
				gpwszMethod = L"RaiseInformationalStatusMsg";
				bPassword = false;
			}
			else if ( !_wcsicmp(argv[iLoop], L"-E") && gpwszMethod == NULL )
			{
				gpwszMethod = L"RaiseErrorStatusMsg";
				bPassword = false;
			}
			else if ( !_wcsicmp(argv[iLoop], L"-W") && gpwszMethod == NULL )
			{
				gpwszMethod = L"RaiseWarningStatusMsg";
				bPassword = false;
			}
		}
	}

	if( iArg != 4 ) return false;

	// Set any non-user-defined variables to their defaults
	if( gpwszMethod == NULL )
		return false;
	if( gpwszAppName == NULL )
		gpwszAppName = L"Unknown Application";
	if( gpwszMachName == NULL )
		gpwszMachName = L"Unknown Machine";

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


// **********************************************************************************
// RaiseStatusMessage : Raises a status message based on the Method in gpwszMethod.
//
// * no parameters *
// Returns: int 
//		0 Success
//		1 CoCreateInstance failed.	
//		2 GetObject SMS_StatusMessage Failed.
//		3 GetMethod failed.
//		4 SpawnInstance failed.
//		5 Setting a property failed.
//		6 ExecMethod failed.
// **********************************************************************************
int RaiseStatusMessage()
{
	// First, a context object that stores the AppName and the MachName is created
	IWbemContext  *pWbemContext = NULL;	// Context object

	if( FAILED(CoCreateInstance(CLSID_WbemContext, NULL, CLSCTX_INPROC_SERVER, IID_IWbemContext, (void**) &pWbemContext)))
		return 1;

	VARIANT vAppName;
	VariantInit(&vAppName);
	V_VT(&vAppName) = VT_BSTR;
	V_BSTR(&vAppName) = SysAllocString(gpwszAppName);

	VARIANT vMachName;
	VariantInit(&vMachName);
	V_VT(&vMachName) = VT_BSTR;
	V_BSTR(&vMachName) = SysAllocString(gpwszMachName);
	
	// Store the AppName and MachName in the context object
	pWbemContext->SetValue(_bstr_t(CONTEXTVALUE_ApplicationName), 0, &vAppName);
	pWbemContext->SetValue(_bstr_t(CONTEXTVALUE_MachineName), 0, &vMachName);


	// Second, we prepare our input parameters object
	IWbemClassObject *pStatusClass = NULL;
	IWbemClassObject *pOutInst = NULL;
	IWbemClassObject *pInParamClass = NULL;
	IWbemClassObject *pInParamInst = NULL;  
    
	// Get the class object for the method definition
	if( FAILED(gpWbemServices->GetObject(_bstr_t(CLASS_SMS_StatusMessage), 0, NULL, &pStatusClass, NULL)))
	{
		pWbemContext->Release();
		return 2;
	}

    // Get the input parameter class object
    if( FAILED(pStatusClass->GetMethod(gpwszMethod, 0, &pInParamClass, NULL)))
	{
		pWbemContext->Release();
		pStatusClass->Release();
		return 3;
	}
	pStatusClass->Release();
	pStatusClass = NULL;

	// Create an instance of the parameter class object
	if( FAILED(pInParamClass->SpawnInstance(0, &pInParamInst)))
	{
		pWbemContext->Release();
		pInParamClass->Release();
		return 4;
	}
	pInParamClass->Release();
	pInParamClass = NULL;

	// Set the properties
	VARIANT vMsgType;			// Message Type
	VariantInit(&vMsgType);
	V_VT(&vMsgType) = VT_I4;
	V_I4(&vMsgType) = gulMessageType;
	if( FAILED( pInParamInst->Put(L"MessageType", 0, &vMsgType, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vMsgType);

	VARIANT vProcessID;			// Process ID
	VariantInit(&vProcessID);
	V_VT(&vProcessID) = VT_I4;
	V_I4(&vProcessID) = gulProcessID;
	if( FAILED( pInParamInst->Put(L"ProcessID", 0, &vProcessID, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vProcessID);

	VARIANT vThreadID;			// Thread ID
	VariantInit(&vThreadID);
	V_VT(&vThreadID) = VT_I4;
	V_I4(&vThreadID) = gulThreadID;
	if( FAILED( pInParamInst->Put(L"ThreadID", 0, &vThreadID, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vThreadID);

	VARIANT vMessageText;		// Message Text
	VariantInit(&vMessageText);
	V_VT(&vMessageText) = VT_BSTR;
	V_BSTR(&vMessageText) = gpwszMessageText;
	if( FAILED( pInParamInst->Put(L"MessageText", 0, &vMessageText, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vMessageText);

	// Now we call the method
	HRESULT hr;
	hr = gpWbemServices->ExecMethod(_bstr_t(CLASS_SMS_StatusMessage), _bstr_t(gpwszMethod),
									0, pWbemContext, pInParamInst, NULL, NULL);
	if(FAILED(hr))
	{ 
		printf("Error Number: %lx \n", hr);
		pWbemContext->Release();
		pInParamInst->Release();
		return 6;
	}

	// Cleanup
	pWbemContext->Release();
	pInParamInst->Release();


	return 0;
}


// **************************************************************************
// wmain : Using wmain for the WCHAR *argv[]
// **************************************************************************
extern "C" void wmain(int argc, WCHAR *argv[]) {
	
	// Parse command line, print help if false is returned
	if( ParseCommandLine(argc, argv) ) 
	{	
		printf("Connecting...");
		
		// Connect
		switch( Init(gpwszServer, gpwszUser, gpwszPassword, gpWbemServices) ) 
		{
		case 0:
			printf("done.\n");
			break;
		case 1:
			printf("error.\nERROR: CoCreateInstance WbemLocator Failed.\n");
			if( gbPassAlloced) CoTaskMemFree(gpwszPassword);
			return;
		case 2:
			printf("error.\nERROR: Could not connect to the specified server.\n");
			if( gbPassAlloced) CoTaskMemFree(gpwszPassword);
			return;
		case 3:
			printf("error.\nERROR: Specified sitecode was invalid.\n");
			if( gbPassAlloced) CoTaskMemFree(gpwszPassword);
			return;
		case 4:
			printf("error.\nERROR: Could not retrieve the namespace path.\n");
			if( gbPassAlloced) CoTaskMemFree(gpwszPassword);
			return;
		case 5:
			printf("error.\nERROR: Could not connect to the provider location.\n");
			if( gbPassAlloced) CoTaskMemFree(gpwszPassword);
			return;
		}

		// Call RaiseStatusMessage
		switch( RaiseStatusMessage() ) 
		{
		case 1:
			printf("ERROR: CoCreateInstance failed.\n");
			break;
		case 2:
			printf("ERROR: GetObject (SMS_StatusMessage) failed.\n");
			break;
		case 3:
			printf("ERROR: GetMethod failed.\n");
			break;
		case 4:
			printf("ERROR: SpawnInstance failed.\n");
			break;
		case 5:
			printf("ERROR: Couldn't set one of the In-Param Properties.\n");
			break;
		case 6:
			printf("ERROR: ExecMethod failed.\n");
			break;
		}

		if( gbPassAlloced) CoTaskMemFree(gpwszPassword);
		gpWbemServices->Release();
		CoUninitialize();
	}
	else 
	{
		printf(
			"\nSTATMSG -- Raises Status Messages\n"
			"-----------------------------------------------------------------\n\n"
			"Usage:  StatMsg <server> <message type> <message text>\n"
			"                [-I, -E, or -W] [options]\n"
			"                [-U:<user> [<password> | *]]\n\n"
			"Where:\n"
			"   server        :  SMS Server\n"
			"   messagetype   :  The message type (256, 512, or 768)\n"
			"   messagetext   :  The text to put in the status message\n"
			"   -I, -E, or -W :  Informational, Error, or Warning Msg\n\n"
			"Options: [-VAR:setting]\n"
			"   -A:<appname>     :  The Application raising the message\n"
            "   -M:<machname>    :  The Machine raising the message\n"
			"   -PID:<processid> :  The ID of the process raising the message\n"
			"   -TID:<threadid>  :  The ID of the thread raising the message\n"
			"   -U:<username>    :  Userid for connection\n"
			"      <password>    :  Password for Userid\n"
		);
	}
}
