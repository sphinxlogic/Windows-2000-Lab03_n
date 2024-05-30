// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// InvList - Version 1.0
//
// Invlist Demonstrates:
// IWbemObjectSink implementation
// IWbemLocator->ConnectServer
// IWbemServices->ExecQuery
// IWbemServices->ExecQueryAsync
// IWbemClassObject->Get
//   InvList generates SMS client inventory statistics.
// After parsing the command line options and connecting, an
// instance of CInvSink (invsink.cpp) is created.  A call to 
// IWbemServices->ExecQueryAsync is performed passing the new
// CInvSink as the ResponseHandler parameter.  CInvSink->Wait is
// then called to pause execution until the query has completed.
// Executing the query synchronously would have been ideal in this
// situation; an asynchronous call is used for demonstration purposes.
// (for more information, see the section titled Asynchronous Processing 
// in the WMI SDK documentation)  ProcessResults() is then passed
// the query results.  For each result from the asynchronous query
// a Count query is constructed and executed.  The results of each
// count query are then displayed.
// *************************************************************

#define _WIN32_DCOM
#include <wbemidl.h>
#include <comdef.h>
#include <stdio.h>
#include <conio.h>
#include "invsink.h"
#include "wbemsec.h"

#define MAX_PASSWORD_LENGTH 255


// ********************************************************
// Global Variables:
// These will store command line parameters
// ********************************************************

WCHAR *gpwszServer = NULL;			// server to connect to
WCHAR *gpwszUser = NULL;			// username to connect with
WCHAR *gpwszPassword = NULL;		// password for user
bool gbOSQuery = false;		// Query Operating Systems?
bool gbCPUQuery = false;	// Query CPUs?
bool gbRAMQuery = false;	// Query RAM?

bool gbPassAlloced = false;			// was password dynamically allocated?

IWbemServices *gpWbemServices = NULL;	// Global WMI services pointer


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


// ****************************************************************************
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
			else if ( !wcsnicmp(argv[iLoop] + 1, L"O", 1) ) {
				gbOSQuery = true;	
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"C", 1) ) {
				gbCPUQuery = true;	
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"M", 1) ) {
				gbRAMQuery = true;	
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"?", 1) ) return false;	// help
		}
	}

	if( !gbOSQuery && !gbCPUQuery && !gbRAMQuery ) {
		gbOSQuery = true;
		gbCPUQuery = true;
		gbRAMQuery = true;
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



// ********************************************************
// ProcessResults : Execute Count queries and display results
//
// [in] IWbemClassObject **ppObjArray
// [in] LONG ObjCount
// [in] int QueryMode
// Returns: int
//		0 Success
//		1 Count query failed
//		2 SetSecurity failed
// ********************************************************
int ProcessResults(IWbemClassObject **ppObjArray, LONG ObjCount, int QueryMode) {
	
	if( ObjCount == 0 ) return 0;
	
	IWbemClassObject *pCountObj = NULL;
	IEnumWbemClassObject *pEnum = NULL;

	WCHAR pwszQuery[255];
	int iLoop;
	ULONG RetCount;

	VARIANT vCaption;
	VARIANT vClockSpeed;
	VARIANT vName;
	VARIANT vMem;
	VARIANT vCount;

	VariantInit(&vCaption);
	VariantInit(&vClockSpeed);
	VariantInit(&vName);
	VariantInit(&vMem);
	VariantInit(&vCount);

	
	// Print a little header
	switch( QueryMode ) {
		case INVQUERY_OS:
			printf("\n-- Operating System Statistics --\n");
			printf("-[count]-[OS Name]---------------\n");
			break;
		case INVQUERY_CPU:
			printf("\n-- System Processor Statistics --\n");
			printf("-[count]-[Processor]-------------\n");
			break;
		case INVQUERY_RAM:
			printf("\n-- Physical Memory Statistics ---\n");
			printf("-[count]-[Total]-----------------\n");
			break;
		}

	for( iLoop=0; iLoop < ObjCount; iLoop++ ) {

		// Build a Count query based on which query mode the user specified on
		// the command line
		switch( QueryMode ) {
		case INVQUERY_OS:
			ppObjArray[iLoop]->Get(_bstr_t(L"Caption"), 0, &vCaption, NULL, NULL);
			swprintf(pwszQuery, L"SELECT Count(*) FROM SMS_G_System_OPERATING_SYSTEM WHERE Caption = \"%wS\"", V_BSTR(&vCaption));
			break;
		case INVQUERY_CPU:
			ppObjArray[iLoop]->Get(_bstr_t(L"CurrentClockSpeed"), 0, &vClockSpeed, NULL, NULL);
			ppObjArray[iLoop]->Get(_bstr_t(L"Name"), 0, &vName, NULL, NULL);
			swprintf(pwszQuery, L"SELECT Count(*) FROM SMS_G_System_PROCESSOR WHERE CurrentClockSpeed = %d AND Name = \"%wS\"", V_UI4(&vClockSpeed), V_BSTR(&vName));
			break;
		case INVQUERY_RAM:
			ppObjArray[iLoop]->Get(_bstr_t(L"TotalPhysicalMemory"), 0, &vMem, NULL, NULL);
			swprintf(pwszQuery, L"SELECT Count(*) FROM SMS_G_System_X86_PC_MEMORY WHERE TotalPhysicalMemory = %d", V_UI4(&vMem));
			break;
		}

		// Execute the query to get a count of the instances meeting the where clause
		// criteria. The query returns a single enumerator object.
		if( FAILED( gpWbemServices->ExecQuery(_bstr_t(L"WQL"), _bstr_t(pwszQuery), 0, NULL, &pEnum) ) ) {
			return 1;
		}

		// Since we set the programs default authentication level to none using 
		// CoInitialSecurity, we must now set the proxy blanket for all interface 
		// pointers not directly created from  IWbemLocator. This call sets the 
		// authentication and impersonation levels to use with the pEnum interface 
		// pointer. Regardless, it is a good practice to set the proxy
		// blanket before using out-of-process interface pointers.
		if( FAILED( SetInterfaceSecurity(pEnum, NULL, gpwszUser, gpwszPassword, true) ) ) {
			pEnum->Release();
			printf("SetInterfaceSecurity failed.  Try -u:DOMAIN\\USER\n");
			return 2;
		}

		// Use the IEnumWbemClassObject::Next method to retrieve first the instance
		// returned from the Count query.
		while( pEnum->Next(-1, 1, &pCountObj, &RetCount) == S_OK) {
			if(pCountObj == NULL) printf("pCountObj == NULL\n");
			
			// Retrieve count result
			pCountObj->Get(_bstr_t(L"Count"), 0, &vCount, NULL, NULL);
			
			// Print the result to the screen
			switch( QueryMode ) {
			case INVQUERY_OS:
				printf(" %6d   %wS\n", V_UI4(&vCount), V_BSTR(&vCaption));
				break;
			case INVQUERY_CPU:
				printf(" %6d   %wS %dMHz\n", V_UI4(&vCount), V_BSTR(&vName), V_UI4(&vClockSpeed));
				break;
			case INVQUERY_RAM:
				//Put a +1 in there to make the memory into a friendly value, not an odd one.
				printf(" %6d   %dMB\n", V_UI4(&vCount), (V_UI4(&vMem) / 1024) + 1);
				break;
			}
			VariantClear(&vCount);
			if(pCountObj) pCountObj->Release();
			pCountObj = NULL;
		}
		
		pEnum->Release();
		pEnum = NULL;
		VariantClear(&vCaption);
		VariantClear(&vName);
		VariantClear(&vClockSpeed);
		VariantClear(&vMem);
	}

	return 0;
}

// **************************************************************************
// wmain : 
// Using wmain for the WCHAR argv.
// **************************************************************************
extern "C" void wmain(int argc, WCHAR *argv[]) {
	
	// Parse command line, print help if false is returned
	if( ParseCommandLine(argc, argv) ) {
		
		printf("Connecting...");
		
		switch( Init(gpwszServer, gpwszUser, gpwszPassword, gpWbemServices) ) {
		case 0:
			printf("done.\n\n");
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

		// Query OS's
		if( gbOSQuery ) {
			
			// Create a new copy of the inventory object sink.
			CInvSink *pOSSink = new CInvSink(gpWbemServices, INVQUERY_OS);

			// Make an asynchronous query to get all distinct instances from the 
			// SMS_G_System_Operating_System class. Pass the object sink interface to
			// WMI, so the data can be passed back via the Indicate method of the sink.
			if( FAILED( gpWbemServices->ExecQueryAsync(_bstr_t(L"WQL"), _bstr_t(L"Select DISTINCT Caption FROM SMS_G_System_OPERATING_SYSTEM"), 0, NULL, pOSSink) ) ) {
				printf("ExecQueryAsync Failed.");
			} else {
				// Wait until the query has completed.
				pOSSink->Wait();
				ProcessResults(pOSSink->m_aObjects, pOSSink->m_lObjCount, INVQUERY_OS);
			}

			pOSSink->Release();
		}

		// Query processors
		if( gbCPUQuery ) {
			
			// Create a new copy of the inventory object sink.
			CInvSink *pCPUSink = new CInvSink(gpWbemServices, INVQUERY_CPU);

			// Make an asynchronous query to get all distinct instances from the 
			// SMS_G_System_Operating_System class. Pass the object sink interface to
			// WMI, so the data can be passed back via the Indicate method of the sink.
			if( FAILED( gpWbemServices->ExecQueryAsync(_bstr_t(L"WQL"), _bstr_t(L"Select DISTINCT CurrentClockSpeed, Name FROM SMS_G_System_PROCESSOR"), 0, NULL, pCPUSink) ) ) {
				printf("ExecQueryAsync Failed.");
			} else {
				// Wait until the query has completed.
				pCPUSink->Wait();
				ProcessResults(pCPUSink->m_aObjects, pCPUSink->m_lObjCount, INVQUERY_CPU);
			}

			pCPUSink->Release();
		}

		// Query memory
		if( gbRAMQuery ) {

			// Create a new copy of the inventory object sink.
			CInvSink *pRAMSink = new CInvSink(gpWbemServices, INVQUERY_RAM);

			// Make an asynchronous query to get all distinct instances from the 
			// SMS_G_System_Operating_System class. Pass the object sink interface to
			// WMI, so the data can be passed back via the Indicate method of the sink.
			if( FAILED( gpWbemServices->ExecQueryAsync(_bstr_t(L"WQL"), _bstr_t(L"Select DISTINCT TotalPhysicalMemory FROM SMS_G_System_X86_PC_MEMORY"), 0, NULL, pRAMSink) ) ) {
				printf("ExecQueryAsync Failed.");
			} else {
				// Wait until the query has completed.
				pRAMSink->Wait();
				ProcessResults(pRAMSink->m_aObjects, pRAMSink->m_lObjCount, INVQUERY_RAM);
			}

			pRAMSink->Release();
		}

		if( gbPassAlloced ) CoTaskMemFree(gpwszPassword);
		gpWbemServices->Release();
		CoUninitialize();
	}
	else {
		printf(
			"\nINVLIST -- Print SMS Client Inventory Statistics\n"
			"------------------------------------------------\n\n"
			"Usage:  invlist <server> [-O] [-C] [-M] [-U:<user> [<password> | *]]\n"
			"\n"
			"Where:\n"
			"   server   :  SMS Server\n"
			"   user     :  Userid for connection\n"
			"   password :  Password for Userid\n"
			"   -O       :  Query Operating System inventory\n"
			"   -C       :  Query Processor inventory\n"
			"   -M       :  Query RAM inventory\n"
			"Note:\n"
			"   By default -O, -C, and -M are specified.\n"
		);
	}
}
