//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  CabView.h
//
//////////////////////////////////////////////////////////////////////

#ifndef CABVIEW_H_INCLUDED
#define CABVIEW_H_INCLUDED

#include "Cabinet.h"

#define WC_CABVIEW  TEXT("CabViewWndClass")

typedef struct 
{
    CHAR szFileName[MAX_PATH];
    CHAR szTypeName[80];
    FILETIME FileTime;
    ULONG nFileSize;
    ULONG nFileAttributes;
} CABINET_FILE_INFO, *PCABINET_FILE_INFO, *LPCABINET_FILE_INFO;

typedef struct
{
    LPSTR lpDestinationDir;
    LPSTR *lpFileList;
} CABINET_EXTRACT_INFO, *PCABINET_EXTRACT_INFO, *LPCABINET_EXTRACT_INFO;

typedef struct
{
    HFDI hFdi;
    BOOL bCabinetOpen;
    CHAR szOpenFile[MAX_PATH];
} CABVIEW_INFO, *PCABVIEW_INFO, *LPCABVIEW_INFO;

#define HANDLE_WM_COMMAND_ID(id, fn) \
    case (id): ((fn)((hWnd), (id), (hWndCtrl), (nCode))); return

// Window/Dialog Procedures
LRESULT CALLBACK CabView_WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK CabView_ExtractDlgProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Helper Functions
VOID WINAPI CabView_DisableAllMenuItems (HMENU hMenu);
LPSTR WINAPI CabView_FormatFileSize (LPSTR lpBuffer, DWORD cbBuffer, ULONG nFileSize);
LPSTR WINAPI CabView_FormatFileDateTime (LPSTR lpBuffer, DWORD cbBuffer, FILETIME *pft);
LPTSTR WINAPI CabView_PathFindFileName (LPCTSTR lpPath);
BOOL WINAPI CabView_RemoveFileName (LPTSTR lpPath);

// Extract destination selection function
VOID WINAPI CabView_GetDestinationPath (HWND hWnd, LPSTR lpDestination);

// Callback Functions Used By Cabinet_Copy
INT CDECL CabView_DecryptCallback (PFDIDECRYPT pfdid);
INT CDECL CabView_CabinetNotifyCallback (FDINOTIFICATIONTYPE fdint, PFDINOTIFICATION pfdin);
INT CDECL CabView_ExtractNotifyCallback (FDINOTIFICATIONTYPE fdint, PFDINOTIFICATION pfdin);

#endif // CABVIEW_H_INCLUDED
