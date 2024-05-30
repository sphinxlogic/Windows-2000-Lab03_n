/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
	mmstubs.h

Abstract:
	
	Stubs for Multi Monitor functions

--*/

#ifndef MMSTUBS_H
#define MMSTUBS_H

extern BOOL     g_bMultiMonitorFunctionalityPresent;

extern int      WINAPI xGetSystemMetrics(int nIndex);
extern int      (WINAPI* g_pfnGetSystemMetrics)(int nIndex);
extern HMONITOR (WINAPI* g_pfnMonitorFromWindow)(HWND, DWORD);
extern HMONITOR (WINAPI* g_pfnMonitorFromRect)(LPCRECT, DWORD);
extern HMONITOR (WINAPI* g_pfnMonitorFromPoint)(POINT, DWORD);
extern BOOL     (WINAPI* g_pfnGetMonitorInfoA)(HMONITOR, LPMONITORINFO);
extern BOOL     (WINAPI* g_pfnGetMonitorInfoW)(HMONITOR, LPMONITORINFO);
extern BOOL     (WINAPI* g_pfnEnumDisplayMonitors)(HDC, LPCRECT, MONITORENUMPROC, LPARAM);
extern BOOL     (WINAPI* g_pfnEnumDisplayDevicesA)(PVOID, DWORD, PDISPLAY_DEVICEA, DWORD);
extern BOOL     (WINAPI* g_pfnEnumDisplayDevicesW)(PVOID, DWORD, PDISPLAY_DEVICEW, DWORD);

#define GetSystemMetrics    xGetSystemMetrics
#define MonitorFromWindow   (*g_pfnMonitorFromWindow)
#define MonitorFromRect     (*g_pfnMonitorFromRect)
#define MonitorFromPoint    (*g_pfnMonitorFromPoint)
#define GetMonitorInfoA     (*g_pfnGetMonitorInfoA)
#define GetMonitorInfoW     (*g_pfnGetMonitorInfoW)
#define EnumDisplayMonitors (*g_pfnEnumDisplayMonitors)
#define EnumDisplayDevicesA (*g_pfnEnumDisplayDevicesA)
#define EnumDisplayDevicesW (*g_pfnEnumDisplayDevicesW)

VOID InitMultiMonitorStubs();

#endif //MMSTUBS_H




#ifdef IMPLEMENT_MULTIMON_STUBS

//-----------------------------------------------------------------------------
//
// fake implementations of Monitor APIs that work with the primary display
// no special parameter validation is made since these run in client code
//
//-----------------------------------------------------------------------------

int 
WINAPI
xGetSystemMetrics(
	int nIndex
)
{
	if (g_bMultiMonitorFunctionalityPresent) {
		
		return (*g_pfnGetSystemMetrics)(nIndex);
	}

    switch (nIndex)
    {
    case SM_CMONITORS:
    case SM_SAMEDISPLAYFORMAT:
        return 1;

    case SM_XVIRTUALSCREEN:
    case SM_YVIRTUALSCREEN:
        return 0;

    case SM_CXVIRTUALSCREEN:
        nIndex = SM_CXSCREEN;
        break;

    case SM_CYVIRTUALSCREEN:
        nIndex = SM_CYSCREEN;
        break;
    }

    return (*g_pfnGetSystemMetrics)(nIndex);
}

#define xPRIMARY_MONITOR ((HMONITOR)0x12340042)

HMONITOR 
WINAPI
xMonitorFromPoint(
	POINT ptScreenCoords, 
	DWORD dwFlags
)
{
    if ((dwFlags & (MONITOR_DEFAULTTOPRIMARY | MONITOR_DEFAULTTONEAREST)) ||
        ((ptScreenCoords.x >= 0) &&
        (ptScreenCoords.x < (*g_pfnGetSystemMetrics)(SM_CXSCREEN)) &&
        (ptScreenCoords.y >= 0) &&
        (ptScreenCoords.y < (*g_pfnGetSystemMetrics)(SM_CYSCREEN))))
    {
        return xPRIMARY_MONITOR;
    }

    return NULL;
}

HMONITOR 
WINAPI
xMonitorFromRect(
	LPCRECT lprcScreenCoords, 
	DWORD dwFlags
)
{
    if ((dwFlags & (MONITOR_DEFAULTTOPRIMARY | MONITOR_DEFAULTTONEAREST)) ||
        ((lprcScreenCoords->right > 0) &&
        (lprcScreenCoords->bottom > 0) &&
        (lprcScreenCoords->left < (*g_pfnGetSystemMetrics)(SM_CXSCREEN)) &&
        (lprcScreenCoords->top < (*g_pfnGetSystemMetrics)(SM_CYSCREEN))))
    {
        return xPRIMARY_MONITOR;
    }

    return NULL;
}

HMONITOR 
WINAPI
xMonitorFromWindow(
	HWND hWnd, 
	DWORD dwFlags
)
{
    WINDOWPLACEMENT wp;

    if (dwFlags & (MONITOR_DEFAULTTOPRIMARY | MONITOR_DEFAULTTONEAREST))
        return xPRIMARY_MONITOR;

    if (IsIconic(hWnd) ?
            GetWindowPlacement(hWnd, &wp) :
            GetWindowRect(hWnd, &wp.rcNormalPosition)) {

        return xMonitorFromRect(&wp.rcNormalPosition, dwFlags);
    }

    return NULL;
}

BOOL 
WINAPI
xGetMonitorInfo(
	HMONITOR hMonitor, 
	LPMONITORINFO lpMonitorInfo
)
{
    RECT rcWork;

    if ((hMonitor == xPRIMARY_MONITOR) &&
        lpMonitorInfo &&
        (lpMonitorInfo->cbSize >= sizeof(MONITORINFO)) &&
        SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcWork, 0))
    {
        lpMonitorInfo->rcMonitor.left = 0;
        lpMonitorInfo->rcMonitor.top  = 0;
        lpMonitorInfo->rcMonitor.right  = (*g_pfnGetSystemMetrics)(SM_CXSCREEN);
        lpMonitorInfo->rcMonitor.bottom = (*g_pfnGetSystemMetrics)(SM_CYSCREEN);
        lpMonitorInfo->rcWork = rcWork;
        lpMonitorInfo->dwFlags = MONITORINFOF_PRIMARY;

        return TRUE;
    }

    return FALSE;
}

BOOL 
WINAPI
xGetMonitorInfoA(
	HMONITOR hMonitor, 
	LPMONITORINFO lpMonitorInfo
)
{
	if (xGetMonitorInfo(hMonitor, lpMonitorInfo)) {

        if (lpMonitorInfo->cbSize >= sizeof(MONITORINFOEX))
            strcpy(((MONITORINFOEXA*)lpMonitorInfo)->szDevice, "DISPLAY");

		return TRUE;
	}

	return FALSE;
}

BOOL 
WINAPI
xGetMonitorInfoW(
	HMONITOR hMonitor, 
	LPMONITORINFO lpMonitorInfo
)
{
	if (xGetMonitorInfo(hMonitor, lpMonitorInfo)) {

        if (lpMonitorInfo->cbSize >= sizeof(MONITORINFOEX))
            wcscpy(((MONITORINFOEXW*)lpMonitorInfo)->szDevice, L"DISPLAY");

		return TRUE;
	}

	return FALSE;
}

BOOL 
WINAPI
xEnumDisplayMonitors(
        HDC             hdcOptionalForPainting,
        LPCRECT         lprcEnumMonitorsThatIntersect,
        MONITORENUMPROC lpfnEnumProc,
        LPARAM          dwData
)
{
    RECT rcLimit;

    if (!lpfnEnumProc)
        return FALSE;

    rcLimit.left   = 0;
    rcLimit.top    = 0;
    rcLimit.right  = (*g_pfnGetSystemMetrics)(SM_CXSCREEN);
    rcLimit.bottom = (*g_pfnGetSystemMetrics)(SM_CYSCREEN);

    if (hdcOptionalForPainting)
    {
        RECT    rcClip;
        POINT   ptOrg;

        switch (GetClipBox(hdcOptionalForPainting, &rcClip))
        {
        default:
            if (!GetDCOrgEx(hdcOptionalForPainting, &ptOrg))
                return FALSE;

            OffsetRect(&rcLimit, -ptOrg.x, -ptOrg.y);
            if (IntersectRect(&rcLimit, &rcLimit, &rcClip) &&
                (!lprcEnumMonitorsThatIntersect ||
                     IntersectRect(&rcLimit, &rcLimit, lprcEnumMonitorsThatIntersect))) {

                break;
            }
            //fall thru
        case NULLREGION:
             return TRUE;
        case ERROR:
             return FALSE;
        }
    } else {
        if (    lprcEnumMonitorsThatIntersect &&
                !IntersectRect(&rcLimit, &rcLimit, lprcEnumMonitorsThatIntersect)) {

            return TRUE;
        }
    }

    return lpfnEnumProc(
            xPRIMARY_MONITOR,
            hdcOptionalForPainting,
            &rcLimit,
            dwData);
}

BOOL 
WINAPI
xEnumDisplayDevicesA(
    PVOID Unused,
    DWORD iDevNum,
    PDISPLAY_DEVICEA lpDisplayDevice,
    DWORD dwFlags
)
{
    if (Unused != NULL)
        return FALSE;

    if (iDevNum != 0)
        return FALSE;

    if (lpDisplayDevice == NULL || lpDisplayDevice->cb < sizeof(DISPLAY_DEVICE))
        return FALSE;

    strcpy((CHAR *)lpDisplayDevice->DeviceName,   "DISPLAY");
    strcpy((CHAR *)lpDisplayDevice->DeviceString, "DISPLAY");
    lpDisplayDevice->StateFlags = DISPLAY_DEVICE_ATTACHED_TO_DESKTOP | DISPLAY_DEVICE_PRIMARY_DEVICE;

    return TRUE;
}

BOOL 
WINAPI
xEnumDisplayDevicesW(
    PVOID Unused,
    DWORD iDevNum,
    PDISPLAY_DEVICEW lpDisplayDevice,
    DWORD dwFlags
)
{
    if (Unused != NULL)
        return FALSE;

    if (iDevNum != 0)
        return FALSE;

    if (lpDisplayDevice == NULL || lpDisplayDevice->cb < sizeof(DISPLAY_DEVICE))
        return FALSE;

    wcscpy((WCHAR *)lpDisplayDevice->DeviceName,   L"DISPLAY");
    wcscpy((WCHAR *)lpDisplayDevice->DeviceString, L"DISPLAY");
    lpDisplayDevice->StateFlags = DISPLAY_DEVICE_ATTACHED_TO_DESKTOP | DISPLAY_DEVICE_PRIMARY_DEVICE;

    return TRUE;
}

#undef xPRIMARY_MONITOR

int      (WINAPI* g_pfnGetSystemMetrics)(int nIndex)                               = 0;
HMONITOR (WINAPI* g_pfnMonitorFromWindow)(HWND, DWORD)                             = xMonitorFromWindow;
HMONITOR (WINAPI* g_pfnMonitorFromRect)(LPCRECT, DWORD)                            = xMonitorFromRect;
HMONITOR (WINAPI* g_pfnMonitorFromPoint)(POINT, DWORD)                             = xMonitorFromPoint;
BOOL     (WINAPI* g_pfnGetMonitorInfoA)(HMONITOR, LPMONITORINFO)                   = xGetMonitorInfoA;
BOOL     (WINAPI* g_pfnGetMonitorInfoW)(HMONITOR, LPMONITORINFO)                   = xGetMonitorInfoW;
BOOL     (WINAPI* g_pfnEnumDisplayMonitors)(HDC, LPCRECT, MONITORENUMPROC, LPARAM) = xEnumDisplayMonitors;
BOOL     (WINAPI* g_pfnEnumDisplayDevicesA)(PVOID, DWORD, PDISPLAY_DEVICEA, DWORD) = xEnumDisplayDevicesA;
BOOL     (WINAPI* g_pfnEnumDisplayDevicesW)(PVOID, DWORD, PDISPLAY_DEVICEW, DWORD) = xEnumDisplayDevicesW;

BOOL     g_bMultiMonitorFunctionalityPresent = FALSE;

#define StoreProcAddress(hModule, ProcName, Proc) \
	(pfn = GetProcAddress(hModule, ProcName), pfn ? *(FARPROC*) Proc = pfn : 0)

VOID InitMultiMonitorStubs()
{
	HMODULE hUser32;
	FARPROC pfn;

	g_bMultiMonitorFunctionalityPresent = 
		(hUser32 = GetModuleHandle(_T("USER32"))) &&
        StoreProcAddress(hUser32, "GetSystemMetrics",    &g_pfnGetSystemMetrics   ) &&
        StoreProcAddress(hUser32, "MonitorFromWindow",   &g_pfnMonitorFromWindow  ) &&
        StoreProcAddress(hUser32, "MonitorFromRect",     &g_pfnMonitorFromRect    ) &&
        StoreProcAddress(hUser32, "MonitorFromPoint",    &g_pfnMonitorFromPoint   ) &&
        StoreProcAddress(hUser32, "EnumDisplayMonitors", &g_pfnEnumDisplayMonitors) &&
        StoreProcAddress(hUser32, "GetMonitorInfoA",     &g_pfnGetMonitorInfoA    ) &&
        StoreProcAddress(hUser32, "GetMonitorInfoW",     &g_pfnGetMonitorInfoW    ) &&
        StoreProcAddress(hUser32, "EnumDisplayDevicesA", &g_pfnEnumDisplayDevicesA) &&
        StoreProcAddress(hUser32, "EnumDisplayDevicesW", &g_pfnEnumDisplayDevicesW);
}

#ifdef __cplusplus

static struct CMultiMonitorStubs
{
	CMultiMonitorStubs()
    {
        InitMultiMonitorStubs();
    }

} MultiMonitorStubs;

#endif //__cplusplus

#endif //IMPLEMENT_MULTIMON_STUBS

