/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
    CMMman.c

Abstract:
    
    Implements a dialog for enumerating / adding / removing / 
    selecting the default CMM

--*/

#include "pch.h"
#include "resource.h"

#ifdef ICM_ENABLED

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "CMMman.h"

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_DialogProc
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
CMMDialog_DialogProc(  
    HWND   hWndDlg,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    HWND hList = GetDlgItem(hWndDlg, IDC_CMMLIST);

    switch (uMsg) {

    case WM_INITDIALOG:
        return CMMDialog_InitDialog(hList);

    case WM_NOTIFY:

        if (((LPNMHDR)lParam)->code == LVN_ITEMCHANGED) {

            // if we receive a notification from the list control,
            // we check whether one of the CMMs is selected and 
            // accordingly enable / disable the remove & select buttons.
            
            BOOL bEnable = ListView_GetSelectedCount(hList) > 0;
            EnableWindow(GetDlgItem(hWndDlg, IDC_REMOVE), bEnable);
            EnableWindow(GetDlgItem(hWndDlg, IDC_SELECT), bEnable);
        }

        break;

    case WM_COMMAND:
        
        switch (LOWORD(wParam)) {

        case IDCLOSE:
            return EndDialog(hWndDlg, IDCLOSE);

        case IDC_ADD:
            return CMMDialog_AddCMM(hList);

        case IDC_REMOVE:
            return CMMDialog_RemoveCMM(hList);

        case IDC_SELECT:
            return CMMDialog_SelectCMM(hList);
        }
        
        break;
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_InitDialog
//
// Routine Description:
//   Initializes the list control in the dialog
//
// Arguments:
//   HWND hList    Handle to the list control
//
// Return Value:
//   Always TRUE since we do not SetFocus to one of the controls
//

BOOL
CMMDialog_InitDialog(
    HWND hList
)
{
    USES_BRESULT;

    HIMAGELIST hIml = 0;
    RECT       rClient;
    LVCOLUMN   lvc;

    ASSERT(hList);

    // Load the "check mark" bitmap

    CHECK(hIml = ImageList_LoadBitmap(
        g_hInstance,
        MAKEINTRESOURCE(IDB_IMAGELIST),
        8,
        1,
        RGB(255, 255, 255)
    ));

    // and associate it with the list control

    ListView_SetImageList(
        hList,
        hIml,
        LVSIL_SMALL
    );

    // insert the column headers to the list control

    CHECK(GetClientRect(
        hList,
        &rClient
    ));

    lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
    
    lvc.pszText  = _T("ID");
    lvc.iSubItem = 0;
    lvc.cx       = rClient.right * 1/4;

    CHECK(ListView_InsertColumn(
        hList, 
        0, 
        &lvc
    ) != -1);

    lvc.pszText  = _T("Path");
    lvc.iSubItem = 1;
    lvc.cx       = rClient.right * 3/4;

    CHECK(ListView_InsertColumn(
        hList, 
        1, 
        &lvc
    ) != -1);

    // fill the list control

    CHECK(CMMDialog_EnumCMM(hList));

    BEGIN_CLEANUP;

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
// dwID
//
// Routine Description:
//   Converts the CMM ID string to its DWORD equivalent
//
// Arguments:
//   PCTSTR szID    CMM ID string
//
// Return Value:
//   DWORD equivalent of the CMM ID
//

__inline
DWORD
dwID(
    PCTSTR szID
)
{
    return 
        (DWORD)szID[0] << 24 |
        (DWORD)szID[1] << 16 |
        (DWORD)szID[2] << 8  |
        (DWORD)szID[3];
}

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_EnumCMM
//
// Routine Description:
//   Reads the names of the CMMs from the registry and inserts these 
//   into a list control
//
// Arguments:
//   HWND hList    Handle to the list control
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CMMDialog_EnumCMM(
    HWND hList
)
{
    USES_BRESULT;

    HKEY   hKey = 0;
    PCTSTR pCMMKeyName;
    DWORD  dwValues;
    DWORD  i;
    DWORD  dwMaxValueNameLen;
    DWORD  dwMaxValueLen;
    PTSTR  pCMMID = 0;
    DWORD  dwType;
    PTSTR  pCMMPath = 0;
    LVITEM lvi;

    ASSERT(hList);

    CHECK(ListView_DeleteAllItems(hList));

    // Try to open the registry key that holds the list of 
    // CMMs in the system. If the key is not present, then there are
    // no registered CMMs in the system.

    if (GetVersion() < 0x80000000) {

        pCMMKeyName = g_szCMMRegKeyNameNT;

    } else {

        pCMMKeyName = g_szCMMRegKeyName9x;
    }

    if (RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        pCMMKeyName,
        0,
        KEY_READ,
        &hKey
    ) != ERROR_SUCCESS) {

        EXIT_FUNCTION;
    }

    // Read the maximum value name length and maximum data length

    CHECK0(RegQueryInfoKey(
        hKey,
        0,
        0,
        0,
        0,
        0,
        0,
        &dwValues,
        &dwMaxValueNameLen,
        &dwMaxValueLen,
        0,
        0
    ));

    // Allocate memory for the value name. The buffer should be 
    // dwMaxValueNameLen + 1 (terminating null) characters long

    ++dwMaxValueNameLen;

    CHECK(pCMMID = (PTSTR) GlobalAlloc(
        GMEM_FIXED,
        dwMaxValueNameLen * sizeof(TCHAR)
    ));

    // Allocate memory for the data

    CHECK(pCMMPath = (PTSTR) GlobalAlloc(
        GMEM_FIXED,
        dwMaxValueLen
    ));

    // Enumerate the key values

    for (i = 0; i < dwValues; ++i) {

        DWORD dwValueNameLen = dwMaxValueNameLen;
        DWORD dwValueLen     = dwMaxValueLen;

        CHECK0(RegEnumValue(
            hKey,
            i,
            pCMMID,
            &dwValueNameLen,
            0,
            &dwType,
            (PBYTE) pCMMPath,
            &dwValueLen
        ));

        // Insert the CMM name and path into the list control

        lvi.mask     = LVIF_TEXT | LVIF_IMAGE;
        lvi.iItem    = i;
        lvi.iSubItem = 0;
        lvi.pszText  = pCMMID;
        lvi.iImage   = dwID(pCMMID) == g_DefaultCMMID ? 1 : 0;

        CHECK(ListView_InsertItem(
            hList, 
            &lvi
        ) != -1);
        
        ListView_SetItemText(
            hList, 
            i, 
            1, 
            pCMMPath
        );
    }

    BEGIN_CLEANUP;

    if (hKey) {

        CHECK0(RegCloseKey(hKey));
    }

    if (pCMMID) {
        
        CHECK(GlobalFree(pCMMID) == 0);
    }

    if (pCMMPath) {
        
        CHECK(GlobalFree(pCMMPath) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_AddCMM
//
// Routine Description:
//   Adds a CMM to the system
//
// Arguments:
//   HWND hList    Handle to the list control
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CMMDialog_AddCMM(
    HWND hList
)
{
    USES_BRESULT;

    PCTSTR    pCMMPath;
    HINSTANCE hCMM = 0;
    DWORD     (WINAPI *pfnCMGetInfo)(DWORD);
    DWORD     dwCMMID = 0;

    ASSERT(hList);

    // Get the CMM file name from the user

    CHECK(pCMMPath = CMMDialog_GetCMMFileName());

    // Try to load the CMM

    CHECK(hCMM = LoadLibrary(pCMMPath));

    // Get the address of the CMGetInfo function within the library

    CHECK(pfnCMGetInfo = (DWORD (WINAPI *)(DWORD)) GetProcAddress(
        hCMM,
        "CMGetInfo"
    ));

    // Ask the CMM ID. Guard this section in a try / except block
    // so that we can survive if the CMM fails

    __try {

        dwCMMID = (*pfnCMGetInfo)(CMM_IDENT);

    } __except(EXCEPTION_EXECUTE_HANDLER) {

        ERROR_MESSAGE(_T("Invalid CMM"));
    }

    // Register the CMM 

    CHECK(RegisterCMM(
        0,
        dwCMMID,
        pCMMPath
    ));

    // Re-list the CMMs

    CHECK(CMMDialog_EnumCMM(hList));

    BEGIN_CLEANUP;

    if (hCMM) {

        CHECK(FreeLibrary(hCMM));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_RemoveCMM
//
// Routine Description:
//   Removes the selected CMM from the system
//
// Arguments:
//   HWND hList    Handle to the list control
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CMMDialog_RemoveCMM(
    HWND hList
)
{
    USES_BRESULT;

    DWORD dwCMMID;

    ASSERT(hList);

    // Get the selected CMM ID

    CHECK(dwCMMID = CMMDialog_GetSelectedCMMID(
        hList
    ));

    // Unregister the CMM

    CHECK(UnregisterCMM(
        0,
        dwCMMID
    ));

    // If the default CMM was deleted, we have no default now

    if (dwCMMID == g_DefaultCMMID) {
        
        g_DefaultCMMID = 0;
    }

    // Re-list the CMMs

    CHECK(CMMDialog_EnumCMM(hList));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_SelectCMM
//
// Routine Description:
//   Selects a CMM as the default. This selection is for the current 
//   process only, it is NOT defaulted system wide.
//
// Arguments:
//   HWND hList    Handle to the list control
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CMMDialog_SelectCMM(
    HWND hList
)
{
    USES_BRESULT;
    
    DWORD dwCMMID;

    ASSERT(hList);

    // Get the selected CMM ID

    CHECK(dwCMMID = CMMDialog_GetSelectedCMMID(
        hList
    ));

    // Select the CMM

    CHECK(SelectCMM(dwCMMID));

    g_DefaultCMMID = dwCMMID;

    // Re-list the CMMs

    CHECK(CMMDialog_EnumCMM(hList));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_GetSelectedCMMID
//
// Routine Description:
//   Returns the ID of the selected CMM
//
// Arguments:
//   HWND hList    Handle to the list control
//
// Return Value:
//   Selected CMM ID / Zero if none selected
//

DWORD
CMMDialog_GetSelectedCMMID(
    HWND hList
)
{
    int   iItem;
    TCHAR szCMMID[5];

    ASSERT(hList);

    iItem = ListView_GetNextItem(
        hList,
        -1,
        LVNI_SELECTED
    );

    if (iItem == -1) {

        return 0;
    }

    ListView_GetItemText(
        hList,
        iItem,
        0,
        szCMMID,
        COUNTOF(szCMMID)
    );

    return dwID(szCMMID);
}

//////////////////////////////////////////////////////////////////////////
//
// CMMDialog_GetCMMFileName
//
// Routine Description:
//   Opens the file name selection dialog
//
// Arguments:
//   none
//
// Return Value:
//   Name of the filename if one is selected / 0 otherwise
//

PCTSTR
CMMDialog_GetCMMFileName()
{
    USES_BRESULT;

    OPENFILENAME ofn = { 0 };
    static TCHAR szFileName[1024];

    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = 0;
    ofn.lpstrFilter     = _T("DLL (*.DLL)\0*.DLL\0");
    ofn.lpstrFile       = szFileName;
	ofn.lpstrFile[0]	= _T('\0');
    ofn.nMaxFile        = COUNTOF(szFileName);
    ofn.Flags           = 
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

    return BRESULT ? szFileName : 0;
}

#endif //ICM_ENABLED
