// -----------------------------------------------------------------------------
// Property.h : Define classes that deals with IMAPIProp properties.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include "edkutcpp.h"

extern IDList PropTags[];
extern IDList PropTypes[];

typedef union _PV UPropVal;

// -----------------------------------------------------------------------------

#define PR_ROW_SET_END (ULONG) ~0

// -----------------------------------------------------------------------------
// This class lets the user get properties using an IMAPIProp interface (such as
// a mapi message interface).  
//
// It lets you move through the properties using the First(), Next(), and 
// bAtEnd() member functions.
//
// It lets you get the properties type, id, and value in either its native format
// of in a readable string.
// -----------------------------------------------------------------------------

class CProperty
{
public:
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Construction, destruction, and setting defaults.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    CProperty();
    ~CProperty()  {Free();}

    // Set the default sign format for int and long.
    BOOL bSetUnsigned( BOOL bUnsigned = TRUE);

    // Set the default format used for doubles and floats.
    CString SetDblFmt( LPSTR pszDblFmt);

    // Frees the property list array.
    void Free( ULONG cValues = 0, LPSPropValue pProps = NULL);    
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Set up the count of values and pointer to them.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Gets the properties using an IMAPIProp interface.
    HRESULT GetProps( IMAPIProp* imapiProp, LPSPropTagArray pta, ULONG ulFlags = 0);
    
    // Set up the properties array to work with.
    void Set( ULONG cValues, LPSPropValue pProps)   {Free( cValues, pProps);}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Moving through the property list array.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void First()    {m_pCurProp = m_pFirstProp;}
    void Next();
    BOOL bAtEnd()   {return( m_pCurProp == NULL);}
    
    ULONG GetCount(){return( m_cValues);}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Getting info about the current property.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Get the current property ID as a ULONG.
    ULONG       ulGetPrID();
    
    // Get the current property ID as a ptr to a char array string.
    const LPSTR szGetPrID()         {return( m_idlPropIDs.Find( ulGetPrID()));}
    
    // Get the current property TYPE as a ULONG.
    ULONG       ulGetPrType();
    
    // Get the current property TYPE as a ptr to a char array string.
    const LPSTR szGetPrType()       {return( m_idlPropTypes.Find( ulGetPrType()));}
    
    // Get the current property VALUE as a union _PV as defined in MAPI.
    UPropVal    upvGetPrValue();
    
    // Get the current property VALUE as a formated CString.  Pass TRUE to treat 
    // ints or longs as unsigned, FALSE otherwise.  If no params passed in we
    // default to a value that may be set through bSetUnsigned().
    CString     szGetPrValue( BOOL bUnsigned = -1);

protected:
    // Initializes property counters and pointers.
    void Init( ULONG cValues = 0, LPSPropValue pProps = NULL);

    ULONG           m_cValues;          // Count of values pointed to by m_pFirstProp.
    LPSPropValue    m_pFirstProp;       // Ptr to first property in array.
    LPSPropValue    m_pLastProp;        // Ptr to last property.
    LPSPropValue    m_pCurProp;         // Ptr to current property.
    CIDList         m_idlPropIDs;       // ID list for valid property ids.
    CIDList         m_idlPropTypes;     // ID list for valid property types.
    BOOL            m_bUnsigned;        // Default signed format for int and long.
    CString         m_sDblFmt;          // Default format for doubles.
};

// -----------------------------------------------------------------------------
// This class gives you the functionality of the above CProperty class but for
// rows of properties.  Set up the row set by calling HrGetTblRows().
//
// Use FirstRow(), NextRow(), and bAtEndRows() to move through the rows of 
// properties.  Then access the properties using the methods of the CProperty 
// class.
// -----------------------------------------------------------------------------

class CPropertyRows : public CProperty
{
public:
    CPropertyRows();
    ~CPropertyRows() {Free();}

    // Frees the rows of properties.
    void Free();
    
    // Gets a row of properties from a MAPI table.
    HRESULT HrGetTblRows(                    // RETURNS: return code
        LPMAPITABLE lpTable,            // Ptr to a mapi table.
        ULONG       cMaxNRows = 10);    // Max.# of rows to return
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Moving through the rows of property list arrays.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void FirstRow()     {SetCurRow(TRUE);}
    void NextRow()      {SetCurRow(FALSE);}
    BOOL bAtEndOfRows() 
    {   
        if( !m_pRowSet)
            return( TRUE);
        return( m_ulCurRowIndex >= m_pRowSet->cRows);
    }

    ULONG GetRowCount() 
    {   
        if( !m_pRowSet)
            return( 0);
        return( m_pRowSet->cRows);
    }

protected:
    void SetCurRow( BOOL bFirst);   // TRUE sets to first row, FALSE sets to next row.

    LPSRowSet   m_pRowSet;          // Ptr to rows of properties.
    ULONG       m_ulCurRowIndex;    // Index of current row.
};

// -----------------------------------------------------------------------------

#endif //_PROPERTY_H_
