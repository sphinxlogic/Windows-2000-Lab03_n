// --toolform.cpp-------------------------------------------------------------
//
//   Implementation of the CToolForm class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "Tool.h"

#include "formdata.h"
#include "form.h"

#include "ToolForm.h"
#include "ToolDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// CToolForm

IMPLEMENT_DYNCREATE(CToolForm, CFormView)

CToolForm::CToolForm()
	: CFormView(CToolForm::IDD)
{
	//{{AFX_DATA_INIT(CToolForm)
	m_strDevelopedBy = _T("");
	m_strIntroduction = _T("");
	m_strLocation = _T("");
	m_strOS = _T("");
	m_strPlatform = _T("");
	m_strToolName = _T("");
	m_strToolType = _T("");
	m_strTopic = _T("");
	//}}AFX_DATA_INIT
}

CToolForm::~CToolForm()
{
}

void CToolForm::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CToolForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolForm)
	DDX_Text(pDX, IDC_DEVELOPEDBY, m_strDevelopedBy);
	DDX_Text(pDX, IDC_INTRODUCTION, m_strIntroduction);
	DDX_Text(pDX, IDC_LOCATION, m_strLocation);
	DDX_CBString(pDX, IDC_OS, m_strOS);
	DDX_CBString(pDX, IDC_PLATFORM, m_strPlatform);
	DDX_Text(pDX, IDC_TOOLNAME, m_strToolName);
	DDX_CBString(pDX, IDC_TOOLTYPE, m_strToolType);
	DDX_Text(pDX, IDC_TOPIC, m_strTopic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolForm, CFormView)
	//{{AFX_MSG_MAP(CToolForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CToolForm diagnostics

#ifdef _DEBUG
void CToolForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CToolForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CToolDoc* CToolForm::GetDocument() // non-debug version is inline
{
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolForm message handlers

void CToolForm::OnInitialUpdate() 
{
 	PutDataIntoWindow();

	CFormView::OnInitialUpdate();
}

void CToolForm::PutDataIntoWindow(void) 
{
    CToolDoc * pDoc = GetDocument();

    //	TODO : Enter FORM DATA specific code here
	m_strTopic         = pDoc->m_theFormData.m_szTopic;
	m_strToolName      = pDoc->m_theFormData.m_szToolName;
	m_strToolType      = pDoc->m_theFormData.m_szToolType;
	m_strPlatform      = pDoc->m_theFormData.m_szPlatform;
	m_strOS            = pDoc->m_theFormData.m_szOS;
	m_strDevelopedBy   = pDoc->m_theFormData.m_szDevelopedBy;
	m_strLocation      = pDoc->m_theFormData.m_szLocation;
	m_strIntroduction  = pDoc->m_theFormData.m_szIntroduction;	
	
	UpdateData(FALSE);
}


void CToolForm::GetDataFromWindow(void) 
{
	UpdateData(TRUE);

    CToolDoc * pDoc = GetDocument();

    //	TODO : Enter FORM DATA specific code here
	strncpy(
        pDoc->m_theFormData.m_szTopic, 
        m_strTopic, 
        sizeof(pDoc->m_theFormData.m_szTopic) - 1);
	strncpy(
        pDoc->m_theFormData.m_szToolName, 
        m_strToolName, 
        sizeof(pDoc->m_theFormData.m_szToolName) - 1);
	strncpy(
        pDoc->m_theFormData.m_szToolType, 
        m_strToolType, 
        sizeof(pDoc->m_theFormData.m_szToolType) - 1);
	strncpy(
        pDoc->m_theFormData.m_szPlatform, 
        m_strPlatform, 
        sizeof(pDoc->m_theFormData.m_szPlatform) - 1);
	strncpy(
        pDoc->m_theFormData.m_szOS, 
        m_strOS, 
        sizeof(pDoc->m_theFormData.m_szOS) - 1);
	strncpy(
        pDoc->m_theFormData.m_szDevelopedBy, 
        m_strDevelopedBy, 
        sizeof(pDoc->m_theFormData.m_szDevelopedBy) - 1);
	strncpy(
        pDoc->m_theFormData.m_szLocation, 
        m_strLocation, 
        sizeof(pDoc->m_theFormData.m_szLocation) - 1);
	strncpy(
        pDoc->m_theFormData.m_szIntroduction, 
        m_strIntroduction, 
        sizeof(pDoc->m_theFormData.m_szIntroduction) - 1);	
}
