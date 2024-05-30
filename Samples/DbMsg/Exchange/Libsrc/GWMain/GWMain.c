// --gwmain.c-------------------------------------------------------------------
// 
//  Logon/logoff a gateway.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#define USES_IID_IMailUser
#include "edk.h"
#include "gwmain.h"

#define NOTIFY_TIMEOUT  60000

static ULONG         ulNewMailAdvise = 0xFFFFFFFFU;

static HANDLE        hNewMailEvent   = NULL;  // new mail event
static LPMAPISESSION lpSession       = NULL;  // session pointer
static LPMDB         lpStore         = NULL;  // message store pointer
static LPMAPIFOLDER  lpRootFolder    = NULL;  // root folder pointer
static LPMAPIFOLDER  lpMtsInFolder   = NULL;  // MTS-IN folder pointer
static LPMAPIFOLDER  lpMtsOutFolder  = NULL;  // MTS-OUT folder pointer
static LPADRBOOK     lpAdrBook       = NULL;  // pointer to address book
static ULONG         cbGalEid        = 0;     // count of bytes in GAL entry ID
static LPENTRYID     lpGalEid        = NULL;  // pointer to GAL entry ID
static LPABCONT      lpGalABCont     = NULL;  // pointer to GAL object

static BOOL          IsInitMAPI      = FALSE; // MAPI Initialized
static BOOL          IsMAPILogon     = FALSE; // MAPI Logon

CRITICAL_SECTION     csNewMailList   = {0};
CRITICAL_SECTION     csNewFileList   = {0};

static CHAR         szServerName[MAX_COMPUTERNAME_LENGTH+1] = {0};

HANDLE               hNewMailThread  = NULL;  // new mail thread
HANDLE               hNewFileThread  = NULL;  // new file thread

DWORD                dwNewMailTimeout = NOTIFY_TIMEOUT;
DWORD                dwNewFileTimeout = NOTIFY_TIMEOUT;

//$--GetGWExchangeServerName------------------------------------------------------
//  Get Exchange server name.
// -----------------------------------------------------------------------------
LPSTR GetGWExchangeServerName(void)
{
    DEBUGPUBLIC("GetGWExchangeServerName()\n");

    return(szServerName);
}

//$--GetGWSession-------------------------------------------------------------
//  Get MAPI session pointer.
// -----------------------------------------------------------------------------
LPMAPISESSION GetGWSession(void)
{
    DEBUGPUBLIC("GetGWSession()\n");

    return(lpSession);
}

//$--GetGWDefaultStore------------------------------------------------------------
//  Get default store pointer.
// -----------------------------------------------------------------------------
LPMDB GetGWDefaultStore(void)
{
    DEBUGPUBLIC("GetGWDefaultStore()\n");

    return(lpStore);
}

//$--GetGWRootFolder-------------------------------------------------------------
//  Get root folder pointer.
// -----------------------------------------------------------------------------
LPMAPIFOLDER GetGWRootFolder(void)
{
    DEBUGPUBLIC("GetGWRootFolder()\n");

    return(lpRootFolder);
}

//$--GetGWMtsInFolder-------------------------------------------------------------
//  Get MTS-IN folder pointer.
// -----------------------------------------------------------------------------
LPMAPIFOLDER GetGWMtsInFolder(void)
{
    DEBUGPUBLIC("GetGWMtsInFolder()\n");

    return(lpMtsInFolder);
}

//$--GetGWMtsOutFolder------------------------------------------------------------
//  Get MTS-OUT folder pointer.
// -----------------------------------------------------------------------------
LPMAPIFOLDER GetGWMtsOutFolder(void)
{
    DEBUGPUBLIC("GetGWMtsOutFolder()\n");

    return(lpMtsOutFolder);
}

//$--GetGWGALEntryIdSize--------------------------------------------------------------
//  Get count of bytes in GAL entry ID.
// -----------------------------------------------------------------------------
ULONG GetGWGALEntryIdSize(void)
{
    DEBUGPUBLIC("GetGWGALEntryIdSize()\n");

    return(cbGalEid);
}

//$--GetGWGALEntryId------------------------------------------------------------------
//  Get GAL entry ID pointer.
// -----------------------------------------------------------------------------
LPENTRYID GetGWGALEntryId(void)
{
    DEBUGPUBLIC("GetGWGALEntryId()\n");

    return(lpGalEid);
}

//$--GetAdrBookPtr--------------------------------------------------------------
//  Get address book pointer pointer.
// -----------------------------------------------------------------------------
LPADRBOOK GetAdrBookPtr(void)
{
    DEBUGPUBLIC("GetAdrBookPtr()\n");

    return(lpAdrBook);
}

//$--GetGWGAL------------------------------------------------------------------
//  Get GAL pointer.
// -----------------------------------------------------------------------------
LPABCONT GetGWGAL(void)
{
    DEBUGPUBLIC("GetGWGAL()\n");

    return(lpGalABCont);
}

//$--GetGWNewMailEvent------------------------------------------------------------
//  Get new mail event.
// -----------------------------------------------------------------------------
HANDLE GetGWNewMailEvent(void)
{
    DEBUGPUBLIC("GetGWNewMailEvent()\n");

    return(hNewMailEvent);
}

//$--GetGWNewMailStatus-----------------------------------------------------------
//  Get new mail status.
// -----------------------------------------------------------------------------
BOOL GetGWNewMailStatus(void)
{
    BOOL  IsNewMail = TRUE;
    DWORD dw        = 0;

    DEBUGPUBLIC("GetGWNewMailStatus()\n");

    if(hNewMailEvent == NULL)
    {
        IsNewMail = FALSE;
        goto cleanup;
    }

    dw = WaitForSingleObject(hNewMailEvent, 0); 

    if((dw != WAIT_OBJECT_0) && (dw != WAIT_ABANDONED))
    {
        HRESULT hr = HR_LOG(E_FAIL);

        IsNewMail = FALSE;
    }

cleanup:

    return(IsNewMail);
}

//$--ScNewMailHandler-----------------------------------------------------------
//  Handle the arrival of new messages.
// -----------------------------------------------------------------------------
static SCODE STDAPICALLTYPE ScNewMailHandler(       // RETURNS: status code
    IN LPVOID lpvContext,                           // pointer to context
    IN ULONG cNotification,                         // count of notifications
    IN LPNOTIFICATION lpNotifications)              // pointer to notifications
{
    DEBUGPRIVATE("ScNewMailHandler()\n");

    if((hNewMailEvent != NULL) && (!SetEvent(hNewMailEvent)))
    {
        HRESULT hr = HR_LOG(E_FAIL);
    }

    return(0);
}

//$--HrGWWaitForStop----------------------------------------------------
//  Wait for the gateway to stop.
// -----------------------------------------------------------------------------
HRESULT HrGWWaitForStop(        // RETURNS: return code
    void)                               // no arguments
{
    HRESULT hr          = NOERROR;
    HANDLE  hObjects[2] = {0};
    DWORD   dwT         = WAIT_FAILED;
    ULONG   i           = 0;

    DEBUGPUBLIC("HrGWWaitForStop()\n");

    if(hNewMailThread != NULL)
    {
        hObjects[i++] = hNewMailThread;
    }

    if(hNewFileThread != NULL)
    {
        hObjects[i++] = hNewFileThread;
    }

    if(i > 0)
    {
        dwT = WaitForMultipleObjects(i, hObjects, TRUE, INFINITE);

        if(dwT == WAIT_FAILED)
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    RETURN(hr);
}

//$--HrGetArbValue--------------------------------------------------------------
//  Get an arbitrary value - allocating memory to hold it.
// -----------------------------------------------------------------------------
static HRESULT HrGetArbValue(       // RETURNS: return code
    IN HKEY hk,                     // the key.
    IN LPSTR pszValue,              // value name in key.
    OUT DWORD * pType,              // where to put type info.
    OUT DWORD * pcb,                // where to put byte count info.
    OUT LPVOID * ppData)            // where to put the data.
{
    HRESULT hr   = E_FAIL;
    LONG    lRet = 0;

    DEBUGPRIVATE("HrGetArbValue()\n");

    *ppData = NULL;

    //
    //  Get its size.
    //
    lRet = RegQueryValueEx(
        hk,
        pszValue,
        NULL,
        pType,
        NULL,
        pcb);

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    //  Allocate memory for it.
    //

    *ppData = GlobalAlloc(GPTR, *pcb);

    if(*ppData == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // get the current value
    //
    lRet = RegQueryValueEx(hk, pszValue, NULL, pType, *ppData, pcb);

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = NOERROR;

cleanup:

    if(FAILED(hr))
    {
        if(ppData != NULL)
        {
            GLOBALFREE(*ppData);
        }
    }

    RETURN(hr);
}

//$--HrCheckExchangeRunning-----------------------------------------------------
//  Check if the Exchange server is running.
// -----------------------------------------------------------------------------
static HRESULT HrCheckExchangeRunning(      // RETURNS: return code
    IN LPSTR lpszServiceName)
{
    HRESULT hr                          = NOERROR;
    LONG    lRet                        = 0;
    DWORD   dwService                   = 0;
    DWORD   dwCurrentState              = 0;
	DWORD   dwType                      = 0;
	DWORD   cbOrig                      = 0;
    LPSTR  lpszServerName              = NULL;
	HKEY    hkParameters                = INVALID_HANDLE_VALUE;
	CHAR   szParametersKey[MAX_PATH+1] = {0};

    //
    //  Open the parameters key.
    //

	sprintf(
	    szParametersKey,
	    "SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	    lpszServiceName);

    lRet = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        szParametersKey, 
        0,
        KEY_READ,
        &hkParameters);

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    //  Get the Exchange server name.
    //

    hr = HrGetArbValue(
        hkParameters, "HomeDSA", &dwType, &cbOrig, (LPVOID) &lpszServerName);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Copy Exchange server name.
    //

    lstrcpyn(szServerName, lpszServerName, MAX_COMPUTERNAME_LENGTH);
    szServerName[MAX_COMPUTERNAME_LENGTH] = 0;

// TODO: remove "#ifndef" and "#endif"
#ifndef DEBUG
    hr = HrGetExchangeStatus(
        lpszServerName,
        &dwService,
        &dwCurrentState);

    if(FAILED(hr))
    {
		MODULE_ERROR1(
		    "The Exchange server on %s is not running!",
		    lpszServerName);

	    hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
#endif

cleanup:

    GLOBALFREE(lpszServerName);

    if(hkParameters != INVALID_HANDLE_VALUE)
    {
        HR_LOG(HRESULT_FROM_WIN32(RegCloseKey(hkParameters)));
    }

    RETURN(hr);
}

//$--HrInternalGatewayLogon-----------------------------------------------------
//  Logon to the gateway.
// -----------------------------------------------------------------------------
static HRESULT HrInternalGatewayLogon(void)  // RETURNS: return code
{
    HRESULT         hr               = NOERROR;

    ULONG           cValues          = 0;
    LPSPropValue    lpProp           = NULL;

    ULONG           ulObjType        = 0;

    ULONG           cbStoreEid       = 0;
    LPENTRYID       lpStoreEid       = NULL;

    SPropTagArray   rgMtsInEntryId   = { 1, { PR_GW_MTSIN_ENTRYID } };
    ULONG           cbMtsInEid       = 0;
    LPENTRYID       lpMtsInEid       = NULL;

    SPropTagArray   rgMtsOutEntryId  = { 1, { PR_GW_MTSOUT_ENTRYID } };
    ULONG           cbMtsOutEid      = 0;
    LPENTRYID       lpMtsOutEid      = NULL;

    CHAR           szGatewayName[MAX_SERVICE_NAME_LENGTH+1] = {0};

	MAPIINIT_0		MapiInit         = { 0 };

    ULONG           ulFlags          = 0;

    LPMAPIADVISESINK lpAdvise        = NULL;

    CHAR           szProfileName[MAX_PATH+1] = {0};

    BOOL            IsProfileCreated = FALSE;

    DEBUGPRIVATE("HrInternalGatewayLogon()\n");

    //
    // Initialize critical section for new mail list.
    //

    InitializeCriticalSection(&csNewMailList);

    //
    // Initialize critical section for new file list.
    //

    InitializeCriticalSection(&csNewFileList);

    //
    // Get gateway service name.
    //

    hr = HrServiceGetName(
        szGatewayName);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Check if Exchange is running.
    //

    hr = HrCheckExchangeRunning(
        szGatewayName);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Create the event object. The new mail event handler function signals
    // this event when it receives a new mail notification.

    hNewMailEvent = CreateEvent(
        NULL,    // no security attributes
        FALSE,   // auto-reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if(hNewMailEvent == (HANDLE)NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    MapiInit.ulVersion = MAPI_INIT_VERSION;

    ulFlags = MAPI_NEW_SESSION|MAPI_EXTENDED|MAPI_NO_MAIL;

  	if(FIsService())
	{	// Services need special initialization.
  		MapiInit.ulFlags = MAPI_NT_SERVICE;
		ulFlags |= MAPI_NT_SERVICE;
	}

    hr = MAPIInitialize(&MapiInit);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    IsInitMAPI = TRUE;

    hr = HrCreateProfileName(
        szGatewayName,
        MAX_PATH+1,
        szProfileName);

    if(FAILED(hr))
    {
        goto cleanup;
    }

	hr = HrCreateGatewayProfile(szGatewayName, szProfileName);

	if(hr == E_ACCESSDENIED)
	{
		MODULE_WARNING(
			"Could not create profile since previous profile with same name "
			"is still logged on.");
        hr = NOERROR;
	}
    else if(FAILED(hr))
    {
        goto cleanup;
    }
    else
    {
        IsProfileCreated = TRUE;
    }

    // Create a MAPI session
    hr = MAPILogonEx(
        0,
        szProfileName,
        NULL,
        ulFlags,
        &lpSession);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    IsMAPILogon = TRUE;

#define PSESSION ((LPMAPISESSION)lpSession)

    // Get entry ID of message store
    hr = HrMAPIFindDefaultMsgStore(lpSession, &cbStoreEid, &lpStoreEid);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = MAPICALL(PSESSION)->OpenMsgStore(
        PSESSION,
        (ULONG)0,
        cbStoreEid,
        lpStoreEid,
        NULL,
        MAPI_DEFERRED_ERRORS | MDB_NO_DIALOG | MDB_WRITE,
        &lpStore);

#undef PSESSION

    if(FAILED(hr))
    {
        goto cleanup;
    }

    // Get the root folder in the default message store
    hr = MAPICALL(lpStore)->OpenEntry(
        lpStore,
        (ULONG)0,
        NULL,
        NULL,
        MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
        &ulObjType,
        (LPUNKNOWN FAR *) &lpRootFolder);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    // Get the MTS-IN entry ID property. 
    hr = MAPICALL(lpStore)->GetProps(
        lpStore,
        &rgMtsInEntryId,
        fMapiUnicode,
        &cValues,
        &lpProp);

    if(FAILED(hr))
    {
        lpProp = NULL;

        goto cleanup;
    }

    // Check to make sure we got the right property.
    if (lpProp->ulPropTag != PR_GW_MTSIN_ENTRYID)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cbMtsInEid = lpProp->Value.bin.cb;

    hr = MAPIAllocateBuffer(cbMtsInEid, (void **)&lpMtsInEid);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    // Copy MTS-IN Entry ID
    CopyMemory(lpMtsInEid,lpProp->Value.bin.lpb,cbMtsInEid);

    MAPIFREEBUFFER(lpProp);

    // Get the MTS-OUT entry ID property. 
    hr = MAPICALL(lpStore)->GetProps(
        lpStore,
        &rgMtsOutEntryId,
        fMapiUnicode,
        &cValues,
        &lpProp);

    if(FAILED(hr))
    {
        lpProp = NULL;

        goto cleanup;
    }

    // Check to make sure we got the right property.
    if(lpProp->ulPropTag != PR_GW_MTSOUT_ENTRYID)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cbMtsOutEid = lpProp->Value.bin.cb;

    hr = MAPIAllocateBuffer(cbMtsOutEid, (void **)&lpMtsOutEid);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    // Copy MTS-OUT Entry ID
    CopyMemory(lpMtsOutEid,lpProp->Value.bin.lpb,cbMtsOutEid);

    MAPIFREEBUFFER(lpProp);

    // Open the MTS-IN folder in the root folder
    hr = MAPICALL(lpRootFolder)->OpenEntry(
        lpRootFolder,
        cbMtsInEid,
        lpMtsInEid,
        NULL,
        MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
        &ulObjType,
        (LPUNKNOWN FAR *) &lpMtsInFolder);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    if(ulObjType != MAPI_FOLDER)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Open the MTS-OUT folder in the root folder
    hr = MAPICALL(lpRootFolder)->OpenEntry(
        lpRootFolder,
        cbMtsOutEid,
        lpMtsOutEid,
        NULL,
        MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
        &ulObjType,
        (LPUNKNOWN FAR *) &lpMtsOutFolder);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    if(ulObjType != MAPI_FOLDER)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Open the Address Book
    hr = MAPICALL(lpSession)->OpenAddressBook(
        lpSession,
        0,
        NULL, 
        AB_NO_DIALOG,
        &lpAdrBook);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = HrFindExchangeGlobalAddressList(
        lpAdrBook,
        &cbGalEid,
        &lpGalEid);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrAllocAdviseSink(ScNewMailHandler, NULL, &lpAdvise);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = MAPICALL(lpStore)->Advise(
        lpStore,
        cbMtsOutEid,
        lpMtsOutEid,
        fnevNewMail,
        lpAdvise,
        &ulNewMailAdvise);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    // Open the global recipient container
    hr = MAPICALL(lpAdrBook)->OpenEntry(
        lpAdrBook, 
        cbGalEid,
        lpGalEid,
        NULL,
        MAPI_DEFERRED_ERRORS,
        &ulObjType,
        (LPUNKNOWN FAR *)&lpGalABCont);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    if(ulObjType != MAPI_ABCONT)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    if(IsProfileCreated == TRUE)
    {
        // Mark profile for deletion
        HR_LOG(HrRemoveProfile(szProfileName));
    };

    ULRELEASE(lpAdvise);

    MAPIFREEBUFFER(lpProp);

    if(FAILED(hr))
    {
        if((ulNewMailAdvise != 0xFFFFFFFFL) && (lpStore != NULL))
        {
            MAPICALL(lpStore)->Unadvise(lpStore, ulNewMailAdvise);
        }

        if(hNewMailEvent != NULL)
        {
            if(!CloseHandle(hNewMailEvent))
            {
                hr = HR_LOG(E_FAIL);
            }
        }


        ULRELEASE(lpGalABCont);

        ULRELEASE(lpAdrBook);

        ULRELEASE(lpMtsInFolder);

        ULRELEASE(lpMtsOutFolder);

        ULRELEASE(lpRootFolder);

        ULRELEASE(lpStore);

        MAPIFREEBUFFER(lpGalEid);

        if(IsMAPILogon == TRUE)
        {
            // Logoff a MAPI session
            MAPICALL(lpSession)->Logoff(
                lpSession,
                (ULONG)0,
                (ULONG)0,
                (ULONG)0);

            MAPICALL(lpSession)->Release(
                lpSession);

            lpSession = NULL;
        }

        if(IsInitMAPI == TRUE)
        {
            MAPIUninitialize();

            IsInitMAPI = FALSE;
        }

        IsMAPILogon = FALSE;
    }

    MAPIFREEBUFFER(lpMtsInEid);

    MAPIFREEBUFFER(lpMtsOutEid);

    MAPIFREEBUFFER(lpStoreEid);

    RETURN(hr);
}

//$--HrInternalGatewayLogoff----------------------------------------------------
//  Logoff of the gateway.
// -----------------------------------------------------------------------------
static HRESULT HrInternalGatewayLogoff(void) // RETURNS: return code
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("HrInternalGatewayLogoff()\n");

    if((ulNewMailAdvise != 0xFFFFFFFFL) && (lpStore != NULL))
    {
        MAPICALL(lpStore)->Unadvise(lpStore, ulNewMailAdvise);
    }

    if(hNewMailEvent != NULL)
    {
        if(!CloseHandle(hNewMailEvent))
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    if(hNewMailThread != NULL)
    {
        if(!CloseHandle(hNewMailThread))
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    if(hNewFileThread != NULL)
    {
        if(!CloseHandle(hNewFileThread))
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    ULRELEASE(lpMtsInFolder);

    ULRELEASE(lpMtsOutFolder);

    ULRELEASE(lpRootFolder);

    ULRELEASE(lpStore);

    MAPIFREEBUFFER(lpGalEid);

    ULRELEASE(lpGalABCont);

    ULRELEASE(lpAdrBook);

    if(IsMAPILogon == TRUE)
    {
        // Logoff a MAPI session
        MAPICALL(lpSession)->Logoff(
            lpSession,
            (ULONG)0,
            (ULONG)0,
            (ULONG)0);

        MAPICALL(lpSession)->Release(
            lpSession);

        lpSession = NULL;
    }

    if(IsInitMAPI == TRUE)
    {
        MAPIUninitialize();

        IsInitMAPI = FALSE;
    }

    IsMAPILogon = FALSE;

    DeleteCriticalSection(&csNewMailList);

    DeleteCriticalSection(&csNewFileList);

    RETURN(hr);
}

//$--HrServiceStartup---------------------------------------------------------
//  This function is called at startup to initialize the gateway.
//------------------------------------------------------------------------------
HRESULT HrServiceStartup(         // RETURNS: return code
    IN HINSTANCE    hInstance,      // handle of current instance
    IN HINSTANCE    hPrevInstance,  // handle of previous instance
    IN HWND         hwndMainWindow, // handle to main window
    IN LPSTR        lpszCmdLine)    // pointer to command line
{
    HRESULT hr  = NOERROR;
    HRESULT hrT = NOERROR;

    DEBUGPUBLIC("HrServiceStartup()\n");

    hr = HrInternalGatewayLogon();

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = HrGWLogon();

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    if(FAILED(hr))
    {
        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    RETURN(hr);
}

//$--ServiceMain--------------------------------------------------------------
//  This function is given its own thread to execute.
//------------------------------------------------------------------------------
void ServiceMain(                 // RETURNS: nothing
    IN HANDLE hEventShutdown)       // handle to shutdown event object
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("ServiceMain()\n");

    __try
    {
        GWMain();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();

    }

    //
    // Wait for the gateway to stop.
    //

    __try
    {
        hr = HrGWWaitForStop();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);
    }

    if(FAILED(hr))
    {
        hr = HR_LOG(hr);
    }

    //
    // Confirm that the gateway has stopped.
    //

    __try
    {
        hr = HrServiceConfirmStop();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);
    }

    if(FAILED(hr))
    {
        hr = HR_LOG(hr);
    }

    ExitThread(0);
}

//$--HrServiceShutdown--------------------------------------------------------
//  This function is called to shutdown the gateway.
//------------------------------------------------------------------------------
HRESULT HrServiceShutdown(            // RETURNS: exit code
    void)
{
    HRESULT hr  = NOERROR;
    HRESULT hrT = NOERROR;

    DEBUGPUBLIC("HrServiceShutdown()\n");

    hr = HrGWLogoff();

    if(FAILED(hr))
    {
        goto cleanup;
    }
        
    hr = HrInternalGatewayLogoff();

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    if(FAILED(hr))
    {
        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    RETURN(hr);
}
