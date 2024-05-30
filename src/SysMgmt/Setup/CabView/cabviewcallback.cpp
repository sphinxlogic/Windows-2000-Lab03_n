//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  CabViewCallback.cpp
//
//      Defines callback functions used by FDICopy.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include "CabView.h"
#include "Resource.h"

//
//  CabView_DecryptCallback - Called by FDICopy to notify the 
//                            application to update the decryption
//                            state and to decrypt data blocks. See
//                            FDI.H for more information
//
INT CDECL CabView_DecryptCallback (PFDIDECRYPT pfdid)
{
    return TRUE;
}


//
//  CabView_CabinetNotifyCallback - Called by FDICopy to notify the
//                                  of file operations on a CAB file
//                                  or to provide information about 
//                                  the CAB file.
//
//                                  Used here to build a list of files
//                                  to add to the listview
//
INT CDECL CabView_CabinetNotifyCallback (FDINOTIFICATIONTYPE fdint, PFDINOTIFICATION pfdin)
{
    if (fdint == fdintCOPY_FILE)
    {
        INT iIndex = 0;
        SHFILEINFO shfi = {0};
        LVITEM item = {0};

        // Store the file's information in a CABINET_FILE_INFO structure. Each item inserted
        // into the list view will have a CABINET_FILE_INFO structure
        LPCABINET_FILE_INFO pcfi = (LPCABINET_FILE_INFO) LocalAlloc (LPTR, sizeof (CABINET_FILE_INFO));
        if (pcfi == NULL)
            return FALSE;

        // Copy the filename
        lstrcpy (pcfi->szFileName, pfdin->psz1);

        // Retrieve and copy the file's type
        SHGetFileInfo (pcfi->szFileName, FILE_ATTRIBUTE_NORMAL, &shfi, 
                       sizeof (SHFILEINFO), 
                       SHGFI_USEFILEATTRIBUTES | SHGFI_TYPENAME);
        lstrcpy (pcfi->szTypeName, shfi.szTypeName);

        // Convert the DOS time to a FILETIME and store the value
        DosDateTimeToFileTime (pfdin->date, pfdin->time, &pcfi->FileTime);

        // Store the file size
        pcfi->nFileSize = pfdin->cb;

        // Store the file attributes
        pcfi->nFileAttributes = pfdin->attribs;

        // Insert the file into the list view
        item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
        item.pszText = LPSTR_TEXTCALLBACK;
        item.iImage = I_IMAGECALLBACK;
        item.lParam = (LPARAM) pcfi;
        iIndex = ListView_InsertItem (GetDlgItem ((HWND) pfdin->pv, IDC_CABINET_LIST), &item);

        // Add the subitem text for the file's size
        ListView_SetItemText (GetDlgItem ((HWND) pfdin->pv, IDC_CABINET_LIST), iIndex, 1, LPSTR_TEXTCALLBACK);

        // Add the subitem text for the file's date/time
        ListView_SetItemText (GetDlgItem ((HWND) pfdin->pv, IDC_CABINET_LIST), iIndex, 2, LPSTR_TEXTCALLBACK);

        // Add the subitem text for the file's description
        ListView_SetItemText (GetDlgItem ((HWND) pfdin->pv, IDC_CABINET_LIST), iIndex, 3, LPSTR_TEXTCALLBACK);

        // Indicate that we are not extracting the file by returning FALSE
        return FALSE;
    }
    return TRUE;
}


