/************************************************************************
*                                                                       *
*   $$Root$$.cpp														*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#include "stdafx.h"
#include "$$Root$$Agent.h"
#include "$$Root$$.h"


void WINAPI ServiceMain(DWORD dwArgc,
						LPTSTR * lpszArgv)
{
	LP$$ROOT$$AGENT			lpAgent = NULL;
	DWORD					dwBytesTransferred;
	DWORD					dwCompKey;
	DWORD					fdwControl;
$$IF(SERVICE_POLL_CONTINUOUSLY)
	DWORD					dwThreadID;
	HANDLE					hThread;
$$ENDIF
	HRESULT					hResult;
	OVERLAPPED *		    lpOverlapped = NULL;
	SERVICE_STATUS_HANDLE	hService;
	SERVICE_STATUS			sStatus;


	//
	// Give the service its first service control
	//
	fdwControl = SERVICE_CONTROL_RUN;
	
	//
	// Register the service with the SCM.  This handle should
	// never be closed
	//
	hService = RegisterServiceCtrlHandler(
		szRegKeyServiceName, 
		(LPHANDLER_FUNCTION)Handler
		);
	if (hService == NULL)
	{
		ErrorMessage(_TEXT("Could not register service ctrl handler!"));
	}
	else
	{
		//
		// Create a new agent
		lpAgent = new C$$Root$$Agent();
		if (lpAgent == NULL)
		{
			ErrorMessage(_TEXT("Out of memory!"));
		}
		else
		{

			sStatus.dwServiceType		= SERVICE_WIN32_OWN_PROCESS; 
			sStatus.dwControlsAccepted	= SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
 
			// Create the completion port and save its handle in a global
			// variable so that the Handler function can access it.
			g_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
			if (g_hIOCP == NULL)
			{
				ErrorMessage("Could not create IO completion port!");
			}
			else
			{
				dwSrvCtrlToPend[SERVICE_CONTROL_SYNCH]	= SERVICE_SYNCH_PENDING;
				dwSrvPendToState[SERVICE_SYNCH_PENDING] = SERVICE_RUNNING;

$$IF(SERVICE_POLL_CONTINUOUSLY)
				//
				// Create a thread to continuously request
				// that the service synchronize
				hThread = CreateThread(
					NULL,
					0,
					(LPTHREAD_START_ROUTINE)AutoSyncher,
					NULL,
					0,
					&dwThreadID
					);
				if (hThread == NULL)
				{
					WarningMessage("Could not start auxiliary polling thread");
				}

$$ENDIF
				do 
				{
					// We got a new control code
					sStatus.dwWin32ExitCode = NO_ERROR; 
					sStatus.dwServiceSpecificExitCode = 0; 
					sStatus.dwCheckPoint = 0; 
					sStatus.dwWaitHint = 0;

					if (fdwControl == SERVICE_CONTROL_INTERROGATE) 
					{
						SetServiceStatus(hService, &sStatus);
					}
					else
					{

						//
						// All control codes return some PENDING state.
						// Determine which PENDING state to return.
						//
						if (dwSrvCtrlToPend[fdwControl] != 0) 
						{
							sStatus.dwCurrentState	= dwSrvCtrlToPend[fdwControl]; 
							sStatus.dwCheckPoint	= 0;  // wait hints not used
							sStatus.dwWaitHint		= 0;  
							SetServiceStatus(hService, &sStatus);
						}

						switch (fdwControl) 
						{
							case SERVICE_CONTROL_RUN:
								hResult = lpAgent->Start();
								if (hResult != ERROR_SUCCESS) // is actually a winerror code
								{
									ErrorMessage("Agent could not be started");
									sStatus.dwCurrentState = SERVICE_STOP_PENDING;
								}
								else
									StatusMessage("Agent started");
								break;
							case SERVICE_CONTROL_SYNCH:   // User-defined control 
								hResult = lpAgent->Synch();
								if (hResult != ERROR_SUCCESS) // is actually a winerror code
								{
									ErrorMessage("Agent synch failed, stopping service");
									sStatus.dwCurrentState = SERVICE_STOP_PENDING;
								}
								else
									StatusMessage("Agent synch succeeded");
								break;
							case SERVICE_CONTROL_STOP:
							case SERVICE_CONTROL_SHUTDOWN:
								break;
						}

						// Determine which complete state to return
						if (dwSrvPendToState[sStatus.dwCurrentState] != 0) 
						{
							sStatus.dwCurrentState = dwSrvPendToState[sStatus.dwCurrentState]; 
							sStatus.dwCheckPoint = sStatus.dwWaitHint = 0;
							SetServiceStatus(hService, &sStatus);
						}

						if (sStatus.dwCurrentState != SERVICE_STOPPED) 
						{
							DebugMessage("Waiting for ctrl code...");
							// Sleep until a control code comes in or a client connects
							GetQueuedCompletionStatus(
								g_hIOCP, 
								&dwBytesTransferred, 
								&dwCompKey, 
								&lpOverlapped, 
								INFINITE
							);
							fdwControl = dwBytesTransferred;
						}
					}  // if (fdwControl == SERVICE_CONTROL_INTERROGATE) ... else 
				} while (sStatus.dwCurrentState != SERVICE_STOPPED);
			}
		}
	}


	//
	// Cleanup and stop this service
	if (lpAgent != NULL) 
	{
		lpAgent->Stop();
		delete lpAgent;
		lpAgent = NULL;
	}

	if (g_hIOCP != NULL)
	{
		CloseHandle(g_hIOCP); 
		g_hIOCP = NULL;
	}

$$IF(SERVICE_POLL_CONTINUOUSLY)
	if (hThread != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hThread);
		hThread = INVALID_HANDLE_VALUE;
	}
$$ENDIF
	
}


void WINAPI Handler(DWORD fdwControl)
{
	PostQueuedCompletionStatus(
		g_hIOCP, 
		fdwControl, 
		CK_SERVICECONTROL, 
		NULL
		);
}

$$IF(SERVICE_POLL_CONTINUOUSLY)
DWORD WINAPI AutoSyncher(LPVOID lpParameter)
{
	while (g_hIOCP != NULL)
	{
		SleepEx(dwPollingInterval, FALSE);
		PostQueuedCompletionStatus(
			g_hIOCP,
			SERVICE_CONTROL_SYNCH,
			CK_SERVICECONTROL,
			NULL
			);
	}

	return 0;  // Must deal with case if PQCS fails 
}
$$ENDIF

// 
// The initialize procedure assigns the global variable
// g_szICSDataDirectory from a parameter obtained from the registry.
//
BOOL Initialize()
{
	BOOL fSuccess = FALSE;
	DWORD dwCbValue;
	DWORD dwDataType;
	DWORD dwResult;
	HKEY hKey;
	TCHAR szBuffer[MAX_PATH];

	//
	// Assign the global variable g_szICSDataDirectory
	// so that it points to the directory specified by
	// the ICSDataDirectory value in the registry
	//
	_stprintf(szBuffer, "SYSTEM\\CurrentControlSet\\Services\\%s", szRegKeyServiceName);
	dwResult = RegOpenKey(
		HKEY_LOCAL_MACHINE,
		szBuffer,
		&hKey
		);
	if (dwResult == ERROR_SUCCESS)
	{
		dwResult = RegQueryValueEx(
			hKey,
			szRegValueICSDataDirectory,
			NULL,
			&dwDataType,
			(LPBYTE)NULL,
			&dwCbValue
			);

		if ((dwResult == ERROR_SUCCESS) || (dwResult == ERROR_MORE_DATA ))
		{
			LPBYTE	szValue = new BYTE[dwCbValue];

			if (szValue)
			{
				dwResult = RegQueryValueEx(
					hKey,
					szRegValueICSDataDirectory,
					NULL,
					&dwDataType,
					(LPBYTE)szValue,
					&dwCbValue
					);

				if (dwResult == ERROR_SUCCESS)
				{
					lstrcpy(g_szICSDataDirectory, (LPTSTR)szValue);
					fSuccess = TRUE;
				}

				delete [] szValue;

			}
			else
			{
				dwResult = ERROR_NOT_ENOUGH_MEMORY;
			}
		}
	}

	//
	// Cleanup: close opened HKEY's
	//
	if (hKey != NULL) RegCloseKey(hKey);

	//
	// If an error was encountered, set the last error
	// to be dwResult
	//
	if (!fSuccess) SetLastError(dwResult);

	return fSuccess;
}

int main(int argc, char* argv[])
{
	int nArgc = argc;
	BOOL fStartService = (nArgc < 2);

	for (int i = 1; i < nArgc; i++) 
	{
		if ((argv[i][0] == _TEXT('-')) || (argv[i][0] == _TEXT('/'))) 
		{
			// Command line switch
			if (lstrcmpi(&argv[i][1], _TEXT("install")) == 0) 
			{
				TCHAR szDir[MAX_PATH];
				if (!CreateAgentService()) printf("Agent service not created");
				if (!AddEventSource()) printf("Agent service not added as event source");
				GetCurrentDirectory(MAX_PATH, szDir);
				if (!SetICSDataDirectory(szDir)) printf("ICS Data directory not set");				
			}

			if (lstrcmpi(&argv[i][1], _TEXT("remove"))  == 0)
			{
				if (!RemoveEventSource()) printf("Event source not removed");
				if (!RemoveAgentService()) printf("Agent service not removed");
			}

			//If you want to add support to run this service as a console 
			//application add "-debug" command line option and implementation
			//support for it. When this option is found in command line you will
			//have to call ServiceMain() directly and also will have to put
			//some related code. For more details please refer to the 
			//code of winwrap project which is supplied as part of exchange
			//sdk (exchsdk). You will have to simply implement some of the
			//equivalent functionality as in winwrap. Another example is
			//gwsample project which is also part of edk.

		}
	}

	if (fStartService)
	{
		if (Initialize())
		{
			SERVICE_TABLE_ENTRY lpServiceStartTable[] = 
			{
				{(char *)szRegKeyServiceName, ServiceMain},
				{NULL, NULL}
			};
		
			StartServiceCtrlDispatcher(lpServiceStartTable); // returns when all services terminate
		}
		else
		{
			ErrorMessage("Can't initialize agent service");
		}
	}

	return 0;
}

/********************************************************************************
*																				*
* The following procedures are utility procedures used by the					*
* ICS Agent service																*
*																				*
********************************************************************************/

//
// Reports an ICS event by adding the specified string to the event log.
// 
BOOL ReportICSEvent(LPCTSTR szMsg,
					int iMsgType)
{    
	BOOL fSuccess = FALSE;
	HANDLE hEventSource;  

    hEventSource = RegisterEventSource(
		NULL,						// uses local computer 
        szRegKeyServiceDisplayName  // the display name of this service  
		);          
	if (hEventSource != NULL) 
	{
		fSuccess = ReportEvent(
			hEventSource,			// event log handle 
            iMsgType,				// event type 
            0,						// category zero 
            ((DWORD)0xC0000004L),   // event identifier 
            NULL,					// no user security identifier 
            1,						// one substitution string 
            0,						// no data 
            (LPCTSTR *)&szMsg,		// pointer to string array 
            NULL					// pointer to data 
			);
	}

	//
	// Cleanup: deregister the event source
	//
    if (hEventSource != NULL) DeregisterEventSource(hEventSource); 

	//
	// Return a value to indicate success/failure
	//
	return fSuccess;
}  


/********************************************************************************
*																				*
* The following procedures handle the installation/deinstallation of the		*
* ICS Agent service.															*
*																				*
********************************************************************************/


//
// Modifies the registry so the ICS Agent Service can use the event log.
// (Establishes the ICS Agent Service as an event source).
//
// Returns TRUE upon success, FALSE on failure.  Call GetLastError()
// for error information.
// 
BOOL AddEventSource()
{
	BOOL fSuccess = FALSE;
	DWORD dwResult;
    DWORD dwSupportedEventTypes; 
    HKEY hKey; 
    TCHAR szBuffer[MAX_PATH]; 

	//
	// Create a new registry key to represent the ICS Agent
	// event source.  
	//

	// Store the name of the new key 
	_stprintf(szBuffer, 
			  "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\%s", 
			  szRegKeyServiceDisplayName);
 
	// Create the key itself
    dwResult = RegCreateKey(
		HKEY_LOCAL_MACHINE, 
		szBuffer,
		&hKey
		);
	if (dwResult == ERROR_SUCCESS)
	{		
		// Set the name of the message file. 
		lstrcpy(szBuffer, "%SystemRoot%\\System\\");
		_stprintf(szBuffer + lstrlen(szBuffer), "%s.dll\0", szRegKeyServiceDisplayName);
 
		// Add the name to the EventMessageFile subkey. 
		dwResult = RegSetValueEx(
			hKey,								// subkey handle 
			"EventMessageFile",					// value name 
			0,									// must be zero 
			REG_EXPAND_SZ,						// value type 
			(LPBYTE)szBuffer,					// pointer to value data 
			sizeof(TCHAR) * lstrlen(szBuffer)	// length of value data 
			);
		if (dwResult == ERROR_SUCCESS)
		{
			//
			// Set the supported event types in the TypesSupported subkey. 
			//
			dwSupportedEventTypes = EVENTLOG_ERROR_TYPE		| 
									EVENTLOG_WARNING_TYPE	| 
									EVENTLOG_INFORMATION_TYPE; 
 
			dwResult = RegSetValueEx(
				hKey,								// subkey handle 
				"TypesSupported",					// value name 
				0,									// must be zero 
				REG_DWORD,							// value type 
				(LPBYTE) &dwSupportedEventTypes,	// pointer to value data 
				sizeof(DWORD)						// length of value data 
				);
			if (dwResult == ERROR_SUCCESS)
			{
				fSuccess = TRUE;
			}
		}
	} 

	//
	// Close the handle to the subkey we opened
	//
    RegCloseKey(hKey); 

	//
	// If the function has failed, the error code will be contained in dwResult
	//
	if (!fSuccess) SetLastError(dwResult);

	//
	// Return a value to indicate success or failure
	//
	return fSuccess;
} 
 

//
// Installs the ICS Agent service.  
//
// Returns TRUE on success, FALSE on failure.  Call GetLastError()
// for error information.
//
BOOL CreateAgentService() {     
	
	BOOL fSuccess = FALSE;
	TCHAR szBinaryPathName[MAX_PATH];
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
    
	GetCurrentDirectory(MAX_PATH, szBinaryPathName);
	lstrcat(szBinaryPathName , _TEXT("\\$$ROOT$$.exe"));

	schSCManager = OpenSCManager(     
		NULL,					// local machine 
		NULL,					// ServicesActive database 
		SC_MANAGER_ALL_ACCESS	// full access rights  if (schSCManager == NULL) 
		); 
	if (schSCManager != NULL)
	{	
		schService = CreateService( 
			schSCManager,				// SCManager database 
			szRegKeyServiceName,		// name of service 
			szRegKeyServiceDisplayName, // service name to display 
			SERVICE_ALL_ACCESS,			// desired access 
			SERVICE_WIN32_OWN_PROCESS,	// service type 
			SERVICE_DEMAND_START,		// start type 
			SERVICE_ERROR_NORMAL,		// error control type 
			szBinaryPathName,			// service's binary 
			NULL,						// no load ordering group 
			NULL,						// no tag identifier 
			NULL,						// no dependencies 
			NULL,						// LocalSystem account 
			NULL);						// no password      if (schService == NULL) 
		if (schService != NULL)
		{
			fSuccess = TRUE;
		}
	}

	//
	// Cleanup code: close the open service handles
	//
	if (schService != NULL) CloseServiceHandle(schService); 
	if (schSCManager != NULL) CloseServiceHandle(schSCManager);

	//
	// If the function has failed, the error code will be 
	// accessable through GetLastError(), so we do not need to set 
	// the last error ourselves.
	//
	// Return a value to indicate success or failure
	//
	return fSuccess;

} 

//
// Uninstalls the ICS Agent service.  Returns TRUE
// on success, FALSE on failure.  Note that this function
// does NOT do such housekeeping as removing the ICS Agent's
// event source from the registry, or removing any other 
// ICS configuration information found in the registry.  This
// should be done separately.  
//
BOOL RemoveAgentService() 
{
	BOOL fSuccess = FALSE;
	SC_HANDLE schSCManager;
	SC_HANDLE schService;

	// Open the SCM on this machine.
	schSCManager = OpenSCManager(
	   NULL, 
	   NULL, 
	   SC_MANAGER_CONNECT
	   );
	if (schSCManager != NULL)
	{
		// Open this service for DELETE access
		schService = OpenService(
			schSCManager, 
			szRegKeyServiceName, 
			DELETE
			);
		if (schService != NULL)
		{
			// Remove this service from the SCM's database.
			fSuccess = DeleteService(schService);
		}
	}

	//
	// Cleanup:  close the SC_HANDLE's we opened
	//
	if (schSCManager != NULL) CloseServiceHandle(schSCManager);
	if (schService != NULL) CloseServiceHandle(schService);

	return fSuccess;
}

//
// Removes all keys from the registry required to establish
// this ICS Agent as an event source.
//
BOOL RemoveEventSource()
{
	BOOL fSuccess = FALSE;
	DWORD dwResult;
    TCHAR szBuffer[MAX_PATH]; 

	//
	// Create a registry key to represent the ICS Agent
	// event source.  
	//

	// Store the name of the event source's key:
	_stprintf(szBuffer, 
			  "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\%s", 
			  szRegKeyServiceDisplayName);
 
	//
	// Delete the key specified in szBuffer
	//
    dwResult = RegDeleteKey(
		HKEY_LOCAL_MACHINE, 
		szBuffer
		);
	if (dwResult == ERROR_SUCCESS)
	{		
		fSuccess = TRUE;
	}

	//
	// If the function has failed, the error code will be contained in dwResult
	//
	if (!fSuccess) SetLastError(dwResult);

	//
	// Return a value to indicate success or failure
	//
	return fSuccess;
} 


//
// Sets the directory containing ICS data to be the
// specified parameter.  
//
// Returns TRUE on success, FALSE on failure.  Call
// GetLastError() to get error information.
//
BOOL SetICSDataDirectory(LPCTSTR lpszDir)
{
	BOOL fSuccess = FALSE;
	DWORD dwResult;
    HKEY hKey; 
	TCHAR szBuffer[MAX_PATH]; 

	if (lpszDir)
	{
		//
		// Store the location of our ICS Agent registry entries in szBuffer
		// 
		_stprintf(szBuffer, 
				  "SYSTEM\\CurrentControlSet\\Services\\%s", 
				  szRegKeyServiceName);
 
		//
		// Open the key found at the location specified in szBuffer
		//
		dwResult = RegCreateKey(
			HKEY_LOCAL_MACHINE, 
			szBuffer,
			&hKey
			);
		if (dwResult == ERROR_SUCCESS)
		{	 
			_stprintf(szBuffer, "%s\0", lpszDir);

			//
			// Create/Set the new ICSDataDirectory value 
			// 
			dwResult = RegSetValueEx(
				hKey,								// subkey handle 
				szRegValueICSDataDirectory,			// value name 
				0,									// must be zero 
				REG_EXPAND_SZ,						// value type 
				(LPBYTE)szBuffer,					// pointer to value data 
				sizeof(TCHAR) * lstrlen(szBuffer)	// length of value data 
				);
			if (dwResult == ERROR_SUCCESS)
			{
				fSuccess = TRUE;
			}
		}

		//
		// Close the handle to the subkey we opened
		//
		RegCloseKey(hKey); 

	}
	else
	{
		dwResult = ERROR_INVALID_PARAMETER;
	}

	//
	// If the function has failed, the error code will be contained in dwResult
	//
	if (!fSuccess) SetLastError(dwResult);

	//
	// Return a value to indicate success or failure
	//
	return fSuccess;
}

