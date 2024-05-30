// --tooldoc.h----------------------------------------------------------------
//
//  Interface of the CToolDoc class
//
//	Copyright (C) 1986-1996. Microsoft Corporation.  All Rights Reserved.
//
// ---------------------------------------------------------------------------

class CToolDoc : public CDocument
{
protected: // create from serialization only
	CToolDoc();
	DECLARE_DYNCREATE(CToolDoc)

// Attributes

// *** ADDED CODE ***
public:
	CFormData	m_theFormData;

	BOOL		m_fOleMapiINITed;
	BOOL		m_fStandaloneApp;
// *** END ADDED CODE ***

// Operations
public:
	void PutDataIntoWindow();
	void GetDataFromWindow();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolDoc)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolDoc)
	afx_msg void OnFileSend();
	afx_msg void OnUpdateFileSend(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

extern FRM * g_pForm;
