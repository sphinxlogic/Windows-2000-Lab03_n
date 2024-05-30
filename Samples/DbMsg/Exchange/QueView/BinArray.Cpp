// -----------------------------------------------------------------------------
// BinArray.cpp: Implements methods that wraps the MAPI SBinaryArray structure.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "BinArray.h"
#include "BinArray.chk"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// $--CBinArray::CBinArray()----------------------------------------------------
// CONSTRUCTOR: Start off with an empty array.
// -----------------------------------------------------------------------------

CBinArray::CBinArray( ULONG AllocUnits)
{
    m_SBA.cValues = 0;
    m_SBA.lpbin = NULL;

    m_Size = 0;
    m_AllocUnits = AllocUnits;
    m_pCurBin = NULL;
}

// $--CBinArray::~CBinArray()---------------------------------------------------
// DESTRUCTOR: Free all allocated memory.
// -----------------------------------------------------------------------------

CBinArray::~CBinArray()
{
    ULONG cValues = m_SBA.cValues;
    LPSBinary pBin = m_SBA.lpbin;
    
    if( cValues)
        ASSERTERROR( pBin != NULL, "m_SBA.lpbin should point to something.");

    while( cValues)
    {   // Delete each byte array pointer.
        
        if( pBin->lpb)
            delete [] pBin->lpb;
        
        // Move pointer to next one.
        cValues --;
        pBin ++;
    }
    
    // Clear this just incase someone else was hanging on to a pointer to it.
    m_SBA.cValues = 0;
    m_SBA.lpbin = NULL;
}

// $--CBinArray::HrAdd()--------------------------------------------------------
// Add binary data to the array.  Returns TRUE if data was added.
// -----------------------------------------------------------------------------

BOOL CBinArray::bAdd( 
    ULONG cb,       // Count of byte array passed in.
    LPBYTE pBytes)  // Ptr to array of bytes.
{
    DEBUGPUBLIC( "CBinArray::bAdd()\n");
    if( FAILED( CHK_CBinArray_bAdd( cb, pBytes)))
        return( FALSE);

    if( m_SBA.cValues > m_Size)
    {
        HR_LOG( E_FAIL); // Corruption of m_SBA.cValues, it's too large.
        return( FALSE);
    }

    // Have we filled the existing array?
    if( m_SBA.cValues == m_Size)
    {   // YES, so expand it.
        if( !bExpand())
            return( FALSE);
    }

    // Allocate memory to hold binary data.
    m_pCurBin->lpb = new BYTE[ cb];
    if( !m_pCurBin->lpb)
        return( FALSE);

    // Make a copy of binary data.
    m_pCurBin->cb = cb;
    memcpy( m_pCurBin->lpb, pBytes, cb);

    // Increment the count and the current pointer.
    m_SBA.cValues ++;
    m_pCurBin ++;

    return( TRUE);
}

// -----------------------------------------------------------------------------
// Expand the array by m_AllocUnits.
// -----------------------------------------------------------------------------

BOOL CBinArray::bExpand()
{
    ULONG OldSize = m_Size;

    if( !CDynamicArray< SBinary>::bExpand( m_AllocUnits))
        return( FALSE);

    // Adjust working pointers.
    m_SBA.lpbin = m_ptr;
    m_pCurBin = m_ptr + OldSize;
    
    return( TRUE);
}

// -----------------------------------------------------------------------------
