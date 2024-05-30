// IvrExplorerDoc.cpp : implementation of the CIvrExplorerDoc class
//

#include "stdafx.h"
#include "IvrExplorerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerDoc

IMPLEMENT_DYNCREATE(CIvrExplorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CIvrExplorerDoc, CDocument)
	//{{AFX_MSG_MAP(CIvrExplorerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerDoc construction/destruction

CIvrExplorerDoc::CIvrExplorerDoc()
{
	// TODO: add one-time construction code here

}

CIvrExplorerDoc::~CIvrExplorerDoc()
{
}

BOOL CIvrExplorerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerDoc serialization

void CIvrExplorerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerDoc diagnostics

#ifdef _DEBUG
void CIvrExplorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIvrExplorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerDoc commands
