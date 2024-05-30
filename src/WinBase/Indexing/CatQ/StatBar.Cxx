/*++

Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.

Module Name:

    statbar.cxx

Abstract:

    Functions required to support the status bar on the bottom of the window

Revision History:

    Steve Firebaugh     9-97          Created from previous samples

--*/


#include <windows.h>            // required for all Windows applications
#include <commctrl.h>           // prototypes and defs for common controls
#include "catq.h"




int catqCreateStatusBar(HWND hwnd)
/*++

    When the main window is created, call this function to create a status
     bar on the bottom of it.  Here, we also create a progress bar as a
     child of the status bar, and then size it in the partition routine.

    Notice that the Win32 API InitCommonControls() must be called before
     this function in order for CreateWindowEx() to succeed with the
     window classes that we are using here.

--*/
{
    HWND hwndStatusBar, hwndProgressBar;

    hwndStatusBar = CreateWindowEx ( NULL,
                                     STATUSCLASSNAME,
                                     TEXT("Comments"),
                                     WS_CHILD | WS_VISIBLE | WS_BORDER,
                                     0,0,0,0,
                                     hwnd,
                                     (HMENU)DID_STATUSBAR,
                                     NULL,
                                     NULL);


    hwndProgressBar = CreateWindowEx ( NULL,
                                       PROGRESS_CLASS,
                                       TEXT(""),
                                       WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                                       0,0,20, 30,
                                       hwndStatusBar,
                                       (HMENU)DID_PROGRESSBAR,
                                       NULL,
                                       NULL);

    catqPartitionStatusBar (hwndStatusBar);
    catqUpdateProgress (hwndStatusBar, CATQ_PROGRESS_ERROR, 0, 0) ;

    return TRUE;
}



int catqPartitionStatusBar(HWND hwndStatusBar)
/*++

    Divide the status bar up into separate "partitions."

    hwndStatusBar - the window handle to the status bar

--*/
{
    int   ptArray[3];
    RECT  rect;
    HDC   hDC;
    int   iQuantum;

    //
    // Fill in the ptArray values with the spacing of the different partitions.
    //

    hDC = GetDC(hwndStatusBar);
    GetClientRect(hwndStatusBar, &rect);
    ReleaseDC(hwndStatusBar, hDC);

    iQuantum = rect.right;
    iQuantum -= rect.bottom;
    iQuantum /= 4;

    ptArray[0] = iQuantum *2;
    ptArray[1] = ptArray[0] + iQuantum;
    ptArray[2] = ptArray[1] + iQuantum;


    //
    // Send this array to the status bar window...
    //

    SendMessage(hwndStatusBar,
                SB_SETPARTS,
                sizeof(ptArray)/sizeof(ptArray[0]),
                (LPARAM)(LPINT)ptArray);

    //
    // Now that the status bar is partitioned correctly, position the
    //  progress bar in the right most partition.
    //

    SetWindowPos ( GetDlgItem (hwndStatusBar, DID_PROGRESSBAR),
                    NULL,
                    ptArray[1]+2,
                    2,
                    iQuantum,
                    rect.bottom-2,
                    SWP_NOZORDER);

    return TRUE;

}




int catqUpdateProgress( HWND hwndStatusBar,
                        int iProgress,
                        LONG lToBeFiltered,
                        LONG lTotal )
/*++


    hwndStatusBar - the window handle to the status bar

--*/
{
#define SBTID_PROGRESS 1

    TCHAR lpszProgressString[MAX_PATH];

    if (iProgress == CATQ_PROGRESS_ERROR)
      wsprintf (lpszProgressString, TEXT("no CISVC status available"));
    else
      wsprintf (lpszProgressString,
                TEXT("To filter: %d / %d.  Done: %d %%"),
                lToBeFiltered, lTotal,
                iProgress);

    SendMessage(hwndStatusBar,
                SB_SETTEXT,
                SBTID_PROGRESS,
                (LPARAM)lpszProgressString);

    SendMessage (GetDlgItem (hwndStatusBar, DID_PROGRESSBAR), PBM_SETPOS, iProgress, 0);

    return TRUE;
}




int catqUpdateStatusComment(HWND hwndStatusBar, LPTSTR lpszStatusString)
{
/*++

    Set the second parameter string into the text of the status bar in
     the first partition.  This is where we report "comments" to the user.

--*/

    SendMessage(hwndStatusBar,
                SB_SETTEXT,
                0,
                (LPARAM)lpszStatusString);

    return TRUE;
}
