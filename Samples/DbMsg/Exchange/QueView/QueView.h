// -----------------------------------------------------------------------------
// QueView.h : header file
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _QUEVIEW_H_
#define _QUEVIEW_H_

// -----------------------------------------------------------------------------

#include "ExAdmin.h"
#include "resource.h"
#include "PrpLstCb.h"

// -----------------------------------------------------------------------------
// Definition of a class that contains the methods and objects necessary to 
// handle the Queue Viewer property sheet as an extension dialog.
// -----------------------------------------------------------------------------

class CQueViewDlg : public CAdminDialog
{
public:
    // A default constructor is the only one we will need.
    CQueViewDlg();
    ~CQueViewDlg();

protected:
    BOOL                    m_bInitilized;     // Initialization succeeded if TRUE.
    BOOL                    m_bMTSIn;          // TRUE if MTS in is to be viewed.
    LPMDB                   m_pMDB;            // Ptr to MDB of admin session.
    LPMDB                   m_pGWmdb;          // Ptr to gateway's message store.
    HGLOBAL                 m_hPropDlgTemplate;// Template to initialize the property dialog.

    // Derived from CWnd.
    CPropsListBox           m_lbMsgs;          // List box containing entry ids of messages.
    CPropsComboBox          m_cbFolders;       // Combo box containing entry ids of folders.
    CButton                 m_btnDelete;       // Delete button object.
    CButton                 m_btnNDR;          // NDR button object.
    CButton                 m_btnRefresh;      // Refresh button object.
    CButton                 m_btnDetails;      // Details button object.

    void DeleteMsgsNow();
    void DeferMsgsAction( 
        ULONG ulAction);     // Should be either ADMINOP_DELETE or ADMINOP_NDR.

    // Called to determine if you supply help.  Return TRUE if you do, defaults to FALSE.
    virtual BOOL bHasHelp();
    
    // Called to start help.  Default does nothing.
    virtual VOID DoHelp();

    // Called when the property sheet has been activated or reactivated.
    virtual void Refresh();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Class wizard stuff.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
public:
	//{{AFX_DATA(CQueViewDlg)
	enum { IDD = IDD_QUEUE_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueViewDlg)
	public:
	protected:
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CQueViewDlg)
	afx_msg void OnCmdRefresh();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnCmdDetails();
	afx_msg void OnSelChangeComboFolders();
	afx_msg void OnSelChangeListMsgs();
	afx_msg void OnCmdDelete();
	afx_msg void OnCmdNdr();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillFocusComboFolders();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_
#pragma message("Declaration of global objects for: " __FILE__)

// Declare an instances of a CAdminDialog derived class.
CQueViewDlg QueViewDlg;

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------

#endif // _QUEVIEW_H_
