// -----------------------------------------------------------------------------
// PropDlg.cpp: Implementation of a class that displays a dialog to show a 
//              list of properties.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "PropDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CPropDlg, CDialog)
	//{{AFX_MSG_MAP(CPropDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------
// CONSTRUCTOR: Takes an ptr to a CProperty interface object pointer.
// -----------------------------------------------------------------------------

CPropDlg::CPropDlg( CProperty* piProp) : CADialog(/*CPropDlg::IDD*/)
{
	//{{AFX_DATA_INIT(CPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_piProp = piProp;
}

// -----------------------------------------------------------------------------
// Initialize the dialog using the properties listed in the CProperty object
// that we got a pointer to in the constructor.
// -----------------------------------------------------------------------------

BOOL CPropDlg::OnInitDialog() 
{
	// Pay tribute to our ancestors.
	CDialog::OnInitDialog();

    // Connect the CListBox object to the appropriate control.
    if( HrSubclassWindow( IDC_LIST_PROPS, m_lbProps) != NOERROR)
        return( TRUE);  // Could not find the list box window.
    
    // Set the tab stops for the list box.
    int nTabStops[] = { 130, 400};
    m_lbProps.SetTabStops( ARRAY_CNT( nTabStops), nTabStops);
    m_lbProps.SetHorizontalExtent( 1000);

    if( !m_piProp)
    {
        HR_LOG( E_FAIL);
        return( TRUE);
    }

    // Get the first property.
    m_piProp->First();
    
    // Fill list box with all properties.
    while( !m_piProp->bAtEnd())
    {   // Format string to add to list box.
        CString sBuf = m_piProp->szGetPrID();
        sBuf += "\t";
        sBuf += m_piProp->szGetPrValue();
        
        // Add formated string to list box.
        m_lbProps.AddString( sBuf);
    
        // Move on to the next property.
        m_piProp->Next();    
    }
	
	return TRUE;  // Return TRUE unless you set the focus to a control.
}

// -----------------------------------------------------------------------------
