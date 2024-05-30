// -----------------------------------------------------------------------------
// Format.cpp: Implements functions to format and return CStrings.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "edkafx.h"
#include "exadmin.h"
#include "format.h"

const int MAX_RESOURCE_MSG = 500;

//----------------------------------------------------------------------------
// These integers control the size of the buffer we allocate for the 
// _vsnprintf() function call.  It grows when _vsnprintf() returns an
// error.  The effect is that we remember the largest buffer needed for
// string formating and always start off by allocating that size of buffer.
// This provides a safe string formating method.
//----------------------------------------------------------------------------

static int nLargestBuf = 256;  
static int nGrowSize = 128;

//----------------------------------------------------------------------------
// Takes arguments just like vprintf(), but returns the result in a CString.
// This performs a safe format with no overwrites.
//----------------------------------------------------------------------------

CString _Format( TCHAR *pFmt, va_list pVArg)
{
    CString sFmtBuf;

    for( ;;)
    {   // Take a shot at formating the string.
        TCHAR* pFmtBuf = sFmtBuf.GetBuffer( nLargestBuf);
        if( _vsntprintf( pFmtBuf, nLargestBuf, pFmt, pVArg) >= 0)
           break;   // Format was successful.
            
        // Buffer was not big enough so enlarge it.
        nLargestBuf += nGrowSize;
        nGrowSize = (int) (nGrowSize * 3 / 2);
    }
    sFmtBuf.ReleaseBuffer();
    return( sFmtBuf);
}

//----------------------------------------------------------------------------
// Takes arguments just like printf(), but returns the result in a CString.
//----------------------------------------------------------------------------

CString Format( TCHAR *pMsgFmt ...)
{
    va_list pVArg;
    va_start( pVArg, pMsgFmt);
    return( _Format( pMsgFmt, pVArg));
}

//----------------------------------------------------------------------------
// Find a format string in the resource and use it to format the CString.
//----------------------------------------------------------------------------

CString _FormatResource( int hResStr, va_list pVArg)
{
    TCHAR sMsgFmt[ MAX_RESOURCE_MSG];    // Arbitrary size that should be big enough.

    if( CAdminDialog::LoadStringA( hResStr, sMsgFmt, sizeof( sMsgFmt)) == 0)
        return( Format( "Unknown error %d m_bOccurred.", hResStr));
    else
        return( _Format( sMsgFmt, pVArg));
}

//----------------------------------------------------------------------------
// Find a format string in the resource and use it to format the CString.
//----------------------------------------------------------------------------

CString FormatResource( int hResStr ...)
{
    va_list pVArg;
    va_start( pVArg, hResStr);
    return( _FormatResource( hResStr, pVArg));
}

//----------------------------------------------------------------------------
