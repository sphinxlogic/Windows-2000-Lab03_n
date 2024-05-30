/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
    CMMman.h

Abstract:
    
    Header file for CMMman.c

--*/

#ifndef CMMMAN_H
#define CMMMAN_H

//
// Function prototypes
//

BOOL 
CALLBACK 
CMMDialog_DialogProc(  
    HWND   hWndDlg,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
);

BOOL
CMMDialog_InitDialog(
    HWND hList
);

BOOL
CMMDialog_EnumCMM(
    HWND hList
);

BOOL
CMMDialog_AddCMM(
    HWND hList
);

BOOL
CMMDialog_RemoveCMM(
    HWND hList
);

BOOL
CMMDialog_SelectCMM(
    HWND hList
);

DWORD
CMMDialog_GetSelectedCMMID(
    HWND hList
);

PCTSTR
CMMDialog_GetCMMFileName();

#endif //CMMMAN_H

