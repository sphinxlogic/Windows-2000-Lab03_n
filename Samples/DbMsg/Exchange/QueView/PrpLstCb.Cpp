// -----------------------------------------------------------------------------
// prpLstCb.cpp: Implements methods for the Queue Viewer's List box and Combo Box.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "prplstcb.h"
#include "helpers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// $--CProps::CProps()----------------------------------------------------------
// CONSTRUCTOR
// -----------------------------------------------------------------------------

CProps::CProps( ULONG cbEID, BYTE* pEID, DWORD dwFlags)
{
    m_cbEID = cbEID;
    if( m_cbEID == 0)
        m_pEID = NULL;
    else    
    {
        m_pEID = new BYTE[ m_cbEID];
        memcpy( m_pEID, pEID, m_cbEID);
    }
    m_dwFlags = dwFlags;
}

// $--CProps::~CProps()---------------------------------------------------------
// DESTRUCTOR
// -----------------------------------------------------------------------------

CProps::~CProps()
{
    if( m_pEID)
        delete [] m_pEID;
}

// $--CPropsListBox::CPropsListBox()------------------------------------------------
// CONSTRUCTOR
// -----------------------------------------------------------------------------

CPropsListBox::CPropsListBox()
{
    static SizedSPropTagArray(5L,sPropColumns) = { 5L, {PR_GW_ADMIN_OPERATIONS, PR_ENTRYID, PR_ORIGINATOR_NAME, PR_SUBJECT, PR_MESSAGE_SIZE}};
    static SizedSSortOrderSet(1L,sSortPrioSet) = { 1L, 0L, 0L, { PR_CLIENT_SUBMIT_TIME, TABLE_SORT_ASCEND}};
    m_psPropColumns = (LPSPropTagArray) &sPropColumns;
    m_psSortPrioSet = (LPSSortOrderSet) &sSortPrioSet;

}

// $--CPropsListBox::HrAddItem()--------------------------------------------------
// This virtual member function is called from HrFillBox().  It extracts the 
// properties from pProps into useable objects, formats them, and then add them 
// to the list box.
// -----------------------------------------------------------------------------

HRESULT CPropsListBox::HrAddItem(  // Returns HRESULT
     CProperty& Properties)  // Ptr to properties of EID, sender, subject, & size.
{
    CString sFlags;
    if( !m_pProps)
        sFlags = "\t\t";
    else
    {
        if( m_pProps->bIsDelete())
            sFlags += "d";
        if( m_pProps->bIsNDR())
            sFlags += "\tn\t";
        else
            sFlags += "\t\t";
    }

    // Take only the mailbox name of the sender distinguished name.
    CString sSenderName = Properties.szGetPrValue();
    sSenderName.MakeLower();
    CHAR szStrToFind[] = "/cn=recipients/cn=";
    int ii = sSenderName.Find( szStrToFind);
    sSenderName = Properties.szGetPrValue();
    if( ii > 0)
        // Take only the name.
        sSenderName = sSenderName.Mid( ii + sizeof( szStrToFind) - 1); 
        
    // Subject.
    Properties.Next();
    CString sSubject = Properties.szGetPrValue();

    // Size.
    Properties.Next();
    CString sSize = Properties.szGetPrValue();

    // Display the originator, subject, and size by adding to list box.
    CString sBuffer;
    sBuffer.Format( "%s%-.12s\t%-.42s\t%.14s", sFlags.GetBuffer(0), sSenderName.GetBuffer(0), 
                    sSubject.GetBuffer(0), sSize.GetBuffer(0));
    AddString( sBuffer);

    return( NOERROR);
}

// $--CPropsComboBox::CPropsComboBox()------------------------------------------
// CONSTRUCTOR
// -----------------------------------------------------------------------------

CPropsComboBox::CPropsComboBox() : m_sCurFolderName( TEXT("MTS-OUT"))
{
    static SizedSPropTagArray(4L,sPropColumns) = { 4L, {PR_GW_ADMIN_OPERATIONS, PR_ENTRYID, PR_DISPLAY_NAME, PR_CONTENT_COUNT}};
    static SizedSSortOrderSet(1L,sSortPrioSet) = { 1L, 0L, 0L, { PR_DISPLAY_NAME, TABLE_SORT_ASCEND}};
    m_psPropColumns = (LPSPropTagArray) &sPropColumns;
    m_psSortPrioSet = (LPSSortOrderSet) &sSortPrioSet;
    m_iFolder = -1;
    m_pFolder = NULL;
    m_pMDB = NULL;
}

// $--CPropsComboBox::HrInitialize()----------------------------------------------
// Find all folders and open default folder.
// -----------------------------------------------------------------------------

HRESULT CPropsComboBox::HrInitialize(
    LPMDB   pMDB)   // Ptr to MDB that contain gateway folders.
{
    DEBUGPUBLIC( "CPropsComboBox::HrInitialize()");
    CHRESULT hr = CHK_CPropsComboBox_HrInitialize( pMDB);
    if(FAILED(hr))
        RETURN( hr);

    // Make sure we have a valid pMDB, even in retail builds
    if( !pMDB)
        RETURN( E_FAIL);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Find the current selection and if there is one save the display 
// name in m_sCurFolderName
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int iCurSel = GetCurSel();
    if( iCurSel != CB_ERR)
    {   // Something is selected.
        GetLBText( iCurSel, m_sCurFolderName);
        int nLen = m_sCurFolderName.Find( TEXT(" -- "));
        m_sCurFolderName.GetBufferSetLength( nLen);
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Remember the MDB ptr and open the root folder.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    m_pMDB = pMDB;

    ULONG ulObjType = 0;
    CMAPIInterface< LPMAPIFOLDER> pRootFolder;
    hr = m_pMDB->OpenEntry(
        0, NULL, NULL, MAPI_DEFERRED_ERRORS, &ulObjType, (LPUNKNOWN FAR *) &pRootFolder);
    if(FAILED(hr))
        RETURN( hr);

    ASSERTERROR(ulObjType == MAPI_FOLDER, "ulObjType is not a MAPI_FOLDER");

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Using the root folder we can initialize a hierarchy table and use it to fill
// the combo box with a list of folders.  Also open the default folder.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Get the contents table for the folder.
    CMAPIInterface< LPMAPITABLE> pHierarchTbl;
    hr = pRootFolder->GetHierarchyTable( MAPI_DEFERRED_ERRORS, &pHierarchTbl);
    if( FAILED( hr))
        RETURN( hr);
    
    // Fill Combo Box with a list of folders.
    hr = HrFillBox( pHierarchTbl);
    if( FAILED( hr))
        RETURN( hr);

    // Select the first folder if non are selected yet.
    if( GetCurSel() == CB_ERR)
        SetCurSel( 0);  
    
    // Open the default folder.
    hr = HrOpenFolder();
    if( FAILED( hr))
        RETURN( hr);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    return( NOERROR);
}

// -----------------------------------------------------------------------------
// This releases the old folder and opens the newly selected one.
// -----------------------------------------------------------------------------

BOOL CPropsComboBox::HrOpenFolder()
{
    DEBUGPUBLIC( "CPropsComboBox::HrOpenFolder()");

    int iFolder = GetCurSel();
    m_iFolder = -1; // In case we fail.

    // Release the old folder.
    ULRELEASE( m_pFolder);

    // Open the folder.
    ULONG ulObjType = 0;
    CHRESULT hr = m_pMDB->OpenEntry( GetByteCnt( iFolder), GetEID( iFolder),
        NULL, MAPI_DEFERRED_ERRORS, &ulObjType, (LPUNKNOWN FAR *) &m_pFolder);

    if( FAILED( hr))
        RETURN( hr);

    if( ulObjType != MAPI_FOLDER)
        RETURN( E_FAIL);
    
    m_iFolder = iFolder;
    return( NOERROR);
}

// $--CPropsComboBox::HrAddItem()-------------------------------------------------
// This virtual member function is called from HrFillBox().  It extracts the 
// properties from pProps into useable objects, formats them, and then add them 
// to the combo box.
// -----------------------------------------------------------------------------

HRESULT CPropsComboBox::HrAddItem( // Returns HRESULT
     CProperty& Properties)  // Ptr to properties of Entry Id and Folder name.
{
    BOOL bIsCurrent = FALSE;

    // Folder name.
    CString sFolderName = Properties.szGetPrValue();
    
    // Explicitly clear the DEFER flag of the MTS-IN folder.
    if( sFolderName == TEXT( "MTS-IN") && m_pProps)
        m_pProps->SetDefer( FALSE);

    // Is this the current one?
    if( sFolderName == m_sCurFolderName)
        bIsCurrent = TRUE;  // Yes

    // Count of messages in folder.
    Properties.Next();
    sFolderName += " -- " + Properties.szGetPrValue();

    // Add the folder name to the combo box.
    int ii = AddString( sFolderName);

    // If this is the current folder set the combo box selection.
    if( bIsCurrent)
        SetCurSel( ii); 
    return( NOERROR);
}

// $--CPropsComboBox::CleanUp()---------------------------------------------------
// Called when the window has been destroyed.
// -----------------------------------------------------------------------------

void CPropsComboBox::Destruct()
{
    CPropsListComboBox<CComboBox>::Destruct();
    m_iFolder = -1;
    ULRELEASE( m_pFolder);
}

// -----------------------------------------------------------------------------
