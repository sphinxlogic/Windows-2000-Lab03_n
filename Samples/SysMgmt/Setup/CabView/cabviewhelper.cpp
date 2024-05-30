//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  CabViewHelper.cpp
//
//      Implementation of CabView helper functions.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>


//
//  CabView_FormatFileSize
//
LPSTR WINAPI CabView_FormatFileSize (LPSTR lpBuffer, DWORD cbBuffer, ULONG nFileSize)
{
    CHAR szNumber[50] = "";
    NUMBERFMT nf = {0, 0, 3, ".", ",", 0};

    wsprintf (szNumber, "%ld", nFileSize);
    if (GetNumberFormat (NULL, 0, szNumber, &nf, lpBuffer, cbBuffer))
        return lpBuffer;
    return NULL;
}


//
//  CabView_FormatFileDateTime
//
LPSTR WINAPI CabView_FormatFileDateTime (LPSTR lpBuffer, DWORD cbBuffer, FILETIME *pft)
{
    SYSTEMTIME st = {0};
    CHAR szDate[12] = "";
    CHAR szTime[10] = "";

    FileTimeToSystemTime (pft, &st);
    GetTimeFormat (NULL, 0, &st, NULL, szTime, 12);
    GetDateFormat (NULL, DATE_SHORTDATE, &st, NULL, szDate, 10);

    if ((DWORD)(lstrlen (szDate) + lstrlen (szTime) + 2) > cbBuffer)
        return NULL;

    wsprintf (lpBuffer, "%s %s", szDate, szTime);
    return lpBuffer;
}


//
//  CabView_DisableAllMenuItems
//
VOID WINAPI CabView_DisableAllMenuItems (HMENU hMenu)
{
    INT iIndex = 0;
    UINT nState = 0;

    while ((nState = GetMenuState (hMenu, iIndex, MF_BYPOSITION)) != ((UINT)(-1)))
    {
        if (nState & MF_POPUP)
            CabView_DisableAllMenuItems (GetSubMenu (hMenu, iIndex));
        EnableMenuItem (hMenu, iIndex, MF_BYPOSITION|MF_GRAYED);
        iIndex++;
    }
}


//
//  CabView_PathFindFileName - Searches a path for a filename
//
LPTSTR WINAPI CabView_PathFindFileName (LPCTSTR lpPath)
{
    if (lpPath == NULL)
        return NULL;

    LPTSTR lpFilename = (LPTSTR)&lpPath[lstrlen(lpPath) - 1];
    BOOL bIsFile = FALSE;

    while (lpFilename > lpPath && *lpFilename != TEXT('\\'))
    {
        if (*lpFilename == TEXT('.'))
            bIsFile = TRUE;
        lpFilename--;
    }

    lpFilename++;
    if (bIsFile == TRUE)
        return lpFilename;
    return (LPTSTR)lpPath;
}


//
//  CabView_RemoveFileName - Removes the filename from a path
//
BOOL WINAPI CabView_RemoveFileName (LPTSTR lpPath)
{
    LPTSTR lpFilename = CabView_PathFindFileName (lpPath);
    if (lpFilename == lpPath)
        return FALSE;

    *lpFilename = TEXT('\0');
    return TRUE;
}