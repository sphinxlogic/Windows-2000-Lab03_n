// -----------------------------------------------------------------------------
// SGWAdmin.h : header file
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _SGWADMIN_H_
#define _SGWADMIN_H_

#pragma message("Including " __FILE__)

// -----------------------------------------------------------------------------

#include "ExAdmin.h"
#include "Resource.h"
#include "EditExt.h"
#include "SGWData.h"

// -----------------------------------------------------------------------------

class CSGWDlg : public CAdminDialog
{
public:
    // A default constructor is the only one we will need.
    CSGWDlg() : CAdminDialog( IDD_SGW, IDS_SGW, SGWBLOBNAME) {}

protected:
    // Validate that a string is not empty and modify the extension data property
    // in memory.
    BOOL bIsValidString( 
        IN ULONG iProp,         // Index of property
        IN CEditExt& editCtrl); // Edit control containing data to validate.

    // Validate that a ulong is within a specified range and modify the extension 
    // data property in memory.
    BOOL bIsValidULong(
        IN ULONG     iProp,     // Index of property
        IN CEditExt& editCtrl,  // Edit control containing data to validate.
        IN ULONG     ulLow,     // Lowest valid value.
        IN ULONG     ulHigh,    // Highest valid value.
        IN int       idErrMsg); // Index of error message resource string.

    // Called when a different property sheet has been selected or when either the 
    // OK or APPLY NOW button is pressed.  Returns TRUE if data has been validated
    // and saved.
    //
    // When we call the CAdminDialog::bSaveData() function it gets saved in an
    // admin memory space.  This makes it available to other property sheets that
    // might be viewing the same data.
    virtual BOOL bSaveData();
    
    // Called when either the OK or APPLY NOW button is pressed and after bSaveData().
    // Return TRUE if data has been committed.
    virtual BOOL bCommitData();
    
    // Called to determine if you supply help.  Return TRUE if you do, defaults to FALSE.
    virtual BOOL bHasHelp();
    
    // Called to start help.  Default does nothing.
    virtual VOID DoHelp();

    // Called when our property sheet is brought into focus to refresh data that
    // may have been altered by other property sheets.
    virtual void Refresh();

    // This boolean is used to keep the apply button from being enabled when
    // we are just repainting the data on the form.
    BOOL m_bRefresh;

    // All of the controls of this dialog.
    CButton  m_CheckInBound;
    CButton  m_CheckOutBound;
    CEditExt m_EditAddrType;
    CEditExt m_EditDispName;
    CEditExt m_EditEmailAddr;
    CEditExt m_EditThreadsIn;
    CEditExt m_EditThreadsOut;
    CEditExt m_EditMsgsIn;
    CEditExt m_EditMsgsOut;
    CEditExt m_EditSleepIn;
    CEditExt m_EditSleepOut;
    CEditExt m_EditPollingIn;
    CEditExt m_EditPollingOut;
    CEditExt m_EditDirIn;
    CEditExt m_EditDirOut;
    CEditExt m_EditConverterIn;
    CEditExt m_EditConverterOut;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Class wizard stuff.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
public:
	//{{AFX_DATA(CSGWDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSGWDlg)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSGWDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChange();
	afx_msg void OnBnClicked();
	//}}AFX_MSG
    
	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_
#pragma message("Declaration of global objects for: " __FILE__)

// Declare an instance of a CAdminDialog derived class.
CSGWDlg SGWDlg;

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------

#endif // _SGWADMIN_H_
