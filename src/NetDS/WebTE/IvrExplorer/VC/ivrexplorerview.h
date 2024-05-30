// IvrExplorerView.h : interface of the CIvrExplorerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVREXPLORERVIEW_H__848B68E6_AB7D_11D2_A419_006094EB33FB__INCLUDED_)
#define AFX_IVREXPLORERVIEW_H__848B68E6_AB7D_11D2_A419_006094EB33FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CIvrExplorerView : public CListView
{
protected: // create from serialization only
	CIvrExplorerView();
	DECLARE_DYNCREATE(CIvrExplorerView)

// Attributes
public:
    ULONG   m_uNumTextLines;
    ULONG   m_uCurrentWidth;

// Operations
public:

    void AddLine(CString *pCString);
    HRESULT Connect(LPTSTR szAppName);
    IWebIvrActiveConnection *GetApp(void) { return m_pApp; }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIvrExplorerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIvrExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    
// Generated message map functions
protected:
	//{{AFX_MSG(CIvrExplorerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    IWebIvrActiveConnection *m_pApp;
    IConnectionPoint   *m_pEventCP;
    DWORD               m_dwCookie;
    DEventsClass        m_DEvents;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVREXPLORERVIEW_H__848B68E6_AB7D_11D2_A419_006094EB33FB__INCLUDED_)
