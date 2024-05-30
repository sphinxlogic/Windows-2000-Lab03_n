//--mbxserv.h-----------------------------------------------------------------
//
// Main header file for the MBXSERV application
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMbxServApp:
// See voxserv.cpp for the implementation of this class
//

class CMbxServApp : public CWinApp
{
public:
	CMbxServApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMbxServApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	LPMAPISESSION	m_lpSession;
	LPMDB			m_lpMDB;
	LPADRBOOK		m_lpAddrBook;
	LPABCONT		m_lpGAL;

	//{{AFX_MSG(CMbxServApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
