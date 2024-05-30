// --process.c------------------------------------------------------------------
//
//  Functions to start a thread to handle processing of new mail or files.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "gwmain.h"

#define SLEEP_TIME  3000

extern HANDLE hNewMailThread;
extern HANDLE hNewFileThread;

extern DWORD  dwNewMailTimeout;
extern DWORD  dwNewFileTimeout;

extern CRITICAL_SECTION csNewMailList;
extern CRITICAL_SECTION csNewFileList;

static HANDLE hFindData  = INVALID_HANDLE_VALUE; // change notification handle
static HANDLE PollHandle = INVALID_HANDLE_VALUE; // poll handle

//$--_GWThreadContext-----------------------------------------------------------
//  Type for gateway thread context information.
// -----------------------------------------------------------------------------
typedef struct _GWThreadContext
{
    BOOL                   fUseFindData;            // if TRUE use lpFindData

    CHAR                   szAddrType[MAX_PATH+1];  // address type

    DWORD                  dwSubmitInterval;        // submit interval
    DWORD                  dwPollingInterval;       // polling interval
    DWORD                  cMessages;               // #messages/thread
    DWORD                  cThreads;                // #threads

    ULONG                  ulThreadNumber;          // thread#

    CHAR                   szFindPath[MAX_PATH+1];  // path
    CHAR                   szFindMask[MAX_PATH+1];  // find mask
    HANDLE                 *lphFindData;            // change notifcation handle
    ULONG                  cFindData;               // find data count
	LPWIN32_FIND_DATA      lpFindData;              // find data
    HANDLE                 *lpPollHandle;           // poll handle

    LPSRowSet              lpRows;                  // rows
    LPMAPITABLE            lpTable;                 // contents table

    LPTHREAD_START_ROUTINE lpStartAddress;          // thread function

} GWTHREADCONTEXT, *LPGWTHREADCONTEXT;

#include "process.chk"

//$--GetGWPath------------------------------------------------------------------
//  Get a gateway path pointer.
// -----------------------------------------------------------------------------
LPSTR GetGWPath(                       // RETURNS: gateway path
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("GetGWPath()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return(NULL);

    if(((LPGWTHREADCONTEXT)lpParameter)->fUseFindData == FALSE)
    {
        return(NULL);
    }

    return(((LPGWTHREADCONTEXT)lpParameter)->szFindPath);
}

//$--GetGWSRowSet-----------------------------------------------------------------
//  Get a SRowSet pointer.
// -----------------------------------------------------------------------------
LPSRowSet GetGWSRowSet(                   // RETURNS: SRowSet
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("GetGWSRowSet()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return(NULL);

    if(((LPGWTHREADCONTEXT)lpParameter)->fUseFindData == TRUE)
    {
        return(NULL);
    }

    return(((LPGWTHREADCONTEXT)lpParameter)->lpRows);
}

//$--GetGWFindData-----------------------------------------------------------
//  Get a WIN32_FIND_DATA pointer.
// -----------------------------------------------------------------------------
LPWIN32_FIND_DATA GetGWFindData(     // RETURNS: WIN32_FIND_DATA
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("GetGWFindData()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return(NULL);

    if(((LPGWTHREADCONTEXT)lpParameter)->fUseFindData == FALSE)
    {
        return(NULL);
    }

    return(((LPGWTHREADCONTEXT)lpParameter)->lpFindData);
}

//$--GetGWFindDataSize-------------------------------------------------------
//  Get a WIN32_FIND_DATA size.
// -----------------------------------------------------------------------------
ULONG GetGWFindDataSize(             // RETURNS: count of WIN32_FIND_DATA
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("GetGWFindDataSize()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return(0);

    if(((LPGWTHREADCONTEXT)lpParameter)->fUseFindData == FALSE)
    {
        return(0);
    }

    return(((LPGWTHREADCONTEXT)lpParameter)->cFindData);
}

//$--GetGWSubmitInterval----------------------------------------------------------
//  Get the submit interval.
// -----------------------------------------------------------------------------
DWORD GetGWSubmitInterval(                // RETURNS: submit interval
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("GetGWSubmitInterval()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return(0);

    return(((LPGWTHREADCONTEXT)lpParameter)->dwSubmitInterval);
}

//$--FreeThreadParameter--------------------------------------------------------
//  Free the thread parameter.
// -----------------------------------------------------------------------------
VOID FreeThreadParameter(               // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("FreeThreadParameter()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return;

    if(((LPGWTHREADCONTEXT)lpParameter)->lpRows != NULL)
    {
        FREEPROWS(((LPGWTHREADCONTEXT)lpParameter)->lpRows);
    }

    if(((LPGWTHREADCONTEXT)lpParameter)->lpFindData != NULL)
    {
        MAPIFREEBUFFER(((LPGWTHREADCONTEXT)lpParameter)->lpFindData);
    }

    MAPIFREEBUFFER(lpParameter);
}

//$--HrGetNewMailList-----------------------------------------------------------
//  Get list of new mail.
// -----------------------------------------------------------------------------
static HRESULT HrGetNewMailList(        // RETURNS: return code
    IN  LPMAPITABLE lpTable,            // contents table
    IN  ULONG cMessages,                // maximum number of messages to get
    IN  DWORD dwPollingInterval,        // polling interval
    OUT LPSRowSet *lppRows)             // new mail list
{
    HRESULT   hr     = NOERROR;
    LPSRowSet lpRows = NULL;

    DEBUGPRIVATE("HrGetNewMailList()");

    EnterCriticalSection(&csNewMailList);

START:

    //
    // Check for service control
    //

    hr = HrServiceProcessControl();

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = MAPICALL(lpTable)->QueryRows(
        lpTable,
        cMessages,
        0,
        &lpRows);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    if((lpRows == NULL) || (lpRows->cRows == 0))
    {
        FREEPROWS(lpRows);
    }
    else
    {
        goto cleanup;
    }

    if((dwPollingInterval == ((DWORD)-1)) && (GetGWNewMailEvent() != NULL))
    {
        DWORD   dw          = 0;
        HANDLE  hObjects[2] = {0};

        hObjects[0] = GetServiceStopEvent();
        hObjects[1] = GetGWNewMailEvent();

        dw = WaitForMultipleObjects(2, hObjects, FALSE, dwNewMailTimeout);

        switch(dw)
        {
        case WAIT_OBJECT_0:
        case (WAIT_ABANDONED_0):

            //
            // Service is stopping.
            //

            hr = HR_LOG(EDK_E_SHUTDOWN_SERVICE);

            goto cleanup;
            break;
        case (WAIT_OBJECT_0+1):
        case (WAIT_ABANDONED_0+1):
            break;
        case (WAIT_TIMEOUT):
            break;
        default:
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }
    else
    {
        if(dwPollingInterval == ((DWORD)-1))
        {
            dwPollingInterval = SLEEP_TIME;
        }

        Sleep(dwPollingInterval);
    }

    // Go to the beginning of the contents table for the folder
    hr = MAPICALL(lpTable)->SeekRow(lpTable, BOOKMARK_BEGINNING, 0, NULL);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    goto START;
                
cleanup:

    if(SUCCEEDED(hr))
    {
        *lppRows = lpRows;
    }
    else
    {
        FREEPROWS(lpRows);
    }

    LeaveCriticalSection(&csNewMailList);

    RETURN(hr);
}

//$--FnNewMailPool--------------------------------------------------------------
//  New mail thread pool function
// -----------------------------------------------------------------------------
static VOID FnNewMailPool(              // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("FnNewMailPool()");

    __try
    {
        for(;;)
        {
            hr = HrGetNewMailList(
                ((LPGWTHREADCONTEXT)lpParameter)->lpTable,
                ((LPGWTHREADCONTEXT)lpParameter)->cMessages,
                ((LPGWTHREADCONTEXT)lpParameter)->dwPollingInterval,
                &((LPGWTHREADCONTEXT)lpParameter)->lpRows);

            if(FAILED(hr))
            {
                break;
            }

            (*((LPGWTHREADCONTEXT)lpParameter)->lpStartAddress)(lpParameter);

            FREEPROWS(((LPGWTHREADCONTEXT)lpParameter)->lpRows);
        }

        FreeThreadParameter(lpParameter);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();

    }
}

//$--FnNewMailMain--------------------------------------------------------------
//  New mail handler main loop.
// -----------------------------------------------------------------------------
static VOID FnNewMailMain(              // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr                = NOERROR;
    SCODE   sc                = 0;
    DWORD   dw                = 0;
    ULONG   i                 = 0;
    BOOL    fStatus           = FALSE;

    LPMAPITABLE lpTable       = NULL;

    DWORD   dwThreadId        = 0;
    HANDLE  hThread           = NULL;

    LONG    NumStartThreads   = 0;
    LONG    NumStopThreads    = 0;

    LONG    cThreads          = 0;

    LONG    cRunningThreads   = 0;

    LPMAPIFOLDER     lpMtsOutFolder  = NULL;

    LPGWTHREADCONTEXT lpContext       = NULL;
    LPGWTHREADCONTEXT lpThreadContext = NULL;

    SizedSPropTagArray(1, rgPropTag) =
    {
        1,
        {
            PR_ENTRYID
        }
    };

    DEBUGPRIVATE("FnNewMailMain()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return;

    lpContext = (LPGWTHREADCONTEXT)lpParameter;

    cThreads = lpContext->cThreads;

    lpMtsOutFolder = GetGWMtsOutFolder();

    //--------------------------------------------------------------------------

    hr = MAPICALL(lpMtsOutFolder)->GetContentsTable(
        lpMtsOutFolder,
        MAPI_DEFERRED_ERRORS,
        &lpTable);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = MAPICALL(lpTable)->SetColumns(
        lpTable,
        (LPSPropTagArray)&rgPropTag,
        TBL_BATCH);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Check for service control
    //

    hr = HrServiceProcessControl();

    if(FAILED(hr))
    {
        goto cleanup;
    }

    NumStartThreads = 0;
    NumStopThreads  = 0;

    cRunningThreads = 0;

    for(i = 0 ; i < ((ULONG)cThreads) ; i++)
    {
        lpThreadContext = NULL;

        sc = MAPIAllocateBuffer(sizeof(GWTHREADCONTEXT), (void **)&lpThreadContext);

        if(FAILED(sc))
        {
            hr = HR_LOG(E_OUTOFMEMORY);
            goto cleanup;
        }

        CopyMemory(lpThreadContext, lpContext, sizeof(GWTHREADCONTEXT));

        lpThreadContext->ulThreadNumber = i;
        lpThreadContext->lpTable        = lpTable;
        lpThreadContext->lpRows         = NULL;

        hThread = HServiceCreateThread(
            &NumStartThreads,
            &NumStopThreads,
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)FnNewMailPool,
            (LPVOID)lpThreadContext,
            0,
            &dwThreadId);

        if(hThread == NULL)
        {
            hr = HR_LOG(E_FAIL);

            if(cRunningThreads == 0)
                goto cleanup;
            else
                goto WAIT;
        }

        CloseHandle(hThread);

        cRunningThreads = i;
        cRunningThreads++;
    }

WAIT:

    // Wait for all threads to start
    while(NumStartThreads != cRunningThreads)
    {
        Sleep(SLEEP_TIME);
    }

    // Wait for all threads to exit
    while(NumStopThreads != cRunningThreads)
    {
        Sleep(SLEEP_TIME);
    }
                
cleanup:

    ULRELEASE(lpTable);

    if(FAILED(hr))
    {
        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    return;
}

//$--FnNewMailThread------------------------------------------------------------
//  New mail thread function
// -----------------------------------------------------------------------------
static VOID FnNewMailThread(            // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr      = NOERROR;
    HGLOBAL hglobal = NULL;

    DEBUGPRIVATE("FnNewMailThread()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        ExitThread(0);

    __try
    {
        FnNewMailMain(lpParameter);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();

    }

    MAPIFREEBUFFER( lpParameter);

    ExitThread(0);
}

//$--HrGWStartNewMailHandler@--------------------------------------------------
//  Start a thread to handle processing of new mail.
// -----------------------------------------------------------------------------
HRESULT HrGWStartNewMailHandlerW(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCWSTR lpszAddrType,                    // address type
    IN LPCWSTR lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress)   // thread function
{
    HRESULT hr            = NOERROR;
    HGLOBAL hglobal       = NULL;
    LPSTR   lpszAddrTypeA = NULL;
    LPSTR   lpszPathA     = NULL;
    DWORD   dwThreadId    = 0;

    LPGWTHREADCONTEXT lpContext = NULL;

    DEBUGPUBLIC("HrGWStartNewMailHandlerW()");

    hr = CHK_HrGWStartNewMailHandlerW(
        dwSubmitInterval, 
        dwPollingInterval,
        cMessages, 
        cThreads, 
        lpszAddrType, 
        lpszPath, 
        lpStartAddress);
    if(FAILED(hr))
        RETURN(hr);

    hr = MAPIAllocateBuffer( sizeof(GWTHREADCONTEXT), (PVOID)&lpContext);
    if( FAILED( hr))
        goto cleanup;

    ZeroMemory(lpContext, sizeof(GWTHREADCONTEXT));

    lpContext->fUseFindData      = FALSE;
    lpContext->dwSubmitInterval  = dwSubmitInterval;
    lpContext->dwPollingInterval = dwPollingInterval;
    lpContext->lpStartAddress    = lpStartAddress;
    lpContext->cMessages         = cMessages;
    lpContext->cThreads          = cThreads;
    lpContext->lpStartAddress    = lpStartAddress;

    hr = HrStrWToStrA( lpszAddrType, &lpszAddrTypeA);
    if( FAILED( hr))
        goto cleanup;

    hr = HrStrWToStrA( lpszPath, &lpszPathA);
    if( FAILED( hr))
        goto cleanup;

    lstrcpyA(lpContext->szAddrType, lpszAddrTypeA);
    lstrcpyA(lpContext->szFindPath, lpszPathA);

    hNewMailThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)FnNewMailThread,
        (LPVOID)lpContext,
        0,
        &dwThreadId);

    if(hNewMailThread == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    MAPIFREEBUFFER( lpszAddrTypeA);
    MAPIFREEBUFFER( lpszPathA);

    if(FAILED(hr))
        MAPIFREEBUFFER( lpContext);

    RETURN(hr);
}

HRESULT HrGWStartNewMailHandlerA(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCSTR  lpszAddrType,                    // address type
    IN LPCSTR  lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress)   // thread function
{
    HRESULT hr         = NOERROR;
    HGLOBAL hglobal    = NULL;
    DWORD   dwThreadId = 0;

    LPGWTHREADCONTEXT lpContext = NULL;

    DEBUGPUBLIC("HrGWStartNewMailHandlerA()");

    hr = CHK_HrGWStartNewMailHandlerA(
        dwSubmitInterval, 
        dwPollingInterval,
        cMessages, 
        cThreads, 
        lpszAddrType, 
        lpszPath, 
        lpStartAddress);
    if(FAILED(hr))
        RETURN(hr);

    hr = MAPIAllocateBuffer( sizeof(GWTHREADCONTEXT), (PVOID)&lpContext);
    if( FAILED( hr))
        goto cleanup;

    ZeroMemory(lpContext, sizeof(GWTHREADCONTEXT));

    lpContext->fUseFindData      = FALSE;
    lpContext->dwSubmitInterval  = dwSubmitInterval;
    lpContext->dwPollingInterval = dwPollingInterval;
    lpContext->lpStartAddress    = lpStartAddress;
    lpContext->cMessages         = cMessages;
    lpContext->cThreads          = cThreads;
    lpContext->lpStartAddress    = lpStartAddress;

    lstrcpyA( lpContext->szAddrType, lpszAddrType);
    lstrcpyA( lpContext->szFindPath, lpszPath);

    hNewMailThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)FnNewMailThread,
        (LPVOID)lpContext,
        0,
        &dwThreadId);

    if(hNewMailThread == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    if(FAILED(hr))
        MAPIFREEBUFFER( lpContext);

    RETURN(hr);
}

//$--HrPollFile-----------------------------------------------------------------
//  Poll for a file.
// -----------------------------------------------------------------------------
static HRESULT HrPollFile(                  // RETURNS: return code
    IN LPSTR             lpszDirectory,    // pointer to directory
    IN LPSTR             lpszFindMask,     // pointer to find mask
    OUT HANDLE            *lpPollHandle,    // pointer to find data handle
	OUT LPWIN32_FIND_DATA lpFindData)       // pointer to find data
{
    HRESULT hr              = NOERROR;
	BOOL    fFound          = FALSE;
	DWORD   dwIgnoreAttrs   =
	                        FILE_ATTRIBUTE_READONLY |
	                        FILE_ATTRIBUTE_SYSTEM |
	                        FILE_ATTRIBUTE_DIRECTORY |
	                        FILE_ATTRIBUTE_TEMPORARY;

    DEBUGPRIVATE("HrPollFile()");

    hr = CHK_HrPollFile(
        lpszDirectory,
        lpszFindMask,
        lpPollHandle,
    	lpFindData);

    if(FAILED(hr))
        RETURN(hr);

	//	One of the following is now true:
    //
	//	A)	We have a search already active, use FindNextFile.
	//		If it fails, we will want to restart the search
	//		(in case something appeared in the search behind
	//		us.
    //
	//	B)	We don't have a search active, use FindFirstFile.

	// Try the active search

	if (*lpPollHandle != INVALID_HANDLE_VALUE)
	{
		fFound = FindNextFile(*lpPollHandle, lpFindData);

		// If we fail, close the old search so we can start
		// a new one below.

		if (!fFound)
		{
			FindClose(*lpPollHandle);
			*lpPollHandle = INVALID_HANDLE_VALUE;

            //
            // If we don't find a file, then return.
            //

            if(GetLastError() == ERROR_NO_MORE_FILES)
            {
                hr = HR_LOG(EDK_E_NOT_FOUND);
            }
            else
            {
                hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
            }

			goto cleanup;
		}
	}

	// If there was no search or if the old one was just closed above

	if (*lpPollHandle == INVALID_HANDLE_VALUE)
	{
		HANDLE hFindT;
		CHAR rgchFileName[MAX_PATH];

		// Copy the directory name. Note that we trust the value in the
		// profile to be correct, since the UI should have enforced a
		// syntax that included a trailing : or \ in the spec.

		lstrcpy(rgchFileName, lpszDirectory);

		lstrcat(rgchFileName, lpszFindMask);

		hFindT = FindFirstFile(rgchFileName, lpFindData);

		// If nothing's found, we're done here.

		if (hFindT == INVALID_HANDLE_VALUE)
        {
            hr = HR_LOG(EDK_E_NOT_FOUND);
			goto cleanup;
        }

		// Found something, continue along.

		fFound = TRUE;
		*lpPollHandle = hFindT;
	}


	//	Here on a match. Exclude unwanted files.
    //
	//	Any match with DIRECTORY, READONLY, SYSTEM or TEMPORARY attribute
	//	is ignored. Keep trying until we exhaust the current supply or we
	//	find a file without these attributes. Also, ignore files smaller
	//	than some arbitrary size, they're probably trash.

	while (fFound)
	{
		//	We found a file. Does it have any of the attributes we
		//	want to ignore? If not, get out. If so, try another.

#define MIN_USEFUL_FILESIZE ((DWORD) 64)

		if ((!((lpFindData)->dwFileAttributes & dwIgnoreAttrs)) &&
			((lpFindData->nFileSizeHigh != 0) ||
			(lpFindData->nFileSizeLow >= MIN_USEFUL_FILESIZE)))
			break;

		fFound = FindNextFile(*lpPollHandle, lpFindData);
	}

	if(!fFound)
	{
		FindClose(*lpPollHandle);
		*lpPollHandle = INVALID_HANDLE_VALUE;

        hr = HR_LOG(EDK_E_NOT_FOUND);
        goto cleanup;
	}

cleanup:

	RETURN(hr);
}

//$--HrGetNewFileList-----------------------------------------------------------
//  Get list of new files.
// -----------------------------------------------------------------------------
static HRESULT HrGetNewFileList(        // RETURNS: return code
    IN  ULONG cMessages,                // maximum number of messages to get
    IN  DWORD dwPollingInterval,        // polling interval
    IN  LPSTR lpszFindPath,            // find path
    IN  LPSTR lpszFindMask,            // find mask
    IN OUT HANDLE *lpPollHandle,        // poll handle
    IN OUT HANDLE *lphFindData,         // change notifcation handle
    OUT ULONG *lpcFindData,             // count of find data
    OUT LPWIN32_FIND_DATA *lppFindData) // new file list
{
    HRESULT           hr         = NOERROR;
	LPWIN32_FIND_DATA lpFindData = NULL;
    ULONG             cBytes     = 0;
    SCODE             sc         = NOERROR;
    ULONG             j          = 0;
    BOOL              fStatus    = FALSE;

    DEBUGPRIVATE("HrGetNewFileList()");

    *lpcFindData = 0;
    *lppFindData = NULL;

    EnterCriticalSection(&csNewFileList);

START:

    //
    // Check for service control
    //

    hr = HrServiceProcessControl();

    if(FAILED(hr))
    {
        goto cleanup;
    }

    lpFindData = NULL;

    cBytes = cMessages*(sizeof(WIN32_FIND_DATA) + MAX_ALIGN);

    sc = MAPIAllocateBuffer(cBytes, (void **)&lpFindData);

    ZeroMemory(lpFindData, cBytes);

    // An error occured allocating the messages buffer

    if(FAILED(sc))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(j = 0 ; j < ((ULONG)cMessages) ; j++)
    {
        hr = HrPollFile(
            lpszFindPath,
            lpszFindMask,
            lpPollHandle,
            &lpFindData[j]);

        if(hr == EDK_E_NOT_FOUND)
        {
            hr = NOERROR;

            //
            // Don't start any more threads after the current one is
            // started since there are no more files to process.
            //

            break;
        }

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    if(j == 0)
    {
        MAPIFREEBUFFER(lpFindData);
    }
    else
    {
        *lpcFindData = j;
        *lppFindData = lpFindData;
        goto cleanup;
    }

    if((dwPollingInterval == ((DWORD)-1)) && (*lphFindData != NULL))
    {
        DWORD   dw          = 0;
        HANDLE  hObjects[2] = {0};

        hObjects[0] = GetServiceStopEvent();
        hObjects[1] = *lphFindData;

        dw = WaitForMultipleObjects(2, hObjects, FALSE, dwNewFileTimeout);

        switch(dw)
        {
        case WAIT_OBJECT_0:
        case (WAIT_ABANDONED_0):

            //
            // Service is stopping.
            //

            hr = HR_LOG(EDK_E_SHUTDOWN_SERVICE);

            goto cleanup;
            break;
        case (WAIT_OBJECT_0+1):
        case (WAIT_ABANDONED_0+1):
            break;
        case (WAIT_TIMEOUT):
            goto START;
            break;
        default:
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        fStatus = FindNextChangeNotification(*lphFindData);

        if(fStatus == FALSE)
        {
            hr = HR_LOG(E_FAIL);

            FindCloseChangeNotification(*lphFindData);
            *lphFindData = NULL;
        }
    }
    else
    {
        if(dwPollingInterval == ((DWORD)-1))
        {
            dwPollingInterval = SLEEP_TIME;
        }

        Sleep(dwPollingInterval);
    }

    goto START;
                
cleanup:

    if(FAILED(hr))
    {
        *lpcFindData = 0;
        *lppFindData = NULL;

        MAPIFREEBUFFER(lpFindData);
    }

    LeaveCriticalSection(&csNewFileList);

    RETURN(hr);
}

//$--FnNewFilePool--------------------------------------------------------------
//  New file thread pool function
// -----------------------------------------------------------------------------
static VOID FnNewFilePool(              // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("FnNewFilePool()");

    __try
    {
        for(;;)
        {
            hr = HrGetNewFileList(
                    ((LPGWTHREADCONTEXT)lpParameter)->cMessages,
                    ((LPGWTHREADCONTEXT)lpParameter)->dwPollingInterval,
                    ((LPGWTHREADCONTEXT)lpParameter)->szFindPath,
                    ((LPGWTHREADCONTEXT)lpParameter)->szFindMask,
                    ((LPGWTHREADCONTEXT)lpParameter)->lpPollHandle,
                    ((LPGWTHREADCONTEXT)lpParameter)->lphFindData,
                    &((LPGWTHREADCONTEXT)lpParameter)->cFindData,
                    &((LPGWTHREADCONTEXT)lpParameter)->lpFindData);

            if(FAILED(hr))
            {
                break;
            }

            (*((LPGWTHREADCONTEXT)lpParameter)->lpStartAddress)(lpParameter);

            MAPIFREEBUFFER(((LPGWTHREADCONTEXT)lpParameter)->lpFindData);
        }

        FreeThreadParameter(lpParameter);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();

    }
}

//$--FnNewFileMain--------------------------------------------------------------
//  New file handler main loop.
// -----------------------------------------------------------------------------
static VOID FnNewFileMain(              // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr                = NOERROR;
    HRESULT hrT               = NOERROR;
    SCODE   sc                = 0;
    DWORD   dw                = 0;
    BOOL    fStatus           = 0;
    ULONG   i                 = 0;

    ULONG   cBytes            = 0;

    DWORD   dwThreadId        = 0;
    HANDLE  hThread           = NULL;

    LONG    NumStartThreads   = 0;
    LONG    NumStopThreads    = 0;

    LONG    cThreads          = 0;
    ULONG   cMessages         = 0;

    LONG    cRunningThreads   = 0;

    DWORD   dwPollingInterval = 0;

    LPGWTHREADCONTEXT lpContext       = NULL;
    LPGWTHREADCONTEXT lpThreadContext = NULL;

    DEBUGPRIVATE("FnNewFileMain()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        return;

    lpContext = (LPGWTHREADCONTEXT)lpParameter;

    cThreads = lpContext->cThreads;

    //--------------------------------------------------------------------------

    //
    // Check for service control
    //

    hr = HrServiceProcessControl();

    if(FAILED(hr))
    {
        goto cleanup;
    }

    NumStartThreads = 0;
    NumStopThreads  = 0;

    cRunningThreads = 0;

    for(i = 0 ; i < ((ULONG)cThreads) ; i++)
    {
        lpThreadContext = NULL;

        sc = MAPIAllocateBuffer(sizeof(GWTHREADCONTEXT), (void **)&lpThreadContext);

        if(FAILED(sc))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        CopyMemory(lpThreadContext, lpContext, sizeof(GWTHREADCONTEXT));

        lpThreadContext->ulThreadNumber = i;
        lpThreadContext->cFindData      = 0;
        lpThreadContext->lpFindData     = NULL;

        hThread = HServiceCreateThread(
            &NumStartThreads,
            &NumStopThreads,
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)FnNewFilePool,
            (LPVOID)lpThreadContext,
            0,
            &dwThreadId);

        if(hThread == NULL)
        {
            hr = HR_LOG(E_FAIL);

            if(cRunningThreads == 0)
                goto cleanup;
            else
                goto WAIT;
        }

        CloseHandle(hThread);

        cRunningThreads = i;
        cRunningThreads++;
    }

WAIT:

    // Wait for all threads to start
    while(NumStartThreads != cRunningThreads)
    {
        Sleep(SLEEP_TIME);
    }

    // Wait for all threads to exit
    while(NumStopThreads != cRunningThreads)
    {
        Sleep(SLEEP_TIME);
    }

cleanup:

    if(FAILED(hr))
    {
        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    return;
}

//$--FnNewFileThread------------------------------------------------------------
//  New file thread function
// -----------------------------------------------------------------------------
static VOID FnNewFileThread(            // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr      = NOERROR;
    BOOL    fStatus = FALSE;

    DEBUGPRIVATE("FnNewFileThread()");

    hr = CHK_HrCheckParameter(lpParameter);

    if(FAILED(hr))
        ExitThread(0);

    __try
    {
        FnNewFileMain(lpParameter);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    __try
    {
        if(*((LPGWTHREADCONTEXT)lpParameter)->lphFindData != NULL)
        {
            fStatus = FindCloseChangeNotification(
                *((LPGWTHREADCONTEXT)lpParameter)->lphFindData);

            if(fStatus == FALSE)
            {
                hr = HR_LOG(E_FAIL);
            }
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);
    }

    MAPIFREEBUFFER( lpParameter);

    ExitThread(0);
}

//$--HrGWStartNewFileHandler@--------------------------------------------------
//  Start a thread to handle processing of new files.
// -----------------------------------------------------------------------------
HRESULT HrGWStartNewFileHandlerW(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCWSTR lpszAddrType,                    // address type
    IN LPCWSTR lpszFileMask,                    // file mask
    IN LPCWSTR lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress)   // thread function
{
    HRESULT hr         = NOERROR;
    HANDLE  hThread    = NULL;
    LPSTR   lpszAddrTypeA = NULL;
    LPSTR   lpszFileMaskA = NULL;
    LPSTR   lpszPathA     = NULL;
    DWORD   dwThreadId = 0;

    LPGWTHREADCONTEXT lpContext = NULL;

    DEBUGPUBLIC("HrGWStartNewFileHandlerW()");

    hr = CHK_HrGWStartNewFileHandlerW(
        dwSubmitInterval,
        dwPollingInterval,
        cMessages,
        cThreads,
        lpszAddrType,
        lpszFileMask,
        lpszPath,
        lpStartAddress);
    if(FAILED(hr))
        RETURN(hr);

    hr = MAPIAllocateBuffer( sizeof(GWTHREADCONTEXT), (PVOID)&lpContext);
    if( FAILED( hr))
        goto cleanup;

    ZeroMemory(lpContext, sizeof(GWTHREADCONTEXT));

    lpContext->fUseFindData      = TRUE;
    lpContext->dwSubmitInterval  = dwSubmitInterval;
    lpContext->dwPollingInterval = dwPollingInterval;
    lpContext->lpStartAddress    = lpStartAddress;
    lpContext->cMessages         = cMessages;
    lpContext->cThreads          = cThreads;
    lpContext->lpStartAddress    = lpStartAddress;

    hr = HrStrWToStrA( lpszAddrType, &lpszAddrTypeA);
    if( FAILED( hr))
        goto cleanup;

    hr = HrStrWToStrA( lpszFileMask, &lpszFileMaskA);
    if( FAILED( hr))
        goto cleanup;

    hr = HrStrWToStrA( lpszPath, &lpszPathA);
    if( FAILED( hr))
        goto cleanup;

    lstrcpyA(lpContext->szAddrType, lpszAddrTypeA);
    lstrcpyA(lpContext->szFindMask, lpszFileMaskA);
    lstrcpyA(lpContext->szFindPath, lpszPathA);

    hFindData = FindFirstChangeNotification(
        lpContext->szFindPath,
        FALSE,
        FILE_NOTIFY_CHANGE_ATTRIBUTES);

    if(hFindData == INVALID_HANDLE_VALUE)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lpContext->lphFindData  = &hFindData;
    lpContext->lpPollHandle = &PollHandle;

    hNewFileThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)FnNewFileThread,
        (LPVOID)lpContext,
        0,
        &dwThreadId);

    if(hNewFileThread == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    MAPIFREEBUFFER( lpszAddrTypeA);
    MAPIFREEBUFFER( lpszFileMaskA);
    MAPIFREEBUFFER( lpszPathA);

    if(FAILED(hr))
        MAPIFREEBUFFER( lpContext);

    RETURN(hr);
}

HRESULT HrGWStartNewFileHandlerA(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCSTR  lpszAddrType,                    // address type
    IN LPCSTR  lpszFileMask,                    // file mask
    IN LPCSTR  lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress)   // thread function
{
    HRESULT hr            = NOERROR;
    HANDLE  hThread       = NULL;
    DWORD   dwThreadId    = 0;

    LPGWTHREADCONTEXT lpContext = NULL;

    DEBUGPUBLIC("HrGWStartNewFileHandlerA()");

    hr = CHK_HrGWStartNewFileHandlerA(
        dwSubmitInterval,
        dwPollingInterval,
        cMessages,
        cThreads,
        lpszAddrType,
        lpszFileMask,
        lpszPath,
        lpStartAddress);
    if(FAILED(hr))
        RETURN(hr);

    hr = MAPIAllocateBuffer( sizeof(GWTHREADCONTEXT), (PVOID)&lpContext);
    if( FAILED( hr))
        goto cleanup;

    ZeroMemory(lpContext, sizeof(GWTHREADCONTEXT));

    lpContext->fUseFindData      = TRUE;
    lpContext->dwSubmitInterval  = dwSubmitInterval;
    lpContext->dwPollingInterval = dwPollingInterval;
    lpContext->lpStartAddress    = lpStartAddress;
    lpContext->cMessages         = cMessages;
    lpContext->cThreads          = cThreads;
    lpContext->lpStartAddress    = lpStartAddress;

    lstrcpy(lpContext->szAddrType, lpszAddrType);
    lstrcpy(lpContext->szFindMask, lpszFileMask);
    lstrcpy(lpContext->szFindPath, lpszPath);

    hFindData = FindFirstChangeNotification(
        lpContext->szFindPath,
        FALSE,
        FILE_NOTIFY_CHANGE_ATTRIBUTES);

    if(hFindData == INVALID_HANDLE_VALUE)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lpContext->lphFindData  = &hFindData;
    lpContext->lpPollHandle = &PollHandle;

    hNewFileThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)FnNewFileThread,
        (LPVOID)lpContext,
        0,
        &dwThreadId);

    if(hNewFileThread == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    if(FAILED(hr))
        MAPIFREEBUFFER( lpContext);

    RETURN(hr);
}


