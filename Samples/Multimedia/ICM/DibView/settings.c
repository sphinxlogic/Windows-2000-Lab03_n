/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    settings.c

Abstract:

    Implementation of the user defined settings operations

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
// BitmapWindow_ReadRegistrySettings
//
// Routine Description:
//   Reads the settings from the registry
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_ReadRegistrySettings(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    HKEY  hKey = 0;
    PTSTR pClass = _T("");
    DWORD dwDisposition;
    DWORD dwType;
    DWORD dwDataSize;
    TCHAR szCurrentDirectory[MAX_PATH];

    ASSERT(BitmapWindow_AssertValid(pWin));

    // Open the registry key. Since we are using RegCreateKeyEx, 
    // the key will be created if it is not already there

    CHECK0(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        BitmapWindow_szRegKeyName,
        0,
        pClass,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        0,
        &hKey,
        &dwDisposition
    ));

    // Read the page margin values. If the values are not present, 
    // assume the default value of one inch from each side

    dwDataSize = sizeof(pWin->m_rMargin);

    if (RegQueryValueEx(
        hKey,
        _T("Margins"),
        0,
        &dwType,
        (PBYTE) &pWin->m_rMargin,
        &dwDataSize
    ) != ERROR_SUCCESS) {
        
        pWin->m_rMargin.left   = 1000;
        pWin->m_rMargin.top    = 1000;
        pWin->m_rMargin.right  = 1000;
        pWin->m_rMargin.bottom = 1000;
    }

    // Read the flag values

    dwDataSize = sizeof(pWin->m_dwFlags);

    if (RegQueryValueEx(
        hKey,
        _T("Flags"),
        0,
        &dwType,
        (PBYTE) &pWin->m_dwFlags,
        &dwDataSize
    ) != ERROR_SUCCESS) {

        pWin->m_dwFlags = 0;
    }

    // Read the current working directory

    dwDataSize = sizeof(szCurrentDirectory);

    if (RegQueryValueEx(
        hKey,
        _T("Current Directory"),
        0,
        &dwType,
        (PBYTE) szCurrentDirectory,
        &dwDataSize
    ) == ERROR_SUCCESS) {

        SetCurrentDirectory(szCurrentDirectory);
    }

    BEGIN_CLEANUP;

    if (hKey) {

        CHECK0(RegCloseKey(hKey));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_SaveRegistrySettings
//
// Routine Description:
//   Saves the settings to the registry
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_SaveRegistrySettings(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    HKEY  hKey = 0;
    PTSTR pClass = _T("");
    DWORD dwDisposition;
    RECT  rWindow;
    TCHAR szCurrentDirectory[MAX_PATH];

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK0(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        BitmapWindow_szRegKeyName,
        0,
        pClass,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        0,
        &hKey,
        &dwDisposition
    ));

    CHECK0(RegSetValueEx(
        hKey,
        _T("Margins"),
        0,
        REG_BINARY,
        (PBYTE) &pWin->m_rMargin,
        sizeof(pWin->m_rMargin)
    ));
        
    CHECK0(RegSetValueEx(
        hKey,
        _T("Flags"),
        0,
        REG_DWORD,
        (PBYTE) &pWin->m_dwFlags,
        sizeof(pWin->m_dwFlags)
    ));

    CHECK(GetWindowRect(
        pWin->m_hWnd,
        &rWindow
    ));

    // Store the width and height of the rectangle in the "right"
    // and "bottom" fields respectively
    
    rWindow.right -= rWindow.left;
    rWindow.bottom -= rWindow.top;

    CHECK0(RegSetValueEx(
        hKey,
        _T("Window Position"),
        0,
        REG_BINARY,
        (PBYTE) &rWindow,
        sizeof(rWindow)
    ));

    // Store the current directory

    CHECK(GetCurrentDirectory(
        COUNTOF(szCurrentDirectory),
        szCurrentDirectory
    ));

    CHECK0(RegSetValueEx(
        hKey,
        _T("Current Directory"),
        0,
        REG_SZ,
        (PBYTE) szCurrentDirectory,
        (_tcslen(szCurrentDirectory) + 1) * sizeof(TCHAR)
    ));

    BEGIN_CLEANUP;

    if (hKey) {

        CHECK0(RegCloseKey(hKey));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// EnableMenuItemID
//
// Routine Description:
//   Enables or disables a menu item
//
// Arguments:
//
// Return Value:
//   Zero on error / nonzero on success
//

__inline 
BOOL 
EnableMenuItemID(
    HMENU hMenu,
    UINT  uIDEnableItem,
    BOOL  bEnable
)
{
    return EnableMenuItem(
        hMenu,
        uIDEnableItem,
        MF_BYCOMMAND | 
        (bEnable ?  MF_ENABLED : MF_GRAYED)
    ) != 0xFFFFFFFF;
}

//////////////////////////////////////////////////////////////////////////
//
// CheckMenuItemID
//
// Routine Description:
//   Puts or removes the check mark on a menu item
//
// Arguments:
//
// Return Value:
//   Zero on error / nonzero on success
//

__inline 
BOOL 
CheckMenuItemID(
    HMENU hMenu,
    UINT  uIDCheckItem,
    BOOL  bCheck
)
{
    return CheckMenuItem(
        hMenu,
        uIDCheckItem,
        MF_BYCOMMAND | 
        (bCheck ?  MF_CHECKED : MF_UNCHECKED)
    ) != 0xFFFFFFFF;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnInitMenu
//
// Routine Description:
//   Modifies the window menu according to the current settings
//
// Arguments:
//   PBITMAPWINDOW pWin   pointer to the object  
//   HMENU         hMenu  handle to the window menu
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnInitMenu(
    PBITMAPWINDOW pWin,
    HMENU         hMenu
)
{
    USES_BRESULT;
    UINT  uItem;
    DWORD dwFlag;
    
    ASSERT(BitmapWindow_AssertValid(pWin));

    // enable / disable menu commands depending on whether 
    // a document is loaded, document is modified, etc.

    CHECK(EnableMenuItemID(hMenu, ID_FILE_SAVE, pWin->m_bIsDirty != 0));

    CHECK(EnableMenuItemID(hMenu, ID_FILE_SAVE_AS, pWin->m_bIsDirty != 0));

    CHECK(EnableMenuItemID(hMenu, ID_FILE_SELECT_SOURCE, g_bTwainFunctionalityPresent));

    CHECK(EnableMenuItemID(hMenu, ID_FILE_ACQUIRE, g_bTwainFunctionalityPresent));

    CHECK(EnableMenuItemID(hMenu, ID_FILE_ACQUIRE, g_bTwainFunctionalityPresent));

    CHECK(EnableMenuItemID(hMenu, ID_FILE_PAGE_SETUP, pWin->m_pDIB != 0));

    CHECK(EnableMenuItemID(hMenu, ID_FILE_PRINT, pWin->m_pDIB != 0));

#ifdef ICM_ENABLED

    CHECK(EnableMenuItemID(hMenu, ID_COLOR_SETUP, g_bICMFunctionalityPresent));

    CHECK(EnableMenuItemID(hMenu, ID_CMM_MANAGER, g_bICMFunctionalityPresent));

#endif ICM_ENABLED

    CHECK(EnableMenuItemID(hMenu, ID_EDIT_COPY, pWin->m_pDIB != 0));

    CHECK(EnableMenuItemID(hMenu, ID_EDIT_PASTE, IsClipboardFormatAvailable(CF_DIB)));

#ifdef ICM_ENABLED

    CHECK(EnableMenuItemID(hMenu, ID_EDIT_COLOR_SPACE, pWin->m_pDIB != 0));

#endif ICM_ENABLED

#ifdef ICM_OUTSIDE_DC

    CHECK(EnableMenuItemID(hMenu, ID_EDIT_TRANSFORM_DIB, g_bICMFunctionalityPresent && pWin->m_pDIB != 0));

    CHECK(EnableMenuItemID(hMenu, ID_EDIT_PROFILE_TO_PROFILE, g_bICMFunctionalityPresent && pWin->m_pDIB != 0));

#endif //ICM_OUTSIDE_DC

    for (
        uItem = ID_SETTINGS_FIRST, dwFlag = 1; 
        uItem <= ID_SETTINGS_LAST; 
        ++uItem, dwFlag <<= 1
    ) {

        CHECK(CheckMenuItemID(hMenu, uItem, pWin->m_dwFlags & dwFlag));
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnStretchToWindow
//
// Routine Description:
//   Updates the stretch flag
//
// Arguments:
//  PBITMAPWINDOW pWin     pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnStretchToWindow(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    RECT rWindow;

    ASSERT(BitmapWindow_AssertValid(pWin));

    // update the flag

    CHECK(BitmapWindow_ToggleMenuItem(
        pWin, 
        BWF_STRETCHTOWINDOW, 
        ID_VIEW_STRETCH_TO_WINDOW
    ));

    // redraw window

    CHECK(InvalidateRect(
        pWin->m_hWnd, 
        0, 
        FALSE
    ));

    // update the scroll bars

    CHECK(GetClientRect(
        pWin->m_hWnd,
        &rWindow
    ));

    SendMessage( 
        pWin->m_hWnd, 
        WM_SIZE, 
        SIZENORMAL, 
        MAKELONG(Rect_W(&rWindow), Rect_H(&rWindow))
    );

    BEGIN_CLEANUP;
    
    return BRESULT;
}
    
//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnKeepAspectRatio
//
// Routine Description:
//   Updates the KeepAspectRatio flag
//
// Arguments:
//  PBITMAPWINDOW pWin     pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnKeepAspectRatio(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(BitmapWindow_ToggleMenuItem(
        pWin, 
        BWF_KEEPASPECTRATIO, 
        ID_VIEW_KEEP_ASPECT_RATIO
    ));

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
// BitmapWindow_OnAutoResizeWindow
//
// Routine Description:
//   Updates the AutoResizeWindow flag
//
// Arguments:
//  PBITMAPWINDOW pWin     pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnAutoResizeWindow(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(BitmapWindow_ToggleMenuItem(
        pWin, 
        BWF_AUTORESIZEWINDOW,
        ID_VIEW_AUTO_RESIZE_WINDOW
    ));

    if (pWin->m_pDIB) {
    
        CHECK(BitmapWindow_AdjustWindowSize(pWin));
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_ToggleMenuItem
//
// Routine Description:
//   Toggles the value of a boolean flag and the associated menu selection
//
// Arguments:
//  PBITMAPWINDOW pWin      pointer to the object
//  DWORD         dwFlag    flag to update
//  UINT          uItem     the flag's menu identifier
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_ToggleMenuItem(
    PBITMAPWINDOW pWin,
    DWORD         dwFlag,
    UINT          uItem
)
{
    USES_BRESULT;
    HMENU hMenu;
    MENUITEMINFO mii; 
    
    ASSERT(BitmapWindow_AssertValid(pWin));

    // toggle the flag's value

    pWin->m_dwFlags ^= dwFlag;
    
    // update the menu accordingly

    CHECK(hMenu = GetMenu(pWin->m_hWnd));

    mii.cbSize = sizeof(mii);
    mii.fMask  = MIIM_STATE;
    mii.fState = pWin->m_dwFlags & dwFlag ? MFS_CHECKED : MFS_UNCHECKED;

    CHECK(SetMenuItemInfo(
        hMenu,
        uItem,
        FALSE,
        &mii
    ));

    // save the new settings to the registry

    CHECK(BitmapWindow_SaveRegistrySettings(pWin));

    BEGIN_CLEANUP;
    
    return BRESULT;
}

