/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    print.c

Abstract:

    Implementation of the printing functions

--*/

#include "pch.h"
#include "resource.h"

#include "check.h"
#include "conv.h"
#include "inline.h"
#include "BitmapWin.h"

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_GetDefaultPrinter
//
// Routine Description:
//   Reads the default printer data
//
// Arguments:
//  PBITMAPWINDOW   pWin          pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_GetDefaultPrinter(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    PRINTDLG  pd = { 0 };
    PDEVMODE  pDevMode = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    // get defaults

    pd.lStructSize = sizeof(pd);
    pd.Flags       = PD_RETURNDEFAULT;

    if (PrintDlg(&pd)) {

        // if we have valid hDevMode and hDevNames handles, store them

        if (pWin->m_hDevMode != pd.hDevMode) {

            if (pWin->m_hDevMode) {
            
                CHECK(GlobalFree(pWin->m_hDevMode) == 0);
            }

            pWin->m_hDevMode = pd.hDevMode;
        }

        if (pWin->m_hDevNames != pd.hDevNames) {

            if (pWin->m_hDevNames) {
            
                CHECK(GlobalFree(pWin->m_hDevNames) == 0);
            }

            pWin->m_hDevNames = pd.hDevNames;
        }

        CHECK(pDevMode = (PDEVMODE) GlobalLock(pWin->m_hDevMode));

#ifdef ICM_ENABLED

        // if the devmode supports DM_ICMMETHOD, initialize it

        if (pDevMode->dmFields & DM_ICMMETHOD) {

            if (pWin->m_bDisableICM) {
            
                pDevMode->dmICMMethod = DMICMMETHOD_NONE;

            } else {

                if (pDevMode->dmICMMethod == DMICMMETHOD_NONE) {
            
                    pDevMode->dmICMMethod = DMICMMETHOD_SYSTEM;
                }
            }
        }

        // if the devmode supports DM_ICMINTENT, initialize it

        if (pDevMode->dmFields & DM_ICMINTENT) {
        
            pDevMode->dmICMIntent = LCS_TO_DMICM(pWin->m_lcsRenderIntent);
        }

#endif //ICM_ENABLED
    
    } else {

        if (pWin->m_hDevMode) {

            CHECK(GlobalFree(pWin->m_hDevMode) == 0);
            pWin->m_hDevMode = 0;
        }

        if (pWin->m_hDevNames) {

            CHECK(GlobalFree(pWin->m_hDevNames) == 0);
            pWin->m_hDevNames = 0;
        }
    }

    BEGIN_CLEANUP;
    
    if (pDevMode) {

        GlobalUnlock(pWin->m_hDevMode);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnPageSetup
//
// Routine Description:
//   Displays a page setup dialog with a print preview image
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnPageSetup(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    PAGESETUPDLG psd = { 0 };

    ASSERT(BitmapWindow_AssertValid(pWin));

    ASSERT(pWin->m_pDIB);
        
    psd.lStructSize         = sizeof(psd);
    psd.hwndOwner           = pWin->m_hWnd;
    psd.hDevMode            = pWin->m_hDevMode;
    psd.hDevNames           = pWin->m_hDevNames;
    psd.Flags               = 
        PSD_DEFAULTMINMARGINS |
        PSD_ENABLEPAGEPAINTHOOK |
        PSD_INTHOUSANDTHSOFINCHES |
        PSD_MARGINS;
    psd.rtMargin            = pWin->m_rMargin;
    psd.lpfnPagePaintHook   = BitmapWindow_PagePaintHook;

    if (!PageSetupDlg(&psd)) {

        CHECK(CommDlgExtendedError() == 0);

    } else {

        pWin->m_rMargin = psd.rtMargin;

        if (pWin->m_hDevMode != psd.hDevMode) {

            CHECK(GlobalFree(pWin->m_hDevMode) == 0);
            pWin->m_hDevMode = psd.hDevMode;
        }

        if (pWin->m_hDevNames != psd.hDevNames) {

            CHECK(GlobalFree(pWin->m_hDevNames) == 0);
            pWin->m_hDevNames = psd.hDevNames;
        }

#ifdef ICM_ENABLED

        CHECK(BitmapWindow_FillPrinterICMInfo(pWin));

#endif //ICM_ENABLED
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}
    
//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_PagePaintHook
//
// Routine Description:
//   Responds to the page setup dialog messages and if WM_PSD_GREEKTEXTRECT
//   is received, displays a print preview image
//
// Arguments:
//  HWND   hdlg     Handle to the Page Setup dialog box window
//  UINT   uiMsg    Identifies the message being received
//  WPARAM wParam   for WM_PSD_GREEKTEXTRECT, handle of the device context 
//  LPARAM lParam   for WM_PSD_GREEKTEXTRECT, a pointer to text rectangle
//
// Return Value:
//   Zero on error / nonzero on success
//

UINT 
CALLBACK 
BitmapWindow_PagePaintHook(  
    HWND   hdlg,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    USES_BRESULT;
    HWND                hParent;
    HWND                hWindow;
    PBITMAPWINDOW       pWin;

    // We will only handle the WM_PSD_GREEKTEXTRECT message
    // i.e. we will only paint the small preview image

    if (uiMsg == WM_PSD_GREEKTEXTRECT) {

        HDC  hDC     = (HDC) wParam;
        RECT rBitmap = *(PRECT) lParam;

        // extract the BITMAPWINDOW pointer

        CHECK(hParent = GetParent(hdlg));
        CHECK(hWindow = GetParent(hParent));
        CHECK(pWin = (PBITMAPWINDOW) GetWindowLongPtr(hWindow, GWLP_USERDATA));

        ASSERT(BitmapWindow_AssertValid(pWin));

        CenterBitmap(
            pWin->m_nImageW,
            pWin->m_nImageH,
            &rBitmap,
            TRUE,
            TRUE
        );

        CHECK(BitmapWindow_MultimonCall(
            BitmapWindow_PrintPreview,
            pWin,
            hDC,
            (LPARAM) &rBitmap
        ));
    
    } else {

        return FALSE;
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_PrintPreview
//
// Routine Description:
//   Strectches the DIB to the given rectangle
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//   HDC           hDC       destination display DC
//   int           nMonitor  index of the monitor 
//   LPARAM        lParam    destination rectangle
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CALLBACK
BitmapWindow_PrintPreview(
     PBITMAPWINDOW pWin,
     int           nMonitor,
     HDC           hDC,
     LPARAM        lParam
)
{
    USES_BRESULT;
    HPALETTE hPalette = 0;

    ASSERT(BitmapWindow_AssertValid(pWin) && hDC && lParam);
    UNREFERENCED_PARAMETER(nMonitor);  // unused if ICM is not enabled

#ifdef ICM_ENABLED

    // here we make a wild guess and regardless of the current 
    // bDisableICM setting we use the proof mode with the current 
    // display and printer profiles

    if (g_bICMFunctionalityPresent) {
    
        CHECK(CreatePaletteAndDrawDIB_ICM(
            hDC,
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &hPalette,
            (PRECT) lParam,
            pWin->m_Monitor[nMonitor].szProfile,
            LCS_GM_ABS_COLORIMETRIC,
            pWin->m_szPrinterProfile,
            LCS_GM_IMAGES
        ));

    } else 

#endif //ICM_ENABLED

    {
        CHECK(CreatePaletteAndDrawDIB(
            hDC,
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &hPalette,
            (PRECT) lParam
        ));
    }

    if (hPalette) {

        DeleteObject(hPalette);
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnPrint
//
// Routine Description:
//   Displays the print dialog and send the image to the selected printer
//
// Arguments:
//   PBITMAPWINDOW pWin    pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnPrint(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    PRINTDLG pd = { 0 };

    ASSERT(BitmapWindow_AssertValid(pWin));

    ASSERT(pWin->m_pDIB);
        
    pd.lStructSize  = sizeof(pd);
    pd.hwndOwner    = pWin->m_hWnd;
    pd.hDevMode     = pWin->m_hDevMode;
    pd.hDevNames    = pWin->m_hDevNames;
    pd.Flags        = 
        PD_HIDEPRINTTOFILE |
        PD_NOPAGENUMS |
        PD_NOSELECTION |
        PD_RETURNDC |
        PD_USEDEVMODECOPIESANDCOLLATE;

    if (!PrintDlg(&pd)) {

        CHECK(CommDlgExtendedError() == 0);

    } else {

        if (pWin->m_hDevMode != pd.hDevMode) {

            CHECK(GlobalFree(pWin->m_hDevMode) == 0);
            pWin->m_hDevMode = pd.hDevMode;
        }

        if (pWin->m_hDevNames != pd.hDevNames) {

            CHECK(GlobalFree(pWin->m_hDevNames) == 0);
            pWin->m_hDevNames = pd.hDevNames;
        }

#ifdef ICM_ENABLED

        CHECK(BitmapWindow_FillPrinterICMInfo(pWin));

#endif //ICM_ENABLED

        CHECK(BitmapWindow_PrintBitmap(
            pWin,
            pd.hDC
        ));
    }

    BEGIN_CLEANUP;
    
    if (pd.hDC) {

        CHECK(DeleteDC(pd.hDC));
    }

    return BRESULT;
}
    
//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_PrintBitmap
//
// Routine Description:
//   Sends the image to the printer DC
//
// Arguments:
//  PBITMAPWINDOW pWin    pointer to the object
//  HDC           hDC     printer DC
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_PrintBitmap(
    PBITMAPWINDOW pWin,
    HDC           hDC
)
{
    USES_BRESULT;
    TCHAR    szDocName[MAX_PATH];
    DOCINFO  di;
    RECT     rBitmap;
    HPALETTE hPalette = 0;
    PDEVMODE pDevMode = 0;
    BOOL     bUseICM = TRUE;

    ASSERT(BitmapWindow_AssertValid(pWin) && hDC);

    // start the document and the only page using the image name

    CHECK(GetWindowText(
        pWin->m_hWnd, 
        szDocName,
        COUNTOF(szDocName)
    ));

    di.cbSize       = sizeof(di);
    di.lpszDocName  = szDocName;
    di.lpszOutput   = 0;
    di.lpszDatatype = 0;
    di.fwType       = 0;

    CHECK(StartDoc(hDC, &di) > 0);
    CHECK(StartPage(hDC) > 0);

    // Find the location of the image on the paper
    // (taking the margins into consideration)

    rBitmap.left   = 
        pWin->m_rMargin.left   * GetDeviceCaps(hDC, LOGPIXELSX) / 1000;

    rBitmap.top    = 
        pWin->m_rMargin.top    * GetDeviceCaps(hDC, LOGPIXELSY) / 1000;
    
    rBitmap.right  = 
        GetDeviceCaps(hDC, HORZRES) - 
        pWin->m_rMargin.right  * GetDeviceCaps(hDC, LOGPIXELSX) / 1000;
    
    rBitmap.bottom = 
        GetDeviceCaps(hDC, VERTRES) - 
        pWin->m_rMargin.bottom * GetDeviceCaps(hDC, LOGPIXELSY) / 1000;

    CenterBitmap(
        pWin->m_nImageW,
        pWin->m_nImageH,
        &rBitmap,
        TRUE,
        TRUE
    );

    // and send the image to the printer DC

#ifdef ICM_ENABLED

    CHECK(pDevMode = (PDEVMODE) GlobalLock(pWin->m_hDevMode));

    if (pDevMode->dmFields & DM_ICMMETHOD) {
    
        bUseICM = pDevMode->dmICMMethod != DMICMMETHOD_NONE;
    }

    if (g_bICMFunctionalityPresent) {
    
        CHECK(CreatePaletteAndDrawDIB_ICM(
            hDC,
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &hPalette,
            &rBitmap,
            bUseICM ? pWin->m_szPrinterProfile : 0,
            DMICM_TO_LCS(pDevMode->dmICMIntent),
            0,
            0
        ));

    } else 

#endif //ICM_ENABLED

    {
        CHECK(CreatePaletteAndDrawDIB(
            hDC,
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &hPalette,
            &rBitmap
        ));
    }

    BEGIN_CLEANUP;
    
    CHECK(EndPage(hDC) > 0);

    CHECK(EndDoc(hDC) > 0);

    if (pDevMode) {

        GlobalUnlock(pWin->m_hDevMode);
    }

    if (hPalette) {

        DeleteObject(hPalette);
    }

    return BRESULT;
}

