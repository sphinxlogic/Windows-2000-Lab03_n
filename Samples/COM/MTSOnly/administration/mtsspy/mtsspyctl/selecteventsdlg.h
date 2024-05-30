
/******************************************************************************\
********************************************************************************
* Filename: SelectEventsDlg.h
*
* Description: Declaration of the CSelectEventsDlg
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


#ifndef __SELECTEVENTSDLG_H_
#define __SELECTEVENTSDLG_H_

#include "resource.h"       // main symbols
class CMtsSpy;
/////////////////////////////////////////////////////////////////////////////
// CSelectEventsDlg
class CSelectEventsDlg : 
	public CDialogImpl<CSelectEventsDlg>
{
private:
	MapStringToPackageInfo * m_map;
	CMtsSpy * m_pSpyObj;

public:
	HRESULT GetDisplayName(EventEnum e, BSTR * sDisplayName);
	void ResetEventList();
	CSelectEventsDlg();
	CSelectEventsDlg(MapStringToPackageInfo * spMap, CMtsSpy * pSpyObj)
	{
		m_map = spMap;
		m_pSpyObj = pSpyObj;
	}
	~CSelectEventsDlg();
	BOOL GetRunningAsps();

	enum { IDD = IDD_SELECTEVENTSDLG };

BEGIN_MSG_MAP(CSelectEventsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(IDC_PACKAGES, OnSelectPackages)
	COMMAND_ID_HANDLER(IDC_ADD_SINK, OnAddSink)
	COMMAND_ID_HANDLER(IDC_REMOVE_FROM_SINK, OnRemoveSink)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroyDlg)
	COMMAND_ID_HANDLER(IDC_EVENTS, EventListHandler)
	COMMAND_ID_HANDLER(IDC_SINKS, SinkListHandler)

END_MSG_MAP()

//
//	Message Handles
//
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelectPackages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAddSink(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnRemoveSink(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDestroyDlg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT EventListHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT SinkListHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);




};

#endif //__SELECTEVENTSDLG_H_

