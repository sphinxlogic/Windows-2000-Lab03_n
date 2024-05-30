// SummInfo.cpp : implementation file
//

#include "stdafx.h"
#include "postsmpl.h"
#include "SummInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSummInfo dialog


CSummInfo::CSummInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CSummInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSummInfo)
	m_psauthor = _T("");
	m_pscomments = _T("");
	m_psdirectory = _T("");
	m_psfilename = _T("");
	m_pskeywords = _T("");
	m_pssubject = _T("");
	m_pstitle = _T("");
	//}}AFX_DATA_INIT
}


void CSummInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSummInfo)
	DDX_Text(pDX, IDC_Author, m_psauthor);
	DDX_Text(pDX, IDC_Comments, m_pscomments);
	DDX_Text(pDX, IDC_Directory, m_psdirectory);
	DDX_Text(pDX, IDC_FileName, m_psfilename);
	DDX_Text(pDX, IDC_Keywords, m_pskeywords);
	DDX_Text(pDX, IDC_Subject, m_pssubject);
	DDX_Text(pDX, IDC_Title, m_pstitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSummInfo, CDialog)
	//{{AFX_MSG_MAP(CSummInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSummInfo message handlers

