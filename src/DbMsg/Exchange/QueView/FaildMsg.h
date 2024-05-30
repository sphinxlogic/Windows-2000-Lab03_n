// -----------------------------------------------------------------------------
// Init.h : header file
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _INIT_H_
#define _INIT_H_

// -----------------------------------------------------------------------------
// This class holds a status of whether something has failed or not.  If it has
// Failed when the destructor is called a message is displayed.
//
// This defaults to FAILED.
// -----------------------------------------------------------------------------

class CMsgOnFail
{
public:    
    CMsgOnFail( CString sMsg, CString sTitle = "Failure");
    ~CMsgOnFail();
    
    void Failed()     { m_bFailed = TRUE;}
    void Succeeded()  { m_bFailed = FALSE;}
    BOOL bHasFailed() { return( m_bFailed);}

protected:
    BOOL    m_bFailed;
    CString m_sMsg;
    CString m_sTitle;
};

// -----------------------------------------------------------------------------

#endif // _INIT_H_
