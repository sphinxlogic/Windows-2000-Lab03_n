// --gwperf.c-------------------------------------------------------------------
//
//  This file contains the DLL side of the Exchange SDK performance 
//  monitoring component.  When this DLL is called by the NT Performance 
//  Monitor it reads the performance data from a shared memory section 
//  created by the gateway side, and returns it to the Performance Monitor.
//  This DLL is also capable of reading the data from several different 
//  gateway processes and combining them into one single Performance 
//  Monitor object with multiple instances.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "monitor.h"
#include "monshare.h"
#include "gwperfm.h"
#include <winperf.h>

//
// Debugging Information
//

// Define VERBOSE_DEBUG here to write to the debug log with every call to 
// CollectGatewayPerformanceData and the routines it calls.  Do this only 
// if you need it, since this routine is called once every second and can 
// quickly fill up your disk!!!

// #define VERBOSE_DEBUG

//
// Local Structure Declarations
//

//$--GINSTANCE------------------------------------------------------------------
//  Holds information about a single gateway instance.
// -----------------------------------------------------------------------------
typedef struct _GInstance			        // (hungarian notation = gi)
{
    BOOL                fOpen;              // TRUE if this instance is open
	HANDLE              hFileMapping;	    // file mapping handle
    LONG                cLockReference;     // mutex lock reference count
	HANDLE              hMutex;			    // mutex handle
	LPMONSHAREDMEMORY   lpmsmMemory;	    // shared mem for gw communication
    LPWSTR              lpwszName;          // gateway instance name
} GINSTANCE, *LPGINSTANCE;

//$--GTYPE----------------------------------------------------------------------
//  Holds information about the gateway type that this DLL handles.
// -----------------------------------------------------------------------------
typedef struct _GType                       // (hungarian notation = gt)
{
    ULONG               cCollectFailures;   // number of times error on collect
    ULONG               cInstances;         // number of instances in array
    LPGINSTANCE         rggiInstances;      // alloc'd array of instance structs
    LONG                iObjectName;        // title index of obj we return
} GTYPE, *LPGTYPE;

//
// Public Function Declarations
//

PM_OPEN_PROC OpenGatewayPerformanceData;
PM_COLLECT_PROC CollectGatewayPerformanceData;
PM_CLOSE_PROC CloseGatewayPerformanceData;

//
// Local Function Declarations
//

static DWORD CreateGType(
    IN  LPWSTR          grwszInstanceNames,
    OUT LPGTYPE *       lppgt);

static DWORD DestroyGType(
    IN OUT  LPGTYPE     lpgt);

static DWORD OpenGInstance(
    IN      LPWSTR      lpwszInstanceName,
    IN OUT  LPGINSTANCE lpgi,
    OUT     LPLONG      lpiObjectName);

static DWORD CloseGInstance(
    IN OUT  LPGINSTANCE lpgi);

static DWORD CountMultiStrings(
    IN  LPWSTR          grwsz,
    OUT LPULONG         pcwsz);

static DWORD LockSharedMemory(
	IN  LPGINSTANCE     lpgi);

static DWORD UnlockSharedMemory(
	IN  LPGINSTANCE     lpgi);

static BOOL fOurDataRequested(
    IN  LPGTYPE         lpgt,
    IN  LPWSTR          lpwszRequest);

static VOID ReadSharedMemoryFromRegistry(
	IN OUT  LPGINSTANCE lpgi);

//
// Local Constants
//

static const ULONG MAX_COLLECT_FAILURES = 10;

//
// Local Variables
//

static LPGTYPE lpgtContext = NULL;

static SECURITY_ATTRIBUTES sa;
static char rgbForSecurityDescriptor[SECURITY_DESCRIPTOR_MIN_LENGTH];

static SECURITY_ATTRIBUTES * psa;
static SECURITY_DESCRIPTOR * psd;

//
// DLL Hook Routines
//

//$--DllEntryPoint------------------------------------------------------------
//  Perform DLL initialization and shutdown.  Returns TRUE if successful, 
//  and FALSE if unsuccessful.
// ---------------------------------------------------------------------------
BOOL WINAPI DllEntryPoint(                  // RETURNS: BOOL
    IN  HINSTANCE       hInstDll,           // DLL instance handle
    IN  DWORD           fdwReason,          // reason we're being called
    IN  LPVOID          lpvReserved)        // reserved
{
    BOOL                fResult             = TRUE;
    BOOL                fEventLogOpen       = FALSE;
    HRESULT             hr                  = NOERROR;
    CHAR                szDllPath[MAX_PATH+1] = {0};
    DWORD               cchDllPath          = 0;

    DEBUGPUBLIC("DllEntryPoint()\n");

    // Check to see why we were called.

    switch (fdwReason)
    {        
        case DLL_PROCESS_ATTACH:

            DEBUGACTION("DLL_PROCESS_ATTACH");

            // Get the path and file name of this DLL.

            cchDllPath = GetModuleFileName(
                GetInstanceModule(hInstDll), 
                szDllPath, 
                sizeof(szDllPath) - 1);
            if (cchDllPath == 0)
            {
                hr = HR_LOG(E_FAIL);
                MODULE_WARNING(
                    "GWPERF_DLL_ENTRY_MODULE_NAME: GetModuleFileName() failed.");
            }

            // If getting the name succeeded then initialize event logging.

            else
            {
                hr = HrEventOpenLog(
                    "EDK GWPerf", 
                    szDllPath, 
                    NULL, 
                    NULL, 
                    NULL, 
                    NULL);
                if (FAILED(hr))
                {
                    MODULE_WARNING1(
                        "GWPERF_DLL_ENTRY_OPEN_LOG: HrEventOpenLog() failed for DLL %s.", 
                        szDllPath);
                }
                else
                {
                    fEventLogOpen = TRUE;
                }
            }

            // Set up a security descriptor with a NULL DACL, to allow all
            // access to an object.  This is used if we need to create the
            // mutex and shared memory section.  Failure to do this is a 
            // fatal error.

            psa = &sa;
            psd = (SECURITY_DESCRIPTOR *)rgbForSecurityDescriptor;

            if (!InitializeSecurityDescriptor(psd, SECURITY_DESCRIPTOR_REVISION))
            {
                EventLogMsg(
                    GWPERF_ERROR, 
                    0, 
                    GetLastError());
                fResult = FALSE;
            }
            else if (!SetSecurityDescriptorDacl(psd, TRUE, (PACL) NULL, FALSE))
            {
                EventLogMsg(
                    GWPERF_ERROR, 
                    0, 
                    GetLastError());
                fResult = FALSE;
            }
            else
            {
                psa->nLength = sizeof(*psa);
                psa->lpSecurityDescriptor = psd;
                psa->bInheritHandle = TRUE;
            }

            // If there was a fatal error on open, then close the event log.

            if (fResult == FALSE && fEventLogOpen == TRUE)
            {
                (void) HrEventCloseLog();
                fEventLogOpen = FALSE;
            }
            
            break;

        case DLL_THREAD_ATTACH:
            DEBUGACTION("DLL_THREAD_ATTACH");
            break;

        case DLL_THREAD_DETACH:
            DEBUGACTION("DLL_THREAD_DETACH");
            break;

        case DLL_PROCESS_DETACH:

            DEBUGACTION("DLL_PROCESS_DETACH");

            // Shut down event logging.

            hr = HrEventCloseLog();
            if (FAILED(hr))
            {
                MODULE_WARNING(
                    "GWPERF_DLL_ENTRY_CLOSE_LOG: HrEventCloseLog() failed for DLL %s.");
            }

            break;

        default:            

            // Invalid reason.

            MODULE_ERROR("GWPERF_DLL_ENTRY_REASON: Invalid reason code.");

            fResult = FALSE;

            break;
    }

    ASSERTERROR(fResult, "GWPERF_DLL_ENTRY_FAILED: GWPerf.dll failed to load.");
    return fResult;
}



//$--OpenGatewayPerformanceData-------------------------------------------------
//  Function called by the NT Performance Monitor (via the registry) to begin 
//  performance monitoring on a gateway.
//
//  NOTE: In this function, all strings are explicitly WCHAR UNICODE strings 
//  because that is what is passed in as device names.
// -----------------------------------------------------------------------------
DWORD APIENTRY OpenGatewayPerformanceData(	// RETURNS: Win32 error code
	IN  LPWSTR          grwszInstanceNames)	// strings from Linkage\Export
{
	DWORD				dwStatus      		= ERROR_SUCCESS;

    DEBUGPUBLIC("OpenGatewayPerformanceData()\n");

    // If we're already open then the path to this DLL must exist in multiple 
    // Performance keys, which is an error.

    if (lpgtContext)
    {
        dwStatus = ERROR_DLL_INIT_FAILED;
        EventLogMsg(
            GWPERF_OPEN_ALREADY_OPEN, 
            0, 
            0);
        goto cleanup;
    }

	// If they didn't have a Linkage\Export value then we can't continue.

	if (grwszInstanceNames == NULL)
	{
        dwStatus = ERROR_DLL_INIT_FAILED;
        EventLogMsg(
            GWPERF_OPEN_NO_LINKAGE, 
            0, 
            0);
        goto cleanup;
	}

    // Create the GTYPE structure and begin all the monitoring.

    dwStatus = CreateGType(grwszInstanceNames, &lpgtContext);
    if (dwStatus)
        goto cleanup;

cleanup:
    return dwStatus;
}



//$--CollectGatewayPerformanceData----------------------------------------------
//  Function called by the NT Performance Monitor to collect performance data 
//  on a gateway.  Always returns either ERROR_SUCCESS or ERROR_MORE_DATA.
// -----------------------------------------------------------------------------
DWORD APIENTRY CollectGatewayPerformanceData( // RETURNS: Win32 error code
	IN      LPWSTR      lpwszRequest,		// type of data requested
	IN OUT  LPVOID *    lppvData,			// buffer where data should be put
	IN OUT  LPDWORD     lpcbBytes,			// size of data buffer
	OUT     LPDWORD     lpcObjectTypes)		// number of object types returned
{
	DWORD				dwStatus      		= ERROR_SUCCESS;

	LPBYTE				*lppData			= (LPBYTE *)lppvData;
	DWORD				igi					= 0;
	LPGINSTANCE	        lpgi				= NULL;
	LPMONSHAREDMEMORY	lpmsm				= NULL;
	BOOL				fPOTCopied			= FALSE;

	LPBYTE				lpOutBuf			= *lppData;
	LPBYTE				lpOutBufPtr			= *lppData;
	DWORD				cbOutBufSize		= *lpcbBytes;
	BOOL				fFoundRunning	    = FALSE;

	PPERF_OBJECT_TYPE	lpOutPOT			= NULL;

#ifdef VERBOSE_DEBUG
    DEBUGPUBLIC("CollectGatewayPerformanceData()\n");
#endif

	// Set the return variables to return no data.

	*lpcbBytes = 0;
	*lpcObjectTypes = 0;
	dwStatus = ERROR_SUCCESS;

    // If they didn't call open before calling here, then log an 
    // error (but only once).

    if (lpgtContext == NULL)
    {
        static BOOL fAlreadyLogged = FALSE;

        if (!fAlreadyLogged)
        {
            EventLogMsg(
                GWPERF_COLLECT_NOT_OPEN, 
                0, 
                0);
            fAlreadyLogged = TRUE;
        }
        goto cleanup;
    }

    // If we've failed too many times then return with no data.

    if (lpgtContext->cCollectFailures > MAX_COLLECT_FAILURES)
    {
		goto cleanup;
    }

    // If we know what our object number is, and the request string is not 
    // asking for our object number, then return with no data.

    if (lpgtContext->iObjectName != -1 && 
        !fOurDataRequested(lpgtContext, lpwszRequest))
        goto cleanup;

	// Loop to build the data structure for all instances by appending 
	// together the structures for each instance.  The new data structure 
	// is created in the buffer provided by the caller.

	for (igi = 0; igi < lpgtContext->cInstances; igi++)
	{
		lpgi = &lpgtContext->rggiInstances[igi];
		lpmsm = lpgi->lpmsmMemory;

		// Initial check for valid data.  If not valid here then don't bother 
        // locking the mutex.  This keeps us from degrading system performance 
        // by locking and unlocking a mutex every time we are called when
        // our gateway isn't running.

		if (!lpmsm->fDataIsValid)
			continue;
        
        // Lock shared memory for gateway instance.  It will be unlocked 
        // later.  Any exceptional conditions between now and "later" must 
        // call UnlockSharedMemory.

		dwStatus = LockSharedMemory(lpgi);
        if (dwStatus)
            goto cleanup;

		// If this shared memory block doesn't contain valid data then skip it.

		lpmsm = lpgi->lpmsmMemory;

		if (!lpmsm->fDataIsValid)
		{
			dwStatus = UnlockSharedMemory(lpgi);
            if (dwStatus)
                goto cleanup;
			continue;
		}

        // If we don't already have our object number then get it from the 
        // shared memory block.

        if (lpgtContext->iObjectName == -1)
        {
            PPERF_OBJECT_TYPE lpPOT = NULL;

            lpPOT = (PPERF_OBJECT_TYPE) 
                (((LPBYTE)(lpgi->lpmsmMemory)) 
                + lpgi->lpmsmMemory->ibHeaderOffset);
    	    lpgtContext->iObjectName = lpPOT->ObjectNameTitleIndex;

            // Now that we finally know our number, check to make sure it is one 
            // of the ones requested.

            if (!fOurDataRequested(lpgtContext, lpwszRequest))
            {
    		    dwStatus = UnlockSharedMemory(lpgi);
                goto cleanup;
            }
        }
        
        // Flag that we found a running gateway instance (i.e. one that has 
        // the fDataIsValid flag set).

		fFoundRunning = TRUE;

		// Copy PERF_OBJECT_TYPE header structure from the first running 
		// gateway instance we find.

		if (!fPOTCopied)
		{
            // If the buffer isn't big enough then request a larger buffer 
            // from the caller.

			if (lpmsm->cbHeaderSize > cbOutBufSize)
			{
    			dwStatus = UnlockSharedMemory(lpgi);
                if (dwStatus)
                    goto cleanup;

				dwStatus = ERROR_MORE_DATA;
				goto cleanup;
			}

            // Copy the header.

			MoveMemory(
				lpOutBufPtr, 
				((LPBYTE)(lpmsm)) + lpmsm->ibHeaderOffset, 
				lpmsm->cbHeaderSize);
			lpOutPOT = (PPERF_OBJECT_TYPE)lpOutBufPtr;
			lpOutBufPtr += lpmsm->cbHeaderSize;
			cbOutBufSize -= lpmsm->cbHeaderSize;

			// Start the header's instance count at 0 instances (it will 
			// be incremented each time we add an instance structure).

			lpOutPOT->NumInstances = 0;

			// Flag that we copied over the PERF_OBJECT_TYPE header structure.

			fPOTCopied = TRUE;
		}

        // If the buffer isn't big enough then request a larger buffer 
        // from the caller.

		if (lpmsm->cbInstanceSize > cbOutBufSize)
		{
			dwStatus = UnlockSharedMemory(lpgi);
            if (dwStatus)
                goto cleanup;

			dwStatus = ERROR_MORE_DATA;
			goto cleanup;
		}

		// Copy the instance data from this gateway instance.

		MoveMemory(
			lpOutBufPtr, 
			((LPBYTE)(lpmsm)) + lpmsm->ibInstanceOffset, 
			lpmsm->cbInstanceSize);
		lpOutBufPtr += lpmsm->cbInstanceSize;
		cbOutBufSize -= lpmsm->cbInstanceSize;

		// Bump up variables in the PERF_OBJECT_TYPE header to reflect 
		// the addition of this instance.

		lpOutPOT->TotalByteLength = lpOutBufPtr - lpOutBuf;
		lpOutPOT->NumInstances++;

		// Unlock the shared memory.

		dwStatus = UnlockSharedMemory(lpgi);
        if (dwStatus)
            goto cleanup;
	}

	// If we found a running gateway instance then update the return variables.

	if (fFoundRunning)
	{
		*lpcObjectTypes = 1;
		*lppData = lpOutBufPtr;
		*lpcbBytes = lpOutBufPtr - lpOutBuf;
	}

cleanup:
    // If there was an error other than ERROR_MORE_DATA, then increment 
    // the collect failure count.  When there gets to be too many errors, 
    // we will start returning "no data" on every call to collect.

    if (dwStatus && dwStatus != ERROR_MORE_DATA)
    {
        ++lpgtContext->cCollectFailures;

        if (lpgtContext->cCollectFailures > MAX_COLLECT_FAILURES)
        {
            EventLogMsg(
                GWPERF_COLLECT_TOO_MANY_FAILURES, 
                0, 
                0);
        }

        dwStatus = ERROR_SUCCESS;
    }

	return dwStatus;
}



//$--CloseGatewayPerformanceData------------------------------------------------
//  Function called by the NT Performance Monitor to end collection of 
//  performance data.
// -----------------------------------------------------------------------------
DWORD APIENTRY CloseGatewayPerformanceData(	// RETURNS: Win32 error code
	void)
{
	DWORD				dwStatus      		= ERROR_SUCCESS;

    DEBUGPUBLIC("CloseGatewayPerformanceData()\n");

    // If they didn't call "open" then log an error (but only once).

    if (lpgtContext == NULL)
    {
        static BOOL fAlreadyLogged = FALSE;

        if (!fAlreadyLogged)
        {
            EventLogMsg(
                GWPERF_CLOSE_NOT_OPEN, 
                0, 
                0);
            fAlreadyLogged = TRUE;
        }
        goto cleanup;
    }

    // Free the gateway type context.

    dwStatus = DestroyGType(lpgtContext);
    if (dwStatus)
        goto cleanup;
    lpgtContext = NULL;

cleanup:
	return dwStatus;
}



//$--CreateGType----------------------------------------------------------------
//  Create a GTYPE structure.
// -----------------------------------------------------------------------------
static DWORD CreateGType(                   // RETURNS: Win32 error code
    IN  LPWSTR          grwszInstanceNames, // group of instance name strings
    OUT LPGTYPE *       lppgt)              // allocated GTYPE structure
{
	DWORD				dwStatus      		= ERROR_SUCCESS;
    ULONG               cInstances          = 0;
	LPGINSTANCE	        lpgi				= NULL;
	ULONG				igi					= 0;
	LPWSTR				lpwszInstanceName	= NULL;
    DWORD               iObjectName         = 0;
    LPGTYPE             lpgt                = NULL;

    DEBUGPRIVATE("CreateGType()\n");

    // Count the instance name strings passed to us.

	dwStatus = CountMultiStrings(grwszInstanceNames, &cInstances);
    if (dwStatus)
        goto cleanup;

    // Allocate the GTYPE structure.

    lpgt = malloc(sizeof(*lpgt));
    if (lpgt == NULL)
    {
        dwStatus = ERROR_NOT_ENOUGH_MEMORY;
        EventLogMsg(
            GWPERF_OPEN_ERROR, 
            0, 
            1, dwStatus);
        goto cleanup;
    }
	ZeroMemory(lpgt, sizeof(*lpgt));

    // Fill in various fields in the GTYPE.

    lpgt->cInstances = cInstances;
    lpgt->iObjectName = -1;

	// Allocate an array of GINSTANCE's, one for each instance name string.

	lpgt->rggiInstances = calloc(cInstances, sizeof(GINSTANCE));
	if (lpgt->rggiInstances == NULL)
    {
        dwStatus = ERROR_NOT_ENOUGH_MEMORY;
        EventLogMsg(
            GWPERF_OPEN_ERROR, 
            0, 
            1, dwStatus);
        goto cleanup;
    }
	ZeroMemory(lpgt->rggiInstances, cInstances * sizeof(GINSTANCE));

	// Loop to open the GINSTANCE's.
	
    for (
        igi = 0, lpwszInstanceName = grwszInstanceNames; 
        igi < lpgt->cInstances; 
        igi++, lpwszInstanceName += (wcslen(lpwszInstanceName) + 1))
	{
		lpgi = &lpgt->rggiInstances[igi];

        // Open this gateway instance.

        dwStatus = OpenGInstance(lpwszInstanceName, lpgi, &iObjectName);
        if (dwStatus)
            goto cleanup;

        // If we haven't found the object name title index yet, and 
        // one was returned from OpenGInstance, use it.

        if (lpgt->iObjectName == -1)
        {
            lpgt->iObjectName = iObjectName;
        }
	}

    // Return the pointer to the GTYPE.

    *lppgt = lpgt;

cleanup:
	if (dwStatus && lpgt)
    {
        (void) DestroyGType(lpgt);
    }

	return dwStatus;
}



//$--DestroyGType---------------------------------------------------------------
//  Destroy a GTYPE structure (even a partially constructed one).
// -----------------------------------------------------------------------------
static DWORD DestroyGType(                  // RETURNS: Win32 error code
    IN OUT  LPGTYPE     lpgt)               // allocated GTYPE structure
{
	DWORD				dwStatus      		= ERROR_SUCCESS;
	DWORD				dwStatusTemp  		= ERROR_SUCCESS;
	ULONG				igi					= 0;

    DEBUGPRIVATE("DestroyGType()\n");

    if (lpgt)
    {
        // Loop to close each GINSTANCE.

        if (lpgt->rggiInstances)
        {
            for (igi = 0; igi < lpgt->cInstances; igi++)
            {
                dwStatusTemp = CloseGInstance(&lpgt->rggiInstances[igi]);
                if (dwStatusTemp)
                {
                    dwStatus = dwStatusTemp;
                }
            }
            FREE(lpgt->rggiInstances);
        }

        // Free the GTYPE.

        FREE(lpgt);
    }

    return dwStatus;
}



//$--OpenGInstance--------------------------------------------------------------
//  Sets up a GINSTANCE structure and maps its shared memory.
// -----------------------------------------------------------------------------
static DWORD OpenGInstance(                 // RETURNS: Win32 error code
    IN      LPWSTR      lpwszInstanceName,  // name of gateway instance
    IN OUT  LPGINSTANCE lpgi,               // instance struct to fill in
    OUT     LPLONG      lpiObjectName)      // obj title name index for instance
                                            // (-1 = it doesn't have valid data)
{
	DWORD				dwStatus      		= ERROR_SUCCESS;
	LONG                cchOutSize          = 0;
    PPERF_OBJECT_TYPE   lpPOT               = NULL;
	WCHAR				wszMappingName		[MAX_PATH] = {0};
	WCHAR				wszMutexName		[MAX_PATH] = {0};
    LONG                iObjectName         = -1;

    DEBUGPRIVATE("OpenGInstance()\n");

    // Initially assume the instance is not locked.

    lpgi->cLockReference = 0;

    // Add an allocated copy of the instance name to the GINSTANCE structure.

    lpgi->lpwszName = _wcsdup(lpwszInstanceName);
    if (lpgi->lpwszName == NULL)
    {
        dwStatus = ERROR_NOT_ENOUGH_MEMORY;
        EventLogMsg(
            GWPERF_OPEN_ERROR, 
            0, 
            1, dwStatus);
        goto cleanup;
    }

    // Create the name of the mutex.

	cchOutSize = wsprintfW(
		wszMutexName, 
		MON_MUTEX_NAME_TEMPLATE_W, 
		lpwszInstanceName);

    if ((cchOutSize + 1) * sizeof(CHAR) > sizeof(wszMutexName))
    {
        dwStatus = ERROR_BUFFER_OVERFLOW;
        EventLogMsg(
            GWPERF_OPEN_ERROR, 
            0, 
            1, dwStatus);
        goto cleanup;
    }

	(void) CharUpperW(wszMutexName);

    // Create the name of the shared memory mapping.

	cchOutSize = wsprintfW(
		wszMappingName, 
		MON_MAPPING_NAME_TEMPLATE_W, 
		lpwszInstanceName);

    if ((cchOutSize + 1) * sizeof(CHAR) > sizeof(wszMappingName))
    {
        dwStatus = ERROR_BUFFER_OVERFLOW;
        EventLogMsg(
            GWPERF_OPEN_ERROR, 
            0, 
            1, dwStatus);
        goto cleanup;
    }

	(void) CharUpperW(wszMappingName);

	// First try to open the mutex and get ownership.

	lpgi->hMutex = OpenMutexW(
	    MUTEX_ALL_ACCESS, 
	    FALSE, 
	    wszMutexName);
	if (lpgi->hMutex)
    {
        dwStatus = LockSharedMemory(lpgi);
        if (dwStatus)
            goto cleanup;
    }

    // If the mutex didn't exist then create it and get ownership.

    else
	{
        dwStatus = GetLastError();
        if (dwStatus != ERROR_FILE_NOT_FOUND)
        {
            EventLogMsg(
                GWPERF_OPEN_ERROR, 
                0, 
                1, dwStatus);
            goto cleanup;
        }

        lpgi->hMutex = CreateMutexW(
            psa, 
            TRUE, 
            wszMutexName);
        if (lpgi->hMutex == NULL)
        {
            dwStatus = GetLastError();
            EventLogMsg(
                GWPERF_OPEN_ERROR, 
                0, 
                1, dwStatus);
            goto cleanup;
        }
        lpgi->cLockReference++;
	}

    // First try to open the shared memory mapping.

	lpgi->hFileMapping = OpenFileMappingW(
	    FILE_MAP_WRITE, 
	    FALSE, 
	    wszMappingName);

    // If the shared memory mapping didn't exist then create it.

	if (lpgi->hFileMapping == NULL)
	{
		dwStatus = GetLastError();
        if (dwStatus != ERROR_FILE_NOT_FOUND)
        {
            EventLogMsg(
                GWPERF_OPEN_ERROR, 
                0, 
                1, dwStatus);
    		goto cleanup;
        }

    	lpgi->hFileMapping = CreateFileMappingW(
    		(HANDLE)0xFFFFFFFF, 			// create in paging file
    		psa, 							// no security
    		PAGE_READWRITE, 				// read/write access
    		0, 								// size (high)
    		sizeof(MONSHAREDMEMORY), 		// size(low)
    		wszMappingName);				// mapping object name

    	if (lpgi->hFileMapping == NULL)
    	{
    		dwStatus = GetLastError();
            EventLogMsg(
                GWPERF_OPEN_ERROR, 
                0, 
                1, dwStatus);
    		goto cleanup;
    	}
	}

	// Map a view of the shared memory file.

	lpgi->lpmsmMemory = MapViewOfFile(
		lpgi->hFileMapping, 
		FILE_MAP_WRITE, 
		0, 0, 0);
	if (lpgi->lpmsmMemory == NULL)
	{
        dwStatus = GetLastError();

        EventLogMsg(
            GWPERF_OPEN_ERROR, 
            0, 
            1, dwStatus);
        goto cleanup;
	}

    // If the signature isn't correct then we have a version mismatch.
    // (0 probably means it hasn't been fully created yet).

    if (lpgi->lpmsmMemory->dwSignature != MON_SHARED_MEMORY_SIGNATURE && 
        lpgi->lpmsmMemory->dwSignature != 0)
    {
        EventLogMsgW(
            GWPERF_VERSION_MISMATCH, 
            1, lpwszInstanceName, 
            0);
        dwStatus = ERROR_DLL_INIT_FAILED;
        goto cleanup;
    }

    // If there is no valid data in the shared memory section then try 
    // to read it from the registry where the gateway saved it the last 
    // time it was started.  If there was an error then the shared memory 
    // fDataIsValid flag is returned as FALSE.

    if (!lpgi->lpmsmMemory->fDataIsValid)
    {
        ReadSharedMemoryFromRegistry(lpgi);

        // Check the signature again because we just read it in.

        if (lpgi->lpmsmMemory->dwSignature != MON_SHARED_MEMORY_SIGNATURE && 
            lpgi->lpmsmMemory->dwSignature != 0)
        {
            EventLogMsgW(
                GWPERF_VERSION_MISMATCH, 
                1, lpwszInstanceName, 
                0);
            dwStatus = ERROR_DLL_INIT_FAILED;
            goto cleanup;
        }
    }

    // If there is valid data in the shared memory section then get the 
    // object name title index from it.

    if (lpgi->lpmsmMemory->fDataIsValid)
    {
        lpPOT = (PPERF_OBJECT_TYPE) (((LPBYTE)(lpgi->lpmsmMemory)) 
            + lpgi->lpmsmMemory->ibHeaderOffset);
    	iObjectName = lpPOT->ObjectNameTitleIndex;
    }

    // Unlock the mutex.

    dwStatus = UnlockSharedMemory(lpgi);
    if (dwStatus)
        goto cleanup;

    // Flag that the instance is open.

	lpgi->fOpen = TRUE;

    // Return the object name title index.

    *lpiObjectName = iObjectName;

cleanup:
    // If we had an error then close the GINSTANCE and return the error code.

    if (dwStatus)
    {
        (void) CloseGInstance(lpgi);
    }

    return dwStatus;
}



//$--CloseGInstance-------------------------------------------------------------
//  Closes a GINSTANCE structure, closes handles, unmaps shared memory, etc. 
//  (even a partially opened one).
// -----------------------------------------------------------------------------
static DWORD CloseGInstance(                // RETURNS: Win32 error code
    IN OUT  LPGINSTANCE lpgi)               // instance struct to fill in
{
	DWORD				dwStatus      		= ERROR_SUCCESS;
	DWORD				dwStatusTemp  		= ERROR_SUCCESS;
    BOOL                fItWorked           = TRUE;

    DEBUGPRIVATE("CloseGInstance()\n");

    // Free the allocated instance name.

    FREE(lpgi->lpwszName);

    // Release and close the shared memory mutex.

	if (lpgi->hMutex)
	{
        // Release the mutex lock.

        while (lpgi->cLockReference > 0)
        {
            dwStatusTemp = UnlockSharedMemory(lpgi);
            if (dwStatusTemp)
            {
                dwStatus = dwStatusTemp;
                break;
            }
        }

        // Close the handle to the mutex.

		fItWorked = CloseHandle(lpgi->hMutex);
		if (!fItWorked)
		{
            dwStatus = GetLastError();
            EventLogMsg(
                GWPERF_ERROR, 
                0, 
                1, dwStatus);
		}
		lpgi->hMutex = NULL;
	}

    // Unmap the view of the shared memory.

	if (lpgi->lpmsmMemory)
	{
		fItWorked = UnmapViewOfFile(lpgi->lpmsmMemory);
		if (!fItWorked)
		{
            dwStatus = GetLastError();
            EventLogMsg(
                GWPERF_ERROR, 
                0, 
                1, dwStatus);
		}
		lpgi->lpmsmMemory = NULL;
	}

    // Close the file mapping handle.

	if (lpgi->hFileMapping)
	{
		fItWorked = CloseHandle(lpgi->hFileMapping);
		if (!fItWorked)
		{
            dwStatus = GetLastError();
            EventLogMsg(
                GWPERF_ERROR, 
                0, 
                1, dwStatus);
		}
		lpgi->hFileMapping = NULL;
	}

    // Zero out the GINSTANCE structure (which will also clear the fOpen flag).

    ZeroMemory(lpgi, sizeof(*lpgi));

    return dwStatus;
}



//$--CountMultiStrings----------------------------------------------------------
//  Returns the number of null terminated strings in a group of word strings.
//  A group of word strings consists of zero or more null-terminated word 
//  strings followed by a null word.
// -----------------------------------------------------------------------------
static DWORD CountMultiStrings(             // RETURNS: Win32 error code
    IN  LPWSTR          grwsz,              // group of strings to count
    OUT LPULONG         pcwsz)              // number of strings found
{
    DWORD               dwStatus            = ERROR_SUCCESS;
	LPWSTR			    pwsz		        = NULL;

    DEBUGPRIVATE("CountMultiStrings()\n");

    *pcwsz = 0;
    for (pwsz = grwsz; *pwsz; pwsz += (wcslen(pwsz) + 1))
	{
        (*pcwsz)++;
    }

    return dwStatus;
}



//$--LockSharedMemory-----------------------------------------------------------
//  Locks the mutex associated with a shared memory block.
// -----------------------------------------------------------------------------
static DWORD LockSharedMemory(		        // RETURNS: Win32 error code
	IN  LPGINSTANCE     lpgi)		        // gateway instance to lock
{
    DWORD               dwStatus             = ERROR_SUCCESS;
    DWORD               dwWaitStatus         = 0;

#ifdef VERBOSE_DEBUG
    DEBUGPRIVATE("LockSharedMemory()\n");
#endif

    // Lock the mutex.

	dwWaitStatus = WaitForSingleObject(lpgi->hMutex, MON_MUTEX_TIMEOUT);
    switch (dwWaitStatus)
    {
        // Failed--log and return error.

        case WAIT_FAILED:
            dwStatus = GetLastError();
            EventLogMsg(
                GWPERF_ERROR, 
                0, 
                1, dwStatus);
            goto cleanup;

        // Timed out--log and return error.

        case WAIT_TIMEOUT:
            dwStatus = ERROR_DLL_INIT_FAILED;
            EventLogMsgW(
                GWPERF_MUTEX_TIMEOUT, 
                1, lpgi->lpwszName, 
                0);
            goto cleanup;

        // Success--increment the reference count.

        default:
            ++lpgi->cLockReference;
            break;
    }

cleanup:
    return dwStatus;
}



//$--UnlockSharedMemory---------------------------------------------------------
//  Unlocks the mutex associated with a shared memory block.
// -----------------------------------------------------------------------------
static DWORD UnlockSharedMemory(	        // RETURNS: Win32 error code
	IN  LPGINSTANCE     lpgi)			    // gateway instance to unlock
{
    DWORD               dwStatus            = ERROR_SUCCESS;
	BOOL 		        fItWorked 		    = FALSE;

#ifdef VERBOSE_DEBUG
    DEBUGPRIVATE("UnlockSharedMemory()\n");
#endif

    // Don't unlock more than we lock.

    if (lpgi->cLockReference > 0)
    {
        // Unlock the mutex.

    	fItWorked = ReleaseMutex(lpgi->hMutex);
    	if (!fItWorked)
        {
            dwStatus = GetLastError();
            EventLogMsg(
                GWPERF_ERROR, 
                0, 
                1, dwStatus);
            goto cleanup;
        }

        // Decrement the reference count.

        --lpgi->cLockReference;
    }

cleanup:
    return dwStatus;
}



//$--fOurDataRequested----------------------------------------------------------
//  Returns TRUE if the value request string is requesting our data.
// -----------------------------------------------------------------------------
static BOOL fOurDataRequested(			    // RETURNS: TRUE=yes, FALSE=no
    IN  LPGTYPE         lpgt,               // gateway type structure
    IN  LPWSTR          lpwszRequest)		// perfomance data request string
{
	BOOL                fReturn             = FALSE;
	LPWSTR		        lpwszOldPtr	        = NULL;
	LONG		        iObjectName	        = 0;

    DEBUGPRIVATE("fOurDataRequested()\n");

	// If they requested "Global", "Costly" or an empty string then 
	// they want our data.

    if (*lpwszRequest == 0 || 
    	!wcscmp(lpwszRequest, L"Global") || 
    	!wcscmp(lpwszRequest, L"Costly"))
	{
		fReturn = TRUE;
        goto cleanup;
	}

    // If they requested "Foreign" then they don't want our data.

	if (!wcscmp(lpwszRequest, L"Foreign"))
	{
		fReturn = FALSE;
        goto cleanup;
	}

    // Search the list for our number.

    fReturn = FALSE;
	while (lpwszRequest != lpwszOldPtr)
	{
		lpwszOldPtr = lpwszRequest;

		iObjectName = wcstol(lpwszRequest, &lpwszRequest, 10);

		if (iObjectName == lpgt->iObjectName && 
			lpwszRequest != lpwszOldPtr)
		{
			fReturn = TRUE;
			goto cleanup;
		}
	}

cleanup:
	return fReturn;
}



//$--ReadSharedMemoryFromRegistry-----------------------------------------------
//  Read the default shared memory data from the registry, where it was stored 
//  the last time the gateway started.    If there was an error then the shared 
//  memory fDataIsValid flag is returned as FALSE.
// -----------------------------------------------------------------------------
static VOID ReadSharedMemoryFromRegistry(	// RETURNS: nothing
	IN OUT  LPGINSTANCE lpgi)			    // gateway instance to unlock
{
    DWORD               dwStatus            = ERROR_SUCCESS;
	BOOL 		        fItWorked 		    = FALSE;
	CHAR		        szKeyName[MAX_PATH] = {0};
	HKEY		        hKey			    = NULL;
	DWORD		        cch				    = 0;
	DWORD		        dwType              = 0;
    DWORD               cbData              = 0;

    DEBUGPRIVATE("ReadSharedMemoryFromRegistry()\n");

    // Zero out the shared memory section first.

    ZeroMemory(lpgi->lpmsmMemory,  sizeof(*(lpgi->lpmsmMemory)));

    // Create the registry key name from the gateway instance name.

	cch = sprintf(
		szKeyName, 
		"SYSTEM\\CurrentControlSet\\Services\\%S\\Parameters", 
		lpgi->lpwszName);
	ASSERTERROR(
		(cch * sizeof(*szKeyName)) < sizeof(szKeyName), 
		"wsprintf overflow: szKeyName");

	// Open the registry key.

	dwStatus = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE, 
		szKeyName, 
		0L, 
		KEY_READ, 
		&hKey);
	if (dwStatus != ERROR_SUCCESS)
    {
        EventLogMsg(
            GWPERF_OPEN_DEFAULT_COUNTERS, 
            1, szKeyName, 
            1, dwStatus);
		goto cleanup;
    }

    // Read the value into the shared memory section.

    cbData = sizeof(*(lpgi->lpmsmMemory));

    dwStatus = RegQueryValueEx(
        hKey, 
        "ObjectDefaultPerformanceData", 
        NULL, 
        &dwType, 
        (LPBYTE) lpgi->lpmsmMemory, 
        &cbData);
    
    // If it is not found then log a message telling the user to run the 
    // gateway once first.

    if (dwStatus == ERROR_FILE_NOT_FOUND)
    {
        EventLogMsgW(
            GWPERF_NO_DEFAULT_COUNTERS, 
            1, lpgi->lpwszName, 
            0);
		goto cleanup;
    }
    
    if (dwStatus != ERROR_SUCCESS)
    {
        EventLogMsg(
            GWPERF_READ_DEFAULT_COUNTERS, 
            1, szKeyName, 
            1, dwStatus);
		goto cleanup;
    }
    
    if (dwType != REG_BINARY)
    {
        EventLogMsg(
            GWPERF_DEFAULT_COUNTERS_WRONG_TYPE, 
            1, szKeyName, 
            0);
        dwStatus = ERROR_FILE_NOT_FOUND;
		goto cleanup;
    }

cleanup:
	// Close the registry key (if it's open).

	if (hKey)
	{
		dwStatus = RegCloseKey(hKey);
        if (dwStatus != ERROR_SUCCESS)
        {
            EventLogMsg(
                GWPERF_CLOSE_DEFAULT_COUNTERS, 
                1, szKeyName, 
                1, dwStatus);

            // We can ignore an error here.

            dwStatus = ERROR_SUCCESS;
        }
	}

    // If it didn't work, then clear out the shared memory, mark it 
    // as having no valid data and continue on.

    if (dwStatus)
    {
        ZeroMemory(lpgi->lpmsmMemory,  sizeof(*(lpgi->lpmsmMemory)));

        lpgi->lpmsmMemory->fDataIsValid = FALSE;
    }
}
