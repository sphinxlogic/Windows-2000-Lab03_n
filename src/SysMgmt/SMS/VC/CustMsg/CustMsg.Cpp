// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// CustMsg - Version 1.0
//
// CustMsg demonstrates:
// IWbemLocator->ConnectServer
// IWbemContext->SetValue
// IWbemClassObject->Get
// IWbemClassObject->Put
// IWbemClassObject->SpawnInstance
// IWbemServices->GetObject
// IWbemServices->ExecMethod
// After parsing the command line and connecting, CustMsg calls
// CoCreateInstance to create an instance of the IWbemContext class.
// IWbemContext->SetValue is then called to add the application name 
// and the machine name to the context object. Next, CustMsg calls
// IWbemServices->GetObject to get an SMS_StatusMessage class object.
// CustMsg next calls IWbemClassObject->GetMethod to get a class object
// representing the RaiseRawStatusMsg method's in-parameters
// Then IWbemClassObject->SpawnInstance is called to create an instance
// of the method input parameters.  Next, CustMsg calls
// IWbemClassObject->Put several times to set all the properties
// of the in-parameters instance.  Finally, CustMsg calls
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

#define _USE_AUTOSYMBOLS  // must be defined before the include
#define _INIT_AUTOSYMBOLS // must be defined before the include in one and only one file
#include "smsprov.h"

using namespace SMSSDK;

// ********************************************************
// Global Variables:
// These will store command line parameters
// ********************************************************

WCHAR *gpwszServer = NULL;			// server to connect to
WCHAR *gpwszUser = NULL;			// username to connect with
WCHAR *gpwszPassword = NULL;		// password for user

BSTR bstraInsStrings[12] = {NULL, NULL, NULL,NULL, NULL, NULL,
							NULL, NULL, NULL,NULL, NULL, NULL};			
									// Status Message Insertion Strings 
int iNumInsStrings=0;				// The number of strings in the bstraInsStrings[] array
WCHAR *gpwszModuleName = NULL;		// Status Message DLL Module containing our message ID
WCHAR *gpwszAppName = NULL;			// The Application raising the status message
WCHAR *gpwszMachName = NULL;		// The Machine raising the status message
unsigned long ulMessageID=0;		// The Message ID
unsigned long ulMessageType=0;		// Message Type (256=MileStone, 512=Detail, 768=Audit)
unsigned long ulProcessID=0;		// The ProcessID the process that is raising the status message
unsigned long ulThreadID=0;			// The ThreadID of the thread that is raising the status message

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
				ulMessageID = _wtol(argv[iLoop]);	// Message ID
				bPassword = false;
				break;
			case 3:
				ulMessageType = _wtol(argv[iLoop]);	// Message Type
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
			else if ( !wcsnicmp(argv[iLoop] + 1, L"C:", 2) )
			{
				gpwszModuleName = argv[iLoop] + 3;		// Module Name
				bPassword = false;
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
				ulProcessID = _wtol(argv[iLoop] + 5);	// Process ID
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"TID:", 4) ) 
			{
				ulThreadID = _wtol(argv[iLoop] + 5);	// Thread ID
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"I:", 2) )
			{
				// This section parses out all the insertion strings
				// a common command line argument would be "-I:String1,String2,String3"
				int iInsLoop = 0;
				int iOffset = 0;
				bool bLoopFinished = false;
				argv[iLoop] += 3; // move past the "-I:"

				while( !bLoopFinished )
				{
					if( (*(argv[iLoop] + iOffset) == ',') && (iInsLoop < 12))
					{
						*(argv[iLoop] + iOffset) = 0;
						bstraInsStrings[iInsLoop] = SysAllocString(argv[iLoop]);

						argv[iLoop] += (iOffset + 1);
						iInsLoop++;
						iOffset = 0;
					}
					else if( (*(argv[iLoop] + iOffset) == 0) && (iInsLoop < 12))
					{
						bstraInsStrings[iInsLoop] = SysAllocString(argv[iLoop]);
						bLoopFinished = true;
					}
					else
						iOffset++;
				}
				iNumInsStrings = iInsLoop + 1;
				bPassword = false;
			}
		}
	}

	if( iArg != 4 ) return false;

	// Set any non-user-defined variables to their defaults
	if( gpwszModuleName == NULL )
		gpwszModuleName = L"SMS Provider";
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


// **************************************************************************
// RaiseStatusMessage : Raises a Status Message 
//
// * no parameters *
// Returns: int 
//		0 Success
//		1 CoCreateInstance failed.	
//		2 GetObject SMS_StatusMessage Failed.
//		3 GetMethod RaiseRawStatusMessage failed.
//		4 SpawnInstance failed.
//		5 Setting the Method Parameters failed.
//		6 ExecMethod failed.
// **************************************************************************
int RaiseStatusMessage()
{
	// First, a context object that stores the Application Name and the Machine Name is created
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

    // Get the input parameters class object
    if( FAILED(pStatusClass->GetMethod(_bstr_t(SMS_StatusMessage::METHOD_RaiseRawStatusMsg), 0, &pInParamClass, NULL)))
	{
		pWbemContext->Release();
		pStatusClass->Release();
		return 3;
	}

	// We no longer need the pStatusClass object, so we'll release it here
	pStatusClass->Release();
	pStatusClass = NULL;

	// Create an instance of the input parameters class object
	if( FAILED(pInParamClass->SpawnInstance(0, &pInParamInst)))
	{
		pWbemContext->Release();
		pInParamClass->Release();
		return 4;
	}

	pInParamClass->Release();
	pInParamClass = NULL;

	// Set the properties of the input parameter instance
	VARIANT vMsgID;				// Message ID
	VariantInit(&vMsgID);
	V_VT(&vMsgID) = VT_I4;
	V_I4(&vMsgID) = ulMessageID;
	if( FAILED( pInParamInst->Put(_bstr_t(SMS_StatusMessage::RaiseRawStatusMsg::In::PARAM_MessageID), 0, &vMsgID, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vMsgID);

	VARIANT vMsgType;			// Message Type
	VariantInit(&vMsgType);
	V_VT(&vMsgType) = VT_I4;
	V_I4(&vMsgType) = ulMessageType;
	if( FAILED( pInParamInst->Put(_bstr_t(SMS_StatusMessage::RaiseRawStatusMsg::In::PARAM_MessageType), 0, &vMsgType, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vMsgType);

	VARIANT vProcessID;			// Process ID
	VariantInit(&vProcessID);
	V_VT(&vProcessID) = VT_I4;
	V_I4(&vProcessID) = ulProcessID;
	if( FAILED( pInParamInst->Put(_bstr_t(SMS_StatusMessage::RaiseRawStatusMsg::In::PARAM_ProcessID), 0, &vProcessID, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vProcessID);

	VARIANT vThreadID;			// Thread ID
	VariantInit(&vThreadID);
	V_VT(&vThreadID) = VT_I4;
	V_I4(&vThreadID) = ulThreadID;
	if( FAILED( pInParamInst->Put(_bstr_t(SMS_StatusMessage::RaiseRawStatusMsg::In::PARAM_ThreadID), 0, &vThreadID, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vThreadID);

	VARIANT vModuleName;		// Module Name
	VariantInit(&vModuleName);
	V_VT(&vModuleName) = VT_BSTR;
	V_BSTR(&vModuleName) = gpwszModuleName;
	if( FAILED( pInParamInst->Put(_bstr_t(SMS_StatusMessage::RaiseRawStatusMsg::In::PARAM_ModuleName), 0, &vModuleName, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vModuleName);

	VARIANT vInsStrings;		// Insertion Strings
	VariantInit(&vInsStrings);
	V_VT(&vInsStrings) = VT_ARRAY | VT_BSTR;

	// Create a SafeArray to store the BSTR array
	SAFEARRAY FAR* pSafeArray;
	SAFEARRAYBOUND saBound[1];
	saBound[0].lLbound = 0;
	saBound[0].cElements = iNumInsStrings;
	pSafeArray = SafeArrayCreate(VT_BSTR, 1, saBound);
	if(pSafeArray == NULL)
	{
		pWbemContext->Release();
		pInParamInst->Release();
		printf("Error: Unable to create the safe array for the insertion strings\n");
		return 5;
	}
	// Populate the SafeArray with the BSTR's
	for(long iCurString=0; iCurString < iNumInsStrings; iCurString++)
	{
		if( FAILED(SafeArrayPutElement(pSafeArray, &iCurString, bstraInsStrings[iCurString])))
		{
			pWbemContext->Release();
			pInParamInst->Release();
			printf("Error: Unable to set one of the insertion string safe array elements\n");
			return 5;
		}
	}
	// Put the Insertion Strings variant into the input parameters instance
	V_ARRAY(&vInsStrings) = pSafeArray;
	if( FAILED( pInParamInst->Put(_bstr_t(SMS_StatusMessage::RaiseRawStatusMsg::In::PARAM_InsStrings), 0, &vInsStrings, 0)))
	{
		pWbemContext->Release();
		pInParamInst->Release();
		return 5;
	}
	VariantClear(&vInsStrings);


	// Call ExecMethod to execute SMS_StatusMessage::RaiseRawStatusMsg
	HRESULT hr;
	hr = gpWbemServices->ExecMethod(_bstr_t(CLASS_SMS_StatusMessage), _bstr_t(SMS_StatusMessage::METHOD_RaiseRawStatusMsg),
									0, pWbemContext, pInParamInst, NULL, NULL);
	if(FAILED(hr))
	{ 
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
			printf("error.\nERROR: Could not retrieve the namespace path.\n");
			if( gbPassAlloced) CoTaskMemFree(gpwszPassword);
			return;
		case 4:
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
			printf("ERROR: Couldn't set one of the Method Parameters.\n");
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
			"\nCUSTMSG -- Raises Status Messages\n"
			"----------------------------------------------------------------\n\n"
			"Usage:  CustMsg <server> <message id> <message type>\n"
			"                [options] [-U:<user> [<password> | *]]\n\n"
			"Where:\n"
			"   server      :  SMS Server\n"
			"   messageid   :  The ID for the status message\n"
			"   messagetype :  The Message Type (256, 512, or 768)\n\n"
			"Options: [-VAR:setting]\n"
			"   -C:<modulename>  :  Message DLL Module Name (SMS Provider)\n"
			"   -A:<appname>     :  The Application raising the message\n"
            "   -M:<machname>    :  The Machine raising the message\n"
			"   -PID:<processid> :  The ID of the process raising the message\n"
			"   -TID:<threadid>  :  The ID of the thread raising the message\n"
			"   -I:<ins string 1>,<ins string 2>,...,<ins string 12>\n"
			"                    :  Specifies the insertion strings for\n"
			"                    :  the raised status message\n"
			"   -U:<username>    :  Userid for connection\n"
			"      <password>    :  Password for Userid\n"
		);
	}
}
