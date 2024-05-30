
/******************************************************************************\
********************************************************************************
* Filename: RmOptionsDlg.h
*
* Description: Declaration of the CRmOptionsDlg -- used for modifying the options
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

#ifndef __RMOPTIONSDLG_H_
#define __RMOPTIONSDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRmOptionsDlg
class CRmOptionsDlg : 
	public CDialogImpl<CRmOptionsDlg>
{
private:
	
	CRmOptions  * m_pOptions;
	BOOL m_bCreatedOptions;

public:
	BOOL CheckDirectory(BSTR sDir);
	void ShowMessage();
	CComBSTR &GetLogDir(){return m_pOptions -> GetLogDir();}
	CComBSTR &GetRecoverDir(){return m_pOptions -> GetRecDir();}
		
	CRmOptionsDlg();
	CRmOptionsDlg(CRmOptions * pOptions){_ASSERTE(pOptions); m_pOptions = pOptions;m_bCreatedOptions = FALSE;}
	~CRmOptionsDlg();
	
	enum { IDD = IDD_RMOPTIONSDLG };

BEGIN_MSG_MAP(CRmOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

};

#endif //__RMOPTIONSDLG_H_
