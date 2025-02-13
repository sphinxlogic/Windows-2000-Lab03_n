//===========================================================================
//
// Module: WINAT.C
//
// Purpose: Main program for WINAT.exe.  This program is a GUI Windows
//          NT AT Command Scheduler.  The base code was taken from the
//          Windows NT AT command files.  I have preserved (mostly) the
//          same algorithms and data structures.
//
// Author: Kory Gill
//
// Date  : March 1993
//
// Copyright: Copyright 1993 - 1998 Microsoft Corporation
//
// Original banner from Windows NT at.c
//
//      /*++
//
//      Copyright 1987 - 1998  Microsoft Corporation
//
//      Module Name:
//
//          atcmd.c
//
//      Abstract:
//
//          Code for AT command, to be used with SCHEDULE service on
//          Windows NT.
//
//          The module was taken from LanManager\at.c and then modified
//          considerably to work with NT Schedule service.
//
//      Author:
//
//          Vladimir Z. Vulovic                     06 - November - 1992
//
//      Environment:
//
//          User Mode - Win32
//
//      Revision History:
//
//          06-Nov-1992
//              Created
//
//          20-Feb-1993
//              Get rid of hard coded strings and parse/print time according
//              to user profile
//
//      --*/
//
//===========================================================================


//===========================================================================
// includes
//===========================================================================

#include <windows.h>    // required for all Windows applications
#include "lmcons.h"     // LAN Manager defines
#include "MYnetmsg.h"   // APE2 defines
#include "lmerr.h"      // LAN Manager error messages
#include "lmat.h"       // AT Command prototypes
#include "lmapibuf.h"   // NetApiBufferFree
#include "WINAT.h"      // specific to this program
#include "listhapi.h"   // hotizontal listbox routines
#include <assert.h>     // assert
#include <stdio.h>      // assert


//===========================================================================
// global variables
//===========================================================================

ATTIME  AtTime[NUM_TIMES] =                 // time strings and ms since 12am
    {
	"00:00",  0, "00:30",  0, "01:00",  0, "01:30",  0,
	"02:00",  0, "02:30",  0, "03:00",  0, "03:30",  0,
	"04:00",  0, "04:30",  0, "05:00",  0, "05:30",  0,
	"06:00",  0, "06:30",  0, "07:00",  0, "07:30",  0,
	"08:00",  0, "08:30",  0, "09:00",  0, "09:30",  0,
	"10:00",  0, "10:30",  0, "11:00",  0, "11:30",  0,
	"12:00",  0, "12:30",  0, "13:00",  0, "13:30",  0,
	"14:00",  0, "14:30",  0, "15:00",  0, "15:30",  0,
	"16:00",  0, "16:30",  0, "17:00",  0, "17:30",  0,
	"18:00",  0, "18:30",  0, "19:00",  0, "19:30",  0,
	"20:00",  0, "20:30",  0, "21:00",  0, "21:30",  0,
	"22:00",  0, "22:30",  0, "23:00",  0, "23:30",  0
    };
AT_INFO GlobalAtInfo;                       // at information structure
BOOL    fTimer;                             // flag for timer events
DWORD   GlobalJobId;                        // job id as dword
DWORD   dwDisposition;                      // used for registry calls
DWORD   dwH = DWH;                          // height of main window
DWORD   dwTime;                             // time in milliseconds
DWORD   dwW = DWW;                          // width of main window
DWORD   dwX = DWX;                          // x location of main window
DWORD   dwY = DWY;                          // y location of main window
FARPROC lpAmPmProc;                                                     // subclass for add/change AmPm edit control
FARPROC lpAmPmDefProc;                                          // default handler for add/change AmPm edit control
FARPROC lpDownButtonProc;                                       // subclass for spin button
FARPROC lpDownButtonDefProc;                            // default handler for spin buttons
FARPROC lpHourProc;                                                     // subclass for add/change hour edit control
FARPROC lpHourDefProc;                                          // default handler for add/change hour edit control
FARPROC lpMinProc;                                                      // subclass for add/change min edit control
FARPROC lpMinDefProc;                                           // default handler for add/change min edit control
FARPROC lpUpButtonProc;                                         // subclass for spin button
FARPROC lpUpButtonDefProc;                                      // default handler for spin buttons
HANDLE  hInst;                              // instance
HCURSOR hCursorOld;                         // old cursor
HCURSOR hCursorWait;                        // hourglass cursor
#ifdef JAPAN
#else
HFONT   hFont;                              // handle to font
#endif
HANDLE  GlobalMessageHandle;                // handle to netmsg.dll
HKEY    hkHandle;                           // hangle to registry
HWND    hCurrentFocus = NULL;                           // handle to window with focus (used for hour/min/ampm spin buttons)
HWND    hGlobalhWnd;                        // handle to main window
HWND    hGlobalAddChg = NULL;               // handle to Add/Change dialog when active
HWND    hHour = NULL;                       // handle to hour
HWND    hMin = NULL;                        // handle to minutes
HWND    hAmPm = NULL;                       // handle to ampm
LOGFONT lf;                                 // font
PWSTR   GlobalComputerName;                 // currently selected comp. name
UCHAR   szRegistryPath[] = SZREGPATH;       // path to registry for stored info
UCHAR   szAppName[] = SZAPPTITLE;           // name of this application
UCHAR   szAtCommand[MAX_ATCMD_LEN+1];       // entire line in atcommand listbox
UCHAR   szCommandM[MAXCOMMANDLEN+1];        // multibyte command
UCHAR   szComputerM[MAXCOMPUTERNAMELEN+1];  // multibyte comp. name
UCHAR   szDateAbbr[4];                      // store day of month as string
#ifdef JAPAN
UCHAR   szDayAbbr[7][8]   =                 // abbreviations
    {
        "月曜日 ", "火曜日 ", "水曜日 ", "木曜日 ", "金曜日 ", "土曜日 ", "日曜日 "
    };
#else
UCHAR   szDayAbbr[7][4]   =                 // abbreviations
    {
	"M ", "T ", "W ", "Th ", "F ", "Sa ", "Su "
    };
#endif
UCHAR   szDefault[] = " ";                  // default char for wide conversion
UCHAR   szError[] = SZGENERROR;             // error message
UCHAR   szNoEntries[] = SZNOENTRIES;        // error message
#ifdef JAPAN
UCHAR   szTime[32];                         // store time as string
#else
UCHAR   szTime[8];                          // store time as string
#endif
UCHAR   szTitle[]   = SZAPPTITLE;           // title bar text
UCHAR   szWhenDay[MAXWHENDAYLEN + 1];       // used to build when/day string
#ifdef JAPAN
#else
UINT    uAmPmChars;                                                     // count of characters in add/change AmPm edit control
#endif
UINT    uHourChars;                                                     // count of characters in add/change hour edit control
UINT    uMinChars;                                                      // count of characters in add/change min edit control
UINT    uTimer;                             // handle of timer
WCHAR   szCommandW[MAXCOMMANDLEN+1];        // widechar command
WCHAR   szComputerW[MAXCOMPUTERNAMELEN+1];  // widechar comp. name

// jean-marc - start
UCHAR   gszCommandLine[MAXCOMPUTERNAMELEN+1]; // stores the passed in commandline
// jean-marc - end


//===========================================================================
// FUNCTION: AddChangeDlgProc()
//===========================================================================

BOOL APIENTRY
AddChangeDlgProc(
    HWND hWnd,         // window handle
    UINT message,      // type of message
    UINT uParam,       // additional information
    LONG lParam        // additional information
    )
{

    NET_API_STATUS  status;
    PAT_INFO        pAtInfo = NULL;
    SYSTEMTIME      SystemTime;
    UCHAR           szAtCommand[MAX_ATCMD_LEN];
    UCHAR           szTemp[30];
    char *          ptr;
    int             JobId;
    int             i;
    int             wmEvent;
    int             wmId;
    static BOOL     fChange;
    BOOL                        Translated;
    UINT                        Value;
    int                         Delta;

    // owner draw stuff
    static LPDRAWITEMSTRUCT  lpdis;          // Long Pointer to owner-draw struct
    LPMEASUREITEMSTRUCT      lpmis;          // Long Pointer to o-d measure struct
    static HBITMAP           hButtonUpDef,   // for button's regular state bm
			     hButtonUpDep,   // for button's pushed  state bm
			     hButtonDownDef, // for button's regular state bm
			     hButtonDownDep; // for button's pushed  state bm

    switch (message) {

		case WM_SPINBUTTON:

	    if ( (hCurrentFocus != hHour) && (hCurrentFocus != hMin) && (hCurrentFocus != hAmPm) ) {

		break;

	    }

		if ( lParam == UP ) {

			Delta = UP;

		} else {

				Delta = DOWN;

		}

		if ( uParam == (UINT)GetDlgItem( hWnd, IDC_HOUR ) ) {

				Value = GetDlgItemInt( hWnd, IDC_HOUR, &Translated, FALSE );

				if ( Translated == 0 ) {

					SetDlgItemInt( hWnd, IDC_HOUR, DEFAULT_HOUR, FALSE );

				} else {

					if ( ( Value >= 12 || Value < 1 ) && Delta == UP ) {

						Value = 1;

					} else if ( ( Value > 12 || Value <= 1 ) && Delta == DOWN ) {

						Value = 12;

					} else {

						if ( (Value == 11 && Delta == UP) || (Value == 12 && Delta == DOWN) ) {

							GetDlgItemText( hWnd, IDC_AMPM, (LPTSTR)&szTemp, sizeof(szTemp) );

#ifdef JAPAN
		        			if ( !strcmp(szTemp, "午前" ) ) {
		        				SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"午後" );
		        			} else {
								SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"午前" );
							}
#else
						if ( szTemp[0] == 'A' || szTemp[0] == 'a' ) {

							SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"PM" );

						} else {

								SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"AM" );

							}
#endif
						}

						Value += Delta;

					}

					SetDlgItemInt( hWnd, IDC_HOUR, Value, FALSE );

				}

				SendDlgItemMessage( hWnd, IDC_HOUR, EM_SETSEL, 0, -1 );
				//SetFocus( (HWND)uParam );

			} else if ( uParam == (UINT)GetDlgItem( hWnd, IDC_MIN ) ) {

		Value = GetDlgItemInt( hWnd, IDC_MIN, &Translated, FALSE );

				if ( Translated == 0 ) {

					SetDlgItemInt( hWnd, IDC_MIN, DEFAULT_MIN, FALSE );

				} else {

					if ( ( Value >= 59 || Value < 0 ) && Delta == UP ) {

						Value = 0;

					} else if ( ( Value > 59 || Value <= 0 ) && Delta == DOWN ) {

						Value = 59;

					} else {

						Value += Delta;

					}

				}

				if ( Value > 9 ) {

					SetDlgItemInt( hWnd, IDC_MIN, Value, FALSE );

				} else {

					szTemp[0] = '0';
					szTemp[1] = '0' + Value;
					szTemp[2] = '\0';

				SetDlgItemText( hWnd, IDC_MIN, szTemp );
			    }

				SendDlgItemMessage( hWnd, IDC_MIN, EM_SETSEL, 0, -1 );
				//SetFocus( (HWND)uParam );

		} else if ( uParam == (UINT)GetDlgItem( hWnd, IDC_AMPM ) ) {

			GetDlgItemText( hWnd, IDC_AMPM, (LPTSTR)&szTemp, sizeof(szTemp) );

#ifdef JAPAN
    			if ( !strcmp(szTemp, "午前") ) {
    				SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"午後" );
    			} else {
					SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"午前" );
				}
#else
			if ( szTemp[0] == 'A' || szTemp[0] == 'a' ) {

				SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"PM" );

			} else {

					SetDlgItemText( hWnd, IDC_AMPM,  (LPCTSTR)"AM" );

				}
#endif

		SendDlgItemMessage( hWnd, IDC_AMPM, EM_SETSEL, 0, -1 );
			//SetFocus( (HWND)uParam );

			}

		break;

	case WM_MEASUREITEM:

	    lpmis = (LPMEASUREITEMSTRUCT)lParam; // for convenience
	    lpmis->itemWidth  = 7;
	    lpmis->itemHeight = 7;

	    break;

	case WM_DRAWITEM:

	    lpdis = (LPDRAWITEMSTRUCT)lParam;    // for convenience

	    switch (lpdis->itemAction) {

		case ODA_DRAWENTIRE:
		    if ( lpdis->CtlID == IDD_DOWNBUT ) {
			DrawBitmap(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hButtonDownDef, SRCCOPY);
		    } else {
			DrawBitmap(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hButtonUpDef, SRCCOPY);
		    }

		    break;

		case ODA_SELECT:
		    // handle select state -- text is right & down 2 pixels
		    // also handle focus state since it's associated
		    if (lpdis->itemState & ODS_SELECTED) {
			if ( lpdis->CtlID == IDD_DOWNBUT ) {
				DrawBitmap(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hButtonDownDep, SRCCOPY);
			    } else {
				DrawBitmap(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hButtonUpDep, SRCCOPY);
			    }
		    }
		    else {
			if ( lpdis->CtlID == IDD_DOWNBUT ) {
				DrawBitmap(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hButtonDownDef, SRCCOPY);
			    } else {
				DrawBitmap(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top, hButtonUpDef, SRCCOPY);
			    }

				if ( hCurrentFocus != NULL ) {

					SetFocus( hCurrentFocus );

				}

		    }
		    break;

		case ODA_FOCUS:
		    if (lpdis->itemState & ODS_FOCUS) {

			    break;
			}

			break;

		default:

		    break;

	    }  //itemAction

	    break;

	case WM_INITDIALOG:

			/* load bitmaps and get area of text rectangle for owner-draw button */

	    hButtonUpDef = LoadBitmap(hInst,"BUTTONUPDEF"); // regular state
	    hButtonUpDep   = LoadBitmap(hInst,"BUTTONUPDEP");   // pushed  state


	    hButtonDownDef = LoadBitmap(hInst,"BUTTONDOWNDEF"); // regular state
	    hButtonDownDep = LoadBitmap(hInst,"BUTTONDOWNDEP");   // pushed  state

	    hCurrentFocus = NULL;
	    hHour = GetDlgItem( hWnd, IDC_HOUR );
	    hMin  = GetDlgItem( hWnd, IDC_MIN );
	    hAmPm = GetDlgItem( hWnd, IDC_AMPM );

#ifdef JAPAN
#else
			SendDlgItemMessage( hWnd, IDC_NEWCOMMAND, WM_SETFONT, (WPARAM)hFont, 1L );
			SendDlgItemMessage( hWnd, IDC_DAYS, WM_SETFONT, (WPARAM)hFont, 1L );
			SendDlgItemMessage( hWnd, IDC_HOUR, WM_SETFONT, (WPARAM)hFont, 1L );
			SendDlgItemMessage( hWnd, IDC_MIN, WM_SETFONT,  (WPARAM)hFont, 1L );
			SendDlgItemMessage( hWnd, IDC_AMPM, WM_SETFONT, (WPARAM)hFont, 1L );
#endif

	    // fill in Days
#ifdef JAPAN
            SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"月曜日");
            SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"火曜日");
            SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"水曜日");
            SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"木曜日");
            SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"金曜日");
            SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"土曜日");
            SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"日曜日");
#else
	    SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"Monday");
	    SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"Tuesday");
	    SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"Wednesday");
	    SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"Thursday");
	    SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"Friday");
	    SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"Saturday");
	    SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)"Sunday");
#endif

	    for ( i=1; i<=9; ++i ) {

		UCHAR szDateAbbr[2];

		szDateAbbr[0] = i + '0';
		szDateAbbr[1] = '\0';

		SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)szDateAbbr );

	    }

		for ( i=10; i<=31; ++i ) {

		UCHAR szDateAbbr[3];

		szDateAbbr[0] = i/10 + '0';
		szDateAbbr[1] = i%10 + '0';
		szDateAbbr[2] = '\0';

		SendDlgItemMessage(hWnd, IDC_DAYS, LB_ADDSTRING, 0, (LPARAM)szDateAbbr );

	    }

		if ( lParam == IDC_ADD ) {

		    SendDlgItemMessage(hWnd, IDC_DAYS, LB_SETCURSEL, 0, 0);

		    // fill in Time

			SetDlgItemInt( hWnd, IDC_HOUR, DEFAULT_HOUR, FALSE );

			if ( DEFAULT_MIN > 9 ) {

					SetDlgItemInt( hWnd, IDC_MIN, DEFAULT_MIN, FALSE );

				} else {

					szTemp[0] = '0';
					szTemp[1] = '0' + DEFAULT_MIN;
					szTemp[2] = '\0';

				SetDlgItemText( hWnd, IDC_MIN, szTemp );
			    }

			SetDlgItemText( hWnd, IDC_AMPM, (LPCTSTR)DEFAULT_AMPM );

		    // set the Every radio button

		    SendDlgItemMessage(hWnd, IDC_EVERY, BM_SETCHECK, TRUE, 0);

		    fChange = FALSE;

#ifdef JAPAN
        		lstrcpy( szTemp, "ｺﾏﾝﾄﾞ追加" );
#else
			lstrcpy( szTemp, "Add Command" );
#endif

		SetWindowText( hWnd, szTemp );

		} else {

		    fChange = TRUE;

#ifdef JAPAN
				lstrcpy( szTemp, "ｺﾏﾝﾄﾞ変更" );
#else
				lstrcpy( szTemp, "Change Command" );
#endif

				SetWindowText( hWnd, szTemp );

				// fill in current command info

				SendDlgItemMessage(
			hGlobalhWnd,
			IDC_ATCOMMANDS,
			LB_GETTEXT,
			SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_GETCURSEL, 0, 0 ),
			(LPARAM)szAtCommand
			);

			// get job id

		    JobId = 0;

		    ptr   = szAtCommand;

		    while( *ptr >= '0' && *ptr <= '9' ) {

			JobId *= 10;
			JobId += (UINT)*ptr - '0';

			ptr++;

		    }

		    // get info on this job

		    status = NetScheduleJobGetInfo(
		    GlobalComputerName,
			JobId,
			(LPBYTE *)&pAtInfo
			);

		    if ( status != NERR_Success ) {

			//MessageBox( hWnd, "Problem getting Job Info.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

			MessagePrint( status );

			EndDialog( hWnd, 0 );

		    }

		    // fill in command

		    WideCharToMultiByte(
			(UINT)CP_ACP,
			(DWORD)0,
			(LPWSTR)pAtInfo->Command,
			MAX_ATCMD_LEN,
		    (LPSTR)szCommandM,
		    MAX_ATCMD_LEN,
		    (LPSTR)NULL, (LPBOOL)NULL
		    );

		SetDlgItemText( hWnd, IDC_NEWCOMMAND, szCommandM );

		// set days this command runs

		if ( pAtInfo->DaysOfWeek != 0) {

			for ( i=0; i<7; ++i ) {

				if ( ( pAtInfo->DaysOfWeek & (1 << i) ) != 0 ) {

					SendDlgItemMessage( hWnd, IDC_DAYS, LB_SETSEL, TRUE, i );

				}

			}

		}

		if ( pAtInfo->DaysOfMonth != 0) {

			for ( i=0; i<31; ++i ) {

				if ( ( pAtInfo->DaysOfMonth & (1L << i) ) != 0 ) {

					SendDlgItemMessage( hWnd, IDC_DAYS, LB_SETSEL, TRUE, i+7 );

				}

			}

		}

		// fill in every/today/tomorrow/next flag

		if ( pAtInfo->Flags & JOB_RUN_PERIODICALLY ) {

			SendDlgItemMessage( hWnd, IDC_EVERY, BM_SETCHECK, TRUE, 0 );

			SendMessage( hWnd, WM_COMMAND, IDC_EVERY, 0 );

		} else if ( (pAtInfo->DaysOfWeek != 0) || (pAtInfo->DaysOfMonth != 0) ) {

			SendDlgItemMessage( hWnd, IDC_NEXT, BM_SETCHECK, TRUE, 0 );

			SendMessage( hWnd, WM_COMMAND, IDC_NEXT, 0 );

				} else if ( pAtInfo->Flags & JOB_RUNS_TODAY ) {

			SendDlgItemMessage( hWnd, IDC_TODAY, BM_SETCHECK, TRUE, 0 );

			SendMessage( hWnd, WM_COMMAND, IDC_TODAY, 0 );

				} else {

			SendDlgItemMessage( hWnd, IDC_TOMORROW, BM_SETCHECK, TRUE, 0 );

			SendMessage( hWnd, WM_COMMAND, IDC_TOMORROW, 0 );

				}

		    // set time for this command

		{

		    UINT  uJobTime = (UINT)(pAtInfo->JobTime / 1000 / 60 / 60);
			UINT  uAM = TRUE;

			if ( uJobTime == 0 ) {

				uJobTime = 12;

			} else if ( uJobTime == 12 ) {

			    uAM = FALSE;

			} else if ( uJobTime > 12 ) {

			    uJobTime -= 12;

			    uAM = FALSE;

				}

			SetDlgItemInt( hWnd, IDC_HOUR, uJobTime, FALSE );

#ifdef JAPAN
	               	uAM ? SetDlgItemText( hWnd, IDC_AMPM, "午前" ) : SetDlgItemText( hWnd, IDC_AMPM, "午後" );
#else
			uAM ? SetDlgItemText( hWnd, IDC_AMPM, "AM" ) : SetDlgItemText( hWnd, IDC_AMPM, "PM" );
#endif

					if ( (UINT)(pAtInfo->JobTime / 1000 / 60 % 60) > 9 ) {

						SetDlgItemInt( hWnd, IDC_MIN, (UINT)(pAtInfo->JobTime / 1000 / 60 % 60), FALSE );

					} else {

						szTemp[0] = '0';
						szTemp[1] = '0' + (UINT)(pAtInfo->JobTime / 1000 / 60 % 60);
						szTemp[2] = '\0';

					SetDlgItemText( hWnd, IDC_MIN, szTemp );
				    }

			    }

		// free buffer

				NetApiBufferFree( (LPVOID)pAtInfo );

		}

	    // set up subclass functions

			lpAmPmProc = MakeProcInstance( (FARPROC)AmPmProc, hInst );
			lpAmPmDefProc = (FARPROC) SetWindowLong( GetDlgItem( hWnd, IDC_AMPM ), GWL_WNDPROC, (LONG)lpAmPmProc );
			lpDownButtonProc = MakeProcInstance( (FARPROC)DownButtonProc, hInst );
			lpDownButtonDefProc = (FARPROC) SetWindowLong( GetDlgItem( hWnd, IDD_DOWNBUT ), GWL_WNDPROC, (LONG)lpDownButtonProc );
			lpUpButtonProc = MakeProcInstance( (FARPROC)UpButtonProc, hInst );
			lpUpButtonDefProc = (FARPROC) SetWindowLong( GetDlgItem( hWnd, IDD_UPBUT ), GWL_WNDPROC, (LONG)lpUpButtonProc );
			lpHourProc = MakeProcInstance( (FARPROC)HourProc, hInst );
			lpHourDefProc = (FARPROC) SetWindowLong( GetDlgItem( hWnd, IDC_HOUR ), GWL_WNDPROC, (LONG)lpHourProc );
			lpMinProc = MakeProcInstance( (FARPROC)MinProc, hInst );
			lpMinDefProc = (FARPROC) SetWindowLong( GetDlgItem( hWnd, IDC_MIN ), GWL_WNDPROC, (LONG)lpMinProc );

			// will default to two chars

			uHourChars = 2;
			uMinChars = 2;


			hGlobalAddChg = hWnd;

		break;

	case WM_COMMAND:    // message: command from application menu

			wmId    = LOWORD(uParam);
			wmEvent = HIWORD(uParam);

			switch (wmId) {

		case IDC_TODAY:
		case IDC_TOMORROW:

		    GetLocalTime( &SystemTime );

		    if ( SystemTime.wDayOfWeek == 0 ) {

			SystemTime.wDayOfWeek = 7;

		    }

			for( i=0; i<NUMDAYITEMS; ++i ) {

				SendDlgItemMessage( hWnd, IDC_DAYS, LB_SETSEL, FALSE, i );

			}

			SendDlgItemMessage(
				hWnd,
				IDC_DAYS,
				LB_SETSEL,
				TRUE,
				wmId == IDC_TOMORROW ? SystemTime.wDayOfWeek : SystemTime.wDayOfWeek - 1 );

		    EnableWindow(GetDlgItem(hWnd, IDC_DAYS), FALSE);

		    break;

		case IDC_EVERY:

		    EnableWindow(GetDlgItem(hWnd, IDC_DAYS), TRUE);

		    break;

		case IDC_NEXT:

		    EnableWindow(GetDlgItem(hWnd, IDC_DAYS), TRUE);

		    break;

				case IDCANCEL:

				    hCurrentFocus = NULL;
				    DeleteObject( hButtonUpDef );
				    DeleteObject( hButtonUpDep );
				    DeleteObject( hButtonDownDep );
				    DeleteObject( hButtonDownDef );

					EndDialog( hWnd, IDCANCEL );

					break;

		case IDOK:

		    if ( ValidateAddChangeArguments( hWnd ) == TRUE ) {

			if( fChange == TRUE) {

				status = JobDel( DEL_ID_CHANGE, hGlobalhWnd);

			}

			status = JobAdd();

			    if ( status == NERR_Success ) {

				SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_BOTTOM );

							hCurrentFocus = NULL;
							DeleteObject( hButtonUpDef );
						    DeleteObject( hButtonUpDep );
						    DeleteObject( hButtonDownDep );
						    DeleteObject( hButtonDownDef );

						    EndDialog( hWnd, IDOK );

			    } else {

				//MessageBox( hWnd, "Problem adding command.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

				MessagePrint( status );

			    }

		    }

		    break;

		case IDC_ADDCHANGEHELP:

#ifdef KKBUGFIX
		    if (!WinHelp (hWnd, "WINAT.HLP", HELP_CONTENTS,0L)) {
#else
		    if (!WinHelp (hWnd, "WINAT.HLP", HELP_KEY,(DWORD)(LPSTR)"CONTENTS")) {
#endif
						MessageBox (GetFocus(),
#ifdef JAPAN
							"ヘルプを起動できません",
#else
							"Unable to activate help",
#endif
							SZWINDOWTITLE, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
		    }

		    break;

	    }

	    break;

    }

    return (0);

}



//===========================================================================
// FUNCTION: AmPmProc()
//===========================================================================
LRESULT APIENTRY AmPmProc( HWND hWnd, UINT message, UINT uParam, LONG lParam )
{
// jean-marc - start
    // NOTE: the dialog resource for this field includes the ES_READONLY flag
    // to prevent the delete key from working, otherwise the delete key was
    // going through by somehow by-passing the WM_CHAR case.

    switch (message)
    {
      case WM_SETFOCUS:
	hCurrentFocus = hWnd;
	break;

      case WM_CHAR:
      {
	switch(uParam)
	{
	  case 'A':
	  case 'a':
#ifdef JAPAN
	    SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)"午前" );
#else
	    SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"AM");
#endif
	    return 0;

	  case 'P':
	  case 'p':
#ifdef JAPAN
	    SendMessage( hWnd, WM_SETTEXT, 0, (LPARAM)"午後" );
#else
	    SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"PM");
#endif
	    return 0;

	  default:
	    MessageBeep(MB_OK);
	    return 0;
	}
      }
      return 0;
    }

    return CallWindowProc( (WNDPROC)lpAmPmDefProc, hWnd, message, uParam, lParam ) ;
// jean-marc - end
}



//===========================================================================
// FUNCTION: AreYouSure()
//
// Arguments:
//
//   Uses globals.
//
// Return Value:
//
//   ID_YES if the yes button pressed
//   ID_NO  if the  no button pressed
//
//===========================================================================
UINT
AreYouSure(
    HWND hWnd
    )
{

    return ( MessageBox(
		 hWnd,
#ifdef JAPAN
                 "選択されたコマンドを削除しますか？",
                 "削除確認",
#else
		 "Remove the selected command?",
		 "Confirm Remove",
#endif
		 MB_YESNO | MB_ICONEXCLAMATION
		 )
	   );

}


//===========================================================================
// FUNCTION: UpButtonProc()
//===========================================================================
LRESULT APIENTRY UpButtonProc( HWND hWnd, UINT message, UINT uParam, LONG lParam )
{
// jean-marc - start
#define TIME_DELAY 150
#define TIME_DELAY 150

  DWORD dwEventTime;

  switch (message)
  {
    case WM_LBUTTONDOWN:
      if (hCurrentFocus == hHour || hCurrentFocus == hMin || hCurrentFocus == hAmPm)
      {
	dwEventTime = GetTickCount() - TIME_DELAY;
	do
	{
	  if (dwEventTime + TIME_DELAY > GetTickCount())
	    continue;
	  SendMessage(hGlobalAddChg, WM_SPINBUTTON, (UINT)hCurrentFocus, (LONG)UP);
	  InvalidateRect(hCurrentFocus, NULL, TRUE);
	  UpdateWindow(hCurrentFocus);
	  dwEventTime = GetTickCount();
	}
	while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
      }
      break;
  }

  return CallWindowProc((WNDPROC)lpUpButtonDefProc, hWnd, message, uParam, lParam);
// jean-marc - end
}


//===========================================================================
// FUNCTION: DownButtonProc()
//===========================================================================
LRESULT APIENTRY DownButtonProc( HWND hWnd, UINT message, UINT uParam, LONG lParam )
{
// jean-marc - start
#define TIME_DELAY 150

  DWORD dwEventTime;

  switch (message)
  {
    case WM_LBUTTONDOWN:
      if (hCurrentFocus == hHour || hCurrentFocus == hMin || hCurrentFocus == hAmPm)
      {
	dwEventTime = GetTickCount() - TIME_DELAY;
	do
	{
	  if (dwEventTime + TIME_DELAY > GetTickCount())
	    continue;
	  SendMessage(hGlobalAddChg, WM_SPINBUTTON, (UINT)hCurrentFocus, (LONG)DOWN);
	  InvalidateRect(hCurrentFocus, NULL, TRUE);
	  UpdateWindow(hCurrentFocus);
	  dwEventTime = GetTickCount();
	}
	while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
      }
      break;
  }

  return CallWindowProc((WNDPROC)lpDownButtonDefProc, hWnd, message, uParam, lParam);
// jean-marc - end
}



/****************************************************************************

    FUNCTION: DrawBitmap

    PURPOSE:  Draw default or pushed button bitmap

****************************************************************************/

void DrawBitmap(
	HDC     hDC,
	LONG    xStart,
	LONG    yStart,
	HBITMAP hBitmap,
	DWORD   rop)
{
  BITMAP        bm;
  HDC           hMemDC;
  POINT                 pt;

  hMemDC = CreateCompatibleDC (hDC);
  SelectObject (hMemDC, hBitmap);
  GetObject (hBitmap, sizeof (BITMAP), (LPSTR) &bm);
  pt.x = bm.bmWidth;
  pt.y = bm.bmHeight;
  BitBlt (hDC, xStart, yStart, pt.x, pt.y, hMemDC, 0, 0, rop);
  DeleteDC (hMemDC);
}



//===========================================================================
// FUNCTION: HourProc()
//===========================================================================
LRESULT APIENTRY HourProc( HWND hWnd, UINT message, UINT uParam, LONG lParam )
{
    UINT  uCurVal;
    UCHAR szCurVal[3];

    switch ( message ) {

	    case WM_COPY:
	    case WM_PASTE:
	    case WM_CUT:

			// cut and paste dont seem to work...

		break;

// jean-marc - start
      case WM_SETFOCUS:
	hCurrentFocus = hWnd;
	break;
// jean-marc - end

	case WM_CHAR:

			if ( uParam == VK_BACK ) {

				if ( uHourChars > 0 ) {

					--uHourChars;

				}

				return CallWindowProc( (WNDPROC)lpHourDefProc, hWnd, message, uParam, lParam ) ;

			} else {

				uHourChars = (UINT) SendMessage( hWnd, WM_GETTEXT, 2, (LPARAM)szCurVal );

				if ( uHourChars == 0 ) {

				uCurVal = 0;

			    } else if ( uHourChars == 1 ) {

				uCurVal = szCurVal[0] - '0';

			    } else if ( uHourChars == 2 ) {

				uCurVal  = szCurVal[0] - '0';
				uCurVal *= 10;
				uCurVal  = szCurVal[1] - '0';

			    } else if ( uHourChars > 2 ) {

				uHourChars = 0;

				SendMessage( hWnd, WM_SETTEXT, 0, (LPARAM)"" );

				return( 0 );

			    }

			}

			if ( ( uParam == ' ' )                                     ||  // space
			     ( uParam < '0' || uParam > '9')                       ||  // not a number
			     ( uParam == '0' && uCurVal == 0 )                     ||  // trying to enter 0 as first char
			     ( (uParam > '2' && uCurVal >= 1) && uHourChars >= 1)  ||  // greater than 12
			     ( uParam <= '2' && uCurVal > 1)                           // greater than 12
			   ) {

				 MessageBeep( MB_OK );

				 return( 0 );

			} else if ( uHourChars < 2 ) {

				++uHourChars;

			} else {

		    MessageBeep( MB_OK );

			    return( 0 );

			}

		break;

	} // switch

	return CallWindowProc( (WNDPROC)lpHourDefProc, hWnd, message, uParam, lParam ) ;

}



//===========================================================================
// FUNCTION: JobAdd()
//
// Routine Description:
//
//     Adds a new item to schedule.
//
// Arguments:
//
//     None.  Uses globals.
//
// Return Value:
//
//     NET_API_STATUS return value of remote api call
//
//===========================================================================
NET_API_STATUS
JobAdd(
    VOID
    )
{

    NET_API_STATUS          status;

    status = NetScheduleJobAdd(
		GlobalComputerName,
		(LPBYTE)&GlobalAtInfo,
		&GlobalJobId
		);

    if ( status != NERR_Success ) {

	/*MessageBox(
	    hGlobalhWnd,
	    ( status == NERR_ServiceNotInstalled ? "The service has not been started" : "Message could not be added." ),
	    SZWINDOWTITLE,
	    MB_OK | MB_ICONEXCLAMATION
	    );
	*/

	MessagePrint( status );
    }

    return ( status );

}



//===========================================================================
//
// FUNCTION: JobDel()
//
//
// Routine Description:
//
//     This does all of the processing necessary to dump out the entire
//     schedule file.  It loops through on each record and formats its
//     information for printing and then goes to the next.
//
// Arguments:
//
//     DEL_ALL if to delete all jobs, DEL_ID otherwise.
//     Uses globals.
//
// Return Value:
//
//     ERROR_SUCCESS                       if everything enumerated OK
//     error returned by remote api        otherwise
//
//===========================================================================
NET_API_STATUS
JobDel(
    UINT Method,
    HWND hWnd
    )
{

    DWORD                       dwSelection;
    NET_API_STATUS  status;
    UCHAR           szAtCommand[MAX_ATCMD_LEN];
    UINT            JobId;
    UINT                        uSelection;
    UINT                        uCount;
    char *          ptr;


    if ( Method != DEL_ID_CHANGE ) {

	if ( AreYouSure(hWnd) == IDNO ) {

		return( ERROR_SUCCESS );

	}

    }

    switch( Method ) {

	case DEL_ALL:

	    status = NetScheduleJobDel(
		    GlobalComputerName,
		    0,
		    (DWORD)-1
		    );

	    if ( status == NERR_Success ) {

		SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_NONE );
		break;

	    }

	    break;

	case DEL_ID:
	case DEL_ID_CHANGE:

	    // compute id

	    uSelection = SendDlgItemMessage( hWnd, IDC_ATCOMMANDS, LB_GETCURSEL, 0, 0 );
	    uCount     = SendDlgItemMessage( hWnd, IDC_ATCOMMANDS, LB_GETCOUNT,  0, 0 );

	    SendDlgItemMessage(
		hWnd,
		IDC_ATCOMMANDS,
		LB_GETTEXT,
		uSelection,
		(LPARAM)szAtCommand
		);

	    JobId = 0;
	    ptr   = szAtCommand;

	    while( *ptr >= '0' && *ptr <= '9' ) {

		JobId *= 10;
		JobId += (UINT)*ptr - '0';

		ptr++;

	    }

	    status = NetScheduleJobDel(
		    GlobalComputerName,
		    JobId,
		    JobId
		    );

	    if ( status != NERR_Success) {

		//MessageBox( hWnd, "Problem deleteing a job.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

		MessagePrint( status );

		break;

	    }

	    if ( uCount == 1 ) {

				// this was the only job

		SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_NONE );

	    } else if ( uSelection == 0 ) {

		// the first/top job was selected and there is more than 1 job

		SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_TOP );

	    } else if ( ( uCount - 1 ) == uSelection ) {

		// the last/bottom job was selected

		SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_BOTTOM );

	    } else {

		// the 2nd thru last-1 job was selected

		dwSelection  = 0;
		dwSelection |= uSelection << 16;
		dwSelection |= SCS_SELINHIGHWORD;

		SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)dwSelection );

	    }

	    break;

    }

    return( status );

}



//===========================================================================
//
// FUNCTION: JobEnum()
//
//
// Routine Description:
//
//     This does all of the processing necessary to dump out the entire
//     schedule file.  It loops through on each record and formats its
//     information for printing and then goes to the next.
//
// Arguments:
//
//     None.  Uses globals.
//
// Return Value:
//
//     ERROR_SUCCESS                       if everything enumerated OK
//     error returned by remote api        otherwise
//
//===========================================================================
NET_API_STATUS
JobEnum(
    DWORD SetCurrentSelection
    )
{

    BOOL            fFlag;
    BOOL            first = TRUE;
    DWORD           EntriesRead;
    DWORD           ResumeJobId = 0;
    DWORD           TotalEntries;
    LPVOID          EnumBuffer = NULL;
    NET_API_STATUS  status = NERR_Success;
    PAT_ENUM        pAtEnum;
    //UCHAR           szTemp[80];
    static UINT         uSelection;
    static UINT         uTopIndex;
    int             i;

    // initialize to current selection

	uSelection = SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_GETCURSEL,   0, 0 );
	uTopIndex  = SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_GETTOPINDEX, 0, 0 );

	if ( uSelection == LB_ERR ) {

		uSelection = 0;

	}

    for ( ; ;) {

	status = NetScheduleJobEnum(
		GlobalComputerName,
		(LPBYTE *)&EnumBuffer,
		(DWORD)-1,
		&EntriesRead,
		&TotalEntries,
		&ResumeJobId
		);

	if ( status != ERROR_SUCCESS  &&  status != ERROR_MORE_DATA) {

	    //
	    // not needded since both the if/else(MessagePrint) will set this text now
	    //
	    //SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_RESETCONTENT, 0, 0 );
	    //
	    //SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)szError );

	    EnableWindow( GetDlgItem( hGlobalhWnd, IDC_ADD    ), FALSE );
	    EnableWindow( GetDlgItem( hGlobalhWnd, IDC_CHANGE ), FALSE );
		EnableWindow( GetDlgItem( hGlobalhWnd, IDC_REMOVE ), FALSE );

		if ( status == NERR_ServiceNotInstalled ) {

		SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_RESETCONTENT, 0, 0 );

#ifdef JAPAN
                SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)"ｽｹｼﾞｭｰﾙ ｻｰﾋﾞｽ 未起動" );

#else
		SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)"Schedule service not started." );
#endif

			if ( ServiceNotStartedHandler() == FALSE ) {

				return( status );

			} else {

			    continue;

			}

		} else  {

		/*wsprintf( szTemp, "The computer %s cannot be found.\nError %u.", &szComputerM[2], status );

		    MessageBox(
			 hGlobalhWnd,
					szTemp,
			SZWINDOWTITLE,
			MB_OK | MB_ICONEXCLAMATION
			);
		    */

				MessagePrint( status );

		    return( status );

		}

	}

	assert( status == ERROR_SUCCESS ? TotalEntries == EntriesRead : TotalEntries > EntriesRead );

	if ( TotalEntries == 0) {

	    break;  //  no items found

	}

	if ( first == TRUE) {

	    ResetListboxExtents( GetDlgItem( hGlobalhWnd, IDC_ATCOMMANDS ) );
	    SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_RESETCONTENT, 0, 0 );

	    first = FALSE;

	}

	for ( pAtEnum = EnumBuffer;  EntriesRead-- > 0;  pAtEnum++) {

	    // not sure what this is doing...

	    /*
	    if ( pAtEnum->Flags & JOB_EXEC_ERROR) {

		if ( MessageGet( APE2_GEN_ERROR, &smallBuffer, 0 ) == 0) {

		    // error reported already
		    exit( -1);

		}

		printf( DUMP_FMT1, smallBuffer );
		LocalFree( smallBuffer );

	    } else {

		printf( DUMP_FMT1, L"");

	    }
	    */

	    // replate with...

	    if ( pAtEnum->Flags & JOB_EXEC_ERROR) {

		MessagePrint( APE2_GEN_ERROR );

	    }

	    szWhenDay[0] = '\0';

	    if ( pAtEnum->Flags & JOB_RUN_PERIODICALLY ) {

#ifdef JAPAN
                lstrcat( szWhenDay, "毎 " );
#else
		lstrcat( szWhenDay, "Each " );
#endif

	    } else if ( pAtEnum->DaysOfWeek != 0 || pAtEnum->DaysOfMonth != 0 ) {

#ifdef JAPAN
                lstrcat( szWhenDay, "次の " );
#else
		lstrcat( szWhenDay, "Next " );
#endif

	    } else if ( pAtEnum->Flags & JOB_RUNS_TODAY ) {

#ifdef JAPAN
                lstrcat( szWhenDay, "今日 " );
#else
		lstrcat( szWhenDay, "Today " );
#endif

	    } else {

#ifdef JAPAN
                lstrcat( szWhenDay, "明日 " );
#else
		lstrcat( szWhenDay, "Tomorrow " );
#endif

	    }

	    if ( pAtEnum->DaysOfWeek != 0 ) {

		for ( i=0; i<7; ++i ) {

		    if ( ( pAtEnum->DaysOfWeek & ( 1 << i ) ) != 0 ) {

			lstrcat( szWhenDay, szDayAbbr[i] );

		    }

		}

	    }

	    if ( pAtEnum->DaysOfMonth != 0 ) {

		for ( i=0; i<31; ++i ) {

		    if ( ( pAtEnum->DaysOfMonth & ( 1L << i ) ) != 0 ) {

			wsprintf( szDateAbbr, "%d ", i+1 );

			lstrcat( szWhenDay, szDateAbbr );
#ifdef JAPAN
                        lstrcat( szWhenDay, "日" );
#endif
		    }

		}

	    }


	    dwTime     = pAtEnum->JobTime / 1000 / 60;       // total minutes

	    szTime[0]  = (UCHAR)( dwTime / 600 ) + '0';      // 10s of hours
	    dwTime    %= 600;

	    szTime[1]  = (UCHAR)( dwTime / 60 )  + '0';      // 1s of hours
	    dwTime    %= 60;

	    szTime[2]  = ':';

	    szTime[3]  = (UCHAR)( dwTime / 10 )  + '0';      // 10s of minutes
	    dwTime    %= 10;

	    szTime[4]  = (UCHAR)( dwTime )       + '0';      // 1s of minutes

	    szTime[5]  = '\0';

	    // convert this 24-hour time to AM/PM form

	    szTime[5] = 'A';
	    szTime[6] = 'M';
	    szTime[7] = '\0';

			// if it is past 1000 but before 2000 (24-hour time)

	    if ( szTime[0] == '1' ) {

		// if it is past 1100

			if ( szTime[1] >= '2' ) {

				szTime[5] = 'P';

			}

		    if( szTime [1] > '2' ) {

			szTime[0] -= 1;
			szTime[1] -= 2;

		    }

	    } else if ( szTime[0] == '2' ) {

		// it is 2000 or later

		szTime[5] = 'P';

		    // if it is 2200 or later

		    if( szTime [1] >= '2' ) {

			szTime[0] -= 1;
			szTime[1] -= 2;

		    } else {

			szTime[0] -= 2;
			szTime[1] += 8;

		    }

		}

			if ( szTime[0] == '0' ) {

				if ( szTime[1] == '0' ) {

					// 12 am or pm

					szTime[0] = '1';
					szTime[1] = '2';

				} else {

					szTime[0] = ' ';

				}

		}

#ifdef JAPAN
            {
                char szBuf[sizeof(szTime)];

                strcpy(szBuf, szTime);
                strcpy(szTime, szBuf[5] == 'A' ? "午前 " : "午後 ");
                szBuf[5] = '\0';
                strcat(szTime, szBuf);
            }
#endif

	    WideCharToMultiByte(
		CP_ACP,
		0,
		pAtEnum->Command,
		-1,
		szCommandM,
		MAXCOMMANDLEN,
		szDefault,
		&fFlag
		);

	    wsprintf( szAtCommand, "%d\t", pAtEnum->JobId );
	    lstrcat( szAtCommand, szWhenDay  );
	    lstrcat( szAtCommand, "\t"       );
	    lstrcat( szAtCommand, szTime     );
	    lstrcat( szAtCommand, "\t"       );
	    lstrcat( szAtCommand, szCommandM );

	    WAddExtentEntry( GetDlgItem( hGlobalhWnd, IDC_ATCOMMANDS ), szAtCommand );
	    SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)szAtCommand );

	}

	if ( EnumBuffer != NULL ) {

	    (VOID)NetApiBufferFree( (LPVOID)EnumBuffer );
	    EnumBuffer = NULL;

	}

	if ( status == ERROR_SUCCESS ) {

	    break;  //  we have read & displayed all the items

	}

    } // for

    if ( first == TRUE) {

	ResetListboxExtents( GetDlgItem( hGlobalhWnd, IDC_ATCOMMANDS ) );
	SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_RESETCONTENT, 0, 0 );
	WAddExtentEntry( GetDlgItem( hGlobalhWnd, IDC_ATCOMMANDS ), szNoEntries );
	SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)szNoEntries );

	EnableWindow( GetDlgItem( hGlobalhWnd, IDC_ADD ), TRUE );
	EnableWindow( GetDlgItem( hGlobalhWnd, IDC_CHANGE ), FALSE );
	EnableWindow( GetDlgItem( hGlobalhWnd, IDC_REMOVE ), FALSE );

    } else {

	switch ( LOWORD( SetCurrentSelection ) ) {

		case SCS_BOTTOM:

			uSelection = SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_GETCOUNT, 0, 0 ) - 1;

			SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_SETCURSEL,  uSelection,     0 );

			break;

		    case SCS_NOCHANGE:

				// uSelection has already been set

		    SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_SETCURSEL,  uSelection, 0 );

		    break;

		case SCS_TOP:

			uSelection = 0;

				SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_SETCURSEL,  uSelection,     0 );

				break;

		case SCS_SELINHIGHWORD:

			    uSelection = HIWORD( SetCurrentSelection );

				SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_SETCURSEL,  uSelection,     0 );

				break;

			case SCS_NONE:
			default:

				break;

	}

	SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_SETTOPINDEX,  uTopIndex,    0 );

	EnableWindow( GetDlgItem( hGlobalhWnd, IDC_ADD ), TRUE );
	EnableWindow( GetDlgItem( hGlobalhWnd, IDC_CHANGE ), TRUE );
	EnableWindow( GetDlgItem( hGlobalhWnd, IDC_REMOVE ), TRUE );

    }

    return( ERROR_SUCCESS );

}




//===========================================================================
// FUNCTION: MessagePrint()
//===========================================================================
DWORD
MessagePrint(
    IN      DWORD       MessageId,
    ...
    )
/*++

Routine Description:

    Finds the unicode message corresponding to the supplied message id,
    merges it with caller supplied string(s), and prints the resulting
    string.

Arguments:

    MessageId       -   message id

Return Value:

    Count of characters, not counting the terminating null character,
    printed by this routine.  Zero return value indicates failure.

--*/
{
    va_list             arglist;
    UCHAR *             buffer = NULL;
    UCHAR *                     ptr;
    DWORD               length;
    LPVOID              lpSource;
    DWORD               dwFlags = FORMAT_MESSAGE_ARGUMENT_ARRAY |
				  FORMAT_MESSAGE_ALLOCATE_BUFFER;


    va_start( arglist, MessageId );

    if ( MessageId < NERR_BASE) {
	//
	//  Get message from system.
	//
	lpSource = NULL; // redundant step according to FormatMessage() spec
	dwFlags |= FORMAT_MESSAGE_FROM_SYSTEM;

    } else if (  ( MessageId >= APE2_AT_DEL_WARNING
		    &&  MessageId <= APE2_AT_DI_COMMAND)
	      //
	      // I cannot find these definitions!!!!
	      //
	      //|| ( MessageId >= IDS_LOAD_LIBRARY_FAILURE
	      //      &&  MessageId <= IDS_USAGE )
	      ) {
	//
	//  Get message from this module.
	//
	lpSource = NULL;
	dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;

    } else {
	//
	//  Get message from netmsg.dll.
	//
	lpSource = GlobalMessageHandle;
	dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;
    }

    length = FormatMessage(
	    dwFlags,                                          //  dwFlags
	    lpSource,                                         //  lpSource
	    MessageId,                                        //  MessageId
	    0L,                                               //  dwLanguageId
	    (LPTSTR)&buffer,                                 //  lpBuffer
	    0,                                                //  size
	    (va_list *) &arglist                              //  lpArguments
	    );

    if ( length != 0) {

	//change to MessageBox
	//printf( "%ws", buffer );

	ptr = buffer;

	while ( *ptr ) {
#ifdef DBCS
            if (IsDBCSLeadByte(*ptr)) {
                ptr++;
            } else
#endif
	    if ( ( *ptr < ' ' ) || ( *ptr > '~' ) ) {

		*ptr = ' ';

	    }

		ptr++;

	}

	SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_RESETCONTENT, 0, 0 );

	SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)(LPTSTR)buffer );

	MessageBox( hGlobalhWnd, (LPCTSTR)buffer, SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

	LocalFree( buffer );

    }

    return( length);

} // MessagePrint()



//===========================================================================
// FUNCTION: MinProc()
//===========================================================================
LRESULT APIENTRY MinProc( HWND hWnd, UINT message, UINT uParam, LONG lParam )
{
    UINT  uCurVal;
    UCHAR szCurVal[3];

    switch ( message ) {

	    case WM_COPY:
	    case WM_PASTE:
	    case WM_CUT:

			// cut and paste dont seem to work...

		break;

// jean-marc - start
      case WM_SETFOCUS:
	hCurrentFocus = hWnd;
	break;
// jean-marc - end

	case WM_CHAR:

			if ( uParam == VK_BACK ) {

				if ( uMinChars > 0 ) {

					--uMinChars;

				}

				return CallWindowProc( (WNDPROC)lpMinDefProc, hWnd, message, uParam, lParam ) ;

			} else {

				uMinChars = (UINT) SendMessage( hWnd, WM_GETTEXT, 2, (LPARAM)szCurVal );

				if ( uMinChars == 0 ) {

				uCurVal = 0;

			    } else if ( uMinChars == 1 ) {

				uCurVal = szCurVal[0] - '0';

			    } else if ( uMinChars == 2 ) {

				uCurVal  = szCurVal[0] - '0';
				uCurVal *= 10;
				uCurVal  = szCurVal[1] - '0';

			    } else if ( uMinChars > 2 ) {

				uMinChars = 0;

				SendMessage( hWnd, WM_SETTEXT, 0, (LPARAM)"" );

				return( 0 );

			    }

			}

			if ( ( uParam == ' ' )                  ||  // space
			     ( uParam < '0' || uParam > '9' )   ||  // not a number
			     ( uCurVal >= 6  )                      // greater than 59
			   ) {

				 MessageBeep( MB_OK );

				 return( 0 );

			} else if ( uMinChars < 2 ) {

				++uMinChars;

			} else {

		    MessageBeep( MB_OK );

			    return( 0 );

			}

		break;

	} // switch

	return CallWindowProc( (WNDPROC)lpMinDefProc, hWnd, message, uParam, lParam ) ;

}



//===========================================================================
// FUNCTION: Refresh()
//===========================================================================
UINT
Refresh(UINT Command)
{

    static BOOL fOkayToRefresh;
	static BOOL     fOkayToRefreshSave;

	switch( Command ) {

		case REFRESH_FALSE:

		    fOkayToRefresh = FALSE;

			break;

		case REFRESH_TRUE:

		    fOkayToRefresh = TRUE;

			break;

		case REFRESH_QUERY:

			return( fOkayToRefresh );

			break;

		case REFRESH_SAVE:

		    fOkayToRefreshSave = fOkayToRefresh;

			break;

		case REFRESH_RESTORE:

		    fOkayToRefresh = fOkayToRefreshSave;

			break;
	}

	return( REFRESH_ERROR );

}



//===========================================================================
// FUNCTION: SelectComputerProc()
//===========================================================================
BOOL APIENTRY SelectComputerProc(
	HWND hWnd,         // window handle
	UINT message,      // type of message
	UINT uParam,       // additional information
		LONG lParam)       // additional information
{

    DWORD           dwLen = MAXCOMPUTERNAMELEN + 1;
    UCHAR           szSelectComputer[MAXCOMPUTERNAMELEN+1];
    int             wmEvent;
    int             wmId;
// jean-marc - start
    UCHAR           szComputerMTemp[MAXCOMPUTERNAMELEN+1];  // multibyte comp. name
// jean-marc - end

    switch (message) {

	case WM_INITDIALOG:
// jean-marc - start
	    // set the text limit for the IDC_SELECTCOMPUTER edit field to be
	    // MAXCOMPUTERNAMELEN
	    SendDlgItemMessage(hWnd,
			       IDC_SELECTCOMPUTER,
			       EM_LIMITTEXT,
			       MAXCOMPUTERNAMELEN,
			       0);
// jean-marc - end

	    if ( !GetComputerName( szSelectComputer, &dwLen ) ) {

#ifdef JAPAN
					MessageBox( hWnd, "コンピュータ名取得エラー.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#else
					MessageBox( hWnd, "Problem getting computer name.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#endif
			} else {

				SetDlgItemText( hWnd, IDC_SELECTCOMPUTER, szSelectComputer );

			}

		break;

	case WM_COMMAND:    // message: command from application menu

	    // Message packing of uParam and lParam have changed for Win32, let us
	    // handle the differences in a conditional compilation:

			wmId    = LOWORD(uParam);
			wmEvent = HIWORD(uParam);

			switch (wmId) {

				case IDCANCEL:

					EndDialog( hWnd, IDCANCEL );

					break;

		case IDOK:

		    GetDlgItemText( hWnd, IDC_SELECTCOMPUTER, &szComputerMTemp[0], MAXCOMPUTERNAMELEN );

// jean-marc - start
		    // make sure backslashes are there, if not then add them
		    if (szComputerMTemp[0] == '\\' && szComputerMTemp[1] == '\\')
		      lstrcpy(szComputerM, szComputerMTemp);
		    else if (szComputerMTemp[0] != '\\' && szComputerMTemp[1] != '\\')
		      wsprintf(szComputerM, "\\\\%s", szComputerMTemp);
		    else if (szComputerMTemp[0] == '\\' || szComputerMTemp[1] == '\\')
		      wsprintf(szComputerM, "\\%s", szComputerMTemp);
		    if (lstrlen(szComputerM) > MAXCOMPUTERNAMELEN || lstrlen(szComputerM) == 2)
#ifdef JAPAN
                    	MessageBox( hWnd, "コンピュータ名は１から１５文字(半角)の長さでなければなりません。", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#else
		      MessageBox( hWnd, "Computer names are 1 to 15 characters long.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#endif
// jean-marc - end

		    else {

			    SetDlgItemText( hGlobalhWnd, IDC_COMPUTER, &szComputerM[2] );

						MultiByteToWideChar(
						CP_ACP,
						MB_PRECOMPOSED,
						szComputerM,
						-1,
						szComputerW,
						MAXCOMPUTERNAMELEN
						);

			GlobalComputerName = szComputerW;

				Refresh( REFRESH_TRUE );

			    EndDialog( hWnd, IDOK );

			}

		    break;

	    }

			break;

    }

    return (0);

}



//===========================================================================
// FUNCTION: ServiceNotStartedHandler()
//===========================================================================
BOOL
ServiceNotStartedHandler(VOID)
{

    BOOL            Done;
    SC_HANDLE       schSCManager;
    SC_HANDLE       schService;
    SERVICE_STATUS  ssServiceStatus;
    UCHAR           szService[] = "Schedule";
    UCHAR           szTemp[80];

#ifdef JAPAN
    wsprintf( szTemp, "%s のスケジュールサービスが開始されていません。\n開始しますか？", &szComputerM[2] );
#else
    wsprintf( szTemp, "Schedule service on %s not started.\nWould you like to start it?", &szComputerM[2] );
#endif

	if ( MessageBox( hGlobalhWnd, szTemp, SZWINDOWTITLE, MB_YESNO ) == IDYES ) {

	    schSCManager = OpenSCManager( szComputerM, NULL, SC_MANAGER_ALL_ACCESS );

	    if ( schSCManager == NULL ) {

#ifdef JAPAN
	    	wsprintf( szTemp, "サービスコントロール マネージャ アクセスエラー\n\nError %d.", GetLastError() );
#else
		wsprintf( szTemp, "Problem accessing Service Control Manager.\n\nError %d.", GetLastError() );
#endif

		MessageBox( hGlobalhWnd, szTemp, SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

		    return( FALSE );

	    } else {

			schService = OpenService( schSCManager, szService, SERVICE_ALL_ACCESS );

			if ( schService == NULL ) {

#ifdef JAPAN
		    	wsprintf( szTemp, "スケージュール サービス オープン エラー\n\nError %d.", GetLastError() );
#else
			wsprintf( szTemp, "Problem opening Schedule service.\n\nError %d.", GetLastError() );
#endif

			MessageBox( hGlobalhWnd, szTemp, SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

			return( FALSE );

		    } else {

				if ( StartService( schService, 0, NULL ) == FALSE ) {

#ifdef JAPAN
			    	wsprintf( szTemp, "スケジュール サービス 開始 エラー\n\nError %d.", GetLastError() );
#else
				wsprintf( szTemp, "Problem starting Schedule service.\n\nError %d.", GetLastError() );
#endif

				MessageBox( hGlobalhWnd, szTemp, SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

					return( FALSE );

			    } else {

				// wait for service to start

				Done = FALSE;

				while( !Done ) {

					if ( QueryServiceStatus( schService, &ssServiceStatus ) == FALSE ) {

#ifdef JAPAN
					    	wsprintf( szTemp, "サービス ステイタス取得エラー\n\nError %d.", GetLastError() );
#else
						wsprintf( szTemp, "Problem getting service status.\n\nError %d.", GetLastError() );
#endif

						MessageBox( hGlobalhWnd, szTemp, SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

							return( FALSE );

						} else {

							switch ( ssServiceStatus.dwCurrentState ) {

								case SERVICE_START_PENDING:

									Sleep( ssServiceStatus.dwWaitHint );

									break;

								case SERVICE_RUNNING:

								    Done = TRUE;

									break;

								default:

#ifdef JAPAN
									wsprintf( szTemp, "予期されないサービス ステイタス\n\nState %d.", ssServiceStatus.dwCurrentState );
#else
									wsprintf( szTemp, "Unexpected service state.\n\nState %d.", ssServiceStatus.dwCurrentState );
#endif

								MessageBox( hGlobalhWnd, szTemp, SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

								Done = TRUE;

								break;

							}

						}

					}

			    }

			CloseServiceHandle(schService);

		}

		CloseServiceHandle(schSCManager);

	    }

		SendDlgItemMessage( hGlobalhWnd, IDC_ATCOMMANDS, LB_RESETCONTENT, 0, 0 );

	SendDlgItemMessage(
		hGlobalhWnd,
		IDC_ATCOMMANDS,
		LB_ADDSTRING,
		0,
#ifdef JAPAN
        	(LPARAM)"スケジュール サービスが正常に開始されました。" );
#else
		(LPARAM)"The Schedule service was started successfully." );
#endif

		MessageBox(
			hGlobalhWnd,
#ifdef JAPAN
			"スケジュール サービスが正常に開始されました。", 
#else
			"The Schedule service was started successfully.",
#endif
			SZWINDOWTITLE,
			MB_OK );

		return( TRUE );

	} else {

	    Refresh( REFRESH_FALSE );

		MessageBox(
			hGlobalhWnd,
#ifdef JAPAN
			"表示は自動的には更新されません。表示を更新するためには、[ファイル]メニューの[コンピュータの選択]を選んでください。", 
#else
			"The display will not be refreshed automatically.  Chose File, Select Computer to refresh the display.",
#endif
			SZWINDOWTITLE,
			MB_OK | MB_ICONEXCLAMATION );

	}

	return( FALSE );

}


//===========================================================================
// FUNCTION: ValidateAddChangeArguments()
//===========================================================================
BOOL
ValidateAddChangeArguments(
	HWND hWnd
	)
{

    SYSTEMTIME              SysTime;
#ifdef JAPAN
    UCHAR                   szAmPm[5];
#else
    UCHAR                   szAmPm[3];
#endif
    UINT                    Items[NUMDAYITEMS];
    UINT                    NumSelected;
    UINT                    i;

	// initialize

    memset( (PBYTE)&GlobalAtInfo, '\0', sizeof(GlobalAtInfo) );

	// command

    SendDlgItemMessage( hWnd, IDC_NEWCOMMAND, WM_GETTEXT, MAXCOMMANDLEN, (LPARAM)szCommandM );

    if ( szCommandM[0] == 0 ) {

	MessageBox(
	    hWnd,
#ifdef JAPAN
            "コマンドを入力してください。",
#else
	    "Enter a command.",
#endif
	    SZWINDOWTITLE,
	    MB_OK | MB_ICONEXCLAMATION
	    );

	SetFocus( GetDlgItem( hWnd, IDC_NEWCOMMAND ) );

	return ( FALSE );

    }

	MultiByteToWideChar(
	CP_ACP,
	MB_PRECOMPOSED,
	szCommandM,
	-1,
	szCommandW,
	MAXCOMMANDLEN
	);

    GlobalAtInfo.Command = szCommandW;

	// hours

    GlobalAtInfo.JobTime = GetDlgItemInt( hWnd, IDC_HOUR, NULL, FALSE );

    GetDlgItemText( hWnd, IDC_AMPM, (LPTSTR)&szAmPm, sizeof(szAmPm) );

#ifdef JAPAN
    if (strcmp(szAmPm, "午前")) {
#else
    if ( szAmPm[0] == 'P' || szAmPm[0] == 'p' ) {
#endif
	if( GlobalAtInfo.JobTime != 12 ) {

		GlobalAtInfo.JobTime += 12;

	}

    } else if( GlobalAtInfo.JobTime == 12 ) {

		GlobalAtInfo.JobTime = 0;

    }


    // convert to minutes

	GlobalAtInfo.JobTime *= 60;

	// add minutes

	GlobalAtInfo.JobTime += GetDlgItemInt( hWnd, IDC_MIN, NULL, FALSE );

	// convert to milliseconds

	GlobalAtInfo.JobTime *= 60 * 1000;

	GetLocalTime( &SysTime );

    if ( SendDlgItemMessage( hWnd, IDC_TODAY, BM_GETCHECK, 0, 0 ) ) {

		if ( (DWORD)( (SysTime.wHour * 60 + SysTime.wMinute) * 60 * 1000) >= GlobalAtInfo.JobTime ) {

			MessageBox(
				hWnd,
#ifdef JAPAN
				"指定された時刻は既に過ぎています。このコマンドは明日実行されます。", 
#else
				"The time you have selected has already passed.  The command will run tomorrow.",
#endif
				SZWINDOWTITLE,
		MB_OK | MB_ICONEXCLAMATION
		);

		}

	}

	if ( SendDlgItemMessage( hWnd, IDC_EVERY, BM_GETCHECK, 0, 0 ) ||
	     SendDlgItemMessage( hWnd, IDC_NEXT, BM_GETCHECK, 0, 0 )    ) {

		// day
		// NOTE: I am assuming that this lisbox will always be correct
		//       and if you select Today/Tomorrow the proper day is selected.

		NumSelected = SendDlgItemMessage( hWnd, IDC_DAYS, LB_GETSELCOUNT, 0, 0 );

		if ( NumSelected == 0 ) {

		MessageBox(
		    hWnd,
#ifdef JAPAN
	            "コマンドを実行する日を選んでください。",
#else
		    "Select the day(s) this command will run.",
#endif
		    SZWINDOWTITLE,
		    MB_OK | MB_ICONEXCLAMATION
		    );

		SetFocus( GetDlgItem( hWnd, IDC_DAYS ) );

		return ( FALSE );

	}

		SendDlgItemMessage( hWnd, IDC_DAYS, LB_GETSELITEMS, NUMDAYITEMS, (LPARAM)Items );

		for( i=0; i<NumSelected; ++i ) {

			if ( Items[i] > 6 ) {

				// days of month
				//0-based, 7 and up are dates (1-31)

			    GlobalAtInfo.DaysOfMonth |= ( 1 << ( Items[i]-7 ) );

			} else {

			    // days of week
			    // 0-based, first 7 are days (M-Su)

			GlobalAtInfo.DaysOfWeek |= ( 1 << Items[i] );

			}

		}

		// flags

	if ( SendDlgItemMessage( hWnd, IDC_EVERY, BM_GETCHECK, 0, 0 ) ) {

	    GlobalAtInfo.Flags |= JOB_RUN_PERIODICALLY;

	}

	} else if ( SendDlgItemMessage( hWnd, IDC_TOMORROW, BM_GETCHECK, 0, 0 ) ) {

		i = SendDlgItemMessage( hWnd, IDC_DAYS, LB_GETCURSEL, 0, 0 );

		if ( i == 0 ) {

		    // set to Sunday

			GlobalAtInfo.DaysOfWeek = ( 1 << 6 );

		} else {

		    // increment to tomorrow

			GlobalAtInfo.DaysOfWeek |= ( 1 << i );

		}

	}

	return( TRUE );

}



//===========================================================================
// FUNCTION: WINATDlgProc()
//===========================================================================
BOOL APIENTRY WINATDlgProc(
	HWND hWnd,         // window handle
	UINT message,      // type of message
	UINT uParam,       // additional information
		LONG lParam)       // additional information
{

    FARPROC         lpAddChangeDlgProc;  // pointer to the "AddChange" function
    FARPROC         lpProcSelect;
    NET_API_STATUS  status;
    int             wmEvent;
    int             wmId;
    int                         iDlgRetCode;
// jean-marc - start
    LOGFONT         lfComputerName;
    static HFONT    hFontComputerName = NULL;
    BOOL            bGetComputerName = FALSE;
// jean-marc - end

    switch (message) {

	case WM_INITDIALOG:
// jean-marc - start
	    // retrieve the font of the field IDC_COMPUTER
	    hFontComputerName = (HFONT)SendDlgItemMessage(hWnd,
							  IDC_COMPUTER,
							  WM_GETFONT,
							  0,
							  0L);

	    // now get the logfont description of the font handle
	    if (GetObject(hFontComputerName, sizeof(LOGFONT), &lfComputerName))
	    {
		// now make the font underlined
		lfComputerName.lfUnderline = 1;

		// next recreate a font handle from this logfont
		hFontComputerName = CreateFontIndirect(&lfComputerName);

		// finally set the font handle for the edit field
		if (hFontComputerName)
		  SendDlgItemMessage(hWnd,
				     IDC_COMPUTER,
				     WM_SETFONT,
				     (WPARAM)hFontComputerName,
				     1L);
	    }
// jean-marc - end
#ifdef JAPAN
#else
	    lf.lfEscapement    = 0;
	    lf.lfOrientation   = 0;
	    lf.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	    lf.lfHeight        = 14;
	    lf.lfWidth         = 0; //6; //5
	    lf.lfWeight        = 0;

	    lf.lfItalic        = 0;
	    lf.lfUnderline     = 0;
	    lf.lfStrikeOut     = 0;

	    lf.lfPitchAndFamily=VARIABLE_PITCH | FF_SWISS;

	    hFont = CreateFontIndirect( &lf );

	    if ( hFont != NULL ) {

		SendDlgItemMessage( hWnd, IDC_ATCOMMANDS, WM_SETFONT, (WPARAM)hFont, 1L );

	    } else {

		MessageBox( hWnd, "Problem creating font.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );

	    }
#endif // !JAPAN

	    hCursorWait = LoadCursor( NULL, IDC_WAIT );

	    if ( !FInitListboxExtents( GetDlgItem( hWnd, IDC_ATCOMMANDS ) ) ) {

#ifdef JAPAN
                MessageBox( hWnd, "メモリ獲得失敗", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#else
		MessageBox( hWnd, "Scrolling broken", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#endif

	    }

	    hGlobalhWnd = hWnd;

	    // get values from registry

	    SendMessage(hWnd, WM_COMMAND, IDM_GET_FROM_REGISTRY, 0);

	    // set tabstops for commands

	    {

#ifdef JAPAN
                UINT Tabs[3] = { 22, 72, 124 };
#else
		UINT Tabs[3] = { 25, 110, 145 };
#endif

		SendDlgItemMessage( hWnd, IDC_ATCOMMANDS, LB_SETTABSTOPS, 3, (LPARAM)Tabs );

	    }

			// get local computer name

			{

				DWORD dwLen = MAXCOMPUTERNAMELEN;

// jean-marc - start
				// process the commandline
				if (gszCommandLine[0])
				{
				  // make sure backslashes are there, if not then add them
				  if (gszCommandLine[0] == '\\' && gszCommandLine[1] == '\\')
				    lstrcpy(szComputerM, gszCommandLine);
				  else if (gszCommandLine[0] != '\\' && gszCommandLine[1] != '\\')
				    wsprintf(szComputerM, "\\\\%s", gszCommandLine);
				  else if (gszCommandLine[0] == '\\' || gszCommandLine[1] == '\\')
				    wsprintf(szComputerM, "\\%s", gszCommandLine);
				  if (lstrlen(szComputerM) > MAXCOMPUTERNAMELEN || lstrlen(szComputerM) == 2)
				  {
#ifdef JAPAN
                    		    MessageBox( hWnd, "コンピュータ名は１から１５文字(半角)の長さでなければなりません。", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#else
				    MessageBox( hWnd, "Computer names are 1 to 15 characters long.\nUsing local computer name.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#endif
				    bGetComputerName = GetComputerName( &szComputerM[2], &dwLen );
				    if (!bGetComputerName)
#ifdef JAPAN
					MessageBox( hWnd, "コンピュータ名取得エラー", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#else
				      MessageBox( hWnd, "Problem getting computer name", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#endif
				  }
				  else
				    bGetComputerName = TRUE;
				}
				else
				{
				  bGetComputerName = GetComputerName( &szComputerM[2], &dwLen );
				  if (!bGetComputerName)
#ifdef JAPAN
				    MessageBox( hWnd, "コンピュータ名取得エラー", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#else
				    MessageBox( hWnd, "Problem getting computer name", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#endif
				}
// jean-marc - end

			    if (bGetComputerName) {

				    szComputerM[0] = '\\';
				szComputerM[1] = '\\';

				    MultiByteToWideChar(
					CP_ACP,
					MB_PRECOMPOSED,
					szComputerM,
					-1,
					szComputerW,
					MAXCOMMANDLEN
					);

		    // set GlobalComputerName for all functions to use
					// only Select Computer will ever change this value

		    GlobalComputerName = szComputerW;

				SendDlgItemMessage( hWnd, IDC_COMPUTER, WM_SETTEXT, 0, (LPARAM)&szComputerM[2]  );

			}

			}

	    // set initial states of buttons to disabled

	    EnableWindow( GetDlgItem( hGlobalhWnd, IDC_ADD    ), FALSE );
	    EnableWindow( GetDlgItem( hGlobalhWnd, IDC_CHANGE ), FALSE );
		EnableWindow( GetDlgItem( hGlobalhWnd, IDC_REMOVE ), FALSE );

		// initialize the commands window

#ifdef JAPAN
        	SendDlgItemMessage( hWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)"初期化中" );
#else
		SendDlgItemMessage( hWnd, IDC_ATCOMMANDS, LB_ADDSTRING, 0, (LPARAM)"Initializing" );
#endif

		// set up timer to go off very soon after the dlgbox is created

	    uTimer = SetTimer( hWnd, 1, 1000, NULL );
	    fTimer = FIRST_TIME;
	    Refresh( REFRESH_TRUE );


	    GlobalMessageHandle = LoadLibrary( "netmsg.dll" );

	    if ( GlobalMessageHandle == NULL ) {

;//                MessagePrint( IDS_LOAD_LIBRARY_FAILURE, GetLastError() );

	    }

	    break;

	case WM_TIMER:

			if ( fTimer == FIRST_TIME ) {

				uTimer = SetTimer( hWnd, 1, REFRESH_RATE, NULL );

				fTimer = !FIRST_TIME;

			}

	    if ( Refresh( REFRESH_QUERY ) == TRUE ) {

		SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_NOCHANGE );

	    }

	    break;

	case WM_COMMAND:    // message: command from application menu

	    // Message packing of uParam and lParam have changed for Win32, let us
	    // handle the differences in a conditional compilation:

			wmId    = LOWORD(uParam);
			wmEvent = HIWORD(uParam);

			switch (wmId) {

				case IDC_ATCOMMANDS:

			    if ( LBN_DBLCLK == wmEvent ) {

				if ( IsWindowEnabled( GetDlgItem( hWnd, IDC_CHANGE ) ) ) {

					PostMessage( hWnd, WM_COMMAND, IDC_CHANGE, 0 );

				}

			    }

				break;

		case IDC_REFRESH:

		    if ( Refresh( REFRESH_QUERY ) == TRUE ) {

			    Refresh( REFRESH_FALSE );

			    hCursorOld = SetCursor( hCursorWait );

			    status = JobEnum( lParam );

			    SetCursor( hCursorOld );

			    if ( status == NERR_Success || status == ERROR_SUCCESS ) {

				Refresh( REFRESH_TRUE );

			    }

			}

		    break;

				case IDC_ADD:

				    Refresh( REFRESH_FALSE );

				    lpAddChangeDlgProc = MakeProcInstance((FARPROC)AddChangeDlgProc, hInstance);

				    iDlgRetCode = DialogBoxParam(
					hInst,
					"ADDCHANGEDLG",
					hWnd,
					(DLGPROC)lpAddChangeDlgProc,
					IDC_ADD);

				    hGlobalAddChg = NULL;

				    FreeProcInstance(lpAddChangeDlgProc);
				    FreeProcInstance(lpAmPmProc);
				    FreeProcInstance(lpAmPmDefProc);
				    FreeProcInstance(lpHourProc);
				    FreeProcInstance(lpHourDefProc);
				    FreeProcInstance(lpMinProc);
				    FreeProcInstance(lpMinDefProc);
				    FreeProcInstance(lpDownButtonProc);
				    FreeProcInstance(lpDownButtonDefProc);
				    FreeProcInstance(lpUpButtonProc);
				    FreeProcInstance(lpUpButtonDefProc);

				    Refresh( REFRESH_TRUE );

				    if ( iDlgRetCode == IDOK ) {

					SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_BOTTOM );

				    }

		    break;

		case IDC_CHANGE:

			Refresh( REFRESH_FALSE );

		    lpAddChangeDlgProc = MakeProcInstance((FARPROC)AddChangeDlgProc, hInstance);

				    iDlgRetCode = DialogBoxParam(
					hInst,
					"ADDCHANGEDLG",
					hWnd,
					(DLGPROC)lpAddChangeDlgProc,
					IDC_CHANGE);

				    hGlobalAddChg = NULL;

				    FreeProcInstance(lpAddChangeDlgProc);
				    FreeProcInstance(lpAmPmProc);
				    FreeProcInstance(lpAmPmDefProc);
				    FreeProcInstance(lpHourProc);
				    FreeProcInstance(lpHourDefProc);
				    FreeProcInstance(lpMinProc);
				    FreeProcInstance(lpMinDefProc);
				    FreeProcInstance(lpDownButtonProc);
				    FreeProcInstance(lpDownButtonDefProc);
				    FreeProcInstance(lpUpButtonProc);
				    FreeProcInstance(lpUpButtonDefProc);

					Refresh( REFRESH_TRUE );

				    if ( iDlgRetCode == IDOK ) {

					SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_BOTTOM );

				    }

		    break;

		case IDC_REMOVE:

		    status = JobDel( DEL_ID, hWnd );

			break;

		case IDM_GET_FROM_REGISTRY:

		    RegCreateKeyEx(REG_HKEY,
				   szRegistryPath,
				   0,
				   "",
				   REG_OPTION_NON_VOLATILE,
				   KEY_ALL_ACCESS,
				   NULL,
				   &hkHandle,
				   &dwDisposition);

		    if ( dwDisposition == REG_CREATED_NEW_KEY ) {

			RegSetValueEx(hkHandle, "dwX", 0, REG_DWORD, (LPBYTE)DWX, sizeof(DWORD));
			RegSetValueEx(hkHandle, "dwY", 0, REG_DWORD, (LPBYTE)DWY, sizeof(DWORD));

		    }

		    {
			DWORD dwType = REG_DWORD;
			DWORD dwSize = sizeof(DWORD);

			RegQueryValueEx(hkHandle, "dwX", 0, &dwType, (LPBYTE)&dwX, &dwSize);
			RegQueryValueEx(hkHandle, "dwY", 0, &dwType, (LPBYTE)&dwY, &dwSize);

		    }

		    RegCloseKey(hkHandle);

		    {
			RECT Rect;

			if(!GetWindowRect(hWnd, &Rect)) {

			    MessageBox(
				hWnd,
#ifdef JAPAN
                                "ウィンドウ位置取得エラー",
#else
				"Problem getting window coordinates.",
#endif
				SZWINDOWTITLE,
				MB_OK | MB_ICONEXCLAMATION
				);

			} else {

			    dwW = Rect.right  - Rect.left;
			    dwH = Rect.bottom - Rect.top;

			}

		    }

		    MoveWindow(hWnd, (INT)dwX, (INT)dwY, (INT)dwW, (INT)dwH, TRUE);

		    break;

		 case IDM_SAVE_TO_REGISTRY:

		    RegCreateKeyEx(REG_HKEY,
				   szRegistryPath,
				   0,
				   "",
				   REG_OPTION_NON_VOLATILE,
				   KEY_ALL_ACCESS,
				   NULL,
				   &hkHandle,
				   &dwDisposition
				   );

		    {
			RECT Rect;

			if(!GetWindowRect(hWnd, &Rect)) {

			    dwX = DWX;
			    dwY = DWY;

			    MessageBox(
				hWnd,
#ifdef JAPAN
                                "ウィンドウ位置取得エラー",
#else
				"Problem getting coordinates.",
#endif
				SZWINDOWTITLE,
				MB_OK | MB_ICONEXCLAMATION
				);

			} else {

			    dwX = Rect.left;
			    dwY = Rect.top;

			}

		    }

		    RegSetValueEx(hkHandle, "dwX", 0, REG_DWORD, (LPBYTE)&dwX, sizeof(DWORD));
		    RegSetValueEx(hkHandle, "dwY", 0, REG_DWORD, (LPBYTE)&dwY, sizeof(DWORD));

		    RegCloseKey(hkHandle);

		    break;

		case IDM_ABOUT:

					Refresh( REFRESH_SAVE );
		    Refresh( REFRESH_FALSE );

// jean-marc - start
		    if ( ShellAbout( hGlobalhWnd, SZWINDOWTITLE, NULL, LoadIcon( hInst, (LPSTR)SZAPPTITLE ) ) == -1 ) {
//old line		    if ( ShellAbout( hGlobalhWnd, SZWINDOWTITLE, SZCREDITS, LoadIcon( hInst, (LPSTR)SZAPPTITLE ) ) == -1 ) {
// jean-marc - end

#ifdef JAPAN
                    	MessageBox( hGlobalhWnd, "メモリ不足", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#else
			MessageBox( hGlobalhWnd, "Out of memory error.", SZWINDOWTITLE, MB_OK | MB_ICONEXCLAMATION );
#endif

		    }

					Refresh( REFRESH_RESTORE );

					break;

		case IDM_SELECTCOMPUTER:

		    Refresh( REFRESH_SAVE );
		    Refresh( REFRESH_FALSE );

		    lpProcSelect = MakeProcInstance((FARPROC)SelectComputerProc, hInst);

					iDlgRetCode = DialogBox(hInst,
						"SelectComputer",
						hWnd,
						(DLGPROC)lpProcSelect);

					FreeProcInstance(lpProcSelect);

		    Refresh( REFRESH_TRUE );

					if ( iDlgRetCode == IDOK ) {

						SendMessage( hWnd, WM_COMMAND, IDC_REFRESH, (LPARAM)SCS_TOP );

					}

			break;

		case IDM_EXIT:

		    Refresh( REFRESH_FALSE );
		    FFreeListboxExtents( GetDlgItem( hWnd, IDC_ATCOMMANDS ) );
		    ShowWindow( hWnd, SW_RESTORE );
		    SendMessage( hWnd, WM_COMMAND, IDM_SAVE_TO_REGISTRY, 0 );
#ifdef JAPAN
#else
		    DeleteObject( hFont );
// jean-marc - start
		    if (hFontComputerName)
		      DeleteObject(hFontComputerName);
// jean-marc - end
#endif
		    KillTimer( hWnd, 1 );
		    EndDialog( hWnd, 0 );

					break;

		case IDC_HELP:

#ifdef KKBUGFIX
		    if (!WinHelp (hWnd, "WINAT.HLP", HELP_CONTENTS,0L)) {
#else
		    if (!WinHelp (hWnd, "WINAT.HLP", HELP_KEY,(DWORD)(LPSTR)"CONTENTS")) {
#endif
						MessageBox (GetFocus(),
#ifdef JAPAN
							"ヘルプを起動できません",
#else
							"Unable to activate help",
#endif
							SZWINDOWTITLE, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
		    }
					break;

		case IDM_HELPCONTENTS:

#ifdef KKBUGFIX
		    if (!WinHelp (hWnd, "WINAT.HLP", HELP_CONTENTS,0L)) {
#else
		    if (!WinHelp (hWnd, "WINAT.HLP", HELP_KEY,(DWORD)(LPSTR)"CONTENTS")) {
#endif
						MessageBox (GetFocus(),
#ifdef JAPAN
							"ヘルプを起動できません",
#else
							"Unable to activate help",
#endif
							SZWINDOWTITLE, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
		    }

		    break;

				case IDM_HELPSEARCH:

		    if (!WinHelp(hWnd, "WINAT.HLP", HELP_PARTIALKEY, (DWORD)(LPSTR)"")) {
						MessageBox (GetFocus(),
#ifdef JAPAN
							"ヘルプを起動できません",
#else
							"Unable to activate help",
#endif
							SZWINDOWTITLE, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
		    }

		    break;

				case IDM_HELPHELP:

		    if(!WinHelp(hWnd, (LPSTR)NULL, HELP_HELPONHELP, 0)) {
						MessageBox (GetFocus(),
#ifdef JAPAN
							"ヘルプを起動できません",
#else
							"Unable to activate help",
#endif
							SZWINDOWTITLE, MB_SYSTEMMODAL|MB_OK|MB_ICONHAND);
		    }

		    break;

	    }

	    break;

	case WM_CLOSE:
	case WM_ENDSESSION:

	    SendMessage(hWnd, WM_COMMAND, IDM_EXIT, 0);

	    break;

    }

    return (0);

}



//===========================================================================
// FUNCTION: WinMain()
//===========================================================================
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

    FARPROC   lpWINATDlgProc;
    WNDCLASS  wc;

    hInst       = hInstance;

	// Fill in window class structure with parameters that describe the
	// main window.

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)DefDlgProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (hInstance, szAppName);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = szAppName;
    wc.lpszClassName = szAppName;

    // Register the window class

    RegisterClass(&wc);

// jean-marc - start
    // store the commandline (only copy over MAXCOMPUTERNAMELEN characters)
    memset(&gszCommandLine, 0, sizeof(gszCommandLine));
    strncpy(gszCommandLine, lpCmdLine, MAXCOMPUTERNAMELEN);
    // the commandline will actually be processed from within the WINATDlgProc
// jean-marc - end

    //
    // this program is only a single dialog box
    //

    lpWINATDlgProc = MakeProcInstance((FARPROC)WINATDlgProc, hInstance);

    DialogBox(hInstance,
	"WINATDLG",
	0,
	(DLGPROC)lpWINATDlgProc
	);

    FreeProcInstance(lpWINATDlgProc);

    return 0;

}
