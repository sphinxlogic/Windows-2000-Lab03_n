/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    twain.c

Abstract:

    Implementation of the TWAIN functions

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"

#ifdef ICM_ENABLED
#include "SelSource.h"
#endif //ICM_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_FillTwainInfo
//
// Routine Description:
//   Fill the Twain application ID and get the default source ID
//
// Arguments:
//  PBITMAPWINDOW pWin    pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
BitmapWindow_FillTwainInfo(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    USES_CONVERSION;

    TCHAR            szFileName[MAX_PATH];
    DWORD            dwHandle;
    DWORD            dwVerInfoSize;
    PVOID            pVerInfo = 0;
    VS_FIXEDFILEINFO *pFixedInfo = 0;
    PDWORD           pLangCodePageId = 0;
    TCHAR            szStringFileInfo[80];
    PTSTR            pStringFileInfoName = 0;
    PTSTR            pFileDescription = 0;
    PTSTR            pCompanyName = 0;
    PTSTR            pProductVersion = 0;
    PTSTR            pProductName = 0;
    UINT             uSize;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(GetModuleFileName(
        0,
        szFileName,
        COUNTOF(szFileName)
    ));

    CHECK(dwVerInfoSize = GetFileVersionInfoSize(
        szFileName, 
        &dwHandle
    ));

    CHECK(pVerInfo = (PVOID) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        dwVerInfoSize
    ));

    CHECK(GetFileVersionInfo(
        szFileName, 
        dwHandle, 
        dwVerInfoSize, 
        pVerInfo
    ));

    CHECK(VerQueryValue(
        pVerInfo,
        _T("\\"),
        (PVOID *) &pFixedInfo,
        &uSize
    )); 

    CHECK(VerQueryValue(
        pVerInfo,
        _T("\\VarFileInfo\\Translation"),
        (PVOID *) &pLangCodePageId,
        &uSize
    )); 

    CHECK(wsprintf(
        szStringFileInfo,
        _T("\\StringFileInfo\\%04X%04X\\"),
        LOWORD(pLangCodePageId[0]),
        HIWORD(pLangCodePageId[0])
    ));

    pStringFileInfoName = szStringFileInfo + _tcslen(szStringFileInfo);

    _tcscpy(pStringFileInfoName, _T("FileDescription"));

    CHECK(VerQueryValue(
        pVerInfo,
        szStringFileInfo,
        (PVOID *) &pFileDescription,
        &uSize
    )); 

    _tcscpy(pStringFileInfoName, _T("CompanyName"));

    CHECK(VerQueryValue(
        pVerInfo,
        szStringFileInfo,
        (PVOID *) &pCompanyName,
        &uSize
    )); 

    _tcscpy(pStringFileInfoName, _T("ProductVersion"));

    CHECK(VerQueryValue(
        pVerInfo,
        szStringFileInfo,
        (PVOID *) &pProductVersion,
        &uSize
    )); 

    _tcscpy(pStringFileInfoName, _T("ProductName"));

    CHECK(VerQueryValue(
        pVerInfo,
        szStringFileInfo,
        (PVOID *) &pProductName,
        &uSize
    )); 

    // todo: fill the correct lang / country info according to current locale

    pWin->m_AppId.Id = 0; 
    pWin->m_AppId.Version.MajorNum = HIWORD(pFixedInfo->dwFileVersionMS);
    pWin->m_AppId.Version.MinorNum = LOWORD(pFixedInfo->dwFileVersionMS);
    pWin->m_AppId.Version.Language = TWLG_USA; 
    pWin->m_AppId.Version.Country  = TWCY_USA;
    
    strncpy(
        pWin->m_AppId.Version.Info,  
        T2A(pFileDescription), 
        COUNTOF(pWin->m_AppId.Version.Info)
    );

    pWin->m_AppId.ProtocolMajor   = TWON_PROTOCOLMAJOR;
    pWin->m_AppId.ProtocolMinor   = TWON_PROTOCOLMINOR;
    pWin->m_AppId.SupportedGroups = DG_IMAGE | DG_CONTROL;
    
    strncpy(
        pWin->m_AppId.Manufacturer,  
        T2A(pCompanyName),      
        COUNTOF(pWin->m_AppId.Manufacturer)
    );
    
    strncpy(
        pWin->m_AppId.ProductFamily, 
        T2A(pProductVersion),   
        COUNTOF(pWin->m_AppId.ProductFamily)
    );
    
    strncpy(
        pWin->m_AppId.ProductName,   
        T2A(pProductName),      
        COUNTOF(pWin->m_AppId.ProductName)
    );

    if (pWin->m_TwainState == State_2_Source_Manager_Loaded) {

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            0, 
            DG_CONTROL, 
            DAT_PARENT, 
            MSG_OPENDSM, 
            (TW_MEMREF) &pWin->m_hWnd
        ) == TWRC_SUCCESS);

        pWin->m_TwainState = State_3_Source_Manager_Open;
    }

    if (pWin->m_TwainState >= State_3_Source_Manager_Open) {

        // this can return TWRC_FAILURE if there is no TWAIN source installed

        DSM_Entry(
            &pWin->m_AppId, 
            0, 
            DG_CONTROL, 
            DAT_IDENTITY, 
            MSG_GETDEFAULT,
            (TW_MEMREF) &pWin->m_SrcId
        );
    }

    BEGIN_CLEANUP;

    if (pVerInfo) {

        CHECK(GlobalFree(pVerInfo) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnSelectSource
//
// Routine Description:
//   Brings up the "select source" dialog box
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnSelectSource(
    PBITMAPWINDOW pWin
)
{
    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_TwainState >= State_3_Source_Manager_Open) {

#ifdef ICM_ENABLED

        if (g_bSTIFunctionalityPresent) {

            return BitmapWindow_OnSelectSource_STI(pWin);

        } else 

#endif //ICM_ENABLED

        {

            return BitmapWindow_OnSelectSource_Twain(pWin);
        }
    }

    return FALSE;
}

#ifdef ICM_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnSelectSource_STI
//
// Routine Description:
//   Brings up "select source" dialog box with ICM profiles support
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnSelectSource_STI(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    SELECTSOURCEDIALOG Dlg;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_TwainState >= State_3_Source_Manager_Open) {

        CHECK(SelectSourceDialog_Construct(
            &Dlg, 
            &pWin->m_AppId
        ));

        if (SelectSourceDialog_DoModal(&Dlg, pWin->m_hWnd) == IDOK) {

            CopyMemory(
                &pWin->m_SrcId,
                &Dlg.m_SelectedSrcId,
                sizeof(pWin->m_SrcId)
            );

            _tcscpy(
                pWin->m_szScannerProfile, 
                Dlg.m_szSelectedProfileName
            );
        }
    }

    BEGIN_CLEANUP;

    CHECK(SelectSourceDialog_Destruct(&Dlg));

    return BRESULT;
}

#endif //ICM_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnSelectSource_Twain
//
// Routine Description:
//   Brings up the twain data source manager's "select source" dialog box
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnSelectSource_Twain(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    TW_UINT16 rc;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_TwainState >= State_3_Source_Manager_Open) {

        rc = DSM_Entry(
            &pWin->m_AppId, 
            0, 
            DG_CONTROL, 
            DAT_IDENTITY, 
            MSG_USERSELECT, 
            (TW_MEMREF) &pWin->m_SrcId
        );

        if (rc != TWRC_SUCCESS) {
        
            CHECK(rc == TWRC_CANCEL);
        }
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnAcquire
//
// Routine Description:
//   Brings up the twain data source's user interface
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnAcquire(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    TW_UINT16       rc;
    MSG             msg;
    BOOL            bDone = FALSE;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_SrcId.ProductName[0] == '\0') {

        ERROR_MESSAGE(ResourceString(IDS_NO_TWAIN_SOURCE));
    }

    if (pWin->m_TwainState == State_3_Source_Manager_Open) {

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            0, 
            DG_CONTROL, 
            DAT_IDENTITY, 
            MSG_OPENDS, 
            (TW_MEMREF) &pWin->m_SrcId
        ) == TWRC_SUCCESS);

        pWin->m_TwainState = State_4_Source_Open;
    }

    // Set to single image transfer mode

    rc = SetCapOneValue(
        &pWin->m_AppId, 
        &pWin->m_SrcId,
        CAP_XFERCOUNT,
        TWTY_INT16,
        1
    );

    if (pWin->m_TwainState == State_4_Source_Open) {

        TW_USERINTERFACE twUI;

        twUI.ShowUI  = TRUE;
        twUI.hParent = pWin->m_hWnd;

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            &pWin->m_SrcId, 
            DG_CONTROL, 
            DAT_USERINTERFACE, 
            MSG_ENABLEDS, 
            (TW_MEMREF) &twUI
        ) == TWRC_SUCCESS);

        pWin->m_TwainState = State_5_Source_Enabled;
    }

    // Disable the parent window before entering the message loop

    EnableWindow(pWin->m_hWnd, FALSE);

    while (!bDone && GetMessage(&msg, 0, 0, 0)) {

        TW_EVENT twEvent;
        
        twEvent.pEvent    = &msg;
        twEvent.TWMessage = MSG_NULL;

        rc = DSM_Entry(
            &pWin->m_AppId, 
            &pWin->m_SrcId, 
            DG_CONTROL, 
            DAT_EVENT, 
            MSG_PROCESSEVENT, 
            (TW_MEMREF) &twEvent
        );

        switch (twEvent.TWMessage) {
    
        case MSG_XFERREADY:
            
            pWin->m_TwainState = State_6_Transfer_Ready;
            
            CHECK(BitmapWindow_OpenDocument(
                pWin, 
                eAcquireFromTwain, 
                ResourceString(IDS_ACQUIRED_IMAGE)
            ));
            
            // we choose to close DS after first successful transfer
            // break;

        case MSG_CLOSEDSREQ:
            bDone = TRUE;
            break;
        }

        if (rc == TWRC_NOTDSEVENT) {
            
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    BEGIN_CLEANUP;

    // enable the parent window upon exiting the mesage loop

    EnableWindow(pWin->m_hWnd, TRUE);
    
    ASSERT(pWin->m_TwainState <= State_6_Transfer_Ready);

    if (pWin->m_TwainState == State_6_Transfer_Ready) {

        TW_PENDINGXFERS twPendingXfers;

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            &pWin->m_SrcId, 
            DG_CONTROL, 
            DAT_PENDINGXFERS, 
            MSG_RESET, 
            (TW_MEMREF) &twPendingXfers
        ) == TWRC_SUCCESS);

        pWin->m_TwainState = State_5_Source_Enabled;
    }

    if (pWin->m_TwainState == State_5_Source_Enabled) {

        TW_USERINTERFACE twUI;

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            &pWin->m_SrcId, 
            DG_CONTROL, 
            DAT_USERINTERFACE, 
            MSG_DISABLEDS, 
            (TW_MEMREF) &twUI
        ) == TWRC_SUCCESS);

        pWin->m_TwainState = State_4_Source_Open;
    }

    if (pWin->m_TwainState == State_4_Source_Open) {

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            0, 
            DG_CONTROL, 
            DAT_IDENTITY, 
            MSG_CLOSEDS, 
            (TW_MEMREF) &pWin->m_SrcId
        ) == TWRC_SUCCESS);

        pWin->m_TwainState = State_3_Source_Manager_Open;
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_AcquireDIB
//
// Routine Description:
//   Transfers an imge through twain
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_AcquireDIB(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    HANDLE hBitmap = 0;
    PBYTE  pBitmap = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (pWin->m_TwainState == State_6_Transfer_Ready) {

        pWin->m_TwainState = State_7_Transferring;

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            &pWin->m_SrcId, 
            DG_IMAGE, 
            DAT_IMAGENATIVEXFER, 
            MSG_GET, 
            (TW_MEMREF) &hBitmap
        ) == TWRC_XFERDONE);

        if (pWin->m_pDIB) {

            CHECK(GlobalFree(pWin->m_pDIB) == 0);
        }

#ifdef ICM_ENABLED

        CHECK(pBitmap = (PBYTE) GlobalLock(hBitmap));
            
        // if ICM functions are present
        // and ICM is enabled
        // and there is no ICM info in the returned DIB
        // and there is an ICM profile selected for the TWAIN source
        // then attach that profile as a linked profile to the DIB

        if (
            g_bICMFunctionalityPresent &&
            !pWin->m_bDisableICM &&
            !IsV5Header(pBitmap) && 
            pWin->m_szScannerProfile[0] != '\0'
        ) {

            LOGCOLORSPACE lcs = { 0 };

            lcs.lcsSignature = LCS_SIGNATURE;
            lcs.lcsVersion   = 0x400;
            lcs.lcsSize      = sizeof(lcs);
            lcs.lcsCSType    = PROFILE_LINKED;
            lcs.lcsIntent    = LCS_GM_IMAGES;
            _tcscpy(lcs.lcsFilename, pWin->m_szScannerProfile);

            CHECK(ModifyDIBColorSpace(
                pBitmap,
                0,
                &lcs,
                &pWin->m_pDIB,
                &pWin->m_dwOffBits
            ));

            pWin->m_dwOffBits = 0; // will be determined later

        } else

#endif //ICM_ENABLED
        {
            pWin->m_pDIB = (PBYTE) GlobalDuplicate(hBitmap);
        }
    }

    BEGIN_CLEANUP;

    if (pBitmap) {
     
        GlobalUnlock(hBitmap);
    }

    if (hBitmap) {
     
        CHECK(GlobalFree(hBitmap) == 0);
    }

    if (pWin->m_TwainState == State_7_Transferring) {

        TW_PENDINGXFERS twPendingXfers;

        CHECK(DSM_Entry(
            &pWin->m_AppId, 
            &pWin->m_SrcId, 
            DG_CONTROL, 
            DAT_PENDINGXFERS, 
            MSG_ENDXFER, 
            (TW_MEMREF) &twPendingXfers
        ) == TWRC_SUCCESS);

        // todo: modify this to handle multi-image transfers

        pWin->m_TwainState = State_6_Transfer_Ready;

        while (twPendingXfers.Count != 0) {

            CHECK(DSM_Entry(
                &pWin->m_AppId, 
                &pWin->m_SrcId, 
                DG_CONTROL, 
                DAT_PENDINGXFERS, 
                MSG_ENDXFER, 
                (TW_MEMREF) &twPendingXfers
            ) == TWRC_SUCCESS);
        }

        pWin->m_TwainState = State_5_Source_Enabled;
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SetCapOneValue
//
// Routine Description:
//   Sets one capability value
//
// Arguments:
//   pTW_IDENTITY pOrigin    application ID
//   pTW_IDENTITY pDest      destination source ID
//   TW_UINT16    Cap        capability
//   TW_UINT16    ItemType   item type
//   TW_UINT32    Item       item value
//
// Return Value:
//   Twain error code
//

TW_UINT16
SetCapOneValue(
    pTW_IDENTITY pOrigin,
    pTW_IDENTITY pDest,
    TW_UINT16    Cap,
    TW_UINT16    ItemType,
    TW_UINT32    Item
)
{
    USES_BRESULT;

    TW_CAPABILITY twCapability;
    pTW_ONEVALUE  pVal = 0;
    TW_UINT16     rc = TWRC_FAILURE;

    twCapability.Cap        = Cap;
    twCapability.ConType    = TWON_ONEVALUE;
    twCapability.hContainer = 0;

    CHECK(twCapability.hContainer = GlobalAlloc(
        GHND, 
        sizeof(TW_ONEVALUE)
    ));

    CHECK(pVal = (pTW_ONEVALUE) GlobalLock(twCapability.hContainer));

    pVal->ItemType = ItemType;
    pVal->Item     = Item;

    GlobalUnlock(twCapability.hContainer);

    rc = DSM_Entry(
        pOrigin, 
        pDest,
        DG_CONTROL,
        DAT_CAPABILITY,
        MSG_SET,
        (TW_MEMREF) &twCapability
    );

    BEGIN_CLEANUP;

    if (twCapability.hContainer) {
    
        CHECK(GlobalFree(twCapability.hContainer) == 0);
    }

    return BRESULT ? rc : TWRC_FAILURE;
}

//////////////////////////////////////////////////////////////////////////
//
// GetCapOneValue
//
// Routine Description:
//   Gets one capability value
//
// Arguments:
//   pTW_IDENTITY pOrigin    application ID
//   pTW_IDENTITY pDest      destination source ID
//   TW_UINT16    Cap        capability
//   pTW_UINT16   pItemType  pointer to a variable that will hold item type
//   pTW_UINT32   pItem      pointer to a variable that will hold item value
//
// Return Value:
//   Twain error code
//

TW_UINT16
GetCapOneValue(
    pTW_IDENTITY pOrigin,
    pTW_IDENTITY pDest,
    TW_UINT16    Cap,
    pTW_UINT16   pItemType,
    pTW_UINT32   pItem
)
{
    USES_BRESULT;

    TW_CAPABILITY twCapability;
    pTW_ONEVALUE  pVal = 0;
    TW_UINT16     rc = TWRC_FAILURE;

    twCapability.Cap        = Cap;
    twCapability.ConType    = TWON_DONTCARE16;
    twCapability.hContainer = 0;

    rc = DSM_Entry(
        pOrigin, 
        pDest,
        DG_CONTROL,
        DAT_CAPABILITY,
        MSG_GET,
        (TW_MEMREF) &twCapability
    );

    CHECK(pVal = (pTW_ONEVALUE) GlobalLock(twCapability.hContainer));

    if (pItemType) {
    
        *pItemType = pVal->ItemType;
    }
    
    if (pItem) {
    
        *pItem = pVal->Item;
    }

    BEGIN_CLEANUP;

    if (twCapability.hContainer) {
    
        CHECK(GlobalFree(twCapability.hContainer) == 0);
    }

    return BRESULT ? rc : TWRC_FAILURE;
}

