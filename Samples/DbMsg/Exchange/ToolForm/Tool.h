// --tool.h-------------------------------------------------------------------
//
//  Main header file for the Tool application
//
//	Copyright (C) 1986-1996. Microsoft Corporation.  All Rights Reserved.
//
// ---------------------------------------------------------------------------

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Tool:
// See Tool.cpp for the implementation of this class
//

class CToolFormApp : public CWinApp
{
public:
	CToolFormApp();

	CSingleDocTemplate * m_pDocTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolFormApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CToolFormApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
extern CToolFormApp theApp;
