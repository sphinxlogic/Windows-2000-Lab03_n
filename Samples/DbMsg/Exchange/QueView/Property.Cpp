// -----------------------------------------------------------------------------
// Property.cpp: Implements methods for classes that works with IMAPIProp.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "property.h"
#include "propdef.h"    // Include only here!  Contains static declarations.
#include "ErrCpp.h"
#include "property.chk"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------------------------
// CONSTRUCTOR
// -----------------------------------------------------------------------------

CProperty::CProperty() : 
    m_idlPropIDs( PropIDs, ARRAY_CNT( PropIDs)),
    m_idlPropTypes( PropTypes, ARRAY_CNT( PropTypes))
{
    Init();
    m_bUnsigned = TRUE;     // Default treatment of int and long to unsigned.
    m_sDblFmt = "%10.2g";   // Default format for printing doubles.
}

// -----------------------------------------------------------------------------
// Set the default sign format for int and long.  Used by szGetPrValue() when
// caller does not provide a parameter.
// -----------------------------------------------------------------------------

BOOL CProperty::bSetUnsigned( BOOL bUnsigned)
{
    BOOL bOldVal = m_bUnsigned;
    m_bUnsigned = bUnsigned;
    return( bOldVal);
}

// -----------------------------------------------------------------------------
// Set the default format used for doubles and floats.  This would be in 
// printf() format.
// -----------------------------------------------------------------------------

CString CProperty::SetDblFmt( LPSTR pszDblFmt)
{
    CString sRetVal = m_sDblFmt;
    m_sDblFmt = pszDblFmt;
    return( m_sDblFmt);
}

// -----------------------------------------------------------------------------
// Frees the property list array.
// -----------------------------------------------------------------------------

void CProperty::Free( 
    ULONG cValues,          // Count of new properties.
    LPSPropValue pProps)    // Ptr to list of new properties.
{   
    MAPIFREEBUFFER( m_pFirstProp);  // Free old list of properties.
    Init( cValues, pProps);         // Initialize list with new properties.
}

// -----------------------------------------------------------------------------
// Gets the properties using an IMAPIProp interface.
// -----------------------------------------------------------------------------

HRESULT CProperty::GetProps( 
    IMAPIProp*      imapiProp,  // MAPI interface to access properties with.
    LPSPropTagArray pta,        // Ptr to property tag array.
    ULONG           ulFlags)    // Optional flags, default to zero.
{
    DEBUGPUBLIC( "CProperty::GetProps()\n");
    CHRESULT hr = CHK_CProperty_GetProps( imapiProp, pta, ulFlags);
    if( FAILED( hr))
        RETURN( hr);

    Free();
    
    // Get the properties using MAPI.
    hr = imapiProp->GetProps( pta, ulFlags, &m_cValues, &m_pFirstProp);
    if( FAILED( hr))
        RETURN( hr);
    
    // Setup to transverse through list of properties.
    m_pLastProp = m_pFirstProp + (m_cValues - 1); 
    First();
    
    return( NOERROR);
}

// -----------------------------------------------------------------------------
// Set current property to the next property.
// -----------------------------------------------------------------------------

void CProperty::Next()
{
    if( m_pCurProp == NULL)
        m_pCurProp = m_pFirstProp;
    else if( m_pCurProp == m_pLastProp)
        m_pCurProp = NULL;
    else
        m_pCurProp ++;
}

// -----------------------------------------------------------------------------
// Get the current property ID as a ULONG.
// -----------------------------------------------------------------------------

ULONG CProperty::ulGetPrID()
{
    ASSERTERROR( m_pCurProp != NULL, "m_pCurProp is NULL!");
    if( m_pCurProp == NULL)
        return( 0);
    
    return( PROP_ID(m_pCurProp->ulPropTag));
}

// -----------------------------------------------------------------------------
// Get the current property TYPE as a ULONG.
// -----------------------------------------------------------------------------

ULONG CProperty::ulGetPrType()
{
    ASSERTERROR( m_pCurProp != NULL, "m_pCurProp is NULL!");
    if( m_pCurProp == NULL)
        return( 0);
    
    return(PROP_TYPE( m_pCurProp->ulPropTag));
}

// -----------------------------------------------------------------------------
// Get the current property VALUE as a union _PV as defined in MAPI.
// -----------------------------------------------------------------------------

UPropVal CProperty::upvGetPrValue()
{
    UPropVal upv;
    upv.ul = 0;     // On error return this property value.

    ASSERTERROR( m_pCurProp != NULL, "m_pCurProp is NULL!");
    if( m_pCurProp == NULL)
        return( upv);
    
    return( m_pCurProp->Value);
}

// -----------------------------------------------------------------------------
// Get the current property VALUE as a formated CString.  Pass TRUE to treat 
// ints or longs as unsigned, FALSE otherwise.  If no params passed in we
// default to a value that may be set through bSetUnsigned().
//
// NOTE: A number of the possible property types don't have a conversion at
//       this time.
// -----------------------------------------------------------------------------

CString CProperty::szGetPrValue( BOOL bUnsigned)
{
    int         ii;
    unsigned    ui;
    double      dbl;
    char        chBuf[4];
    LPBYTE      pByte;
    CString     sRetVal;
    FILETIME    LocalFT = {0};
    SYSTEMTIME  st = {0};
    UPropVal    upv = upvGetPrValue();

    if( bUnsigned == -1)
        bUnsigned = m_bUnsigned;

    switch( ulGetPrType())
    {
        case PT_I2:
            if( bUnsigned)
            {
                ui = (unsigned) upv.i; // Convert to short unsigned to regular unsigned.
                sRetVal.Format( "%u", ui);
            }
            else
            {
                ii = upv.i;             // Convert to short int to regular int.
                sRetVal.Format( "%d", ii);
            }
            break;
        
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_LONG:
            if( bUnsigned)
                sRetVal.Format( "%lu", upv.ul);
            else
                sRetVal.Format( "%ld", upv.l);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_R4:
            dbl = upv.flt;
            sRetVal.Format( m_sDblFmt, dbl);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_DOUBLE:
            sRetVal.Format( m_sDblFmt, upv.dbl);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_BOOLEAN:
            if( upv.b)
                sRetVal = "TRUE";
            else
                sRetVal = "FALSE";
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_SYSTIME:
            if( FileTimeToLocalFileTime( &upv.ft, &LocalFT))
            {
                if( FileTimeToSystemTime( &LocalFT, &st))
                {
                    sRetVal.Format( "%.2d:%.2d:%.2d %.2d/%.2d/%.2d",
                        st.wHour, st.wMinute, st.wSecond,
                        st.wMonth, st.wDay, st.wYear);
                    break;
                }
            }

            sRetVal.Format( "Error %lu converting file time to local or system time.", GetLastError());
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_STRING8:
            sRetVal.Format( "%s", upv.lpszA);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_BINARY:
            sRetVal.Format( "CB:%d 0x", upv.bin.cb);  // Format the count.
            
            // Make sure we don't format more than 100 bytes.
            if( upv.bin.cb > 100)
                ii = 100;
            else
                ii = upv.bin.cb;
            
            // Loop to format into hex digits.
            pByte = upv.bin.lpb;
            while( ii)
            {   // Format a single byte into a hex value and add to sRetVal.
                ui = *pByte;
                sprintf( chBuf, "%.2x", ui);
                sRetVal += chBuf;
                
                // Next byte.
                pByte ++;
                ii --;
            }
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_ERROR:
        {
            CHRESULT hr = upv.err;
            sRetVal.Format( "Error %s [%.8lx]", hr.Msg(), hr);
            break;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        default: 
            sRetVal = szGetPrType();
            sRetVal += " has no conversion at this time.";
            break;
    }
    return( sRetVal);
}

// $--CProperty::Init()---------------------------------------------------------
// Initializes property counters and pointers.
// -----------------------------------------------------------------------------

void CProperty::Init( ULONG cValues, LPSPropValue pProps)
{
    m_cValues = cValues;
    m_pFirstProp = pProps;
    m_pLastProp = m_pFirstProp + (m_cValues - 1);
    m_pCurProp = NULL;
}

// -----------------------------------------------------------------------------
// CONSTRUCTOR
// -----------------------------------------------------------------------------

CPropertyRows::CPropertyRows()
{
    m_pRowSet = NULL;                   // No property row set.
    m_ulCurRowIndex = PR_ROW_SET_END;   // No current row.
}

// -----------------------------------------------------------------------------
// Frees the rows of properties then initializes the base class values since we
// don't want it trying to free a single row of properties that no longer exists.
// -----------------------------------------------------------------------------

void CPropertyRows::Free()
{
    if( !m_pRowSet)
        return;

    FreeProws( m_pRowSet);
    m_pRowSet = NULL;
    m_ulCurRowIndex = PR_ROW_SET_END;   // No current row.

    Init( 0, NULL);
}

// -----------------------------------------------------------------------------
// Gets a row of properties from a MAPI table.
// -----------------------------------------------------------------------------

HRESULT CPropertyRows::HrGetTblRows( // RETURNS: return code
    LPMAPITABLE lpTable,        // Ptr to a mapi table.
    ULONG       cMaxNRows)      // Max.# of rows to return
{
    DEBUGPUBLIC( "CPropertyRows::HrGetTblRows()\n");
    CHRESULT hr = CHK_CPropertyRows_HrGetTblRows( lpTable, cMaxNRows);
    if( FAILED( hr))
        RETURN( hr);

    // Free last row set before trying to get another.
    Free();     

    // Get the next list of messages in the folder
    hr = lpTable->QueryRows( cMaxNRows, 0L, &m_pRowSet);
    if( FAILED( hr))
        RETURN( hr);

    // Make sure we received a valid pointer.
    if( !m_pRowSet)
        RETURN( E_FAIL);
    
    // Have we reached the end of the row list?
    if( m_pRowSet->cRows == 0)
        RETURN( EDK_E_END_OF_FILE);    // YES, since no rows found return EDK_E_END_OF_FILE.

    FirstRow();

    return( NOERROR);
}

// $--CPropertyRows::SetCurRow()------------------------------------------------
// Set currency to either the first or the next row of properties.
// -----------------------------------------------------------------------------

void CPropertyRows::SetCurRow( BOOL bFirst) // TRUE sets to first row, FALSE sets to next row.
{
    if( !m_pRowSet)
        return; // There is no row set.

    // Were we requested to set to the first row, or were we at the end of the row list?
    if( bFirst || m_ulCurRowIndex == PR_ROW_SET_END)
        m_ulCurRowIndex = 0;    // YES, so set to first row.
    else
        m_ulCurRowIndex ++;     // NO, so set to the next row.
       
    if( bAtEndOfRows())
    {   
        m_ulCurRowIndex = PR_ROW_SET_END;
        return;
    }

    // Initialize base class so that it's first and current property 
    // point to the first one in this row.
    Init( m_pRowSet->aRow[ m_ulCurRowIndex].cValues, m_pRowSet->aRow[ m_ulCurRowIndex].lpProps); 
    First();    // First property of this row.
}

// -----------------------------------------------------------------------------
