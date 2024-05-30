/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    about.c

Abstract:

    Implementation of the window message handling functions

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"
#include "Convert.h"

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_WindowProc
//
// Routine Description:
//   Processes messages sent to the bitmap window
//
// Arguments:
//   HWND   hwnd      handle to window  
//   UINT   uMsg      message identifier
//   WPARAM wParam    first message parameter
//   LPARAM lParam    second message parameter
//
// Return Value:
//   Depends on message
//

LRESULT 
CALLBACK 
BitmapWindow_WindowProc(  
    HWND   hWnd,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    PBITMAPWINDOW pWin = (PBITMAPWINDOW) GetWindowLongPtr(
        hWnd, 
        GWLP_USERDATA
    );

    // keep the current number of open windows in this static variable

    static LONG nWindows = 0;

    switch(uMsg) {

    case WM_CREATE:

        // when each window is created, increase the counter

        InterlockedIncrement(&nWindows);
        return 0;

    case WM_DESTROY:

        // Upon destruction, delete the associated BitmapWindow struct

        BitmapWindow_Destruct(pWin);
        GlobalFree(pWin);

        // Decrease the open windows counter, if all the windows are closed, 
        // exit the app

        if (InterlockedDecrement(&nWindows) == 0) {
            
            PostQuitMessage(0);
        }

        return 0;

    case WM_CLOSE:
        if (!BitmapWindow_CanClose(pWin)) {
            
            return 0;
        }
        break;

    case WM_ERASEBKGND:

        // OnPaint() paints all client area, there is no background 
        // that needs to be erased, so we skip the WM_ERASEBKGND message
        
        return 1;

    case WM_PAINT:
        BitmapWindow_OnPaint(pWin);
        return 0;

    case WM_QUERYNEWPALETTE:
        BitmapWindow_ApplyPalette(
            pWin, 
            FALSE
        );
        return TRUE;

    case WM_PALETTECHANGED:

        // if this is not the window that changed the palette itself,

        if ( (HWND)wParam != hWnd) {
        
            // apply the background palette to the window 

            BitmapWindow_ApplyPalette(
                pWin, 
                TRUE
            );
        }   
        return TRUE;

    case WM_DISPLAYCHANGE:
        BitmapWindow_OnDisplayChange(pWin);
        return 0;

    case WM_MOVE:
        BitmapWindow_OnMove(pWin);
        break;

    case WM_SIZE:
        BitmapWindow_OnSize(
            pWin, 
            wParam,
            LOWORD(lParam), 
            HIWORD(lParam)
        );
        return 0;

    case WM_HSCROLL:
        BitmapWindow_OnScroll(
            pWin, 
            SB_HORZ,
            LOWORD(wParam)
        );
        return 0;

    case WM_VSCROLL:
        BitmapWindow_OnScroll(
            pWin, 
            SB_VERT,
            LOWORD(wParam)
        );
        return 0;

    case WM_MOUSEWHEEL:
        BitmapWindow_OnMouseWheel(
            hWnd,
            HIWORD(wParam)
        );
        return 0;

    case WM_DROPFILES:
        BitmapWindow_OnDropFiles(
            pWin, 
            (HDROP) wParam
        );
        return 0;

    case WM_LBUTTONDOWN:
        BitmapWindow_OnLButtonDown(
            pWin,
            LOWORD(lParam),
            HIWORD(lParam)
        );
        return 0;

    case WM_LBUTTONUP:
        ReleaseCapture();
        return 0;

    case WM_MOUSEMOVE:
        BitmapWindow_OnMouseMove(
            pWin,
            wParam,
            LOWORD(lParam),
            HIWORD(lParam)
        );
        return 0;

    case WM_INITMENU:
        BitmapWindow_OnInitMenu(
            pWin,
            (HMENU) wParam
        );
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {

            case ID_FILE_NEW:
                CreateBitmapWindow(SW_SHOW, eOpenEmpty, 0);
                return 0;

            case ID_FILE_OPEN:
                BitmapWindow_OnFileOpen(pWin);
                return 0;

            case ID_FILE_SAVE:
                BitmapWindow_OnFileSave(pWin);
                return 0;

            case ID_FILE_SAVE_AS:
                BitmapWindow_OnFileSaveAs(pWin);
                return 0;

            case ID_FILE_CLOSE:
                if (BitmapWindow_CanClose(pWin)) {

                    PostMessage(pWin->m_hWnd, WM_DESTROY, 0, 0);
                }
                return 0;

            case ID_FILE_SELECT_SOURCE:
                BitmapWindow_OnSelectSource(pWin);
                return 0;

            case ID_FILE_ACQUIRE:
                BitmapWindow_OnAcquire(pWin);
                return 0;

            case ID_FILE_PAGE_SETUP:
                BitmapWindow_OnPageSetup(pWin);
                return 0;

            case ID_FILE_PRINT:
                BitmapWindow_OnPrint(pWin);
                return 0;

#ifdef ICM_ENABLED

            case ID_COLOR_SETUP:
                BitmapWindow_OnColorSetup(pWin, 0);
                return 0;

            case ID_CMM_MANAGER:
                BitmapWindow_OnCMMManager(pWin);
                return 0;

#endif //ICM_ENABLED
            
            case ID_FILE_EXIT:
                EnumThreadWindows(
                    GetCurrentThreadId(),
                    BitmapWindow_DestroyWindow, 
                    0
                );
                return 0;
            
            case ID_EDIT_COPY:
                BitmapWindow_CopyToClipboard(pWin);
                return 0;
            
            case ID_EDIT_PASTE:
                BitmapWindow_OpenDocument(
                    pWin, 
                    ePasteFromClipboard, 
                    ResourceString(IDS_CLIPBOARD_DATA)
                );
                return 0;

#ifdef ICM_ENABLED

            case ID_EDIT_COLOR_SPACE:
                BitmapWindow_EditColorSpace(pWin);
                return 0;

#endif //ICM_ENABLED

#ifdef ICM_OUTSIDE_DC

            case ID_EDIT_TRANSFORM_DIB:
                BitmapWindow_TransformDIB(pWin);
                return 0;

            case ID_EDIT_PROFILE_TO_PROFILE:
                BitmapWindow_ProfileToProfile(pWin);
                return 0;

#endif //ICM_OUTSIDE_DC
            
            case ID_VIEW_STRETCH_TO_WINDOW:
                BitmapWindow_OnStretchToWindow(pWin);
                return 0;

            case ID_VIEW_KEEP_ASPECT_RATIO:
                BitmapWindow_OnKeepAspectRatio(pWin);
                return 0;

            case ID_VIEW_AUTO_RESIZE_WINDOW:
                BitmapWindow_OnAutoResizeWindow(pWin);
                return 0;

            case ID_HELP_ABOUT:
                BitmapWindow_OnHelpAbout(pWin);
                break;
        }
        break;
    }

    return DefWindowProc(
        hWnd,
        uMsg, 
        wParam, 
        lParam
    );
}
  
//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_DestroyWindow
//
// Routine Description:
//   Destroys the enumerated window
//
// Arguments:
//   HWND   hWnd      handle to window  
//   LPARAM lParam    not used
//
// Return Value:
//   Returns TRUE to continue enumeration
//

BOOL 
CALLBACK 
BitmapWindow_DestroyWindow(  
    HWND   hWnd,
    LPARAM lParam
)
{
    UNREFERENCED_PARAMETER(lParam);

    SendMessage(hWnd, WM_CLOSE, 0, 0);

    return TRUE; 
}
  
//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_ApplyPalette
//
// Routine Description:
//   Applies the palette to the display DC
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//   BOOL bForceBackground
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_ApplyPalette(
    PBITMAPWINDOW pWin,
    BOOL bForceBackground
)
{
    USES_BRESULT;
    HDC           hDC = 0;
    HPALETTE      hOldPalette = 0;
    int           nMonitor = 0;

#ifdef MULTIMON_ENABLED

    HMONITOR      hMonitor;
    MONITORINFOEX miex;

    // find the monitor that has the largest intersection with the window

    CHECK(hMonitor = MonitorFromWindow(
        pWin->m_hWnd, 
        MONITOR_DEFAULTTOPRIMARY
    ));

    // get the monitor name

    miex.cbSize = sizeof(miex);

    CHECK(GetMonitorInfo(
        hMonitor,
        (LPMONITORINFO) &miex
    ));

    // find the monitor name in our monitors array

    for (
        nMonitor = 0;
        nMonitor < pWin->m_nNumMonitors &&
        _tcscmp(pWin->m_Monitor[nMonitor].szName, miex.szDevice);
        ++nMonitor
    );

    ASSERT(nMonitor < pWin->m_nNumMonitors);

#endif //MULTIMON_ENABLED

    if (pWin->m_Monitor[nMonitor].hPalette) {

        CHECK(hDC = GetDC(pWin->m_hWnd));

        CHECK(hOldPalette = SelectPalette(
            hDC,
            pWin->m_Monitor[nMonitor].hPalette,
            bForceBackground
        ));

        CHECK(RealizePalette(hDC) != GDI_ERROR);
    }

    CHECK(InvalidateRect(
        pWin->m_hWnd,
        0,
        FALSE
    )); 

    BEGIN_CLEANUP;

    if (hOldPalette) {

        CHECK(SelectPalette(
            hDC,
            hOldPalette,
            TRUE
        ));
    }

    if (hDC) {

        CHECK(ReleaseDC(pWin->m_hWnd, hDC));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnPaint
//
// Routine Description:
//   WM_PAINT handler. Draws the current image onto the screen.
//
// Arguments:
//   PBITMAPWINDOW pWin    pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnPaint(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    PAINTSTRUCT ps;
    HDC         hDC = 0;
    HBRUSH      hBrush = 0;
    HBRUSH      hOldBrush = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(hDC = BeginPaint(
        pWin->m_hWnd, 
        &ps
    ));

    if (!IsRectEmpty(&ps.rcPaint)) {

        RECT rWindow;
        RECT rBitmap;

        // center the image in the window

        CHECK(GetClientRect(
            pWin->m_hWnd,
            &rWindow
        ));

        rBitmap = rWindow;

        CenterBitmap(
            pWin->m_nImageW,
            pWin->m_nImageH,
            &rBitmap,
            pWin->m_dwFlags & BWF_STRETCHTOWINDOW,
            pWin->m_dwFlags & BWF_KEEPASPECTRATIO
        );

        // draw the bitmap separately on each monitor

        CHECK(BitmapWindow_MultimonCall(
            BitmapWindow_DisplayBitmap,
            pWin,
            hDC,
            (LPARAM) &rBitmap
        ));

        // draw a frame along the four sides of the image

        CHECK(hBrush = GetSysColorBrush(COLOR_WINDOW));

        CHECK(hOldBrush = (HBRUSH) SelectObject(hDC, hBrush));

        CHECK(PatBlt(
            hDC, 
            0, 0,
            rWindow.right, rBitmap.top,
            PATCOPY 
        ));

        CHECK(PatBlt(
            hDC, 
            0, rBitmap.bottom,
            rWindow.right, rBitmap.top,
            PATCOPY 
        ));

        CHECK(PatBlt(
            hDC, 
            0, rBitmap.top,
            rBitmap.left, Rect_H(&rBitmap),
            PATCOPY 
        ));

        CHECK(PatBlt(
            hDC, 
            rBitmap.right, rBitmap.top, 
            rBitmap.left, Rect_H(&rBitmap),
            PATCOPY 
        ));
    }

    BEGIN_CLEANUP;

    if (hOldBrush) {

        CHECK(SelectObject(
            hDC, 
            hOldBrush
        ));
    }

    if (hBrush) {

        CHECK(DeleteObject(hBrush));
    }

    if (hDC) {
        
        EndPaint(
            pWin->m_hWnd, 
            &ps
        );
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_DisplayBitmap
//
// Routine Description:
//   Multimonitor callback for BitmapWindow_OnPaint.
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//   int           nMonitor  index of the monitor 
//   HDC           hDC       destination display DC
//   LPARAM        lParam    destination rectangle
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CALLBACK
BitmapWindow_DisplayBitmap(
    PBITMAPWINDOW pWin,
    int           nMonitor,
    HDC           hDC,
    LPARAM        lParam
)
{
    USES_BRESULT;
    POINT cOrigin;

    ASSERT(BitmapWindow_AssertValid(pWin) && hDC);

    if (pWin->m_Monitor[nMonitor].hDIBSect) {

        // set the viewport origin according to the scroll bar positions

        CHECK(SetViewportOrgEx(
            hDC,
            -GetScrollPos(pWin->m_hWnd, SB_HORZ),
            -GetScrollPos(pWin->m_hWnd, SB_VERT),
            &cOrigin
        ));

        // draw the DDB

        CHECK(DrawDDB(
            hDC,
            pWin->m_Monitor[nMonitor].hDIBSect,
            pWin->m_Monitor[nMonitor].hPalette,
            pWin->m_nImageW,
            pWin->m_nImageH,
            (PRECT) lParam
        ));

        // restore the DC origin

        CHECK(SetViewportOrgEx(
            hDC,
            cOrigin.x, 
            cOrigin.y,
            0
        ));
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnDisplayChange
//
// Routine Description:
//   Redraws the DDB when the display resolution is changed
//
// Arguments:
//   PBITMAPWINDOW pWin               pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnDisplayChange(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    int nMonitor;

#ifdef MULTIMON_ENABLED

    // WM_DISPLAYCHANGE is also sent if there is change in monitor 
    // positioning, so we should refresh our monitor info

    int nNewNumMonitors = GetSystemMetrics(SM_CMONITORS);
    
    if (pWin->m_nNumMonitors != nNewNumMonitors) {

        // if the number of enabled display monitors have changed,
        // we should adjust the size of our BITMAPWINDOW struct

        CHECK(pWin = BitmapWindow_ResizeStruct(
            pWin, 
            nNewNumMonitors
        ));
    }

#endif //MULTIMON_ENABLED

#ifdef ICM_ENABLED

    // Fill the ICM profiles info

    for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

        CHECK(BitmapWindow_FillMonitorICMInfo(
            pWin,
            nMonitor
        ));
    }

#endif //ICM_ENABLED

    // If a DIB is loaded, convert it to the new display resolution

    if (pWin->m_pDIB) {

        for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

            CHECK(BitmapWindow_CreateDDB(
                pWin, 
                nMonitor 
            ));
        }
    }

    // Redraw the window

    CHECK(InvalidateRect(
        pWin->m_hWnd, 
        0, 
        FALSE
    ));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnMove
//
// Routine Description:
//   Finds the update region when the window is moved accross monitors
//
// Arguments:
//  PBITMAPWINDOW pWin         pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnMove(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

#ifdef MULTIMON_ENABLED

    int  nMonitor;
    
    BOOL bSameMonitorFormats = GetSystemMetrics(SM_SAMEDISPLAYFORMAT);
    BOOL bSameMonitorProfiles = TRUE;

    ASSERT(BitmapWindow_AssertValid(pWin));

#ifdef ICM_ENABLED

    for (nMonitor = 1; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

        bSameMonitorProfiles = bSameMonitorProfiles && _tcscmp(
            pWin->m_Monitor[nMonitor].szProfile,
            pWin->m_Monitor[0].szProfile
        ) == 0;
    }

#endif //ICM_ENABLED

    for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

        RECT rNewMonitorClient;

        // convert the monitor coordinates to our new client
        // coordinate system

        rNewMonitorClient = pWin->m_Monitor[nMonitor].rMonitorScreen;

        CHECK(ScreenToClient(
            pWin->m_hWnd,
            (PPOINT) &rNewMonitorClient.left
        ));

        CHECK(ScreenToClient(
            pWin->m_hWnd,
            (PPOINT) &rNewMonitorClient.right
        ));

        if (bSameMonitorFormats && !bSameMonitorProfiles) {

            // if the display formats are the same for all monitors,
            // windows will not generate a WM_PAINT message for the
            // portion of the window that moves from one monitor to the other.
            // But if the color profiles are different for the monitors,
            // we need to repaint that region. In that case, we need to 
            // find the update rectangle ourselves and force a repaint.

            RECT rClient;
            RECT rOldIntersection;
            RECT rNewIntersection;
            RECT rUpdate;

            // get the client window size

            CHECK(GetClientRect(
                pWin->m_hWnd,
                &rClient
            ));

            // find the old and new portions of our window on this monitor

            IntersectRect(
                &rOldIntersection,
                &pWin->m_Monitor[nMonitor].rMonitorClient,
                &rClient
            );

            IntersectRect(
                &rNewIntersection,
                &rNewMonitorClient,
                &rClient
            );

            // the difference of these two portions is the area that 
            // we should repaint. If you "subtract" one rectangle from 
            // another, the result is four rectagles

            if (rNewIntersection.left < rOldIntersection.left) {

                rUpdate.left   = rNewIntersection.left;
                rUpdate.top    = rNewIntersection.top;
                rUpdate.right  = rOldIntersection.left;
                rUpdate.bottom = rNewIntersection.bottom;

                CHECK(InvalidateRect(
                    pWin->m_hWnd,
                    &rUpdate,
                    FALSE
                ));
            }

            if (rNewIntersection.top < rOldIntersection.top) {

                rUpdate.left   = rNewIntersection.left;
                rUpdate.top    = rNewIntersection.top;
                rUpdate.right  = rNewIntersection.right;
                rUpdate.bottom = rOldIntersection.top;

                CHECK(InvalidateRect(
                    pWin->m_hWnd,
                    &rUpdate,
                    FALSE
                ));
            }

            if (rNewIntersection.right > rOldIntersection.right) {

                rUpdate.left   = rOldIntersection.right;
                rUpdate.top    = rNewIntersection.top;
                rUpdate.right  = rNewIntersection.right;
                rUpdate.bottom = rNewIntersection.bottom;

                CHECK(InvalidateRect(
                    pWin->m_hWnd,
                    &rUpdate,
                    FALSE
                ));
            }

            if (rNewIntersection.bottom > rOldIntersection.bottom) {

                rUpdate.left   = rNewIntersection.left;
                rUpdate.top    = rOldIntersection.bottom;
                rUpdate.right  = rNewIntersection.right;
                rUpdate.bottom = rNewIntersection.bottom;

                CHECK(InvalidateRect(
                    pWin->m_hWnd,
                    &rUpdate,
                    FALSE
                ));
            }
        }

        // store the monitor rectangle converted to new client coordinates

        pWin->m_Monitor[nMonitor].rMonitorClient = rNewMonitorClient;
    }

    BEGIN_CLEANUP;

#endif //MULTIMON_ENABLED

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnSize
//
// Routine Description:
//   In response to a WM_SIZE message, updates the scroll bar sizes
//
// Arguments:
//  PBITMAPWINDOW pWin         pointer to the object
//  DWORD         fwSizeType   resizing flag 
//  DWORD         nWidth       width of the client area  
//  DWORD         nHeight      height of the client area 
//
// Return Value:
//   Zero on error / nonzero on success
//

VOID
BitmapWindow_OnSize(
    PBITMAPWINDOW pWin,
    DWORD         fwSizeType,
    DWORD         nWidth,
    DWORD         nHeight
)
{
    SCROLLINFO si;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_pDIB != 0 && !pWin->m_bUpdatingScrollBars) {

        DWORD dwStyle;
        DWORD nCXVScroll = GetSystemMetrics(SM_CXVSCROLL);
        DWORD nCYHScroll = GetSystemMetrics(SM_CYVSCROLL);
        DWORD dwMaxW;
        DWORD dwMaxH;

        // extend the client area limits to include the scroll bar region

        dwStyle = GetWindowLongPtr(
            pWin->m_hWnd, 
            GWL_STYLE
        );

        if (dwStyle & WS_VSCROLL) {
    
            nWidth  += nCXVScroll;
        }

        if (dwStyle & WS_HSCROLL) {

            nHeight += nCYHScroll;
        }

        if (pWin->m_dwFlags & BWF_STRETCHTOWINDOW) {

            // if we are stretching the image to the window size, 
            // there will be no scroll bars

            dwMaxW = nWidth;
            dwMaxH = nHeight;

        } else {

            // determine whether we need scroll bars and adjust client area

            dwMaxW = pWin->m_nImageW;
            dwMaxH = pWin->m_nImageH;

            if (dwMaxW > nWidth) {

                nHeight -= nCYHScroll;

                if (dwMaxH > nHeight) {

                    nWidth -= nCXVScroll;
                }

            } else if (dwMaxH > nHeight) {

                nWidth -= nCXVScroll;
        
                if (dwMaxW > nWidth) {

                    nHeight -= nCYHScroll;
                } 
            } 
        }

        pWin->m_bUpdatingScrollBars = TRUE;

        // set horizontal scroll bar limits

        si.cbSize = sizeof(si);
        si.fMask  = SIF_RANGE | SIF_PAGE;
        si.nMin   = 0;
        si.nMax   = dwMaxW;
        si.nPage  = nWidth + 1;

        SetScrollInfo(
            pWin->m_hWnd,
            SB_HORZ,
            &si,
            TRUE
        );

        // set vertical scroll bar limits

        si.cbSize = sizeof(si);
        si.fMask  = SIF_RANGE | SIF_PAGE;
        si.nMin   = 0;
        si.nMax   = dwMaxH;
        si.nPage  = nHeight + 1;

        SetScrollInfo(
            pWin->m_hWnd,
            SB_VERT,
            &si,
            TRUE
        );

        pWin->m_bUpdatingScrollBars = FALSE;
    }
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnScroll
//
// Routine Description:
//   In response to WM_HSCROLL or WM_VSCROLL messages, scrolls the contents
//   of the window
//
// Arguments:
//  PBITMAPWINDOW pWin           pointer to the object
//  int           fnBar          scroll bar flag (SB_HORZ or SB_VERT)
//  INT           nScrollCode    scroll bar value 
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnScroll(
    PBITMAPWINDOW pWin,
    int           fnBar,
    INT           nScrollCode
)
{
    USES_BRESULT;
    SCROLLINFO si;
    int        nOldPos;
    int        nDisp;

    ASSERT(BitmapWindow_AssertValid(pWin));

    si.cbSize = sizeof(si);
    si.fMask  = SIF_ALL;
    
    GetScrollInfo(
        pWin->m_hWnd,
        fnBar,
        &si
    );

    nOldPos = si.nPos;

    switch (nScrollCode) {

    case SB_TOP:
        si.nPos = si.nMin;
        break;

    case SB_BOTTOM:
        si.nPos = si.nMax;
        break;

    case SB_LINEUP:
        si.nPos -= 1;
        break;

    case SB_LINEDOWN:
        si.nPos += 1;
        break;

    case SB_PAGEUP:
        si.nPos -= si.nPage;
        break;

    case SB_PAGEDOWN:
        si.nPos += si.nPage;
        break;

    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
        si.nPos = si.nTrackPos;
        break;

    case SB_ENDSCROLL:
    default:
        return 0;
    }

    si.nPos = Clip(
        si.nPos,
        si.nMin, 
        si.nMax - (int) si.nPage + 1
    );

    si.fMask  = SIF_POS;

    SetScrollInfo(  
        pWin->m_hWnd,
        fnBar,
        &si,
        TRUE
    );

    nDisp = nOldPos - si.nPos;

    if (nDisp) {

#ifdef MULTIMON_ENABLED

        int nMonitor;

        for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {
 
            CHECK(ScrollWindowEx(
                pWin->m_hWnd,
                fnBar == SB_HORZ ? nDisp : 0,
                fnBar == SB_VERT ? nDisp : 0,
                0,
                &pWin->m_Monitor[nMonitor].rMonitorClient,
                0,
                0,
                SW_INVALIDATE
            ) != ERROR);
        
            CHECK(UpdateWindow(pWin->m_hWnd));
        }

#else //MULTIMON_ENABLED

        CHECK(ScrollWindowEx(
            pWin->m_hWnd,
            fnBar == SB_HORZ ? nDisp : 0,
            fnBar == SB_VERT ? nDisp : 0,
            0,
            0,
            0,
            0,
            SW_INVALIDATE
        ) != ERROR);

        CHECK(UpdateWindow(pWin->m_hWnd));

#endif //MULTIMON_ENABLED

    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnMouseWheel
//
// Routine Description:
//   In response to WM_MOUSEWHEEL, scrolls the window contents
//
// Arguments:
//  HWND hWnd      Handle to the window whose contents will scroll
//  short zDelta   wheel rotation
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnMouseWheel(
    HWND hWnd,
    short zDelta
)
{
    USES_BRESULT;
    UINT       nWheelScrollLines;
    static int nTotalDelta = 0;
    UINT       i;

    ASSERT(hWnd);
    
    CHECK(SystemParametersInfo(
        SPI_GETWHEELSCROLLLINES,
        0,
        &nWheelScrollLines,
        0
    ));

    nTotalDelta += zDelta;

    while (nTotalDelta >= WHEEL_DELTA) {

        nTotalDelta -= WHEEL_DELTA;

        for (i = 0; i < nWheelScrollLines; ++i) {

            CHECK(PostMessage(
                hWnd,
                WM_VSCROLL,
                MAKEWORD(SB_LINEUP, 0),
                0
            ));
        }
    } 
    
    while (nTotalDelta <= -WHEEL_DELTA) {

        nTotalDelta += WHEEL_DELTA;

        for (i = 0; i < nWheelScrollLines; ++i) {

            CHECK(PostMessage(
                hWnd,
                WM_VSCROLL,
                MAKEWORD(SB_LINEDOWN, 0),
                0
            ));
        }
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnLButtonDown
//
// Routine Description:
//   In response to WM_LBUTTONDOWN, enters panning mode
//
// Arguments:
//  PBITMAPWINDOW pWin  pointer to the object
//  short         xPos  horizontal position of cursor 
//  short         yPos  vertical position of cursor
//
// Return Value:
//   Zero on error / nonzero on success
//

VOID
BitmapWindow_OnLButtonDown(
    PBITMAPWINDOW pWin,
    short         xPos,
    short         yPos
)
{
    ASSERT(BitmapWindow_AssertValid(pWin));

    pWin->m_nMouseXPos = xPos;
    pWin->m_nMouseYPos = yPos;

    SetCapture(pWin->m_hWnd);
    SetCursor(LoadCursor(0, IDC_SIZEALL));
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnMouseMove
//
// Routine Description:
//   In response to WM_MOUSEMOVE, scrolls the window contents
//
// Arguments:
//  PBITMAPWINDOW pWin     pointer to the object
//  DWORD         fwKeys   key flags 
//  short         xPos     horizontal position of cursor 
//  short         yPos     vertical position of cursor
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnMouseMove(
    PBITMAPWINDOW pWin,
    DWORD         fwKeys,
    short         xPos,
    short         yPos
)
{
    USES_BRESULT;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (fwKeys & MK_LBUTTON) {

        int nDispX = MoveScrollBar(
            pWin->m_hWnd,
            SB_HORZ,
            pWin->m_nMouseXPos - xPos
        );

        int nDispY = MoveScrollBar(
            pWin->m_hWnd,
            SB_VERT,
            pWin->m_nMouseYPos - yPos
        );

        if (nDispX || nDispY) {

#ifdef MULTIMON_ENABLED

            int nMonitor;

            for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {
 
                CHECK(ScrollWindowEx(
                    pWin->m_hWnd,
                    nDispX,
                    nDispY,
                    0,
                    &pWin->m_Monitor[nMonitor].rMonitorClient,
                    0,
                    0,
                    SW_INVALIDATE
                ) != ERROR);

                CHECK(UpdateWindow(pWin->m_hWnd));
            }

#else //MULTIMON_ENABLED

            CHECK(ScrollWindowEx(
                pWin->m_hWnd,
                nDispX,
                nDispY,
                0,
                0,
                0,
                0,
                SW_INVALIDATE
            ) != ERROR);

            CHECK(UpdateWindow(pWin->m_hWnd));

#endif //MULTIMON_ENABLED

        }

        pWin->m_nMouseXPos = xPos;
        pWin->m_nMouseYPos = yPos;
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// MoveScrollBar
//
// Routine Description:
//   Updates the scroll bars of a window according to a given displacement
//
// Arguments:
//  HWND hWnd           Handle to the window
//  int  fnBar          scroll bar flag (SB_HORZ or SB_VERT)
//  int  nDisplacement  amount to move the scroll bar
//
// Return Value:
//   The effective displacement
//

int
MoveScrollBar(
    HWND hWnd,
    int  fnBar,
    int  nDisplacement
)
{
    INT nNewDisplacement;
    SCROLLINFO si;

    si.cbSize = sizeof(si);
    si.fMask  = SIF_ALL;
    
    GetScrollInfo(
        hWnd,
        fnBar,
        &si
    );

    nNewDisplacement = si.nPos;

    si.nPos = Clip(
        si.nPos + nDisplacement,
        si.nMin, 
        si.nMax - (int) si.nPage + 1
    );

    nNewDisplacement -= si.nPos;

    if (nNewDisplacement) {

        si.fMask = SIF_POS;

        SetScrollInfo(
            hWnd,
            fnBar,
            &si,
            TRUE
        );
    }

    return nNewDisplacement;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_AdjustWindowSize
//
// Routine Description:
//   Sets the size of the window. Behavior changes according to the 
//   eAutoResizeWindow flag, if it is set, the window is resized
//   in accordance with the image size. If it is not set, then
//   only the scroll bars are updated
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_AdjustWindowSize(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    RECT rWindow;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_dwFlags & BWF_AUTORESIZEWINDOW) {

        // Find the size of the window, taking the non-client area
        // (window border, title bar, menu bar, etc.) into consideration

        // known bug: If the bitmap width is so small that the menu wraps to
        // the second line, AdjustWindowRectEx doesn't take this into account

        rWindow.left   = 0;
        rWindow.top    = 0;
        rWindow.right  = pWin->m_nImageW;
        rWindow.bottom = pWin->m_nImageH;

        CHECK(AdjustWindowRectEx(
            &rWindow,
            GetWindowLongPtr(pWin->m_hWnd, GWL_STYLE),
            TRUE,
            GetWindowLongPtr(pWin->m_hWnd, GWL_EXSTYLE)
        ));

        // Resize the window

        CHECK(SetWindowPos(
            pWin->m_hWnd, 
            0,
            0, 
            0,
            Rect_W(&rWindow), 
            Rect_H(&rWindow),
            SWP_NOMOVE | 
            SWP_NOZORDER
        ));

    } else {

        // Reset the size of the window (so that the scroll bars get updated)

        CHECK(GetClientRect(
            pWin->m_hWnd,
            &rWindow
        ));

        CHECK(PostMessage( 
            pWin->m_hWnd, 
            WM_SIZE, 
            SIZENORMAL, 
            MAKELONG(Rect_W(&rWindow), Rect_H(&rWindow))
        ));
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

