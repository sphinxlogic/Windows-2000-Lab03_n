// -----------------------------------------------------------------------------
// FaildMsg.cpp : Implements a class that keeps a failed status and displays
//                a message when the destructor is called and it has failed.
//
//                This is useful to functions that have many exit points that
//                all wish to display the same message if the function fails.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#include "faildmsg.h"

// -----------------------------------------------------------------------------

CMsgOnFail::CMsgOnFail( CString sMsg, CString sTitle)
{
    m_bFailed = TRUE;
    m_sMsg = sMsg;
    m_sTitle = sTitle;
}

// -----------------------------------------------------------------------------

CMsgOnFail::~CMsgOnFail()
{
    if( m_bFailed)
        ::MessageBox( NULL, m_sMsg, m_sTitle, MB_TASKMODAL);
}

// -----------------------------------------------------------------------------
