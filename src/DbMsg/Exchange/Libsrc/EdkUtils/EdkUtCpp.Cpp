// EdkUtCpp.CPP-----------------------------------------------------------------
// Implements methods for a class that supplies a list of id's and strings 
// which can be found by ID.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "EdkUtCpp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------------------------
// CONSTRUCTOR: Pass in a pointer to an array of IDList and it's number of items.
// Use ARRAY_CNT( IDListArray) to get this.
// -----------------------------------------------------------------------------

CIDList::CIDList( 
    PIDList pIDList,    // Pointer to array of IDList.
    UINT nCnt)          // Number of items in the list.
{
    m_pIDList = pIDList;
    m_nCnt = nCnt;
}

// -----------------------------------------------------------------------------
// Find an ID in the pIDList and return it's string.
// -----------------------------------------------------------------------------

const LPSTR CIDList::Find(  // Returns the string found or a not found message string.
    ULONG ulID)             // ID to search for.
{
    if( m_pIDList)
    {
        PIDList pIDList = m_pIDList;
        UINT nCnt = m_nCnt;
        while( nCnt)
        {
            if( pIDList->ulID == ulID)
                return( pIDList->pszValue); // Found the item we were looking for.
            pIDList ++;
            nCnt --;
        }
    }
        
    // NOTE: If you change this format you must also change the declration 
    // of m_chNotFound to reflect the maximum size.
    sprintf( m_chNotFound, "(ID: 0x%lX not found)", ulID);
    return( m_chNotFound);
}

// -----------------------------------------------------------------------------
