// --gwreport.c-----------------------------------------------------------------
// 
//  Gateway report functions.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "gwreport.h"

#define SZ_MTS_ID               "/c=XX/a=X/p=X/l=X"

#define CENTRIES_FIRST  4
#define CENTRIES_NEXT   32

//$--HrCreateEmptyRecipList-----------------------------------------------------
//
//  Create an empty list of recipients.
//
// -----------------------------------------------------------------------------
static HRESULT HrCreateEmptyRecipList(      // RETURNS: return code
    OUT    LPADRLIST*    lppAdrList)        // address list
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("HrCreateEmptyRecipList()\n");

    hr = HrMAPICreateSizedAddressList(
        CENTRIES_FIRST,
        lppAdrList);

    if(FAILED(hr))
    {
        goto cleanup;
    }
    else
    {
        (*lppAdrList)->cEntries = 0;
    }

cleanup:

    RETURN(hr);
}

//$--HrNDRCreateFailedRecipList-------------------------------------------------
//
//  Create an empty list of failed recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRCreateFailedRecipList(         // RETURNS: return code
    OUT    LPADRLIST*    lppAdrList)        // address list
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrNDRCreateFailedRecipList()\n");

    hr = HrCreateEmptyRecipList(lppAdrList);

    RETURN(hr);
}

//$--HrNDRGetFailedRecipList----------------------------------------------------
//
//  Create a failed recipient entry.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRGetFailedRecipList(            // RETURNS: return code
    IN     LPADRENTRY    lpAdrEntry,        // address entry
    IN     ULONG         cExtraProps,       // count of extra properties
    IN     LPSPropValue  lpExtraProps,      // extra properties
    OUT    ULONG*        lpcFailedProps,    // count of failed properties
    OUT    LPSPropValue* lppFailedProps)    // failed properties
{
    HRESULT      hr           = NOERROR;
    FILETIME     ftReportTime = {0};
    ULONG        i            = 0;
    SPropValue   rgProps[9]   = {0};
    ULONG        cValues      = 0;
    LPSPropValue lpProps      = NULL;
    ULONG        cNewValues   = 0;
    LPSPropValue lpNewProps   = NULL;
    LPSPropValue lpPropT      = NULL;

    DEBUGPUBLIC("HrNDRGetFailedRecipList()\n");

    //
    // Get the current time
    //

    if((cExtraProps > 0) && (lpExtraProps != NULL))
    {
        hr = HrMAPIAppendSPropValues(
            lpAdrEntry->cValues,
            lpAdrEntry->rgPropVals,
            cExtraProps,
            lpExtraProps,
            &cValues,
            &lpProps);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }
    else
    {
        cValues = lpAdrEntry->cValues;

        hr = ScDupPropset(
            lpAdrEntry->cValues,
            lpAdrEntry->rgPropVals,
    		MAPIAllocateBuffer,
            &lpProps);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }

    //
    // Default any missing properties.
    //

    lpPropT = LpValFindProp(PR_NDR_REASON_CODE, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_NDR_REASON_CODE))
    {
        rgProps[i  ].ulPropTag = PR_NDR_REASON_CODE;
        rgProps[i++].Value.l   = 0;
    }

    lpPropT = LpValFindProp(PR_NDR_DIAG_CODE, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_NDR_DIAG_CODE))
    {
        rgProps[i  ].ulPropTag = PR_NDR_DIAG_CODE;
        rgProps[i++].Value.l   = -1;
    }

    lpPropT = LpValFindProp(PR_REPORT_TIME, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_REPORT_TIME))
    {
        GetSystemTimeAsFileTime( &ftReportTime);

        rgProps[i  ].ulPropTag = PR_REPORT_TIME;
        rgProps[i++].Value.ft  = ftReportTime;
    }

    lpPropT = LpValFindProp(PR_REPORT_TEXT, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_REPORT_TEXT))
    {
        rgProps[i  ].ulPropTag  = PR_REPORT_TEXT;
        rgProps[i++].Value.LPSZ = TEXT(" ");
    }

    lpPropT = LpValFindProp(PR_RECIPIENT_NUMBER, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_RECIPIENT_NUMBER))
    {
        rgProps[i  ].ulPropTag = PR_RECIPIENT_NUMBER;
        rgProps[i++].Value.l   = 1;
    }

    lpPropT = LpValFindProp(
        PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED;
        rgProps[i++].Value.b   = TRUE;
    }

    lpPropT = LpValFindProp(
        PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
        rgProps[i++].Value.b   = FALSE;
    }

    lpPropT = LpValFindProp(
        PR_READ_RECEIPT_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_READ_RECEIPT_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_READ_RECEIPT_REQUESTED;
        rgProps[i++].Value.b   = FALSE;
    }

    lpPropT = LpValFindProp(
        PR_NON_RECEIPT_NOTIFICATION_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_NON_RECEIPT_NOTIFICATION_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_NON_RECEIPT_NOTIFICATION_REQUESTED;
        rgProps[i++].Value.b   = FALSE;
    }

    if(i > 0)
    {
        hr = HrMAPIAppendSPropValues(
            cValues,
            lpProps,
            i,
            rgProps,
            &cNewValues,
            &lpNewProps);

        MAPIFREEBUFFER(lpProps);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        *lpcFailedProps = cNewValues;
        *lppFailedProps = lpNewProps;
    }
    else
    {
        *lpcFailedProps = cValues;
        *lppFailedProps = lpProps;
    }

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(lpProps);
        MAPIFREEBUFFER(lpNewProps);

        *lpcFailedProps = 0;
        *lppFailedProps = NULL;
    }

    RETURN(hr);
}

//$--HrAddToRecipList-----------------------------------------------------------
//
//  Add a recipient entry to the list of recipients.
//
// -----------------------------------------------------------------------------
static HRESULT HrAddToRecipList(            // RETURNS: return code
    IN     ULONG         cProps,            // count of properties
    IN     LPSPropValue  lpProps,           // properties
    IN OUT LPADRLIST*    lppAdrList)        // address list
{
    HRESULT    hr          = NOERROR;
    SCODE      sc          = 0;
    ULONG      cOldEntries = 0;
    ULONG      cEntries    = 0;
    ULONG      cBytes      = 0;
    ULONG      i           = 0;
    LPADRENTRY lpAdrEntry  = NULL;
    LPADRLIST  lpAdrList   = NULL;

    DEBUGPRIVATE("HrAddToRecipList()\n");

    cEntries = (*lppAdrList)->cEntries;

    cOldEntries = cEntries;

    //
    // Grow the address list if necessary.
    //

    if((cEntries == CENTRIES_FIRST) ||
       ((cEntries > CENTRIES_FIRST) &&
       (((cEntries - CENTRIES_FIRST) % CENTRIES_NEXT) == 0)))
    {
        cEntries += CENTRIES_NEXT;

        cBytes = CbNewADRLIST(cEntries);

        sc = MAPIAllocateBuffer(cBytes, (void **)&lpAdrList);

        if(FAILED(sc))                           
        {                                                   
            hr = HR_LOG(E_OUTOFMEMORY);                                 
            goto cleanup;
        }                                                   

        ZeroMemory(lpAdrList, cBytes);

        lpAdrEntry = lpAdrList->aEntries;

        //
        // Copy existing address entries to the new address list.
        //

        for(i = 0; i < (*lppAdrList)->cEntries; i++)
        {
            lpAdrEntry[i].cValues =
                (*lppAdrList)->aEntries[i].cValues;
            lpAdrEntry[i].rgPropVals =
                (*lppAdrList)->aEntries[i].rgPropVals;
        }

        MAPIFREEBUFFER(*lppAdrList);

        *lppAdrList = lpAdrList;
    }

    //
    // Add an address entry to the address list.
    //

    i = cOldEntries;

    (*lppAdrList)->cEntries = ++i;

    i--;

    hr = HrMAPISetAddressList(
        i,
        cProps,
        lpProps,
        *lppAdrList);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrNDRAddToFailedRecipList--------------------------------------------------
//
//  Add a recipient entry to the list of failed recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRAddToFailedRecipList(          // RETURNS: return code
    IN     ULONG         cFailedProps,      // count of failed properties
    IN     LPSPropValue  lpFailedProps,     // failed properties
    IN OUT LPADRLIST*    lppAdrList)        // address list
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrNDRAddToFailedRecipList()\n");

    hr = HrAddToRecipList(cFailedProps, lpFailedProps, lppAdrList);

    RETURN(hr);
}

//$--HrExtractProps-------------------------------------------------------------
//
//  Get NDR/DR properties from the original message.
//
// -----------------------------------------------------------------------------
static HRESULT HrExtractProps(              // RETURNS: return code
    IN     BOOL          IsNdr,             // report is an NDR, otherwise a DR
    IN     LPMESSAGE     lpMessage,         // message
    OUT    ULONG*        lpcProps,          // count of properties
    OUT    LPSPropValue* lppProps)          // properties
{
    HRESULT      hr                     = NOERROR;
    SCODE        sc                     = 0;
    ULONG        cBytes                 = 0;
	FILETIME     ftSubmitTime           = {0};
    ULONG        i                      = 0;
    ULONG        cValues                = 0;
    LPSPropValue lpProps                = NULL;
    LPSTR       lpszMessageClass       = NULL;
    LPSTR       lpszReportMessageClass = NULL;
    LPSTR       lpsz                   = NULL;
    ULONG        cch                    = 0;

	SizedSPropTagArray(18, rgMessagePropTags) =
	{
		18,
		{
			PR_MESSAGE_CLASS,
            PR_SUBJECT,
            PR_NORMALIZED_SUBJECT,
			PR_SUBJECT_PREFIX,
			PR_CLIENT_SUBMIT_TIME,
            PR_MTS_ID,
            PR_SENDER_NAME,
            PR_SENDER_ENTRYID,
            PR_DELETE_AFTER_SUBMIT,
            PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED,
            PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED,
            PR_READ_RECEIPT_REQUESTED,
            PR_NON_RECEIPT_NOTIFICATION_REQUESTED,
            PR_CONTENT_RETURN_REQUESTED,
            PR_PRIORITY,
            PR_IMPORTANCE,
            PR_REPORT_NAME,
            PR_REPORT_ENTRYID
        }
    };

    DEBUGPRIVATE("HrExtractProps()\n");

    //
    // Get report properties from the message.
    //

	hr = MAPICALL(lpMessage)->GetProps(
	    lpMessage,
		(LPSPropTagArray)&rgMessagePropTags,
		fMapiUnicode,
		&cValues,
		&lpProps);

	if(FAILED(hr))
	{
        lpProps = NULL;

		goto cleanup;
	}

    //
    // Create report message class
    //

    if(lpProps[0].ulPropTag == PR_MESSAGE_CLASS)
    {
        lpszMessageClass = lpProps[0].Value.LPSZ;
    }

    if(lpszMessageClass == NULL)
    {
        cch = 0;
    }
    else
    {
        cch = lstrlen(lpszMessageClass);
    }

    if(cch == 0)
    {
        lpszMessageClass = TEXT("IPM.NOTE");
        cch = lstrlen(lpszMessageClass);
    }

    cch += lstrlen(TEXT("REPORT."));

    if(IsNdr == TRUE)
    {
        cch += lstrlen(TEXT(".NDR"));
    }
    else
    {
        cch += lstrlen(TEXT(".DR"));
    }

    cch++; // terminating NULL character

    cBytes = cch * sizeof(CHAR);

    sc = MAPIAllocateMore(cBytes, lpProps, &lpszReportMessageClass);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;
    }                                                   

    lstrcpy(lpszReportMessageClass, TEXT("REPORT."));
    lstrcat(lpszReportMessageClass, lpszMessageClass);
    if(IsNdr == TRUE)
    {
        lstrcat(lpszReportMessageClass, TEXT(".NDR"));
    }
    else
    {
        lstrcat(lpszReportMessageClass, TEXT(".DR"));
    }

    //
    // PR_MESSAGE_CLASS
    //

	lpProps[0].ulPropTag  = PR_MESSAGE_CLASS;
    lpProps[0].Value.LPSZ = lpszReportMessageClass;

    //
    // PR_SUBJECT
    //

	if(lpProps[1].ulPropTag != PR_SUBJECT)
    {
        cBytes = cbStrLen("");

        sc = MAPIAllocateMore(cBytes, lpProps, &lpsz);

        if(FAILED(sc))                           
        {                                                   
            hr = HR_LOG(E_OUTOFMEMORY);                                 
            goto cleanup;
        }                                                   

        lstrcpy(lpsz, TEXT(""));

	    lpProps[1].ulPropTag  = PR_SUBJECT;
	    lpProps[1].Value.LPSZ = lpsz;
    }

    //
    // PR_NORMALIZED_SUBJECT
    //

	if(lpProps[2].ulPropTag != PR_NORMALIZED_SUBJECT)
    {
        cBytes = cbStrLen("");

        sc = MAPIAllocateMore(cBytes, lpProps, &lpsz);

        if(FAILED(sc))                           
        {                                                   
            hr = HR_LOG(E_OUTOFMEMORY);                                 
            goto cleanup;
        }                                                   

        lstrcpy(lpsz, TEXT(""));

	    lpProps[2].ulPropTag  = PR_NORMALIZED_SUBJECT;
	    lpProps[2].Value.LPSZ = lpsz;
    }

    //
    // PR_SUBJECT_PREFIX
    //

	if(lpProps[3].ulPropTag != PR_SUBJECT_PREFIX)
    {
        cBytes = cbStrLen("");

        sc = MAPIAllocateMore(cBytes, lpProps, &lpsz);

        if(FAILED(sc))                           
        {                                                   
            hr = HR_LOG(E_OUTOFMEMORY);                                 
            goto cleanup;
        }                                                   

        lstrcpy(lpsz, TEXT(""));

	    lpProps[3].ulPropTag  = PR_SUBJECT_PREFIX;
	    lpProps[3].Value.LPSZ = lpsz;
    }

    //
    // PR_CLIENT_SUBMIT_TIME
    //

	if(lpProps[4].ulPropTag != PR_CLIENT_SUBMIT_TIME)
    {
	    GetSystemTimeAsFileTime( &ftSubmitTime);

	    lpProps[4].ulPropTag = PR_CLIENT_SUBMIT_TIME;
	    lpProps[4].Value.ft  = ftSubmitTime;
    }

    //
    // PR_MTS_SUBJECT_ID
    //

	if(lpProps[5].ulPropTag != PR_MTS_ID)
    {
        cBytes = cbStrLen(SZ_MTS_ID);

        sc = MAPIAllocateMore(cBytes, lpProps, &lpsz);

        if(FAILED(sc))                           
        {                                                   
            hr = HR_LOG(E_OUTOFMEMORY);                                 
            goto cleanup;
        }                                                   

        lstrcpy(lpsz, TEXT(SZ_MTS_ID));

    	lpProps[5].ulPropTag     = PR_MTS_ID;
    	lpProps[5].Value.bin.cb  = cBytes;
    	lpProps[5].Value.bin.lpb = (LPBYTE) lpsz;	 
    }

    lpProps[5].ulPropTag         = PR_MTS_SUBJECT_ID;

    if((lpProps[16].ulPropTag == PR_REPORT_NAME) &&
       (lpProps[17].ulPropTag == PR_REPORT_ENTRYID))
    {
        lpProps[6].ulPropTag     = PR_SENDER_NAME;
        lpProps[6].Value.LPSZ    = lpProps[16].Value.LPSZ;

        lpProps[7].ulPropTag     = PR_SENDER_ENTRYID;
        lpProps[7].Value.bin.cb  = lpProps[17].Value.bin.cb;
        lpProps[7].Value.bin.lpb = lpProps[17].Value.bin.lpb;
    }

    //
    // PR_REPORT_DESTINATION_NAME
    //

	if(lpProps[6].ulPropTag != PR_SENDER_NAME)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lpProps[6].ulPropTag         = PR_REPORT_DESTINATION_NAME;

    //
    // PR_REPORT_DESTINATION_ENTRYID
    //

	if(lpProps[7].ulPropTag != PR_SENDER_ENTRYID)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lpProps[7].ulPropTag         = PR_REPORT_DESTINATION_ENTRYID;

    //
    // PR_DELETE_AFTER_SUBMIT
    //

    lpProps[8].ulPropTag         = PR_DELETE_AFTER_SUBMIT;
    lpProps[8].Value.b           = TRUE;

    //
    // PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED
    //

	if(lpProps[9].ulPropTag != PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED)
    {
        lpProps[9].ulPropTag = PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED;
        lpProps[9].Value.b   = TRUE;
    }

    //
    // PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED
    //

	if(lpProps[10].ulPropTag != PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED)
    {
        lpProps[10].ulPropTag = PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
        lpProps[10].Value.b   = FALSE;
    }

    //
    // PR_READ_RECEIPT_REQUESTED
    //

	if(lpProps[11].ulPropTag != PR_READ_RECEIPT_REQUESTED)
    {
        lpProps[11].ulPropTag = PR_READ_RECEIPT_REQUESTED;
        lpProps[11].Value.b   = FALSE;
    }

    //
    // PR_NON_RECEIPT_NOTIFICATION_REQUESTED
    //

	if(lpProps[12].ulPropTag != PR_NON_RECEIPT_NOTIFICATION_REQUESTED)
    {
        lpProps[12].ulPropTag = PR_NON_RECEIPT_NOTIFICATION_REQUESTED;
        lpProps[12].Value.b   = FALSE;
    }

    //
    // PR_CONTENT_RETURN_REQUESTED
    //

	if(lpProps[13].ulPropTag != PR_CONTENT_RETURN_REQUESTED)
    {
        lpProps[13].ulPropTag = PR_CONTENT_RETURN_REQUESTED;
        lpProps[13].Value.b   = TRUE;
    }

    //
    // PR_PRIORITY
    //

	if(lpProps[14].ulPropTag != PR_PRIORITY)
    {
        lpProps[14].ulPropTag = PR_PRIORITY;
        lpProps[14].Value.l   = PRIO_NORMAL;
    }

    //
    // PR_IMPORTANCE
    //

	if(lpProps[15].ulPropTag != PR_IMPORTANCE)
    {
        lpProps[15].ulPropTag = PR_IMPORTANCE;
        lpProps[15].Value.l   = IMPORTANCE_NORMAL;
    }

    *lpcProps = cValues - 2;
    *lppProps = lpProps;

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(lpProps);

        *lpcProps = 0;
        *lppProps = NULL;
    }

    RETURN(hr);
}

//$--HrNDRGetFailedProps----------------------------------------------------------
//
//  Get NDR properties from the original message.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRGetFailedProps(                  // RETURNS: return code
    IN     LPMESSAGE     lpMessage,         // message
    OUT    ULONG*        lpcProps,          // count of properties
    OUT    LPSPropValue* lppProps)          // properties
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrNDRGetFailedProps()\n");

    hr = HrExtractProps(TRUE, lpMessage, lpcProps, lppProps);

    RETURN(hr);
}

//$--HrXDRCreate----------------------------------------------------------------
//
//  Create a non-delivery or delivery report.
//
// -----------------------------------------------------------------------------
static HRESULT HrXDRCreate(                 // RETURNS: return code
    IN     LPADRBOOK     lpAdrBook,         // address book
    IN     LPMAPIFOLDER  lpFolder,          // folder
    IN     LPMESSAGE     lpMessage,         // message
    IN     LPADRLIST     lpAdrList,         // address list
    IN     ULONG         cProps,            // count of properties
    IN     LPSPropValue  lpProps,           // properties
    OUT    LPMESSAGE*    lppReport)         // report
{
    HRESULT      hr              = NOERROR;
    LPMESSAGE    lpReport        = NULL;
    ULONG        ulAttachmentNum = 0;
    LPATTACH     lpAttach        = NULL;
    LPMESSAGE    lpContent       = NULL;
    BOOL         fReturnContent  = FALSE;
    SPropValue   rgProps[1]      = {0};
    LPSPropValue lpPropT         = NULL;

    DEBUGPRIVATE("HrXDRCreate()\n");

    *lppReport = NULL;

    //
    // Create a message
    //

    hr = MAPICALL(lpFolder)->CreateMessage(
        lpFolder,
        NULL,
        MAPI_DEFERRED_ERRORS,
        &lpReport);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Return content if available and requested.
    //

    lpPropT = LpValFindProp(
        PR_CONTENT_RETURN_REQUESTED, cProps, lpProps);

    if(lpPropT == NULL)
    {
        fReturnContent = TRUE;
    }
    else if(lpPropT->ulPropTag != PR_CONTENT_RETURN_REQUESTED)
    {
        lpPropT->ulPropTag = PR_CONTENT_RETURN_REQUESTED;
        lpPropT->Value.b   = TRUE;
    }
    else
    {
        fReturnContent = lpPropT->Value.b;
    }

    if((lpMessage != NULL) && (fReturnContent == TRUE))
    {
        //
        // Create an embedded message
        //

        hr = MAPICALL(lpReport)->CreateAttach(
            lpReport,
            NULL,
            (ULONG)0,
            &ulAttachmentNum,
            &lpAttach);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        rgProps[0].ulPropTag = PR_ATTACH_METHOD;
        rgProps[0].Value.ul  = ATTACH_EMBEDDED_MSG;

        hr = MAPICALL(lpAttach)->SetProps(
            lpAttach,
            1,
            rgProps,
            NULL);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        hr = MAPICALL(lpAttach)->OpenProperty(
            lpAttach,
            PR_ATTACH_DATA_OBJ,
            (LPIID)&IID_IMessage,
            0,
            MAPI_CREATE|MAPI_MODIFY|MAPI_DEFERRED_ERRORS,
            (LPUNKNOWN *)&lpContent);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }

    if(lpAdrList != NULL)
    {
        hr = MAPICALL(lpReport)->ModifyRecipients(
            lpReport,
            0,
            lpAdrList);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }

    //
    // Set envelope properties
    //

    if((cProps > 0) && (lpProps != NULL))
    {
        hr = MAPICALL(lpReport)->SetProps(
            lpReport,
            cProps,
            lpProps,
            NULL);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }

    if((lpMessage != NULL) && (fReturnContent == TRUE))
    {
        hr = MAPICALL(lpMessage)->CopyTo(
            lpMessage,
            0,
            NULL,
            NULL,
            0,
            NULL,
            (LPIID)&IID_IMessage,
            lpContent,
            0,
            NULL);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        if(hr == MAPI_W_ERRORS_RETURNED)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = MAPICALL(lpContent)->SaveChanges(lpContent, KEEP_OPEN_READWRITE);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        hr = MAPICALL(lpAttach)->SaveChanges(lpAttach, KEEP_OPEN_READWRITE);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }

    hr = MAPICALL(lpReport)->SaveChanges(lpReport, KEEP_OPEN_READWRITE);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    *lppReport = lpReport;

cleanup:

    ULRELEASE(lpContent);

    ULRELEASE(lpAttach);

    if(FAILED(hr))
    {
        ULRELEASE(lpReport);

        *lppReport = NULL;
    }

    RETURN(hr);
}

//$--HrNDRCreate----------------------------------------------------------------
//
//  Create a non-delivery report.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRCreate(                        // RETURNS: return code
    IN     LPADRBOOK     lpAdrBook,         // address book
    IN     LPMAPIFOLDER  lpFolder,          // folder
    IN     LPMESSAGE     lpMessage,         // message
    IN     LPADRLIST     lpAdrList,         // address list
    IN     ULONG         cProps,            // count of properties
    IN     LPSPropValue  lpProps,           // properties
    OUT    LPMESSAGE*    lppReport)         // report
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrNDRCreate()\n");

    hr = HrXDRCreate(
        lpAdrBook,
        lpFolder,
        lpMessage,
        lpAdrList,
        cProps,
        lpProps,
        lppReport);

    RETURN(hr);
}

//$--HrDRCreateDeliveredRecipList-----------------------------------------------
//
//  Create an empty list of delivered recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrDRCreateDeliveredRecipList(       // RETURNS: return code
    OUT    LPADRLIST*    lppAdrList)        // address list
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrDRCreateDeliveredRecipList()\n");

    hr = HrCreateEmptyRecipList(lppAdrList);

    RETURN(hr);
}

//$--HrDRGetDeliveredRecip--------------------------------------------------
//
//  Create a delivered recipient entry.
//
// -----------------------------------------------------------------------------
HRESULT HrDRGetDeliveredRecip(          // RETURNS: return code
    IN     LPADRENTRY    lpAdrEntry,        // address entry
    IN     ULONG         cExtraProps,       // count of extra properties
    IN     LPSPropValue  lpExtraProps,      // extra properties
    OUT    ULONG*        lpcDeliveredProps, // count of delivered properties
    OUT    LPSPropValue* lppDeliveredProps) // delivered properties
{
    HRESULT      hr            = NOERROR;
    FILETIME     ftReportTime  = {0};
    FILETIME     ftDeliverTime = {0};
    ULONG        i             = 0;
    SPropValue   rgProps[9]    = {0};
    ULONG        cValues       = 0;
    LPSPropValue lpProps       = NULL;
    ULONG        cNewValues    = 0;
    LPSPropValue lpNewProps    = NULL;
    LPSPropValue lpPropT       = NULL;

    DEBUGPUBLIC("HrDRGetDeliveredRecip()\n");

    if((cExtraProps > 0) && (lpExtraProps != NULL))
    {
        hr = HrMAPIAppendSPropValues(
            lpAdrEntry->cValues,
            lpAdrEntry->rgPropVals,
            cExtraProps,
            lpExtraProps,
            &cValues,
            &lpProps);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }
    else
    {
        cValues = lpAdrEntry->cValues;

        hr = ScDupPropset(
            lpAdrEntry->cValues,
            lpAdrEntry->rgPropVals,
    		MAPIAllocateBuffer,
            &lpProps);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }

    //
    // Default any missing properties.
    //

    lpPropT = LpValFindProp(PR_REPORT_TIME, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_REPORT_TIME))
    {
        GetSystemTimeAsFileTime( &ftReportTime);

        rgProps[i  ].ulPropTag = PR_REPORT_TIME;
        rgProps[i++].Value.ft  = ftReportTime;
    }

    lpPropT = LpValFindProp(PR_REPORT_TEXT, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_REPORT_TEXT))
    {
        rgProps[i  ].ulPropTag  = PR_REPORT_TEXT;
        rgProps[i++].Value.LPSZ = TEXT(" ");
    }

    lpPropT = LpValFindProp(PR_DELIVER_TIME, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_DELIVER_TIME))
    {
        GetSystemTimeAsFileTime( &ftDeliverTime);

        rgProps[i  ].ulPropTag = PR_DELIVER_TIME;
        rgProps[i++].Value.ft  = ftDeliverTime;
    }

    lpPropT = LpValFindProp(PR_REPORT_TEXT, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_REPORT_TEXT))
    {
        rgProps[i  ].ulPropTag  = PR_REPORT_TEXT;
        rgProps[i++].Value.LPSZ = TEXT(" ");
    }

    lpPropT = LpValFindProp(PR_RECIPIENT_NUMBER, cValues, lpProps);

    if((lpPropT == NULL) || (lpPropT->ulPropTag != PR_RECIPIENT_NUMBER))
    {
        rgProps[i  ].ulPropTag = PR_RECIPIENT_NUMBER;
        rgProps[i++].Value.l   = 1;
    }

    lpPropT = LpValFindProp(
        PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED;
        rgProps[i++].Value.b   = TRUE;
    }

    lpPropT = LpValFindProp(
        PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
        rgProps[i++].Value.b   = FALSE;
    }

    lpPropT = LpValFindProp(
        PR_READ_RECEIPT_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_READ_RECEIPT_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_READ_RECEIPT_REQUESTED;
        rgProps[i++].Value.b   = FALSE;
    }

    lpPropT = LpValFindProp(
        PR_NON_RECEIPT_NOTIFICATION_REQUESTED, cValues, lpProps);

    if((lpPropT == NULL) ||
       (lpPropT->ulPropTag != PR_NON_RECEIPT_NOTIFICATION_REQUESTED))
    {
        rgProps[i  ].ulPropTag = PR_NON_RECEIPT_NOTIFICATION_REQUESTED;
        rgProps[i++].Value.b   = FALSE;
    }

    if(i > 0)
    {
        hr = HrMAPIAppendSPropValues(
            cValues,
            lpProps,
            i,
            rgProps,
            &cNewValues,
            &lpNewProps);

        MAPIFREEBUFFER(lpProps);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        *lpcDeliveredProps = cNewValues;
        *lppDeliveredProps = lpNewProps;
    }
    else
    {
        *lpcDeliveredProps = cValues;
        *lppDeliveredProps = lpProps;
    }

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(lpProps);
        MAPIFREEBUFFER(lpNewProps);

        *lpcDeliveredProps = 0;
        *lppDeliveredProps = NULL;
    }

    RETURN(hr);
}

//$--HrDRAddToDeliveredRecipList------------------------------------------------
//
//  Add a recipient entry to the list of delivered recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrDRAddToDeliveredRecipList(        // RETURNS: return code
    IN     ULONG         cDeliveredProps,   // count of delivered properties
    IN     LPSPropValue  lpDeliveredProps,  // delivered properties
    IN OUT LPADRLIST*    lppAdrList)        // address list
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrDRAddToDeliveredRecipList()\n");

    hr = HrAddToRecipList(cDeliveredProps, lpDeliveredProps, lppAdrList);

    RETURN(hr);
}

//$--HrDRGetProps-----------------------------------------------------------
//
//  Get DR properties from the original message.
//
// -----------------------------------------------------------------------------
HRESULT HrDRGetProps(                   // RETURNS: return code
    IN     LPMESSAGE     lpMessage,         // message
    OUT    ULONG*        lpcProps,          // count of properties
    OUT    LPSPropValue* lppProps)          // properties
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrDRGetProps()\n");

    hr = HrExtractProps(FALSE, lpMessage, lpcProps, lppProps);

    RETURN(hr);
}

//$--HrDRCreate-----------------------------------------------------------------
//
//  Create a delivery report.
//
// -----------------------------------------------------------------------------
HRESULT HrDRCreate(                         // RETURNS: return code
    IN     LPADRBOOK     lpAdrBook,         // address book
    IN     LPMAPIFOLDER  lpFolder,          // folder
    IN     LPMESSAGE     lpMessage,         // message
    IN     LPADRLIST     lpAdrList,         // address list
    IN     ULONG         cProps,            // count of properties
    IN     LPSPropValue  lpProps,           // properties
    OUT    LPMESSAGE*    lppReport)         // report
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrDRCreate()\n");

    hr = HrXDRCreate(
        lpAdrBook,
        lpFolder,
        lpMessage,
        lpAdrList,
        cProps,
        lpProps,
        lppReport);

    RETURN(hr);
}
