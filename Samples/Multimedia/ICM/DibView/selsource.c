/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    selsource.c

Abstract:
    
    Implements a dialog for selecting a TWAIN data source and 
    corresponding ICM profile

--*/


#include "pch.h"
#include "resource.h"

#ifdef ICM_ENABLED

#include "conv.h"
#include "check.h"
#include "inline.h"

#include "SelSource.h"

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_Construct
//
// Routine Description:
//   Initializes a SelectSourceDialog structure. 
//   Establishes connection with the STI interface and gets the STI 
//   devices list, which will be referred to several times during the 
//   lifetime of the dialog
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg     Pointer to the object
//   pTW_IDENTITY        pAppId   Pointer to the AppId for TWAIN operations
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_Construct(
    PSELECTSOURCEDIALOG pDlg,
    pTW_IDENTITY        pAppId
)
{
    USES_BRESULT;

    pDlg->m_AppId = *pAppId;
    pDlg->m_SelectedSrcId.Id = 0;
    pDlg->m_SelectedSrcId.ProductName[0] = '\0';
    
    pDlg->m_szSelectedProfileName[0] = '\0';

    pDlg->m_pSti            = 0;
    pDlg->m_pdi             = 0;
    pDlg->m_dwNumDevices    = 0;

    CHECK(StiCreateInstance(
        GetModuleHandle(0),
        STI_VERSION,
        &pDlg->m_pSti,
        0
    ) == S_OK);

    CHECK(IStillImage_GetDeviceList(
        pDlg->m_pSti, 
        0,
        0,
        &pDlg->m_dwNumDevices,
        (PVOID *) &pDlg->m_pdi
    ) == S_OK);

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_Destruct
//
// Routine Description:
//   Cleans up the sources list and terminates connection to the STI 
//   interface
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg     Pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_Destruct(
    PSELECTSOURCEDIALOG pDlg
)
{
    USES_BRESULT;

    HWND hList;

    BEGIN_CLEANUP;

    if (hList = GetDlgItem(pDlg->m_hWndDlg, IDC_SOURCELIST)) {

        CHECK(SelectSourceDialog_FreeSourcesList(hList));
    }

    if (pDlg->m_pdi) {
    
        CHECK(LocalFree(pDlg->m_pdi) == 0);
    }

    if (pDlg->m_pSti) {
    
        CHECK(IStillImage_Release(pDlg->m_pSti) == S_OK);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_FreeSourcesList
//
// Routine Description:
//   Frees the sources list. A pointer to SrcId struct is stored with
//   the lParam of each list item, so they must be free'd
//
// Arguments:
//   HWND hList     Handle to the list control
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_FreeSourcesList(
    HWND hList
)
{
    USES_BRESULT;

    int iItem;

    BEGIN_CLEANUP;

    for (
        iItem = ListView_GetNextItem(hList, -1, LVNI_ALL);
        iItem != -1;
        iItem = ListView_GetNextItem(hList, iItem, LVNI_ALL)
    ) {

        LVITEM lvi;

        lvi.mask       = LVIF_PARAM;
        lvi.iItem      = iItem;
        lvi.iSubItem   = 0;

        CHECK(ListView_GetItem(hList, &lvi) != -1);

        if (lvi.lParam) {
        
            CHECK(GlobalFree((HGLOBAL) lvi.lParam) == 0);
        }
    }

    CHECK(ListView_DeleteAllItems(hList));

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_DoModal
//
// Routine Description:
//   Displays the SelectSourceDialog as a modal dialog box
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg        Pointer to the object
//   HWND                hWndParent  Handle to the parent window
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_DoModal(
    PSELECTSOURCEDIALOG pDlg,
    HWND                hWndParent
)
{
    return DialogBoxParam(
        GetModuleHandle(0),
        MAKEINTRESOURCE(IDD_SELECT_SOURCE_DIALOG),
        hWndParent,
        SelectSourceDialog_DialogProc,
        (LPARAM) pDlg
    );
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_DialogProc
//
// Routine Description:
//   Processes messages sent to the dialog
//
// Arguments:
//   HWND   hWndDlg   handle to dialog window
//   UINT   uMsg      message identifier
//   WPARAM wParam    first message parameter
//   LPARAM lParam    second message parameter
//
// Return Value:
//   If uMsg == WM_INITDIALOG, the return value should be zero if 
//   we call the SetFocus function to set the focus to one of the 
//   controls in the dialog box. Otherwise, it should be nonzero, 
//   in which case the system sets the focus to the first control 
//   in the dialog box that can be given the focus. 
//   If uMsg != WM_INITDIALOG, the return value should be nonzero 
//   if we process the message, and zero if we do not
//

BOOL 
CALLBACK 
SelectSourceDialog_DialogProc(  
    HWND   hWndDlg,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (uMsg) {

    case WM_INITDIALOG:

        return SelectSourceDialog_InitDialog(
            (PSELECTSOURCEDIALOG) lParam, 
            hWndDlg
        );

    case WM_NOTIFY: {
        
        LPNMHDR pnm = (LPNMHDR) lParam;

        if (pnm->code == LVN_ITEMCHANGED) {

            PSELECTSOURCEDIALOG pDlg = (PSELECTSOURCEDIALOG) GetWindowLongPtr(
                hWndDlg, 
                DWLP_USER
            );

            switch (pnm->idFrom) {

            case IDC_SOURCELIST:
                return SelectSourceDialog_OnSourceChange(
                    pDlg, 
                    (LPNMLISTVIEW) lParam
                );

            case IDC_PROFILELIST:
                return SelectSourceDialog_OnProfileChange(
                    pDlg, 
                    (LPNMLISTVIEW) lParam
                );
            }
        }

        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case IDOK:
            return EndDialog(hWndDlg, IDOK);

        case IDCANCEL:
            return EndDialog(hWndDlg, IDCANCEL);
        }
        break;
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_InitDialog
//
// Routine Description:
//   Initializes the columns of the list controls, fills the sources list
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg     Pointer to the object
//   HWND                hWndDlg  Handle to the dialog
//
// Return Value:
//   Always TRUE since we do not SetFocus to one of the controls
//

BOOL
SelectSourceDialog_InitDialog(
    PSELECTSOURCEDIALOG pDlg,
    HWND                hWndDlg
)
{
    USES_BRESULT;

    HWND     hSourceList;
    HWND     hProfileList;
    LVCOLUMN lvc;
    RECT     r;

    // Store the pointers
        
    pDlg->m_hWndDlg = hWndDlg;

    SetWindowLongPtr(
        pDlg->m_hWndDlg, 
        DWLP_USER, 
        (LONG_PTR) pDlg
    );

    // Initialize the one and only column in SourceList
        
    CHECK(hSourceList = GetDlgItem(pDlg->m_hWndDlg, IDC_SOURCELIST));

    CHECK(GetClientRect(hSourceList, &r));

    lvc.mask     = LVCF_SUBITEM | LVCF_WIDTH;
    lvc.iSubItem = 0;
    lvc.cx       = r.right;

    CHECK(ListView_InsertColumn(
        hSourceList, 
        0, 
        &lvc
    ) != -1);

    // Initialize the one and only column in ProfileList
        
    CHECK(hProfileList = GetDlgItem(pDlg->m_hWndDlg, IDC_PROFILELIST));

    CHECK(GetClientRect(hProfileList, &r));

    lvc.mask     = LVCF_SUBITEM | LVCF_WIDTH;
    lvc.iSubItem = 0;
    lvc.cx       = r.right;

    CHECK(ListView_InsertColumn(
        hProfileList, 
        0, 
        &lvc
    ) != -1);

    // fill in the TWAIN source names

    CHECK(SelectSourceDialog_FillSourceNames(pDlg));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_FillSourceNames
//
// Routine Description:
//   Creates a list of installed TWAIN sources
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg     Pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_FillSourceNames(
    PSELECTSOURCEDIALOG pDlg
)
{
    USES_BRESULT;
    USES_CONVERSION;

    HWND          hSourceList;
    HWND          hSelectButton;
    int           nSources = 0;
    pTW_IDENTITY  pSrcId = 0;
    TW_UINT16     rc;

    ASSERT(pDlg);

    CHECK(hSourceList = GetDlgItem(pDlg->m_hWndDlg, IDC_SOURCELIST));

    CHECK(SelectSourceDialog_FreeSourcesList(hSourceList));

    CHECK(pSrcId = (pTW_IDENTITY) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        sizeof(TW_IDENTITY))
    );

    rc = DSM_Entry(
        &pDlg->m_AppId, 
        0, 
        DG_CONTROL, 
        DAT_IDENTITY, 
        MSG_GETFIRST,
        (TW_MEMREF) pSrcId
    );
    
    while (rc == TWRC_SUCCESS) {

        LVITEM lvi;

        lvi.mask      = LVIF_TEXT | LVIF_STATE | LVIF_PARAM;
        lvi.iItem     = nSources;
        lvi.iSubItem  = 0;
        lvi.state     = nSources == 0 ? LVIS_SELECTED : 0;
        lvi.stateMask = LVIS_SELECTED;
        lvi.pszText   = A2T(pSrcId->ProductName);
        lvi.lParam    = (LPARAM) pSrcId;

        CHECK(ListView_InsertItem(hSourceList, &lvi) != -1);

        ++nSources;

        // we store a pointer to the current SrcId in the lparam field
        // and allocate a new SrcId struct for the next entry

        CHECK(pSrcId = (pTW_IDENTITY) GlobalAlloc(
            GMEM_FIXED | GMEM_ZEROINIT, 
            sizeof(TW_IDENTITY))
        );

        rc = DSM_Entry(
            &pDlg->m_AppId, 
            0, 
            DG_CONTROL, 
            DAT_IDENTITY, 
            MSG_GETNEXT,
            (TW_MEMREF) pSrcId
        );
    }

    BEGIN_CLEANUP;

    if (nSources == 0) {

        // if there are no sources, disable the select button

        CHECK(hSelectButton = GetDlgItem(pDlg->m_hWndDlg, IDOK));
        
        EnableWindow(hSelectButton, FALSE);
    }

    if (pSrcId) {

        CHECK(GlobalFree(pSrcId) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_OnSourceChange
//
// Routine Description:
//   Called when a new source is selected
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg     Pointer to the object
//   LPNMLISTVIEW        pnmlv    Pointer to the notification message struct
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_OnSourceChange(
    PSELECTSOURCEDIALOG pDlg,
    LPNMLISTVIEW        pnmlv
)
{
    USES_BRESULT;

    if (pnmlv->uNewState & LVIS_SELECTED) {

        LVITEM lvi;

        lvi.mask       = LVIF_PARAM;
        lvi.iItem      = pnmlv->iItem;
        lvi.iSubItem   = 0;

        CHECK(ListView_GetItem(pnmlv->hdr.hwndFrom, &lvi) != -1);

        pDlg->m_SelectedSrcId = *(pTW_IDENTITY) lvi.lParam;

        CHECK(SelectSourceDialog_FillProfileNames(pDlg));
    }
 
    BEGIN_CLEANUP;

    return BRESULT;
}


//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_FillProfileNames
//
// Routine Description:
//   Finds the STI device id corresponding to the selected TWAIN source
//   and creates a list of the ICM profiles associated with the device
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg     Pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_FillProfileNames(
    PSELECTSOURCEDIALOG pDlg
)
{
    USES_BRESULT;
    USES_CONVERSION;

    HCURSOR   hPrevCur = 0;
    HWND      hProfileList;
    PWSTR     pSelected = 0;
    DWORD     nDevice;
    PWSTR     pBuffer = (PWSTR) GlobalAlloc(GMEM_FIXED, 1024);
    PWSTR     pProfileName;
    int       nProfiles = 0;

    ASSERT(pDlg);

    hPrevCur = SetCursor(LoadCursor(0, IDC_WAIT));

    CHECK(hProfileList = GetDlgItem(pDlg->m_hWndDlg, IDC_PROFILELIST));

    CHECK(ListView_DeleteAllItems(hProfileList));

    // find the corresponding STI device for the selected source

    for (
        nDevice = 0; 
        nDevice < pDlg->m_dwNumDevices && pSelected == 0;
        ++nDevice
    ) {

        CHECK(GetDeviceValue_ReAlloc(
            pDlg->m_pSti, 
            pDlg->m_pdi[nDevice].szDeviceInternalName,
            STI_DEVICE_VALUE_TWAIN_NAME,
            (PBYTE *) &pBuffer
        ));

        if (strcmp(W2A(pBuffer), pDlg->m_SelectedSrcId.ProductName) == 0) {

            pSelected = pDlg->m_pdi[nDevice].szDeviceInternalName;
        }
    }

    // list ICM profiles if the STI device is found

    if (pSelected) {

        CHECK(GetDeviceValue_ReAlloc(
            pDlg->m_pSti, 
            pSelected,
            STI_DEVICE_VALUE_ICM_PROFILE,
            (PBYTE *) &pBuffer
        ));

        // trace the MULTI_SZ string list

        for (
            pProfileName = pBuffer; 
            *pProfileName; 
            pProfileName += wcslen(pProfileName) + 1
        ) {

            LVITEM  lvi;

            lvi.mask      = LVIF_TEXT | LVIF_STATE;
            lvi.iItem     = nProfiles;
            lvi.iSubItem  = 0;
            lvi.state     = nProfiles == 0 ? LVIS_SELECTED : 0;
            lvi.stateMask = LVIS_SELECTED;
            lvi.pszText   = W2T(pProfileName);

            CHECK(ListView_InsertItem(
                hProfileList, 
                &lvi
            ) != -1);

            ++nProfiles;
        }
    }

    BEGIN_CLEANUP;

    if (pBuffer) {

        CHECK(GlobalFree(pBuffer) == 0);
    }

    if (hPrevCur) {
        
        SetCursor(hPrevCur);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SelectSourceDialog_OnProfileChange
//
// Routine Description:
//   Called when a new profile is selected
//
// Arguments:
//   PSELECTSOURCEDIALOG pDlg     Pointer to the object
//   LPNMLISTVIEW        pnmlv    Pointer to the notification message struct
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SelectSourceDialog_OnProfileChange(
    PSELECTSOURCEDIALOG pDlg,
    LPNMLISTVIEW        pnmlv
)
{
    USES_BRESULT;
 
    if (pnmlv->uNewState & LVIS_SELECTED) {

        LVITEM lvi;
        TCHAR  szText[MAX_PATH];

        lvi.mask       = LVIF_TEXT;
        lvi.iItem      = pnmlv->iItem;
        lvi.iSubItem   = 0;
        lvi.pszText    = szText;
        lvi.cchTextMax = COUNTOF(szText);

        CHECK(ListView_GetItem(
            pnmlv->hdr.hwndFrom, 
            &lvi
        ) != -1);

        _tcscpy(
            pDlg->m_szSelectedProfileName, 
            lvi.pszText
        );
    }
 
    BEGIN_CLEANUP;

    return BRESULT;
}


//////////////////////////////////////////////////////////////////////////
//
// GetDeviceValue_ReAlloc
//
// Routine Description:
//   Wrapper for IStillImage_GetDeviceValue that re-allocates output memory 
//   as needed
//
// Arguments:
//  IStillImage *pSti         COM interface pointer
//  PWSTR       pDeviceName   Name of the STI device
//  PWSTR       pValueName    Name of the device value
//  PBYTE       *ppBuffer     A double pointer to the device data
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
GetDeviceValue_ReAlloc(
    IStillImage *pSti,
    PWSTR       pDeviceName,
    PWSTR       pValueName,
    PBYTE       *ppBuffer
)
{
    USES_BRESULT;

    BOOL   bEnumResult;
    INT    nRetries;
    DWORD  dwType;
    DWORD  dwSize;

    ASSERT(pSti);
    ASSERT(pDeviceName);
    ASSERT(pValueName);
    ASSERT(ppBuffer);

    dwSize = GlobalSize(*ppBuffer);

    bEnumResult = IStillImage_GetDeviceValue(
        pSti, 
        pDeviceName,
        pValueName, 
        &dwType, 
        *ppBuffer, 
        &dwSize
    );

    if (bEnumResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {

        // if no profiles have been associated with this device 
        // before, we will get this error. In this case, return silently...
        
        *ppBuffer[0] = 0;

    } else {

        // While the enumeration fails because of insufficient buffer
        // size, resize the buffer and retry. It is advisable to put a limit 
        // to the max number of retries (for example, 10)

        for (nRetries = 0; bEnumResult != S_OK && nRetries < 10; ++nRetries) {

            if (bEnumResult == ERROR_MORE_DATA) {

                // Deallocate the previous buffer, allocate a new buffer 
                // according to dwSize returned from the last call and retry

                if (*ppBuffer) {

                    CHECK(GlobalFree(*ppBuffer) == 0);
                }

                CHECK(*ppBuffer = (PBYTE) GlobalAlloc(
                    GMEM_FIXED,
                    dwSize
                ));

                bEnumResult = IStillImage_GetDeviceValue(
                    pSti, 
                    pDeviceName,
                    pValueName, 
                    &dwType, 
                    *ppBuffer, 
                    &dwSize
                );

            } else {

                SYSTEM_ERROR_MESSAGE(bEnumResult);
            }
        }

        if (bEnumResult != S_OK) {

            SYSTEM_ERROR_MESSAGE(bEnumResult);
        }
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// EnumColorProfiles_ReAlloc
//
// Routine Description:
//   Wrapper for EnumColorProfiles that re-allocates output memory 
//   as needed
//
// Arguments:
//  PBYTE       *ppBuffer     A double pointer to the device data
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EnumColorProfiles_ReAlloc(
    PENUMTYPE pet,
    PBYTE     *ppBuffer
)
{
    USES_BRESULT;

    BOOL    bEnumResult;
    INT     nRetries;
    DWORD   dwSize;
    DWORD   dwNum;

    ASSERT(pet);
    ASSERT(ppBuffer);

    dwSize = GlobalSize(*ppBuffer);

    bEnumResult = EnumColorProfiles(
        0,
        pet,
        *ppBuffer,
        &dwSize,
        &dwNum
    );

    // If the enumeration fails because of insufficient buffer
    // size, resize the buffer and retry (at most NUM_RETRIES times)

    for (nRetries = 0; !bEnumResult && nRetries < 10; ++nRetries) {

        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            // If we have previously allocated a new buffer, 
            // deallocate it first

            if (*ppBuffer) {

                CHECK(GlobalFree(*ppBuffer) == 0);
            }

            // Allocate the new buffer (according to dwSize 
            // returned from the last enum call)

            CHECK(*ppBuffer = (PBYTE) GlobalAlloc(
                GMEM_FIXED,
                dwSize
            ));

            // Retry

            bEnumResult = EnumColorProfiles(
                0,
                pet,
                *ppBuffer,
                &dwSize,
                &dwNum
            );

        } else {

            SYSTEM_ERROR_MESSAGE(GetLastError());
        }
    }

    if (!bEnumResult) {

        SYSTEM_ERROR_MESSAGE(GetLastError());
    }

    BEGIN_CLEANUP;

    return BRESULT;
}



#endif //ICM_ENABLED

