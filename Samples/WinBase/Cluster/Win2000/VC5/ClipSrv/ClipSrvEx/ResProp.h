/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 99 <company name>
//
//	Module Name:
//		ResProp.h
//
//	Implementation File:
//		ResProp.cpp
//
//	Description:
//		Definition of the resource extension property page classes.
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 99
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __RESPROP_H__
#define __RESPROP_H__

/////////////////////////////////////////////////////////////////////////////
// Include Files
/////////////////////////////////////////////////////////////////////////////

#ifndef _BASEPAGE_H_
#include "BasePage.h"	// for CBasePropertyPage
#endif

#ifndef _PROPLIST_H_
#include "PropList.h"	// for CObjectPropert
#endif

/////////////////////////////////////////////////////////////////////////////
// Forward Class Declarations
/////////////////////////////////////////////////////////////////////////////

class CClipSrvParamsPage;

/////////////////////////////////////////////////////////////////////////////
// External Class Declarations
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
//	CClipSrvParamsPage
//
//	Purpose:
//		Parameters page for resources.
//
/////////////////////////////////////////////////////////////////////////////

class CClipSrvParamsPage : public CBasePropertyPage
{
	DECLARE_DYNCREATE( CClipSrvParamsPage )

// Construction
public:
	CClipSrvParamsPage( void );

// Dialog Data
	//{{AFX_DATA(CClipSrvParamsPage)
	enum { IDD = IDD_PP_CLIPSRV_PARAMETERS };
	CString	m_strComment;
	//}}AFX_DATA
	CString	m_strPrevComment;

protected:
	enum
	{
		epropComment,
		epropMAX
	};
	CObjectProperty		m_rgProps[ epropMAX ];

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CClipSrvParamsPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	virtual const CObjectProperty *	Pprops( void ) const	{ return m_rgProps; }
	virtual DWORD					Cprops( void ) const	{ return sizeof( m_rgProps ) / sizeof( CObjectProperty ); }

// Implementation
protected:
	BOOL	BAllRequiredFieldsPresent( void ) const;

	// Generated message map functions
	//{{AFX_MSG(CClipSrvParamsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRequiredField();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};  //*** class CClipSrvParamsPage

/////////////////////////////////////////////////////////////////////////////

#endif // __RESPROP_H__
