// --report.h-------------------------------------------------------------------
// 
//  Header file for module containing report functions.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_REPORT_H)
#define _REPORT_H

#include <wchar.h>
#include <tchar.h>
#include "retcode.h"
#include "edkdebug.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//$--HrEDKCreateDeliveryReport--------------------------------------------------
//  Create a delivery report.
// -----------------------------------------------------------------------------
HRESULT HrEDKCreateDeliveryReport(          // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpEnvelope,                // pointer to message envelope
    IN LPMESSAGE lpMessage,                 // pointer to message
    IN LPADRLIST lpAdrList,                 // pointer to address list
    OUT LPMESSAGE *lppReportEnvelope,       // pointer to report envelope
    OUT LPMESSAGE *lppReport);              // pointer to report

//$--HrEDKCreateReadNotificationReport------------------------------------------
//  Create a read notification report.
// -----------------------------------------------------------------------------
HRESULT HrEDKCreateReadNotificationReport(  // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpMessage,                 // pointer to message
    IN LPTSTR lpszReportText,               // pointer to report text
    OUT LPMESSAGE *lppReportEnvelope,       // pointer to report envelope
    OUT LPMESSAGE *lppReport);              // pointer to report

//$--HrEDKCreateNonReadNotificationReport---------------------------------------
//  Create a non-read notification report.
// -----------------------------------------------------------------------------
HRESULT HrEDKCreateNonReadNotificationReport(   // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,                   // pointer to folder
    IN LPMESSAGE lpMessage,                     // pointer to message
    IN LPTSTR lpszReportText,                   // pointer to report text
    IN ULONG ulNonReceiptReason,                // non-receipt reason
    IN ULONG ulDiscardReason,                   // discard reason
    OUT LPMESSAGE *lppReportEnvelope,           // pointer to report envelope
    OUT LPMESSAGE *lppReport);                  // pointer to report

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
