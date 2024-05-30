/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    construct.c

Abstract:

    Implementation of the BITMAPWINDOW struct contruction / destruction 

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"

//////////////////////////////////////////////////////////////////////////
//
// CreateBitmapWindow
//
// Routine Description:
//   Creates a new bitmap window
//
// Arguments:
//   int nCmdShow                          show state
//   BitmapWindow_eOpenMethod eOpenMethod  how / where to open
//   PCTSTR pFileName                      name of the file to open
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
CreateBitmapWindow(
    int                      nCmdShow,
    BitmapWindow_eOpenMethod eOpenMethod,
    PCTSTR                   pFileName
)
{
    USES_BRESULT;
    PBITMAPWINDOW pWin;
#ifdef MULTIMON_ENABLED
    int           nNumMonitors = GetSystemMetrics(SM_CMONITORS);
#else  //MULTIMON_ENABLED
    int           nNumMonitors = 1;
#endif //MULTIMON_ENABLED

    CHECK(pWin = (PBITMAPWINDOW) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        sizeof(BITMAPWINDOW) + 
        sizeof(MONITORDATA) * (nNumMonitors - 1)
    ));

    CHECK(BitmapWindow_Construct(pWin, nNumMonitors));

    CHECK(BitmapWindow_Create(pWin));

    if (eOpenMethod != eOpenEmpty) {
        
        if (!BitmapWindow_OpenDocument(pWin, eOpenMethod, pFileName)) {

            PostMessage(pWin->m_hWnd, WM_DESTROY, 0, 0);
            return FALSE;
        }
    }

    ShowWindow(pWin->m_hWnd, nCmdShow);

    CHECK(UpdateWindow(pWin->m_hWnd));

    DragAcceptFiles(pWin->m_hWnd, TRUE);

    BEGIN_CLEANUP;

    if (!BRESULT && pWin) {

        CHECK(GlobalFree(pWin) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_Construct
//
// Routine Description:
//   Initializes a new BitmapWindow structure
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the structure
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_Construct(
    PBITMAPWINDOW pWin,
    int           nNumMonitors
)
{
    USES_BRESULT;

#ifdef DEBUG
    
    pWin->m_dwValid = '-OK-';

#endif //DEBUG

#ifdef ICM_ENABLED

    pWin->m_lcsRenderIntent = LCS_GM_IMAGES;
    pWin->m_lcsProofIntent  = LCS_GM_IMAGES;

#endif //ICM_ENABLED

    pWin->m_nNumMonitors = nNumMonitors;

    if (g_bTwainFunctionalityPresent) {

        pWin->m_TwainState = State_2_Source_Manager_Loaded;

    } else {

        pWin->m_TwainState = State_1_Pre_Session;
    }

    CHECK(BitmapWindow_ReadRegistrySettings(pWin));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_Destruct
//
// Routine Description:
//   Performs shutdown operations before freeing the BitmapWindow structure
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the structure
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_Destruct(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    ASSERT(BitmapWindow_AssertValid(pWin));

    BEGIN_CLEANUP;

    CHECK(BitmapWindow_SaveRegistrySettings(pWin));

    ASSERT(pWin->m_TwainState <= State_3_Source_Manager_Open);

    if (pWin->m_TwainState == State_3_Source_Manager_Open) {

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            0, 
            DG_CONTROL, 
            DAT_PARENT, 
            MSG_CLOSEDSM, 
            (TW_MEMREF) &pWin->m_hWnd
        ) == TWRC_SUCCESS);

        pWin->m_TwainState = State_2_Source_Manager_Loaded;
    }

    CHECK(BitmapWindow_DeleteContents(pWin));

#ifdef DEBUG
    
    pWin->m_dwValid = 'FREE';

#endif //DEBUG
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_DeleteContents
//
// Routine Description:
//   Frees the dynamically allocated fields
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the object  
// 
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_DeleteContents(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    int nMonitor;

    ASSERT(BitmapWindow_AssertValid(pWin));

    BEGIN_CLEANUP;

    if (pWin->m_pDIB) {

        CHECK(GlobalFree(pWin->m_pDIB) == 0);
        pWin->m_pDIB = 0;
    }

    if (pWin->m_pLogPal) {

        CHECK(GlobalFree(pWin->m_pLogPal) == 0);
        pWin->m_pLogPal = 0;
    }

    if (pWin->m_hIcon) {

        CHECK(DestroyIcon(pWin->m_hIcon));
        pWin->m_hIcon = 0;
    }

    if (pWin->m_hDevMode) {

        CHECK(GlobalFree(pWin->m_hDevMode) == 0);
        pWin->m_hDevMode = 0;
    }

    if (pWin->m_hDevNames) {

        CHECK(GlobalFree(pWin->m_hDevNames) == 0);
        pWin->m_hDevNames = 0;
    }

    for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

        if (pWin->m_Monitor[nMonitor].hDIBSect) {

            CHECK(DeleteObject(pWin->m_Monitor[nMonitor].hDIBSect));
            pWin->m_Monitor[nMonitor].hDIBSect = 0;
        }

        if (pWin->m_Monitor[nMonitor].hPalette) {
            
            CHECK(DeleteObject(pWin->m_Monitor[nMonitor].hPalette));
            pWin->m_Monitor[nMonitor].hPalette = 0;
        }
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_AssertValid
//
// Routine Description:
//   Debug routine to check the validity of the BitmapWindow structure.
//   The check is performed only in DEBUG builds
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the structure
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_AssertValid(
    PBITMAPWINDOW pWin
)
{
#ifdef DEBUG

    return pWin && pWin->m_dwValid == '-OK-';

#else //DEBUG

    UNREFERENCED_PARAMETER(pWin);
    
    return TRUE;

#endif //DEBUG
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_RegisterClass
//
// Routine Description:
//   Registers the BitmapWindow class
//
// Arguments:
//   none
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_RegisterClass()
{
    USES_BRESULT;
    WNDCLASSEX  wcex;

    wcex.cbSize         = sizeof(wcex);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = BitmapWindow_WindowProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = g_hInstance;
    wcex.hIcon          = LoadIcon(0, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(0, IDC_ARROW);
    wcex.hbrBackground  = 0;
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
    wcex.lpszClassName  = BitmapWindow_szClassName;
    wcex.hIconSm        = 0;

    CHECK(RegisterClassEx(&wcex));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_Create
//
// Routine Description:
//   Reads the window coordinates from registry and creates the window
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_Create(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    HDC   hDC = 0;
    HKEY  hKey = 0;
    DWORD dwType;
    RECT  rWindow;
    DWORD dwDataSize = sizeof(rWindow);
    int   nMonitor = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    // get a DC for the entire screen

    CHECK(hDC = GetDC(0));

    // Read the initial window position from the registry

    if (
        RegOpenKeyEx(
            HKEY_CURRENT_USER,
            BitmapWindow_szRegKeyName,
            0,
            KEY_QUERY_VALUE,
            &hKey
        ) != ERROR_SUCCESS 

        ||
        
        RegQueryValueEx(
            hKey,
            _T("Window Position"),
            0,
            &dwType,
            (PBYTE) &rWindow,
            &dwDataSize
        ) != ERROR_SUCCESS

        ||

        !PtVisible(
            hDC, 
            rWindow.left, 
            rWindow.top
        )
    ) {

        // If we cannot open the registry key 
        // or we cannot read the value of initial window position
        // or the upper left corner is not in the visible region
        // use the default size and position.

        rWindow.left    = CW_USEDEFAULT;
        rWindow.top     = CW_USEDEFAULT;
        rWindow.right   = CW_USEDEFAULT;
        rWindow.bottom  = CW_USEDEFAULT;
    }

    CHECK(pWin->m_hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        BitmapWindow_szClassName,
        ResourceString(IDS_APP_NAME),
        WS_OVERLAPPEDWINDOW,
        rWindow.left,
        rWindow.top,
        rWindow.right,
        rWindow.bottom,
        0,
        0,
        g_hInstance,
        0
    ));

    // Attach the piggyback BitmapWindow pointer to the GWL_USERDATA field

    SetWindowLongPtr(
        pWin->m_hWnd, 
        GWLP_USERDATA, 
        (LONG_PTR) pWin
    );

    // Fill in the monitor, default printer and scanner data

#ifdef MULTIMON_ENABLED

    CHECK(EnumDisplayMonitors(
        0,
        0,
        BitmapWindow_MonitorEnumProc,
        (LPARAM) pWin
    ));

#else //MULTIMON_ENABLED

    _tcscpy(
        pWin->m_Monitor[0].szName,
        _T("DISPLAY")
    );

#endif //MULTIMON_ENABLED

    CHECK(BitmapWindow_GetDefaultPrinter(pWin));

    CHECK(BitmapWindow_FillTwainInfo(pWin));

#ifdef ICM_ENABLED

    // Fill in the default ICM data

    for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

        CHECK(BitmapWindow_FillMonitorICMInfo(
            pWin,
            nMonitor
        ));
    }

    CHECK(BitmapWindow_FillPrinterICMInfo(pWin));

    CHECK(BitmapWindow_FillTwainICMInfo(pWin));

#endif //ICM_ENABLED

    BEGIN_CLEANUP;

    if (hDC) {

        CHECK(ReleaseDC(0, hDC));
    }

    if (hKey) {

        CHECK0(RegCloseKey(hKey));
    }

    return BRESULT;
}

#ifdef MULTIMON_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_ResizeStruct
//
// Routine Description:
//   Reallocates the BITMAPWINDOW struct according to the new number of 
//   display monitors
//
// Arguments:
//  PBITMAPWINDOW pWin           pointer to the object  
//  int           nNumMonitors   number of display monitors
//
// Return Value:
//   Pointer to the new object / zero on error
//

PBITMAPWINDOW
BitmapWindow_ResizeStruct(
    PBITMAPWINDOW pWin,
    int           nNewNumMonitors
)
{
    USES_BRESULT;
    PBITMAPWINDOW pNewWin = 0;
    int           nMonitor;

    ASSERT(BitmapWindow_AssertValid(pWin));

    // allocate the new zero initialized memory

    CHECK(pNewWin = (PBITMAPWINDOW) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT,
        sizeof(BITMAPWINDOW) + 
        sizeof(MONITORDATA) * (nNewNumMonitors - 1)
    ));

    // copy the common data
    
    CopyMemory(
        pNewWin,
        pWin,
        FIELD_OFFSET(BITMAPWINDOW, m_nNumMonitors)
    );

    // fill in the new monitor data

    pNewWin->m_nNumMonitors = nNewNumMonitors;

    CHECK(EnumDisplayMonitors(
        0,
        0,
        BitmapWindow_MonitorEnumProc,
        (LPARAM) pNewWin
    ));

    // attach the new struct pointer to the window word

    CHECK(SetWindowLongPtr(
        pWin->m_hWnd, 
        GWLP_USERDATA, 
        (LONG_PTR) pNewWin
    ));

    // free the old entries associated with the monitors

    for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

        if (pWin->m_Monitor[nMonitor].hDIBSect) {

            CHECK(DeleteObject(pWin->m_Monitor[nMonitor].hDIBSect));
        }

        if (pWin->m_Monitor[nMonitor].hPalette) {
            
            CHECK(DeleteObject(pWin->m_Monitor[nMonitor].hPalette));
        }
    }

    // free the old struct

    CHECK(GlobalFree(pWin) == 0);

    BEGIN_CLEANUP;

    if (!BRESULT && pNewWin) {

        CHECK(GlobalFree(pNewWin) == 0);
    }

    return BRESULT ? pNewWin : 0;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_MonitorEnumProc
//
// Routine Description:
//   
//
// Arguments:
//  HMONITOR hMonitor    handle to display monitor
//  HDC      hdcMonitor  handle to monitor-appropriate device context  
//  PRECT    prcMonitor  pointer to monitor intersection rectangle  
//  LPARAM   dwData      pointer to BITMAPWINDOW struct
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CALLBACK
BitmapWindow_MonitorEnumProc(
    HMONITOR hMonitor,
    HDC      hdcMonitor,
    PRECT    prcMonitor,
    LPARAM   dwData
)
{
    USES_BRESULT;
    PBITMAPWINDOW pWin = (PBITMAPWINDOW) dwData;
    MONITORINFOEX miex;
    int           nMonitor;

    ASSERT(BitmapWindow_AssertValid(pWin) && hMonitor);
    UNREFERENCED_PARAMETER(hdcMonitor);
    UNREFERENCED_PARAMETER(prcMonitor);

    // get the monitor name

    miex.cbSize = sizeof(miex);

    CHECK(GetMonitorInfo(
        hMonitor,
        (LPMONITORINFO) &miex
    ));

    // find this monitor's entry (or an empty one) in our monitors array

    for (
        nMonitor = 0; 
        pWin->m_Monitor[nMonitor].szName[0] != '\0' &&
        _tcscmp(pWin->m_Monitor[nMonitor].szName, miex.szDevice) != 0;
        ++nMonitor
    );

    ASSERT(nMonitor < pWin->m_nNumMonitors);

    // copy the monitor name and monitor rectangle

    _tcscpy(
        pWin->m_Monitor[nMonitor].szName,
        miex.szDevice
    );

    
    // store the monitor rectangle in screen coordinates

    pWin->m_Monitor[nMonitor].rMonitorScreen = miex.rcMonitor;

    BEGIN_CLEANUP;

    return BRESULT;
}

#endif //MULTIMON_ENABLED

