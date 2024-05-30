//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
//
// Author: S.R.
//         Support Engineer - Internet Client SDK
//         Microsoft Developer Support
//
// AboutBox.h : Declaration of the CAboutBox
//--------------------------------------------------------------------------

#ifndef __ABOUTBOX_H_
#define __ABOUTBOX_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAboutBox
class CAboutBox : 
	public CDialogImpl<CAboutBox>
{
public:
	CAboutBox(HWND hwndParent);
	~CAboutBox();

	enum { IDD = IDD_ABOUTBOX };

BEGIN_MSG_MAP(CAboutBox)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()

private:
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

   HWND m_hwndParent;
};

#endif //__ABOUTBOX_H_
