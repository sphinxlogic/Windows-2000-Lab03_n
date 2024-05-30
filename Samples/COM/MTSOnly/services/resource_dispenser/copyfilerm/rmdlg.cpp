
/******************************************************************************\
********************************************************************************
* Filename: RmDlg.cpp
*
* Description: Implementation of CRmDlg
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/
#include "stdafx.h"
#include "RmDlg.h"
#include "rmoptions.h"
#include "RmOptionsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRmDlg

CRmDlg::CRmDlg()
{
	m_pOptions = NULL;
}

CRmDlg::~CRmDlg()
{
}

LRESULT CRmDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	_ASSERTE(m_pOptions);
	SetDlgItemText(IDC_LOGDIR, m_pOptions -> GetLogDir());	
	SetDlgItemText(IDC_RECOVERDIR, m_pOptions -> GetRecDir());

	return 1;  // Let the system set the focus
}

LRESULT CRmDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnExit(wNotifyCode, wID, hWndCtl, bHandled);

}

LRESULT CRmDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnExit(wNotifyCode, wID, hWndCtl, bHandled);
}

void CRmDlg::SetUsageCount(long lCount)
{
	if (!m_hWnd)
		return;

	TCHAR sz[16];
	wsprintf((TCHAR *)sz,L"%ld", lCount);
	SetDlgItemText(IDC_USAGE, sz);
	UpdateWindow();
}

LRESULT CRmDlg::OnExit(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
	
	long lLockCount = _Module.GetLockCount();
	if (lLockCount > 1)
	{
	
		TCHAR sz[128];
		wsprintf((TCHAR *)sz,L"There are outstanding references on this object!\n\nLockCount is: %ld\nClosing it will probably cause a GP Fault!\nDo you wish to close the RM?", lLockCount - 1);
		if (::MessageBox(NULL, sz,L"File Resource Manager", MB_ICONSTOP|MB_YESNO) == IDNO)
			return 0;

		try
		{
			while (_Module.Unlock() > 1)
				;
		}
		catch(...)
		{


		}

	}
	else
	{

		
		if (::MessageBox(NULL, L"Do you wish to close the RM?",L"File Resource Manager", MB_ICONQUESTION|MB_YESNO) == IDNO)
			return 0;

	}

	
	bHandled = TRUE;
	DWORD dwThreadID = GetCurrentThreadId();
	PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
	return 0;
}

void CRmDlg::SetLockCount(long lCount)
{

	if (!m_hWnd)
		return;

	TCHAR sz[16];
	wsprintf((TCHAR *)sz,L"%ld", lCount);
	SetDlgItemText(IDC_LOCKS, sz);
	UpdateWindow();
}
LRESULT CRmDlg::OnOptions(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
	_ASSERTE(m_pOptions);
	CRmOptionsDlg dlg(m_pOptions);
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_LOGDIR, dlg.GetLogDir());
		SetDlgItemText(IDC_RECOVERDIR, dlg.GetRecoverDir());

	}				
	return 1;  // Let the system set the focus
}
