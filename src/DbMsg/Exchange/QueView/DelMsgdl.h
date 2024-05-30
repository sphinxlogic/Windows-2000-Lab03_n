// delmsgdl.h : header file
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.

/////////////////////////////////////////////////////////////////////////////
// CDelMsgDlg dialog
#include "resource.h"

class CDelMsgDlg : public CDialog
{
// Construction
public:
	CDelMsgDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDelMsgDlg)
	enum { IDD = IDD_DELETE_MESSAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDelMsgDlg)
	afx_msg void OnCmdDeleteByGateway();
	afx_msg void OnCmdDeleteNow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
