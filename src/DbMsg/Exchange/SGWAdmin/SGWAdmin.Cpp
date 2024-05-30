// -----------------------------------------------------------------------------
// SGWAdmin.cpp : Implements an Exchange Administration property sheet dialog.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "SGWAdmin.h"
#include "errcpp.h"
#include "Format.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------------------------
// Declaration of static data used to initialize and hold cfg extension data.
// -----------------------------------------------------------------------------

static const CHAR szNOTIFICATION[]      = TEXT("NOTIFICATION");

// The following text string pointers are cast as LONGLONG here because 
// a bug in the MIPS C++ compiler causes problems if we try to do the cast 
// inside the ExtensionProps structure.

static const LONGLONG llszDfltAddrType  = (LONGLONG) TEXT("addrtype");
static const LONGLONG llszDfltDispName  = (LONGLONG) TEXT("System Administrator");
static const LONGLONG llszDfltEmailAddr = (LONGLONG) TEXT("sysadmin");
static const LONGLONG llszDfltDirIn     = (LONGLONG) TEXT("\\in");
static const LONGLONG llszDfltDirOut    = (LONGLONG) TEXT("\\out");
static const LONGLONG llszDfltCnvrtrIn  = (LONGLONG) TEXT("inbound");
static const LONGLONG llszDfltCnvrtrOut = (LONGLONG) TEXT("outbound");

// Setup default structure.
static SInitPropValue ExtensionProps[] =
{
    { PT_BOOLEAN, 0, TRUE},                         // IDX_CHECK_IN_BOUND  
    { PT_BOOLEAN, 0, TRUE},                         // IDX_CHECK_OUT_BOUND 
    { PT_LONG,    0, 4},                            // IDX_EDIT_THREADS_IN 
    { PT_LONG,    0, 4},                            // IDX_EDIT_THREADS_OUT
    { PT_LONG,    0, 1},                            // IDX_EDIT_MSGS_IN    
    { PT_LONG,    0, 1},                            // IDX_EDIT_MSGS_OUT   
    { PT_LONG,    0, 0},                            // IDX_EDIT_SLEEP_IN   
    { PT_LONG,    0, 0},                            // IDX_EDIT_SLEEP_OUT  
    { PT_LONG,    0, INFINITE},                     // IDX_EDIT_POLLING_IN 
    { PT_LONG,    0, INFINITE},                     // IDX_EDIT_POLLING_OUT
    { PT_STRING8, 0, llszDfltAddrType},             // IDX_ADDR_TYPE       
    { PT_STRING8, 0, llszDfltDispName},             // IDX_DISP_NAME       
    { PT_STRING8, 0, llszDfltEmailAddr},            // IDX_EMAIL_ADDR      
    { PT_STRING8, 0, llszDfltDirIn},                // IDX_DIR_IN          
    { PT_STRING8, 0, llszDfltDirOut},               // IDX_DIR_OUT         
    { PT_STRING8, 0, llszDfltCnvrtrIn},             // IDX_CONVERTER_IN
    { PT_STRING8, 0, llszDfltCnvrtrOut},            // IDX_CONVERTER_OUT
};

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CSGWDlg, CAdminDialog)
	//{{AFX_MSG_MAP(CSGWDlg)
	ON_EN_CHANGE(IDC_EDIT_DIR_IN, OnEnChange)
	ON_BN_CLICKED(IDC_CHECK_IN_BOUND, OnBnClicked)
	ON_EN_CHANGE(IDC_EDIT_DIR_OUT, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_DISP_NAME, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_EMAIL_ADDR, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_MSGS_IN, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_MSGS_OUT, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_POLLING_IN, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_POLLING_OUT, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_SLEEP_IN, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_SLEEP_OUT, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_THREADS_IN, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_THREADS_OUT, OnEnChange)
	ON_BN_CLICKED(IDC_CHECK_OUT_BOUND, OnBnClicked)
	ON_EN_CHANGE(IDC_EDIT_ADDR_TYPE, OnEnChange)
    ON_EN_CHANGE(IDC_EDIT_CONVERTER_IN, OnEnChange)
	ON_EN_CHANGE(IDC_EDIT_CONVERTER_OUT, OnEnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//$--CSGWDlg::OnEnChange()------------------------------------------------------
// Called when an edit control is changed.
// -----------------------------------------------------------------------------

void CSGWDlg::OnEnChange() 
{
    if( !m_bRefresh)
        DataHasChanged();
}

//$--CSGWDlg::OnBnClicked()-----------------------------------------------------
// Called when a check box is changed.
// -----------------------------------------------------------------------------

void CSGWDlg::OnBnClicked() 
{
    if( !m_bRefresh)
        DataHasChanged();
}

//$--CSGWDlg::bHasHelp()--------------------------------------------------------
// Called to determine if you supply help.  Return TRUE if you do.
// -----------------------------------------------------------------------------

BOOL CSGWDlg::bHasHelp()
{
    return( TRUE);
}
    
//$--CSGWDlg::DoHelp()----------------------------------------------------------
// Called to start help.
// -----------------------------------------------------------------------------
    
VOID CSGWDlg::DoHelp()
{
    CHAR szDllPath[MAX_PATH+1] = {0};
    DWORD cchDllPath = 0;

    // Get the path and file name of this DLL.

    cchDllPath = GetModuleFileName(
        (HMODULE)(AfxGetInstanceHandle()), 
        szDllPath, 
        sizeof(szDllPath) - 1);

    // If we got back something that ends in ".DLL", then change the 
    // extension to ".HLP" and call it as the help file.

    if (cchDllPath >=4 && !stricmp(&szDllPath[cchDllPath-4],".DLL"))
    {
        strcpy(&szDllPath[cchDllPath-4], ".HLP");
        ::WinHelp( GetSafeHwnd(), szDllPath, HELP_CONTENTS, 0);
    }

    // Otherwise it's an error.

    else
    {
        MODULE_WARNING(
            "GWPERF_DLL_ENTRY_MODULE_NAME: GetModuleFileName() failed.");
    }
}

//$--CSGWDlg::Refresh()---------------------------------------------------------
// Called so that property sheet can refresh with data that may have been 
// changed by another property sheet.  Even though this DLL does not have more 
// than one property sheet that modifies the same data fields the Exchange SDK 
// provides a sample that lets an Administrator view and modify any Exchange 
// SDK packed extension data array.
// -----------------------------------------------------------------------------

void CSGWDlg::Refresh()
{
    // While in refresh mode we do not want to the enable the APPLY
    // button if we are just repainting the screen.
    m_bRefresh = TRUE;

    // Set the check boxes in the dialog.
    m_CheckInBound.SetCheck(  GetExtBool( IDX_CHECK_IN_BOUND));
    m_CheckOutBound.SetCheck( GetExtBool( IDX_CHECK_OUT_BOUND));

    // Set the numerical values in the dialog.
    static char szFmt[] = "%lu";
    SetDlgItemText( IDC_EDIT_THREADS_IN,  Format( szFmt, GetExtDWord(  IDX_EDIT_THREADS_IN)));
    SetDlgItemText( IDC_EDIT_THREADS_OUT, Format( szFmt, GetExtDWord(  IDX_EDIT_THREADS_OUT)));
    SetDlgItemText( IDC_EDIT_MSGS_IN,     Format( szFmt, GetExtDWord(  IDX_EDIT_MSGS_IN)));
    SetDlgItemText( IDC_EDIT_MSGS_OUT,    Format( szFmt, GetExtDWord(  IDX_EDIT_MSGS_OUT)));
    SetDlgItemText( IDC_EDIT_SLEEP_IN,    Format( szFmt, GetExtDWord(  IDX_EDIT_SLEEP_IN)));
    SetDlgItemText( IDC_EDIT_SLEEP_OUT,   Format( szFmt, GetExtDWord(  IDX_EDIT_SLEEP_OUT)));
    
    if( GetExtDWord( IDX_EDIT_POLLING_IN) == INFINITE)
        SetDlgItemText( IDC_EDIT_POLLING_IN,  szNOTIFICATION); 
    else
        SetDlgItemText( IDC_EDIT_POLLING_IN,  Format( szFmt, GetExtDWord(  IDX_EDIT_POLLING_IN )));
    
    if( GetExtDWord( IDX_EDIT_POLLING_OUT) == INFINITE)
        SetDlgItemText( IDC_EDIT_POLLING_OUT, szNOTIFICATION); 
    else
        SetDlgItemText( IDC_EDIT_POLLING_OUT, Format( szFmt, GetExtDWord(  IDX_EDIT_POLLING_OUT)));

    // Place strings in the dialog.
    SetDlgItemText( IDC_EDIT_ADDR_TYPE,     GetExtString( IDX_ADDR_TYPE));   
    SetDlgItemText( IDC_EDIT_DISP_NAME,     GetExtString( IDX_DISP_NAME));   
    SetDlgItemText( IDC_EDIT_EMAIL_ADDR,    GetExtString( IDX_EMAIL_ADDR));  
    SetDlgItemText( IDC_EDIT_DIR_IN,        GetExtString( IDX_DIR_IN));      
    SetDlgItemText( IDC_EDIT_DIR_OUT,       GetExtString( IDX_DIR_OUT));     
    SetDlgItemText( IDC_EDIT_CONVERTER_IN,  GetExtString( IDX_CONVERTER_IN));
    SetDlgItemText( IDC_EDIT_CONVERTER_OUT, GetExtString( IDX_CONVERTER_OUT));

    // Ending refresh mode.
    m_bRefresh = FALSE;
}

// -----------------------------------------------------------------------------

BOOL CSGWDlg::OnInitDialog() 
{
	CAdminDialog::OnInitDialog();
	
    ASSERTERROR( SGWDATA_PROP_COUNT == ARRAY_CNT( ExtensionProps), "Property count and default array inconsistent.");

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Subclass all controls.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( FAILED( HrSubclassWindow( IDC_CHECK_IN_BOUND,     m_CheckInBound)))   
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_CHECK_OUT_BOUND,    m_CheckOutBound)))  
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_ADDR_TYPE,     m_EditAddrType)))   
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_DISP_NAME,     m_EditDispName)))   
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_EMAIL_ADDR,    m_EditEmailAddr)))  
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_THREADS_IN,    m_EditThreadsIn)))  
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_THREADS_OUT,   m_EditThreadsOut))) 
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_MSGS_IN,       m_EditMsgsIn)))     
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_MSGS_OUT,      m_EditMsgsOut)))    
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_SLEEP_IN,      m_EditSleepIn)))    
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_SLEEP_OUT,     m_EditSleepOut)))   
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_POLLING_IN,    m_EditPollingIn)))  
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_POLLING_OUT,   m_EditPollingOut))) 
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_DIR_IN,        m_EditDirIn)))      
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_DIR_OUT,       m_EditDirOut)))     
        return( TRUE);                                                        
                                                                              
    if( FAILED( HrSubclassWindow( IDC_EDIT_CONVERTER_IN,  m_EditConverterIn)))
        return( TRUE);

    if( FAILED( HrSubclassWindow( IDC_EDIT_CONVERTER_OUT, m_EditConverterOut)))  
        return( TRUE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Initialize the extension data to defaults if it does not exist.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Is extension data available? 
    if( GetExtCount() == 0)
    {   // NO, extension data is not available so set the 
        // memory copy of this to the defaults.
        if( FAILED( HrSetExtProps( SGWDATA_PROP_COUNT, ExtensionProps)))
            return( TRUE);
        
        // Save it in Admin's memory buffer as well.
        CAdminDialog::bSaveData();
    }

	return( TRUE);  // Return TRUE unless you set the focus to a control.
}

//$--CSGWDlg::bIsValidString()--------------------------------------------------
// Validate that a string is not empty and modify the extension data property
// in memory.
// -----------------------------------------------------------------------------

BOOL CSGWDlg::bIsValidString( 
    IN ULONG iProp,         // Index of property
    IN CEditExt& editCtrl)  // Edit control containing data to validate.
{
    CString str = editCtrl.GetString();
    if( str.GetLength() == 0)
    {
        InvalidEntry( IDS_INVALID_STRING, editCtrl);
        return( FALSE);
    }
    CHRESULT hr = HrModExtString( iProp, str);
    if( FAILED( hr))
        return( FALSE);

    return( TRUE);
}

// -----------------------------------------------------------------------------
// Validate that a ulong is within a specified range and modify the extension 
// data property in memory.
// -----------------------------------------------------------------------------

BOOL CSGWDlg::bIsValidULong(
    IN ULONG     iProp,         // Index of property
    IN CEditExt& editCtrl,  // Edit control containing data to validate.
    IN ULONG     ulLow,
    IN ULONG     ulHigh,
    IN int       idErrMsg)
{
    ULONG ul = editCtrl.GetULong();
    if( ul < ulLow || ul > ulHigh)
    {
        InvalidEntry( idErrMsg, editCtrl);
        return( FALSE);
    }
    CHRESULT hr = HrModExtDWord( iProp, ul);
    if( FAILED( hr))
        return( FALSE);

    return( TRUE);
}

//$--CSGWDlg::bSaveData()-------------------------------------------------------
// Called when a different property sheet has been selected or when either the 
// OK or APPLY NOW button is pressed.  Returns TRUE if data has been validated
// and saved.
//
// When we call the CAdminDialog::bSaveData() function it gets saved in an
// admin memory space.  This makes it available to other property sheets that
// might be viewing the same data.
// -----------------------------------------------------------------------------

BOOL CSGWDlg::bSaveData()
{
    CHRESULT hr;
    ULONG    ul = 0;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Check boxes need no validation so just store them in the property value array.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -    

    hr = HrModExtBool(  IDX_CHECK_IN_BOUND,   m_CheckInBound.GetCheck());
    if( FAILED( hr))
        return( FALSE);

    hr = HrModExtBool(  IDX_CHECK_OUT_BOUND,  m_CheckOutBound.GetCheck());
    if( FAILED( hr))
        return( FALSE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// The thread count must be between 1 and 20.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( !bIsValidULong( IDX_EDIT_THREADS_IN, m_EditThreadsIn, 1, 20, IDS_INVALID_THREAD_CNT))
        return( FALSE);

    if( !bIsValidULong( IDX_EDIT_THREADS_OUT, m_EditThreadsOut, 1, 20, IDS_INVALID_THREAD_CNT))
        return( FALSE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Messages per thread must be between one and MAX_ULONG.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( !bIsValidULong( IDX_EDIT_MSGS_IN, m_EditMsgsIn, 1, MAX_ULONG, IDS_INVALID_MSGS_PER_THREAD))
        return( FALSE);

    if( !bIsValidULong( IDX_EDIT_MSGS_OUT, m_EditMsgsOut, 1, MAX_ULONG, IDS_INVALID_MSGS_PER_THREAD))
        return( FALSE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// The sleep between messages must be between zero and five minutes.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( !bIsValidULong( IDX_EDIT_SLEEP_IN, m_EditSleepIn, 0, 60000 * 5, IDS_INVALID_SLEEP_BETWEEN_MSGS))
        return( FALSE);

    if( !bIsValidULong( IDX_EDIT_SLEEP_OUT, m_EditSleepOut, 0, 60000 * 5, IDS_INVALID_SLEEP_BETWEEN_MSGS))
        return( FALSE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Polling interval needs no validation so just store them in the property value 
// array.  Entering anything but a number causes us to set to notification.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( (ul = m_EditPollingIn.GetULong()) == 0)
        hr = HrModExtDWord( IDX_EDIT_POLLING_IN, INFINITE);   // Notification
    else
        hr = HrModExtDWord( IDX_EDIT_POLLING_IN, ul);
    if( FAILED( hr))
        return( FALSE);

    if( (ul = m_EditPollingOut.GetULong()) == 0)
        hr = HrModExtDWord( IDX_EDIT_POLLING_OUT, INFINITE);   // Notification
    else
        hr = HrModExtDWord( IDX_EDIT_POLLING_OUT, ul);
    if( FAILED( hr))
        return( FALSE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Validate that the string values are not empty.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( !bIsValidString( IDX_ADDR_TYPE, m_EditAddrType))
        return( FALSE);

    if( !bIsValidString( IDX_DISP_NAME, m_EditDispName))
        return( FALSE);

    if( !bIsValidString( IDX_EMAIL_ADDR, m_EditEmailAddr))
        return( FALSE);

    if( !bIsValidString( IDX_DIR_IN, m_EditDirIn))
        return( FALSE);

    if( !bIsValidString( IDX_DIR_OUT, m_EditDirOut))
        return( FALSE);

    if( !bIsValidString( IDX_CONVERTER_IN, m_EditConverterIn))
        return( FALSE);

    if( !bIsValidString( IDX_CONVERTER_OUT, m_EditConverterOut))
        return( FALSE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// We are complete, the data is valid, so lets save it.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -    
    return( CAdminDialog::bSaveData());
}
    
// -----------------------------------------------------------------------------
// Called when either the OK or APPLY NOW button is pressed and after bSaveData().
// Return TRUE if it is OK to committed the saved data.
// -----------------------------------------------------------------------------

BOOL CSGWDlg::bCommitData()
{
    MessageBox2( IDS_RESTARTGATEWAY);
    return( TRUE);
}

// -----------------------------------------------------------------------------
// Admin will call this function directly (it is not a member function).  It is
// called once for each standard property sheet.  We have the option to keep one
// or more of the standard property sheets from showing.
// -----------------------------------------------------------------------------

BOOL PASCAL bShowPage( UINT iddAdminPage)
{
    BOOL bRet = TRUE;   // Show the standard property sheet.
    switch( iddAdminPage)
    {   // Do NOT show the following sheets:
        case iddGWSchedule:
        case iddGWDelivery_Restrictions:
        case iddGWAdvanced:
        case iddGWImportContainer:
        case iddGWExportContainers:
            bRet = FALSE;
    }
    return( bRet);
}

// $--iStartPage()--------------------------------------------------------------
// This function is called once durring initialization.  Return -1 to cause the 
// first standard property sheet to be displayed.  Or return the index of one of 
// our property sheets to have it come up first.
// -----------------------------------------------------------------------------
/*
INT PASCAL iStartPage( void)
{
    int i = -1; // Default to the first standard property sheet.
    return( i);
}
*/
// -----------------------------------------------------------------------------
    
