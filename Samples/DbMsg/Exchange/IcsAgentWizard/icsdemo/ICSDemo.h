// ICSDemo.h : main header file for the ICSDEMO application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "MAPIApp.h"

/////////////////////////////////////////////////////////////////////////////
// CICSDemoApp:
// See ICSDemo.cpp for the implementation of this class
//

class CICSDemoApp : public CWinApp
{
public:
	CICSDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CICSDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CICSDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMAPIApp		*m_lpMAPIApp;

public:
	LPMAPISESSION MAPISession() { return m_lpMAPIApp->Session(); };
	void ShowErrorMessage(LPCSTR lpszInfoString,HRESULT hResult);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
