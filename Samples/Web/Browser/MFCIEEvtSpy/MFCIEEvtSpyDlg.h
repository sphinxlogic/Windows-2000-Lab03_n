/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/




// MFCIEEvtSpyDlg.h : header file
//
// This source code is provided as-is, without warranty.
//
// Created by S. R.
// Microsoft Developer Support - Internet Client SDK
/////////////////////////////////////////////////////////

//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_MFCIEEVTSPYDLG_H__A6543949_9D7F_11D1_ABEE_00D049C10000__INCLUDED_)
#define AFX_MFCIEEVTSPYDLG_H__A6543949_9D7F_11D1_ABEE_00D049C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ExDisp.h>  // Contains declaration for IWebBrowser2
#include "IE4Events.h"

/////////////////////////////////////////////////////////////////////////////
// CMFCIEEvtSpyDlg dialog

class CMFCIEEvtSpyDlg : public CDialog
{
// Construction
public:
	CMFCIEEvtSpyDlg(CWnd* pParent = NULL);	// standard constructor
	~CMFCIEEvtSpyDlg();

   enum ListBoxType { IE4ListBox, WBListBox };

   void OnIE4Quit();
   void AddEventToList(ListBoxType lst, CString strEvent);

// Dialog Data
	//{{AFX_DATA(CMFCIEEvtSpyDlg)
	enum { IDD = IDD_MFCIEEVTSPY_DIALOG };
	CButton	m_btnStartIE;
	CListBox	m_lstIE4Events;
	CListBox	m_lstWBEvents;
	CWebBrowser2 m_webBrowser;
	CString	m_strAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCIEEvtSpyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CIE4Events* m_pIE4Events;
   IWebBrowser2* m_pIE;
   IConnectionPoint* m_pConnectionPoint;   // For DIID_DWebBrowserEvents2

   DWORD m_dwCookie;
   int   m_nIELstBoxHorizExtent;
   int   m_nWBLstBoxHorizExtent;
   HICON m_hIcon;

   void ShutDownIE4EventSink();

	// Generated message map functions
	//{{AFX_MSG(CMFCIEEvtSpyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartIE();
	afx_msg void OnExit();
	afx_msg void OnGo();
	afx_msg void OnDestroy();
	afx_msg void OnClearListboxes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   // WebBrowser event handlers
   afx_msg void OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
   afx_msg void OnCommandStateChange(long lCommand, BOOL bEnable);
   afx_msg void OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
   afx_msg void OnDownloadComplete();
   afx_msg void OnNavigateComplete2(LPDISPATCH pDisp, VARIANT* URL);
   afx_msg void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
   afx_msg void OnProgressChange(long lProgress, long lProgressMax);
   afx_msg void OnQuit();
   afx_msg void OnStatusTextChange(LPCTSTR lpszText);
   afx_msg void OnTitleChange(LPCTSTR lpszText);

   // Event map declaration for WebBrowser control events.
   DECLARE_EVENTSINK_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCIEEVTSPYDLG_H__A6543949_9D7F_11D1_ABEE_00D049C10000__INCLUDED_)
