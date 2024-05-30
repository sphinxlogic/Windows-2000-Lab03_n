//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       DLG.CPP
//  Content:    Dialog Box Procedures
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"

DWSTR _rgCallType[] = {
	{NM_CALL_DEFAULT, TEXT("Default")},
	{NM_CALL_T120,    TEXT("T120")},
	{NM_CALL_H323,    TEXT("H323")},
};

DWSTR _rgAddrType[] = {
	{NM_ADDR_UNKNOWN,      TEXT("Unknown")},
	{NM_ADDR_IP,           TEXT("IP")},
	{NM_ADDR_MACHINENAME,  TEXT("Machine name")},
	{NM_ADDR_PSTN,         TEXT("PSTN")},
	{NM_ADDR_ULS,          TEXT("ULS")},
	{NM_ADDR_H323_GATEWAY, TEXT("H323 Gateway")},
};

VOID InitLBox(HWND hwndCombo, DWSTR *pdwstr, UINT cElt, DWORD dwDefault)
{
	DWORD dwIndex;
	DWORD iSel = 0;

	ASSERT(NULL != hwndCombo);

	for ( ; cElt > 0; cElt--, pdwstr++)
	{
		dwIndex = SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) pdwstr->psz); 
		SendMessage(hwndCombo, CB_SETITEMDATA, dwIndex, (LPARAM) pdwstr->dw);
		if (pdwstr->dw == dwDefault)
		{
			iSel = dwIndex;
		}
	}

	SendMessage(hwndCombo, CB_SETCURSEL, dwDefault, 0);
}


//****************************************************************************
//
// DWORD GetLBoxDw(HWND hwndCombo)
//
//****************************************************************************

DWORD GetLBoxDw(HWND hwndCombo)
{
	int iSel = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
	if (CB_ERR == iSel)
		return 0;

	return SendMessage(hwndCombo, CB_GETITEMDATA, (WPARAM) iSel, 0);
}


//****************************************************************************
//
// VOID InitUserLBox(HWND hdlg, BOOL fEveryone)
//
//****************************************************************************

VOID InitUserLBox(HWND hdlg, BOOL fEveryone)
{
	HWND hwndCombo = GetDlgItem(hdlg, IDL_USERS);
	ASSERT(NULL != hwndCombo);
	InitializeUserList(hwndCombo, fEveryone);
}


//****************************************************************************
//
// VOID InitializeUserList(HWND hwndCombo, BOOL fEveryone)
//
//****************************************************************************

VOID InitializeUserList(HWND hwndCombo, BOOL fEveryone)
{
	if (NULL == g_pListUser)
		return;

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		POSITION posSav = pos;
		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		AddUserToUList(pUser, hwndCombo, fEveryone);
	}

	SendMessage(hwndCombo, CB_SETCURSEL, 0, 0); 
}


//****************************************************************************
//
// VOID AddUserToUList(PUSER pUser, HWND hwndCombo, BOOL fEveryone)
//
//****************************************************************************

VOID AddUserToUList(PUSER pUser, HWND hwndCombo, BOOL fEveryone)
{
	DWORD dwIndex;
	ASSERT(NULL != pUser);
	if (fEveryone && (S_OK == pUser->pMember->IsSelf()))
	{
		dwIndex = SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) TEXT("<all>")); 
	}
	else
	{
		dwIndex = SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) pUser->pszName); 
	}
	SendMessage(hwndCombo, CB_SETITEMDATA, dwIndex, (LPARAM) pUser); 
}


//****************************************************************************
//
// VOID RemoveUserFromUList(PUSER pUser, HWND hwndCombo)
//
//****************************************************************************

VOID RemoveUserFromUList(PUSER pUser, HWND hwndCombo)
{
	ASSERT(NULL != pUser);

	if (!IsWindow(hwndCombo))
	{
		ERROR_MSG("RemoveUserFromUList: invalid hwndcombo?");
		return;
	}

	for (DWORD dwIndex = 0; ; dwIndex++)
	{
		DWORD dw = SendMessage(hwndCombo, CB_GETITEMDATA, dwIndex, 0);
		if (CB_ERR == dw)
		{
			break;
		}
		if (pUser == (PUSER) dw)
		{
			SendMessage(hwndCombo, CB_DELETESTRING, (WPARAM)dwIndex, 0); 
			return;
		}
	}

	ERROR_MSG("RemoveUserFromUList: Unable to delete [%s]", pUser->pszName);
}


//****************************************************************************
//
// VOID DrawUserItem(LPDRAWITEMSTRUCT lpdis)
//
//****************************************************************************

VOID DrawUserItem(LPDRAWITEMSTRUCT lpdis)
{
	if (lpdis->itemID == -1)
		return; 

	PUSER pUser = (PUSER) lpdis->itemData;
	COLORREF cvText;
	COLORREF cvBack;

	cvText = SetTextColor(lpdis->hDC, GetSysColor((lpdis->itemState & ODS_SELECTED)
		? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT)); 

	cvBack = SetBkColor(lpdis->hDC, GetSysColor((lpdis->itemState & ODS_SELECTED)
		? COLOR_HIGHLIGHT : COLOR_WINDOW)); 

	if (NULL == pUser->pszName)
	{
		static const TCHAR szUnknownUser[] = TEXT("? user");
		ExtTextOut(lpdis->hDC, lpdis->rcItem.left+2, lpdis->rcItem.top+2, 
			ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem,
			szUnknownUser, CCHMAX(szUnknownUser)-1, NULL); 
	}
	else
	{
		ExtTextOut(lpdis->hDC, lpdis->rcItem.left+2, lpdis->rcItem.top+2, 
			ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem,
			pUser->pszName, lstrlen(pUser->pszName), NULL); 
	}

	SetTextColor(lpdis->hDC, cvText); 
	SetBkColor(lpdis->hDC, cvBack); 
 
	if (lpdis->itemState & ODS_FOCUS)
	{
		DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
	}
}
   

//****************************************************************************
//
// LRESULT CALLBACK ConferenceDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK ConferenceDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		SetDlgItemText(hdlg, IDE_NAME, gPref.pszConferenceName);
		SetDlgItemText(hdlg, IDE_PASSWORD, gPref.pszPassword);

		{ // check channel types
			DWORD dwFlag = 0x01;
			for (int id = IDC_NMCH_FIRST; id <= IDC_NMCH_LAST; id++)
			{
				CheckDlgButton(hdlg, id, 0 != (gPref.dwNmch & dwFlag));
				dwFlag <<= 1;
			}
		}

		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			GetDlgItemPsz(hdlg, IDE_NAME, &gPref.pszConferenceName);
			GetDlgItemPsz(hdlg, IDE_PASSWORD, &gPref.pszPassword);

			{ // check media types
				DWORD dwFlag = 0x01;
				gPref.dwNmch = 0;
				for (int id = IDC_NMCH_FIRST; id <= IDC_NMCH_LAST; id++)
				{
					if (IsDlgButtonChecked(hdlg, id))
						gPref.dwNmch |= dwFlag;
					dwFlag <<= 1;
				}
			}

			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgNewConference(VOID)
//
//****************************************************************************

BOOL DlgNewConference(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_CONFERENCE),
		ghwndMain, (DLGPROC)ConferenceDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK SendFileDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK SendFileDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hwnd;
	
		CenterWindow(hdlg, ghwndMain);

		hwnd = GetDlgItem(hdlg, IDC_USERNAME);
	
		InitUserLBox(hdlg, TRUE);
		
		// Set the default filename
		SetDlgItemText(hdlg, IDE_FILENAME, gPref.pszFileName);
		
		return TRUE;
	}

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		{
			INmMember * pMember = NULL;
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				if (NULL != pUser)
				{
					pMember = pUser->pMember;
					if (S_OK == pMember->IsSelf())
						pMember = NULL; // everyone
				}
			}
			GetDlgItemPsz(hdlg, IDE_FILENAME, &gPref.pszFileName);

			SendFile(pMember);
			EndDialog(hdlg, 0);
			return TRUE;
		}

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;
		
		case IDB_BROWSE:
		{
			TCHAR szFileName[MAX_PATH];

			// Get the file name
			if (!FGetFileName(szFileName))
				return FALSE;
			
			SetDlgItemText(hdlg, IDE_FILENAME, szFileName);
			return TRUE;
		}


		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}

//****************************************************************************
//
// BOOL DlgSendFile(VOID)
//
//****************************************************************************

BOOL DlgSendFile(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_SENDFILE),
		ghwndMain, (DLGPROC)SendFileDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK CallConfDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK CallConfDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		SetDlgItemText(hdlg, IDE_ADDR,       gPref.pszAddr);
		SetDlgItemText(hdlg, IDE_CONFERENCE, gPref.pszConferenceName);
		SetDlgItemText(hdlg, IDE_PASSWORD,   gPref.pszPassword);

		InitLBox(GetDlgItem(hdlg, IDL_ADDR_TYPE),
			_rgAddrType, ARRAY_ELEMENTS(_rgAddrType), gPref.nmAddrType);
		InitLBox(GetDlgItem(hdlg, IDL_CALL_TYPE),
			_rgCallType, ARRAY_ELEMENTS(_rgCallType), gPref.nmCallType);
		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			GetDlgItemPsz(hdlg, IDE_ADDR,       &gPref.pszAddr);
			GetDlgItemPsz(hdlg, IDE_CONFERENCE, &gPref.pszConferenceName);
			GetDlgItemPsz(hdlg, IDE_PASSWORD,   &gPref.pszPassword);

			gPref.nmAddrType = (NM_ADDR_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_ADDR_TYPE));
			gPref.nmCallType = (NM_CALL_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_CALL_TYPE));

			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgCallConf(VOID)
//
//****************************************************************************

BOOL DlgCallConf(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_CALL_CONF),
		ghwndMain, (DLGPROC)CallConfDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK CallDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK CallDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		SetDlgItemText(hdlg, IDE_ADDR, gPref.pszAddr);
		InitLBox(GetDlgItem(hdlg, IDL_ADDR_TYPE),
			_rgAddrType, ARRAY_ELEMENTS(_rgAddrType), gPref.nmAddrType);
		InitLBox(GetDlgItem(hdlg, IDL_CALL_TYPE),
			_rgCallType, ARRAY_ELEMENTS(_rgCallType), gPref.nmCallType);
		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			GetDlgItemPsz(hdlg, IDE_ADDR, &gPref.pszAddr);

			gPref.nmAddrType = (NM_ADDR_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_ADDR_TYPE));
			gPref.nmCallType = (NM_CALL_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_CALL_TYPE));

			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgNewCall(VOID)
//
//****************************************************************************

BOOL DlgNewCall(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_CALL),
		ghwndMain, (DLGPROC)CallDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK OptionsDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK OptionsDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		CheckDlgButton(hdlg, IDC_MONITOR, gPref.fAutoMonitor);

		CheckDlgButton(hdlg, IDC_HOST, gPref.fAutoHost);
		SetDlgItemText(hdlg, IDE_CONFERENCE_NAME, gPref.pszConferenceName);

		CheckDlgButton(hdlg, IDC_CALL_USER, gPref.fAutoCall);
		SetDlgItemText(hdlg, IDE_USER_NAME, gPref.pszAddr);

		CheckDlgButton(hdlg, IDC_AUTO_CHAT, gPref.fAutoChat);

		CheckDlgButton(hdlg, IDC_MSG_TRACE,   gPref.fMsgTrace);
		CheckDlgButton(hdlg, IDC_MSG_OBJECTS, gPref.fMsgObjects);
		CheckDlgButton(hdlg, IDC_MSG_NOTIFY,  gPref.fMsgNotify);

		CheckRadioButton(hdlg, IDR_INIT_NORMAL, IDR_INIT_NO_LAUNCH,
			gPref.iInit + IDR_INIT_NORMAL);
		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			gPref.fAutoMonitor= IsDlgButtonChecked(hdlg, IDC_MONITOR);

			gPref.fAutoHost   = IsDlgButtonChecked(hdlg, IDC_HOST);
			GetDlgItemPsz(hdlg, IDE_CONFERENCE_NAME, &gPref.pszConferenceName);

			gPref.fAutoCall   = IsDlgButtonChecked(hdlg, IDC_CALL_USER);
			GetDlgItemPsz(hdlg, IDE_USER_NAME, &gPref.pszAddr);

			gPref.fAutoChat   = IsDlgButtonChecked(hdlg, IDC_AUTO_CHAT);

			gPref.fMsgTrace   = IsDlgButtonChecked(hdlg, IDC_MSG_TRACE);
			gPref.fMsgObjects = IsDlgButtonChecked(hdlg, IDC_MSG_OBJECTS);
			gPref.fMsgNotify  = IsDlgButtonChecked(hdlg, IDC_MSG_NOTIFY);

			if (IsDlgButtonChecked(hdlg, IDR_INIT_NORMAL))
				gPref.iInit = NM_INIT_NORMAL;
			else if (IsDlgButtonChecked(hdlg, IDR_INIT_CONTROL))
				gPref.iInit = NM_INIT_CONTROL;
			else if (IsDlgButtonChecked(hdlg, IDR_INIT_NO_LAUNCH))
				gPref.iInit = NM_INIT_NO_LAUNCH;

			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgOptions(VOID)
//
//****************************************************************************

BOOL DlgOptions(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_OPTIONS),
		ghwndMain, (DLGPROC)OptionsDlgProc));
}


//****************************************************************************
//
// VOID UpdateAudioSettings(HWND hdlg)
//
//****************************************************************************

VOID UpdateAudioSettings(HWND hdlg)
{
	int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
	if (CB_ERR == iSel)
		return;

	PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
		CB_GETITEMDATA, (WPARAM) iSel, 0);
	INmChannelAudio * pChannel = pUser->m_pChannelAudio;
	if (NULL != pChannel)
	{
		NM_AUDIO_STATE uState;
		if (SUCCEEDED(pChannel->GetState(&uState)))
		{
			TRACE_MSG("Audio State is %d", uState);
		}
		
		DWORD dwLevel;
		if (SUCCEEDED(pChannel->GetProperty(NM_AUDPROP_LEVEL, &dwLevel)))
		{
			SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETPOS, TRUE,
								dwLevel );

			SetDlgItemInt(hdlg, IDE_LEVEL, dwLevel, FALSE);
		}
		
		CheckDlgButton(hdlg, IDC_ACTIVE,
			(S_OK == pChannel->IsActive()) ? BST_CHECKED : BST_UNCHECKED);

		DWORD fPause = FALSE;
		pChannel->GetProperty(NM_AUDPROP_PAUSE, &fPause);
		CheckDlgButton(hdlg, IDC_PAUSE, fPause ? BST_CHECKED : BST_UNCHECKED);
	}
}


//****************************************************************************
//
// LRESULT CALLBACK AudioDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK AudioDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);

		InitUserLBox(hdlg, FALSE);
		
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETRANGEMIN, FALSE,
			0 );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETRANGEMAX, FALSE,
			NM_MAX_AUDIO_LEVEL );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETTICFREQ, 
			8096, 0 );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETPAGESIZE, 
			0, 8096 );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETLINESIZE, 
			0, 256 );

		UpdateAudioSettings(hdlg);
		return TRUE;
	}
	
	case WM_DRAWITEM: 
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		case IDB_UPDATE:
		{
			UpdateAudioSettings(hdlg);
			return TRUE;
		}
		
		case IDC_ACTIVE:
		{
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				INmChannelAudio * pChannel = pUser->m_pChannelAudio;
				if (NULL != pChannel)
				{
					// Flip the active state
					BOOL fActive = (S_OK != pChannel->IsActive());
					hr = pChannel->SetActive(fActive);
					TRACE_MSG("SetActive result=%s", GetHrSz(hr));
				}
			}
			return TRUE;
		}

		case IDC_PAUSE:
		{
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				INmChannelAudio * pChannel = pUser->m_pChannelAudio;
				if (NULL != pChannel)
				{
					// Flip the pause state
					DWORD fPause = IsDlgButtonChecked(hdlg, IDC_PAUSE);
					hr = pChannel->SetProperty(NM_AUDPROP_PAUSE, fPause);
					TRACE_MSG("SetProperty result=%s", GetHrSz(hr));
				}
			}
			return TRUE;
		}

		default:
			return TRUE;
		} /* switch (cmd) */

	case WM_HSCROLL:
	{
		DWORD dwLevel = SendDlgItemMessage( hdlg, IDC_LEVEL,
					TBM_GETPOS, 0, 0 );
		SetDlgItemInt(hdlg, IDE_LEVEL, dwLevel, FALSE);

		if (TB_ENDTRACK == LOWORD(wParam))
		{
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				INmChannelAudio * pChannel = pUser->m_pChannelAudio;
				if (NULL != pChannel)
				{
					hr = pChannel->SetProperty(NM_AUDPROP_LEVEL, dwLevel);
					TRACE_MSG("SetProperty result=%s", GetHrSz(hr));
				}
			}
		}
		return TRUE;
	}

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgAudio(VOID)
//
//****************************************************************************

BOOL DlgAudio(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_AUDIO),
		ghwndMain, (DLGPROC)AudioDlgProc));
}


//****************************************************************************
//
// Application sharing
//
//****************************************************************************

#define ILV_AS_HWND   0
#define ILV_AS_STATUS 1
#define ILV_AS_NAME   2

static COL _rgColShare[] = {
	{70,  "Hwnd"},
	{70,  "Status"},
	{120, "Name"},
};


//****************************************************************************
//
// VOID FreeShareList(HWND hwnd)
//
//****************************************************************************

VOID FreeShareList(HWND hwnd)
{
	LV_ITEM lvi;

	ClearStruct(&lvi);
	lvi.mask = LVIF_PARAM;

	for (int iItem = 0; ; iItem++)
	{
		lvi.iItem = iItem;
		if (!ListView_GetItem(hwnd, &lvi))
			break;

		INmSharableApp * pApp = (INmSharableApp *) lvi.lParam;
		ASSERT(NULL != pApp);
		pApp->Release();
	}

	ListView_DeleteAllItems(hwnd);
}


//****************************************************************************
//
// VOID UpdateShareList(HWND hwnd)
//
//****************************************************************************

VOID UpdateShareList(HWND hwnd)
{
	LV_ITEM  lvItem;
	HRESULT hr;
	ULONG cFetched;
	IEnumNmSharableApp * pEnum;
	INmSharableApp * pApp;
	NM_SHAPP_STATE uState;
	HWND   hwndApp;
	int    iItem;
	BSTR   bstr;
	LPTSTR psz;
	TCHAR  sz[MAX_PATH];

	FreeShareList(hwnd);

	if (NULL == g_pChannelShare)
		return;

	ClearStruct(&lvItem);
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;

	hr = g_pChannelShare->EnumSharableApp(&pEnum);
	if (FAILED(hr))
	{
    	return;
	}

	for ( ; ; )
	{
		hr = pEnum->Next(1, &pApp, &cFetched);
		if (S_OK != hr)
			break;

		hr = pApp->GetHwnd(&hwndApp);
		wsprintf(sz, "%08X", hwndApp);

		lvItem.pszText = sz;
		lvItem.cchTextMax = lstrlen(sz);
		lvItem.lParam = (LPARAM) pApp;
		iItem = ListView_InsertItem(hwnd, &lvItem);

		hr = pApp->GetState(&uState);
		ListView_SetItemText(hwnd, iItem, ILV_AS_STATUS,
			(NM_SHAPP_SHARED == uState) ? TEXT("Shared") : TEXT("Not Shared"));

		hr = pApp->GetName(&bstr);
		psz = PszFromBstr(bstr);
		ListView_SetItemText(hwnd, iItem, ILV_AS_NAME, psz);
		SysFreeString(bstr);
		FreePlpv(&psz);

		// pApp->Release();  // Release this in FreeShareList()
	}

	pEnum->Release();
}


//****************************************************************************
//
// VOID InitShareList(HWND hdlg)
//
//****************************************************************************

VOID InitShareList(HWND hdlg)
{
	HWND hwnd = GetDlgItem(hdlg, IDL_APP);
	ASSERT(NULL != hwnd);

	// Initialize column data
	{
		int   iCol;
		LPCOL lpCol;
		LV_COLUMN lvc;

		lpCol = _rgColShare;
		ClearStruct(&lvc);
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_LEFT;
		for (iCol = 0; iCol < ARRAY_ELEMENTS(_rgColShare); iCol++)
		{
			lvc.iSubItem = iCol;
			lvc.cx = lpCol->dwWidth;
			lvc.pszText = lpCol->lpsz;
			if (ListView_InsertColumn(hwnd, iCol, &lvc) == -1)
				return;
			lpCol++;
		}
	}

	UpdateShareList(hwnd);
}


//****************************************************************************
//
// LRESULT CALLBACK ShareDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK ShareDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);
		InitShareList(hdlg);
		return TRUE;
	}
	
	case WM_COMMAND:
	{
		UINT wCmd = GET_WM_COMMAND_ID(wParam, lParam);
		switch (wCmd)
		{
		case IDOK:
		case IDCANCEL:
			FreeShareList(GetDlgItem(hdlg, IDL_APP));
			EndDialog(hdlg, 1);
			return TRUE;

		case IDB_UPDATE:
			UpdateShareList(GetDlgItem(hdlg, IDL_APP));
			break;

		case IDB_SHARE:
		case IDB_UNSHARE:
		{
			HRESULT hr;
			NM_SHAPP_STATE uState;
			HWND hwndLv = GetDlgItem(hdlg, IDL_APP);
			int iItem = ListView_GetNextItem(hwndLv, -1, LVNI_ALL | LVNI_SELECTED);
			if (-1 == iItem)
				break;

			LV_ITEM lvi;
			ClearStruct(&lvi);
			lvi.iItem = iItem;
			lvi.mask = LVIF_PARAM;
			if (!ListView_GetItem(hwndLv, &lvi))
				break;

			INmSharableApp * pApp = (INmSharableApp *) lvi.lParam;
			ASSERT(NULL != pApp);
			hr = pApp->GetState(&uState);
			if (FAILED(hr))
			{
				ERROR_MSG("Invalid hwnd? hr=%s", GetHrSz(hr));
				break;
			}
			TRACE_MSG("hwnd state=%d", uState);
			hr = pApp->SetState((IDB_SHARE == wCmd) ? NM_SHAPP_SHARED : NM_SHAPP_NOT_SHARED);
			return TRUE;
		}

		default:
			return TRUE;
		} /* switch (cmd) */
	}

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgShare(VOID)
//
//****************************************************************************

BOOL DlgShare(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_SHARE),
		ghwndMain, (DLGPROC)ShareDlgProc));
}


//****************************************************************************
//
// VOID _InitGuidLBox(HWND hwnd)
//
//****************************************************************************

VOID _InitGuidLBox(HWND hwnd)
{
	HRESULT hr;
	DWORD dwIndex;
	GUID  guid;
	TCHAR szGuid[MAX_PATH];
	INmSysInfo * pSysInfo;

	hr = g_pMgr->GetSysInfo(&pSysInfo);
	if (FAILED(hr))
	{
		ERROR_MSG("GetSysInfo Failed hr=%s", GetHrSz(hr));
		return;
	}

	// TODO: use INmMgr::GetNmApp to enumerate local items

	GuidToSz((GUID *)&g_guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 

	GuidToSz((GUID *)&g_guidNM2Chat, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 

	memset(&guid, 0x00, sizeof(GUID));
	GuidToSz((GUID *)&guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 
	
	memset(&guid, 0x11, sizeof(GUID));
	GuidToSz((GUID *)&guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 
	
	memset(&guid, 0x22, sizeof(GUID));
	GuidToSz((GUID *)&guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 

	
	SendMessage(hwnd, CB_SETCURSEL, 0, 0); 
	pSysInfo->Release();
}


//****************************************************************************
//
// LRESULT CALLBACK LaunchDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK LaunchDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);

		InitUserLBox(hdlg, TRUE);
		_InitGuidLBox(GetDlgItem(hdlg, IDL_GUID));
		return TRUE;
	}
	
	case WM_DRAWITEM: 
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		{
			// Get the Member
			INmMember * pMember = NULL;
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				if (NULL != pUser)
				{
					pMember = pUser->pMember;
					if (S_OK == pMember->IsSelf())
						pMember = NULL; // everyone
				}
			}

			// Get the Guid
			GUID guid;
			TCHAR szGuid[MAX_PATH];
			GetDlgItemText(hdlg, IDL_GUID, szGuid, CCHMAX(szGuid));
			SzToGuid(szGuid, &guid);

			INmConference * pConference = GetCurrentConference();
			HRESULT hr;
			if (NULL == pConference)
			{
				hr = E_FAIL;
			}
			else
			{
				hr = pConference->LaunchRemote(guid, pMember);
			}

			if (FAILED(hr))
			{
				ERROR_MSG("LaunchRemote Failed hr=%s", GetHrSz(hr));
			}
			else
			{
				EndDialog(hdlg, 1);
			}
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hdlg, 0);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgLaunch(VOID)
//
//****************************************************************************

BOOL DlgLaunch(VOID)
{
	if (NULL == GetCurrentConference())
		return FALSE;

	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_LAUNCH),
		ghwndMain, (DLGPROC)LaunchDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK EjectDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK EjectDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);

		InitUserLBox(hdlg, FALSE);
		return TRUE;
	}
	
	case WM_DRAWITEM: 
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		{
			// Get the Member
			INmMember * pMember = NULL;
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				if (NULL != pUser)
					pMember = pUser->pMember;
			}

			if (NULL != pMember)
			{
				HRESULT hr = pMember->Eject();

				if (FAILED(hr))
				{
					ERROR_MSG("LaunchRemote Failed hr=%s", GetHrSz(hr));
				}
			}

			EndDialog(hdlg, 1);
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hdlg, 0);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgEject(VOID)
//
//****************************************************************************

BOOL DlgEject(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_EJECT),
		ghwndMain, (DLGPROC)EjectDlgProc));
}


const int iMinVideoQuality = NM_VIDEO_MIN_QUALITY;
const int iMaxVideoQuality = NM_VIDEO_MAX_QUALITY;

const int iMinAutoSize = 0;
const int iMaxAutoSize = 400;

//****************************************************************************
//
// CLASS CVideoDlg
//
//****************************************************************************

class CVideoDlg
{
private:
	HWND m_hDlg;
	CVideoNotify *m_pVideoNotify[10];
	BOOL m_fPaused;

	INmChannelVideo* CVideoDlg::GetChannel(int iChnl);
	INmChannelVideo* CVideoDlg::GetCurrentChannel();

	VOID FormatDialog();
	VOID SourceDialog();
	VOID SetFrameSize(DWORD dwFrameSize);
	VOID SetQuality(DWORD dwQuality);
	VOID Pause(BOOL fPause);
	VOID ShowWindow(BOOL fShow);
	VOID SetTopMost(BOOL fTopMost);
	VOID AdjustSize(int cx, int cy);
	VOID AdjustPosition(int cx, int cy);
	VOID SetAutoSize(DWORD dwSize);
	VOID Activate(BOOL fActive);

	BOOL ProcessInitDialog(HWND hDdlg);
	BOOL ProcessCommand(WPARAM wParam, LPARAM lParam);
	BOOL ProcessQualitySlider(WPARAM wParam);
	BOOL ProcessAutoSizeSlider(WPARAM wParam);
	BOOL ProcessDestroy();

public:
	CVideoDlg();
	VOID UpdateControls();
	VOID UpdateStatus(DWORD dwProperty);

	static LRESULT CALLBACK DlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static VOID StateChanged(NM_VIDEO_STATE uState, DWORD dwParam);
	static VOID PropertyChanged(DWORD dwProperty, DWORD dwParam);
};


//****************************************************************************
//
// Constructor
//
//****************************************************************************

CVideoDlg::CVideoDlg() :
	m_fPaused(TRUE)
{
}


//****************************************************************************
//
// INmChannelVideo* CVideoDlg::GetChannel(int iChnl)
//
//****************************************************************************

INmChannelVideo* CVideoDlg::GetChannel(int iChnl)
{
	PUSER pUser = (PUSER) SendDlgItemMessage(m_hDlg, IDL_USERS,
		CB_GETITEMDATA, (WPARAM) iChnl, 0);
	return pUser->m_pChannelVideo;
}


//****************************************************************************
//
// INmChannelVideo* CVideoDlg::GetCurrentChannel()
//
//****************************************************************************

INmChannelVideo* CVideoDlg::GetCurrentChannel()
{
	int iSel = SendDlgItemMessage(m_hDlg, IDL_USERS, CB_GETCURSEL, 0, 0);
	if (CB_ERR != iSel)
	{
		return GetChannel(iSel);
	}
	return NULL;
}


//****************************************************************************
//
// VOID CVideoDlg::UpdateControls()
//
//****************************************************************************

VOID CVideoDlg::UpdateControls()
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		BOOL fCapturing = FALSE;
	    BOOL fIncoming  = (S_OK == pChannel->IsIncoming());
		LPTSTR lpszState = "Unknown";
		NM_VIDEO_STATE uState;
		pChannel->GetState(&uState);
		switch (uState)
		{
		case NM_VIDEO_IDLE:
			lpszState = "Idle";
			break;
		case NM_VIDEO_LOCAL_PAUSED:
			lpszState = "Local Paused";
			break;
		case NM_VIDEO_PREVIEWING:
			lpszState = "Previewing";
			fCapturing = !fIncoming;
			break;
		case NM_VIDEO_TRANSFERRING:
			lpszState = "Transferring";
			fCapturing = !fIncoming;
			break;
		case NM_VIDEO_BOTH_PAUSED:
			lpszState = "Both Paused";
			break;
		case NM_VIDEO_REMOTE_PAUSED:
			lpszState = "Remote Paused";
			fCapturing = !fIncoming;
			break;
		}
		SetDlgItemText(m_hDlg, IDC_VIDEO_STATE, lpszState);

		EnableWindow(GetDlgItem(m_hDlg, IDC_VIDEO_SMALL), !fIncoming);
		EnableWindow(GetDlgItem(m_hDlg, IDC_VIDEO_MEDIUM), !fIncoming);
		EnableWindow(GetDlgItem(m_hDlg, IDC_VIDEO_LARGE), !fIncoming);
        
        ULONG uValue;
		pChannel->GetProperty(NM_VIDPROP_IMAGE_PREFERRED_SIZE, &uValue);
		switch (uValue)
		{
		case 0x01:
			uValue = 0;
			break;
		default:
		case 0x02:
			uValue = 1;
			break;
		case 0x04:
			uValue = 2;
			break;
		}
		CheckRadioButton(m_hDlg,
				IDC_VIDEO_SMALL,
				IDC_VIDEO_LARGE,
				IDC_VIDEO_SMALL + uValue);

		if (fCapturing)
		{
			pChannel->GetProperty(NM_VIDPROP_CAMERA_DIALOG, &uValue);
		}
		else
		{
			uValue = 0;
		}
		EnableWindow(GetDlgItem(m_hDlg, IDC_VIDEO_SOURCE), uValue & 0x01);
		EnableWindow(GetDlgItem(m_hDlg, IDC_VIDEO_FORMAT), uValue & 0x02);

		uValue = (S_OK == pChannel->IsActive());
		EnableWindow(GetDlgItem(m_hDlg, IDC_ACTIVE), fIncoming || uValue);
		CheckDlgButton(m_hDlg, IDC_ACTIVE, uValue ? BST_CHECKED : BST_UNCHECKED);

		pChannel->GetProperty(NM_VIDPROP_PAUSE, &uValue);
		CheckDlgButton(m_hDlg, IDC_PAUSE, uValue ? BST_CHECKED : BST_UNCHECKED);

		EnableWindow(GetDlgItem(m_hDlg, IDC_VIDEO_QUALITY), fIncoming);
		if (fIncoming)
		{
			pChannel->GetProperty(NM_VIDPROP_IMAGE_QUALITY, &uValue);
		}
		else
		{
			uValue = 0;
		}
		SendDlgItemMessage (m_hDlg, IDC_VIDEO_QUALITY, TBM_SETRANGE, FALSE,
			MAKELONG (iMinVideoQuality, iMaxVideoQuality ));

		SendDlgItemMessage (m_hDlg, IDC_VIDEO_QUALITY, TBM_SETTICFREQ, 
			( iMaxVideoQuality - iMinVideoQuality ) / 8, 0 );

		SendDlgItemMessage (m_hDlg, IDC_VIDEO_QUALITY, TBM_SETPAGESIZE, 
			0, ( iMaxVideoQuality - iMinVideoQuality ) / 8 );

		SendDlgItemMessage (m_hDlg, IDC_VIDEO_QUALITY, TBM_SETLINESIZE, 
			0, 1 );

		SendDlgItemMessage (m_hDlg, IDC_VIDEO_QUALITY, TBM_SETPOS, TRUE,
							iMaxVideoQuality - uValue );

		pChannel->GetProperty(NM_VIDPROP_WINDOW_AUTO_SIZE, &uValue);
		SetDlgItemInt(m_hDlg, IDC_E_AUTOSIZE, uValue, FALSE);

		SendDlgItemMessage (m_hDlg, IDC_S_AUTOSIZE, TBM_SETRANGE, FALSE,
			MAKELONG (iMinAutoSize, iMaxAutoSize ));

		SendDlgItemMessage (m_hDlg, IDC_S_AUTOSIZE, TBM_SETTICFREQ, 
			100, 0 );

		SendDlgItemMessage (m_hDlg, IDC_S_AUTOSIZE, TBM_SETPAGESIZE, 
			0, 100 );

		SendDlgItemMessage (m_hDlg, IDC_S_AUTOSIZE, TBM_SETLINESIZE, 
			0, 10 );

		SendDlgItemMessage (m_hDlg, IDC_S_AUTOSIZE, TBM_SETPOS, TRUE,
							uValue );

		pChannel->GetProperty(NM_VIDPROP_WINDOW_VISIBLE, &uValue);
		CheckDlgButton(m_hDlg, IDC_VISIBLE, uValue ? BST_CHECKED : BST_UNCHECKED);

		pChannel->GetProperty(NM_VIDPROP_WINDOW_TOP_MOST, &uValue);
		CheckDlgButton(m_hDlg, IDC_TOPMOST, uValue ? BST_CHECKED : BST_UNCHECKED);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::UpdateStatus(DWORD dwProperty)
//
//****************************************************************************

VOID CVideoDlg::UpdateStatus(DWORD dwProperty)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		ULONG uValue;
		pChannel->GetProperty((NM_VIDPROP)dwProperty, &uValue);

		TCHAR szProperty[MAX_PATH];

		switch (dwProperty)
		{
		case NM_VIDPROP_PAUSE:
			wsprintf(szProperty, "Pause: %d", uValue);
			break;
		case NM_VIDPROP_WINDOW_AUTO_SIZE:
			wsprintf(szProperty, "Window Auto Size: %d", uValue);
			break;
		case NM_VIDPROP_WINDOW_SIZE:
			wsprintf(szProperty, "Window Size: (%d, %d)",
				(short)LOWORD(uValue), (short)HIWORD(uValue));
			break;
		case NM_VIDPROP_WINDOW_POSITION:
			wsprintf(szProperty, "Window Position: (%d, %d)",
				(short)LOWORD(uValue), (short)HIWORD(uValue));
			break;
		case NM_VIDPROP_WINDOW_TOP_MOST:
			wsprintf(szProperty, "Window Top Most: %d", uValue);
			break;
		case NM_VIDPROP_WINDOW_VISIBLE:
			wsprintf(szProperty, "Window Visible: %d", uValue);
			break;
		case NM_VIDPROP_IMAGE_PREFERRED_SIZE:
			wsprintf(szProperty, "Image Prefered Size: %d", uValue);
			break;
		case NM_VIDPROP_IMAGE_QUALITY:
			wsprintf(szProperty, "Image Quality: %d", uValue);
			break;
		case NM_VIDPROP_CAMERA_DIALOG:
			wsprintf(szProperty, "Camera Dialog: %d", uValue);
			break;
		default:
			wsprintf(szProperty, "Unknown Property: %d", dwProperty);
			break;
		}
		SetDlgItemText(m_hDlg, IDC_VIDEO_STATUS, szProperty);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::SourceDialog()
//
//****************************************************************************

VOID CVideoDlg::SourceDialog()
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		pChannel->SetProperty(NM_VIDPROP_CAMERA_DIALOG, NM_VIDEO_SOURCE_DIALOG);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::FormatDialog()
//
//****************************************************************************

VOID CVideoDlg::FormatDialog()
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		pChannel->SetProperty(NM_VIDPROP_CAMERA_DIALOG, NM_VIDEO_FORMAT_DIALOG);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::SetFrameSize(DWORD dwFrameSize)
//
//****************************************************************************

VOID CVideoDlg::SetFrameSize(DWORD dwFrameSize)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		pChannel->SetProperty(NM_VIDPROP_IMAGE_PREFERRED_SIZE, dwFrameSize);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::SetQuality(DWORD dwQuality)
//
//****************************************************************************

VOID CVideoDlg::SetQuality(DWORD dwQuality)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		pChannel->SetProperty(NM_VIDPROP_IMAGE_QUALITY, iMaxVideoQuality - dwQuality);
	}
}


//****************************************************************************
//
// BOOL CVideoDlg::ProcessInitDialog(HWND hDlg)
//
//****************************************************************************

BOOL CVideoDlg::ProcessInitDialog(HWND hDlg)
{
	m_hDlg = hDlg;

	CenterWindow(hDlg, ghwndMain);

	InitUserLBox(hDlg, FALSE);

	UpdateControls();

	int iCnt = SendDlgItemMessage(hDlg, IDL_USERS, CB_GETCOUNT, 0, 0);

	for (int i = 0; i < iCnt; ++i)
	{
		INmChannelVideo * pChannel = GetChannel(i);
		if (NULL != pChannel)
		{
			m_pVideoNotify[i] = new CVideoNotify(CVideoDlg::StateChanged, CVideoDlg::PropertyChanged, (DWORD)this);
			m_pVideoNotify[i]->Connect(pChannel);
		}
	}

	return TRUE;
}


//****************************************************************************
//
// VOID CVideoDlg::Pause(BOOL fPause)
//
//****************************************************************************
	
VOID CVideoDlg::Pause(BOOL fPause)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		pChannel->SetProperty(NM_VIDPROP_PAUSE, fPause);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::ShowWindow(BOOL fShow)
//
//****************************************************************************

VOID CVideoDlg::ShowWindow(BOOL fShow)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		DWORD dwShow = fShow;
		pChannel->SetProperty(NM_VIDPROP_WINDOW_VISIBLE, dwShow);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::SetTopMost(BOOL fTopMost)
//
//****************************************************************************

VOID CVideoDlg::SetTopMost(BOOL fTopMost)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		DWORD dwTopMost = fTopMost;
		pChannel->SetProperty(NM_VIDPROP_WINDOW_TOP_MOST, dwTopMost);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::AdjustSize(int cx, int cy)
//
//****************************************************************************

VOID CVideoDlg::AdjustSize(int cx, int cy)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		DWORD dwSize;
		WORD x, y;
		pChannel->GetProperty(NM_VIDPROP_WINDOW_SIZE, &dwSize);
		x = LOWORD(dwSize) + cx;
		y = HIWORD(dwSize) + cy;
		dwSize = MAKELONG(x, y);
		pChannel->SetProperty(NM_VIDPROP_WINDOW_SIZE, dwSize);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::AdjustPosition(int cx, int cy)
//
//****************************************************************************

VOID CVideoDlg::AdjustPosition(int cx, int cy)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		DWORD dwPos;
		WORD x, y;
		pChannel->GetProperty(NM_VIDPROP_WINDOW_POSITION, &dwPos);
		x = LOWORD(dwPos) + cx;
		y = HIWORD(dwPos) + cy;
		dwPos = MAKELONG(x, y);
		pChannel->SetProperty(NM_VIDPROP_WINDOW_POSITION, dwPos);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::SetAutoSize(DWORD dwSize)
//
//****************************************************************************

VOID CVideoDlg::SetAutoSize(DWORD dwSize)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		pChannel->SetProperty(NM_VIDPROP_WINDOW_AUTO_SIZE, dwSize);
	}
}


//****************************************************************************
//
// VOID CVideoDlg::Activate(BOOL fActive)
//
//****************************************************************************

VOID CVideoDlg::Activate(BOOL fActive)
{
	INmChannelVideo * pChannel = GetCurrentChannel();
	if (NULL != pChannel)
	{
		pChannel->SetActive(fActive);
	}
}


//****************************************************************************
//
// BOOL CVideoDlg::ProcessCommand(WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

BOOL CVideoDlg::ProcessCommand(WPARAM wParam, LPARAM lParam)
{
	switch (GET_WM_COMMAND_ID(wParam, lParam))
	{
	case IDOK:
	case IDCANCEL:
		EndDialog(m_hDlg, 1);
		break;
	
	case IDC_ACTIVE:
		Activate(IsDlgButtonChecked(m_hDlg, IDC_ACTIVE));
		break;

	case IDB_UPDATE:
		UpdateControls();
		break;

	case IDC_VIDEO_SOURCE:
		SourceDialog();
		break;

	case IDC_VIDEO_FORMAT:
		FormatDialog();
		break;

	case IDC_PAUSE:
		Pause(IsDlgButtonChecked(m_hDlg, IDC_PAUSE));
		break;

	case IDL_USERS:
		UpdateControls();
		break;

	case IDC_VIDEO_SMALL:
		SetFrameSize(NM_VIDEO_SMALL);
		break;
	case IDC_VIDEO_MEDIUM:
		SetFrameSize(NM_VIDEO_MEDIUM);
		break;
	case IDC_VIDEO_LARGE:
		SetFrameSize(NM_VIDEO_LARGE);
		break;

	case IDC_VISIBLE:
		ShowWindow(IsDlgButtonChecked(m_hDlg, IDC_VISIBLE));
		break;

	case IDC_TOPMOST:
		SetTopMost(IsDlgButtonChecked(m_hDlg, IDC_TOPMOST));
		break;

	case IDC_TALL:
		AdjustSize(0, 10);
		break;
	case IDC_SHORT:
		AdjustSize(0, -10);
		break;
	case IDC_THIN:
		AdjustSize(-10, 0);
		break;
	case IDC_WIDE:
		AdjustSize(10, 0);
		break;

	case IDC_UP:
		AdjustPosition(0, -10);
		break;
	case IDC_DOWN:
		AdjustPosition(0, 10);
		break;
	case IDC_LEFT:
		AdjustPosition(-10, 0);
		break;
	case IDC_RIGHT:
		AdjustPosition(10, 0);
		break;

	default:
		return FALSE;
	} /* switch (cmd) */

	return TRUE;
}
		

//****************************************************************************
//
// BOOL CVideoDlg::ProcessQualitySlider(WPARAM wParam)
//
//****************************************************************************

BOOL CVideoDlg::ProcessQualitySlider(WPARAM wParam)
{
	if (TB_ENDTRACK == LOWORD(wParam))
	{
		DWORD dwValue = SendDlgItemMessage( m_hDlg, IDC_VIDEO_QUALITY,
					TBM_GETPOS, 0, 0 );

		{
			SetQuality(dwValue);
			return TRUE;
		}
	}
	return FALSE;
}


//****************************************************************************
//
// BOOL CVideoDlg::ProcessAutoSizeSlider(WPARAM wParam)
//
//****************************************************************************

BOOL CVideoDlg::ProcessAutoSizeSlider(WPARAM wParam)
{
	if (TB_ENDTRACK == LOWORD(wParam))
	{
		DWORD dwValue = SendDlgItemMessage( m_hDlg, IDC_S_AUTOSIZE,
					TBM_GETPOS, 0, 0 );

		{
			SetAutoSize(dwValue);
			return TRUE;
		}
	}
	return FALSE;
}


//****************************************************************************
//
// BOOL CVideoDlg::ProcessDestroy()
//
//****************************************************************************

BOOL CVideoDlg::ProcessDestroy()
{
	int iCnt = SendDlgItemMessage(m_hDlg, IDL_USERS, CB_GETCOUNT, 0, 0);
	for (int i = 0; i < iCnt; ++i)
	{
		m_pVideoNotify[i]->Disconnect();
		m_pVideoNotify[i]->Release();
	}
	return TRUE;
}

//****************************************************************************
//
// LRESULT CALLBACK CVideoDlg::DlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK CVideoDlg::DlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CVideoDlg* pVideoDlg = (CVideoDlg*)GetWindowLong(hdlg, GWL_USERDATA);

	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetWindowLong(hdlg, GWL_USERDATA, lParam);

		pVideoDlg = (CVideoDlg*)lParam;
		return pVideoDlg->ProcessInitDialog(hdlg);
	
	case WM_DRAWITEM: 
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;

	case WM_COMMAND:
		return pVideoDlg->ProcessCommand(wParam, lParam);

	case WM_VSCROLL:
		return pVideoDlg->ProcessQualitySlider(wParam);

	case WM_HSCROLL:
		return pVideoDlg->ProcessAutoSizeSlider(wParam);

	case WM_DESTROY:
		return pVideoDlg->ProcessDestroy();

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// VOID CVideoDlg::StateChanged(NM_VIDEO_STATE uState, DWORD dwParam)
//
//****************************************************************************

VOID CVideoDlg::StateChanged(NM_VIDEO_STATE uState, DWORD dwParam)
{
	((CVideoDlg*)dwParam)->UpdateControls();
}


//****************************************************************************
//
// VOID CVideoDlg::PropertyChanged(DWORD dwProperty, DWORD dwParam)
//
//****************************************************************************

VOID CVideoDlg::PropertyChanged(DWORD dwProperty, DWORD dwParam)
{
	((CVideoDlg*)dwParam)->UpdateControls();
	((CVideoDlg*)dwParam)->UpdateStatus(dwProperty);
}


//****************************************************************************
//
// BOOL DlgVideo(VOID)
//
//****************************************************************************

BOOL DlgVideo(VOID)
{
	CVideoDlg VideoDlg;

	return (0 == DialogBoxParam(ghInst, MAKEINTRESOURCE(IDD_VIDEO),
		ghwndMain, (DLGPROC)CVideoDlg::DlgProc, (LPARAM)&VideoDlg));
}
