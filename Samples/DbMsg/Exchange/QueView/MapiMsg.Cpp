// -----------------------------------------------------------------------------
// MAPIMsg.cpp: Implements a class that opens a mapi message and does the 
//              appropriate error checking.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "MAPIMsg.h"
#include "mapimsg.chk"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// $--CMAPIMessage::CMAPIMessage()----------------------------------------------
// CONSTRUCTOR: Opens the mapi message using a mapi container and does the 
// appropriate error checking.  Releases the object if it is not a MAPI_MESSAGE.
// -----------------------------------------------------------------------------

CMAPIMessage::CMAPIMessage(
    LPMAPICONTAINER pMAPIContainer, // Containter to use to open message.
    ULONG cb,                       // Count of bytes in Entry Id.
    LPENTRYID pEID,                 // Entry Id of message to open.
    ULONG ulFlags)                  // Defaults to 0L, MAPI_MODIFY is a likely one to pass in.
{
    // NOTE: Initialization of members MUST be initialized before CHK function is called.
    m_pMsg = NULL;  

    DEBUGPUBLIC( "CMAPIMessage::CMAPIMessage()\n");
    m_hr = CHK_CMAPIMessage_CMAPIMessage( pMAPIContainer, cb, pEID, ulFlags);
    if( FAILED( m_hr))
        return;
    
    ULONG ulObjType = 0;
    m_hr = pMAPIContainer->OpenEntry(
        cb, pEID, NULL, ulFlags|MAPI_DEFERRED_ERRORS, &ulObjType, (LPUNKNOWN*) &m_pMsg);
    if( FAILED( m_hr))
        return;

    if( ulObjType != MAPI_MESSAGE)
    {
        m_hr = HR_LOG( E_FAIL);
        ULRELEASE( m_pMsg);
    }
}

// -----------------------------------------------------------------------------
