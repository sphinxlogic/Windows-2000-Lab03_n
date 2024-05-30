/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    about.c

Abstract:

    Implementation of the about dialog

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"

#include "BitmapWin.h"


//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnHelpAbout
//
// Routine Description:
//   Displays an "about" dialog. Reads the version information is from
//   the resources.
//
// Arguments:
//  PBITMAPWINDOW pWin      pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnHelpAbout(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    TCHAR   szFileName[MAX_PATH];
    DWORD   dwHandle;
    DWORD   dwVerInfoSize;
    PVOID   pVerInfo = 0;
    PDWORD  pLangCodePageId = 0;
    TCHAR   szStringFileInfo[80];
    PTSTR   pStringFileInfoName = 0;
    PTSTR   pInternalName = 0;
    PTSTR   pFileDescription = 0;
    UINT    uSize;

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

    _tcscpy(pStringFileInfoName, _T("InternalName"));

    CHECK(VerQueryValue(
        pVerInfo,
        szStringFileInfo,
        (PVOID *) &pInternalName,
        &uSize
    )); 

    _tcscpy(pStringFileInfoName, _T("FileDescription"));

    CHECK(VerQueryValue(
        pVerInfo,
        szStringFileInfo,
        (PVOID *) &pFileDescription,
        &uSize
    )); 

    BEGIN_CLEANUP;
    
    ShellAbout(
        pWin->m_hWnd,
        pInternalName,
        pFileDescription,
        pWin->m_hIcon
    );

    if (pVerInfo) {

        CHECK(GlobalFree(pVerInfo) == 0);
    }

    return BRESULT;
}

