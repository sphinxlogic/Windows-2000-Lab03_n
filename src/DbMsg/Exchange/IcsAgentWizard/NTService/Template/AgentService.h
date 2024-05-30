/************************************************************************
*                                                                       *
*   $$Root$$.h														*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

//
// The names of registry keys and values 
// used by the ICS Agent Service
//
const TCHAR szRegKeyServiceName[]			= _TEXT("ICS_$$Root$$");
const TCHAR szRegKeyServiceDisplayName[]	= _TEXT("ICS$$Root$$Service");
const TCHAR szRegValueICSDataDirectory[]	= _TEXT("$$Root$$_Data");

//
// The completion key used by the handler.
// Signifies that the I/O completion event
// is a service control.
//
const DWORD CK_SERVICECONTROL				= 0x00000080;

//
// User-defined service control codes:
//
#define SERVICE_CONTROL_RUN					0x00000000
#define SERVICE_CONTROL_SYNCH				0x00000080 

//
// User defined service states:
// 
#define SERVICE_SYNCH_PENDING				0x00000080

//
// State transition data
//
DWORD dwSrvCtrlToPend[256] = {   // 255 is max user-defined code
	/* 0: SERVICE_CONTROL_RUN				*/	SERVICE_START_PENDING, 
	/* 1: SERVICE_CONTROL_STOP				*/	SERVICE_STOP_PENDING,
	/* 2: SERVICE_CONTROL_PAUSE				*/	0,	// unsupported
	/* 3: SERVICE_CONTROL_CONTINUE			*/	0,	// unsupported
	/* 4: SERVICE_CONTROL_INTERROGATE		*/	0, 
	/* 5: SERVICE_CONTROL_SHUTDOWN			*/	SERVICE_STOP_PENDING,
	/* 6: SERVICE_CONTROL_PARAMCHANGE		*/	0,	// unsupported
	/* 7  SERVICE_CONTROL_NETBINDADD		*/  0,	// unsupported
	/* 8  SERVICE_CONTROL_NETBINDREMOVE		*/	0,	// unsupported
	/* 9  SERVICE_CONTROL_NETBINDENABLE		*/	0,	// unsupported
	/* 10 SERVICE_CONTROL_NETBINDDISABLE	*/	0,	// unsupported
	/* User-defined states:	128-255			*/	0
};

DWORD dwSrvPendToState[256] = { 
	/* 0: Undefined					*/ 0,
	/* 1: SERVICE_STOPPED			*/ 0,	// not a pending state
	/* 2: SERVICE_START_PENDING		*/ SERVICE_RUNNING,
	/* 3: SERVICE_STOP_PENDING		*/ SERVICE_STOPPED, 
	/* 4: SERVICE_RUNNING			*/ 0,	// not a pending state
	/* 5: SERVICE_CONTINUE_PENDING	*/ 0,	// unsupported
	/* 6: SERVICE_PAUSE_PENDING		*/ 0,	// unsupported
	/* 7: SERVICE_PAUSED			*/ 0,	// not a pending state
	/* User-defined states:			*/ 0
};

//
// Functions used in the operation of the ICS Agent Service
//
void WINAPI Handler(DWORD fdwControl);
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR * lpszArgv);

//
// Utility functions used by the ICS Agent Service
//
BOOL ReportICSEvent(LPCTSTR szMsg, int iMsgType);

//
// Functions used to install/uninstall the ICS Agent Service
//
BOOL AddEventSource();		
BOOL CreateAgentService();
BOOL RemoveAgentService();
BOOL RemoveEventSource();
BOOL SetICSDataDirectory(LPCTSTR lpszDir);

$$IF(SERVICE_POLL_CONTINUOUSLY)
//
// Function to continually request the service to synchronize
DWORD WINAPI AutoSyncher(LPVOID lpParameter);
const DWORD dwPollingInterval = 30000;
$$ENDIF

//
// Global variables
//

//
// Global handle, used by I/O completion ports
// to communciate between threads
//
HANDLE g_hIOCP = NULL;

// The handler function for our NT service
const LPHANDLER_FUNCTION g_lpHandler	= Handler;

//
// The directory containing all ICS data, 
// such as which folders are to be monitored, 
// and the synchronization state of each 
// monitored folder
//
TCHAR g_szICSDataDirectory[MAX_PATH];			





