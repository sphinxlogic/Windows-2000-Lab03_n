//--mbxadmin.cpp--------------------------------------------------------------
//
// Implements an Exchange Administration property sheet dialog.
//
// This file is the class that display's the property sheet in Exchange's 
// Admin program.  It also modify's the extension-data for a mailbox.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "edkafx.h"

#include "exadmin.h"
#include "resource.h"
#include "mbxdata.h"
#include "mbxadmin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CMbxAdminDlg::CMbxAdminDlg()
    : CAdminDialog( IDD_MBXADMIN, IDS_MBXADMIN, MBXBLOBNAME)
{
    m_strPassword  = _T("");
    m_strPassword2 = _T("");
}

BEGIN_MESSAGE_MAP(CMbxAdminDlg, CAdminDialog)
	//{{AFX_MSG_MAP(CMbxAdminDlg)
    ON_EN_CHANGE(IDC_PASSWORD, OnChange)
    ON_EN_CHANGE(IDC_PASSWORD2, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMbxAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CAdminDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMbxAdminDlg)
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
    DDX_Text(pDX, IDC_PASSWORD2, m_strPassword2);
	//}}AFX_DATA_MAP
}

//$--CMbxAdminDlg::OnInitDialog()---------------------------------------------
// Initialize the dialog with extension data.
// Create extension data if necessary.
// ---------------------------------------------------------------------------

BOOL CMbxAdminDlg::OnInitDialog() 
{
    CAdminDialog::OnInitDialog();

    m_strPassword = m_strPassword2 = GetExtString(IDX_PASSWORD);

    UpdateData(FALSE);  // Send to the window

    // If there are no properties in our blob...
    if( GetExtCount() == 0)
    {   // NO, extension data is not available so set the memory copy of this
        // to the defaults.

        // The following text string pointers are cast as LONGLONG here
        // because  a bug in the MIPS C++ compiler causes problems if we try
        // to do the cast inside the ExtensionProps structure.

        static const LONGLONG llszPassword    = (LONGLONG) TEXT("");

        static SInitPropValue ExtensionProps[] =
        {
            { PT_STRING8, 0, llszPassword },
        };
    
        // Initialize the property value array used to create the extension
        // data blob.
        if( FAILED( HrSetExtProps( ARRAY_CNT( ExtensionProps), ExtensionProps)))
            return( TRUE);

        // Save it in Admin's memory buffer as well.
        CAdminDialog::bSaveData();
    }
    
    return( TRUE);  // return TRUE unless you set the focus to a control
}


//$--CMbxAdminDlg::bSaveData()------------------------------------------------
// Called when a different property sheet has been selected or when either the 
// OK or APPLY NOW button is pressed.  Returns TRUE if data has been validated
// and saved.
// ---------------------------------------------------------------------------

BOOL CMbxAdminDlg::bSaveData()
{
    HRESULT hr;
    UpdateData (TRUE);

	if (m_strPassword != m_strPassword2)
		return (FALSE);

    hr = HrModExtString( IDX_PASSWORD, m_strPassword);
    if( FAILED( hr))
        return( FALSE);

    return( CAdminDialog::bSaveData());
}

//$--CMbxAdminDlg::OnChange()-------------------------------------------------
// Called when either edit box changes
// ---------------------------------------------------------------------------

void CMbxAdminDlg::OnChange()
{
    DataHasChanged();
}