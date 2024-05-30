/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    selsource.h

Abstract:
    
    Header file for selsource.c

--*/

#ifndef SELSOURCE_H
#define SELSOURCE_H

typedef struct _SELECTSOURCEDIALOG {

    HWND                    m_hWndDlg;
    TW_IDENTITY             m_AppId;
    TW_IDENTITY             m_SelectedSrcId;
    TCHAR                   m_szSelectedProfileName[MAX_PATH];
    PSTI                    m_pSti;
    PSTI_DEVICE_INFORMATION m_pdi;
    DWORD                   m_dwNumDevices;

} SELECTSOURCEDIALOG, *PSELECTSOURCEDIALOG;

BOOL
SelectSourceDialog_Construct(
    PSELECTSOURCEDIALOG pDlg,
    pTW_IDENTITY        pAppId
);

BOOL
SelectSourceDialog_Destruct(
    PSELECTSOURCEDIALOG pDlg
);

BOOL
SelectSourceDialog_FreeSourcesList(
    HWND hList
);

BOOL
SelectSourceDialog_DoModal(
    PSELECTSOURCEDIALOG pDlg,
    HWND                hWndParent
);

BOOL 
CALLBACK 
SelectSourceDialog_DialogProc(  
    HWND   hWndDlg,
    UINT   uMsg,
    WPARAM wParam,
    LPARAM lParam
);

BOOL
SelectSourceDialog_InitDialog(
    PSELECTSOURCEDIALOG pDlg,
    HWND                hWndDlg
);

BOOL
SelectSourceDialog_FillSourceNames(
    PSELECTSOURCEDIALOG pDlg
);

BOOL
SelectSourceDialog_FillProfileNames(
    PSELECTSOURCEDIALOG pDlg
);

BOOL
SelectSourceDialog_OnSourceChange(
    PSELECTSOURCEDIALOG pDlg,
    LPNMLISTVIEW        pnmlv
);

BOOL
SelectSourceDialog_OnProfileChange(
    PSELECTSOURCEDIALOG pDlg,
    LPNMLISTVIEW        pnmlv
);

BOOL
GetDeviceValue_ReAlloc(
    IStillImage *pSti,
    PWSTR       pDeviceName,
    PWSTR       pValueName,
    PBYTE       *ppBuffer
);

BOOL
EnumColorProfiles_ReAlloc(
    PENUMTYPE pet,
    PBYTE     *ppBuffer
);

#endif //SELSOURCE_H

