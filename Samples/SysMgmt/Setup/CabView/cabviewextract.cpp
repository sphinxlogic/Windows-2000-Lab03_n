//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  CabViewExtract.cpp
//
//      Defines callback function used by FDICopy to extract files.
//
////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include "CabView.h"
#include "Cabinet.h"
#include "Resource.h"

LPSTR lpExtractPath = NULL;

//
//  BrowseCallbackProc - Callback function for SHBrowseForFolder
//
INT CALLBACK BrowseCallbackProc (HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    switch (uMsg)
    {
        case BFFM_INITIALIZED:
            SendMessage (hWnd, BFFM_SETSELECTION, TRUE, lpData);
            break;
    }
    return 0;
}


//
//  CabView_GetDestinationPath - Prompts user to select a destination 
//                               folder for extracted files. Uses
//                               SHBrowseForFolder.
//
VOID WINAPI CabView_GetDestinationPath (HWND hWnd, LPSTR lpDestination)
{
    CHAR szDisplayName[MAX_PATH] = "";
    BROWSEINFO bi = {0};
    LPITEMIDLIST pidl = NULL;

    bi.hwndOwner = hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szDisplayName;
    bi.lpszTitle = "Select the destination folder for extracted files.";
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
    bi.lpfn = BrowseCallbackProc;
    bi.lParam = (LPARAM) lpDestination;

    pidl = SHBrowseForFolder (&bi);
    if (pidl != NULL)
    {
        SHGetPathFromIDList (pidl, lpDestination);

        LPMALLOC pMalloc = NULL;
        SHGetMalloc (&pMalloc);
        pMalloc->Free ((LPVOID) pMalloc);
        pMalloc->Release ();
    }
}


//
//  CabView_IsFileInFileList - Called to determine if the current file being
//                             examined in the FDICopy function is in the list
//                             of files to be extracted.
//
BOOL CDECL CabView_IsFileInFileList (LPSTR lpFilename, LPSTR *lpFileList)
{
    UINT nIndex = 0;

    while (lpFileList[nIndex] != NULL)
    {
        if (lstrcmpi (lpFilename, lpFileList[nIndex]) == 0)
            return TRUE;
        nIndex++;
    }
    return FALSE;
}


//
//  CabView_ExtractNotifyCallback - Called by FDICopy to notify the
//                                  of file operations on a CAB file
//                                  or to provide information about 
//                                  the CAB file.
//
//                                  Used here to extract a list of
//                                  files from a CAB file
//
INT CDECL CabView_ExtractNotifyCallback (FDINOTIFICATIONTYPE fdint, PFDINOTIFICATION pfdin)
{
    LPCABINET_EXTRACT_INFO pcei = (LPCABINET_EXTRACT_INFO) pfdin->pv;
    LPSTR *lpFileList = pcei->lpFileList;
    CHAR szFileToCreate[MAX_PATH] = "";

    switch (fdint)
    {
        case fdintCOPY_FILE:
            if (CabView_IsFileInFileList (pfdin->psz1, lpFileList) == FALSE)
                return 0;

            // Create the file to extract to.
            wsprintf (szFileToCreate, "%s\\%s", pcei->lpDestinationDir, pfdin->psz1);
            return Cabinet_CreateFile (szFileToCreate, O_CREAT | O_RDWR | O_BINARY, S_IWRITE);

        case fdintCLOSE_FILE_INFO:
            if (Cabinet_CloseFile (pfdin->hf) == 0)
                return 1;
            return 0;
            break;
    }
    return 1;
}

