// --rptdriv.c------------------------------------------------------------------
// 
//  Report generation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "gwmain.h"
#include "report.h"

#include "rptdriv.chk"

//  Defined for NT service shell
TCHAR szAppName[]       = TEXT("RPTDRIV");
TCHAR szWindowTitle[]   = TEXT("Reports Sample");

static LPMAPISESSION    lpSession       = NULL;
static LPMDB            lpStore         = NULL;
static LPMAPIFOLDER     lpRootFolder    = NULL;
static LPMAPIFOLDER     lpMtsInFolder   = NULL;
static LPMAPIFOLDER     lpMtsOutFolder  = NULL;
static ULONG            cbGalEid        = 0;
static LPENTRYID        lpGalEid        = NULL;

#define NDR     0
#define DR      1
#define RN      2
#define NRN     3
#define UNKNOWN 4

//$--UlMakeReportType-----------------------------------------------------------
//  Make a report type from a string.
// -----------------------------------------------------------------------------
static ULONG UlMakeReportType(          // RETURNS: type of report
    IN LPTSTR lpszStr)                  // string
{
    ULONG  ulReportType = UNKNOWN;
    LPTSTR lpszCurr     = NULL;
    LPTSTR lpszName     = NULL;

    if(lpszStr == NULL)
    {
        ulReportType = UNKNOWN;
        goto cleanup;
    }

    lpszName = lpszStr;

    //
    // Skip leading white space.
    //

    while(*lpszName && ((*lpszName == ' ') || (*lpszName == '\t')))
    {
        lpszName++;
    }

    lpszCurr = lpszName;

    while(*lpszCurr && (*lpszCurr != ' ') && (*lpszCurr != '\t'))
    {
        lpszCurr++;
    }

    *lpszCurr = 0;

    if(lstrcmpi(lpszName, "NDR") == 0)
    {
        ulReportType = NDR;
    }
    else if(lstrcmpi(lpszName, "DR") == 0)
    {
        ulReportType = DR;
    }
    else if(lstrcmpi(lpszName, "RN") == 0)
    {
        ulReportType = RN;
    }
    else if(lstrcmpi(lpszName, "NRN") == 0)
    {
        ulReportType = NRN;
    }
    else
    {
        ulReportType = UNKNOWN;
    }

cleanup:

    return(ulReportType);
}

//$--HrBuildSampleNDRAdrList----------------------------------------------------
//  Build a sample non-delivery report address list.
// -----------------------------------------------------------------------------
HRESULT HrBuildSampleNDRAdrList(            // RETURNS: return code
    IN LPMESSAGE lpMessage,                 // pointer to message
    OUT LPADRLIST *lppAdrList)              // pointer to address list pointer
{
    HRESULT         hr              = NOERROR;
    HRESULT         hrT             = NOERROR;
    LPADRLIST       lpAdrList       = NULL;
    LPADRLIST       lpNewAdrList    = NULL;
    SPropValue      rgProps[5]      = {0};
    ULONG           cHeadProps      = 0;
    LPSPropValue    lpHeadProps     = NULL;
    ULONG           cTailProps      = 0;
    LPSPropValue    lpTailProps     = NULL;
    ULONG           cNewProps       = 0;
    LPSPropValue    lpNewProps      = NULL;
    LPMAPITABLE     lpTable         = NULL;
    ULONG           cRows           = 0;

    DEBUGPUBLIC("HrBuildSampleNDRAdrList()\n");

    hr = CHK_HrBuildSampleNDRAdrList(
        lpMessage,
        lppAdrList);

    if(FAILED(hr))
        RETURN(hr);

//------------------------------------------------------------------------------

    hrT = MAPICALL(lpMessage)->GetRecipientTable(
        lpMessage,
        MAPI_DEFERRED_ERRORS,
        &lpTable);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpTable)->GetRowCount(lpTable, 0, &cRows);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpTable)->QueryRows(
        lpTable,
        cRows,
        0,
        (LPSRowSet *)&lpAdrList);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
    else if((lpAdrList == NULL) || (lpAdrList->cEntries != cRows))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

//------------------------------------------------------------------------------

    hr = HrNDRCreateFailedRecipList(
        &lpNewAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrNDRGetFailedRecipList(
        &lpAdrList->aEntries[0],
        0,
        NULL,
        &cNewProps,
        &lpNewProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrNDRAddToFailedRecipList(
        cNewProps,
        lpNewProps,
        &lpNewAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    *lppAdrList = lpNewAdrList;

cleanup:

    ULRELEASE(lpTable);

    MAPIFREEBUFFER(lpNewProps);

    FREEPADRLIST(lpAdrList);

    RETURN(hr);
}

//$--HrSendNDR------------------------------------------------------------------
//  Send a non-delivery report.
// -----------------------------------------------------------------------------
HRESULT HrSendNDR(                          // RETURNS: return code
    IN LPADRBOOK  lpAdrBook,                // pointer to address book
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpEnvelope,                // pointer to message envelope
    IN LPMESSAGE lpMessage)                 // pointer to message
{
    HRESULT      hr               = NOERROR;
    HRESULT      hrT              = NOERROR;
    LPMESSAGE    lpReport         = NULL;
    ULONG        cValues          = 0;
    LPSPropValue lpProps          = NULL;
    LPADRLIST    lpAdrList        = NULL;

    DEBUGPUBLIC("HrSendNDR()\n");

    hr = CHK_HrSendNDR(
        lpAdrBook,
        lpFolder,
        lpEnvelope,
        lpMessage);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrBuildSampleNDRAdrList(
        lpMessage,
        &lpAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrNDRGetFailedProps(
        lpMessage,
        &cValues,
        &lpProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrNDRCreate(
        lpAdrBook,
        lpFolder,
        lpMessage,
        lpAdrList,
        cValues,
        lpProps,
        &lpReport);

    FREEPADRLIST(lpAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Submit report
    hrT = MAPICALL(lpReport)->SubmitMessage(lpReport, FORCE_SUBMIT);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    FREEPADRLIST(lpAdrList);

    MAPIFREEBUFFER(lpProps);

    ULRELEASE(lpReport);

    RETURN(hr);
}

//$--HrBuildSampleDRAdrList-----------------------------------------------------
//  Build a sample delivery report address list.
// -----------------------------------------------------------------------------
HRESULT HrBuildSampleDRAdrList(             // RETURNS: return code
    IN LPMESSAGE lpMessage,                 // pointer to message
    OUT LPADRLIST *lppAdrList)              // pointer to address list pointer
{
    HRESULT         hr              = NOERROR;
    HRESULT         hrT             = NOERROR;
    LPADRLIST       lpAdrList       = NULL;
    LPADRLIST       lpNewAdrList    = NULL;
    SPropValue      rgProps[5]      = {0};
    ULONG           cHeadProps      = 0;
    LPSPropValue    lpHeadProps     = NULL;
    ULONG           cTailProps      = 0;
    LPSPropValue    lpTailProps     = NULL;
    ULONG           cNewProps       = 0;
    LPSPropValue    lpNewProps      = NULL;
    LPSPropValue    lpPropT         = NULL;
    LPMAPITABLE     lpTable         = NULL;
    ULONG           cRows           = 0;

    DEBUGPUBLIC("HrBuildSampleDRAdrList()\n");

    hr = CHK_HrBuildSampleDRAdrList(
        lpMessage,
        lppAdrList);

    if(FAILED(hr))
        RETURN(hr);

//------------------------------------------------------------------------------

    hrT = MAPICALL(lpMessage)->GetRecipientTable(
        lpMessage,
        MAPI_DEFERRED_ERRORS,
        &lpTable);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpTable)->GetRowCount(lpTable, 0, &cRows);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpTable)->QueryRows(
        lpTable,
        cRows,
        0,
        (LPSRowSet *)&lpAdrList);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
    else if((lpAdrList == NULL) || (lpAdrList->cEntries != cRows))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

//------------------------------------------------------------------------------

    hr = HrDRCreateDeliveredRecipList(
        &lpNewAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrDRGetDeliveredRecip(
        &lpAdrList->aEntries[0],
        0,
        NULL,
        &cNewProps,
        &lpNewProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lpPropT = LpValFindProp(
        PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED, cNewProps, lpNewProps);

    if(lpPropT != NULL)
    {
       lpPropT->ulPropTag = PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
       lpPropT->Value.b   = TRUE;
    }

    hr = HrDRAddToDeliveredRecipList(
        cNewProps,
        lpNewProps,
        &lpNewAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    *lppAdrList = lpNewAdrList;

cleanup:

    ULRELEASE(lpTable);

    MAPIFREEBUFFER(lpNewProps);

    FREEPADRLIST(lpAdrList);

    RETURN(hr);
}

//$--HrSendDR-------------------------------------------------------------------
//  Send a delivery report.
// -----------------------------------------------------------------------------
HRESULT HrSendDR(                           // RETURNS: return code
    IN LPADRBOOK  lpAdrBook,                // pointer to address book
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpEnvelope,                // pointer to message envelope
    IN LPMESSAGE lpMessage)                 // pointer to message
{
    HRESULT      hr               = NOERROR;
    HRESULT      hrT              = NOERROR;
    LPMESSAGE    lpReport         = NULL;
    ULONG        cValues          = 0;
    LPSPropValue lpProps          = NULL;
    LPSPropValue lpPropT          = NULL;
    LPADRLIST    lpAdrList        = NULL;

    DEBUGPUBLIC("HrSendDR()\n");

    hr = CHK_HrSendDR(
        lpAdrBook,
        lpFolder,
        lpEnvelope,
        lpMessage);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrBuildSampleDRAdrList(
        lpMessage,
        &lpAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrDRGetProps(
        lpMessage,
        &cValues,
        &lpProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrDRCreate(
        lpAdrBook,
        lpFolder,
        lpMessage,
        lpAdrList,
        cValues,
        lpProps,
        &lpReport);

    FREEPADRLIST(lpAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Submit report
    hrT = MAPICALL(lpReport)->SubmitMessage(lpReport, FORCE_SUBMIT);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    FREEPADRLIST(lpAdrList);

    MAPIFREEBUFFER(lpProps);

    ULRELEASE(lpReport);

    RETURN(hr);
}

//$--HrBuildSampleRNSender------------------------------------------------------
//  Build a sample sender for a RN/NRN report.
// -----------------------------------------------------------------------------
HRESULT HrBuildSampleRNSender(          // RETURNS: return code
    IN LPMESSAGE lpMessage,             // pointer to message
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    OUT LPTSTR    *lppszDisplayName,    // pointer to display name
    OUT ULONG     *lpcbeid,             // pointer count of bytes in entry ID
    OUT LPENTRYID *lppeid)              // pointer to entry ID
{
    HRESULT      hr         = NOERROR;
    HRESULT      hrT        = NOERROR;
    SCODE        sc         = 0;
    ULONG        cBytes     = 0;
    LPADRLIST    lpAdrListT = NULL;
    LPADRLIST    lpAdrList  = NULL;
    ULONG        cValues    = 0;
    LPSPropValue lpProps    = NULL;
    LPSPropValue lpPropT    = NULL;
    LPMAPITABLE  lpTable    = NULL;
    ULONG        cRows      = 0;

    SPropValue   prop[2]    = {0};

    SizedSPropTagArray(2, rgPropTags) =
    {
        2, 
        {
            PR_DISPLAY_NAME,
            PR_ENTRYID,
        }
    };

    DEBUGPUBLIC("HrBuildSampleRNSender()\n");

    hr = CHK_HrBuildSampleRNSender(
        lpMessage,
        lpAdrBook,
        lppszDisplayName,
        lpcbeid,
        lppeid);

    if(FAILED(hr))
        RETURN(hr);

    *lpcbeid = 0;
    *lppeid  = NULL;

//------------------------------------------------------------------------------

    //
    // Get a row from the recipient table
    //

    hrT = MAPICALL(lpMessage)->GetRecipientTable(
        lpMessage,
        MAPI_DEFERRED_ERRORS,
        &lpTable);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpTable)->GetRowCount(lpTable, 0, &cRows);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpTable)->QueryRows(
        lpTable,
        cRows,
        0,
        (LPSRowSet *)&lpAdrListT);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
    else if((lpAdrListT == NULL) || (lpAdrListT->cEntries != cRows))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

//------------------------------------------------------------------------------

    //
    // Get the entry ID
    //

    cValues = lpAdrListT->aEntries[0].cValues;
    lpProps = lpAdrListT->aEntries[0].rgPropVals;

    lpPropT = LpValFindProp(PR_ENTRYID, cValues, lpProps);

    if(lpPropT != NULL)
    {
        if((lpPropT->Value.bin.cb == 0) || (lpPropT->Value.bin.lpb == NULL))
        {
            hr = HR_LOG(E_FAIL);                                 
            goto cleanup;
        }
    }
    else
    {
        hr = HR_LOG(E_FAIL);                                 
        goto cleanup;
    }

    prop[0].ulPropTag       = PR_ENTRYID;
    prop[0].Value.bin.cb    = lpPropT->Value.bin.cb;
    prop[0].Value.bin.lpb   = (LPBYTE)lpPropT->Value.bin.lpb;
    prop[1].ulPropTag       = PR_RECIPIENT_TYPE;
    prop[1].Value.ul        = MAPI_TO;

    hr = HrMAPICreateSizedAddressList(1, &lpAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetAddressList(
        0,
        2,
        prop,
        lpAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = MAPICALL(lpAdrBook)->PrepareRecips( lpAdrBook,
        0,
        (LPSPropTagArray)&rgPropTags,
        lpAdrList);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Copy the display name
    //

    cBytes = cbStrLen(lpAdrList->aEntries[0].rgPropVals[0].Value.LPSZ);

    sc = MAPIAllocateBuffer(cBytes, lppszDisplayName);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;
    }                                                   

    CopyMemory(
        *lppszDisplayName,
        lpAdrList->aEntries[0].rgPropVals[0].Value.LPSZ,
        cBytes);

    //
    // Copy the entry ID
    //

    cBytes = lpAdrList->aEntries[0].rgPropVals[1].Value.bin.cb;

    sc = MAPIAllocateBuffer(cBytes, lppeid);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;
    }                                                   

    *lpcbeid = cBytes;

    CopyMemory(
        *lppeid,
        lpAdrList->aEntries[0].rgPropVals[1].Value.bin.lpb,
        cBytes);

cleanup:

    ULRELEASE(lpTable);

    FREEPADRLIST(lpAdrListT);
    FREEPADRLIST(lpAdrList);

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(*lppszDisplayName);

        *lpcbeid = 0;

        MAPIFREEBUFFER(*lppeid);
    }

    RETURN(hr);
}

//$--HrSendRN-------------------------------------------------------------------
//  Send a read notification report.
// -----------------------------------------------------------------------------
HRESULT HrSendRN(                           // RETURNS: return code
    IN LPADRBOOK lpAdrBook,                 // pointer to address book
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpEnvelope,                // pointer to envelope
    IN LPMESSAGE lpMessage)                 // pointer to message
{
    HRESULT     hr                  = NOERROR;
    HRESULT     hrT                 = NOERROR;
    LPMESSAGE   lpReportEnvelope    = NULL;
    LPMESSAGE   lpReport            = NULL;
    LPTSTR      lpszDisplayName     = NULL;
    ULONG       cbeid               = 0;
    LPENTRYID   lpeid               = NULL;
    FILETIME    ft                  = {0};
    SPropValue  rgProps[3]          = {0};

    DEBUGPUBLIC("HrSendRN()\n");

    hr = CHK_HrSendRN(
        lpAdrBook,
        lpFolder,
        lpEnvelope,
        lpMessage);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrBuildSampleRNSender(
        lpEnvelope,
        lpAdrBook,
        &lpszDisplayName,
        &cbeid,
        &lpeid);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    GetSystemTimeAsFileTime( &ft);

    rgProps[0].ulPropTag     = PR_RCVD_REPRESENTING_NAME;
    rgProps[0].Value.LPSZ    = lpszDisplayName;

    rgProps[1].ulPropTag     = PR_RCVD_REPRESENTING_ENTRYID;
    rgProps[1].Value.bin.cb  = cbeid;
    rgProps[1].Value.bin.lpb = (LPBYTE)lpeid;

    rgProps[2].ulPropTag     = PR_CLIENT_SUBMIT_TIME;
    rgProps[2].Value.ft      = ft;

     hrT = MAPICALL(lpMessage)->SetProps(
        lpMessage,
        3,
        rgProps,
        NULL);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrEDKCreateReadNotificationReport(
        lpFolder,
        lpMessage,
        TEXT("sample report text"),
        &lpReportEnvelope,
        &lpReport);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Submit report
    hrT = MAPICALL(lpReportEnvelope)->SubmitMessage(lpReportEnvelope, FORCE_SUBMIT);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    MAPIFREEBUFFER(lpszDisplayName);

    MAPIFREEBUFFER(lpeid);

    ULRELEASE(lpReport);

    ULRELEASE(lpReportEnvelope);

    RETURN(hr);
}

//$--HrSendNRN------------------------------------------------------------------
//  Send a non-read notification report.
// -----------------------------------------------------------------------------
HRESULT HrSendNRN(                          // RETURNS: return code
    IN LPADRBOOK lpAdrBook,                 // pointer to address book
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpEnvelope,                // pointer to envelope
    IN LPMESSAGE lpMessage)                 // pointer to message
{
    HRESULT     hr                  = NOERROR;
    HRESULT     hrT                 = NOERROR;
    LPMESSAGE   lpReportEnvelope    = NULL;
    LPMESSAGE   lpReport            = NULL;
    LPTSTR      lpszDisplayName     = NULL;
    ULONG       cbeid               = 0;
    LPENTRYID   lpeid               = NULL;
    FILETIME    ft                  = {0};
    SPropValue  rgProps[3]          = {0};

    DEBUGPUBLIC("HrSendNRN()\n");

    hr = CHK_HrSendNRN(
        lpAdrBook,
        lpFolder,
        lpEnvelope,
        lpMessage);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrBuildSampleRNSender(
        lpEnvelope,
        lpAdrBook,
        &lpszDisplayName,
        &cbeid,
        &lpeid);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    GetSystemTimeAsFileTime( &ft);

    rgProps[0].ulPropTag     = PR_RCVD_REPRESENTING_NAME;
    rgProps[0].Value.LPSZ    = lpszDisplayName;

    rgProps[1].ulPropTag     = PR_RCVD_REPRESENTING_ENTRYID;
    rgProps[1].Value.bin.cb  = cbeid;
    rgProps[1].Value.bin.lpb = (LPBYTE)lpeid;

    rgProps[2].ulPropTag     = PR_CLIENT_SUBMIT_TIME;
    rgProps[2].Value.ft      = ft;

     hrT = MAPICALL(lpMessage)->SetProps(
        lpMessage,
        3,
        rgProps,
        NULL);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrEDKCreateNonReadNotificationReport(
        lpFolder,
        lpMessage,
        TEXT("sample report text"),
        0,
        0,
        &lpReportEnvelope,
        &lpReport);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Submit report
    hrT = MAPICALL(lpReportEnvelope)->SubmitMessage(lpReportEnvelope, FORCE_SUBMIT);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    MAPIFREEBUFFER(lpszDisplayName);

    MAPIFREEBUFFER(lpeid);

    ULRELEASE(lpReport);

    ULRELEASE(lpReportEnvelope);

    RETURN(hr);
}

//$--HrSendReport---------------------------------------------------------------
//
//  Send a report to the originator of the message.
//
// -----------------------------------------------------------------------------
HRESULT HrSendReport(                   // RETURNS: return code
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    IN LPMESSAGE lpMessage,             // pointer to message
    IN LPMESSAGE lpEnvelope)            // pointer to envelope
{
    HRESULT  hr              = NOERROR;
    ULONG    ulReportType    = 0;
    ULONG    cbSubject       = 0;
    LPTSTR   lpszSubject     = NULL;
    LPTSTR   lpszNullSubject = TEXT("NULL");

    hr = CHK_HrSendReport(
        lpAdrBook,
        lpMessage,
        lpEnvelope);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrMAPIGetPropString(
        (LPMAPIPROP)lpMessage,
        PR_SUBJECT,
        &cbSubject,
        (void **)&lpszSubject);

    if(FAILED(hr) && (hr != MAPI_E_NOT_FOUND))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(lpszSubject == NULL)
    {
        lpszSubject = lpszNullSubject;
    }

    //
    // Determine which type of report to return to the originator.
    //

    ulReportType = UlMakeReportType(lpszSubject);

    //
    // Send the report.
    //

    switch(ulReportType)
    {
    case NDR:
        hr = HrSendNDR(
            lpAdrBook,
            lpMtsInFolder,
            lpEnvelope,
            lpMessage);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        break;
    case DR:
        hr = HrSendDR(
            lpAdrBook,
            lpMtsInFolder,
            lpEnvelope,
            lpMessage);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        break;
    case RN:
        hr = HrSendRN(
            lpAdrBook,
            lpMtsInFolder,
            lpEnvelope,
            lpMessage);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        break;
    case NRN:
        hr = HrSendNRN(
            lpAdrBook,
            lpMtsInFolder,
            lpEnvelope,
            lpMessage);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        break;
    default:
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    if(lpszSubject != lpszNullSubject)
    {
        MAPIFREEBUFFER(lpszSubject);
    }

    RETURN(hr);
}

//$--Process--------------------------------------------------------------------
//  Process messages arriving at MTS-OUT.
// -----------------------------------------------------------------------------
DWORD Process(
    IN LPVOID lpParameter)
{
    HRESULT      hr                 = NOERROR;
    HRESULT      hrT                = 0;
    ULONG        i                  = 0;
    ULONG        cRows              = 0;
    ULONG        cValues            = 0;
    ULONG        ulObjType          = 0;

    LPADRBOOK    lpAdrBook          = NULL;

    LPMESSAGE    lpMessage          = NULL;
    LPMESSAGE    lpEnvelope         = NULL;
    LPATTACH     lpAttach           = NULL;

    ULONG        cbeid              = 0;
    LPENTRYID    lpeid              = NULL;

    LPTSTR       pszMessageClass    = NULL;
    ULONG        cbMessageClass     = 0;

    LPSPropValue lpProps            = NULL;


    cRows = GetGWSRowSet(lpParameter)->cRows;

    // Open the Address Book
    hrT = MAPICALL(lpSession)->OpenAddressBook(
        lpSession,
        0,
        NULL, 
        AB_NO_DIALOG,
        &lpAdrBook);

    if(FAILED(hrT))                 
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0; i < cRows; i++)
    {
        cValues = GetGWSRowSet(lpParameter)->aRow[i].cValues;

        lpProps = GetGWSRowSet(lpParameter)->aRow[i].lpProps;

        cbeid = lpProps[0].Value.bin.cb;
        lpeid = (LPENTRYID)lpProps[0].Value.bin.lpb;

        // Get the message in the MTS-OUT folder
        hrT = MAPICALL(lpMtsOutFolder)->OpenEntry(
            lpMtsOutFolder,
            cbeid,
            lpeid,
            NULL,
            MAPI_MODIFY|MAPI_DEFERRED_ERRORS,
            &ulObjType,
            (LPUNKNOWN FAR *)&lpEnvelope);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        if(ulObjType != MAPI_MESSAGE)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Get the attachment in the envelope
        hrT = MAPICALL(lpEnvelope)->OpenAttach(
            lpEnvelope,
            0,
            NULL,
            MAPI_MODIFY|MAPI_DEFERRED_ERRORS,
            &lpAttach);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Open a message interface on the attachment
        hrT = MAPICALL(lpAttach)->OpenProperty(
            lpAttach,
            PR_ATTACH_DATA_OBJ,
            (LPIID)&IID_IMessage,
            0,
            MAPI_MODIFY|MAPI_DEFERRED_ERRORS,
            (LPUNKNOWN *)&lpMessage);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // ---------------------------------------------------------------------

        (void)HrSendReport(lpAdrBook, lpMessage, lpEnvelope);

        // ---------------------------------------------------------------------

        ULRELEASE(lpMessage);

        ULRELEASE(lpAttach);

        ULRELEASE(lpEnvelope);

        // ---------------------------------------------------------------------

        hr = HrMAPIDeleteMessage(
            lpMtsOutFolder,
            cbeid,
            lpeid);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // ---------------------------------------------------------------------
    }

cleanup:

    ULRELEASE(lpAttach);

    ULRELEASE(lpMessage);

    ULRELEASE(lpEnvelope);

    MAPIFREEBUFFER(pszMessageClass);

    ULRELEASE(lpAdrBook);

    RETURN(0);
}

//$--GWMain----------------------------------------------------------------
//  Start threads.
// -----------------------------------------------------------------------------
void GWMain(
    void)
{
    HRESULT               hr                     = NOERROR;
    EDK_SERVICE_CONTROL_T sc                     = 0;
    DWORD                 dwRet                  = 0;
    CHAR                  szTempPath[MAX_PATH+1] = {0};

    dwRet = GetTempPath(MAX_PATH, szTempPath);

    if((dwRet == 0) || (dwRet > MAX_PATH))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGWStartNewMailHandler(
        1000,
        (ULONG)-1,
        1,
        1,
        EXCHANGE_ADDRTYPE,			// Currently "EX"
        szTempPath,
        (LPTHREAD_START_ROUTINE)Process);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    if(FAILED(hr))
    {
        ServiceStop();
    }

    //
    // Wait for a request for the service to stop.
    //

    hr = HR_LOG(HrServiceWaitForStop(INFINITE, &sc));

    return;
}

//$--HrGWLogon-------------------------------------------------------------
//  Logon to the gateway.
// -----------------------------------------------------------------------------
HRESULT HrGWLogon(void)
{
    HRESULT hr = NOERROR;

    lpSession      = GetGWSession();
    lpStore        = GetGWDefaultStore();
    lpRootFolder   = GetGWRootFolder();
    lpMtsInFolder  = GetGWMtsInFolder();
    lpMtsOutFolder = GetGWMtsOutFolder();
    cbGalEid       = GetGWGALEntryIdSize();
    lpGalEid       = GetGWGALEntryId();

    RETURN(hr);
}

//$--HrGWLogoff------------------------------------------------------------
//  Logoff of the gateway.
// -----------------------------------------------------------------------------
HRESULT HrGWLogoff(void)
{
    HRESULT hr = NOERROR;
            
    RETURN(hr);
}
