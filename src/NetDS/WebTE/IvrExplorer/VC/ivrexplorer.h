// IvrExplorer.h : main header file for the IVREXPLORER application
//

#if !defined(AFX_IVREXPLORER_H__848B68DC_AB7D_11D2_A419_006094EB33FB__INCLUDED_)
#define AFX_IVREXPLORER_H__848B68DC_AB7D_11D2_A419_006094EB33FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "genview.h"
#include "IvrExplorerView.h"

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerApp:
// See IvrExplorer.cpp for the implementation of this class
//

class CIvrExplorerApp : public CWinApp
{
public:
	CIvrExplorerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIvrExplorerApp)
	public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

    UINT         GetNumberOfRows() { return m_numberOfRows; };
    IWebIvrService     *GetWebIvr() { return m_pIvr; };

	//{{AFX_MSG(CIvrExplorerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnFileConnect();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileConnect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    InitIvr();

private:
        
    UINT        m_numberOfRows;
    IWebIvrService    *m_pIvr;
    BOOL        m_fConnected;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVREXPLORER_H__848B68DC_AB7D_11D2_A419_006094EB33FB__INCLUDED_)
