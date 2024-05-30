// --tooldoc.cpp--------------------------------------------------------------
//
//   Implementation of the CToolDoc class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "tool.h"

#include "formdata.h"
#include "form.h"

#include "tooldoc.h"
#include "toolform.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

FRM	* g_pForm		= NULL;

/////////////////////////////////////////////////////////////////////////////
// CToolDoc

IMPLEMENT_DYNCREATE(CToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolDoc, CDocument)
	//{{AFX_MSG_MAP(CToolDoc)
	ON_COMMAND(ID_FILE_SEND, OnFileSend)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND, OnUpdateFileSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolDoc construction/destruction

CToolDoc::CToolDoc()
{
// *** ADDED CODE ***
    m_fOleMapiINITed	= FALSE;
	m_fStandaloneApp	= TRUE;

	HRESULT hr = NOERROR;

	hr = HrStartOleAndRegisterClassFactory();		// Start OLE and MAPI
	if (NOERROR == hr)	
	{
		m_fOleMapiINITed = TRUE;
	}
// *** END ADDED CODE ***
}



CToolDoc::~CToolDoc()
{
	if (TRUE == m_fOleMapiINITed)
	{
		HrStopForms();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolDoc serialization

void CToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolDoc diagnostics

#ifdef _DEBUG
void CToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolDoc commands

void CToolDoc::OnFileSend() 
{
	AfxGetMainWnd()->SetWindowText("Sending ...");
	
    POSITION pos = theApp.m_pDocTemplate->GetFirstDocPosition();
    ASSERT (pos);

    CToolDoc * pDoc = (CToolDoc*)theApp.m_pDocTemplate->GetNextDoc(pos);
    
    POSITION posVW = pDoc->GetFirstViewPosition();
    ASSERT (posVW);

    CToolForm * pView = (CToolForm*) pDoc->GetNextView (posVW);

    if (NULL != pView)
	{
		pView->GetDataFromWindow();
	}

    if (g_pForm)
    {
    	g_pForm->AddressForm(AfxGetMainWnd()->m_hWnd, FALSE);
		
    	// ----- Update our forms information based on user interaction
    	g_pForm->SetFormData(m_theFormData);

    	// ----- Send this form, then shut it down
    	g_pForm->SendForm();
    	g_pForm->ShutdownForm(OLECLOSE_NOSAVE);
		g_pForm->Release();
    }
	
}

void CToolDoc::OnUpdateFileSend(CCmdUI* pCmdUI) 
{
    if (NULL != g_pForm)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}
