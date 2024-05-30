// delmsgdl.cpp : implementation file
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.

#include "edkafx.h"
	// add additional includes here
#include "delmsgdl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelMsgDlg dialog


CDelMsgDlg::CDelMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDelMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CDelMsgDlg)
	ON_BN_CLICKED(IDC_CMD_DELETE_BY_GATEWAY, OnCmdDeleteByGateway)
	ON_BN_CLICKED(IDC_CMD_DELETE_NOW, OnCmdDeleteNow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDelMsgDlg message handlers

void CDelMsgDlg::OnCmdDeleteByGateway() 
{
    EndDialog( IDC_CMD_DELETE_BY_GATEWAY);
}

void CDelMsgDlg::OnCmdDeleteNow() 
{
	EndDialog( IDC_CMD_DELETE_NOW);
}
