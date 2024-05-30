// **************************************************************************
// Copyright (c) 1997-1999 Microsoft Corporation.
//
// File:  UserInfo.h
//
// Description:
//	This file declares the CUserInfo dialog class. It collects
//		user information for OnAddUser().
// 
// Part of: WMI Tutorial #1.
//
// Used by: CHMMSampleDlg::OnAddUser().
//
// History:
//
// **************************************************************************

#if !defined(AFX_USERINFO_H__34EFC7A3_02B6_11D1_AD84_00AA00B8E05A__INCLUDED_)
#define AFX_USERINFO_H__34EFC7A3_02B6_11D1_AD84_00AA00B8E05A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UserInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog

class CUserInfo : public CDialog
{
// Construction
public:
	CUserInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserInfo)
	enum { IDD = IDD_USERINFO };
	CString	m_AcctName;
	CString	m_Domain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINFO_H__34EFC7A3_02B6_11D1_AD84_00AA00B8E05A__INCLUDED_)
