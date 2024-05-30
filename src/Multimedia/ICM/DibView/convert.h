/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
    convert.h

Abstract:
    
    Header file for convert.c

--*/

#ifndef CONVERT_H
#define CONVERT_H

#ifdef ICM_ENABLED

BOOL
EditColorSpaceDialog_DoModal(
    LPLOGCOLORSPACE plcs,
    HWND            hWndParent
);

BOOL
CALLBACK 
EditColorSpaceDialog_DialogProc(  
    HWND   hDlg,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
);

BOOL
EditColorSpaceDialog_SetDialogData(
    HWND            hDlg,
    LPLOGCOLORSPACE plcs
);

BOOL
EditColorSpaceDialog_GetDialogData(
    HWND            hDlg,
    LPLOGCOLORSPACE plcs
);

BOOL
EditColorSpaceDialog_OnUpdateCSType(
    HWND            hDlg
);

#endif //ICM_ENABLED


#ifdef ICM_OUTSIDE_DC

typedef struct _PROFILETOPROFILEDIALOG {

	LOGCOLORSPACE m_lcsSrc;
	LOGCOLORSPACE m_lcsDst;

} PROFILETOPROFILEDIALOG, *PPROFILETOPROFILEDIALOG;


BOOL
ProfileToProfileDialog_DoModal(
    PPROFILETOPROFILEDIALOG pDlg,
    HWND					hWndParent
);

BOOL
CALLBACK 
ProfileToProfileDialog_DialogProc(  
    HWND   hDlg,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
);

BOOL
ProfileToProfileDialog_SetDialogData(
    HWND                    hDlg,
    PPROFILETOPROFILEDIALOG pDlg
);

BOOL
ProfileToProfileDialog_GetDialogData(
    HWND                    hDlg,
    PPROFILETOPROFILEDIALOG pDlg
);

#endif //ICM_OUTSIDE_DC

//
// inline functions
//

__inline 
BOOL
ComboBox_ResetContent(
    HWND   hWnd
)
{
    SendMessage(
        hWnd, 
        CB_RESETCONTENT, 
        0, 
        0
    );
    
    return TRUE;
}



__inline 
int
ComboBox_FindString(
    HWND   hWnd,
    int    indexStart,
    PCTSTR pszFind
)
{ 
    return (int) SendMessage(
        hWnd, 
        CB_FINDSTRING, 
        (WPARAM)  indexStart, 
        (LPARAM)  pszFind
    );
}

__inline 
BOOL
ComboBox_InsertString(
    HWND   hWnd,
    int    index,
    PCTSTR psz
)
{ 
    return SendMessage(
        hWnd, 
        CB_INSERTSTRING, 
        (WPARAM)  index, 
        (LPARAM)  psz
    ) == (LPARAM) index;
}

__inline 
BOOL
ComboBox_AddString(
    HWND   hWnd,
    PCTSTR psz
)
{ 
    return SendMessage(
        hWnd, 
        CB_ADDSTRING, 
        0, 
        (LPARAM) psz
    ) >= 0;
}

__inline 
BOOL
ComboBox_GetLBText(
    HWND  hWnd,
    int   index,
    PTSTR pszBuffer
)
{ 
    if (index < 0) {

        pszBuffer[0] = '\0';

        return TRUE;
    }

    return SendMessage(
        hWnd, 
        CB_GETLBTEXT, 
        (WPARAM) index, 
        (LPARAM) pszBuffer
    ) >= 0;
}

__inline 
BOOL
ComboBox_SetCurSel(
    HWND  hWnd,
    int   index
)
{
    if (index < 0) {

        index = 0;
    }

    return SendMessage(
        hWnd, 
        CB_SETCURSEL, 
        (WPARAM) index, 
        0
    ) == index;
}

__inline 
int
ComboBox_GetCurSel(
    HWND   hWnd
)
{
    return (int) SendMessage(
        hWnd, 
        CB_GETCURSEL, 
        0, 
        0
    );
}

__inline 
BOOL
SetFloat(
    HWND   hWnd,
    double nNum
)
{
    TCHAR szNum[10];
        
    _stprintf(szNum, _T("%.5f"), nNum);
    
    return SetWindowText(hWnd, szNum);
}

__inline 
double
GetFloat(
    HWND   hWnd
)
{
    char szNum[10];

    GetWindowTextA(
        hWnd, 
        szNum, 
        COUNTOF(szNum)
    );

    return atof(szNum);
}




#endif //CONVERT_H


