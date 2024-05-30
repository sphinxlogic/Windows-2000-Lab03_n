
/******************************************************************************\
********************************************************************************
* Filename: RmDlg.h
*
* Description:: Declaration of the CRmDlg
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

#ifndef __RMDLG_H_
#define __RMDLG_H_

#include "resource.h"       // main symbols
class CRmOptions;
/////////////////////////////////////////////////////////////////////////////
// CRmDlg
class CRmDlg : 
	public CDialogImpl<CRmDlg>
{

private:
			
	CComBSTR m_sRecoverDir;
	CComBSTR m_sLogDir;
	CRmOptions * m_pOptions;

public:
	void SetLockCount(long lCount);
	CRmDlg();
	~CRmDlg();

	CRmDlg(CRmOptions * pOpt)
	{
		m_pOptions = pOpt;
	}

	void SetOptions(CRmOptions * pOpt)
	{
		m_pOptions = pOpt;
	}

	CComBSTR &GetLogDir(){return m_sLogDir;}
	CComBSTR &GetRecoverDir(){return m_sRecoverDir;}

	enum { IDD = IDD_RMDLG };

BEGIN_MSG_MAP(CRmDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)	
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(ID_FILE_EXIT, OnExit)
	COMMAND_ID_HANDLER(WM_CLOSE, OnExit)
	COMMAND_ID_HANDLER(ID_OPTIONS, OnOptions)

END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnExit(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
	LRESULT OnOptions(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
	
	
	void SetUsageCount(long lCount);
};

#endif //__RMDLG_H_
