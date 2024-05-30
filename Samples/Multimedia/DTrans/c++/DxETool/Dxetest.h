// DxeTest.h : main header file for the TEST application
//
#if !defined(AFX_TEST_H__53BE834E_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
#define AFX_TEST_H__53BE834E_4A55_11D1_81AA_0000F87557DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "DxeView.h"
#include "DxeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTestApp:
// See test.cpp for the implementation of this class
//

class CTestApp : public CWinApp
{
public:
	CTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
        CTransitionDlg*    m_pDlgBar;
        CTestView*         m_pView;

		// Server object for document creation

	//{{AFX_MSG(CTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__53BE834E_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
