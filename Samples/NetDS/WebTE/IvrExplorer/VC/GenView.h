//////////////////////////////////////////////////////////////////////////////
//  FILE          : GenView.h                                               //
//                                                                          //
//  DESCRIPTION   : Interface of the CGeneralView class.                    //
//                                                                          //
//  AUTHOR        : EyalA                                                   //
//                                                                          //
//  HISTORY       :                                                         //
//      Dec 15 1996 EyalA   Init.                                           //
//      Feb 20 1997 BarakH  Added OnUpdateEditCopy and OnEditCopy to handle //
//                          copy to clipboard.                              //
//                                                                          //
//  Copyright (C) 1996 Microsoft Corporation   All Rights Reserved          //
//////////////////////////////////////////////////////////////////////////////

#ifndef GENVIEW_H_INCLUDED
#define GENVIEW_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// CGeneralView view

class CGeneralView : public CListView
{
protected:
    CGeneralView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CGeneralView)

// Attributes
public:
    ULONG   m_uNumTextLines;
    ULONG   m_uCurrentWidth;

// Operations
public:
    void AddLine(CString *pCString);
    HRESULT Connect(LPSTR szAppName);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGeneralView)
    protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~CGeneralView();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(CGeneralView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // GENVIEW_H_INCLUDED
