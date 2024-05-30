// -----------------------------------------------------------------------------
// PropDlg.h : Declaration of a class that displays a dialog to show a 
//             list of properties.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _PROPDLG_H_
#define _PROPDLG_H_

// -----------------------------------------------------------------------------

#include "resource.h"
#include "ExAdmin.h"
#include "Property.h"

// -----------------------------------------------------------------------------

class CPropDlg : public CADialog
{
public:
	CPropDlg( CProperty* piProp);   // standard constructor

protected:
    CProperty*  m_piProp;   // Pointer to CProperty interface object.
    CListBox    m_lbProps;  // List box to show properties in.

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Class wizard stuff.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
public:
	//{{AFX_DATA(CPropDlg)
	enum { IDD = IDD_PROPS};
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropDlg)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CPropDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------

#endif //_PROPDLG_H_
