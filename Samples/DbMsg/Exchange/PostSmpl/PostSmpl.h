//=========================================================================
// PostSmpl.h
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//    main header file for the POSTSMPL application
//=========================================================================



#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <mapiutil.h>
#include <mapix.h>


/////////////////////////////////////////////////////////////////////////////
// CPostSmplApp:
// See PostSmpl.cpp for the implementation of this class
//

class CPostSmplApp : public CWinApp
{
public:
	CPostSmplApp();
	CString m_lpBuffer;
	BOOL    m_bEmbedded;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostSmplApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPostSmplApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFilePostmsg();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnFileSumInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CPostSmplApp theApp;
/////////////////////////////////////////////////////////////////////////////
