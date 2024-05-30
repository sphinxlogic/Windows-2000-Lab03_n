//=========================================================================
//  PostView.cpp
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
// 
//
// Purpose:
//    implementation of the CPostSmplView class
//=========================================================================


#include "stdafx.h"
#include "PostSmpl.h"

#include "PostDoc.h"
#include "PostView.h"
#include "PostData.h"
#include "freedoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostSmplView

IMPLEMENT_DYNCREATE(CPostSmplView, CEditView)

BEGIN_MESSAGE_MAP(CPostSmplView, CEditView)
	//{{AFX_MSG_MAP(CPostSmplView)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_POSTDOC, OnFilePostdoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_POSTDOC, OnUpdateFilePostdoc)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostSmplView construction/destruction

CPostSmplView::CPostSmplView()
{
	//  add construction code here

}

CPostSmplView::~CPostSmplView()
{
}

BOOL CPostSmplView::PreCreateWindow(CREATESTRUCT& cs)
{
	//  Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPostSmplView drawing

void CPostSmplView::OnDraw(CDC* pDC)
{
	CPostSmplDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//  add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPostSmplView printing

BOOL CPostSmplView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPostSmplView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	//  add extra initialization before printing
}

void CPostSmplView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	//  add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPostSmplView diagnostics

#ifdef _DEBUG
void CPostSmplView::AssertValid() const
{
	CEditView::AssertValid();
}

void CPostSmplView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CPostSmplDoc* CPostSmplView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPostSmplDoc)));
	return (CPostSmplDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPostSmplView message handlers

void CPostSmplView::OnFileSave() 
{
	CPostSmplDoc* pDoc = GetDocument();
	
	//Get the text body from edit box
	GetDataFromEdit();
	
	if (pDoc)
	{
		//Save text to the file
		pDoc->OnFileSave();
	
		//Get the name of the saved file
		PostData.szFile = pDoc->GetPathName();
		PostData.szFileTitle = pDoc->GetTitle();
	}
}

void CPostSmplView::OnFileSaveAs() 
{
	CPostSmplDoc* pDoc = GetDocument();
	
	//Get the text body from edit box
	GetDataFromEdit();

	if (pDoc)
	{
		//Save text to the file
		pDoc->OnFileSaveAs();
	
		//Get the name of the saved file
		PostData.szFile = pDoc->GetPathName();
		PostData.szFileTitle = pDoc->GetTitle();
	}
}


void CPostSmplView::OnFileOpen() 
{
	CPostSmplDoc* pDoc = GetDocument();
	
	//Open the document file specified by user
	theApp.OnFileOpen();

	if (pDoc)
	{
		//Get the filename
		PostData.szFile = pDoc->GetPathName();
		PostData.szFileTitle = pDoc->GetTitle();

		//Get the summary property set
		GetSummaryInfo( pDoc->GetStorage(), 
						&PostData.m_psTitle, 
						&PostData.m_psSubject, 
						&PostData.m_psAuthor, 
						&PostData.m_psKeywords, 
						&PostData.m_psComments);
	}

	//Update the editbox with document text
	PutDataToEdit();
}

void CPostSmplView::OnFileNew() 
{																		 
		
	//Create a new document
	theApp.OnFileNew();

	//clear the editbox
	PutDataToEdit();
}

void CPostSmplView::GetDataFromEdit()
{
	//Get data from edit box window
	CEdit &EdtCtrl = GetEditCtrl();
	UINT cLen = GetBufferLength();
	EdtCtrl.GetWindowText(theApp.m_lpBuffer);

}

void CPostSmplView::PutDataToEdit()
{
	//Put data to edit box window	
	CEdit &EdtCtrl = GetEditCtrl();
	EdtCtrl.SetWindowText(theApp.m_lpBuffer);
}


void CPostSmplView::OnFilePostdoc() 
{
	CPostSmplDoc* pDoc = GetDocument();

	if (pDoc)
		//Post the document
		PostData.FilePost(pDoc->GetStorage());
}

void CPostSmplView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CPostSmplDoc* pDoc = GetDocument();
	if (pDoc)
	{
		//Get the filename
		PostData.szFile = pDoc->GetPathName();
		PostData.szFileTitle = pDoc->GetTitle();

		//Update the editbox with document text
		PutDataToEdit();

		//Get the summary property set
		GetSummaryInfo( pDoc->GetStorage(), 
						&PostData.m_psTitle, 
						&PostData.m_psSubject, 
						&PostData.m_psAuthor, 
						&PostData.m_psKeywords, 
						&PostData.m_psComments);
	
	}
	CView::OnUpdate(pSender, lHint, pHint);	
}

void CPostSmplView::OnUpdateFilePostdoc(CCmdUI* pCmdUI) 
{
	if (theApp.m_bEmbedded)
		pCmdUI->Enable( FALSE );
}

