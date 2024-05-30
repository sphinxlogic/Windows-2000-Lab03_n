// -----------------------------------------------------------------------------
// EditExt.cpp : Implements a data reading and conversion extension to the CEdit 
//               class.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "EditExt.h"

//$--CEditExt::GetString()------------------------------------------------------
// Returns the data from an edit control as a CString.
// -----------------------------------------------------------------------------

CString CEditExt::GetString( int nIndex)
{
    int Len = LineLength( nIndex) + sizeof(TCHAR);
    CString sBuf;
    GetLine( nIndex, sBuf.GetBuffer( Len), Len);
    sBuf.ReleaseBuffer();
    return( sBuf);
}

//$--CEditExt::GetLong()--------------------------------------------------------
// Returns the data from an edit control as a long.
// -----------------------------------------------------------------------------

LONG CEditExt::GetLong( int nIndex)
{
    return( _tcstol( GetString( nIndex), NULL, 0)); 
}

//$--CEditExt::GetULong()-------------------------------------------------------
// Returns the data from an edit control as a unsigned long.
// -----------------------------------------------------------------------------

ULONG CEditExt::GetULong( int nIndex)
{
    return( _tcstoul( GetString( nIndex), NULL, 0)); 
}

// -----------------------------------------------------------------------------
