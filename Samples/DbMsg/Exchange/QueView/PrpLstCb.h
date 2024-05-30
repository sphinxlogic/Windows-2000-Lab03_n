// -----------------------------------------------------------------------------
// PrpLstCb.h : header file
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _PRPLSTCB_H_
#define _PRPLSTCB_H_

#include "ErrCpp.h"
#include "Property.h"
#include "prplstcb.chk"

// -----------------------------------------------------------------------------

#define ADMINOP_HIDDEN  0x01L
#define ADMINOP_DEFER   0x02L
#define ADMINOP_DELETE  0x04L
#define ADMINOP_NDR     0x08L

// -----------------------------------------------------------------------------
// Used to contain properties such as entry id and flags.
// -----------------------------------------------------------------------------

class CProps
{
public:
    CProps( ULONG cbEID, BYTE* pEID, DWORD dwFlags);
    ~CProps();

    // Get the entry id and byte count for a specific index.
    ULONG GetByteCnt() {return( m_cbEID);}
    LPENTRYID GetEID() {return( (LPENTRYID) m_pEID);}
    
    // Functions to return the state of a flag.
    BOOL bTestFlags( DWORD dwBits) {return( (m_dwFlags & dwBits) == dwBits);}
    BOOL bIsHidden()    {return( bTestFlags(ADMINOP_HIDDEN));}
    BOOL bIsDefer()     {return( bTestFlags(ADMINOP_DEFER));}
    BOOL bIsDelete()    {return( bTestFlags(ADMINOP_DELETE));}
    BOOL bIsNDR()       {return( bTestFlags(ADMINOP_NDR));}
    DWORD dwGetFlags()  {return( m_dwFlags);}   // Returns all of the flags.
    
    // Set one of the flags (pass in TRUE or FALSE).
    void SetHidden( BOOL bState)    { m_dwFlags = (m_dwFlags & ~ADMINOP_HIDDEN) | bState;}
    void SetDefer( BOOL bState)     { m_dwFlags = (m_dwFlags & ~ADMINOP_DEFER ) | bState << 1;}
    void SetDelete( BOOL bState)    { m_dwFlags = (m_dwFlags & ~ADMINOP_DELETE) | bState << 2;}
    void SetNDR( BOOL bState)       { m_dwFlags = (m_dwFlags & ~ADMINOP_NDR   ) | bState << 3;}
    
protected:
    ULONG   m_cbEID;
    BYTE*   m_pEID;
    DWORD   m_dwFlags;
};

// Helper function.
inline BOOL bIsHidden( DWORD dwFlags) {return( (dwFlags & 0x01) == 0x01);}

// Used to replace a null CProps*.
extern CProps  NullCProps;

// -----------------------------------------------------------------------------
// Definition of a class that keeps a list of entry ids using struct _EID to 
// contain them.  This is a template class which is to be derived from either 
// CListBox or CComboBox.
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
class CPropsListComboBox : public BASE_CLASS
{
public:
    CPropsListComboBox()    { m_pProps = NULL;}
    ~CPropsListComboBox()   { Destruct();}

    // Fills the list or combo box with data from the table, uses HrAddItem to prepare the data.
    HRESULT HrFillBox( LPMAPITABLE pTable);    
    
    // Clears all data from the box.
    void ResetContent();

    // Use this to remove an item from the list.
    int DeleteString( int ii);
    
    // Get the entry id and byte count for a specific index.
    CProps* GetProps( int ii);  // Always returns valid pointer, GUARENTEED!
    ULONG GetByteCnt( int ii)   {return( GetProps( ii)->GetByteCnt());}
    LPENTRYID GetEID( int ii)   {return( GetProps( ii)->GetEID());}
    DWORD dwGetFlags( int ii)   {return( GetProps( ii)->dwGetFlags());}

protected:    
    LPSPropTagArray     m_psPropColumns;    // Set this in your derived class.
    LPSSortOrderSet     m_psSortPrioSet;    // Set this in your derived class.
    CProps*             m_pProps;           // Used by AddString() and HrFillBox()

    // Pure virtual function called by HrFillBox.
    virtual HRESULT HrAddItem( CProperty& Properties) = 0;

    // Used to add a string and its properties.
    int AddString( const LPCTSTR lpszItem);
    
    // Use this because we can't use a message map in a template class.
    virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam);

    // Clean up when the window has been destroyed.
    virtual void Destruct();

    // These functions may not be used unless they are implemented properly.
    int InsertString( UINT nIndex, LPCTSTR lpszItem) 
    { 
        ASSERTERROR( FALSE, "NOT IMPLEMENTED");
        return( LB_ERR);
    }
};

// $--CPropsListComboBox< BASE_CLASS>::HrFillBox()------------------------------
// Fill the list or combo box with data from a table.  This function reads the 
// data from the caller specified table and validates it.
// 
// A pure virtual function named HrAddItem() supplies the method for formating 
// and placing the data into the list or combo box.  HrAddItem() could also 
// decide to throw it away or use it.  
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
HRESULT CPropsListComboBox< BASE_CLASS>::HrFillBox(
    LPMAPITABLE     pTable)
{
    DEBUGPUBLIC( "CPropsListComboBox< BASE_CLASS>::HrFillBox()\n");
    CHRESULT hr = CHK_CPropsListComboBox_HrFillBox( pTable);
    if(FAILED(hr))
        RETURN( hr);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Setup the table's columns and sort order.  
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Set the columns to return.
    hr = pTable->SetColumns( m_psPropColumns, 0L);
    if( FAILED( hr))
        RETURN( hr);

    // Sort the table.
    hr = pTable->SortTable( m_psSortPrioSet, 0L);
    if(FAILED(hr))
        RETURN( hr);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Contents table has been initialize so lets display it.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Clear the list/combo box of all entries.
    ResetContent();   

    // Fill list/combo box with info from folder until end of table reached.
    while( TRUE)
    {   // Read the first 10 message headers from the contents table.
        CPropertyRows PropRowSet;
        CHRESULT hr = PropRowSet.HrGetTblRows( pTable);
        if( hr == EDK_E_END_OF_FILE )
            return( NOERROR);    // All done.

        if( FAILED( hr))
            RETURN( hr);
            
        // Process all messages in the current table.
        for( PropRowSet.FirstRow(); !PropRowSet.bAtEndOfRows(); PropRowSet.NextRow())
        {   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // Validate that the property array has the correct number of values
            // and that it has the correct properties in the expected order.
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            //#ifdef DEBUG
                PropRowSet.First();
                unsigned cProps = m_psPropColumns->cValues;
                if( PropRowSet.GetCount() < cProps)
                {
                    RETURN( E_FAIL);
                }
                
                if( PropRowSet.ulGetPrID() != PROP_ID( PR_GW_ADMIN_OPERATIONS))
                {
                    RETURN( E_FAIL);
                }
                
                PropRowSet.Next();
                if( PropRowSet.ulGetPrID() != PROP_ID( PR_ENTRYID))
                {
                    RETURN( E_FAIL);
                }

                unsigned ii;
                for( ii = 2; ii < cProps; ii ++)
                {
                    PropRowSet.Next();
                    if( PropRowSet.ulGetPrID() != PROP_ID( m_psPropColumns->aulPropTag[ ii]))
                    {
                        RETURN( E_FAIL);
                    }
                }
            //#endif
            
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // Extract the properties from pRowSet into useable objects.
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            PropRowSet.First();

            // PR_GW_ADMIN_OPERATIONS
            DWORD dwFlags;
            if( PropRowSet.ulGetPrType() != PT_LONG)
                dwFlags = 0;
            else
                dwFlags = PropRowSet.upvGetPrValue().ul;
            if( bIsHidden( dwFlags))
                continue;   // No need to go any further, this one is hidden.

            // PR_ENTRYID
            // Create a CProps object which will be added to list in AddString().
            PropRowSet.Next();
            if( m_pProps)
                delete m_pProps;    
            if( PropRowSet.ulGetPrType() != PT_BINARY)
                m_pProps = new CProps( 0, NULL, dwFlags);
            else
                m_pProps = new CProps( PropRowSet.upvGetPrValue().bin.cb, PropRowSet.upvGetPrValue().bin.lpb, dwFlags);

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // Add the item to the list.
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            PropRowSet.Next();
            hr = HrAddItem( PropRowSet);
            if( FAILED( hr))
                RETURN( hr);
        } // End For Loop
    }
}

// $--CPropsListComboBox< BASE_CLASS>::ResetContent()---------------------------
// Frees all entry ids associated with the list box items and clears the list box.
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
void CPropsListComboBox< BASE_CLASS>::ResetContent()
{
    // Are we still connected to the windows control?
    if( !::IsWindow(m_hWnd))
        return; // NO, we are not connected.

    // Free all property info objects.
    int ii = GetCount();
    while( ii)
    {
        ii --;
        CProps* pProps = (CProps*) GetItemDataPtr( ii);
        delete pProps;
    }
    BASE_CLASS::ResetContent();
}

// $--CPropsListComboBox< BASE_CLASS>::DeleteString()---------------------------
// Use this to remove an item from the list.
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
int CPropsListComboBox< BASE_CLASS>::DeleteString( int ii) // Index of list item.
{
    // Are we still connected to the windows control?
    if( !::IsWindow(m_hWnd))
    {   // NO, we are not connected.
        HR_LOG( E_FAIL);
        return(0);  
    }

    // NOTE: This parameter test MUST be done after the above test since
    //       the GetCount() function depends upon being connected to the
    //       windows control.
    if( ii < 0 || ii >= GetCount())
    {
        HR_LOG( E_FAIL);
        return( 0);
    }
    
    CProps* pProps = (CProps*) GetItemDataPtr( ii);
    delete pProps;
    return( BASE_CLASS::DeleteString( (UINT) ii));
}    
    
// $--CPropsListComboBox< BASE_CLASS>::GetProps()-------------------------------
// Returns CProps object and GUARENTEES it to be valid.  This does error 
// checking and if it can't get the pointer requested it returns a pointer to 
// NullCProps which has NULL for all values and always exists.
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
CProps* CPropsListComboBox< BASE_CLASS>::GetProps( int ii)   // Index of entry id.
{
    // Are we still connected to the windows control?
    if( !::IsWindow(m_hWnd))
    {
        HR_LOG( E_FAIL);
        return(0);  // NO we are not connected.
    }

    // NOTE: This parameter test MUST be done after the above test since
    //       the GetCount() function depends upon being connected to the
    //       windows control.
    if( ii < 0 || ii >= GetCount())
    {
        HR_LOG( E_FAIL);
        return( &NullCProps);
    }

    CProps* pProps = (CProps*) GetItemDataPtr( ii);
    if( !pProps || pProps == (CProps*) -1l)
    {
        HR_LOG( E_FAIL);
        return( &NullCProps);
    }

    return( pProps);
}

// $--CPropsListComboBox< BASE_CLASS>::AddString()------------------------------
// Add a string to the list box and an entry id to associate with it.
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
int CPropsListComboBox< BASE_CLASS>::AddString( // Return index of list box item.
    const LPCTSTR lpszItem)                     // Ptr to string to add to list.
{
    DEBUGPUBLIC( "CPropsListComboBox< BASE_CLASS>::AddString()\n");
    if( FAILED( CHK_CPropsListComboBox_AddString( lpszItem)))
        return( LB_ERR);

    // Add the displayable row to the list box.
	int ii = BASE_CLASS::AddString( lpszItem);
    if( ii == LB_ERR)
    {
        HR_LOG( E_FAIL);
        return( ii);
    }
    else if( ii == LB_ERRSPACE)
    {
        HR_LOG( E_FAIL);
        return( ii);
    }

	// Add a pointer to the properties as additional data.
	// Do we have properties to add?
	if( m_pProps)
    {   // YES, so associate it with the box's row.
        SetItemDataPtr( ii, (void*) m_pProps);
        m_pProps = NULL;    // So it does not get deleted before it should.
    }
    
    return( ii);
}

// $--CPropsListComboBox< BASE_CLASS>::WindowProc()-----------------------------
// Clean up when list box is being destroyed.
// Use this because we can't use a message map in a template class therefore
// we can't capture ON_WM_DESTROY in the usual MFC manor.
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
LRESULT CPropsListComboBox< BASE_CLASS>::WindowProc( UINT message, WPARAM wParam, LPARAM lParam)
{
    if( message == WM_DESTROY)
        Destruct();
    return( CWnd::WindowProc( message, wParam, lParam)); // Dispatch message anyway.
}

// $--CPropsListComboBox< BASE_CLASS>::Destruct()-------------------------------
// Clean up when the window has been destroyed.  This virtual function is 
// supplied so that derived classes do not have to implement a message map or 
// a WindowProc().  Plus we must delete all CProps objects.
// -----------------------------------------------------------------------------

template< class BASE_CLASS>
void CPropsListComboBox< BASE_CLASS>::Destruct()
{
    ResetContent();
    if( m_pProps)
    {
        delete m_pProps;
        m_pProps = NULL;
    }
}

// -----------------------------------------------------------------------------
// Derived class to support the list box in the QueViewer.
// -----------------------------------------------------------------------------

class CPropsListBox : public CPropsListComboBox< CListBox>
{
public:
    CPropsListBox();

protected:
    // Virtual function called by HrFillBox.
    virtual HRESULT HrAddItem( CProperty& Properties);
};

// -----------------------------------------------------------------------------
// Derived class to support the combo box in the QueViewer.
// -----------------------------------------------------------------------------

class CPropsComboBox : public CPropsListComboBox< CComboBox>
{
public:
    CPropsComboBox();    

    // Find all folders, and open default folder.
    HRESULT HrInitialize(
        LPMDB   pMDB);  // Ptr to MDB that contain gateway folders.

    // Returns TRUE if a folder selection has changed.
    BOOL bSelectionChanged() { return( m_iFolder != GetCurSel());}

    // Returns the folder that is selected.
    LPMAPIFOLDER GetFolder() {return( m_pFolder);}
    BOOL bIsDefer()    { return( GetProps( m_iFolder)->bIsDefer());}
    BOOL bIsDelete()   { return( GetProps( m_iFolder)->bIsDelete());}
    BOOL bIsNDR()      { return( GetProps( m_iFolder)->bIsNDR());}

protected:
    int                     m_iFolder;  // Index of folder being viewed.
    LPMAPIFOLDER            m_pFolder;  // Ptr to folder being viewed.
    LPMDB                   m_pMDB;     // Ptr to MSD of gateway.       
    CString                 m_sCurFolderName; // Contains name of selected folder.

    // Open the selected folder.
    BOOL HrOpenFolder();

    // Virtual function called by HrFillBox.
    virtual HRESULT HrAddItem( CProperty& Properties);
    
    // Clean up when the window has been destroyed.
    virtual void Destruct();
};

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_
#pragma message("Declaration of global objects for: " __FILE__)

// Used to replace a null CProps*.
CProps  NullCProps( 0, NULL, 0);

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------

#endif //_PRPLSTCB_H_
