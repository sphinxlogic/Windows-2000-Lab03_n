//=========================================================================
// PostView.h
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//    interface of the CPostSmplView class
//=========================================================================


class CPostSmplView : public CEditView
{
protected: // create from serialization only
	CPostSmplView();
	DECLARE_DYNCREATE(CPostSmplView)

// Attributes
public:
	CPostSmplDoc* GetDocument();
	void PutDataToEdit();
	void GetDataFromEdit();
	
// Operations
public:
   
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostSmplView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPostSmplView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPostSmplView)
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnFilePostdoc();
	afx_msg void OnUpdateFilePostdoc(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PostSmplView.cpp
inline CPostSmplDoc* CPostSmplView::GetDocument()
   { return (CPostSmplDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
