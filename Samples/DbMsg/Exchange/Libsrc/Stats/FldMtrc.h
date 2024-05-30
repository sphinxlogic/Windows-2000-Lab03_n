// --fldmtrc.h------------------------------------------------------------------
//
//  Defines the folder metrics object. 
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __fldmtrc_h
#define __fldmtrc_h

#include <windows.h>
#include <mapix.h>

// Flags for metric to calculate.
// ------------------------------
#define FM_CMESSAGES        0x00000001
#define FM_LONGEST_WAIT     0x00000002
#define FM_TOTAL_WAIT       0x00000004

//$--CFolderMetrics-------------------------------------------------------------
// Defines the folder metrics class; An object that is attached to a folder 
// and can be queried for certain folder properties like size, length of
// wait of messages etc.
// -----------------------------------------------------------------------------
class CFolderMetrics
{
public:
    CFolderMetrics();
    virtual ~CFolderMetrics();
    HRESULT HrReset(IN LPMAPIFOLDER lpFolder);
    HRESULT HrGetFolderMetrics(IN __int64 liNow, IN DWORD fMetric, OUT DWORD &cMessages, OUT __int64 &liLongestWait, OUT __int64 &liTotalWait);

private:
    HRESULT HrGetcMessages(OUT DWORD &cMessages);
    HRESULT HrGetLongestWait(IN __int64 liNow, OUT __int64 &liLongestWait);
    HRESULT HrGetTotalWait(IN __int64 liNow, OUT DWORD &cMessages, OUT __int64 &liTotalWait);

    LPMAPIFOLDER m_lpFolder;
    LPMAPITABLE m_lpTable; 

    static SPropTagArray m_sFolderContentCount;   
    static SPropTagArray m_sInFolderSince;        
    static SSortOrderSet m_sSortOrderSet;         
};

#endif __fldmtrc_h
