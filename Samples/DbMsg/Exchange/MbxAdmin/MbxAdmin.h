//--mbxadmin.h----------------------------------------------------------------
//
// Declaration for the CMbxAdminDlg class.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

class CMbxAdminDlg : public CAdminDialog
{
public:
    CMbxAdminDlg();

protected:
    virtual BOOL bSaveData();
    
public:
	//{{AFX_DATA(CMbxAdminDlg)
		CString m_strPassword;
        CString m_strPassword2;
	//}}AFX_DATA

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMbxAdminDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMbxAdminDlg)
	virtual BOOL OnInitDialog();
    afx_msg void OnChange();
	//}}AFX_MSG
    
	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_

// Declare any instances of a CAdminDialog derived class.
CMbxAdminDlg dlg;

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------
