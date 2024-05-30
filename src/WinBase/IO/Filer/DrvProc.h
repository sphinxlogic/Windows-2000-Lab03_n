
/******************************************************************************\
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1993-1999.  Microsoft Corporation.  All rights reserved.

*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/


//
// Forward declarations in DRVPROC.C
//
LONG    GetLBText           (HWND, PTCHAR);

BOOL    OpenListBoxItem     (LPCINFO);
BOOL    RunListBoxItem      (LPCINFO);
BOOL    FilerGetVersion     (LPTSTR, DWORD, LPTSTR);
BOOL    IsDirectory         (LPTSTR, LPTSTR);

BOOL    ExecuteFileAction   (LPSINFO);
BOOL    FillSelectDlg       (HWND, LPSINFO);
BOOL    DoFileIO            (HWND, LPSINFO);
void    UpdateFileLB        (HWND);
BOOL    HandleIOError       (HWND, DWORD, LPTSTR, LPTSTR);
PTCHAR  TStrChr             (const PTCHAR, UINT);


LRESULT WINAPI DrvWndProc   (HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI VersionProc  (HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI SelectProc   (HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI RenameProc   (HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI MkDirProc    (HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI TextWndProc  (HWND, UINT, WPARAM, LPARAM);
