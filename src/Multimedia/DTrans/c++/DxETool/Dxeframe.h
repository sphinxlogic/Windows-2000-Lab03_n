// DxeFrame.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINFRM_H__53BE8353_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
#define AFX_MAINFRM_H__53BE8353_4A55_11D1_81AA_0000F87557DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DxeDlg.h"

class CMainFrame : public CFrameWnd
{
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CStatusBar     m_wndStatusBar;
        CTransitionDlg m_DlgBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileLoadMeshA();
	afx_msg void OnFileLoadMeshB();
	afx_msg void OnFileLoadSurfaceA();
	afx_msg void OnFileLoadSurfaceB();
	afx_msg void OnFileSubmeshAIn();
	afx_msg void OnFileSubmeshBIn();
	afx_msg void OnViewInputMeshA();
	afx_msg void OnViewInputMeshB();
	afx_msg void OnViewOutputMesh();
	afx_msg void OnUpdateViewInputMeshA(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewInputMeshB(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewOutputMesh(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    void OnUseSubmeshes(DWORD dwWhichInput);	// Helper for OnFileSubmeshXIn();
    void OnSurfaceChange(DWORD dwWhichSurface);	// Helper for OnFileLoadSurfaceX().
    void OnMeshChange(DWORD dwWhichMesh);	// Helper for OnFileLoadMeshX().
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__53BE8353_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
