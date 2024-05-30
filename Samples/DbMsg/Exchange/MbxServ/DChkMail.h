//--dchkmail.h----------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CCheckMailDlg dialog

class CCheckMailDlg : public CDialog
{
// Construction
public:
	CCheckMailDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckMailDlg)
	enum { IDD = IDD_VOXSERV_DIALOG };
	CString	m_strAlias;
	CString	m_strPassword;
	//}}AFX_DATA
	COwnerDrawListBox	m_lbMail;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckMailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
	LPABCONT m_lpGAL;	// Global address book
	LPMAPISESSION m_lpSession;
	LPMDB	m_lpMDB;

// Implementation
protected:
	HICON m_hIcon;

	HRESULT HrDispMailboxSubjects(LPMDB  lpMDB);
	HRESULT HrGetMsgList(LPMAPITABLE lpTable, LONG cMaxNRows, LPSRowSet *lppRows);
	HRESULT HrCheckPassword (SBinaryArray * lpbaExtData, LPCTSTR szPassword);

	// Generated message map functions
	//{{AFX_MSG(CCheckMailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnGetMail();
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
