
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// wabtool.h : main header file for the WABTOOL application
//

#if !defined(AFX_WABTOOL_H__268ADD69_EF27_11D0_9A7E_00A0C91F9C8B__INCLUDED_)
#define AFX_WABTOOL_H__268ADD69_EF27_11D0_9A7E_00A0C91F9C8B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWabtoolApp:
// See wabtool.cpp for the implementation of this class
//

class CWabtoolApp : public CWinApp
{
public:
	CWabtoolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWabtoolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWabtoolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WABTOOL_H__268ADD69_EF27_11D0_9A7E_00A0C91F9C8B__INCLUDED_)
