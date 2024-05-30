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
// AboutBox.cpp : Implementation of CAboutBox
//--------------------------------------------------------------------------
#include "stdafx.h"
#include "AboutBox.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutBox

CAboutBox::CAboutBox(HWND hwndParent)
{
   m_hwndParent = hwndParent;
}

CAboutBox::~CAboutBox()
{
}

LRESULT CAboutBox::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   CenterWindow(m_hwndParent);

	return 1;  // Let the system set the focus
}

LRESULT CAboutBox::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CAboutBox::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

