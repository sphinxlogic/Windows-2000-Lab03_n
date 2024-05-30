// NShowMFC.h : main header file for the NSHOWMFC application
//

#if !defined(AFX_NSHOWMFC_H__4DD2ED96_AE23_11D1_9F80_00C04FD7AC7F__INCLUDED_)
#define AFX_NSHOWMFC_H__4DD2ED96_AE23_11D1_9F80_00C04FD7AC7F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNShowMFCApp:
// See NShowMFC.cpp for the implementation of this class
//

class CNShowMFCApp : public CWinApp
{
public:
	CNShowMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNShowMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNShowMFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NSHOWMFC_H__4DD2ED96_AE23_11D1_9F80_00C04FD7AC7F__INCLUDED_)
