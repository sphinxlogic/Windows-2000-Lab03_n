
/******************************************************************************\
********************************************************************************
* Filename: FileRmClientDlg.h
*
* Description: header file
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

/////////////////////////////////////////////////////////////////////////////
// CFileRmClientDlg dialog
//{{AFX_INCLUDES()
#include "cpicturectl1.h"
//}}AFX_INCLUDES


class CFileRmClientDlg : public CDialog
{
// Construction
public:
	CFileRmClientDlg(CWnd* pParent = NULL);	// standard constructor
	// Dialog Data
	//{{AFX_DATA(CFileRmClientDlg)
	enum { IDD = IDD_FILERMCLIENT_DIALOG };
	CString	m_sSource;
	CString	m_sImgFileName;
	CString	m_sMainColor;
	CString	m_sTheme;
	CString	m_sDescription;
	CString	m_sMsg;
	CString	m_sDest;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileRmClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CNewPictureCtl m_ctlPict;
	// Generated message map functions
	//{{AFX_MSG(CFileRmClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCopy();
	afx_msg void OnCopyDirectory();
	afx_msg void OnInsertData();
	afx_msg void OnPictureChanged(BSTR FAR* PictureFileName);
	afx_msg void OnSelectPicture();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
