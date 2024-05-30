/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    mmon.c

Abstract:

    Implementation of the multi monitor support functions

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"

#ifdef MULTIMON_ENABLED

typedef struct _MONITORENUMPROCDATA {

    PBITMAPWINDOW    pWin;
    LPARAM           lParam;
    BOOL             bResult;
    MULTIMONCALLBACK pfnCallback;

} MONITORENUMPROCDATA, *PMONITORENUMPROCDATA;

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_MonitorEnumStubProc
//
// Routine Description:
//   Stub function for multi-monitor enabled function calls. 
//
// Arguments:
//  HMONITOR hMonitor    handle to display monitor
//  HDC      hdcMonitor  handle to monitor-appropriate device context  
//  PRECT    prcMonitor  pointer to monitor intersection rectangle  
//  LPARAM   dwData      pointer to MONITORENUMPROCDATA struct
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CALLBACK
BitmapWindow_MonitorEnumStubProc(
    HMONITOR hMonitor,
    HDC      hdcMonitor,
    PRECT    prcMonitor,
    LPARAM   dwData
)
{
    USES_BRESULT;
    PMONITORENUMPROCDATA pData  = (PMONITORENUMPROCDATA) dwData;
    MONITORINFOEX        miex;
    int                  nMonitor;

    ASSERT(BitmapWindow_AssertValid(pData->pWin) && hMonitor && hdcMonitor);
    UNREFERENCED_PARAMETER(prcMonitor);

    // get the monitor name

    miex.cbSize = sizeof(miex);

    CHECK(GetMonitorInfo(
        hMonitor,
        (LPMONITORINFO) &miex
    ));

    // find the monitor name in our monitors array

    for (
        nMonitor = 0;
        nMonitor < pData->pWin->m_nNumMonitors &&
        _tcscmp(pData->pWin->m_Monitor[nMonitor].szName, miex.szDevice);
        ++nMonitor
    );

    ASSERT(nMonitor < pData->pWin->m_nNumMonitors);

    // call the callback

    CHECK((*pData->pfnCallback)(
        pData->pWin,
        nMonitor,
        hdcMonitor,
        pData->lParam
    ));

    BEGIN_CLEANUP;

    // store the result

    pData->bResult = BRESULT;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_MonitorEnumStubProc
//
// Routine Description:
//
// Arguments:
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
BitmapWindow_MultimonCall(
    MULTIMONCALLBACK pfnCallback,
    PBITMAPWINDOW    pWin,
    HDC              hDC,
    LPARAM           lParam
)
{
    MONITORENUMPROCDATA mepd;

    mepd.pWin        = pWin;
    mepd.lParam      = lParam;
    mepd.pfnCallback = pfnCallback;

    return EnumDisplayMonitors(
        hDC,
        0,
        BitmapWindow_MonitorEnumStubProc,
        (LPARAM) &mepd
    );
}

#else //MULTIMON_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_MonitorEnumStubProc
//
// Routine Description:
//
// Arguments:
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
BitmapWindow_MultimonCall(
    MULTIMONCALLBACK pfnCallback,
    PBITMAPWINDOW    pWin,
    HDC              hDC,
    LPARAM           lParam
)
{
    return pfnCallback(
        pWin,
        0,
        hDC,
        lParam
    );
}

#endif //MULTIMON_ENABLED

