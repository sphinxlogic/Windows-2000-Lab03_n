/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    document.c

Abstract:

    Implementation of the image file handling operations

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"
#include "FFilter.h"

// Global variable to enumerate the image file read filters
extern FILEFILTERSLIST g_FileFiltersList;

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnFileOpen
//
// Routine Description:
//   Puts up a GetOpenFileName common dialog, gets the file name(s)
//   and tries to open the files
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnFileOpen(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    OPENFILENAME ofn = { 0 };
    TCHAR        szBuffer[0xFFFF];
    BOOL         bOpenInNewWindow;

    ASSERT(BitmapWindow_AssertValid(pWin));

    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = pWin->m_hWnd;
    ofn.lpstrFilter     = g_FileFiltersList.m_pFiltersStr;
    ofn.lpstrFile       = szBuffer;
	ofn.lpstrFile[0]	= _T('\0');
    ofn.nMaxFile        = COUNTOF(szBuffer);
    ofn.Flags           = 
        OFN_ALLOWMULTISELECT |
        OFN_EXPLORER | 
        OFN_FILEMUSTEXIST | 
        OFN_HIDEREADONLY;
    
    BRESULT = GetOpenFileName(&ofn);

    if (!BRESULT && CommDlgExtendedError() == CDERR_STRUCTSIZE) {

        // If the system does not recognize the OPENFILENAME size,
        // we retry with the old ver 4 OPENFILENAME struct size

        ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;
        BRESULT         = GetOpenFileName(&ofn);
    }

    if (!BRESULT) {

        // If the user cancels or closes the dialog, we will get error 0

        CHECK(CommDlgExtendedError() == 0);

    } else {

        // If a single file is selected, ofn.lpstrFile contains the file name
        // If multiple files are selected, the format of ofn.lpstrFile is
        // pathname\0filename_1\0filename_2\0...\0filename_n\0\0
        // The following loop handles both cases

        TCHAR szPathName[MAX_PATH];
        PCTSTR pFileName;

        // Copy the pathname to buffer, append a backslash and 
        // use this path for each of the files in the list

        _tcscpy(szPathName, ofn.lpstrFile);

        szPathName[ofn.nFileOffset - 1] = '\\';

        // Open the first document in the current window
        // and the rest in separate windows

        bOpenInNewWindow = FALSE;

        for (
            pFileName = ofn.lpstrFile + ofn.nFileOffset;
            *pFileName;
            pFileName += _tcslen(pFileName) + 1
        ) {

            _tcscpy(
                szPathName + ofn.nFileOffset, 
                pFileName
            );

            if (bOpenInNewWindow) {
                
                CreateBitmapWindow(
                    SW_SHOW, 
                    eReadFromFile,
                    szPathName
                );

            } else {

                bOpenInNewWindow |= BitmapWindow_OpenDocument(
                    pWin, 
                    eReadFromFile,
                    szPathName
                );
            }
        }
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnDropFiles
//
// Routine Description:
//   Try to open the files dropped from the explorer
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//   HDROP         hDrop     handle from the explorer 
//
// Return Value:
//   none
//

VOID
BitmapWindow_OnDropFiles(
    PBITMAPWINDOW pWin,
    HDROP         hDrop
)
{
    TCHAR szFileName[MAX_PATH];
    UINT nFiles;
    UINT i;
    BOOL bOpenInNewWindow;

    ASSERT(BitmapWindow_AssertValid(pWin) && hDrop);

    // Get the number of dropped files

    nFiles = DragQueryFile(
        hDrop,
        0xFFFFFFFF,
        0,
        0
    );

    // Open each file. Open the first one in the current window, 
    // and the rest in separate windows

    bOpenInNewWindow = FALSE;

    for (i = 0; i < nFiles; ++i) {

        DragQueryFile(
            hDrop,
            i,
            szFileName,
            COUNTOF(szFileName)
        );

        if (bOpenInNewWindow) {

            CreateBitmapWindow(
                SW_SHOW, 
                eReadFromFile,
                szFileName
            );

        } else {

            bOpenInNewWindow |= BitmapWindow_OpenDocument(
                pWin, 
                eReadFromFile,
                szFileName
            );
        }
    }
    
    DragFinish(hDrop);
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OpenDocument
//
// Routine Description:
//   Tries to open the document based on file extension 
//
// Arguments:
//   PBITMAPWINDOW pWin                    pointer to the object  
//   BitmapWindow_eOpenMethod eOpenMethod  how / where to open
//   PCTSTR pFileName                      name of the file to open
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OpenDocument(
    PBITMAPWINDOW            pWin,
    BitmapWindow_eOpenMethod eOpenMethod,
    PCTSTR                   pFileName
)
{
    USES_BRESULT;
    HCURSOR       hPrevCur = 0;
    PBITMAPWINDOW pNewWin = 0;
    int           nMonitor;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (eOpenMethod != eAttachToDIB && !BitmapWindow_CanClose(pWin)) {
        
        return FALSE;
    }

    // this may be a lengthy operation, display the hourglass

    hPrevCur = SetCursor(LoadCursor(0, IDC_WAIT));

    // Create a zero initialized new struct for the new document 
    // and copy the current settings

    CHECK(pNewWin = (PBITMAPWINDOW) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        sizeof(BITMAPWINDOW) + 
        sizeof(MONITORDATA) * (pWin->m_nNumMonitors - 1)
    ));

#ifdef DEBUG

    pNewWin->m_dwValid    = pWin->m_dwValid;

#endif //DEBUG

    pNewWin->m_hWnd       = pWin->m_hWnd;
    
    CHECK(SetWindowLongPtr(
        pNewWin->m_hWnd, 
        GWLP_USERDATA, 
        (LONG_PTR) pNewWin
    ));

    pNewWin->m_AppId      = pWin->m_AppId;
    pNewWin->m_SrcId      = pWin->m_SrcId;

    pNewWin->m_TwainState = pWin->m_TwainState;

    pNewWin->m_hDevMode   = (HANDLE) GlobalDuplicate(pWin->m_hDevMode);
    pNewWin->m_hDevNames  = (HANDLE) GlobalDuplicate(pWin->m_hDevNames);
    pNewWin->m_rMargin    = pWin->m_rMargin;

    pNewWin->m_dwFlags    = pWin->m_dwFlags;

#ifdef ICM_ENABLED
 
    pNewWin->m_bDisableICM     = pWin->m_bDisableICM;
    pNewWin->m_bEnableProofing = pWin->m_bEnableProofing;
    pNewWin->m_lcsRenderIntent = pWin->m_lcsRenderIntent;
    pNewWin->m_lcsProofIntent  = pWin->m_lcsProofIntent;
    _tcscpy(pNewWin->m_szPrinterName, pWin->m_szPrinterName);
    _tcscpy(pNewWin->m_szPrinterProfile, pWin->m_szPrinterProfile);
    _tcscpy(pNewWin->m_szTargetProfile, pWin->m_szTargetProfile);
    _tcscpy(pNewWin->m_szScannerProfile, pWin->m_szScannerProfile);

#endif //ICM_ENABLED

    pNewWin->m_nNumMonitors = pWin->m_nNumMonitors;

    for (nMonitor = 0; nMonitor < pNewWin->m_nNumMonitors; ++nMonitor) {

        _tcscpy(
            pNewWin->m_Monitor[nMonitor].szName, 
            pWin->m_Monitor[nMonitor].szName
        );

#ifdef ICM_ENABLED

        _tcscpy(
            pNewWin->m_Monitor[nMonitor].szProfile, 
            pWin->m_Monitor[nMonitor].szProfile
        );

#endif //ICM_ENABLED

#ifdef MULTIMON_ENABLED

        pNewWin->m_Monitor[nMonitor].rMonitorScreen = 
            pWin->m_Monitor[nMonitor].rMonitorScreen;

        pNewWin->m_Monitor[nMonitor].rMonitorClient = 
            pWin->m_Monitor[nMonitor].rMonitorClient;

#endif //MULTIMON_ENABLED

    }

    // Open the document

    switch (eOpenMethod) {

    case eReadFromFile: {

        CHECK(FileFiltersList_ReadImageFile(
            &g_FileFiltersList,
            pFileName,
            &pNewWin->m_pDIB,
            &pNewWin->m_dwOffBits
        ));

        _tcscpy(pNewWin->m_szFileName, pFileName);
        pNewWin->m_bIsDirty      = FALSE;

        break;
    }

    case ePasteFromClipboard:
        
        CHECK(BitmapWindow_PasteFromClipboard(pNewWin));
        
        pNewWin->m_szFileName[0] = '\0';
        pNewWin->m_bIsDirty      = TRUE;
        
        break;
    
    case eAcquireFromTwain:
        
        CHECK(BitmapWindow_AcquireDIB(pNewWin));
        
        pNewWin->m_szFileName[0] = '\0';
        pNewWin->m_bIsDirty      = TRUE;
        
        break;

    case eAttachToDIB:
        
        pNewWin->m_pDIB      = (PBYTE) GlobalDuplicate(pWin->m_pDIB);
        pNewWin->m_dwOffBits = pWin->m_dwOffBits;
        
        _tcscpy(pNewWin->m_szFileName, pFileName);
        pNewWin->m_bIsDirty      = TRUE;
        
        break;
    }

    // If we get to this point, we must have loaded the DIB
    // Process its header...

    CHECK(BitmapWindow_ProcessHeader(pNewWin));

    // Create a device dependent bitmap for each display monitor

    for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

        CHECK(BitmapWindow_CreateDDB(
            pNewWin, 
            nMonitor
        ));
    }

    // Apply the new palette to the display monitor

    CHECK(BitmapWindow_ApplyPalette(
        pNewWin,
        FALSE
    ));

    // Adjust the window size, scroll bars, etc

    CHECK(BitmapWindow_AdjustWindowSize(pNewWin));

    // Create the icon as a small version of the bitmap
    
    CHECK(BitmapWindow_CreateIcon(pNewWin));

    // Set the window's title as the image file name

    CHECK(SetWindowText(
        pNewWin->m_hWnd, 
        pFileName
    ));

    BEGIN_CLEANUP;

    // Redraw the window

    CHECK(InvalidateRect(
        pWin->m_hWnd, 
        0, 
        FALSE
    ));

    if (BRESULT) {
    
        // If we have successfully opened the new document, 
        // destroy the old document and copy over the new content

        BitmapWindow_DeleteContents(pWin);
        
        CopyMemory(
            pWin,
            pNewWin,
            sizeof(BITMAPWINDOW) + 
            sizeof(MONITORDATA) * (pWin->m_nNumMonitors - 1)
        );

    } else {

        // If something has gone wrong, delete the "half created"
        // current document

        BitmapWindow_DeleteContents(pNewWin);
    }

    if (pNewWin) {
    
        CHECK(SetWindowLongPtr(
            pNewWin->m_hWnd, 
            GWLP_USERDATA, 
            (LONG_PTR) pWin
        ));

        CHECK(GlobalFree(pNewWin) == 0);
    }

    if (hPrevCur) {
        
        SetCursor(hPrevCur);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnFileSave
//
// Routine Description:
//   Saves the image file to disk
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnFileSave(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_szFileName[0] == '\0') {

        CHECK(BitmapWindow_OnFileSaveAs(pWin));

    } else {

        CHECK(SaveBMP(
            pWin->m_szFileName, 
            pWin->m_pDIB, 
            pWin->m_dwOffBits
        ));

        pWin->m_bIsDirty = FALSE;
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnFileSaveAs
//
// Routine Description:
//   Puts up a GetOpenFileName common dialog, gets the file name(s)
//   and tries to open the files
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnFileSaveAs(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    OPENFILENAME  ofn = { 0 };
    TCHAR         szBuffer[MAX_PATH];

    ASSERT(BitmapWindow_AssertValid(pWin));

    // open the file save dialog

    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = pWin->m_hWnd;
	ofn.hInstance		= g_hInstance;
    ofn.lpstrFilter     = _T("BMP (*.bmp)\0*.bmp\0");
    ofn.lpstrFile       = szBuffer;
    _tcscpy(ofn.lpstrFile, pWin->m_szFileName);
    ofn.nMaxFile        = COUNTOF(szBuffer);
    ofn.Flags           = 
        OFN_EXPLORER        | 
        OFN_OVERWRITEPROMPT |
        OFN_HIDEREADONLY;
    ofn.lpstrDefExt     = _T(".bmp");

    
    BRESULT = GetSaveFileName(&ofn);

    if (!BRESULT && CommDlgExtendedError() == CDERR_STRUCTSIZE) {

        // If the system does not recognize the OPENFILENAME size,
        // we retry with the old ver 4 OPENFILENAME struct size

        ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;
        BRESULT         = GetSaveFileName(&ofn);
    }

    if (!BRESULT) {

        // If the user cancels or closes the dialog, we will get error 0

        CHECK(CommDlgExtendedError() == 0);

    } else {

        _tcscpy(pWin->m_szFileName, ofn.lpstrFile);

        CHECK(BitmapWindow_OnFileSave(pWin));

        CHECK(SetWindowText(
            pWin->m_hWnd, 
            pWin->m_szFileName
        ));
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_CanClose
//
// Routine Description:
//   Displays a warning message to give the user a last chance to save a
//   modified DIB file
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_CanClose(
    PBITMAPWINDOW pWin
)
{
    TCHAR szQuestion[4096];

    if (!pWin->m_bIsDirty) {

        return TRUE;
    }

    wsprintf(
        szQuestion, 
        ResourceString(IDS_SAVE_BEFORE_EXIT), 
        pWin->m_szFileName
    );

    switch (MessageBox(
        pWin->m_hWnd, 
        szQuestion,
        ResourceString(IDS_APP_NAME),
        MB_ICONWARNING | 
        MB_YESNOCANCEL |
        MB_DEFBUTTON1
    )) {

    case IDYES:
        return BitmapWindow_OnFileSave(pWin);

    case IDNO:
        return TRUE;

    case IDCANCEL:
        return FALSE;

    default:
        ASSERT(0);
        return TRUE;
    }
}
