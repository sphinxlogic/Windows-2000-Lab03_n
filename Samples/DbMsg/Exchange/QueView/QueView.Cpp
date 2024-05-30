// -----------------------------------------------------------------------------
// QueView.cpp : Implements an Exchange Administration property sheet to be used
//               for viewing the MTS-IN and MTS-OUT folders of a gateway.
//
// NOTE: To use the Delete and NDR buttons the PR_GW_ADMIN_OPERATIONS on each
//       folder you want this capability for must be set to 14.  Either do this 
//       in your gateway application or use MDBVU32.EXE to do this.  At the time
//       this note was written PR_GW_ADMIN_OPERATIONS equates to 0x6658.  When 
//       creating it create it as a ULONG.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
//#define _EXAMPLES_
#include "helpers.h"
#include "queview.h"
#include "property.h"
#include "PropDlg.h"
#include "MAPIMsg.h"
#include "BinArray.h"
#include "DynArray.h"
#include "delmsgdl.h"
#include "faildmsg.h"

/* #define INITGUID
#include <initguid.h>
#include <edkguid.h>
#define USES_IID_IMessage
#define USES_IID_IMAPIProp
#define USES_IID_IMAPIPropData
#define USES_IID_IMAPIFolder
#define USES_IID_IABContainer
#define USES_IID_IAddrBook
#define USES_IID_IMAPIFormInfo
#define USES_IID_IMailUser
#define USES_IID_IAttachment
#define USES_IID_IDistList
#define USES_IID_IMAPIStatus
#define USES_IID_IMAPISession
#define USES_IID_IMsgStore
#define USES_IID_IProfSect
#include <mapiguid.h>
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------------------------

const UINT iRefreshTimerId = 1; // The one and only timer we use.
UINT nRefreshTime = 1000;  // One second wait before refreshing combo box.

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CQueViewDlg, CAdminDialog)
	//{{AFX_MSG_MAP(CQueViewDlg)
	ON_BN_CLICKED(IDC_CMD_REFRESH, OnCmdRefresh)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CMD_DETAILS, OnCmdDetails)
	ON_CBN_SELCHANGE(IDC_COMBO_FOLDERS, OnSelChangeComboFolders)
	ON_LBN_SELCHANGE(IDC_LIST_MSGS, OnSelChangeListMsgs)
	ON_BN_CLICKED(IDC_CMD_DELETE, OnCmdDelete)
	ON_BN_CLICKED(IDC_CMD_NDR, OnCmdNdr)
	ON_WM_TIMER()
	ON_LBN_DBLCLK(IDC_LIST_MSGS, OnCmdDetails)
	ON_CBN_KILLFOCUS(IDC_COMBO_FOLDERS, OnKillFocusComboFolders)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//$--CQueViewDlg::CQueViewDlg()-------------------------------------------------
// CONSTRUCTOR:
// -----------------------------------------------------------------------------

CQueViewDlg::CQueViewDlg() : CAdminDialog( IDD_QUEUE_VIEW, IDS_QUEUE_VIEW)
{
    m_bInitilized = FALSE;
    m_bMTSIn = FALSE;
    m_pGWmdb = NULL;
    m_hPropDlgTemplate = NULL;
}

//$--CQueViewDlg::~CQueViewDlg()-------------------------------------------------
// DESTRUCTOR:
// -----------------------------------------------------------------------------

CQueViewDlg::~CQueViewDlg()
{
    if( m_hPropDlgTemplate)
        FreeDialogTemplate( &m_hPropDlgTemplate);
}

//$--CQueViewDlg::bHasHelp()----------------------------------------------------
// Called to determine if you supply help.  Return TRUE if you do.
// -----------------------------------------------------------------------------

BOOL CQueViewDlg::bHasHelp()
{
    return( TRUE);
}
    
//$--CQueViewDlg::DoHelp()------------------------------------------------------
// Called to start help.
// -----------------------------------------------------------------------------
    
VOID CQueViewDlg::DoHelp()
{
    ::WinHelp( GetSafeHwnd(), TEXT( "queview.hlp"), HELP_CONTENTS, 0);
}

//$--CQueViewDlg::Refresh()-----------------------------------------------------
// Called when the property sheet has been activated or reactivated.
// -----------------------------------------------------------------------------

void CQueViewDlg::Refresh()
{
    OnCmdRefresh();
}

//$--CQueViewDlg::OnCmdRefresh()------------------------------------------------
// Handles the Refresh button.  Uses the selected folder to fill the list box 
// with Sender, Subject, and Size of each message in the folder.  Also refreshes
// the combo box with the current list of folders.
// -----------------------------------------------------------------------------

void CQueViewDlg::OnCmdRefresh()
{
    DEBUGPUBLIC( "CQueViewDlg::OnCmdRefresh()");
    if( !::IsWindow(m_hWnd))
        return; // Our list box is not connected to a window.

    // Initialize the folder combo box with the current list.
    CHRESULT hr = m_cbFolders.HrInitialize( m_pGWmdb);
    if( FAILED( hr))
        return;
    
    // Get the folder we have selected.
    LPMAPIFOLDER pFolder = m_cbFolders.GetFolder();
    if( !pFolder)
    {
        HR_LOG( E_FAIL);
        return;
    }

    // Get the contents table for the folder.
    CMAPIInterface< LPMAPITABLE> pContentsTbl;
    hr = pFolder->GetContentsTable( MAPI_DEFERRED_ERRORS, &pContentsTbl);
    if( FAILED( hr))
        return;

    // Fill the list box with the data from this table.
    hr = m_lbMsgs.HrFillBox( pContentsTbl);
    if( FAILED( hr))
        return;

    OnSelChangeListMsgs();    
}                       

//$--CQueViewDlg::OnInitDialog()------------------------------------------------
// Initialize the dialog, connect class objects to controls, open MDB and folders.
// -----------------------------------------------------------------------------

BOOL CQueViewDlg::OnInitDialog() 
{
    DEBUGPUBLIC( "CQueViewDlg::OnInitDialog()");

	// Pay tribute to our ancestors.
	CAdminDialog::OnInitDialog();
    
    // This object will validate that initialization completed when this 
    // function exits.  If it has not then a message will be displayed.
    CMsgOnFail bInitStatus( "Could not logon to the information store.", "Queue Viewer");

    if( !GetMAPISession())
        return( TRUE);  // We don't have a session handle so we must bail out now.

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Code to open the default message store.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Get the entry ID of the default message store.
    ULONG cbeid = 0;              // count of bytes in entry ID
    CMAPIBuffer<LPENTRYID>  lpeid; // Entry ID of default store
    CHRESULT hr = HrMAPIFindDefaultMsgStore( GetMAPISession(), &cbeid, &lpeid);
    if( FAILED( hr))
        return( TRUE);
    ASSERTERROR( cbeid != 0, "Entry ID count should not be zero."); 
    ASSERTERROR( lpeid != NULL, "NULL lpeid pointer");
    
    // Open the default message store.
    DEBUGACTION( "Opening Default Message Store");
    hr = GetMAPISession()->OpenMsgStore( 0, cbeid, lpeid, NULL, MDB_NO_DIALOG | MDB_WRITE, &m_pMDB);
    if( FAILED(hr))
        return( TRUE);
    ASSERTERROR( m_pMDB != NULL, "NULL lpMDB pointer");

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Convert server name.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int cb = WideCharToMultiByte( CP_ACP, 0, GetDNHomeMDB(), -1, NULL, 0, NULL, NULL);
    if( cb == 0)
    {
        HR_LOG( E_FAIL);
        return( TRUE);
    }

    CString sServer;
    char* pszServer = sServer.GetBuffer(cb);
    cb = WideCharToMultiByte( CP_ACP, 0, GetDNHomeMDB(), -1, pszServer, cb, NULL, NULL);
    if( cb == 0)
    {
        HR_LOG( E_FAIL);
        return( TRUE);
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Convert container distinguished name.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cb = WideCharToMultiByte( CP_ACP, 0, GetDN(), -1, NULL, 0, NULL, NULL);
    if( cb == 0)
    {
        HR_LOG( E_FAIL);
        return( TRUE);
    }

    CString sDN;
    char* pszDN = sDN.GetBuffer(cb);
    cb = WideCharToMultiByte( CP_ACP, 0, GetDN(), -1, pszDN, cb, NULL, NULL);
    if( cb == 0)
    {
        HR_LOG( E_FAIL);
        return( TRUE);
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Now logon to the message database of this gateway.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    hr = HrMailboxLogon(           
        GetMAPISession(),    // Ptr to MAPI session handle.
        m_pMDB,
        pszServer,           // Ptr to server DN.
        pszDN,               // Ptr to mailbox DN.
        &m_pGWmdb);          // Ptr to gateway mailbox message store ptr.

    if( FAILED( hr))
        return( TRUE);
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Initialize the m_cbFolder object which will connect it to the 
// IDC_COMBO_FOLDERS combo box window, and get list of folders.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( HrSubclassWindow( IDC_COMBO_FOLDERS, m_cbFolders) != NOERROR)
        return( TRUE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Initialize the m_lbMsgs object by connecting it to the IDC_LIST_MSGS list 
// box window.  Also set the tab stops for the list box.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( HrSubclassWindow( IDC_LIST_MSGS, m_lbMsgs) != NOERROR)
        return( TRUE);

    int nTabStops[] = { 6, 12, 76, 215};
    m_lbMsgs.SetTabStops( ARRAY_CNT( nTabStops), nTabStops);
    m_lbMsgs.SetHorizontalExtent( 1000);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Connect the buttons to CButton objects.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( HrSubclassWindow( IDC_CMD_DELETE, m_btnDelete) != NOERROR)
        return( TRUE);

    if( HrSubclassWindow( IDC_CMD_NDR, m_btnNDR) != NOERROR)
        return( TRUE);

    if( HrSubclassWindow( IDC_CMD_REFRESH, m_btnRefresh) != NOERROR)
        return( TRUE);
    m_btnRefresh.EnableWindow( TRUE);

    if( HrSubclassWindow( IDC_CMD_DETAILS, m_btnDetails) != NOERROR)
        return( TRUE);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // We succeed, do not display a message.
    bInitStatus.Succeeded();
    	
	return( TRUE);  // return TRUE unless you set the focus to a control
}

// -----------------------------------------------------------------------------
// Do the cleanup work for member data.
// MAPI Interfaces must be released here.  We can not wait until the DLL exits
// to release the object interfaces since the code goes single threaded at that 
// time and causes deadlocks while waiting for MAPI threads to exit.
// -----------------------------------------------------------------------------

void CQueViewDlg::OnDestroy() 
{
	CAdminDialog::OnDestroy();
    ULRELEASE( m_pMDB); // Must be done here.  See note above.
    HRESULT hr = HrMailboxLogoff( &m_pGWmdb);
}

//$--CQueViewDlg::OnSelChangeComboFolders()-------------------------------------
// There are three functions that deal with changes in the folders combo box.
// They are: OnTimer, OnKillFocusComboFolders, and this one.  The reason we can
// not just refresh right here if the selection changes is that the refresh
// involves opening folders and reading the contents which takes a little bit
// of time.  If the user is scrolling through the list of folders using the 
// arrow keys it gets slow and jerky.
// 
// To deal with this we (re)set a timer each time the selection changes.  If
// the timer goes off the user has stopped scrolling through the list and we
// can refresh without it being jerky.  Also if the control looses focus we
// want to immediately refresh the folder and the message lists.
// -----------------------------------------------------------------------------

void CQueViewDlg::OnSelChangeComboFolders() 
{
    // Kill the old timer that may be running so we can start it again.
    KillTimer( iRefreshTimerId);
    
    // Set the timer to delay opening the folder and reading its contents.
    SetTimer( iRefreshTimerId, nRefreshTime, NULL);
}

//$--CQueViewDlg::OnTimer()-----------------------------------------------------
// If the selection changed we refresh the combo box of folders, open the new
// folder, and then update the list box data.
//
// (See CQueViewDlg::OnSelChangeComboFolders() above for a full description.)
// -----------------------------------------------------------------------------

void CQueViewDlg::OnTimer( UINT nIDEvent) 
{
    // We no longer need the timer.
    KillTimer( nIDEvent);

    // Refresh the dialog with the current data only 
    // if the selection has truly changed.
    if( m_cbFolders.bSelectionChanged())
        OnCmdRefresh(); 
}

//$--CQueViewDlg::OnKillFocusComboFolders()-------------------------------------
// If the selection changed we refresh the combo box of folders, open the new
// folder, and then update the list box data.  
//
// (See CQueViewDlg::OnSelChangeComboFolders() above for a full description.)
// -----------------------------------------------------------------------------

void CQueViewDlg::OnKillFocusComboFolders() 
{
    // Has the selection has changed?
    if( m_cbFolders && m_cbFolders.bSelectionChanged())
    {   // YES, it has so kill the timer and refresh the 
        // dialog with the current data.
        KillTimer( iRefreshTimerId);
        OnCmdRefresh(); 
    }
}

//$--CQueViewDlg::OnSelChangeListMsgs()-----------------------------------------
// Enable and disable the buttons depending upon the number of list box items
// that are selected.
// -----------------------------------------------------------------------------

void CQueViewDlg::OnSelChangeListMsgs()
{
	int nCnt = m_lbMsgs.GetSelCount();
    
#if 1   // Set to 0 to force buttons on for testing purposes.
    // Button enabled when delete is available and at least one is selected. 
    m_btnDelete.EnableWindow( m_cbFolders.bIsDelete() && nCnt != 0); 
    
    // Button enabled when delete is available and at least one is selected.
    m_btnNDR.EnableWindow( m_cbFolders.bIsNDR() && m_cbFolders.bIsDefer() && nCnt != 0);      
#else
    // Code to enable buttons when testing.
    m_btnDelete.EnableWindow( TRUE); 
    m_btnNDR.EnableWindow( TRUE);      
#endif

    // Button enabled when only one is selected.
    m_btnDetails.EnableWindow( nCnt == 1);  
}

// -----------------------------------------------------------------------------
// Displays the details of a single message.  Should only get here when only
// one line is selected in the list box.
// -----------------------------------------------------------------------------

void CQueViewDlg::OnCmdDetails() 
{
    DEBUGPUBLIC( "CQueViewDlg::OnCmdDetails()");
	ASSERTERROR( m_lbMsgs.GetSelCount() == 1, "This button should be disabled when there are not 1 items selected.");
    ASSERTERROR( m_cbFolders.GetFolder() != NULL, "There should be a folder available.");

    // Get the index of the entry id for the selected message.
    int ii = -1;
    m_lbMsgs.GetSelItems( 1, &ii);
	ASSERTERROR( ii >= 0 && ii < m_lbMsgs.GetCount(), "INVALID EID index.");

    // Open the selected message.
    ULONG        cb = m_lbMsgs.GetByteCnt( ii);
    LPENTRYID    pEID = m_lbMsgs.GetEID( ii);
    CMAPIMessage MAPIMsg( m_cbFolders.GetFolder(), cb, pEID);
    if( FAILED( MAPIMsg.m_hr))
    {   // Construction of MAPIMsg failed!  Probably messages are obsolete.
        MessageBox2( IDS_MESSAGE_GONE);
        OnCmdRefresh();    
        return; 
    }

    // List of properties that we are interested in.
    static SizedSPropTagArray( 13, sProps) = 
    { 13, 
        {
            PR_ARRIVAL_TIME, 
            PR_DISPLAY_TO, 
            PR_GW_ADMIN_OPERATIONS,
            PR_HASATTACH,
            PR_IMPORTANCE,
            PR_MESSAGE_CLASS,
            PR_MESSAGE_SIZE,
            PR_ORIGINATOR_ADDR,
            PR_ORIGINATOR_ADDRTYPE,
            PR_ORIGINATOR_NAME, 
            PR_PRIORITY,
            PR_SENSITIVITY,
            PR_SUBJECT
        }
    };

    // Get the properties from the message using a CProperty interface object
    // to access and contain properties.
    CProperty iProp;
    CHRESULT hr = iProp.GetProps( MAPIMsg, (LPSPropTagArray) &sProps);
    if( FAILED( hr))
        return;

    // Load the dialog into memory as a template so the fonts 
    // and language get set appropriatly.
    if( !m_hPropDlgTemplate)
    {
        m_hPropDlgTemplate = LoadDialogTemplate( IDD_PROPS);
        if( !m_hPropDlgTemplate)
        {
            hr = HR_LOG( E_FAIL);
            return;
        }
    }

    // Initialize the dialog listing the properties.
    CPropDlg PropDlg( &iProp);
    if( !PropDlg.InitModalIndirect( m_hPropDlgTemplate))
    {
        hr = HR_LOG( E_FAIL);
        return;
    }

    // Show the dialog listing the properties.
    PropDlg.DoModal();
}

// -----------------------------------------------------------------------------

void CQueViewDlg::OnCmdDelete() 
{
    int iUserAnswer;
    if( m_cbFolders.bIsDefer())
    {
        CDelMsgDlg DelMsgDlg;
        iUserAnswer = DelMsgDlg.DoModal();
    }
    else
    {
        iUserAnswer = MessageBox2( IDS_DELETENOW, IDS_DELETEMSGTITLE, 
                                  MB_YESNO | MB_ICONQUESTION);
    }

    switch( iUserAnswer)
    {
        case IDYES:
        case IDC_CMD_DELETE_NOW:
            DeleteMsgsNow();
            break;
        
        case IDC_CMD_DELETE_BY_GATEWAY:
            DeferMsgsAction( ADMINOP_DELETE);
            break;
        
        default:
            break;
    }
}

//$--CQueViewDlg::DeleteMsgsNow()-----------------------------------------------
// Delete the selected messages right now using MAPI.
// -----------------------------------------------------------------------------

void CQueViewDlg::DeleteMsgsNow() 
{
    DEBUGPUBLIC( "CQueViewDlg::DeleteMsgsNow()");
    // Get a pointer to the folder that contain the messages we will be working on.
    LPMAPIFOLDER pFolder = m_cbFolders.GetFolder();
	if( !pFolder)
    {
        return;
    }

    // Determine the count of messages to delete.
    int nSelCnt = m_lbMsgs.GetSelCount();
    if( nSelCnt < 1)
    {
        return;
    }

    // Allocate an array to hold the indexes of messages to delete.
    CDynamicArray< int> IndexArray( nSelCnt);
    if( !IndexArray)
    {
        HR_LOG( E_OUTOFMEMORY);
        return;
    }

    // Create the array needed to delete all selected messages at once.
    m_lbMsgs.GetSelItems( nSelCnt, IndexArray);
    CBinArray EIDList( nSelCnt);
    int* pIndex = IndexArray;
    while( nSelCnt)
    {
        if( !EIDList.bAdd( m_lbMsgs.GetByteCnt( *pIndex), (LPBYTE) m_lbMsgs.GetEID( *pIndex)))
        {
            HR_LOG( E_FAIL);
            return;
        }

        // Move on to next message.
        pIndex ++;
        nSelCnt--;
    }

    // Delete all selected messages now.
    CHRESULT hr = pFolder->DeleteMessages( EIDList, (ULONG) GetSafeHwnd(), NULL, MESSAGE_DIALOG);
    if( FAILED( hr))
        return;

    // Refresh the dialog with the messages that are now in the folder.
    OnCmdRefresh();
}

//$--CQueViewDlg::DeferMsgsAction()---------------------------------------------
// This function sets the specified action flags in the PR_GW_ADMIN_OPERATIONS 
// property of each message that is selected.  The only two action flags that 
// are appropriate for setting are ADMINOP_DELETE or ADMINOP_NDR.
//
// This affectivly causes defered deletions or NDRs of a messages.
// -----------------------------------------------------------------------------

void CQueViewDlg::DeferMsgsAction(
    ULONG ulAction)     // Should be either ADMINOP_DELETE or ADMINOP_NDR.
{
    // Get a pointer to the folder that contain the messages we will be working on.
    LPMAPIFOLDER pFolder = m_cbFolders.GetFolder();
	if( !pFolder)
        return;

    // Determine the count of messages to modify.
    int nSelCnt = m_lbMsgs.GetSelCount();
    if( nSelCnt < 1)
        return;

    // Allocate an array to hold the indexes of messages to modify.
    CDynamicArray< int> IndexArray( nSelCnt);
    if( !IndexArray)
    {
        HR_LOG( E_OUTOFMEMORY);
        return;
    }

    // Mark all selected messages to be modified.
    m_lbMsgs.GetSelItems( nSelCnt, IndexArray);
    int* pIndex = IndexArray;
    for( ; nSelCnt; pIndex ++, nSelCnt--)
    {
        ULONG cb = m_lbMsgs.GetByteCnt( *pIndex);
        LPENTRYID pEID = m_lbMsgs.GetEID( *pIndex);
        
        // Open the message.
        CMAPIMessage MAPIMsg( pFolder, cb, pEID, 0);
        if( FAILED( MAPIMsg.m_hr))
        {   // Log error but continue to try and modify the other messages.
            continue;   // Move on to next message.
        }

        // We have an opened message.  Now set the properties.
        SPropValue PropVal;
        PropVal.ulPropTag = PR_GW_ADMIN_OPERATIONS;
        PropVal.Value.ul = m_lbMsgs.dwGetFlags( *pIndex) | ulAction;
        CHRESULT hr = MAPIMsg->SetProps( 1, &PropVal, NULL);
        if( FAILED( hr))
        {   // Log error but continue to try and modify the other messages.
            continue;   // Move on to next message.
        }
        
        // We modified the properties successfully.  Now save the changes.
        hr = MAPIMsg->SaveChanges(0);
        if( FAILED( hr))
        {   // Log error but continue to try and modify the other messages.
            continue;   // Move on to next message.
        }
    }
    OnCmdRefresh();
}

// -----------------------------------------------------------------------------

void CQueViewDlg::OnCmdNdr() 
{
    DEBUGPUBLIC( "CQueViewDlg::OnCmdNdr()");
    int iUserAnswer = MessageBox2( IDS_NDRNOW, IDS_NDRMSGTITLE, 
                              MB_YESNO | MB_ICONQUESTION);

    if( iUserAnswer == IDYES)
        DeferMsgsAction( ADMINOP_NDR);
}

// -----------------------------------------------------------------------------

