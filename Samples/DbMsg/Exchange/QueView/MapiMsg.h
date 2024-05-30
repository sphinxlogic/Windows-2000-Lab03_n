// -----------------------------------------------------------------------------
// MAPIMsg.h: Wrapper class for a mapi message interface pointer.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _MAPIMSG_H_
#define _MAPIMSG_H_

#include "ErrCpp.h"

// -----------------------------------------------------------------------------
// A wrapper class to contain an interface to a mapi message.  This contains the
// error checking and automatic release of the pointer upon destruction.  
//
// Construct by passing a pointer to a mapi container (could be a folder), a 
// count of bytes of the entry id, and the entry id.
//
// Test FAILED( m_hr) for validity of the object, and use m_pMsg to access
// the mapi message interface pointer.
// -----------------------------------------------------------------------------

class CMAPIMessage
{
public:
    // CONSTRUCTOR: Opens the mapi message using a mapi container and does the 
    // appropriate error checking.  Releases the object if it is not a MAPI_MESSAGE.
    CMAPIMessage( 
        LPMAPICONTAINER pMAPIContainer, // Containter to use to open message.
        ULONG cb,                       // Count of bytes in Entry Id.
        LPENTRYID pEID,                 // Entry Id of message to open.
        ULONG ulFlags = 0L);            // MAPI_MODIFY is a likely one to pass in.
    
    // DESTRUCTOR: Releases MAPI's IMessage interface pointer.
    ~CMAPIMessage()     {ULRELEASE( m_pMsg);}

    LPMESSAGE   m_pMsg; // Pointer to MAPI's IMessage interface.
    CHRESULT    m_hr;   // Contains the actual HRESULT from the OpenEntry().

    // Returns a pointer to the MAPI Message.
    operator LPMESSAGE() {return( m_pMsg);}

    // Returns a pointer to the MAPI Message for -> operations.
    LPMESSAGE operator ->() {return( m_pMsg);}
};

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_
#pragma message("Declaration of global objects for: " __FILE__)

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------

#endif // _MAPIMSG_H_
