/*++

Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.

Module Name:

    main.cxx

Abstract:

    WinMain() and other functions required to interact with Windows.

Revision History:

    Steve Firebaugh     9-97          Created from previous samples

--*/


#include <windows.h>
#include <commctrl.h>
#include <ntquery.h>
#include "catq.h"


//
// Declare a global HWND for this module.  It will contain the window
//  handle for the main dialog.  Make it global so that the comment
//  and result reporting functions in this module do not require HWND
//  parameters (since they are called from other modules that don't
//  need to know anything about HWND).
//

HWND hwndGlobalDlg = NULL;




int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
/*++

  required for all WIN32 applications
  input parameters:  c.f. generic sample

--*/
{
    int iRet;

    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
    UNREFERENCED_PARAMETER( nCmdShow);


    //
    // Detect platform and exit gracefully if app will not work correctly.
    //  notice that this may need to be updated over time if/when Index Server
    //  is expanded to run on additional platforms.
    //
    // Here we check first for Windows NT, and then for version 5 or greater.
    //

    {
      OSVERSIONINFO osvi;
      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      GetVersionEx (&osvi);

      if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) {
        MessageBox (NULL,
                    TEXT ("Application requires Windows NT"),
                    SZ_APP_TITLE,
                    MB_OK | MB_ICONSTOP);
        return 0;
      }

      if (osvi.dwMajorVersion < 5) {
        MessageBox (NULL,
                    TEXT ("Application requires at least Windows NT version 5"),
                    SZ_APP_TITLE,
                    MB_OK | MB_ICONSTOP);
        return 0;
      }
    }  // end version checking



    //
    // Just put up a dialog box that does all of the work.  Interesting code
    //  is in the MainDlgProc() below.
    //
    // Here we use DialogBoxParam() rather than just DialogBox(), because we
    //  want to pass the hInstance to the WM_INITDIALOG message.
    //

    iRet = (int) DialogBoxParam (hInstance,
                           TEXT("mainDlg"),
                           NULL,
                           (DLGPROC)MainDlgProc,
                           (LPARAM) hInstance);
    return iRet;
}




LRESULT CALLBACK MainDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
/*++

  standard WIN32 dialog procedure for the main window

  input parameters:  c.f. generic sample

--*/
{

  switch (message) {

    case WM_INITDIALOG: {

      //
      // Store the hwnd in the global variable for use later.
      //

      hwndGlobalDlg = hwnd;


      //
      // The dialog template in the .rc file specifies the location and size
      //  of most of the "child controls."  However, we also want a status bar
      //  on the bottom of the main window.  Create the status bar here, but
      //  before doing that, call the Windows function to initialize the
      //  common controls.  StatusBars and ProgressBars are "common controls"
      //  and will not work until InitCommonControls is called.
      //

      InitCommonControls ();
      catqCreateStatusBar (hwnd);


      //
      // Set the font for the text display windows to be a fixed width font
      //

      SendDlgItemMessage (hwnd,
                          DID_OUTRESULTS,
                          WM_SETFONT,
                          (WPARAM) GetStockObject (ANSI_FIXED_FONT),
                          (LPARAM) 0 );

      //
      // Set initial values into the input controls.  For the machine this
      //  is just "."  For the catalog, we call the appropriate query API.
      //  For the directory scope, we try to locate the SDK.  For the search
      //  text we start with some friendly initial string.
      //

      { WCHAR szbuffer[MAX_PATH];

      SetWindowText (GetDlgItem (hwnd, DID_MACHINE), TEXT("."));

      catqInitializeSDKPath (GetDlgItem (hwnd, DID_SCOPE), szbuffer);

      catqInitializeCatalogs (GetDlgItem (hwnd, DID_CATALOG), szbuffer);

      SetWindowText (GetDlgItem (hwnd, DID_CONTAIN), TEXT("<search text here>"));
      }

      //
      // Select all of the text in the search-string edit control so that
      //  anything the user types will replace what is there.
      //

      SendMessage (GetDlgItem (hwnd, DID_CONTAIN), EM_SETSEL, 0, MAX_PATH);
      SetFocus ( GetDlgItem (hwnd, DID_CONTAIN));


      //
      // Since main window is a dialog it does not get an app defined icon
      //  by default... so, load one out of the built in resources, and
      //  associate it with this window.  Notice hInstance passed in as
      //  lParam ala DialogBoxParam().
      //

      SendMessage (hwnd, WM_SETICON, ICON_BIG, (LPARAM) LoadIcon ((HINSTANCE)lParam, TEXT("catqIcon")));


      //
      // Start a window timer to post us a messsage every one second.
      //  Use this later to keep fields in the status bar up-to-date.
      //

      SetTimer (hwnd, TID_PROGRESS, 1000, NULL);


      //
      // Content indexing is only available if the correct service is running.
      //  Ensure that it is running, or start it if it is not.
      //

      catqStartCIService ( hwnd );

      return FALSE;
    } break;  // WM_INITDIALOG


    case WM_TIMER:

      //
      // Timer messages with ID of TID_PROGRESS indicate that we should
      //  query the progress of the indexing effort.
      //

      if ((int) wParam == TID_PROGRESS) {
        LONG lTotal, lFinished;
        int iProgress;

        iProgress = catqPDHQueryProgress (&lFinished, &lTotal);

        catqUpdateProgress (GetDlgItem (hwnd, DID_STATUSBAR),
                            iProgress,
                            lFinished, lTotal);


      }
    break;


    case WM_COMMAND:

    //
    // Handle the events caused by the buttons on the main page
    //

      switch (LOWORD(wParam)) {

        //
        // When one of the files in the listbox is double clicked, launch
        //  the file that has been selected.  If ShellExecute() fails, try
        //  to load the file into notepad.  This will work for all "text files"
        //  but will look ugly for "binary files" that are indexed.
        //

        case DID_OUTRESULTS      :
          if (HIWORD (wParam) == LBN_DBLCLK) {
            HWND hwndLB;
            LRESULT lRet;
            TCHAR pszBuffer [ MAX_PATH ] ;

            hwndLB = GetDlgItem (hwnd, DID_OUTRESULTS);
            lRet = SendMessage (hwndLB, LB_GETCURSEL, 0,0);
            lRet = SendMessage (hwndLB, LB_GETTEXT, (WPARAM)lRet, (LPARAM) pszBuffer);

            lRet = (LRESULT) ShellExecute (NULL,
                                           TEXT("open"),
                                           pszBuffer,
                                           NULL,
                                           NULL,
                                           SW_SHOW);

            if (lRet <= 32 ) { // magic number, see docs
              catqLogCommentVariable (TEXT ("ShellExecute (%s) failed (%Id).  Loading into notepad." ),
                                      pszBuffer, lRet);
              lRet = (LRESULT) ShellExecute (NULL,
                                             TEXT("open"),
                                             TEXT("notepad"),
                                             pszBuffer,
                                             NULL,
                                             SW_SHOW);
            }
          }
        break;


        //
        // When the "find now" button is hit, take appropriate action.
        //

        case DID_FINDNOW      : {
           TCHAR szCatalog[MAX_PATH]     = TEXT("");
           TCHAR szMachine[MAX_PATH]     = TEXT("");
           TCHAR szScope[MAX_PATH]     = TEXT("");
           TCHAR szRestriction[MAX_PATH] = TEXT("");

           HRESULT hr;

           //
           // Clear out the old results list from the listbox,
           //

           SendMessage( GetDlgItem (hwnd, DID_OUTRESULTS),
                        LB_RESETCONTENT, 0, 0);


           //
           // Query the edit controls for the user specified parameters
           //

           GetWindowText (GetDlgItem (hwnd, DID_CATALOG),
                         szCatalog,
                         MAX_PATH);

           GetWindowText (GetDlgItem (hwnd, DID_MACHINE),
                         szMachine,
                         MAX_PATH);

           GetWindowText (GetDlgItem (hwnd, DID_SCOPE),
                         szScope,
                         MAX_PATH);

           GetWindowText (GetDlgItem (hwnd, DID_CONTAIN),
                         szRestriction,
                         MAX_PATH);


           //
           // And finally, with these parameters, call our own function
           //  to perform the query (and display the results).
           //

           hr = DoQuery( szCatalog,
                         szMachine,
                         szScope,
                         szRestriction);

           if ( FAILED( hr ) )
           {
               catqReportError ( hr );
               return 0;
           }

        } break;

      } // end switch (LOWORD())

    break; // WM_COMMAND



    case WM_SIZE: {

      //
      // Pass the WM_SIZE along to the status bar window procedure (provided
      //  by windows, not part of this application code)...  it will resize
      //  itself to fit in the bottom of the window... once this is done,
      //  re-space the different sections of  the status bar with our function.
      //

      SendMessage (GetDlgItem (hwnd, DID_STATUSBAR),
                   WM_SIZE, wParam, lParam);

      catqPartitionStatusBar (GetDlgItem (hwnd, DID_STATUSBAR));



      //
      // Adjust the large list box to fill the remainder of the window.
      //

#define NICEBORDER 5
#define BELOWINPUTCONTROLS 115

      int x, y, cx, cy;
      int nWidth, nHeight;
      RECT rect;

      nWidth = LOWORD (lParam);
      nHeight = HIWORD (lParam);

      SendMessage (GetDlgItem (hwnd, DID_STATUSBAR), SB_GETRECT, 0, (LPARAM) &rect);

      x = NICEBORDER;
      cx = nWidth - (2* NICEBORDER);

      nHeight -= BELOWINPUTCONTROLS;
      nHeight -= rect.bottom;
      nHeight -= 2* NICEBORDER;

      cy = (nHeight > 0) ? nHeight : 0;

      y = BELOWINPUTCONTROLS + NICEBORDER;
      SetWindowPos ( GetDlgItem (hwnd, DID_OUTRESULTS),
                    NULL,
                    x,
                    y,
                    cx,
                    cy,
                    SWP_NOZORDER);
      return 0;

    } break; // WM_SIZE


    case WMAPP_ADDRESULT:

      //
      // Application defined message.
      //
      // Append a new file name to the bottom of the results listbox.
      //
      // wParam is ignored
      // lParam is pointer to the string to add to the listbox.
      //

      SendMessage (GetDlgItem (hwnd, DID_OUTRESULTS),
                     LB_ADDSTRING, 0, lParam);

    break;


    case WM_SYSCOMMAND:

    //
    //  ignore all syscommand messages, except for SC_CLOSE.  On this one,
    //   log one final comment for the debugger output and call EndDialog().
    //

      if (wParam == SC_CLOSE) {

        catqLogComment (TEXT("bye."));

        EndDialog (hwnd, TRUE);
        return TRUE;
      } else
        return FALSE;
    break;


    default: return FALSE;
  } // end switch(message)
  return TRUE;
}



int catqInitializeCatalogs ( HWND hwndComboBox, LPTSTR pszScope )
/*++

    Fill the combobox indicated by the first parameter with catalogs
     as returned by the WIN32 API LocateCatalogs.  The second parameter
     is the "scope" that we are checking catalogs for.  We expect this
     to be the directory location of the SDK.

--*/
{
#define PSZ_SYSTEMCATALOG TEXT("System")

    HRESULT hr = S_OK;
    ULONG iBmk;
    ULONG iCountSuccess = 0;

    //
    // Loop through calls to LocateCatalogs until the return value is not
    //  S_OK.  For any catalog that we get, verify that the strings were
    //  big enough, and add the catalog name to the combobox.
    //
    // This code is taken from the LocateCatalogs documentation.
    //

    for ( iBmk = 0; S_OK == hr; iBmk++ ) {

      TCHAR atcMachine[ MAX_COMPUTERNAME_LENGTH + 1 ];
      const ULONG ctcMachineBuffer = sizeof atcMachine / sizeof TCHAR;
      ULONG ctcMachine = ctcMachineBuffer;
      TCHAR atcCatalog[ MAX_PATH + 1 ];
      const ULONG ctcCatalogBuffer = sizeof atcCatalog / sizeof TCHAR;
      ULONG ctcCatalog = ctcCatalogBuffer;


      hr = LocateCatalogs( pszScope,
                           iBmk,
                           atcMachine,
                           &ctcMachine,
                           atcCatalog,
                           &ctcCatalog );

      if ( ( hr == S_OK ) &&
           ( ctcMachine <= ctcMachineBuffer ) &&
           ( ctcCatalog <= ctcCatalogBuffer ) )    {
          iCountSuccess++;
          SendMessage ( hwndComboBox,
                        CB_ADDSTRING,
                        0,
                        (LPARAM) atcCatalog);

      }
    }


    //
    // In some cases (the scope parameter is "\" for example) LocateCatalogs
    //  will not return any useful catalogs.  We detect this case by comparing
    //  iCountSuccess with 0.  In this case, add the system catalog anyway.
    //
    // The failure of LocateCatalogs("\" ... ) may change in a later release.
    //

    if (iCountSuccess == 0)
        SendMessage ( hwndComboBox,
                      CB_ADDSTRING,
                      0,
                      (LPARAM) PSZ_SYSTEMCATALOG);


    //
    // Select the initial value to be the system catalog.
    //

    SendMessage ( hwndComboBox,
                  CB_SELECTSTRING,
                  0,
                  (LPARAM) PSZ_SYSTEMCATALOG);
    return TRUE;
}



int catqInitializeSDKPath (HWND hwndEdit, LPTSTR pszPath )
/*++

    This routine is called one time at window creation time.  It initializes
     the value in the passed in edit control to be equal to the directory
     location of the SDK.  Separate this out as a function only because
     the logic is rather involved and would clutter up the main window proc.

    hwndEdit -- the edit control that this function fills.
    pszPath -- buffer to return the path in to the calling routine.

--*/
{
    DWORD dwRet;
    TCHAR pszSDKEnvVar[MAX_PATH];

    //
    // Query the environment for the location where the SDK is installed.
    //

    dwRet = GetEnvironmentVariable (TEXT("MSSDK"), pszSDKEnvVar, MAX_PATH);

    if (dwRet == 0) {
      catqLogComment (TEXT("Can't locate SDK.  Defaulting to \\."));
      lstrcpy (pszSDKEnvVar, TEXT("\\"));
    }

    SetWindowText (hwndEdit, pszSDKEnvVar);
    lstrcpy (pszPath, pszSDKEnvVar);

  return TRUE;
}



int catqReportError ( int iError )
/*++

    Call WIN32 API GetLastError, format it for human consumption, and pass
     it along to our application output routine.

--*/
{
    DWORD  dwRet;
    TCHAR  szBuffer[MAX_PATH], szCommentStr[MAX_PATH];

    dwRet = FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           iError,
                           LANG_NEUTRAL,
                           szBuffer,
                           MAX_PATH,
                           NULL);


    //
    // If formatmessage succeeds, glue the numeric value on the end just
    //  for fun.  If it fails, report that along with the numeric value.
    //

    if (dwRet)
        wsprintf (szCommentStr,
                  TEXT("%s (0x%x)"),
                  szBuffer,
                  iError);

    else
        wsprintf (szCommentStr,
                  TEXT("FormatMessage failed on 0x%x"),
                  iError);


    catqLogComment ( szCommentStr );

    return TRUE;
}


void
_cdecl
catqReportResultsVariable(
    PTCH Format,
    ...
    )
/*++

    Format the variable number of arguments passed in based on the first
     argument (the format string), and display the message to the user.

    Uses GLOBAL hwndGlobalDlg

--*/
{
    static TCHAR buffer[MAX_PATH];

    va_list marker;
    va_start (marker,Format);
    wvsprintf (buffer,Format, marker);


    if (IsWindow(hwndGlobalDlg))
        SendMessage (hwndGlobalDlg,
                     WMAPP_ADDRESULT,
                     0,
                     (LPARAM) buffer);
    else
        MessageBox (NULL,
                    buffer,
                    SZ_APP_TITLE,
                    MB_OK );
    return;
}


void
_cdecl
catqLogCommentVariable(
    PTCH Format,
    ...
    )
/*++

    Format the variable number of arguments passed in based on the first
     argument (the format string), and call the routine to log the comment.

--*/
{
    static TCHAR buffer[MAX_PATH];

    va_list marker;
    va_start (marker,Format);
    wvsprintf (buffer,Format, marker);

    catqLogComment ( buffer );
    return;
}



int catqLogComment ( PTCHAR ptString )
/*++

    If the main window has been created already (i.e. hwnd is valid), then
     display the message (second input parameter) in the statusbar.
     If the main window does not exist, put up a message box.

    Uses GLOBAL hwndGlobalDlg

--*/
{
    if (IsWindow(hwndGlobalDlg))
        catqUpdateStatusComment(GetDlgItem(hwndGlobalDlg, DID_STATUSBAR),
                                ptString);
    else
        MessageBox (NULL,
                    ptString,
                    SZ_APP_TITLE,
                    MB_OK | MB_ICONSTOP);

    //
    // Also write to the debug output stream for the sake of anyone running
    //  under a debugger.  Or, notice that DBMON.EXE from the SDK will allow
    //  one to monitor output sent to OutputDebugString ().
    //

    OutputDebugString ( TEXT("catq: "));
    OutputDebugString ( ptString );
    OutputDebugString ( TEXT("\n"));

    return TRUE;
}
