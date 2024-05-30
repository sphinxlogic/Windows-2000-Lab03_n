// --cfgnotif.c-----------------------------------------------------------------
//
//  Routines to provide notification when a given extension data section has 
//  changed, and read the new data.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "attrname.h"
#include "cfgnotif.chk"

//
// Internal Function Declarations
//

static DWORD WINAPI PollThread(
    IN LPVOID lpvThreadParam);

static HRESULT HrUpdateAdviseNotify(
    IN      LPSPropValue    lpNewData,
    IN OUT  LPADVISENOTIFY  lpNotify);

static HRESULT HrDestroyAdviseNotify(
    IN OUT  LPADVISENOTIFY * lppNotify);

//
// Configuration API Routines
//

//$--HrCfgCreateAdviseObj-------------------------------------------------------
//  Begin monitoring of a MAPI session for changes to extension data.
//  This routine should be called once to create an advise object for a MAPI 
//  session that is being monitored.  Then, HrCfgAdvise() should be called 
//  once for each extension data section that is being monitored.
//  If nPollInterval == 0 then no monitoring thread is created, and the user 
//  must do polling manually by calling HrCfgPollAdviseObj().
// -----------------------------------------------------------------------------
HRESULT HrCfgCreateAdviseObj(               // RETURNS: HRESULT
    IN  LPMAPISESSION       lpSession,      // MAPI session to monitor
    IN  ULONG               nPollInterval,  // milliseconds between polling
    OUT LPADVISEOBJ *       lppAdviseObj)   // created advise object
{
    HRESULT                 hr              = NOERROR;
    LPADVISEOBJ             lpAdviseObj     = NULL;
	SECURITY_ATTRIBUTES     saEvent         = {0, NULL, TRUE};
    BOOL                    fCriticalSectionInitialized     = FALSE;

    hr = CHK_HrCfgCreateAdviseObj(
        lpSession, 
        nPollInterval, 
        lppAdviseObj);
    if (FAILED(hr))
        RETURN(hr);

    DEBUGPUBLIC("HrCfgCreateAdviseObj()\n");

    // Get memory for the advise object.

    hr = MAPIAllocateBuffer(sizeof(*lpAdviseObj), &lpAdviseObj);
    if (FAILED(hr))
        goto cleanup;

    ZeroMemory(lpAdviseObj, sizeof(*lpAdviseObj));

    // Store parameters in advise object.

    lpAdviseObj->lpSession = lpSession;
    lpAdviseObj->nPollInterval = nPollInterval;

    // Get an IMAPIProp interface on the current object.

    hr = HrOpenSessionObject(lpSession, &lpAdviseObj->lpCurrentObject);
    if (FAILED(hr))
        goto cleanup;

    // Get the property tag for USN-Changed.

    hr = HrCfgPropertyTagFromNameId(
        lpAdviseObj->lpCurrentObject, 
        NM_USN_CHANGED, 
        &lpAdviseObj->ulUSNChangedPropTag);
    if (FAILED(hr))
        goto cleanup;

    // If it came back without the property type then set it to PT_LONG.

    if (PROP_TYPE(lpAdviseObj->ulUSNChangedPropTag) == 0)
    {
        lpAdviseObj->ulUSNChangedPropTag = 
            CHANGE_PROP_TYPE(lpAdviseObj->ulUSNChangedPropTag, 
            PT_LONG);
    }

    // Get the property tag for Extension-Data.

    hr = HrCfgPropertyTagFromNameId(
        lpAdviseObj->lpCurrentObject, 
        NM_EXTENSION_DATA, 
        &lpAdviseObj->ulExtensionDataPropTag);
    if (FAILED(hr))
        goto cleanup;

    // If it came back without the property type then set it to PT_MV_BINARY.

    if (PROP_TYPE(lpAdviseObj->ulExtensionDataPropTag) == 0)
    {
        lpAdviseObj->ulExtensionDataPropTag = 
            CHANGE_PROP_TYPE(lpAdviseObj->ulExtensionDataPropTag, 
            PT_MV_BINARY);
    }

    // Create a critical section to synchronize access to the advise object.

    InitializeCriticalSection(&lpAdviseObj->csCriticalSection);
    fCriticalSectionInitialized = TRUE;

    // "Poll" the object to get the initial values of the extension data blobs.

    hr = HrCfgPollAdviseObj(lpAdviseObj);
    if (FAILED(hr))
        goto cleanup; 

    // Only create the thread if nPollInterval != 0.

    if (nPollInterval != 0)
    {
        // Create an event to stop the polling thread.

        lpAdviseObj->hPollThreadStop = CreateEvent(&saEvent, FALSE, FALSE, NULL);
    	if (lpAdviseObj->hPollThreadStop == NULL)
    	{
    		hr = HR_LOG(E_FAIL);
    		goto cleanup;
    	}

    	// Create the polling thread.

    	lpAdviseObj->hPollThread = CreateThread(
    	    NULL, 
    	    0, 
    	    PollThread, 
    	    lpAdviseObj, 
    	    0, 
    		&lpAdviseObj->ulPollThreadID);
    	if (lpAdviseObj->hPollThread == NULL)
    	{
    		hr = HR_LOG(E_FAIL);
    		goto cleanup;
    	}
    }

    // Set the return variable.

    *lppAdviseObj = lpAdviseObj;

cleanup:
    if (FAILED(hr) && lpAdviseObj)
    {
        CLOSEHANDLE(lpAdviseObj->hPollThreadStop);

        if (fCriticalSectionInitialized)
            DeleteCriticalSection(&lpAdviseObj->csCriticalSection);

        ULRELEASE(lpAdviseObj->lpCurrentObject);

        MAPIFREEBUFFER(lpAdviseObj);
    }

    RETURN(hr);
}

//$--HrCfgPollAdviseObj---------------------------------------------------------
//  Checks an advise object against what is stored in the DSA.  Calls the 
//  notification routines if there are any changes.
// -----------------------------------------------------------------------------
HRESULT HrCfgPollAdviseObj(                 // RETURNS: HRESULT
    IN  LPADVISEOBJ     lpAdviseObj)        // advise object to poll
{
    HRESULT             hr                  = NOERROR;
    ULONG               ulNewUSNChanged     = 0;
    LPSPropValue        lpNewExtensionData  = NULL;
    ULONG               cValues             = 0;
    LPADVISENOTIFY      lpAdviseNotify      = NULL;

    hr = CHK_HrCfgPollAdviseObj(
        lpAdviseObj);
    if (FAILED(hr))
        RETURN(hr);

    DEBUGPUBLIC("HrCfgPollAdviseObj()\n");

    // Lock the object against access by other threads.

    EnterCriticalSection(&lpAdviseObj->csCriticalSection);

    // Get the new USN-Changed from the DSA.  If the new USN-Changed is 
    // different from the one we have stored then something in the object 
    // has changed (possibly the extension data).  Note: the first time these 
    // statements are executed, USN-Changed will always have "changed" since 
    // the one we have stored starts out at 0.

    hr = HrMAPIGetPropLong(
        lpAdviseObj->lpCurrentObject, 
        lpAdviseObj->ulUSNChangedPropTag, 
        &ulNewUSNChanged);
    if (FAILED(hr))
        goto cleanup;

    // If USN-Changed is different then do the update.

    if (ulNewUSNChanged != lpAdviseObj->ulUSNChanged)
    {
        SizedSPropTagArray(1, ExtDataTag) = 
            {1, {lpAdviseObj->ulExtensionDataPropTag}};

        // Read the new extension data.

        hr = MAPICALL(lpAdviseObj->lpCurrentObject)->GetProps(
            lpAdviseObj->lpCurrentObject, 
            (LPSPropTagArray) &ExtDataTag, 
            0, 
            &cValues, 
            &lpNewExtensionData);

        // If the property was not found then allocate an empty multivalued 
        // binary property and store it as if it had been read from the 
        // extension data property.

        if (hr == MAPI_W_ERRORS_RETURNED && 
            cValues == 1 && 
            PROP_TYPE(lpNewExtensionData->ulPropTag) == PT_ERROR && 
            lpNewExtensionData->Value.err == MAPI_E_NOT_FOUND)
        {
            lpNewExtensionData->ulPropTag = lpAdviseObj->ulExtensionDataPropTag;
            lpNewExtensionData->Value.MVbin.cValues = 0;

            hr = MAPIAllocateMore(
                0, 
                lpNewExtensionData, 
                &lpNewExtensionData->Value.MVbin.lpbin);
            if (FAILED(hr))
                goto cleanup;

            hr = NOERROR;
        }

        // If there was any other error then return.

        if (FAILED(hr) || hr == MAPI_W_ERRORS_RETURNED)
            goto cleanup;

        // Loop for each ADVISENOTIFY and check to see if it's data has changed.
        // If it has, update it and call the callback routine.  After this 
        // loop is done, the blob pointers in the ADVISENOTIFY structures will 
        // point into the new extension data property, not the old one.  Then, 
        // the old one can be freed and replaced in the ADVISEOBJ structure 
        // by the new one.

        for (
            lpAdviseNotify = lpAdviseObj->lpNotifyList; 
            lpAdviseNotify; 
            lpAdviseNotify = lpAdviseNotify->lpNext)
        {
            hr = HrUpdateAdviseNotify(lpNewExtensionData, lpAdviseNotify);
            if (FAILED(hr))
                goto cleanup;
        }

        // Replace the old extension data property with the new one.

        MAPIFREEBUFFER(lpAdviseObj->lpExtensionData);
        lpAdviseObj->lpExtensionData = lpNewExtensionData;
        lpNewExtensionData = NULL;

        // Replace the old USN-Changed value with the new one.

        lpAdviseObj->ulUSNChanged = ulNewUSNChanged;
    }

cleanup:
    MAPIFREEBUFFER(lpNewExtensionData);

    // Unlock the object to allow access by other threads.

    LeaveCriticalSection(&lpAdviseObj->csCriticalSection);

    RETURN(hr);
}

//$--HrCfgDestroyAdviseObj------------------------------------------------------
//  End monitoring of a MAPI session.  This routine calls HrCfgUnadvise() for 
//  any extension data sections that are actively being monitored.
// -----------------------------------------------------------------------------
HRESULT HrCfgDestroyAdviseObj(              // RETURNS: HRESULT
    IN  LPADVISEOBJ         lpAdviseObj)    // advise object to destroy
{
    HRESULT             hr                  = NOERROR;
    HRESULT             hrT                 = NOERROR;
    BOOL                fItWorked           = TRUE;
    DWORD               dwStatus            = 0;

    DEBUGPUBLIC("HrCfgDestroyAdviseObj()\n");

    hr = CHK_HrCfgDestroyAdviseObj(
        lpAdviseObj);
    if (FAILED(hr))
        RETURN(hr);

    if (lpAdviseObj)
    {
        // Signal the thread to stop and then release the signal event.

        if (lpAdviseObj->hPollThreadStop)
        {
            fItWorked = SetEvent(lpAdviseObj->hPollThreadStop);
            if (!fItWorked)
            {
                hr = HR_LOG(E_FAIL);
            }
            CLOSEHANDLE(lpAdviseObj->hPollThreadStop);
        }

        // Wait for thread to terminate and then release it's handle.

        if (lpAdviseObj->hPollThread)
        {
            dwStatus = WaitForSingleObject(lpAdviseObj->hPollThread, INFINITE);
            if (dwStatus != WAIT_OBJECT_0)
            {
                hr = HR_LOG(E_FAIL);
            }
            CLOSEHANDLE(lpAdviseObj->hPollThread);
        }

        // Free the notification structures.

        while (lpAdviseObj->lpNotifyList)
        {
            hrT = HrDestroyAdviseNotify(&lpAdviseObj->lpNotifyList);
            if (FAILED(hrT))
            {
                hr = hrT;
            }
        }

        // Delete the critical section.

        DeleteCriticalSection(&lpAdviseObj->csCriticalSection);

        // Release the IMAPIProp interface.

        ULRELEASE(lpAdviseObj->lpCurrentObject);

        // Free the extension data property.

        MAPIFREEBUFFER(lpAdviseObj->lpExtensionData);

        // Free the advise object itself.

        MAPIFREEBUFFER(lpAdviseObj);
    }

    RETURN(hr);
}

//$--HrCfgAdvise----------------------------------------------------------------
//  Begin monitoring of an extension data section.  When the extension data 
//  changes, the specified callback routine is called.  Note: The callback 
//  routine will be called once from hrCfgAdvise() to set the initial extension 
//  data values.
// -----------------------------------------------------------------------------
HRESULT HrCfgAdvise(                        // RETURNS: HRESULT
    IN  LPADVISEOBJ         lpAdviseObj,    // advise object
    IN  LPSTR              lpszSection,    // name of extension data section
    IN  LPADVISECALLBACK    lpfnCallback,   // function to call on changes
    IN  LPVOID              lpvUserContext) // user-defined context
{
    HRESULT                 hr              = NOERROR;
    LPADVISENOTIFY          lpNotify        = NULL;
    ULONG                   cchSection      = 0;
    ULONG                   cchActual       = 0;

    DEBUGPUBLIC("HrCfgAdvise()\n");

    hr = CHK_HrCfgAdvise(
        lpAdviseObj, 
        lpszSection, 
        lpfnCallback, 
        lpvUserContext);
    if (FAILED(hr))
        RETURN(hr);

    // Allocate memory for the ADVISENOTIFY structure.

    hr = MAPIAllocateBuffer(
        sizeof(*lpNotify), 
        &lpNotify);
    if (FAILED(hr))
        goto cleanup;
    ZeroMemory(lpNotify, sizeof(*lpNotify));

    // Get the number of characters in the section name.

    cchSection = lstrlen(lpszSection);

    // Allocate memory for the LPSTR section name and copy the section 
    // name into it.

    hr = MAPIAllocateMore(
        cchSection + 1, 
        lpNotify, 
        &lpNotify->lpszOwnerTag);
    if (FAILED(hr))
        goto cleanup;

    lstrcpy(lpNotify->lpszOwnerTag, lpszSection);

    // Allocate memory for the UNICODE section name, and copy the section 
    // name into it, converting to UNICODE.

    hr = MAPIAllocateMore(
        (cchSection + 1) * sizeof(WCHAR), 
        lpNotify, 
        &lpNotify->lpwszOwnerTag);
    if (FAILED(hr))
        goto cleanup;

	SetLastError(ERROR_SUCCESS);

    cchActual = wsprintfW(lpNotify->lpwszOwnerTag, L"%hs", lpszSection);
	if (GetLastError() != ERROR_SUCCESS || cchActual != cchSection)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

    // Fill in the structure members.

    lpNotify->lpfnCallback = lpfnCallback;
    lpNotify->lpvUserContext = lpvUserContext;

    // Lock the object against access by other threads.

    EnterCriticalSection(&lpAdviseObj->csCriticalSection);

    // Cause the callback routine to be called for the first time.

    lpNotify->fFirstTime = TRUE;
    hr = HrUpdateAdviseNotify(lpAdviseObj->lpExtensionData, lpNotify);

    // NOTE: Don't check the return value for failure until after 
    // we leave the critical section.

    // Link the structure into the object's list.

    if (SUCCEEDED(hr))
    {
        lpNotify->lpNext = lpAdviseObj->lpNotifyList;
        lpAdviseObj->lpNotifyList = lpNotify;
    }

    // Unlock the object to allow access by other threads.

    LeaveCriticalSection(&lpAdviseObj->csCriticalSection);

cleanup:
    if (FAILED(hr))
    {
        MAPIFREEBUFFER(lpNotify);
    }

    RETURN(hr);
}

//$--HrCfgUnadvise--------------------------------------------------------------
//  End monitoring of an extension data section.
// -----------------------------------------------------------------------------
HRESULT HrCfgUnadvise(                      // RETURNS: HRESULT
    IN  LPADVISEOBJ         lpAdviseObj,    // advise object
    IN  LPSTR              lpszSection)    // name of extension data section
{
    HRESULT                 hr              = NOERROR;
    LPADVISENOTIFY *        lppNotify       = NULL;
    BOOL                    fFound          = FALSE;

    DEBUGPUBLIC("HrCfgAdvise()\n");

    hr = CHK_HrCfgUnadvise(
        lpAdviseObj, 
        lpszSection);
    if (FAILED(hr))
        RETURN(hr);

    // Lock the object against access by other threads.

    EnterCriticalSection(&lpAdviseObj->csCriticalSection);

    // Search the list of ADVISENOTIFY structures for the section name we want.

    for (
        lppNotify = &lpAdviseObj->lpNotifyList; 
        *lppNotify; 
        lppNotify = &((*lppNotify)->lpNext))
    {
        if (!lstrcmp(lpszSection, (*lppNotify)->lpszOwnerTag))
        {
            // Found it, so destroy it.

            hr = HrDestroyAdviseNotify(lppNotify);

            fFound = TRUE;
            break;
        }
    }

    if (!fFound)
    {
        hr = HR_LOG(E_FAIL);
    }

    // Unlock the object to allow access by other threads.

    LeaveCriticalSection(&lpAdviseObj->csCriticalSection);

    RETURN(hr);
}

//
// Local Helper Routines
//

//$--PollThread-----------------------------------------------------------------
//  Function that is called as a seperate thread.  It wakes up periodically 
//  and polls the extension data sections.  If any have changed, it calls 
//  the routine registered for that section.
// -----------------------------------------------------------------------------
static DWORD WINAPI PollThread(             // RETURNS: error code
    IN  LPVOID          lpvThreadParam)     // pointer to advise object
{
    HRESULT             hr                  = NOERROR;
	LPADVISEOBJ         lpAdviseObj         = lpvThreadParam;
    BOOL                fDone               = FALSE;
    DWORD               dwStatus            = 0;

    DEBUGPRIVATE("PollThread()\n");

    hr = CHK_PollThread(
        lpvThreadParam);
    if (FAILED(hr))
        RETURN(hr);

    // Main loop: sleep, poll object.

    while (!fDone)
    {
        // Sleep and wait for the timer.

        dwStatus = WaitForSingleObject(
            lpAdviseObj->hPollThreadStop, 
            lpAdviseObj->nPollInterval);

		switch (dwStatus)
		{
			case WAIT_TIMEOUT:
                // Poll the object.
                hr = HrCfgPollAdviseObj(lpAdviseObj);
                if (FAILED(hr))
                    goto cleanup;
                break;

			case WAIT_OBJECT_0:
                // Thread terminate request.
				fDone = TRUE;
				break;

			default:
				// Some kind of error.
                hr = HR_LOG(E_FAIL);
                goto cleanup;
		}
    }

cleanup:
    return(ERROR_SUCCESS);
}

//$--HrUpdateAdviseNotify-------------------------------------------------------
//  Compare new extension data property with the old one for changes to the 
//  blob defined by the ADVISENOTIFY structure.  If it has changed, then call 
//  the callback routine.  In any case, point the ADVISENOTIFY structure at the 
//  new extension data blob, so that the old one may be freed.
// -----------------------------------------------------------------------------
static HRESULT HrUpdateAdviseNotify(        // RETURNS: HRESULT
    IN      LPSPropValue    lpNewData,      // new extension data
    IN OUT  LPADVISENOTIFY  lpNotify)       // notification structure
{
    HRESULT             hr                  = NOERROR;
    LPSBinary           lpNewBlobArray      = NULL;
    ULONG               cNewBlobArray       = 0;
    ULONG               iBlob               = 0;
    LPBYTE              lpbNewBlob          = NULL;
    ULONG               cbNewBlob           = 0;
    LPSPropValue        lpUnpackedProps     = NULL;
    ULONG               cUnpackedProps      = 0;
    LPSTR              lpszUnpackedName    = NULL;

    DEBUGPRIVATE("HrUpdateAdviseNotify()\n");

    hr = CHK_HrUpdateAdviseNotify(
        lpNewData, 
        lpNotify);
    if (FAILED(hr))
        RETURN(hr);

    // Find the owner tag in the new extension data property array.

    if (lpNewData)
    {
        lpNewBlobArray = lpNewData->Value.MVbin.lpbin;
        cNewBlobArray = lpNewData->Value.MVbin.cValues;

        for (iBlob = 0; iBlob < cNewBlobArray; iBlob++)
        {
            if (!wcscmp(
                lpNotify->lpwszOwnerTag, 
                (LPWSTR) lpNewBlobArray[iBlob].lpb))
            {
                lpbNewBlob = lpNewBlobArray[iBlob].lpb;
                cbNewBlob = lpNewBlobArray[iBlob].cb;
            }
        }
    }

    // If the blob has changed then unpack the properties and call the 
    // callback routine.

    if (lpNotify->fFirstTime || 
        lpNotify->cbBlob != cbNewBlob || 
        (lpNotify->lpbBlob && 
        lpbNewBlob && 
        memcmp(lpNotify->lpbBlob, lpbNewBlob, cbNewBlob)))
    {
        // If the new blob exists then unpack the properties.
        // Otherwise, use a NULL pointer for a non-existant blob.

        if (lpbNewBlob)
        {
            hr = HrCfgUnpackData(
                cbNewBlob, 
                lpbNewBlob, 
                &lpszUnpackedName, 
                &cUnpackedProps, 
                &lpUnpackedProps);
            if (FAILED(hr))
                goto cleanup;
        }

        // Call the callback routine.

        hr = (*lpNotify->lpfnCallback)(
            lpNotify->lpvUserContext, 
            lpNotify->lpwszOwnerTag, 
            cUnpackedProps, 
            lpUnpackedProps);
        if (FAILED(hr))
            goto cleanup;

        // If the callback succeeded then zero out the unpacked property 
        // variables so we don't free them (that's the user's responsiblity).

        cUnpackedProps = 0;
        lpUnpackedProps = NULL;

        // Callback has now been called at least once.

        lpNotify->fFirstTime = FALSE;
    }

    // Replace the old blob with the new one in the ADVISENOTIFY structure.

    lpNotify->lpbBlob = lpbNewBlob;
    lpNotify->cbBlob = cbNewBlob;

cleanup:
    MAPIFREEBUFFER(lpszUnpackedName);
    if (FAILED(hr))
    {
        MAPIFREEBUFFER(lpUnpackedProps);
    }

    RETURN(hr);
}

//$--HrDestroyAdviseNotify------------------------------------------------------
//  Destroy an ADVISENOTIFY structure and remove it from the linked list.
//  This routine takes as its argument the address of a pointer to the 
//  structure to be destroyed and returns with that pointer pointing to 
//  the next structure in the linked list.
// -----------------------------------------------------------------------------
static HRESULT HrDestroyAdviseNotify(       // RETURNS: HRESULT
    IN OUT  LPADVISENOTIFY * lppNotify)     // address of ptr to ADVISENOTIFY
{
    HRESULT             hr                  = NOERROR;
    LPADVISENOTIFY      lpNotify            = NULL;

    DEBUGPRIVATE("HrDestroyAdviseNotify()\n");

    hr = CHK_HrDestroyAdviseNotify(
        lppNotify);
    if (FAILED(hr))
        RETURN(hr);

    // Save pointer to the structure.

    lpNotify = *lppNotify;

    // Take structure out of list, by making whatever pointed to it point 
    // to the next thing on the list.

    *lppNotify = lpNotify->lpNext;

    // Free the structure.

    MAPIFREEBUFFER(lpNotify);

    RETURN(hr);
}
