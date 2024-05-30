// -----------------------------------------------------------------------------
// BinArray.h: Wrapper class for a mapi SBinaryArray.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _BINARRAY_H_
#define _BINARRAY_H_

#include "DynArray.h"

// -----------------------------------------------------------------------------
// Wraps a MAPI SBinaryArray structure and provides methods for creating it, 
// filling it, and cleaning up when it goes out of scope.
// -----------------------------------------------------------------------------

class CBinArray : CDynamicArray< SBinary>
{
public:
    // A MAPI SBinaryArray.  Don't do anything with this except pass it to MAPI 
    // functions.  This class will do the maintenance on it.
    SBinaryArray    m_SBA;     

    // CONSTRUCTOR: Start off with an empty array.
    CBinArray( ULONG AllocUnits = 10);

    // DESTRUCTOR: Free all allocated memory.
    ~CBinArray();

    // Add binary data to the array.
    BOOL bAdd( 
        ULONG cb,       // Count of byte array passed in.
        LPBYTE pBytes); // Ptr to array of bytes.

    // Returns a pointer to the SBinaryArray by just specifying the object.
    operator SBinaryArray*() {return( &m_SBA);}

protected:
    ULONG           m_AllocUnits;   // Number of units for each array expansion.
    LPSBinary       m_pCurBin;      // Ptr to next SBinary to fill up with data.
    
    // Expand the array by m_AllocUnits.
    BOOL bExpand();                  
};

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_
#pragma message("Declaration of global objects for: " __FILE__)

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------

#endif // _BINARRAY_H_
