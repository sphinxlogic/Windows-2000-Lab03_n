// **************************************************************************
// Copyright (c) 1997-1999 Microsoft Corporation.
//
// File:  UserInfo.cpp
//
// Description:
//	This file implements the CUserInfo dialog class which 
//		collects information for the OnAddUser() routine.
// 
// History:
//
// **************************************************************************

#include "stdafx.h"
#include "WBEMSamp.h"
#include "UserInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog


CUserInfo::CUserInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserInfo)
	m_AcctName = _T("");
	m_Domain = _T("");
	//}}AFX_DATA_INIT
}


void CUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInfo)
	DDX_Text(pDX, IDC_ACCTNAME, m_AcctName);
	DDX_Text(pDX, IDC_DOMAIN, m_Domain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserInfo, CDialog)
	//{{AFX_MSG_MAP(CUserInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInfo message handlers
