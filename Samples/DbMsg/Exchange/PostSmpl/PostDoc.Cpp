//=========================================================================
// PostDoc.CPP
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
// 
//
// Purpose:
//    implementation of the CPostSmplDoc class
//=========================================================================


#include "stdafx.h"
#include "PostSmpl.h"
#include "PostDoc.h"
#include "PostData.h"
#include "Freedoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostSmplDoc

IMPLEMENT_DYNCREATE(CPostSmplDoc, COleDocument)

BEGIN_MESSAGE_MAP(CPostSmplDoc, COleDocument)
	//{{AFX_MSG_MAP(CPostSmplDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//ON_COMMAND(ID_FILE_POSTDOC, OnFilePostdoc)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)


	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostSmplDoc construction/destruction

CPostSmplDoc::CPostSmplDoc()
{
	//  add one-time construction code here
	EnableCompoundFile(TRUE);

}

CPostSmplDoc::~CPostSmplDoc()
{
}

BOOL CPostSmplDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	//  add reinitialization code here
	// (SDI documents will reuse this document)
	

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPostSmplDoc serialization

void CPostSmplDoc::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		// Save document to disk
		ar.Write((LPCSTR)theApp.m_lpBuffer, 
				theApp.m_lpBuffer.GetLength()); 
		
		//Save the summary property set
		SetSummaryInfo( m_lpRootStg, 
				(LPCSTR)PostData.m_psTitle, 
				(LPCSTR)PostData.m_psSubject, 
				(LPCSTR)PostData.m_psAuthor, 
				(LPCSTR)PostData.m_psKeywords, 
				(LPCSTR)PostData.m_psComments);
	}
	else
	{
		// Load the document data
		CONST nRequested = 100;
		INT nReturned	 = 100;
		char lpszBuf[nRequested] = "";
		theApp.m_lpBuffer = TEXT("");

		while (nReturned == nRequested)
		{
			nReturned = ar.Read(lpszBuf, 
									nRequested); 
			theApp.m_lpBuffer += lpszBuf;
		}
		
	}

}

/////////////////////////////////////////////////////////////////////////////
// CPostSmplDoc diagnostics

#ifdef _DEBUG
void CPostSmplDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CPostSmplDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPostSmplDoc commands


void CPostSmplDoc::OnFileSave() 
{
	//  Add your command handler code here
	COleDocument::OnFileSave();
	
}
void CPostSmplDoc::OnFileSaveAs() 
{
	//  Add your command handler code here
	COleDocument::OnFileSaveAs();
	
}

