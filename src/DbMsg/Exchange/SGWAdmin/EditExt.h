// -----------------------------------------------------------------------------
// EditExt.h : Defines a data reading and conversion extension to the CEdit 
//             class.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _EDITEXT_H_
#define _EDITEXT_H_

// -----------------------------------------------------------------------------

class CEditExt : public CEdit
{
public:
    CString GetString( int nIndex = 0);
    LONG GetLong( int nIndex = 0);
    ULONG GetULong( int nIndex = 0);
};

// -----------------------------------------------------------------------------

#endif // _EDITEXT_H_
