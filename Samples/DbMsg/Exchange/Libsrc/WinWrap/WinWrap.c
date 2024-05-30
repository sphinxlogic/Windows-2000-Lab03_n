// --winwrap.c------------------------------------------------------------------
// 
//  Windows NT service (Windows application) shell for EDK applications.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include <stdlib.h>

static struct _tparam
{
    LPLONG                 lplStartThreads;
    LPLONG                 lplStopThreads;
    LPTHREAD_START_ROUTINE lpStartAddress;
    LPVOID                 lpParameter;
};

#include "winwrap.chk"

#define DEFAULT_WAIT_HINT   30000

#define SERVICE_NAME        "WINWRAP"

#define WAIT_DESTROY        120000


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static BOOL                    fIsService                = TRUE;

static DWORD                   dwStartWaitHint           = DEFAULT_WAIT_HINT;
static DWORD                   dwStartCheckPoint         = 0;

static DWORD                   dwPauseWaitHint           = DEFAULT_WAIT_HINT;
static DWORD                   dwPauseCheckPoint         = 0;

static DWORD                   dwContinueWaitHint        = DEFAULT_WAIT_HINT;
static DWORD                   dwContinueCheckPoint      = 0;

static DWORD                   dwStopWaitHint            = DEFAULT_WAIT_HINT;
static DWORD                   dwStopCheckPoint          = 0;

static HINSTANCE               hInst                     = NULL;

static HANDLE                  hServiceStopEvent         = NULL;
static HANDLE                  hServicePauseEvent        = NULL;
static HANDLE                  hServiceContinueEvent     = NULL;

static HANDLE                  hStopConfirmEvent         = NULL;

static SERVICE_STATUS          ssStatus                  = {0};

static SERVICE_STATUS_HANDLE   sshStatusHandle           = 0;

static HWND                    hAppWnd                   = NULL;

static DWORD                   dwWorkerTID               = 0;
static HANDLE                  hWorkerThread             = NULL;

static DWORD                   dwShutdownTID             = 0;
static HANDLE                  hShutdownThread           = NULL;

static DWORD                   dwServiceTID              = 0;
static HANDLE                  hServiceThread            = NULL;

// -----------------------------------------------------------------------------

static DWORD                   dwServiceArgc             = 0;
static LPSTR                  *lpszServiceArgv          = NULL;

static CHAR                   szServiceName[MAX_SERVICE_NAME_LENGTH+1] = {0};

static DWORD                   dwSvcWin32ExitCode           = 0;
static DWORD                   dwSvcServiceSpecificExitCode = 0;

static struct _WinMainContext
{
    HINSTANCE   hInstance;
    HINSTANCE   hPrevInstance;
    LPSTR       lpszCmdLine;
    int         nCmdShow;
}   WinMainContext;

//$--FIsService-----------------------------------------------------------------
//  Returns TRUE if the application is running as an NT service.
// -----------------------------------------------------------------------------
BOOL FIsService(                        // RETURNS: TRUE if service
    VOID)                               // no arguments
{
    return(fIsService);
}

//$--GetServiceStopEvent-------------------------------------------------------
//  Returns the handle for the service stop event.
// -----------------------------------------------------------------------------
HANDLE GetServiceStopEvent(            // RETURNS: handle to stop event
    VOID)                               // no arguments
{
    return(hServiceStopEvent);
}

//$--GetServiceInstance--------------------------------------------------------
//  Returns the handle for the service instance.
// -----------------------------------------------------------------------------
HANDLE GetServiceInstance(             // RETURNS: handle to service instance
    VOID)                               // no arguments
{
    return(hInst);
}


//Turning off /Og optimization for FnCreateThread() 
#pragma optimize ("g", off)


//$--FnCreateThread-------------------------------------------------------------
//  Wrapper for CreateThread() function.
// -----------------------------------------------------------------------------
static VOID FnCreateThread(             // RETURNS: nothing
    IN LPVOID lpParameter)              // parameter
{
    HRESULT hr      = NOERROR;
    HGLOBAL hglobal = NULL;

    struct _tparam *lpContext = NULL;

    DEBUGPRIVATE("FnCreateThread()\n");

    hr = CHK_HrFnCreateThread(
        lpParameter);

    if(FAILED(hr))
        return;

    lpContext = (struct _tparam *)lpParameter;

    InterlockedIncrement(lpContext->lplStartThreads);

    __try
    {
        (*(lpContext->lpStartAddress))(lpContext->lpParameter);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);
    }

    InterlockedIncrement(lpContext->lplStopThreads);

    __try
    {
        hglobal = GlobalFree(lpContext);

        if(hglobal != NULL)
        {
            hr = HR_LOG(E_FAIL);
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);
    }
}

//Following pragma with null string will set optimizations to default values
//So it will set /Og optimization to default, which was turned off for FnCreateThread() 
#pragma optimize ("", on)


//$--HServiceCreateThread-----------------------------------------------------------
//  Create a wrapped thread.
// -----------------------------------------------------------------------------
HANDLE HServiceCreateThread(                            // RETURNS: handle
    IN  LPLONG lplStartThreads,                     // number of running threads
    IN  LPLONG lplStopThreads,                      // number of stopped threads
    IN  LPSECURITY_ATTRIBUTES lpThreadAttributes,   // thread attributes
    IN  DWORD dwStackSize,                          // stack size
    IN  LPTHREAD_START_ROUTINE lpStartAddress,      // start address
    IN  LPVOID lpParameter,                         // parameter
    IN  DWORD dwCreationFlags,                      // creation flags
    OUT LPDWORD lpThreadId)                         // thread ID
{
    HRESULT        hr         = NOERROR;
    HGLOBAL        hglobal    = NULL;
    HANDLE         handle     = NULL;
    struct _tparam *lpContext = NULL;

    DEBUGPUBLIC("HServiceCreateThread()\n");

    SetLastError(ERROR_SUCCESS);

    hr = CHK_HrEDKCreateThread(
        lplStartThreads,
        lplStopThreads,
        lpThreadAttributes,
        dwStackSize,
        lpStartAddress,
        lpParameter,
        dwCreationFlags,
        lpThreadId);

    if(FAILED(hr))
        return(NULL);

    lpContext = (struct _tparam *)GlobalAlloc(GPTR, sizeof(struct _tparam));

    if(lpContext == NULL)
    {
        hr = HR_LOG(E_FAIL);

        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        goto cleanup;
    }

    lpContext->lplStartThreads = lplStartThreads;
    lpContext->lplStopThreads  = lplStopThreads;
    lpContext->lpStartAddress  = lpStartAddress;
    lpContext->lpParameter     = lpParameter;

    handle = CreateThread(
        lpThreadAttributes,
        dwStackSize,
        (LPTHREAD_START_ROUTINE)FnCreateThread,
        (LPVOID)lpContext,
        dwCreationFlags,
        lpThreadId);

cleanup:

    if((handle == NULL) && (lpContext != NULL))
    {
        hr = HR_LOG(E_FAIL);

        __try
        {
            hglobal = GlobalFree(lpContext);

            if(hglobal != NULL)
            {
                hr = HR_LOG(E_FAIL);
            }
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            SetLastError(_exception_code());

            hr = HR_LOG(E_FAIL);
        }
    }

    return(handle);
}

//$--HrServiceGetName--------------------------------------------------------
//  The HrServiceGetName function can be used by any thread to get the
//  service name after the service has been started. lpszName must point to a
//  block of memory at least MAX_SERVICE_NAME_LENGTH+1 bytes in length.
// -----------------------------------------------------------------------------
HRESULT HrServiceGetName(            // RETURNS: return code
    OUT LPSTR lpszName)                // pointer to service name buffer
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrServiceGetName()\n");

    hr = CHK_HrServiceGetName(
        lpszName);

    if(FAILED(hr))
        RETURN(hr);

    lstrcpyn(lpszName, szServiceName, MAX_SERVICE_NAME_LENGTH+1);

    lpszName[MAX_SERVICE_NAME_LENGTH] = 0;

    RETURN(hr);
}

//$--HrServiceGetArgv--------------------------------------------------------
//  The HrServiceGetArgv function can be used by any thread to get the
//  service argv[] after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceGetArgv(            // RETURNS: return code
    OUT DWORD  *lpdwArgc,               // pointer to argc address variable
    OUT LPSTR **lppszArgv)             // pointer to argv[] address variable
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrServiceGetArgv()\n");

    hr = CHK_HrServiceGetArgv(
        lpdwArgc,
        lppszArgv);

    if(FAILED(hr))
        RETURN(hr);

    *lppszArgv = lpszServiceArgv;
    *lpdwArgc  = dwServiceArgc;

    RETURN(hr);
}

//$--WaitShutdown---------------------------------------------------------------
//  Thread that will send WM_DESTROY once hShutdownEvent is signalled.
//------------------------------------------------------------------------------
void WaitShutdown(                  // RETURNS: nothing
    IN HANDLE hShutdownEvent)       // Handle to Shutdown event object
{
    HRESULT hr = NOERROR;
    DWORD   dw = 0;

    DEBUGPUBLIC("WaitShutdown()\n");

    hr = CHK_HrWaitShutdown(
        hShutdownEvent);

    if(FAILED(hr))
        return;

    if(hAppWnd == NULL)
    {
        hr = HR_LOG(E_FAIL);
        return;
    }

    dw = WaitForSingleObject(hShutdownEvent, INFINITE);

    if((dw != WAIT_OBJECT_0) && (dw != WAIT_ABANDONED))
    {
        hr = HR_LOG(E_FAIL);
    }

    if(hAppWnd != NULL)
    {
        PostMessage(hAppWnd, WM_DESTROY, 0, 0);
    }

    ExitThread(0);

    return;
}

//$--fInitApplication-----------------------------------------------------------
//  Initializes window data and registers window class
// -----------------------------------------------------------------------------
BOOL fInitApplication(              // RETURNS: TRUE if successful
    IN HINSTANCE hInstance)         // Handle to instance of application
{
    WNDCLASS wc = {0};

    DEBUGPUBLIC("fInitApplication()\n");

    // Fill in window class structure with parameters that describe the
    // main window.

    wc.style         = CS_HREDRAW | CS_VREDRAW; // Class style(s).
    wc.lpfnWndProc   = (WNDPROC)WndProc;        // Window Procedure
    wc.cbClsExtra    = 0;                       // No per-class extra data.
    wc.cbWndExtra    = 0;                       // No per-window extra data.
    wc.hInstance     = hInstance;               // Owner of this class
    wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);   // Icon
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);            // Cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);// Default color
    wc.lpszMenuName  = NULL;                    // Menu name
    wc.lpszClassName = szAppName;               // Name to register as

    if(wc.hIcon == NULL)
    {
        wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION);        // Icon
    }

    // Register the window class and return success/failure code.

    return(RegisterClass(&wc));
}

//$--fInitInstance--------------------------------------------------------------
//  Saves instance handle and creates main window
// -----------------------------------------------------------------------------
BOOL fInitInstance(                 // RETURNS: TRUE if successful
    IN HINSTANCE hInstance,         // handle to instance of application
    IN int       nCmdShow)          // argument for ShowWindow()
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("fInitInstance()\n");

    // Save the instance handle in static variable, which will be used in
    // many subsequence calls from this application to Windows.

    hInst = hInstance; // Store instance handle in our global variable

    // Create a main window for this application instance.

    hAppWnd = CreateWindow(
        szAppName,                  // See RegisterClass() call.
        szWindowTitle,              // Text for window title bar.
        WS_MINIMIZE |
        WS_POPUP |
        WS_SYSMENU |
        WS_VISIBLE,                 // Window style.
        CW_USEDEFAULT, 0,           // Use default positioning
        CW_USEDEFAULT, 0,           // Use default positioning
        NULL,                       // Overlapped windows have no parent.
        NULL,                       // Use the window class menu.
        hInstance,                  // This instance owns this window.
        NULL                        // We don't use any data in our WM_CREATE
    );

    //
    // If window could not be created, return "failure"
    //

    if(hAppWnd == NULL)
    {
        hr = HR_LOG(E_FAIL);

        return(FALSE);
    }

    if(fIsService == FALSE)
    {
        //
        // Make the window visible; update its client area; and return "success"
        //

        ShowWindow(hAppWnd, nCmdShow);  // Show the window
        UpdateWindow(hAppWnd);          // Sends WM_PAINT message
    }

    return(TRUE);
}

//$--WorkerThread---------------------------------------------------------------
//  This function does the actual nuts and bolts work that
//  the service requires.  It will also Pause or Stop when
//  asked by the ServiceCtrlProc function.
// -----------------------------------------------------------------------------
VOID WorkerThread(                  // RETURNS: nothing
    IN HANDLE hShutdownEvent)       // service shutdown event handle
{
    HRESULT   hr            = NOERROR;
    HINSTANCE hInstance     = NULL;
    HINSTANCE hPrevInstance = NULL;
    LPSTR     lpszCmdLine   = NULL;
    int       nCmdShow      = 0;
    MSG       msg           = {0};
    BOOL      fT            = FALSE;

    DEBUGPUBLIC("WorkerThread()\n");

    hInstance     = WinMainContext.hInstance;
    hPrevInstance = WinMainContext.hPrevInstance;
    lpszCmdLine   = WinMainContext.lpszCmdLine;
    nCmdShow      = WinMainContext.nCmdShow;

    hr = CHK_HrWorkerThread(
        hShutdownEvent);

    if(FAILED(hr))
        return;

    // Are there other instances of the app running?
    if(hPrevInstance == NULL)               
    {	// YES, so initialize shared things.
        if(fInitApplication(hInstance) == FALSE)
        {
            hr = HR_LOG(E_FAIL);

            ServiceStop();

            goto cleanup;
        }
    }

    // Perform initializations that apply to a specific instance
    if(fInitInstance(hInstance, nCmdShow) == FALSE)
    {
        hr = HR_LOG(E_FAIL);

        ServiceStop();

        goto cleanup;
    }

    hr = HrServiceStartup(hInstance, hPrevInstance, hAppWnd, lpszCmdLine);

    if(FAILED(hr))
    {
        ServiceStop();

        goto cleanup;
    }

    //
    // Create a thread that waits for the shut down event to trigger.
    //

    hShutdownThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)WaitShutdown,
        (LPVOID)hShutdownEvent,
        0,
        &dwShutdownTID);

    if(hShutdownThread == NULL)
    {
        hr = HR_LOG(E_FAIL);

        ServiceStop();

        //
        // The service thread has not started yet so just shut down.
        //

        (void)HrServiceShutdown();

        goto cleanup;
    }

    // Start a thread that executes the ServiceMain function.
    hServiceThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ServiceMain,
        (LPVOID)hShutdownEvent,
        0,
        &dwServiceTID);

    if(hServiceThread == NULL)
    {
        hr = HR_LOG(E_FAIL);

        ServiceStop();
    }

    // Acquire and dispatch messages until a WM_QUIT message is received.
    while (GetMessage(
        &msg,   // message structure
        NULL,   // handle of window receiving the message
        0,      // lowest message to examine
        0))     // highest message to examine
    {
        TranslateMessage(&msg);// Translates virtual key codes
        DispatchMessage(&msg); // Dispatches message to window
    }

    hr = NOERROR;

cleanup:

    if(FAILED(hr))
        SetServiceExitCode( ERROR_SERVICE_LOGON_FAILED, NOERROR);

    CLOSEHANDLE(hShutdownThread);

    ExitThread(0);

    return;
}

//$--SzMakeServiceName----------------------------------------------------------
//  Make a service name from the EXE name.
// -----------------------------------------------------------------------------
static LPSTR SzMakeServiceName(        // RETURNS: name of service
    IN LPSTR lpszExe)                  // executable name
{
    LPSTR lpszCurr    = NULL;
    LPSTR lpszName    = NULL;

    if(lpszExe == NULL)
    {
        return(NULL);
    }

    lpszName = lpszExe + lstrlen(lpszExe);

    while(lpszName != lpszExe)
    {
        //
        // Check if character is a delimiter
        //

        lpszCurr = ":\\";

        while(*lpszCurr)
        {
            if(*lpszName == *lpszCurr)
            {
                //
                // Found a delimiter
                //

                goto cleanup;
            }

            lpszCurr++;
        }

        //
        // Remove file extension
        //

        if(*lpszName == '.')
        {
            *lpszName = 0;
        }

        lpszName--;
    }

cleanup:

    if(lpszName != lpszExe)
    {
        //
        // Advance past delimiter
        //

        lpszName++;
    }

    return(lpszName);
}

//$--dwDoServiceCtrlPause-------------------------------------------------------
//  This function is called by ServiceCtrl whenever
//  someone calls ControlService to pause our service.
// -----------------------------------------------------------------------------
static DWORD dwDoServiceCtrlPause(         // RETURNS: service state
    VOID)                           // no arguments
{
    HRESULT hr       = NOERROR;
    DWORD   dwState  = SERVICE_RUNNING;
    DWORD   dwStatus = 0;
    BOOL    fStatus  = TRUE;

    DEBUGPUBLIC("dwDoServiceCtrlPause()\n");

    dwState = ssStatus.dwCurrentState;

    if(ssStatus.dwCurrentState == SERVICE_RUNNING)
    {
        // Report the status, specifying the checkpoint and wait-hint,
        // before setting the continue event.

        dwState = SERVICE_PAUSED;

        dwPauseCheckPoint++;

        FServiceReportStatus(
            dwState,              // current state
            NOERROR,              // exit code
            NOERROR,              // exit code
            dwPauseCheckPoint,    // checkpoint
            dwPauseWaitHint);     // wait hint

        if((hServicePauseEvent != NULL) && (hServiceContinueEvent != NULL))
        {
            fStatus = ResetEvent(hServiceContinueEvent);

            if(fStatus == FALSE)
            {
                hr = HR_LOG(E_FAIL);
            }

            fStatus = SetEvent(hServicePauseEvent);

            if(fStatus == FALSE)
            {
                hr = HR_LOG(E_FAIL);
            }
        }
        else
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    return(dwState);
}

//$--dwDoServiceCtrlContinue----------------------------------------------------
//  This function is called by ServiceCtrl whenever
//  someone calls ControlService to continue our service.
// -----------------------------------------------------------------------------
static DWORD dwDoServiceCtrlContinue(      // RETURNS: service state
    VOID)                           // no arguments
{
    HRESULT hr       = NOERROR;
    DWORD   dwState  = SERVICE_RUNNING;
    DWORD   dwStatus = 0;
    BOOL    fStatus  = TRUE;

    DEBUGPUBLIC("dwDoServiceCtrlContinue()\n");

    dwState = ssStatus.dwCurrentState;

    if(ssStatus.dwCurrentState == SERVICE_PAUSED)
    {
        // Report the status, specifying the checkpoint and wait-hint,
        // before setting the continue event.

        dwState = SERVICE_RUNNING;

        dwContinueCheckPoint++;

        FServiceReportStatus(
            dwState,              // current state
            NOERROR,              // exit code
            NOERROR,              // exit code
            dwContinueCheckPoint, // checkpoint
            dwContinueWaitHint);  // wait hint

        if((hServicePauseEvent != NULL) && (hServiceContinueEvent != NULL))
        {
            fStatus = ResetEvent(hServicePauseEvent);

            if(fStatus == FALSE)
            {
                hr = HR_LOG(E_FAIL);
            }

            fStatus = SetEvent(hServiceContinueEvent);

            if(fStatus == FALSE)
            {
                hr = HR_LOG(E_FAIL);
            }
        }
        else
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    return(dwState);
}

//$--dwDoServiceCtrlStop--------------------------------------------------------
//  This function is called by ServiceCtrl whenever
//  someone calls ControlService to stop our service.
// -----------------------------------------------------------------------------
static DWORD dwDoServiceCtrlStop(          // RETURNS: service state
    VOID)                           // no arguments
{
    HRESULT hr       = NOERROR;
    DWORD   dwState  = SERVICE_RUNNING;
    DWORD   dwStatus = 0;
    BOOL    fStatus  = TRUE;

    DEBUGPUBLIC("dwDoServiceCtrlStop()\n");

    dwState = SERVICE_STOP_PENDING;

    // Report the status, specifying the checkpoint and wait-hint,
    // before setting the termination event.

    dwStopCheckPoint++;

    FServiceReportStatus(
        SERVICE_STOP_PENDING, // current state
        NOERROR,              // exit code
        NOERROR,              // exit code
        dwStopCheckPoint,     // checkpoint
        dwStopWaitHint);      // wait hint

    if(hServiceStopEvent != NULL)
    {
        fStatus = SetEvent(hServiceStopEvent);

        if(fStatus == FALSE)
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    return(dwState);
}

//$--ServiceCtrlProc------------------------------------------------------------
//  This function is called by the Service Controller whenever
//  someone calls ControlService in reference to our service.
// -----------------------------------------------------------------------------
static VOID WINAPI ServiceCtrlProc(         // RETURNS: nothing
    IN DWORD dwCtrlCode)            // control code
{
    HRESULT hr       = NOERROR;
    DWORD   dwState  = SERVICE_RUNNING;
    DWORD   dwStatus = 0;
    BOOL    fStatus  = FALSE;

    DEBUGPUBLIC("ServiceCtrlProc()\n");

    //
    // Handle the requested control code.
    //

    switch(dwCtrlCode) 
    {
        // Pause the service if it is running.
        case SERVICE_CONTROL_PAUSE:
            dwState = dwDoServiceCtrlPause();
            break;

        // Resume the paused service.
        case SERVICE_CONTROL_CONTINUE:
            dwState = dwDoServiceCtrlContinue();
            break;

        // Stop the service.
        case SERVICE_CONTROL_STOP:
            dwState = dwDoServiceCtrlStop();
            return;

        // Update the service status.
        case SERVICE_CONTROL_INTERROGATE:
            break;

        // Invalid control code
        default:
            break;
    }

    //
    // Send a status response.
    //

    fStatus = FServiceReportStatus(dwState, NOERROR, NOERROR, 0, 0);

    if(fStatus == FALSE)
    {
        hr = HR_LOG(E_FAIL);
    }
}

//$--_ServiceMain---------------------------------------------------------------
//  This function takes care of actually starting the service,
//  informing the service controller at each step along the way.
//  After launching the worker thread, it waits on the event
//  that the worker thread will signal at its termination.
// -----------------------------------------------------------------------------
VOID _ServiceMain(                   // RETURNS: nothing
    IN DWORD dwArgc,                // count of arguments
    IN LPSTR *lpszArgv)            // pointer to arguments
{
    HRESULT hr         = NOERROR;
    DWORD   dw         = 0;
    DWORD   dwThreadID = 0;
    BOOL    fStatus    = FALSE;

    DEBUGPUBLIC("_ServiceMain()");

    hr = CHK__ServiceMain(
        dwArgc,
        lpszArgv);

    if(FAILED(hr))
        return;

    // Register our service control handler:

    lstrcpyn(
        szServiceName,
        SzMakeServiceName(lpszArgv[0]),
        MAX_SERVICE_NAME_LENGTH);

    szServiceName[MAX_SERVICE_NAME_LENGTH] = 0;

    dwServiceArgc   = dwArgc;
    lpszServiceArgv = lpszArgv;

    if(fIsService == TRUE)
    {
        sshStatusHandle = RegisterServiceCtrlHandler(
            szServiceName,
            ServiceCtrlProc);

        if(sshStatusHandle == 0)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ssStatus.dwServiceSpecificExitCode = 0;

    // Report the status to Service Control Manager.

    dwStartCheckPoint++;

    if(FServiceReportStatus(
        SERVICE_START_PENDING,      // service state
        NOERROR,                    // exit code
        NOERROR,                    // exit code
        dwStartCheckPoint,          // checkpoint
        dwStartWaitHint) == FALSE)  // wait hint
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Create the event object. The control handler function signals
    // this event when it receives the "stop" control code.

    hServiceStopEvent = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if(hServiceStopEvent == (HANDLE)NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Create the event object. The control handler function signals
    // this event when it receives the "pause" control code.

    hServicePauseEvent = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if(hServicePauseEvent == (HANDLE)NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Create the event object. The control handler function signals
    // this event when it receives the "continue" control code.

    hServiceContinueEvent = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if(hServiceContinueEvent == (HANDLE)NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Create the event object. The application signals
    // this event when it is ready to "stop".

    hStopConfirmEvent = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if(hStopConfirmEvent == (HANDLE)NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Report the status to the service control manager.

    dwStartCheckPoint++;

    if(FServiceReportStatus(
        SERVICE_START_PENDING,      // service state
        NOERROR,                    // exit code
        NOERROR,                    // exit code
        dwStartCheckPoint,          // checkpoint
        dwStartWaitHint) == FALSE)  // wait hint
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Start the thread that performs the work of the service.
    hWorkerThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)WorkerThread,
        (LPVOID)hServiceStopEvent,
        0,
        &dwWorkerTID);

    if(hWorkerThread == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Report the status to the service control manager.
    if(FServiceReportStatus(
        SERVICE_RUNNING, // service state
        NOERROR,         // exit code
        NOERROR,         // exit code
        0,               // checkpoint
        0) == FALSE)     // wait hint
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Wait indefinitely until worker thread exits.
    //

    dw = WaitForSingleObject(hWorkerThread, INFINITE);

    if((dw != WAIT_OBJECT_0) && (dw != WAIT_ABANDONED))
    {
        hr = HR_LOG(E_FAIL);
    }

cleanup:

    CLOSEHANDLE(hWorkerThread);

    CLOSEHANDLE(hServiceStopEvent);

    CLOSEHANDLE(hServicePauseEvent);

    CLOSEHANDLE(hServiceContinueEvent);

    CLOSEHANDLE(hStopConfirmEvent);

    //
    // Try to report the stopped status to the service control manager.
    //

    if(sshStatusHandle != 0)
    {
        fStatus = FServiceReportStatus(
            SERVICE_STOPPED,
            dwSvcWin32ExitCode,
            dwSvcServiceSpecificExitCode,
            0,
            0);

        if(fStatus == FALSE)
        {
            hr = HR_LOG(E_FAIL);
        }
    }

    // When SERVICE MAIN FUNCTION returns in a single service
    // process, the StartServiceCtrlDispatcher function in
    // the main thread returns, terminating the process.

    return;
}

//$--HrWaitServiceStopConfirm---------------------------------------------------
//  This function is called to wait for the application to stop.
// -----------------------------------------------------------------------------
HRESULT HrWaitServiceStopConfirm(   // RETURNS: return code
    VOID)                           // no arguments
{
    HRESULT hr            = NOERROR;
    DWORD   dwT           = 0;
    DWORD   dwStopTimeOut = dwStopWaitHint/2;

    DEBUGPUBLIC("HrWaitServiceStopConfirm()\n");

    for(;;)
    {
        if(fIsService == TRUE)
        {
            // Report the status, specifying the checkpoint and wait-hint.

            dwStopCheckPoint++;

            FServiceReportStatus(
                SERVICE_STOP_PENDING, // current state
                NOERROR,              // exit code
                NOERROR,              // exit code
                dwStopCheckPoint,     // checkpoint
                dwStopWaitHint);      // wait hint
        }

        //
        // Wait until application has stopped or a timeout occurs.
        //

        dwT = WaitForSingleObject(hStopConfirmEvent, dwStopTimeOut);

        switch(dwT)
        {
        case (WAIT_OBJECT_0):
        case (WAIT_ABANDONED_0):
            hr = NOERROR;
            goto cleanup;
            break;
        case WAIT_TIMEOUT:
            break;
        default:
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

cleanup:

    RETURN(hr);
}

//$--SetServiceExitCode---------------------------------------------------------
//  This function is called by the application to set the service exit code.
//
//  dwWin32ExitCode
//
//      - specifies a Win32 error code that the service uses to
//        report an error that occurs when it is starting or
//        stopping. To return an error code specific to the service,
//        the service must set this value to
//        ERROR_SERVICE_SPECIFIC_ERROR to indicate that the
//        dwServiceSpecificExitCode member contains the error code.
//        The service should set this value to NO_ERROR when it is
//        running and on normal termination. 
//
//  dwServiceSpecificExitCode
//
//      - specifies a service specific error code that the
//        service returns when an error occurs while the service is
//        starting or stopping. This value is ignored unless the
//        dwWin32ExitCode member is set to ERROR_SERVICE_SPECIFIC_ERROR. 
//      
// -----------------------------------------------------------------------------
VOID SetServiceExitCode(
    IN DWORD dwWin32ExitCode,           // Win32 exit code
    IN DWORD dwServiceSpecificExitCode) // service specific exit code
{
    DEBUGPUBLIC("SetServiceExitCode()");

    dwSvcWin32ExitCode           = dwWin32ExitCode;
    dwSvcServiceSpecificExitCode = dwServiceSpecificExitCode;
}

//$--HrServiceConfirmStop----------------------------------------------------
//  This function is called by the application to indicate that it has stopped.
// -----------------------------------------------------------------------------
HRESULT HrServiceConfirmStop(    // RETURNS: return code
    VOID)                           // no arguments
{
    HRESULT hr      = NOERROR;
    BOOL    fStatus = TRUE;

    DEBUGPUBLIC("HrServiceConfirmStop()\n");

    if(hStopConfirmEvent != NULL)
    {
        fStatus = SetEvent(hStopConfirmEvent);

        if(fStatus == FALSE)
        {
            hr = HR_LOG(E_FAIL);
        }
    }
    else
    {
        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);
}

//------------------------------------------------------------------------------
// Utility functions...
//------------------------------------------------------------------------------

//$--FServiceReportStatus-------------------------------------------------------
//  This function is called by the private _ServiceMain() and
//  ServCtrlHandler() functions to update the service's status
//  to the service control manager.
// -----------------------------------------------------------------------------
BOOL FServiceReportStatus(              // RETURNS: TRUE if successful
    IN DWORD dwCurrentState,            // current state of service
    IN DWORD dwWin32ExitCode,           // service Win32 exit code
    IN DWORD dwServiceSpecificExitCode, // service specific exit code
    IN DWORD dwCheckPoint,              // check point number
    IN DWORD dwWaitHint)                // time to wait
{
    BOOL fResult = TRUE;

    DEBUGPUBLIC("FServiceReportStatus()\n");

    // Disable control requests until the service is started.

    if(dwCurrentState == SERVICE_START_PENDING)
    {
        ssStatus.dwControlsAccepted = 0;
    }
    else
    {
        ssStatus.dwControlsAccepted =
            SERVICE_ACCEPT_STOP |
            SERVICE_ACCEPT_PAUSE_CONTINUE;
    }

    // These SERVICE_STATUS members are set from parameters.

    ssStatus.dwCurrentState            = dwCurrentState;
    ssStatus.dwWin32ExitCode           = dwWin32ExitCode;
    ssStatus.dwServiceSpecificExitCode = dwServiceSpecificExitCode;
    ssStatus.dwCheckPoint              = dwCheckPoint;
    ssStatus.dwWaitHint                = dwWaitHint;

    // Report the status of the service to the service control manager.

    if(fIsService == TRUE)
    {
        fResult = SetServiceStatus(
            sshStatusHandle,    // service reference handle
            &ssStatus);         // SERVICE_STATUS structure

        if(fResult == FALSE)
        {
            // If an error occurs, stop the service.

            ServiceStop();
        }
    }

    return(fResult);
}

//$--ServiceStop-------------------------------------------------------------
//  This function can be used by any thread to stop the service.
// -----------------------------------------------------------------------------
VOID ServiceStop(                // RETURNS: nothing
    VOID)                           // no argument
{
    HRESULT hr      = NOERROR;
    BOOL    fStatus = TRUE;

    DEBUGPUBLIC("ServiceStop()\n");

    // Set a termination event to stop SERVICE MAIN FUNCTION.

    if(hServiceStopEvent != NULL)
    {
        fStatus = SetEvent(hServiceStopEvent);

        if(fStatus == FALSE)
        {
            hr = HR_LOG(E_FAIL);
        }
    }
}

//$--HrServiceWaitForControl----------------------------------------------------
//  The HrServiceWaitForControl function can be used by any thread to get or
//  wait for service control after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceWaitForControl(        // RETURNS: return code
    IN DWORD dwTimeout,                 // time-out interval in milliseconds
    OUT EDK_SERVICE_CONTROL_T *pedksc)  // pointer to service name buffer
{
    HRESULT hr          = NOERROR;
    DWORD   cObjects    = 3;
    HANDLE  hObjects[3] = {0};
    DWORD   dwResult    = WAIT_FAILED;

    DEBUGPUBLIC("HrServiceWaitForControl()\n");

    hr = CHK_HrServiceWaitForControl(
        dwTimeout,
        pedksc);

    if(FAILED(hr))
        RETURN(hr);

    hObjects[0] = hServiceStopEvent;
    hObjects[1] = hServicePauseEvent;
    hObjects[2] = hServiceContinueEvent;

    dwResult = WaitForMultipleObjects(cObjects, hObjects, FALSE, dwTimeout);

    *pedksc = EDK_SC_NONE;

    switch(dwResult)
    {
    case (WAIT_OBJECT_0):
        *pedksc = EDK_SC_STOP;
        break;
    case (WAIT_OBJECT_0+1):
        *pedksc = EDK_SC_PAUSE;
        break;
    case (WAIT_OBJECT_0+2):
        *pedksc = EDK_SC_CONTINUE;
        break;
    case (WAIT_ABANDONED_0):
        break;
    case (WAIT_ABANDONED_0+1):
        break;
    case (WAIT_ABANDONED_0+2):
        break;
    case WAIT_TIMEOUT:
        break;
    default:
        *pedksc = EDK_SC_STOP;

        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);
}

//$--HrServiceWaitForContinue---------------------------------------------------
//  The HrServiceWaitForContinue function can be used by any thread to get or
//  wait for service control after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceWaitForContinue(       // RETURNS: return code
    IN DWORD dwTimeout,                 // time-out interval in milliseconds
    OUT EDK_SERVICE_CONTROL_T *pedksc)  // pointer to service name buffer
{
    HRESULT hr          = NOERROR;
    DWORD   cObjects    = 2;
    HANDLE  hObjects[2] = {0};
    DWORD   dwResult    = WAIT_FAILED;

    DEBUGPUBLIC("HrServiceWaitForContinue()\n");

    hr = CHK_HrServiceWaitForContinue(
        dwTimeout,
        pedksc);

    if(FAILED(hr))
        RETURN(hr);

    hObjects[0] = hServiceStopEvent;
    hObjects[1] = hServiceContinueEvent;

    dwResult = WaitForMultipleObjects(cObjects, hObjects, FALSE, dwTimeout);

    *pedksc = EDK_SC_NONE;

    switch(dwResult)
    {
    case (WAIT_OBJECT_0):
        *pedksc = EDK_SC_STOP;
        break;
    case (WAIT_OBJECT_0+1):
        *pedksc = EDK_SC_CONTINUE;
        break;
    case (WAIT_ABANDONED_0):
        break;
    case (WAIT_ABANDONED_0+1):
        break;
    case WAIT_TIMEOUT:
        break;
    default:
        *pedksc = EDK_SC_STOP;

        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);
}

//$--HrServiceWaitForStop-------------------------------------------------------
//  The HrServiceWaitForStop function can be used by any thread to get or
//  wait for service control after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceWaitForStop(           // RETURNS: return code
    IN DWORD dwTimeout,                 // time-out interval in milliseconds
    OUT EDK_SERVICE_CONTROL_T *pedksc)  // pointer to service name buffer
{
    HRESULT hr          = NOERROR;
    DWORD   cObjects    = 1;
    HANDLE  hObjects[1] = {0};
    DWORD   dwResult    = WAIT_FAILED;

    DEBUGPUBLIC("HrServiceWaitForStop()\n");

    hr = CHK_HrServiceWaitForStop(
        dwTimeout,
        pedksc);

    if(FAILED(hr))
        RETURN(hr);

    hObjects[0] = hServiceStopEvent;

    dwResult = WaitForMultipleObjects(cObjects, hObjects, FALSE, dwTimeout);

    *pedksc = EDK_SC_NONE;

    switch(dwResult)
    {
    case (WAIT_OBJECT_0):
        *pedksc = EDK_SC_STOP;
        break;
    case (WAIT_ABANDONED_0):
        break;
    case WAIT_TIMEOUT:
        break;
    default:
        *pedksc = EDK_SC_STOP;

        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);
}

//$--HrServiceProcessControl---------------------------------------------------
//  Check for service control
// -----------------------------------------------------------------------------
HRESULT HrServiceProcessControl(       // RETURNS: return code
    VOID)                               // no arguments
{
    HRESULT               hr    = NOERROR;
    HRESULT               hrT   = NOERROR;
    EDK_SERVICE_CONTROL_T edksc = EDK_SC_NONE;

    DEBUGPUBLIC("HrServiceProcessControl()\n");

    for(;;)
    {
        switch(edksc)
        {
        case EDK_SC_PAUSE:
            // Wait for service to continue or stop
            hrT = HrServiceWaitForContinue(INFINITE, &edksc);
            break;
        default:
            // Wait for service to pause, continue or stop
            hrT = HrServiceWaitForControl(0, &edksc);
        }

        if(SUCCEEDED(hrT))
        {
            switch(edksc)
            {
            case EDK_SC_NONE:
                goto cleanup;
                break;
            case EDK_SC_PAUSE:
                break;
            case EDK_SC_CONTINUE:
                goto cleanup;
                break;
            case EDK_SC_STOP:
                hr = HR_LOG(EDK_E_SHUTDOWN_SERVICE);
                goto cleanup;
                break;
            default:
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }
        else
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

cleanup:

    RETURN(hr);
}

//$--HrFreeArgvW----------------------------------------------------------------
//  Free a wide character copy of argv[].
// -----------------------------------------------------------------------------
static HRESULT HrFreeArgvW(         // RETURNS: exit code
    IN     DWORD  dwArgc,           // Number of arguments
    IN OUT LPWSTR **lppszArgvW)     // pointer to wide character command line
{
    HRESULT hr     = NOERROR;
    DWORD   i      = 0;
    LPWSTR  *lpwsz = NULL;

    DEBUGPRIVATE("HrFreeArgvW()\n");

    hr = CHK_HrFreeArgvW(
        dwArgc,
        lppszArgvW);

    if(FAILED(hr))
        RETURN(hr);

    lpwsz = *lppszArgvW;

    if(lpwsz != NULL)
    {
        for(i = 0 ; i < dwArgc ; i++)
        {
            if(lpwsz[i] != NULL)
            {
                free(lpwsz[i]);
                lpwsz[i] = NULL;
            }
        }

        free(lpwsz);
        lpwsz = NULL;
    }

    *lppszArgvW = NULL;

    RETURN(hr);
}

//$--ControlHandler-------------------------------------------------------------
//  Handle console control events.
// -----------------------------------------------------------------------------
static BOOL WINAPI ControlHandler(          // RETURNS: TRUE if successful
    IN DWORD dwCtrlType)                    // control event type
{
    switch( dwCtrlType )
    {
    case CTRL_BREAK_EVENT:  // use Ctrl+C or Ctrl+Break to simulate
    case CTRL_C_EVENT:      // SERVICE_CONTROL_STOP in debug mode

        ServiceStop();

        return(TRUE);
        break;
    default:
        ;
    }

    return(FALSE);
}

//$--WinMain--------------------------------------------------------------------
//  This function starts the service.
// -----------------------------------------------------------------------------
int APIENTRY WinMain(               // RETURNS: exit code
    IN  HINSTANCE hInstance,        // Handle to instance of application
    IN  HINSTANCE hPrevInstance,    // Handle to previous instance
    IN  LPSTR lpszCmdLine,          // Pointer to command line
    IN  int nCmdShow)               // Argument for ShowWindow()
{
    HRESULT hr       = NOERROR;
    DWORD   dwArgc   = 0;
    LPSTR* lpszArgv = NULL;

    SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)_ServiceMain },
        { NULL, NULL }
    };

    DEBUGPUBLIC("WinMain()\n");

    //
    // Parse command line
    //

    dwArgc   = (DWORD) __argc;
    lpszArgv = __argv;

    //
    // Check if running as a service
    //

    if((dwArgc > 1) && (lstrcmpi(lpszArgv[1], "NOTSERV") == 0))
    {
        fIsService = FALSE;
    }

    WinMainContext.hInstance     = hInstance;
    WinMainContext.hPrevInstance = hPrevInstance;
    WinMainContext.lpszCmdLine   = lpszCmdLine;
    WinMainContext.nCmdShow      = nCmdShow;

    if(fIsService == TRUE)
    {
        //
        // Run as a service
        //

        if(StartServiceCtrlDispatcher(dispatchTable) == FALSE)
        {
            hr = HR_LOG(E_FAIL);

            ServiceStop();
        }
    }
    else
    {
        SetConsoleCtrlHandler(ControlHandler, TRUE);

        if(dwArgc == 2)
        {
            hr = HR_LOG(E_FAIL);
        }
        else
        {
            _ServiceMain(dwArgc-2, lpszArgv+2);  // NOTE:  if we're running by command line,
                                                // need to pass arg after 'NOTSERV' as service
                                                // name rather than exe name.
        }
    }

    return(0);
}

//$--WndProc--------------------------------------------------------------------
//  Processes messages
// -----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(           // RETURNS: LRESULT
    IN HWND hWnd,                   // window handle
    IN UINT message,                // type of message
    IN WPARAM uParam,               // additional information
    IN LPARAM lParam)               // additional information
{
    HRESULT hr        = NOERROR;
    HRESULT hrT       = NOERROR;
    LRESULT lRetVal   = 0;
    BOOL    fStatus   = TRUE;
    DWORD   dw        = 0;

    DEBUGPUBLIC("WndProc()\n");

    switch( message)
    {
    //  Closing the window will signal the shutdown event object and cause
    //  WaitShutdown to send a WM_DESTROY message and end its thread.
    case WM_CLOSE:
		ServiceStop();
        break;

    //  Before destroying the window, call NTServiceShutdown.
    case WM_DESTROY:

        //
        // Wait for application to stop.
        //

        hrT = HR_LOG(HrWaitServiceStopConfirm());

        //
        // Wait for service thread to exit.
        //

        if(hServiceThread != NULL)
        {
            dw = WaitForSingleObject(hServiceThread, WAIT_DESTROY);

            if((dw != WAIT_OBJECT_0) && (dw != WAIT_ABANDONED_0))
            {
                hr = HR_LOG(E_FAIL);
            }

            CLOSEHANDLE(hServiceThread);
        }

        hrT = HR_LOG(HrServiceShutdown());

        //
        // Cause message loop in WorkerThread() to terminate.
        //

        PostQuitMessage(0);
        break;

    //  Paint the icon if its background is erased.
    case WM_ICONERASEBKGND:

        DefWindowProc(hWnd, WM_ICONERASEBKGND, uParam, lParam);
        PostMessage(hWnd, WM_PAINTICON, 0, 0);
        break;

    //  Users are not allowed to "Switch To" this application via Task Manager
    //  since it has no main window.  According to the API, if the icon can not
    //  be opened, this message should return FALSE.
    case WM_QUERYOPEN:

        lRetVal = (LRESULT)FALSE;
        break;

    //  Do the default action for any other message.
    default:

        lRetVal = DefWindowProc(hWnd, message, uParam, lParam);
        break;
    }

    return(lRetVal);
}
