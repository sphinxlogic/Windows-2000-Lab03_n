// --monitor.c------------------------------------------------------------------
//
//  This file implements the monitored object side of the EDK performance 
//  monitoring component.
//
//  This component uses the stats.lib to generate a suite of statistics.  The 
//  statistics are periodically copied to a memory area shared with the other 
//  side of the performance monitoring component: a performance DLL which is 
//  called by the NT Performance Monitor.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "monshare.h"
#include "monctx.h"
#include "monitor.chk"

//
// Internal Function Declarations
//

static HRESULT HrAllocateContext(
	OUT LPMONCONTEXT *lppmcx);

static HRESULT HrGetCurrentTime(
	OUT __int64 * lpdwlTime);

static HRESULT HrReadObjectClass(
	IN LPMONCONTEXT lpmcx);

static HRESULT HrReadRegistryInfo(
	IN LPMONCONTEXT lpmcx);

static HRESULT HrReadRegistryDWORD(
	IN HKEY hKey,
	IN LPSTR lpszValueName,
	OUT LPDWORD lpdwValue);

static HRESULT HrCreateSharedMemory(
	IN LPMONCONTEXT lpmcx);

static HRESULT HrFillInSharedMemory(
	IN LPMONCONTEXT lpmcx, 
	IN DWORD ccdCounters,
	IN LPCOUNTERDEF lpcdCounters);

static HRESULT HrBuildStructures(
	IN LPMONCONTEXT lpmcx,
	IN DWORD ccdCounters,
	IN LPCOUNTERDEF lpcdCounters);

static HRESULT HrMonFindFolder(
	IN  LPMONFOLDER   lpmfFolderList,
	IN  LPMAPIFOLDER  lpFolder,
	OUT LPMONFOLDER * lppmfFolder);

static HRESULT HrStartUpdateThread(
	IN LPMONCONTEXT lpmcx);

static DWORD WINAPI UpdateThread(
	IN LPVOID lpThreadParameter);

static HRESULT HrFreeEverything(
	IN LPMONCONTEXT *lppmcx);

static HRESULT HrFreeCounterList(
	IN LPMONCOUNTER *lppmcCounterList);

static HRESULT HrFreeFolderList(
	IN LPMONFOLDER *lppmfFolderList);

static HRESULT HrAddToCounters(
	IN LPMONCONTEXT lpmcx,
	IN LPMONCOUNTER lpmcList,
	IN LONG dwAmount);

static HRESULT HrSetCounters(
	IN LPMONCOUNTER lpmcList,
	IN DWORD dwAmount);

static HRESULT HrComputeCounterType(
	IN  COUNTERTYPE ctStatistic,
	IN  PERIODTYPE perPeriod,
	IN  DWORD dwUserCounterType,
	OUT DWORD *lpdwCounterType);

static HRESULT HrAlignPointer(
	IN     DWORD cbAlignment,
	IN OUT LPVOID * lppvPointer);

static ULONG STDAPICALLTYPE FolderNotification(
	IN LPVOID lpvContext,
	IN DWORD cNotification,
	IN LPNOTIFICATION lpNotifications);

static HRESULT HrWakeUpdateThread(
	IN LPMONCONTEXT lpmcx);

static HRESULT HrRegisterNotification(
	IN LPMONCONTEXT lpmcx);

static HRESULT HrLinkCounterIntoList(
	IN LPMONCONTEXT lpmcx,
	IN LPMONFOLDER lpmf,
	IN LPMONCOUNTER lpmc,
	IN COUNTERTYPE ctCounterType);

static HRESULT HrVerifyLinkage(
	IN LPMONCONTEXT lpmcx);

static HRESULT HrSaveSharedMemoryInRegistry(
    IN LPMONCONTEXT lpmcx);

//
// Local Variable Declarations
//

static LPMONCONTEXT lpmcxContext = NULL; // place to save allocated context

// Security descriptor to allow all access -- only need to initialize once!!!

static BOOL fSecurityDescriptorInitialized = FALSE;

static SECURITY_ATTRIBUTES sa;
static char rgbForSecurityDescriptor[SECURITY_DESCRIPTOR_MIN_LENGTH];

static SECURITY_ATTRIBUTES * psa = &sa;
static SECURITY_DESCRIPTOR * psd 
                    = (SECURITY_DESCRIPTOR *)rgbForSecurityDescriptor;

//
// Monitor API Routines
//

//$--HrMonInit--------------------------------------------------------------
//  Begins performance monitoring of the current monitored object.
//
//  If lpszObjectClass != NULL, then use lpszObjectClass as the class of the  
//  monitored object.
//  If lpszObjectClass == NULL, then read the object class from the 
//  Parameters\ObjectClass value under the object's registry key, or if 
//  it's not present, assume that the object class is the same as the object 
//  name.
// -----------------------------------------------------------------------------
HRESULT HrMonInit( 					// RETURNS: HRESULT
	IN DWORD dwFlags,					// for future use--must be zero
	IN LPSTR lpszObjectClass,			// class of monitored object, or NULL
	IN LPSTR lpszObjectName, 			// gateway instance name
	IN DWORD dwObjectTitleOffset,		// index number of object name in 
										// the registry database (offset from
										// First Counter)
	IN DWORD dwObjectDetailLevel,		// complexity of object (see winperf.h)
	IN LONG dwDefaultCounter,			// zero-based number of default counter 
										// for this object
	IN DWORD ccdNumberOfCounters,		// number of counter structures
										// being passed in
	IN LPCOUNTERDEF lpcdCounters)		// pointer to array of counter
										// structures
{
    // This routine creates a "context" structure in allocated memory that 
    // holds all the information needed for performance monitoring.  When fully 
    // allocated, this context contains open handles to various objects, and 
    // pointers to other allocated memory structures.  HrMonInit() calls 
    // several other routines, each of which allocates some of the handles 
    // and structures attached to the context.
    //
    // If one of these routines fails for any reason, it does NOT clean up what 
    // it has created in the context.  Instead, it simply returns an error, and 
    // then HrMonInit calls a "catch-all" cleanup routine called 
    // HrFreeEverything().  HrFreeEverything frees/closes anything attached 
    // to the context and then frees the context itself.  HrFreeEverything() 
    // is also called by MonitorShutdown() to end performance monitoring.

	HRESULT			hr 				= NOERROR;

	DEBUGPUBLIC("HrMonInit()\n");

	// Check the parameters.

	hr = CHK_HrMonInit(
		dwFlags, 
		lpszObjectClass, 
		lpszObjectName, 
		dwObjectTitleOffset, 
		dwObjectDetailLevel, 
		dwDefaultCounter, 
		ccdNumberOfCounters, 
		lpcdCounters);
	if (FAILED(hr))
		RETURN(hr);

    // Set up a security descriptor with a NULL DACL, to allow all
    // access to an object.  This is used if we need to create the
    // mutex and shared memory section.

    if (!fSecurityDescriptorInitialized)
    {
        if (!InitializeSecurityDescriptor(psd, SECURITY_DESCRIPTOR_REVISION))
        {
		    hr = HR_LOG(E_FAIL);
		    goto cleanup_no_free;
        }

        if (!SetSecurityDescriptorDacl(psd, TRUE, (PACL) NULL, FALSE))
        {
		    hr = HR_LOG(E_FAIL);
		    goto cleanup_no_free;
        }

        psa->nLength = sizeof(*psa);
        psa->lpSecurityDescriptor = psd;
        psa->bInheritHandle = TRUE;

        fSecurityDescriptorInitialized = TRUE;
    }

    // Make sure this hasn't already been called before.

	if (lpmcxContext != NULL)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup_no_free;
	}

	// Allocate and zero out performance monitoring context.

	hr = HrAllocateContext(&lpmcxContext);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// Store various parameters in the context.

	lpmcxContext->iObjectTitleOffset = dwObjectTitleOffset;
	lpmcxContext->dwObjectDetailLevel = dwObjectDetailLevel;
	lpmcxContext->dwDefaultCounter = dwDefaultCounter;

	// Get the current system time and put it in the context.

	hr = HrGetCurrentTime(&lpmcxContext->dwlCurrentTime);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// Add allocated copies of the gateway type name and instance name to 
	// the performance monitoring context.  If they passed NULL for the 
    // gateway type then read it from the Parameters\ObjectClass value 
    // under the gateway's service entry in the registry.

	lpmcxContext->lpszObjectName = _strdup(lpszObjectName);
	if (lpmcxContext->lpszObjectName == NULL)
	{
		hr = HR_LOG(E_OUTOFMEMORY);
		goto cleanup;
	}

    if (lpszObjectClass)
    {
    	lpmcxContext->lpszObjectClass = _strdup(lpszObjectClass);
    	if (lpmcxContext->lpszObjectClass == NULL)
    	{
    		hr = HR_LOG(E_OUTOFMEMORY);
    		goto cleanup;
    	}
    }
    else
    {
        hr = HrReadObjectClass(lpmcxContext);
        if (FAILED(hr))
        {
            goto cleanup;
        }
    }

    // Verify that there is a back link from the gateway type to the 
    // gateway name so the DLL can link to our shared memory section.

    hr = HrVerifyLinkage(lpmcxContext);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// Read the Counter and Help values from the registry.

	hr = HrReadRegistryInfo(lpmcxContext);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// Create the shared memory section and mutex.  This leaves us as the 
	// owner of the mutex and we must release it before we return.

	hr = HrCreateSharedMemory(lpmcxContext);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// Fill in the shared memory section with the structure that will be 
	// passed to the DLL, and from there to the Performance Monitor.

	hr = HrFillInSharedMemory(
		lpmcxContext, ccdNumberOfCounters, lpcdCounters);
	if (FAILED(hr))
	{
		goto cleanup;
	}

    // Save a copy of the shared memory block to the registry so that 
    // GWPERF.DLL will be able to generate a blank set of counters when 
    // the gateway isn't running.

    hr = HrSaveSharedMemoryInRegistry(lpmcxContext);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// Set up structures representing folders, and linked lists of counters 
	// hanging off the performance monitoring context.

	hr = HrBuildStructures(
		lpmcxContext, ccdNumberOfCounters, lpcdCounters);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// Register the notification routines on all folders that need them.

	hr = HrRegisterNotification(lpmcxContext);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	// If there are any jumping sliding windows or folders, then start 
	// the thread that updates them.

	if (lpmcxContext->lpmcJSWCounterList || lpmcxContext->lpmfFolderList)
	{
		hr = HrStartUpdateThread(lpmcxContext);
		if (FAILED(hr))
		{
			goto cleanup;
		}
	}

	// Set flag that the shared memory data structure is now valid.

	lpmcxContext->lpmsmSharedMemory->fDataIsValid = TRUE;

	// Release the mutex (it was "locked" when the mutex was created).

	hr = HrMonUnlockCounters();
	if (FAILED(hr))
	{
		goto cleanup;
	}

cleanup:
	if (FAILED(hr))
	{
        HRESULT hrT = NOERROR;

		hrT = HrFreeEverything(&lpmcxContext);
        if (FAILED(hrT))
            HR_LOG(hrT);
	}

cleanup_no_free:
	RETURN(hr);
}


 
//$--HrMonUninit----------------------------------------------------------
//  Ends performance monitoring of the current gateway.
// -----------------------------------------------------------------------------
HRESULT HrMonUninit(void)		    // RETURNS: HRESULT
{
	HRESULT			hr 				= NOERROR;

	DEBUGPUBLIC("HrMonUninit()\n");

    // Make sure there's a context.

    if (lpmcxContext == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	ASSERT_WRITE_PTR(lpmcxContext, sizeof(*lpmcxContext), 
		"lpmcxContext: bad write pointer");

	// Shut down, and free the context and all memory attached to it.

	hr = HrFreeEverything(&lpmcxContext);
    if (FAILED(hr))
        goto cleanup;

cleanup:
    RETURN(hr);
}



//$--HrMonCollectNDRStats----------------------------------------------------
//  Call this after processing an NDR.
// -----------------------------------------------------------------------------
HRESULT HrMonCollectNDRStats(		// RETURNS: HRESULT
	IN DWORD cNDRs,						// number of NDR's processed
	IN DIRECTIONTYPE dir)				// direction of NDR's
{
	HRESULT			hr 				= NOERROR;
	HRESULT			hrT				= NOERROR;

	DEBUGPUBLIC("HrMonCollectNDRStats()\n");

	// Check the parameters.

	hr = CHK_HrMonCollectNDRStats(cNDRs, dir);
	if (FAILED(hr))
		RETURN(hr);

    // Make sure there's a context.

    if (lpmcxContext == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	ASSERT_WRITE_PTR(lpmcxContext, sizeof(*lpmcxContext), 
		"lpmcxContext: bad write pointer");

    // Lock the shared memory against modification.

	hr = HrMonLockCounters();
    if (FAILED(hr))
        goto cleanup;

    // Get current time for JSW's.

	hr = HrGetCurrentTime(&lpmcxContext->dwlCurrentTime);
    if (FAILED(hr))
        goto cleanup;

    // Update the counters.

	switch (dir)
	{
		case DIRECTIONTYPE_IN:
			hr = HrAddToCounters(lpmcxContext, lpmcxContext->lpmcNDRsIn, cNDRs);
            if (FAILED(hr))
                goto cleanup;
			break;

		case DIRECTIONTYPE_OUT:
			hr = HrAddToCounters(lpmcxContext, lpmcxContext->lpmcNDRsOut, cNDRs);
            if (FAILED(hr))
                goto cleanup;
			break;
	}

cleanup:
    // Unlock the shared memory.

    if (lpmcxContext)
    {
    	hrT = HrMonUnlockCounters();
        if (FAILED(hrT))
        {
            hr = hrT;
        }
    }

    RETURN(hr);
}



//$--HrMonCollectMessageXferStats-------------------------------------
//  Call this after transferring a message.
// -----------------------------------------------------------------------------
HRESULT HrMonCollectMessageXferStats( // RETURNS: HRESULT
	IN DWORD cMessages, 				// number of messages transferred
	IN DWORD cBytes, 					// number of bytes transferred
	IN DIRECTIONTYPE dir)				// direction of message transfer
{
	HRESULT		hr		= NOERROR;
	HRESULT		hrT		= NOERROR;

	DEBUGPUBLIC("HrMonCollectMessageXferStats()\n");

	// Check the parameters.

	hr = CHK_HrMonCollectMessageXferStats(cMessages, cBytes, dir);
	if (FAILED(hr))
		RETURN(hr);

    // Make sure there's a context.

    if (lpmcxContext == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	ASSERT_WRITE_PTR(lpmcxContext, sizeof(*lpmcxContext), 
		"lpmcxContext: bad write pointer");

	hr = HrMonLockCounters();
    if (FAILED(hr))
        goto cleanup;

	hr = HrGetCurrentTime(&lpmcxContext->dwlCurrentTime);
    if (FAILED(hr))
        goto cleanup;

	switch (dir)
	{
		case DIRECTIONTYPE_IN:

			hr = HrAddToCounters(
				lpmcxContext, 
				lpmcxContext->lpmcMessagesTransferredIn, 
				cMessages);
            if (FAILED(hr))
                goto cleanup;

			hr = HrAddToCounters(
				lpmcxContext, 
				lpmcxContext->lpmcBytesTransferredIn, 
				cBytes);
            if (FAILED(hr))
                goto cleanup;
			break;

		case DIRECTIONTYPE_OUT:

			hr = HrAddToCounters(
				lpmcxContext, 
				lpmcxContext->lpmcMessagesTransferredOut, 
				cMessages);
            if (FAILED(hr))
                goto cleanup;

			hr = HrAddToCounters(
				lpmcxContext, 
				lpmcxContext->lpmcBytesTransferredOut, 
				cBytes);
            if (FAILED(hr))
                goto cleanup;
			break;
	}

cleanup:
    if (lpmcxContext)
    {
    	hrT = HrMonUnlockCounters();
        if (FAILED(hrT))
        {
            hr = hrT;
        }
    }

    RETURN(hr);
}



//$--HrMonCollectAssociationStats--------------------------------------------
//  Call this after making or breaking an association, or to set a new total 
//  number of associations.
// -----------------------------------------------------------------------------
HRESULT HrMonCollectAssociationStats( // RETURNS: HRESULT
	IN BOOL fSetNewTotal,				// if TRUE, iAssociations becomes 
										// the new total of associations.
										// if FALSE, iAssociations is added 
										// to the number of associations.

	IN LONG cAssociations)				// number of associations to add to
										// total (can be negative), or new 
										// total if fSetNewTotal == TRUE
{
	HRESULT		hr		= NOERROR;
	HRESULT		hrT		= NOERROR;

	DEBUGPUBLIC("HrMonCollectAssociationStats()\n");

	// Check the parameters.

	hr = CHK_HrMonCollectAssociationStats(fSetNewTotal, cAssociations);
	if (FAILED(hr))
		RETURN(hr);

    // Make sure there's a context.

    if (lpmcxContext == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	ASSERT_WRITE_PTR(lpmcxContext, sizeof(*lpmcxContext), 
		"lpmcxContext: bad write pointer");

	hr = HrMonLockCounters();
    if (FAILED(hr))
        goto cleanup;

	hr = HrGetCurrentTime(&lpmcxContext->dwlCurrentTime);
    if (FAILED(hr))
        goto cleanup;

	if (fSetNewTotal)
	{
		// Set all counters to the given value.

		ASSERTERROR(cAssociations >= 0, 
			"cAssociations < 0 on set associations");

		hr = HrSetCounters(
			lpmcxContext->lpmcAssociations, 
			cAssociations);
        if (FAILED(hr))
            goto cleanup;
	}
	else
	{
		// Add given value to counters (value can be negative).

		hr = HrAddToCounters(
			lpmcxContext, 
			lpmcxContext->lpmcAssociations, 
			cAssociations);
        if (FAILED(hr))
            goto cleanup;
	}

cleanup:
    if (lpmcxContext)
    {
    	hrT = HrMonUnlockCounters();
        if (FAILED(hrT))
        {
            hr = hrT;
        }
    }

    RETURN(hr);
}



//$--HrMonLockCounters------------------------------------------------------
//  Locks the block of counters against access by other threads/processes.
//  This should be called before accessing a user defined counter.
// -----------------------------------------------------------------------------
HRESULT HrMonLockCounters(void)		// RETURNS: HRESULT
{
    HRESULT         hr              = NOERROR;
	DWORD			dwReturnValue	= 0;

	DEBUGPUBLIC("HrMonLockCounters()\n");

    // Make sure there's a context.

    if (lpmcxContext == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	ASSERT_WRITE_PTR(lpmcxContext, sizeof(*lpmcxContext), 
		"lpmcxContext: bad write pointer");
	ASSERTERROR(lpmcxContext->hSharedMemoryMutex != NULL, 
		"lpmcxContext->hSharedMemoryMutex == NULL");

	dwReturnValue = WaitForSingleObject(
		lpmcxContext->hSharedMemoryMutex, 
		MON_MUTEX_TIMEOUT);
	if (dwReturnValue == WAIT_FAILED || dwReturnValue == WAIT_TIMEOUT)
	{
        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	ASSERTERROR(
		dwReturnValue == WAIT_FAILED || 
		dwReturnValue == WAIT_ABANDONED || 
		dwReturnValue == WAIT_OBJECT_0 || 
		dwReturnValue == WAIT_TIMEOUT, 
		"dwReturnValue: illegal value");

	ASSERTERROR(dwReturnValue != WAIT_TIMEOUT, 
		"lpmcxContext->hSharedMemoryMutex: dwReturnValue == WAIT_TIMEOUT");

cleanup:
    RETURN(hr);
}



//$--HrMonUnlockCounters----------------------------------------------------
//  Unlocks the block of counters to allow access by other threads/processes.
//  This should be called after accessing a user defined counter.
// -----------------------------------------------------------------------------
HRESULT HrMonUnlockCounters(void)	// RETURNS: HRESULT
{
    HRESULT         hr              = NOERROR;
	BOOL 			fItWorked 		= FALSE;

	DEBUGPUBLIC("HrMonUnlockCounters()\n");

    // Make sure there's a context.

    if (lpmcxContext == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	ASSERT_WRITE_PTR(lpmcxContext, sizeof(*lpmcxContext), 
		"lpmcxContext: bad write pointer");
	ASSERTERROR(lpmcxContext->hSharedMemoryMutex != NULL, 
		"lpmcxContext->hSharedMemoryMutex == NULL");

	fItWorked = ReleaseMutex(lpmcxContext->hSharedMemoryMutex);
	if (!fItWorked)
	{
        DWORD dwStatus = GetLastError();

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

cleanup:
    RETURN(hr);
}



//
// Internal Helper Functions
//



//$--HrAllocateContext----------------------------------------------------------
//  Helper function that allocates a new performance monitoring context and 
//  zeros out its components.
// -----------------------------------------------------------------------------
static HRESULT HrAllocateContext(	    // RETURNS: HRESULT
	OUT LPMONCONTEXT *lppmcx)			// pointer to address variable for
										// performance monitor context ptr
{
	LPMONCONTEXT	lpmcxNew 		= NULL;
	HRESULT			hr 				= NOERROR;

	DEBUGPRIVATE("HrAllocateContext()\n");

	// Check the parameters.

	hr = CHK_HrAllocateContext(lppmcx);
	if (FAILED(hr))
		RETURN(hr);

	lpmcxNew = malloc(sizeof(*lpmcxNew));
	if (lpmcxNew == NULL)
	{
		hr = HR_LOG(E_OUTOFMEMORY);
		goto cleanup;
	}
	ZeroMemory(lpmcxNew, sizeof(*lpmcxNew));
	*lppmcx = lpmcxNew;

cleanup:
	RETURN(hr);
}



//$--HrGetCurrentTime-----------------------------------------------------------
//  Helper function that returns the current system time in 8-byte format.
// -----------------------------------------------------------------------------
static HRESULT HrGetCurrentTime(		// RETURNS: HRESULT
	OUT __int64 * lpdwlTime)			// current time
{
	HRESULT			hr 				= NOERROR;
	SYSTEMTIME		st				= {0};
	__int64			dwlTime			= 0;
	BOOL			fItWorked		= TRUE;

	DEBUGPRIVATE("HrGetCurrentTime()\n");

	// Check the parameters.

	hr = CHK_HrGetCurrentTime(lpdwlTime);
	if (FAILED(hr))
		RETURN(hr);

	GetSystemTime(&st);
	fItWorked = SystemTimeToFileTime(&st, &TO_FILETIME(dwlTime));
	if (!fItWorked)
	{
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

	*lpdwlTime = dwlTime;

cleanup:
    RETURN(hr);
}



//$--HrReadRegistryInfo---------------------------------------------------------
//  Helper function that reads the First Counter and First Help values from the 
//  SYSTEM\CurrentControlSet\Services\<lpszObjectClass>\Performance key.
//  Note that the context must already have lpszObjectClass defined.
// -----------------------------------------------------------------------------
static HRESULT HrReadRegistryInfo(	    // RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx)				// pointer to perf mon context
{
	HRESULT		hr			            = NOERROR;
	DWORD		dwStatus		        = 0;
	TCHAR		szKeyName[MAX_PATH]     = {0};
	HKEY		hKey			        = NULL;
	DWORD		cch				        = 0;

	DEBUGPRIVATE("HrReadRegistryInfo()\n");

	// Check the parameters.

	hr = CHK_HrReadRegistryInfo(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

	ASSERT_STRING_PTR(lpmcx->lpszObjectClass, 
		"lpmcx->lpszObjectClass: bad string pointer");

	// Create the registry key name from the gateway type.

	cch = wsprintf(
		szKeyName, 
		TEXT("SYSTEM\\CurrentControlSet\\Services\\%s\\Performance"), 
		lpmcx->lpszObjectClass);
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
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Read the values: First Counter, First help, Last Counter, Last Help.

	hr = HrReadRegistryDWORD(hKey, "First Counter", 
		&lpmcx->dwFirstCounter);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	hr = HrReadRegistryDWORD(hKey, "First Help", 
		&lpmcx->dwFirstHelp);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	hr = HrReadRegistryDWORD(hKey, "Last Counter", 
		&lpmcx->dwLastCounter);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	hr = HrReadRegistryDWORD(hKey, "Last Help", 
		&lpmcx->dwLastHelp);
	if (FAILED(hr))
	{
		goto cleanup;
	}

cleanup:

	// Close the registry key (if it's open).

	if (hKey)
	{
		dwStatus = RegCloseKey(hKey);
		if (dwStatus != ERROR_SUCCESS)
		{
            hr = HR_LOG(E_FAIL);
		}
	}

	RETURN (hr);
}



//$--HrReadObjectClass----------------------------------------------------------
//  Helper function that reads the gateway type out of the registry.
// -----------------------------------------------------------------------------
static HRESULT HrReadObjectClass(       // RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx)              // pointer to perf mon context
{
	HRESULT		hr				        = NOERROR;
    DWORD       dwStatus                = ERROR_SUCCESS;
    BOOL        fValueNotFound          = FALSE;
	TCHAR		szKeyName[MAX_PATH]     = {0};
	HKEY		hKey			        = NULL;
	DWORD		cch				        = 0;
    DWORD       dwType                  = 0;
    TCHAR       szObjectClass[MAX_PATH] = {0};
    DWORD       cbObjectClass           = sizeof(szObjectClass);

	DEBUGPRIVATE("HrReadObjectClass()\n");

	// Check the parameters.

	hr = CHK_HrReadObjectClass(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

	// Create the registry key name from the gateway name.

	cch = wsprintf(
		szKeyName, 
		TEXT("SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters"), 
		lpmcx->lpszObjectName);
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
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

    // Read the value.

    dwStatus = RegQueryValueEx(
        hKey, 
        TEXT("ObjectClass"), 
        NULL, 
        &dwType, 
        szObjectClass, 
        &cbObjectClass);
	if (dwStatus != ERROR_SUCCESS || dwType != REG_SZ)
    {
        if (dwStatus == ERROR_FILE_NOT_FOUND)
            fValueNotFound = TRUE;
        else
            hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

    // Add it to the context.

    lpmcx->lpszObjectClass = _strdup(szObjectClass);
    if (lpmcx->lpszObjectClass == NULL)
    {
        hr = HR_LOG(E_OUTOFMEMORY);
		goto cleanup;
    }

cleanup:
    // If we couldn't read it then use the gateway name as the type.

    if (fValueNotFound)
    {
        lpmcx->lpszObjectClass = _strdup(lpmcx->lpszObjectClass);
        if (lpmcx->lpszObjectClass == NULL)
    		hr = HR_LOG(E_FAIL);
    }

	// Close the registry key (if it's open).

	if (hKey)
	{
		dwStatus = RegCloseKey(hKey);
        if (dwStatus != ERROR_SUCCESS)
            hr = HR_LOG(E_FAIL);
	}

    RETURN(hr);
}



//$--HrReadRegistryDWORD--------------------------------------------------------
//  Helper function that reads a DWORD value from the registry and makes sure
//  everything is as it should be.
// -----------------------------------------------------------------------------
static HRESULT HrReadRegistryDWORD(	    // RETURNS: HRESULT
	IN HKEY hKey,						// open key handle
	IN LPSTR lpszValueName,			// name of value to get
	OUT LPDWORD lpdwValue)				// address of DWORD to return value
{
	HRESULT		hr				= NOERROR;
	DWORD		dwStatus		= ERROR_SUCCESS;
	DWORD		dwValueType		= 0;
	DWORD		dwValueSize		= sizeof(*lpdwValue);

	DEBUGPRIVATE("HrReadRegistryDWORD()\n");

	// Check the parameters.

	hr = CHK_HrReadRegistryDWORD(hKey, lpszValueName, lpdwValue);
	if (FAILED(hr))
		RETURN(hr);

	dwStatus = RegQueryValueEx(
		hKey, 
		lpszValueName, 
		0L, 
		&dwValueType, 
		(LPBYTE)lpdwValue, 
		&dwValueSize);
	if (dwStatus != ERROR_SUCCESS)
	{
		hr = HR_LOG(E_FAIL);
	}
	else if (dwValueType != REG_DWORD)
	{
		hr = HR_LOG(E_FAIL);
	}

	RETURN(hr);
}



//$--HrCreateSharedMemory-------------------------------------------------------
//  Helper function that creates a shared memory section and a mutex.
//  NOTE: On successful return, the mutex will be owned by the current thread
//  and must be released.
// -----------------------------------------------------------------------------
static HRESULT HrCreateSharedMemory(	// RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx)				// pointer to performance monitoring
										// context
{
	HRESULT		hr				            = NOERROR;
	CHAR		szMappingName[MAX_PATH]     = {0};
	CHAR		szMutexName[MAX_PATH]       = {0};
	BOOL		fItWorked		            = FALSE;
	DWORD		cch				            = 0;

	DEBUGPRIVATE("HrCreateSharedMemory()\n");

	// Check the parameters.

	hr = CHK_HrCreateSharedMemory(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

	ASSERTERROR(lpmcx->cbSharedMemorySize == 0, 
		"lpmcx->cbSharedMemorySize != 0");
	ASSERTERROR(lpmcx->hSharedMemoryMapping == NULL, 
		"lpmcx->hSharedMemoryMapping != NULL");
	ASSERTERROR(lpmcx->lpmsmSharedMemory == NULL, 
		"lpmcx->lpmsmSharedMemory != NULL");
	ASSERTERROR(lpmcx->hSharedMemoryMutex == NULL, 
		"lpmcx->hSharedMemoryMutex != NULL");

	// Create the name of the mutex that controls access to the shared memory.

	cch = wsprintf(
		szMutexName, 
		MON_MUTEX_NAME_TEMPLATE, 
		lpmcx->lpszObjectName);
	ASSERTERROR(
		(cch * sizeof(*szMutexName)) < sizeof(szMutexName), 
		"wsprintf overflow: szMutexName");
	(void) CharUpper(szMutexName);

	MODULE_STATUS1("mutex name = [%s]", szMutexName);

	// First try to open the mutex and get ownership.

	lpmcx->hSharedMemoryMutex = OpenMutex(
        MUTEX_ALL_ACCESS, 
        FALSE, 
        szMutexName);
    if (lpmcx->hSharedMemoryMutex)
    {
        hr = HrMonLockCounters();
        if (FAILED(hr))
            goto cleanup;
    }

    // If the mutex didn't exist then create it and get ownership.

    else
    {
        if (GetLastError() != ERROR_FILE_NOT_FOUND)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    	lpmcx->hSharedMemoryMutex = CreateMutex(
    		psa,
    		TRUE,
    		szMutexName);
    	if (lpmcx->hSharedMemoryMutex == NULL)
    	{
    		hr = HR_LOG(E_FAIL);
    		goto cleanup;
    	}
    }

	// Set the shared memory size.

	lpmcx->cbSharedMemorySize = sizeof(MONSHAREDMEMORY);

	// Create name of shared memory file mapping object.

	cch = wsprintf(
		szMappingName, 
		MON_MAPPING_NAME_TEMPLATE, 
		lpmcx->lpszObjectName);
	ASSERTERROR(
		(cch * sizeof(*szMappingName)) < sizeof(szMappingName), 
		"wsprintf overflow: szMappingName");
	(void) CharUpper(szMappingName);

	MODULE_STATUS1("mapping name = [%s]", szMappingName);

    // First try to open the shared memory file mapping object.

	lpmcx->hSharedMemoryMapping = OpenFileMapping(
        FILE_MAP_ALL_ACCESS, 
        FALSE, 
        szMappingName);

	// If the file mapping object didn't exist then create it.

    if (lpmcx->hSharedMemoryMapping == NULL)
    {
        if (GetLastError() != ERROR_FILE_NOT_FOUND)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    	lpmcx->hSharedMemoryMapping = CreateFileMapping(
    		(HANDLE)0xFFFFFFFF, 			// create in paging file
    		psa, 							// no security
    		PAGE_READWRITE, 				// read/write access
    		0, 								// size (high)
    		lpmcx->cbSharedMemorySize, 		// size(low)
    		szMappingName);					// mapping object name

    	if (lpmcx->hSharedMemoryMapping == NULL)
    	{
    		hr = HR_LOG(E_FAIL);
    		goto cleanup;
    	}
    }

	// Map a view of the file mapping object.

	lpmcx->lpmsmSharedMemory = MapViewOfFile(
		lpmcx->hSharedMemoryMapping, 
		FILE_MAP_ALL_ACCESS, 
		0, 
		0, 
		lpmcx->cbSharedMemorySize);

	if (lpmcx->lpmsmSharedMemory == NULL)
	{
		hr = HR_LOG(E_OUTOFMEMORY);
		goto cleanup;
	}
    ZeroMemory(lpmcx->lpmsmSharedMemory, lpmcx->cbSharedMemorySize);

	// Set the flag that the shared memory is not valid yet.

	lpmcx->lpmsmSharedMemory->fDataIsValid = FALSE;

    // Set the signature value.

    lpmcx->lpmsmSharedMemory->dwSignature = MON_SHARED_MEMORY_SIGNATURE;

cleanup:
	RETURN(hr);
}



//$--HrFillInSharedMemory-------------------------------------------------------
//  Helper function that fills in the shared memory section with the structure 
//  that is sent to the Windows NT Performance Monitor via the DLL.
//
//  This process is done in two passes.  The first pass sets up the various 
//  pointers into the structure where data will be written, but does not write 
//  any actual data.  After the first pass, the size of the resulting structure 
//  is known, and a check is made to see that the resulting structure will fit 
//  into the shared memory section.  The second pass then takes the pointers 
//  that were set up by the first pass and fills in the actual data.
//
//  The structure that is created in the shared memory section has the 
//  following format, which conforms to the specification in WINPERF.H for 
//  the structure used to communicate with the Windows NT Performance Monitor:
//
//				   /+===============================+
//				  / |  _PERF_OBJECT_TYPE            |
//				 |  +===============================+
//				 |  |  _PERF_COUNTER_DEFINITION #1  |
//				 |  +-------------------------------+
//	"Header ---->|  |  _PERF_COUNTER_DEFINITION #2  |
//	 Data"		 |  +-------------------------------+
//				 |  :  ...........................  :
//				 |  +-------------------------------+
//				  \ |  _PERF_COUNTER_DEFINITION #N  |
//				   >+===============================+
//				  / |  _PERF_INSTANCE_DEFINITION    |
//				 |  +-------------------------------+
//				 |  |  Instance Name (UNICODE)      |
//				 |  +===============================+
//				 |  |  _PERF_COUNTER_BLOCK          |
//				 |  +-------------------------------+
//	"Instance -->|  |  Counter #1 (COUNTER)         |
//	 Data"		 |  +-------------------------------+
//				 |  |  Counter #2 (COUNTER)         |
//				 |  +-------------------------------+
//				 |  |  ....................         :
//				 |  +-------------------------------+
//				  \ |  Counter #N (COUNTER)         |
//				   \+===============================+
//
//  In addition to the above structure, the shared memory section contains 
//  some housekeeping information that is used to communicate with the 
//  DLL, but is not sent to the Windows NT Performance Monitor.  This 
//  information is described in the shared memory structure defined in 
//  MONSHARE.H.  In this housekeeping information is information that tells 
//  the DLL how to break the structure diagrammed above into two parts: 
//  "Header Data" and "Instance Data".  This is done so that if there are two 
//  instances of a gateway communicating with the same DLL, the DLL can easily 
//  take the "Header Data" from one gateway and combine it with the 
//  "Instance Data" sections from both gateways to form a single 
//  structure to pass to the Windows NT Performance Monitor.  This allows 
//  the user of Performance Monitor to see the gateways as a single object 
//  with multiple instances, rather than two separate objects.
// -----------------------------------------------------------------------------
static HRESULT HrFillInSharedMemory(	// RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx, 				// pointer to perf mon context
	IN DWORD ccdCounters,				// number of COUNTERDEF structures
	IN LPCOUNTERDEF lpcdCounters)		// array of COUNTERDEF structures
{
	HRESULT						hr						= NOERROR;

	// Variables used to create _PERF_COUNTER_DEFINITION structures, and to 
	// create MONFOLDER and MONCOUNTER structures.

	DWORD						iCounter				= 0;
	LPCOUNTERDEF				lpcdSrc					= NULL;
	PPERF_COUNTER_DEFINITION	lpDest					= NULL;
	LPCOUNTERDEF				lpcdCounter				= NULL;

	// Pointers used to allocate chunks off of the 
	// MONSHAREDMEMORY.rgbDataBlock[] structure.

	LPBYTE						lpbNextFreeByte			= NULL;
	LPBYTE						lpbNextFreeByteLim		= NULL;

	// Pointers to structures defined in winperf.h.

	PPERF_OBJECT_TYPE			lpObjectType			= NULL;
	PPERF_COUNTER_DEFINITION	lpCounterDefinition		= NULL;
	PPERF_INSTANCE_DEFINITION	lpInstanceDefinition	= NULL;
	LPWSTR						lpwszInstanceName		= NULL;
	DWORD						cwInstanceNameSize		= 0;
	PPERF_COUNTER_BLOCK			lpCounterBlock			= NULL;
	LPCOUNTER					lpcntCounter			= NULL;
    DWORD                       cLargeCounters          = 0;
    DWORD                       iCounterAllocated       = 0;
	LPBYTE						lpbStructureEnd			= NULL;

	DEBUGPRIVATE("HrFillInSharedMemory()\n");

	// Check the parameters.

	hr = CHK_HrFillInSharedMemory(lpmcx, ccdCounters, lpcdCounters);
	if (FAILED(hr))
		RETURN(hr);

	ASSERTERROR(lpmcx->lpcntCounter == NULL, "lpmcx->lpcntCounter != NULL");

    // Count the number of user-defined counters that are of size 
    // PERF_SIZE_LARGE because we will have to allow double space for them.
    // While we're counting, if we find any counters of size PERF_SIZE_ZERO 
    // or PERF_SIZE_VARIABLE_LEN then return an error, because we don't 
    // support those types.

    for (iCounter = 0; iCounter < ccdCounters; iCounter++)
    {
        if (lpcdCounters[iCounter].ctStatistic == COUNTERTYPE_USER_DEFINED)
        {
            switch (lpcdCounters[iCounter].dwUserCounterType & 0x00000300)
            {
                case PERF_SIZE_LARGE:
                    cLargeCounters++;
                    break;

                case PERF_SIZE_DWORD:
                    break;

                default:
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
            }
        }
    }

    // Initially zero out the block in shared memory.

    ZeroMemory(lpmcx->lpmsmSharedMemory->rgbDataBlock, MON_DATA_BLOCK_SIZE);

	// Set pointers into the build buffer area of shared memory.
	// These pointers are used to get chunks of memory from the 
	// buffer and check for overflow.

	lpbNextFreeByte = lpmcx->lpmsmSharedMemory->rgbDataBlock;
	lpbNextFreeByteLim = lpbNextFreeByte + MON_DATA_BLOCK_SIZE;

	// Set pointers into the build buffer for where the various structures 
	// will go (don't fill anything in just yet--we have to check for overflow 
	// first!).

	hr = HrAlignPointer(4, &lpbNextFreeByte);
    if (FAILED(hr))
        goto cleanup;

	lpObjectType = (PERF_OBJECT_TYPE *)lpbNextFreeByte;
	lpbNextFreeByte += sizeof(*lpObjectType);

	lpCounterDefinition = (PERF_COUNTER_DEFINITION *)lpbNextFreeByte;
	lpbNextFreeByte += ccdCounters * sizeof(*lpCounterDefinition);

	lpInstanceDefinition = (PERF_INSTANCE_DEFINITION *)lpbNextFreeByte;
	lpbNextFreeByte += sizeof(*lpInstanceDefinition);

	// NOTE: Instance name is always UNICODE!!!

	lpwszInstanceName = (LPWSTR)lpbNextFreeByte;

	// Calculate how many characters are needed for the conversion.
	if (lstrlen(lpmcx->lpszObjectName) == 0)
	{
		cwInstanceNameSize = 0;
	}
	else
	{
		cwInstanceNameSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, 
			lpmcx->lpszObjectName, -1, 0, 0);
		if (cwInstanceNameSize == 0)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
		cwInstanceNameSize--;
	}

	lpbNextFreeByte += (cwInstanceNameSize + 1) * sizeof(WCHAR);

	hr = HrAlignPointer(4, &lpbNextFreeByte);
    if (FAILED(hr))
        goto cleanup;

	lpCounterBlock = (PERF_COUNTER_BLOCK *)lpbNextFreeByte;
	lpbNextFreeByte += sizeof(lpCounterBlock->ByteLength);

	lpcntCounter = (LPCOUNTER)lpbNextFreeByte;
	lpbNextFreeByte += (ccdCounters + cLargeCounters) * sizeof(COUNTER);

	hr = HrAlignPointer(4, &lpbNextFreeByte);
    if (FAILED(hr))
        goto cleanup;

	lpbStructureEnd = lpbNextFreeByte;

	// Check for overflow.

	if (lpbNextFreeByte > lpbNextFreeByteLim)
	{
		hr = HR_LOG(E_OUTOFMEMORY);
		goto cleanup;
	}

	// Fill in _PERF_OBJECT_TYPE structure.

	lpObjectType->TotalByteLength = lpbStructureEnd - (LPBYTE)lpObjectType;
	lpObjectType->DefinitionLength = 
		(LPBYTE)lpInstanceDefinition - (LPBYTE)lpObjectType;
	lpObjectType->HeaderLength = 
		(LPBYTE)lpCounterDefinition - (LPBYTE)lpObjectType;
	lpObjectType->ObjectNameTitleIndex = 
		lpmcx->dwFirstCounter + lpmcx->iObjectTitleOffset;
	if (lpObjectType->ObjectNameTitleIndex > lpmcx->dwLastCounter)
	{
		hr = HR_LOG(E_INVALIDARG);
		goto cleanup;
	}
	lpObjectType->ObjectNameTitle = NULL;
	lpObjectType->ObjectHelpTitleIndex = 
		lpmcx->dwFirstHelp + lpmcx->iObjectTitleOffset;
	if (lpObjectType->ObjectHelpTitleIndex > lpmcx->dwLastHelp)
	{
		hr = HR_LOG(E_INVALIDARG);
		goto cleanup;
	}
	lpObjectType->ObjectHelpTitle = NULL;
	lpObjectType->DetailLevel = lpmcx->dwObjectDetailLevel;
	lpObjectType->NumCounters = ccdCounters;
	lpObjectType->DefaultCounter = lpmcx->dwDefaultCounter;
	lpObjectType->NumInstances = 1;
	lpObjectType->CodePage = 0;
	lpObjectType->PerfTime.LowPart = 0;
	lpObjectType->PerfTime.HighPart = 0;
	lpObjectType->PerfFreq.LowPart = 0;
	lpObjectType->PerfFreq.HighPart = 0;


	// Fill in _PERF_COUNTER_DEFINITION structures.

    // Set iCounterAllocated = 1 to skip a DWORD at the front for the 
    // PERF_COUNTER_BLOCK header.

    iCounterAllocated = 1;

	for (iCounter = 0; iCounter < ccdCounters; ++iCounter)
	{
		lpcdSrc = &lpcdCounters[iCounter];
		lpDest = &lpCounterDefinition[iCounter];

		ASSERT_DETAIL_LEVEL(lpcdSrc->dwDetailLevel, 
			"lpcdSrc->dwDetailLevel: invalid value");

		lpDest->ByteLength = sizeof(*lpDest);
		lpDest->CounterNameTitleIndex = 
			lpmcx->dwFirstCounter + lpcdSrc->iCounterTitleOffset;
		if (lpDest->CounterNameTitleIndex > lpmcx->dwLastCounter)
		{
			hr = HR_LOG(E_INVALIDARG);
			goto cleanup;
		}
		lpDest->CounterNameTitle = NULL;
		lpDest->CounterHelpTitleIndex = 
			lpmcx->dwFirstHelp + lpcdSrc->iCounterTitleOffset;
		if (lpDest->CounterHelpTitleIndex > lpmcx->dwLastHelp)
		{
			hr = HR_LOG(E_INVALIDARG);
			goto cleanup;
		}
		lpDest->CounterNameTitle = NULL;
		lpDest->DefaultScale = lpcdSrc->dwDefaultScale;
		lpDest->DetailLevel = lpcdSrc->dwDetailLevel;
		hr = HrComputeCounterType(
			lpcdSrc->ctStatistic, 
			lpcdSrc->perPeriod, 
			lpcdSrc->dwUserCounterType, 
			&lpDest->CounterType);
        if (FAILED(hr))
		{
			hr = HR_LOG(E_INVALIDARG);
			goto cleanup;
		}

        if ((lpcdSrc->dwUserCounterType & 0x00000300) == PERF_SIZE_LARGE)
        {
    		lpDest->CounterSize = 2 * sizeof(COUNTER);
    		lpDest->CounterOffset = iCounterAllocated * sizeof(COUNTER);
            iCounterAllocated += 2;
        }
        else
        {
    		lpDest->CounterSize = sizeof(COUNTER);
    		lpDest->CounterOffset = iCounterAllocated * sizeof(COUNTER);
            iCounterAllocated++;
        }
	}

	// Fill in _PERF_INSTANCE_DEFINITION structure.

	lpInstanceDefinition->ByteLength = 
		(LPBYTE)lpCounterBlock - (LPBYTE)lpInstanceDefinition;
	lpInstanceDefinition->ParentObjectTitleIndex = 0;
	lpInstanceDefinition->ParentObjectInstance = 0;
	lpInstanceDefinition->UniqueID = PERF_NO_UNIQUE_ID;
	lpInstanceDefinition->NameOffset = sizeof(*lpInstanceDefinition);

	// Fill in instance name.  NOTE: Instance name is always UNICODE!!!

	lpInstanceDefinition->NameLength = (cwInstanceNameSize + 1) * sizeof(WCHAR);

	if (lstrlen(lpmcx->lpszObjectName) == 0)
	{
		cwInstanceNameSize = 0;
	}
	else
	{
		if (
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpmcx->lpszObjectName, 
			-1, lpwszInstanceName, cwInstanceNameSize + 1) == 0)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
	}
	lpwszInstanceName[cwInstanceNameSize] = 0;

	// Fill in _PERF_COUNTER_BLOCK structure.

	lpCounterBlock->ByteLength = lpbStructureEnd - (LPBYTE)lpCounterBlock;

	// Fill in the shared memory header block (this is some information in the 
	// shared memory, before the _PERF blocks, which helps the DLL get easy 
	// access to the two halves of the _PERF structure group that it needs).

	lpmcx->lpmsmSharedMemory->ibHeaderOffset = 
		(LPBYTE)lpObjectType - (LPBYTE)lpmcx->lpmsmSharedMemory;
	lpmcx->lpmsmSharedMemory->cbHeaderSize = 
		(LPBYTE)lpInstanceDefinition - (LPBYTE)lpObjectType;
	lpmcx->lpmsmSharedMemory->ibInstanceOffset = 
		(LPBYTE)lpInstanceDefinition - (LPBYTE)lpmcx->lpmsmSharedMemory;
	lpmcx->lpmsmSharedMemory->cbInstanceSize = 
		lpbStructureEnd - (LPBYTE)lpInstanceDefinition;

	// Save a pointer to the counters in the context (for use by
	// HrMonBuildStructures).

	lpmcx->lpcntCounter = lpcntCounter;

cleanup:
	RETURN(hr);
}



//$--HrBuildStructures----------------------------------------------------------
//  Helper function that sets up structures representing folders and counters
//  in the performance monitoring context.
// -----------------------------------------------------------------------------
static HRESULT HrBuildStructures(	    // RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx,				// pointer to perf mon context
	IN DWORD ccdCounters,				// number of COUNTERDEF structures
	IN LPCOUNTERDEF lpcdCounters)		// array of COUNTERDEF structures
{
	HRESULT						hr						= NOERROR;
	HRESULT						hrT						= NOERROR;

	// Variables used to create MONFOLDER and MONCOUNTER structures.

	LPMONCOUNTER				lpmcCounter				= NULL;
	LPMONFOLDER					lpmfFolder				= NULL;

	// Variables used to access COUNTERDEF structures.

	DWORD						iCounter				= 0;
	LPCOUNTERDEF				lpcdCounter				= NULL;

	// Variables used to create jumping sliding windows (JSW's).

	__int64						dwlJSWStartTime			= 0;

	DEBUGPRIVATE("HrBuildStructures()\n");

	// Check the parameters.

	hr = CHK_HrBuildStructures(lpmcx, ccdCounters, lpcdCounters);
	if (FAILED(hr))
		RETURN(hr);

	ASSERTERROR(lpmcx->lpmcMessagesTransferredIn == NULL, 
		"lpmcx->lpmcMessagesTransferredIn != NULL");
	ASSERTERROR(lpmcx->lpmcMessagesTransferredOut == NULL, 
		"lpmcx->lpmcMessagesTransferredOut != NULL");
	ASSERTERROR(lpmcx->lpmcBytesTransferredIn == NULL, 
		"lpmcx->lpmcBytesTransferredIn != NULL");
	ASSERTERROR(lpmcx->lpmcBytesTransferredOut == NULL, 
		"lpmcx->lpmcBytesTransferredOut != NULL");
	ASSERTERROR(lpmcx->lpmcNDRsIn == NULL, 
		"lpmcx->lpmcNDRsIn != NULL");
	ASSERTERROR(lpmcx->lpmcNDRsOut == NULL, 
		"lpmcx->lpmcNDRsOut != NULL");
	ASSERTERROR(lpmcx->lpmcAssociations == NULL, 
		"lpmcx->lpmcAssociations != NULL");
	ASSERTERROR(lpmcx->lpmcFreeList == NULL, 
		"lpmcx->lpmcFreeList != NULL");
	ASSERTERROR(lpmcx->lpmcJSWCounterList == NULL, 
		"lpmcx->lpmcJSWCounterList != NULL");
	ASSERTERROR(lpmcx->lpmfFolderList == NULL, 
		"lpmcx->lpmfFolderList != NULL");

	// Compute time to use as base for JSW's, which should be on an even 
	// minute boundry.

	dwlJSWStartTime = (lpmcx->dwlCurrentTime / ONE_MINUTE) * ONE_MINUTE;

	// Process each COUNTERDEF structure.  If it is for a user defined counter 
	// then return a pointer to it to the caller of HrMonInit().  If it is 
	// for any other type of counter, then add entries to the MONCOUNTER lists 
	// and the MONFOLDER list as appropriate and create a JSWindow structure 
	// if needed.

	for (iCounter = 0; iCounter < ccdCounters; ++iCounter)
	{
		lpcdCounter = &lpcdCounters[iCounter];

		// If this is a user defined counter then return a pointer to 
		// the actual counter in the place requested in the call to 
		// HrMonInit().

		if (lpcdCounter->ctStatistic == COUNTERTYPE_USER_DEFINED)
		{
			ASSERTERROR(lpcdCounter->lppcntUserCounter != NULL, 
				"lpcdCounter->lppcntUserCounter == NULL");
			ASSERTERROR(lpcdCounter->perPeriod == PERIODTYPE_NONE, 
				"lpcdCounter->perPeriod != PERIODTYPE_NONE");

			*(lpcdCounter->lppcntUserCounter) = 
				&(lpmcx->lpcntCounter[iCounter]);

			// Skip to the next COUNTERDEF.

			continue;
		}

		// If we reach here then it's not a user defined counter.

		ASSERTERROR(lpcdCounter->ctStatistic < COUNTERTYPE_LAST, 
			"lpcdCounter->ctStatistic: illegal value");
		ASSERTERROR(lpcdCounter->perPeriod < PERIODTYPE_LAST, 
			"lpcdCounter->perPeriod: illegal value");
		ASSERT_DETAIL_LEVEL(lpcdCounter->dwDetailLevel, 
			"lpcd->dwDetailLevel: illegal value");

		// Allocate and fill in a new MONCOUNTER structure.  Put new 
		// MONCOUNTER structure on the free list so MonFreeEverything() 
		// will be able to find it and free it in case we have to abort.
		// The free list is really just a temporary holding area that 
		// will never have more than one entry at a time.

		lpmcCounter = malloc(sizeof(*lpmcCounter));
		if (lpmcCounter == NULL)
		{
			hr = HR_LOG(E_OUTOFMEMORY);
			goto cleanup;
		}
		ZeroMemory(lpmcCounter, sizeof(*lpmcCounter));

		lpmcCounter->lpmcNext = lpmcx->lpmcFreeList;
		lpmcx->lpmcFreeList = lpmcCounter;

        // If the period type is anything other than PERIODTYPE_CONTINUOUS 
        // then we need to zero out the counter when HrMonUninit is called.
        // This makes sure all the counters go to zero for any PerfMon still 
        // watching.  We shouldn't zero the "continuous" ones, because their 
        // displayed value is based on their increase, and zeroing them may 
        // result in a huge value being briefly displayed.  Of course, we 
        // will see that huge value anyway if PerfMon is still watching when 
        // the gateway restarts, but that seems like a better place to take 
        // the hit.

        if (lpcdCounter->perPeriod != PERIODTYPE_CONTINUOUS)
            lpmcCounter->fZeroOnFree = TRUE;

		// If there is a folder associated with this COUNTERDEF, then we need 
		// to find a MONFOLDER structure that matches it or create a new one if 
		// one does not already exist.  If there is no folder associated with 
		// this counter then we can skip this part.

		lpmfFolder = NULL;

		if (lpcdCounter->lpFolder != NULL)
		{
			// See if a MONFOLDER structure has already been defined for this 
			// folder.

			hrT = HrMonFindFolder(lpmcx->lpmfFolderList, lpcdCounter->lpFolder, 
				&lpmfFolder);
			if (FAILED(hrT))
			{
	            ULONG			cValues						= 0;
	            LPSPropValue	lpProps						= NULL;
	            SizedSPropTagArray(1, rgPropTags) = 
	                {1, {PR_MESSAGE_SIZE}};

				// A MONFOLDER structure has not already been defined for 
				// this folder, so allocate one, fill it in and add it to 
				// the folder list.

				lpmfFolder = malloc(sizeof(*lpmfFolder));
				if (lpmfFolder == NULL)
				{
					hr = HR_LOG(E_OUTOFMEMORY);
					goto cleanup;
				}
				ZeroMemory(lpmfFolder, sizeof(*lpmfFolder));

				lpmfFolder->lpmcx = lpmcx;
				lpmfFolder->lpFolder = lpcdCounter->lpFolder;

                // We need to do AddRef/Release because we are keeping 
                // folder pointers around between HrMonInit and HrMonUninit.

                MAPICALL(lpmfFolder->lpFolder)->AddRef(lpmfFolder->lpFolder);

				lpmfFolder->lpmfNext = lpmcx->lpmfFolderList;
				lpmcx->lpmfFolderList = lpmfFolder;

                // Get the number of bytes in the folder (PR_MESSAGE_SIZE) 
                // and store it in lpmfFolder->cTotalBytesEnteringFolder.
                // This will allow proper handling of the "bytes leaving 
                // folder" counter in the case where messages are waiting 
                // in the folder when monitoring starts.

				hr = lpmfFolder->lpFolder->lpVtbl->GetProps(
					lpmfFolder->lpFolder, 
					(LPSPropTagArray) &rgPropTags, 
					fMapiUnicode, 
					&cValues, 
					&lpProps);
                if (FAILED(hr) || hr == MAPI_W_ERRORS_RETURNED)
                {
                    if (hr == MAPI_W_ERRORS_RETURNED)
                    {
                        MAPIFREEBUFFER(lpProps);
                        hr = HR_LOG(E_FAIL);
                    }
                    goto cleanup;
                }

				lpmfFolder->cTotalBytesEnteringFolder = lpProps[0].Value.ul;

				MAPIFREEBUFFER(lpProps);
                
                // Create a critical section for this folder.

				InitializeCriticalSection(&lpmfFolder->csCriticalSection);
				lpmfFolder->fCriticalSectionInitialized = TRUE;

				// Set the folder to get it's initial size.

				lpmfFolder->fUpdateFolderSize = TRUE;
			}
		}

		// Take the MONCOUNTER structure off the free list in preparation 
		// for linking it into another list.

		ASSERTERROR(lpmcx->lpmcFreeList != NULL, "free list empty");

		lpmcCounter = lpmcx->lpmcFreeList;
		lpmcx->lpmcFreeList = lpmcx->lpmcFreeList->lpmcNext;

		// Link the MONCOUNTER structure into the proper list.  This could 
		// be a general list attached to the context structure, or a folder-
		// specific list attached to a MONFOLDER structure.

		hr = HrLinkCounterIntoList(
			lpmcx, 
			lpmfFolder, 
			lpmcCounter, 
			lpcdCounter->ctStatistic);
		if (FAILED(hr))
		{
			goto cleanup;
		}

		// Create the JSW attached to the counter structure if one is requested 
		// by the PERIODTYPE.

		if (lpcdCounter->perPeriod == PERIODTYPE_LAST_N_MINUTES)
		{
			__int64 dwlJumpTime = ONE_MINUTE;

			hr = HrJSOpen(
				JSWINDOW_TOTAL_RATE, 
				&TO_FILETIME(dwlJSWStartTime), 
				&TO_FILETIME(dwlJumpTime), 
				lpcdCounter->cMinutes, 
				&lpmcCounter->hjswJumpWindow);

			if (FAILED(hr))
			{
				lpmcCounter->hjswJumpWindow = NULL;	// Just to make sure.
				goto cleanup;
			}

			// Also add the counter structure to the list of counter structures 
			// that have JSWs.

			lpmcCounter->lpmcNextJSW = lpmcx->lpmcJSWCounterList;
			lpmcx->lpmcJSWCounterList = lpmcCounter;
		}

		// Add a pointer to the counter to the MONCOUNTER structure.

		if (lpmcCounter)
		{
			lpmcCounter->lpcntCounter = &(lpmcx->lpcntCounter[iCounter]);
		}

	} // end for

cleanup:
	RETURN(hr);
}



//$--HrMonFindFolder------------------------------------------------------------
//  Helper function that takes a MAPIFOLDER as input and searches a list of 
//  folders to find a MONFOLDER structure for that folder.  If the folder is 
//  found a pointer to it is placed in the memory pointed to by lppmfFolder and 
//  NOERROR is returned.  Otherwise, and error is returned.
// -----------------------------------------------------------------------------
static HRESULT HrMonFindFolder(			// RETURNS: HRESULT
	IN  LPMONFOLDER   lpmfFolderList,	// list of folder structs to search
	IN  LPMAPIFOLDER  lpFolder,			// folder to search for
	OUT LPMONFOLDER * lppmfFolder)		// folder found
{
	HRESULT		hr		= NOERROR;

	DEBUGPRIVATE("HrMonFindFolder()\n");

	// Check the parameters.

	hr = CHK_HrMonFindFolder(lpmfFolderList, lpFolder, lppmfFolder);
	if (FAILED(hr))
		RETURN(hr);

	while (lpmfFolderList && lpmfFolderList->lpFolder != lpFolder)
	{
		lpmfFolderList = lpmfFolderList->lpmfNext;

		ASSERT_READ_PTR_OR_NULL(lpmfFolderList, sizeof(*lpmfFolderList), 
			"lpmfFolderList: bad read pointer");
	}

	if (lpmfFolderList == NULL)
	{
		hr = HR_LOG(EDK_E_NOT_FOUND);
	}
	else
	{
		*lppmfFolder = lpmfFolderList;
	}

	RETURN(hr);
}



//$--HrStartUpdateThread--------------------------------------------------------
//  Helper function that starts the thread that wakes up periodically to update 
//  the jumping sliding windows and folders.
// -----------------------------------------------------------------------------
static HRESULT HrStartUpdateThread(     // RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx)              // pointer to perf mon context
{
	HRESULT					hr			= NOERROR;
	SECURITY_ATTRIBUTES		saEvent		= {0, NULL, TRUE};

	DEBUGPRIVATE("HrStartUpdateThread()\n");

	// Check the parameters.

	hr = CHK_HrStartUpdateThread(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

	ASSERTERROR(!lpmcx->fUpdateThreadRunning, "thread already running");
	ASSERTERROR(lpmcx->hUpdateThread == NULL, "lpmcx->hUpdateThread != NULL");
	ASSERTERROR(lpmcx->hUpdateThreadWakeEvent == NULL, 
		"lpmcx->hUpdateThreadWakeEvent != NULL");
	ASSERTERROR(lpmcx->dwUpdateThreadID == 0, "lpmcx->dwUpdateThreadID != 0");
	ASSERTERROR(lpmcx->fUpdateThreadTerminate == FALSE, 
		"lpmcx->fUpdateThreadTerminate != FALSE");

	// Create an unnamed, inheritable, auto-reset event.  This will be 
	// set by the gateway process to wake the thread, either to update 
	// or to terminate.  Start it signaled so the update thread wakes 
	// up to set the initial values of the folder counters.

	lpmcx->hUpdateThreadWakeEvent = CreateEvent(&saEvent, FALSE, TRUE, NULL);
	if (lpmcx->hUpdateThreadWakeEvent == NULL)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Create the thread.

	lpmcx->hUpdateThread = CreateThread(NULL, 0, UpdateThread, lpmcx, 0, 
		&lpmcx->dwUpdateThreadID);
	if (lpmcx->hUpdateThread == NULL)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

cleanup:
	if (FAILED(hr))
	{
		CLOSEHANDLE(lpmcx->hUpdateThreadWakeEvent);
	}
	RETURN (hr);
}



//$--UpdateThread---------------------------------------------------------------
//  Function that is called as a seperate thread.  It wakes up periodically and 
//  updates the jumping sliding windows and folders.
// -----------------------------------------------------------------------------
static DWORD WINAPI UpdateThread(	    // RETURNS: error code
	IN LPVOID lpThreadParameter)		// pointer to perf mon context
{
	static BOOL		fGetPropsErrorLoggedOnce	= FALSE;
	static BOOL		fJSWFailureLoggedOnce		= FALSE;

	LPMONCONTEXT	lpmcx						= lpThreadParameter;

	HRESULT			hr							= NOERROR;
	DWORD			dwStatus					= ERROR_SUCCESS;

	LPMONCOUNTER	lpmc						= NULL;
	LPMONFOLDER		lpmf						= NULL;

	DWORD			dwMillisecondsToWait		= 0;
	DWORD			dwWindowValue				= 0;
	DWORD			dwFractionCompleteNum		= 0;
	DWORD			dwFractionCompleteDen		= 0;

	DWORD			cMessagesInFolder			= 0;
	DWORD			cBytesInFolder				= 0;
	DWORD			cMessagesEnteringFolder		= 0;
	DWORD			cBytesEnteringFolder		= 0;
	DWORD			cMessagesLeavingFolder		= 0; 
	DWORD			cBytesLeavingFolder			= 0;

	ULONG			cValues						= 0;
	LPSPropValue	lpProps						= NULL;
	SizedSPropTagArray(2, rgPropTags) = 
	    {2, {PR_CONTENT_COUNT, PR_MESSAGE_SIZE}};

    BOOL            fCountersLocked             = FALSE;


	DEBUGPRIVATE("UpdateThread()\n");

	// Check the parameters.

	hr = CHK_UpdateThread(lpThreadParameter);
	if (FAILED(hr))
		RETURN(hr);

	// Loop until flag is set to stop the thread.

	while (!lpmcx->fUpdateThreadTerminate)
	{
		// If we have JSW's, then calculate how many milliseconds to wait 
		// until the next even minute mark.  Wait an extra second just to 
		// be sure we don't wake up too early.

		if (lpmcx->lpmcJSWCounterList)
		{
			__int64 dwlCurrentTime = 0;

		    hr = HrGetCurrentTime(&dwlCurrentTime);
            if (FAILED(hr))
                goto cleanup;

			dwMillisecondsToWait = (DWORD)
				(((ONE_MINUTE - (dwlCurrentTime % ONE_MINUTE)) 
				+ 10000000) / 10000);
		}

		// Otherwise, wait until the other thread wakes us up.

		else
		{
			dwMillisecondsToWait = INFINITE;
		}

		// Wait for specified time or wake event.

		dwStatus = WaitForSingleObject(
			lpmcx->hUpdateThreadWakeEvent, 
			dwMillisecondsToWait);
        if (dwStatus != WAIT_TIMEOUT && dwStatus != WAIT_OBJECT_0)
        {
            hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		// Check for terminate request.

		if (lpmcx->fUpdateThreadTerminate)
			goto cleanup;

		// Update the folder counters from the "update request" variables.

		if (lpmcx->lpmfFolderList)
		{
			for (
				lpmf = lpmcx->lpmfFolderList; 
				lpmf; 
				lpmf = lpmf->lpmfNext)
			{
				cMessagesEnteringFolder = 0;
				cBytesEnteringFolder = 0;
				cMessagesLeavingFolder = 0;
				cBytesLeavingFolder = 0;
				cMessagesInFolder = 0;
				cBytesInFolder = 0;

				if (lpmf->fUpdateFolderSize)
				{
					// Check for terminate request.

					if (lpmcx->fUpdateThreadTerminate)
						goto cleanup;

					// Get and reset the "update request" variables.

					EnterCriticalSection(&lpmf->csCriticalSection);

					cMessagesEnteringFolder = lpmf->cMessagesEnteringFolder;
					lpmf->cMessagesEnteringFolder = 0;
					cBytesEnteringFolder = lpmf->cBytesEnteringFolder;
					lpmf->cBytesEnteringFolder = 0;
					cMessagesLeavingFolder = lpmf->cMessagesLeavingFolder;
					lpmf->cMessagesLeavingFolder = 0;
					cBytesLeavingFolder = lpmf->cBytesLeavingFolder;
					lpmf->cBytesLeavingFolder = 0;
					lpmf->fUpdateFolderSize = FALSE;

					LeaveCriticalSection(&lpmf->csCriticalSection);

					// Check for terminate request.

					if (lpmcx->fUpdateThreadTerminate)
						goto cleanup;

					// Get number of messages and bytes in folder.

					if (lpmf->lpmcMessagesInFolder || 
					    lpmf->lpmcBytesInFolder || 
					    lpmf->lpmcBytesLeavingFolder)
					{
						// Get the PR_CONTENT_COUNT and PR_MESSAGE_SIZE props.

						hr = lpmf->lpFolder->lpVtbl->GetProps(
							lpmf->lpFolder, 
							(LPSPropTagArray) &rgPropTags, 
							fMapiUnicode, 
							&cValues, 
							&lpProps);
                        if (FAILED(hr) || hr == MAPI_W_ERRORS_RETURNED)
                        {
                            if (hr == MAPI_W_ERRORS_RETURNED)
                            {
                                MAPIFREEBUFFER(lpProps);
                            }
                            goto cleanup;
                        }

						cMessagesInFolder = lpProps[0].Value.ul;
						cBytesInFolder = lpProps[1].Value.ul;

						MAPIFREEBUFFER(lpProps);
					}

					// Check for terminate request.

					if (lpmcx->fUpdateThreadTerminate)
						goto cleanup;

					// If they want the number of bytes leaving the folder 
					// then calculate it and keep track of it here.

					if (lpmf->lpmcBytesLeavingFolder)
					{
						// Compute the total number of bytes entering folder 
						// so far.

						lpmf->cTotalBytesEnteringFolder += cBytesEnteringFolder;

						// Figure out how many bytes should be in the folder 
						// according to the running totals of bytes entering 
						// and bytes leaving that we have reported.  If the 
						// "should be" is higher than the actual, then report  
						// the difference as the number of bytes leaving the 
						// folder, and update the reported number leaving.

						if (lpmf->cTotalBytesEnteringFolder - 
							lpmf->cTotalBytesLeavingFolder > 
							cBytesInFolder)
						{
							cBytesLeavingFolder = 
								lpmf->cTotalBytesEnteringFolder - 
								lpmf->cTotalBytesLeavingFolder - 
								cBytesInFolder;
							lpmf->cTotalBytesLeavingFolder += 
								cBytesLeavingFolder;
						}
					}

					// Lock the counters.

					hr = HrMonLockCounters();
                    if (FAILED(hr))
                        goto cleanup;
                    fCountersLocked = TRUE;

                    // Get the system time.

					hr = HrGetCurrentTime(&lpmcx->dwlCurrentTime);
                    if (FAILED(hr))
                        goto cleanup;

                    // Update the counters.

					hr = HrAddToCounters(
						lpmcx, 
						lpmf->lpmcMessagesEnteringFolder, 
						cMessagesEnteringFolder);
                    if (FAILED(hr))
                        goto cleanup;

					hr = HrAddToCounters(
						lpmcx, 
						lpmf->lpmcBytesEnteringFolder, 
						cBytesEnteringFolder);
                    if (FAILED(hr))
                        goto cleanup;

					hr = HrAddToCounters(
						lpmcx, 
						lpmf->lpmcMessagesLeavingFolder, 
						cMessagesLeavingFolder);
                    if (FAILED(hr))
                        goto cleanup;

					hr = HrAddToCounters(
						lpmcx, 
						lpmf->lpmcBytesLeavingFolder, 
						cBytesLeavingFolder);
                    if (FAILED(hr))
                        goto cleanup;

					hr = HrSetCounters(
						lpmf->lpmcMessagesInFolder, 
						cMessagesInFolder);
                    if (FAILED(hr))
                        goto cleanup;

					hr = HrSetCounters(
						lpmf->lpmcBytesInFolder, 
						cBytesInFolder);
                    if (FAILED(hr))
                        goto cleanup;

                    // Unlock the counters.

                    fCountersLocked = FALSE;
					hr = HrMonUnlockCounters();
                    if (FAILED(hr))
                        goto cleanup;
				}
			}
		}

		// Update the JSW counters.

		if (lpmcx->lpmcJSWCounterList)
		{
			for (
				lpmc = lpmcx->lpmcJSWCounterList; 
				lpmc; 
				lpmc = lpmc->lpmcNextJSW)
			{
				ASSERT_READ_PTR(lpmc, sizeof(*lpmc), 
					"lpmc: bad write pointer");
				ASSERT_WRITE_PTR(lpmc->lpcntCounter, 
					sizeof(*lpmc->lpcntCounter), 
					"lpmc->lpcntCounter: bad write pointer");
				ASSERTERROR(lpmc->hjswJumpWindow != NULL, 
					"lpmc->hjswJumpWindow == NULL");

				// Check for terminate request.

				if (lpmcx->fUpdateThreadTerminate)
					goto cleanup;

				// Lock the counters.

				hr = HrMonLockCounters();
                if (FAILED(hr))
                    goto cleanup;
                fCountersLocked = TRUE;

				// Get the value of the JSWindow (update system time).

				hr = HrGetCurrentTime(&lpmcx->dwlCurrentTime);
                if (FAILED(hr))
                    goto cleanup;

				hr = HrJSGetValue(
					lpmc->hjswJumpWindow, 
					&TO_FILETIME(lpmcx->dwlCurrentTime), 
					&dwWindowValue, 
					&dwFractionCompleteNum, 
					&dwFractionCompleteDen);
				if (FAILED(hr))
                    goto cleanup;

				*lpmc->lpcntCounter = dwWindowValue;

                // Unlock the counters.

                fCountersLocked = FALSE;
				hr = HrMonUnlockCounters();
                if (FAILED(hr))
                    goto cleanup;
			} // end for

		} // end if

	} // end while (!lpmcx->fUpdateThreadTerminate)

cleanup:
    // Unlock the counters if they're locked.

    if (fCountersLocked)
    {
	    hr = HrMonUnlockCounters();
        if (FAILED(hr))
            HR_LOG(hr);
    }

    // Always return success.

	return(ERROR_SUCCESS);
}



//$--HrFreeEverything-----------------------------------------------------------
//  Helper function that shuts down the thread, monitoring, and frees memory.
// -----------------------------------------------------------------------------
static HRESULT HrFreeEverything(		// RETURNS: HRESULT
	IN LPMONCONTEXT *lppmcx)			// the address of the pointer to the 
										// performance monitoring context (the 
										// pointer will be set to NULL)
{
	BOOL			fItWorked		= FALSE;
	HRESULT			hr				= NOERROR;
	HRESULT			hrT				= NOERROR;
	LPMONCONTEXT	lpmcx			= NULL;
	LPMONFOLDER		lpmf			= NULL;
	LPMONCOUNTER	lpmc			= NULL;

	DEBUGPRIVATE("HrFreeEverything()\n");

	// Check the parameters.

	hr = CHK_HrFreeEverything(lppmcx);
	if (FAILED(hr))
		RETURN(hr);

	// This pointer is easier to use.

	lpmcx = *lppmcx;

	// Free the context only if there is one allocated.

	if (lpmcx)
	{
		// Tell the update thread to shut down and wait for it to do so.

		if (lpmcx->hUpdateThread)
		{
			lpmcx->fUpdateThreadTerminate = TRUE;

			hrT = HrWakeUpdateThread(lpmcx);
            if (FAILED(hrT))
                hr = hrT;
			else
			{
				DWORD dw = WaitForSingleObject(lpmcx->hUpdateThread, INFINITE);
				if (dw != WAIT_OBJECT_0)
				{
                    hr = HR_LOG(E_FAIL);
				}
			}
			CLOSEHANDLE(lpmcx->hUpdateThread);
			lpmcx->dwUpdateThreadID = 0;
		}

		// Close the handle to the thread termination event.

		CLOSEHANDLE(lpmcx->hUpdateThreadWakeEvent);

		// Unhook monitoring routines and delete critical sections for folders.

		for (
			lpmf = lpmcx->lpmfFolderList; 
			lpmf; 
			lpmf = lpmf->lpmfNext)
		{
			if (lpmf->fCriticalSectionInitialized)
			{
				DeleteCriticalSection(&lpmf->csCriticalSection);
				lpmf->fCriticalSectionInitialized = FALSE;
			}

			if (lpmf->lpTable)
			{
				hrT = MAPICALL(lpmf->lpTable)->
					Unadvise(lpmf->lpTable, lpmf->ulConnection);
                if (FAILED(hrT))
                    hr = hrT;
				lpmf->lpTable = NULL;

				ULRELEASE(lpmf->lpTable);
				lpmf->lpTable = NULL;
			}
			ULRELEASE(lpmf->lpAdvise);
			lpmf->lpAdvise = NULL;
			lpmf->ulConnection = 0;
		}

		// Free strings attached to the context.

		ASSERT_STRING_PTR_OR_NULL(lpmcx->lpszObjectName, 
			"lpmcx->lpszObjectName: bad string pointer");
		FREE(lpmcx->lpszObjectName);

		ASSERT_STRING_PTR_OR_NULL(lpmcx->lpszObjectClass, 
			"lpmcx->lpszObjectClass: bad string pointer");
		FREE(lpmcx->lpszObjectClass);

		// Close all the JSW's.

		for (lpmc = lpmcx->lpmcJSWCounterList; lpmc; lpmc = lpmc->lpmcNextJSW)
		{
			ASSERTERROR(lpmc->hjswJumpWindow != NULL, 
				"lpmc->hjswJumpWindow == NULL");

			JSClose(lpmc->hjswJumpWindow);
			lpmc->hjswJumpWindow = NULL;
		}
		lpmcx->lpmcJSWCounterList = NULL;

		// Free all the MONCOUNTER structures attached directly to the context.

		hrT = HrFreeCounterList(&lpmcx->lpmcMessagesTransferredIn);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmcx->lpmcMessagesTransferredOut);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmcx->lpmcBytesTransferredIn);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmcx->lpmcBytesTransferredOut);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmcx->lpmcNDRsIn);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmcx->lpmcNDRsOut);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmcx->lpmcAssociations);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmcx->lpmcFreeList);
        if (FAILED(hrT))
            hr = hrT;

		// Free all the MONFOLDER structures, including the MONCOUNTER 
		// structures attached to the folders.

		hrT = HrFreeFolderList(&lpmcx->lpmfFolderList);
        if (FAILED(hrT))
            hr = hrT;

		// If we mapped the shared memory, unmap the view of the file.
        // NOTE: LEAVE THE fDateIsValid FLAG UNCHANGED SO ANYBODY STILL 
        // WATCHING US WILL SEE VALID DATA!!!

		if (lpmcx->lpmsmSharedMemory)
		{
			fItWorked = UnmapViewOfFile(lpmcx->lpmsmSharedMemory);
			if (!fItWorked)
			{
                hr = HR_LOG(E_FAIL);
			}
			lpmcx->lpmsmSharedMemory = NULL;
		}

		// Close file mapping object if it is open.

		CLOSEHANDLE(lpmcx->hSharedMemoryMapping);

		// Clear other shared memory variables.

		lpmcx->cbSharedMemorySize = 0;

		// Close mutex handle if it is open.

		CLOSEHANDLE(lpmcx->hSharedMemoryMutex);

		// Free the context itself.

		FREE(*lppmcx);
	}

    RETURN(hr);
}



//$--HrFreeCounterList----------------------------------------------------------
//  Helper function that frees a list of MONCOUNTER structures.
// -----------------------------------------------------------------------------
static HRESULT HrFreeCounterList(		// RETURNS: HRESULT
	IN LPMONCOUNTER *lppmcCounterList)	// address of pointer to first element
										// of counter list to be freed
{
	HRESULT			hr			= NOERROR;
	LPMONCOUNTER 	lpmc		= NULL;
	LPMONCOUNTER	lpmcNext	= NULL;

	DEBUGPRIVATE("HrFreeCounterList()\n");

	// Check the parameters.

	hr = CHK_HrFreeCounterList(lppmcCounterList);
	if (FAILED(hr))
		RETURN(hr);

	lpmc = *lppmcCounterList;
	while (lpmc)
	{
		ASSERT_WRITE_PTR(lpmc, sizeof(*lpmc), "lpmc: bad write pointer");
		ASSERTWARNING(lpmc->hjswJumpWindow == NULL, 
			"lpmc->hjswJumpWindow != NULL");

        // Zero out the actual counter if requested.

        if (lpmc->fZeroOnFree && lpmc->lpcntCounter)
            *(lpmc->lpcntCounter) = 0;

        // Now free this node and move to the next one.

		lpmcNext = lpmc->lpmcNext;
		FREE(lpmc);
		lpmc = lpmcNext;
	}
	*lppmcCounterList = NULL;

    RETURN(hr);
}



//$--HrFreeFolderList-----------------------------------------------------------
//  Helper function that frees a list of MONFOLDER structures and the 
//  MONCOUNTER structures attached to them.
// -----------------------------------------------------------------------------
static HRESULT HrFreeFolderList(		// RETURNS: HRESULT
	IN LPMONFOLDER *lppmfFolderList)	// address of pointer to first element
										// of folder list to be freed
{
	HRESULT			hr			= NOERROR;
	HRESULT			hrT			= NOERROR;
	LPMONFOLDER 	lpmf		= NULL;
	LPMONFOLDER		lpmfNext	= NULL;

	DEBUGPRIVATE("HrFreeFolderList()\n");

	// Check the parameters.

	hr = CHK_HrFreeFolderList(lppmfFolderList);
	if (FAILED(hr))
		RETURN(hr);

	lpmf = *lppmfFolderList;
	while (lpmf)
	{
        ULONG ulRefCount = 0;

		ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");

        // We need to do AddRef/Release because we are keeping 
        // folder pointers around between HrMonInit and HrMonUninit.

        ulRefCount = MAPICALL(lpmf->lpFolder)->Release(lpmf->lpFolder);
        ASSERTWARNING(ulRefCount <= 2, "ulRefCount > 2");

		hrT = HrFreeCounterList(&lpmf->lpmcMessagesInFolder);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmf->lpmcBytesInFolder);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmf->lpmcMessagesEnteringFolder);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmf->lpmcBytesEnteringFolder);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmf->lpmcMessagesLeavingFolder);
        if (FAILED(hrT))
            hr = hrT;

		hrT = HrFreeCounterList(&lpmf->lpmcBytesLeavingFolder);
        if (FAILED(hrT))
            hr = hrT;

		lpmfNext = lpmf->lpmfNext;
		FREE(lpmf);
		lpmf = lpmfNext;
	}
	*lppmfFolderList = NULL;

    RETURN(hr);
}




//$--HrAddToCounters------------------------------------------------------------
//  Helper function that adds a value to each of the counters on the list.
// -----------------------------------------------------------------------------
static HRESULT HrAddToCounters(			// RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx,				// pointer to perf mon context
	IN LPMONCOUNTER lpmcList,			// pointer to list of counters
	IN LONG dwAmount)					// amount to add to each one
{
	static BOOL			fLoggedOnce		= FALSE;
	HRESULT				hr				= NOERROR;
	LPMONCOUNTER		lpmc			= NULL;

	DEBUGPRIVATE("HrAddToCounters()\n");

	// Check the parameters.

	hr = CHK_HrAddToCounters(lpmcx, lpmcList, dwAmount);
	if (FAILED(hr))
		RETURN(hr);

	for (lpmc = lpmcList; lpmc; lpmc = lpmc->lpmcNext)
	{
		ASSERT_READ_PTR(lpmc, sizeof(*lpmc), "lpmc: bad read pointer");

		if (lpmc->hjswJumpWindow)
		{
			// Update jump window.

			hr = HrJSCollectDataPoint(
				lpmc->hjswJumpWindow, 
				&TO_FILETIME(lpmcx->dwlCurrentTime), 
				dwAmount);
			if (FAILED(hr))
                goto cleanup;
		}
		else
		{
			// Update counter directly.

			ASSERT_WRITE_PTR(
				lpmc->lpcntCounter, 
				sizeof(*lpmc->lpcntCounter), 
				"lpmc->lpcntCounter: bad write pointer");

			*lpmc->lpcntCounter += dwAmount;
		}
	}

cleanup:
    RETURN(hr);
}



//$--HrSetCounters--------------------------------------------------------------
//  Helper function that assigns a value to each of the counters on the list.
// -----------------------------------------------------------------------------
static HRESULT HrSetCounters(			// RETURNS: HRESULT
	IN LPMONCOUNTER lpmcList,			// pointer to list of counters
	IN DWORD dwAmount)					// amount to set each one to
{
	HRESULT				hr		= NOERROR;
	LPMONCOUNTER		lpmc	= NULL;

	DEBUGPRIVATE("HrSetCounters()\n");

	// Check the parameters.

	hr = CHK_HrSetCounters(lpmcList, dwAmount);
	if (FAILED(hr))
		RETURN(hr);

	for (lpmc = lpmcList; lpmc; lpmc = lpmc->lpmcNext)
	{
		ASSERT_READ_PTR(lpmc, sizeof(*lpmc), "lpmc: bad read pointer");
		ASSERTERROR(lpmc->hjswJumpWindow == NULL, 
			"lpmc->hjswJumpWindow != NULL");
		ASSERT_WRITE_PTR(lpmc->lpcntCounter, sizeof(*lpmc->lpcntCounter), 
			"lpmc->lpcntCounter: bad write pointer");

		*lpmc->lpcntCounter = dwAmount;
	}

    RETURN(hr);
}



//$--HrComputeCounterType-------------------------------------------------------
//  Helper function that computes the counter type value to use in the 
//  _PERF_COUNTER_DEFINITION structure defined in winperf.h.
// -----------------------------------------------------------------------------
static HRESULT HrComputeCounterType(	// RETURNS: HRESULT
	IN  COUNTERTYPE ctStatistic,		// the statistic this counter monitors
	IN  PERIODTYPE perPeriod,			// the period of this counter
	IN  DWORD dwUserCounterType,		// the CounterType (if ctStatistic is 
										// COUNTERTYPE_USER_DEFINED)
	OUT DWORD * lpdwCounterType)		// returned counter type
{
	HRESULT		hr				= NOERROR;
	DWORD		dwCounterType	= PERF_COUNTER_RAWCOUNT;

	DEBUGPRIVATE("HrComputeCounterType()\n");

	// Check the parameters.

	hr = CHK_HrComputeCounterType(
		ctStatistic, 
		perPeriod, 
		dwUserCounterType, 
		lpdwCounterType);
	if (FAILED(hr))
		RETURN(hr);

	switch (ctStatistic)
	{
		case COUNTERTYPE_MESSAGES_IN_FOLDER:
		case COUNTERTYPE_BYTES_IN_FOLDER:
		case COUNTERTYPE_ASSOCIATIONS:
			ASSERTERROR(perPeriod == PERIODTYPE_NONE, 
				"perPeriod != PERIODTYPE_NONE");
			dwCounterType = PERF_COUNTER_RAWCOUNT;
			break;

		case COUNTERTYPE_MESSAGES_ENTERING_FOLDER:
		case COUNTERTYPE_BYTES_ENTERING_FOLDER:
		case COUNTERTYPE_MESSAGES_LEAVING_FOLDER:
		case COUNTERTYPE_BYTES_LEAVING_FOLDER:
		case COUNTERTYPE_MESSAGES_TRANSFERRED_IN:
		case COUNTERTYPE_BYTES_TRANSFERRED_IN:
		case COUNTERTYPE_MESSAGES_TRANSFERRED_OUT:
		case COUNTERTYPE_BYTES_TRANSFERRED_OUT:
		case COUNTERTYPE_NDRS_IN:
		case COUNTERTYPE_NDRS_OUT:
			ASSERTERROR(perPeriod != PERIODTYPE_NONE, 
				"perPeriod == PERIODTYPE_NONE");
			if (perPeriod == PERIODTYPE_CONTINUOUS)
			{
				dwCounterType = PERF_COUNTER_COUNTER;
			}
			else
			{
				dwCounterType = PERF_COUNTER_RAWCOUNT;
			}
			break;

		case COUNTERTYPE_USER_DEFINED:
			dwCounterType = dwUserCounterType;
			break;

		default:
            hr = HR_LOG(E_FAIL);
			goto cleanup;
	}

	*lpdwCounterType = dwCounterType;

cleanup:
    RETURN(hr);
}



//$--HrAlignPointer-------------------------------------------------------------
//  Helper function that moves a pointer forward, if nescessary, so that it has 
//  a given alignment.  NOTE: the alignment must be a power of 2.
// -----------------------------------------------------------------------------
static HRESULT HrAlignPointer(		    // RETURNS: HRESULT
	IN     DWORD cbAlignment,			// the alignment desired
	IN OUT LPVOID * lppvPointer)		// the pointer to be aligned
{
	HRESULT			hr			= NOERROR;

	DEBUGPRIVATE("HrAlignPointer()\n");

	// Make sure the alignment is a power of 2.

	// Check the parameters.

	hr = CHK_HrAlignPointer(cbAlignment, lppvPointer);
	if (FAILED(hr))
		RETURN(hr);

	*lppvPointer = ((LPVOID)
		(((DWORD)(((LPBYTE)(*lppvPointer)) + cbAlignment - 1)) & 
		(~(cbAlignment - 1)))
		);

    RETURN(hr);
}



//$--FolderNotification---------------------------------------------------------
//  Function called by the notification engine when a folder is changed.  
//	It sets the "update request" variables to tell the folder update thread 
//	to update the counters associated with this folder.  In order to make this 
//	routine run faster it does not update the counters directly.  Since the 
//	notification engine only allows one notification routine per process to 
//	run at any one time, this improves efficiency.
// -----------------------------------------------------------------------------
static ULONG STDAPICALLTYPE FolderNotification(   // RETURNS: S_OK (always)
	IN LPVOID lpvContext,				// pointer to MONFOLDER structure
	IN DWORD cNotification,				// number of elements in following array
	IN LPNOTIFICATION lpNotifications)	// array of notification structures
{
	HRESULT			hr							= NOERROR;
	LPMONFOLDER		lpmf						= lpvContext;
	ULONG			cValues						= 0;
	LPSPropValue	lpProps						= NULL;

	DWORD			cBytesEnteringFolder		= 0;
	DWORD			cMessagesEnteringFolder		= 0;
	DWORD			cBytesLeavingFolder			= 0;
	DWORD			cMessagesLeavingFolder		= 0;
	BOOL			fUpdateFolderSize			= FALSE;

	DEBUGPRIVATE("FolderNotification()\n");

	// Check the parameters.

	hr = CHK_FolderNotification(lpvContext, cNotification, lpNotifications);
	if (FAILED(hr))
		return (S_OK);

	// If cNotification == 0, just take a snapshot of the folder.

	if (cNotification == 0)
	{
		fUpdateFolderSize = TRUE;
	}

	// Go through the list of notifications, counting up the number of bytes 
	// and messages that entered or left the folder.  Also figure out if the 
	// folder size changed so we know if we need to get the new size.

	for (; cNotification; cNotification--, lpNotifications++)
	{
		// If it's not a table notification then ignore it.

		if (lpNotifications->ulEventType == fnevTableModified)
		{
			// Handle different types of table notifications.

			switch (lpNotifications->info.tab.ulTableEvent)
			{
				case TABLE_ROW_ADDED:
					// Update counters for bytes and messages entering folder.

					if (lpmf->lpmcBytesEnteringFolder)
					{
						for (
							lpProps = lpNotifications->info.tab.row.lpProps, 
							cValues = lpNotifications->info.tab.row.cValues; 
							cValues; 
							cValues--, lpProps++)
						{
							if (lpProps->ulPropTag == PR_MESSAGE_SIZE)
							{
								cBytesEnteringFolder += lpProps->Value.ul;
								break;
							}
						}
						ASSERTWARNING(cValues, 
							"PR_MESSAGE_SIZE not found: 0 assumed");
					}

					cMessagesEnteringFolder++;

					fUpdateFolderSize = TRUE;
					break;

				case TABLE_ROW_DELETED:
					// Update counter for messages leaving folder.  The 
					// number of bytes leaving the folder will be calculated 
					// in the thread, since the notification engine doesn't 
					//  give us that information.

					cMessagesLeavingFolder++;

					fUpdateFolderSize = TRUE;
					break;

				case TABLE_SORT_DONE:
				case TABLE_RESTRICT_DONE:
				case TABLE_SETCOL_DONE:
					// Nothing really changed in the folder.
					break;

				default:
					// (fall through)
				case TABLE_ROW_MODIFIED:
				case TABLE_CHANGED:
				case TABLE_ERROR:
					fUpdateFolderSize = TRUE;
					break;
			} // end switch
		} // end if
	} // end for


	// Now set the "update request" variables for any counters that need 
	// updating.

	if (fUpdateFolderSize)
	{
		EnterCriticalSection(&lpmf->csCriticalSection);

		lpmf->fUpdateFolderSize = TRUE;
		if (cBytesEnteringFolder && lpmf->lpmcBytesEnteringFolder)
			lpmf->cBytesEnteringFolder += cBytesEnteringFolder;
		if (cMessagesEnteringFolder && lpmf->lpmcMessagesEnteringFolder)
			lpmf->cMessagesEnteringFolder += cMessagesEnteringFolder;
		if (cBytesLeavingFolder && lpmf->lpmcBytesLeavingFolder)
			lpmf->cBytesLeavingFolder += cBytesLeavingFolder;
		if (cMessagesLeavingFolder && lpmf->lpmcMessagesLeavingFolder)
			lpmf->cMessagesLeavingFolder += cMessagesLeavingFolder;

		LeaveCriticalSection(&lpmf->csCriticalSection);

		(void) HrWakeUpdateThread(lpmf->lpmcx);
	}

	return (S_OK);
}



//$--HrWakeUpdateThread---------------------------------------------------------
//  Helper function that signals the update thread to wake up.
// -----------------------------------------------------------------------------
static HRESULT HrWakeUpdateThread(
	IN LPMONCONTEXT lpmcx)
{
	HRESULT			hr				= NOERROR;
	BOOL			fItWorked		= TRUE;

	DEBUGPRIVATE("HrWakeUpdateThread()\n");

	// Check the parameters.

	hr = CHK_HrWakeUpdateThread(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

	fItWorked = SetEvent(lpmcx->hUpdateThreadWakeEvent);
	if (!fItWorked)
	{
        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

cleanup:
	RETURN(hr);
}



//$--HrRegisterNotification-----------------------------------------------------
//  Helper function that registers notification on folders.
// -----------------------------------------------------------------------------
static HRESULT HrRegisterNotification(  // RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx)              // pointer to perf mon context
{
    HRESULT            	hr             			= NOERROR;
    HRESULT          	hrT						= SUCCESS_SUCCESS;
	LPMONFOLDER			lpmf					= NULL;
	SPropTagArray		rgPropTagBytesInMessage	= {1, {PR_MESSAGE_SIZE}};
    ULONG               ulRowCount              = 0;

	DEBUGPRIVATE("HrRegisterNotification()\n");

	// Check the parameters.

	hr = CHK_HrRegisterNotification(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

	// Start monitoring for each folder in the list.

	for (lpmf = lpmcx->lpmfFolderList; lpmf; lpmf = lpmf->lpmfNext)
	{
		ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");
		ASSERTERROR(lpmf->lpmcx == lpmcx, "lpmf->lpmcx != lpmcx");
		ASSERTERROR(lpmf->lpFolder != NULL, "lpmf->lpFolder == NULL");
		ASSERTERROR(lpmf->ulConnection == 0, 
			"lpmf: folder already has notification set");
		ASSERTWARNING(
			lpmf->lpmcMessagesInFolder || 
			lpmf->lpmcBytesInFolder || 
			lpmf->lpmcMessagesEnteringFolder || 
			lpmf->lpmcBytesEnteringFolder || 
			lpmf->lpmcMessagesLeavingFolder || 
			lpmf->lpmcBytesLeavingFolder, 
			"lpmf: folder without counters");
		ASSERTWARNING(lpmf->lpTable == NULL, "lpmf->lpTable != NULL");
		ASSERTWARNING(lpmf->lpAdvise == NULL, "lpmf->lpAdvise != NULL");

		// Set notification on this folder.

		hrT = MAPICALL(lpmf->lpFolder)->GetContentsTable(lpmf->lpFolder, MAPI_DEFERRED_ERRORS, 
			&lpmf->lpTable);
	    if (FAILED(hrT))
	    {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
	    }

		hrT = MAPICALL(lpmf->lpTable)->SetColumns(lpmf->lpTable, 
			&rgPropTagBytesInMessage, 0);
	    if (FAILED(hrT))
	    {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
	    }

	    hrT = HrAllocAdviseSink(FolderNotification, lpmf, &lpmf->lpAdvise);
	    if (FAILED(hrT))
	    {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
	    }

	    hrT = MAPICALL(lpmf->lpTable)->Advise(
	        lpmf->lpTable,
	        fnevTableModified,
	        lpmf->lpAdvise,
	        &lpmf->ulConnection);
	    if (FAILED(hrT))
	    {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
	    }

        // Call GetRowCount to make Advise work correctly.

        hrT = MAPICALL(lpmf->lpTable)->GetRowCount(
            lpmf->lpTable, 
            0, 
            &ulRowCount);
	    if (FAILED(hrT))
	    {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
	    }

	} // end for

cleanup:
    RETURN(hr);
}



//$--HrLinkCounterIntoList------------------------------------------------------
//  Helper function that takes a MONCOUNTER structure and links it into the 
//  proper list in the MONCONTEXT or the specified MONFOLDER, depending on the 
//  counter type.
// -----------------------------------------------------------------------------
static HRESULT HrLinkCounterIntoList(	// RETURNS: return code
	IN LPMONCONTEXT lpmcx,				// pointer to perf mon context
	IN LPMONFOLDER lpmf,				// for folder-specific counters
	IN LPMONCOUNTER lpmc,				// counter structure to add to list
	IN COUNTERTYPE ctCounterType)		// type of counter this is
{
	MONCOUNTER **	lppmcPlaceToAdd		= NULL;
	HRESULT			hr					= NOERROR;

	DEBUGPRIVATE("HrLinkCounterIntoList()\n");

	// Check the parameters.

	hr = CHK_HrLinkCounterIntoList(lpmcx, lpmf, lpmc, ctCounterType);
	if (FAILED(hr))
		RETURN(hr);

	switch (ctCounterType)
	{
		case COUNTERTYPE_MESSAGES_IN_FOLDER:
			ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");
			lppmcPlaceToAdd = &lpmf->lpmcMessagesInFolder;
			break;
		case COUNTERTYPE_BYTES_IN_FOLDER:
			ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");
			lppmcPlaceToAdd = &lpmf->lpmcBytesInFolder;
			break;
		case COUNTERTYPE_MESSAGES_ENTERING_FOLDER:
			ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");
			lppmcPlaceToAdd = &lpmf->lpmcMessagesEnteringFolder;
			break;
		case COUNTERTYPE_BYTES_ENTERING_FOLDER:
			ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");
			lppmcPlaceToAdd = &lpmf->lpmcBytesEnteringFolder;
			break;
		case COUNTERTYPE_MESSAGES_LEAVING_FOLDER:
			ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");
			lppmcPlaceToAdd = &lpmf->lpmcMessagesLeavingFolder;
			break;
		case COUNTERTYPE_BYTES_LEAVING_FOLDER:
			ASSERT_WRITE_PTR(lpmf, sizeof(*lpmf), "lpmf: bad write pointer");
			lppmcPlaceToAdd = &lpmf->lpmcBytesLeavingFolder;
			break;
		case COUNTERTYPE_MESSAGES_TRANSFERRED_IN:
			lppmcPlaceToAdd = &lpmcx->lpmcMessagesTransferredIn;
			break;
		case COUNTERTYPE_BYTES_TRANSFERRED_IN:
			lppmcPlaceToAdd = &lpmcx->lpmcBytesTransferredIn;
			break;
		case COUNTERTYPE_MESSAGES_TRANSFERRED_OUT:
			lppmcPlaceToAdd = &lpmcx->lpmcMessagesTransferredOut;
			break;
		case COUNTERTYPE_BYTES_TRANSFERRED_OUT:
			lppmcPlaceToAdd = &lpmcx->lpmcBytesTransferredOut;
			break;
		case COUNTERTYPE_NDRS_IN:
			lppmcPlaceToAdd = &lpmcx->lpmcNDRsIn;
			break;
		case COUNTERTYPE_NDRS_OUT:
			lppmcPlaceToAdd = &lpmcx->lpmcNDRsOut;
			break;
		case COUNTERTYPE_ASSOCIATIONS:
			lppmcPlaceToAdd = &lpmcx->lpmcAssociations;
			break;
		default:
			hr = HR_LOG(E_FAIL);
			goto cleanup;
	}

	lpmc->lpmcNext = *lppmcPlaceToAdd;
	*lppmcPlaceToAdd = lpmc;

cleanup:
	RETURN(hr);
}



//$--HrVerifyLinkage------------------------------------------------------------
//  Verify that the Export value in the Linkage key for the gateway type 
//  exists and contains the gateway name.
// -----------------------------------------------------------------------------
static HRESULT HrVerifyLinkage(         // RETURNS: HRESULT
	IN LPMONCONTEXT lpmcx)              // pointer to perf mon context
{
	HRESULT		hr				        = NOERROR;
    DWORD       dwStatus                = ERROR_SUCCESS;
	TCHAR		szKeyName[MAX_PATH]     = {0};
	HKEY		hKey			        = NULL;
	DWORD		cch				        = 0;
    DWORD       dwType                  = 0;
    TCHAR       szExport[1000]          = {0};
    DWORD       cbExport                = sizeof(szExport);
    BOOL        fFound                  = FALSE;
    LPTSTR      psz                     = NULL;

	DEBUGPRIVATE("HrVerifyLinkage()\n");

	// Check the parameters.

	hr = CHK_HrVerifyLinkage(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

	// Create the registry key name from the gateway name.

	cch = wsprintf(
		szKeyName, 
		TEXT("SYSTEM\\CurrentControlSet\\Services\\%s\\Linkage"), 
		lpmcx->lpszObjectClass);
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
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

    // Read the value.

    dwStatus = RegQueryValueEx(
        hKey, 
        TEXT("Export"), 
        NULL, 
        &dwType, 
        szExport, 
        &cbExport);
	if (dwStatus != ERROR_SUCCESS || dwType != REG_MULTI_SZ)
    {
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

    // Look in the multi-valued value for the gateway name.

    fFound = FALSE;
    for (psz = szExport; *psz; psz += (strlen(psz) + 1))
    {
        if (!lstrcmpi(psz, lpmcx->lpszObjectName))
        {
            fFound = TRUE;
            break;
        }
    }

    // If we didn't find it then return an error.

    if (!fFound)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
	// Close the registry key (if it's open).

	if (hKey)
	{
		dwStatus = RegCloseKey(hKey);
        if (dwStatus != ERROR_SUCCESS)
            hr = HR_LOG(E_FAIL);
	}

    RETURN(hr);
}



//$--HrSaveSharedMemoryInRegistry-----------------------------------------------
//  Save a copy of the shared memory block to the registry so that 
//  GWPERF.DLL will be able to generate a blank set of counters when 
//  the gateway isn't running.
// -----------------------------------------------------------------------------
static HRESULT HrSaveSharedMemoryInRegistry(    // RETURNS: HRESULT
    IN LPMONCONTEXT lpmcx)                      // pointer to perf mon context
{
	HRESULT		hr				        = NOERROR;
    DWORD       dwStatus                = ERROR_SUCCESS;
	TCHAR		szKeyName[MAX_PATH]     = {0};
	HKEY		hKey			        = NULL;
	DWORD		cch				        = 0;
    BOOL        fSave_DataIsValid       = FALSE;

	DEBUGPRIVATE("HrSaveSharedMemoryInRegistry()\n");

	// Check the parameters.

	hr = CHK_HrSaveSharedMemoryInRegistry(lpmcx);
	if (FAILED(hr))
		RETURN(hr);

    // Save off the previous value of fDataIsValid.

    fSave_DataIsValid = lpmcx->lpmsmSharedMemory->fDataIsValid;

    // Create the registry key name from the gateway instance name.

	cch = wsprintf(
		szKeyName, 
		TEXT("SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters"), 
		lpmcx->lpszObjectName);
	ASSERTERROR(
		(cch * sizeof(*szKeyName)) < sizeof(szKeyName), 
		"wsprintf overflow: szKeyName");

	// Open the registry key.

	dwStatus = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE, 
		szKeyName, 
		0L, 
		KEY_SET_VALUE, 
		&hKey);
	if (dwStatus != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

	// Temporarily set the flag that the data in the shared memory 
    // is valid, so that it will be stored as valid in the registry.

	lpmcx->lpmsmSharedMemory->fDataIsValid = TRUE;

    // Write the value (calculate the size of the block that contains 
    // real data by adding the offset of the instance data and its size).

    dwStatus = RegSetValueEx(
        hKey, 
        TEXT("ObjectDefaultPerformanceData"), 
        0, 
        REG_BINARY, 
        (LPBYTE) lpmcx->lpmsmSharedMemory, 
        lpmcx->lpmsmSharedMemory->ibInstanceOffset + 
            lpmcx->lpmsmSharedMemory->cbInstanceSize);
	if (dwStatus != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

cleanup:
	// Restore the previous value of fDataIsValid.

	lpmcx->lpmsmSharedMemory->fDataIsValid = fSave_DataIsValid;

	// Close the registry key (if it's open).

	if (hKey)
	{
		dwStatus = RegCloseKey(hKey);
        if (dwStatus != ERROR_SUCCESS)
            hr = HR_LOG(E_FAIL);
	}

    RETURN(hr);
}
