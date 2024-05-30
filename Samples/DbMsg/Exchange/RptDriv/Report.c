// --report.c-------------------------------------------------------------------
// 
//  Module containing report functions.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"

//$--REPORT_T-------------------------------------------------------------------
//  Report type.
// -----------------------------------------------------------------------------
typedef enum __REPORT_T
{
    NDR = 0,        // non-delivery report
    DR,             // delivery report
    RN,             // read notification report
    NRN,            // non-read notification report
    REPORT_LAST     // all report values are less than this 
} REPORT_T;

#define VALID_REPORT_T(x) (((x) >= ((ULONG)0)) && \
                            ((x) <= ((ULONG)REPORT_LAST)))

#include "report.chk"

//$--HrEDKReportSubject---------------------------------------------------------
//  Return a report subject.
// -----------------------------------------------------------------------------
static HRESULT HrEDKReportSubject(          // RETURNS: return code
    IN REPORT_T ReportType,                 // report type
    IN LPTSTR lpszSubject,                  // pointer to subject
    OUT LPTSTR *lppszReportSubject)         // pointer to report subject
{
    HRESULT hr                  = NOERROR;
    ULONG   cch                 = 0;
    LPTSTR  lpszOrigSubject     = NULL;
    LPTSTR  lpszReportPrefix    = NULL;
    SCODE   sc                  = 0;
    ULONG   cBytes              = 0;

    DEBUGPRIVATE("HrEDKReportSubject()\n");

    hr = CHK_HrEDKReportSubject(
        ReportType,
        lpszSubject,
        lppszReportSubject);

    if(FAILED(hr))
        RETURN(hr);

    *lppszReportSubject = NULL;

    cch = 0;

    if(lpszSubject != NULL)
    {
        cch = lstrlen(lpszSubject);
    }

    if(cch == 0)
    {
        lpszOrigSubject = TEXT("");
    }
    else
    {
        lpszOrigSubject = lpszSubject;
    }

    switch(ReportType)
    {
    case NDR:
        lpszReportPrefix = TEXT("Undeliverable: ");
        break;
    case DR:
        lpszReportPrefix = TEXT("Delivered: ");
        break;
    case RN:
        lpszReportPrefix = TEXT("Read: ");
        break;
    case NRN:
        lpszReportPrefix = TEXT("Unread: ");
        break;
    default:
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cch += lstrlen(lpszReportPrefix);

    cch++;  // terminating NULL character

    cBytes = cch * sizeof(TCHAR);

    sc = MAPIAllocateBuffer(cBytes, lppszReportSubject);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;
    }                                                   

    _tcscpy(*lppszReportSubject, lpszReportPrefix);
    _tcscat(*lppszReportSubject, lpszOrigSubject);

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(*lppszReportSubject);
    }

    RETURN(hr);
}

//$--HrEDKReportMessageClass----------------------------------------------------
//  Return a report message class.
// -----------------------------------------------------------------------------
static HRESULT HrEDKReportMessageClass(     // RETURNS: return code
    IN REPORT_T ReportType,                 // report type
    IN LPTSTR lpszMessageClass,             // pointer to message class
    OUT LPTSTR *lppszReportMessageClass)    // pointer to report message class
{
    HRESULT hr                  = NOERROR;
    ULONG   cch                 = 0;
    LPTSTR  lpszMsgClass        = NULL;
    LPTSTR  lpszReportSuffix    = NULL;
    SCODE   sc                  = 0;
    ULONG   cBytes              = 0;

    DEBUGPRIVATE("HrEDKReportMessageClass()\n");

    hr = CHK_HrEDKReportMessageClass(
        ReportType,
        lpszMessageClass,
        lppszReportMessageClass);

    if(FAILED(hr))
        RETURN(hr);

    *lppszReportMessageClass = NULL;

    cch = lstrlen(lpszMessageClass);

    if(cch == 0)
    {
        lpszMsgClass = TEXT("IPM.NOTE");
        cch = lstrlen(lpszMsgClass);
    }
    else
    {
        lpszMsgClass = lpszMessageClass;
    }

    cch += lstrlen(TEXT("REPORT."));

    switch(ReportType)
    {
    case NDR:
        lpszReportSuffix = TEXT(".NDR");
        break;
    case DR:
        lpszReportSuffix = TEXT(".DR");
        break;
    case RN:
        lpszReportSuffix = TEXT(".IPNRN");
        break;
    case NRN:
        lpszReportSuffix = TEXT(".IPNNRN");
        break;
    default:
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cch += lstrlen(lpszReportSuffix);

    cch++;  // terminating NULL character

    cBytes = cch * sizeof(TCHAR);

    sc = MAPIAllocateBuffer(cBytes, lppszReportMessageClass);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;
    }                                                   

    _tcscpy(*lppszReportMessageClass, TEXT("REPORT."));
    _tcscat(*lppszReportMessageClass, lpszMsgClass);
    _tcscat(*lppszReportMessageClass, lpszReportSuffix);

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(*lppszReportMessageClass);
    }

    RETURN(hr);
}

//$--HrEDKSetReportMessageClass-------------------------------------------------
//  Set the report message class.
// -----------------------------------------------------------------------------
static HRESULT HrEDKSetReportMessageClass(  // RETURNS: return code
    IN REPORT_T ReportType,                 // report type
    IN LPMESSAGE lpMessage,                 // pointer to message
    IN OUT LPMESSAGE lpReport)              // pointer to report
{
    HRESULT hr                      = NOERROR;
    HRESULT hrT                     = 0;
    ULONG   cbMessageClass          = 0;
    LPTSTR  lpszMessageClass        = NULL;
    LPTSTR  lpszReportMessageClass  = NULL;

    DEBUGPRIVATE("HrEDKSetReportMessageClass()\n");

    hr = CHK_HrEDKSetReportMessageClass(
        ReportType,
        lpMessage,
        lpReport);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrMAPIGetPropString(
        (LPMAPIPROP)lpMessage,
        PR_MESSAGE_CLASS,
        &cbMessageClass,
        (LPVOID *)&lpszMessageClass);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrEDKReportMessageClass(
        ReportType,
        lpszMessageClass,
        &lpszReportMessageClass);

    MAPIFREEBUFFER(lpszMessageClass);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetPropString(
        (LPMAPIPROP)lpReport,
        PR_MESSAGE_CLASS,
        (LPVOID)lpszReportMessageClass);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    MAPIFREEBUFFER(lpszMessageClass);

    MAPIFREEBUFFER(lpszReportMessageClass);

    RETURN(hr);
}

//$--HrEDKEnvelopeMessageClass--------------------------------------------------
//  Return an envelope message class.
// -----------------------------------------------------------------------------
static HRESULT HrEDKEnvelopeMessageClass(   // RETURNS: return code
    IN LPTSTR lpszMessageClass,             // pointer to message class
    OUT LPTSTR *lppszEnvelopeMessageClass)  // pointer to envelope message class
{
    HRESULT hr                  = NOERROR;
    ULONG   cch                 = 0;
    LPTSTR  lpszMsgClass        = NULL;
    LPTSTR  lpszReportSuffix    = NULL;
    SCODE   sc                  = 0;
    ULONG   cBytes              = 0;

    DEBUGPRIVATE("HrEDKEnvelopeMessageClass()\n");

    hr = CHK_HrEDKEnvelopeMessageClass(
        lpszMessageClass,
        lppszEnvelopeMessageClass);

    if(FAILED(hr))
        RETURN(hr);

    *lppszEnvelopeMessageClass = NULL;

    cch = lstrlen(lpszMessageClass);

    if(cch == 0)
    {
        lpszMsgClass = "IPM.NOTE";
        cch = lstrlen(lpszMsgClass);
    }
    else
    {
        lpszMsgClass = lpszMessageClass;
    }

    cch += lstrlen(TEXT("ENVELOPE."));

    cch++;  // terminating NULL character

    cBytes = cch * sizeof(TCHAR);

    sc = MAPIAllocateBuffer(cBytes, lppszEnvelopeMessageClass);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;
    }                                                   

    _tcscpy(*lppszEnvelopeMessageClass, TEXT("ENVELOPE."));
    _tcscat(*lppszEnvelopeMessageClass, lpszMsgClass);

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(*lppszEnvelopeMessageClass);
    }

    RETURN(hr);
}

//$--HrEDKCopyReportProps-------------------------------------------------------
//  Copy report properties.
// -----------------------------------------------------------------------------
static HRESULT HrEDKCopyReportProps(        // RETURNS: return code
    IN REPORT_T ReportType,                 // report type
    IN LPMESSAGE lpReport,                  // pointer to report
    IN ULONG cbSubjectMtsId,                // count of bytes in subject MTS-ID
    IN LPBYTE lpSubjectMtsId,               // pointer to subject MTS-ID
    IN LPTSTR lpszReportName,               // pointer to report name
    IN ULONG cbReportEntryId,               // count of bytes in report entry ID
    IN LPENTRYID lpReportEntryId,           // pointer to report entry ID
    IN OUT LPMESSAGE lpReportEnvelope)      // pointer to report envelope
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("HrEDKCopyReportProps()\n");

    hr = CHK_HrEDKCopyReportProps(
        ReportType,
        lpReport,
        cbSubjectMtsId,
        lpSubjectMtsId,
        lpszReportName,
        cbReportEntryId,
        lpReportEntryId,
        lpReportEnvelope);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrMAPIMoveOneProp(
        (LPMAPIPROP)lpReport,
        PR_SUBJECT,
        PR_SUBJECT,
        FALSE,
        TRUE,
        (LPMAPIPROP)lpReportEnvelope);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrEDKSetReportMessageClass(
        ReportType,
        lpReport,
        lpReportEnvelope);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetPropBinary(
        (LPMAPIPROP)lpReportEnvelope,
        PR_MTS_SUBJECT_ID,
        cbSubjectMtsId,
        (LPVOID)lpSubjectMtsId);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetPropString(
        (LPMAPIPROP)lpReportEnvelope,
        PR_REPORT_DESTINATION_NAME,
        (LPVOID)lpszReportName);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetPropBinary(
        (LPMAPIPROP)lpReportEnvelope,
        PR_REPORT_DESTINATION_ENTRYID,
        cbReportEntryId,
        (LPVOID)lpReportEntryId);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetPropBoolean(
        (LPMAPIPROP)lpReportEnvelope,
        PR_DELETE_AFTER_SUBMIT,
        TRUE);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

// These strings are explicitly not localized.

static const char lpszReport[] = "REPORT.";
static const char lpszIPNRN[] = ".IPNRN";
static const char lpszIPNNRN[] = ".IPNNRN";
static const UINT  cchReportClass = sizeof(lpszReport) + sizeof(lpszIPNNRN);

static const enum
{
	IREPORT = 0, ICONVERSATION, ICONVERSATIONTOPIC, ICONVERSATIONIDX, ISEARCH,
	IMSGCLASS, ISUBJECT, ISUBJECTPREFX, ISUBJECTNORM, ISENDERNAME, ISENDEREID,
	ISENDADRTYPE, ISENDEMAIL, IREPORTNAME, IREPORTEID, IRECEIVENAME, IRECEIVEEID,
	IPRIORITY, IIMPORTANCE, ISENTREPNAME, ISENTREPEID, IRCVDREPNAME, IRCVDREPEID,
	IMSGDELTIME, ISUBMITTIME, IDISPTO, IDISPCC, IDISPBCC, ISENSITIVITY,
	INDRREQUEST, IDRREQUEST, IRNREQUEST, RRN_PROP_MAX
};

static const enum
{
	IRECIPTYPE = 0, IRECIPDISPNM, IRECIPEID, IRECIPADRTYPE, IRECIPEMAIL,
	RRN_RECIP_PROP_MAX
};


//$--HrReadReceipt--------------------------------------------------------------
//  Create a read/non-read notification report.
// -----------------------------------------------------------------------------
static HRESULT HrReadReceipt(           // RETURNS: return code
    IN ULONG ulFlags,                   // flags
	IN LPSTR lpszReportText,            // report text
	IN LPSTR lpszSubjectPrefix,         // subject prefix
    IN LPMESSAGE lpMessage,             // message
    OUT LPMESSAGE lpReadReceipt)        // report
{
	SCODE			sc					= S_OK;
	HRESULT			hr					= hrSuccess;
	ADRLIST			AdrList             = {0};
	BOOL			fSetError			= FALSE;
	BOOL			fSubjectOpenProperty= FALSE;
	CHAR			chNull				= 0;
	FILETIME 		ft                  = {0};
	LPSPropValue	lpOrigProps			= NULL;
	LPSPropValue	lpRecipVals			= NULL;
	LPSTR			lpszMessageClass	= NULL;
	LPSTR			lpszReadSubject		= NULL;
	LPSTR			lpszSubjOrig		= NULL;
	SPropValue 		rgMsgVals[ RRN_PROP_MAX ] = {0};
	SYSTEMTIME 		st                  = {0};
	UINT			iNumProp            = 0;
	ULONG			ulSize              = 0;
	ULONG			ulT                 = 0;
#ifdef DEBUG
	LPSPropProblemArray	lpProblem		= NULL;
#endif

	static SizedSPropTagArray(RRN_PROP_MAX, ptagaOrigMsg) =
	{
		RRN_PROP_MAX,
		{
			PR_REPORT_TAG,
			PR_CONVERSATION_KEY,
			PR_CONVERSATION_TOPIC_A,
			PR_CONVERSATION_INDEX,
			PR_SEARCH_KEY,				// must
			PR_MESSAGE_CLASS_A,			// must
			PR_SUBJECT_A,
			PR_SUBJECT_PREFIX_A,
			PR_NORMALIZED_SUBJECT_A,
			PR_SENDER_NAME_A,
			PR_SENDER_ENTRYID,			// must
			PR_SENDER_ADDRTYPE,
			PR_SENDER_EMAIL_ADDRESS,
			PR_REPORT_NAME_A,
			PR_REPORT_ENTRYID,
			PR_RECEIVED_BY_NAME_A,
			PR_RECEIVED_BY_ENTRYID,
			PR_PRIORITY,
			PR_IMPORTANCE,
			PR_SENT_REPRESENTING_NAME_A,
			PR_SENT_REPRESENTING_ENTRYID,
			PR_RCVD_REPRESENTING_NAME_A,
			PR_RCVD_REPRESENTING_ENTRYID,
			PR_MESSAGE_DELIVERY_TIME,	// must
			PR_CLIENT_SUBMIT_TIME,
			PR_DISPLAY_TO_A,
			PR_DISPLAY_CC_A,
			PR_DISPLAY_BCC_A,
			PR_SENSITIVITY,

			/*	Properties from here out are just place
			 *	holders for values we set into a message
			 *	regardless of the value in the original
			 *	message
			 */
			
			PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED,
			PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED,
			PR_READ_RECEIPT_REQUESTED
		}
	};

	static enum
	{
		outIREPORTTEXT = 0, outIMESSAGECLASS, outIREPORTTIME, outIORIGAUTHOREID,
		outIORIGDELIVERYTIME, outIPARENTKEY, outIDELETEAFTERSUBMIT,
		outCMAXIDX
	};

    hr = CHK_HrReadReceipt(
        ulFlags,
    	lpszReportText,
    	lpszSubjectPrefix,
        lpMessage,
        lpReadReceipt);

    if(FAILED(hr))
        RETURN(hr);

#ifdef DEBUG

	// Determine if we should fill out the out the empty message.

	hr = HrGetOneProp((LPMAPIPROP)lpMessage, PR_READ_RECEIPT_REQUESTED, &lpOrigProps);
	if (FAILED(hr) && hr != ResultFromScode(MAPI_E_NOT_FOUND))
	{
		MODULE_ERROR("HrReadReceipt: Failure to get prop");
		goto exit;
	}

	ASSERTERROR(!(GetScode(hr) == MAPI_E_NOT_FOUND || !lpOrigProps->Value.l),
			"PR_READ_RECEIPT_REQUESTED Flag not found");

	MAPIFreeBuffer(lpOrigProps);
	lpOrigProps = NULL;
#endif

	// get the props we need from the original message

	hr = lpMessage->lpVtbl->GetProps(lpMessage,
		(LPSPropTagArray)&ptagaOrigMsg, 0, // ansi
		&ulT, &lpOrigProps);
	if (FAILED(hr))
	{
		MODULE_ERROR("HrReadReceipt: Failure to get Original msg props");
		fSetError = TRUE;
		goto exit;
	}

    // if message delivery time is not found then add it

	if(lpOrigProps[IMSGDELTIME].ulPropTag != PR_MESSAGE_DELIVERY_TIME)
    {
    	GetSystemTime(&st);
    	SystemTimeToFileTime(&st, &ft);

    	lpOrigProps[IMSGDELTIME].ulPropTag = PR_MESSAGE_DELIVERY_TIME;
    	lpOrigProps[IMSGDELTIME].Value.ft  = ft;
    }

	// check to see if we have the "must" properties

	if (lpOrigProps[ISEARCH].ulPropTag 	!= PR_SEARCH_KEY
	  || lpOrigProps[IMSGCLASS].ulPropTag 	!= PR_MESSAGE_CLASS_A
	  || lpOrigProps[ISENDEREID].ulPropTag 	!= PR_SENDER_ENTRYID
	  || lpOrigProps[IMSGDELTIME].ulPropTag != PR_MESSAGE_DELIVERY_TIME)
	{
		hr = HR_LOG(ResultFromScode(MAPI_E_NOT_FOUND));
		MODULE_ERROR("HrReadReceipt: Required property(s) not found");
        goto exit;
	}

	// Get the original subject

	if (lpOrigProps[ISUBJECTNORM].ulPropTag == PR_NORMALIZED_SUBJECT_A)
		lpszSubjOrig = lpOrigProps[ISUBJECTNORM].Value.lpszA;
	else if (lpOrigProps[ISUBJECT].ulPropTag == PR_SUBJECT_A)
		lpszSubjOrig = lpOrigProps[ISUBJECT].Value.lpszA;
	else if (lpOrigProps[ISUBJECT].Value.err == MAPI_E_NOT_ENOUGH_MEMORY)
	{
		//	We've got a mondo subject.  Use OpenProperty...
		//
		LPSTREAM 		lpstreamSrc	= NULL;
		LPSTREAM 		lpstreamDst	= NULL;
		ULARGE_INTEGER	uliRead 	= { 0 };
		ULARGE_INTEGER	uliWritten 	= { 0 };
		ULARGE_INTEGER	uliSize;
		LARGE_INTEGER	liMove;
		ULONG			cbWritten	= 0;

		// open the source Stream

		hr = lpMessage->lpVtbl->OpenProperty(lpMessage, PR_SUBJECT_A,
				&IID_IStream, 0, 0, (LPUNKNOWN *)&lpstreamSrc);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: Failure calling OpenProperty on subject Src");
			fSetError = TRUE;
			goto openprop_cleanup;
		}

		// open the destination	Stream

		hr = lpReadReceipt->lpVtbl->OpenProperty(lpReadReceipt, PR_SUBJECT_A,
				&IID_IStream, 0, MAPI_CREATE | MAPI_MODIFY,
				(LPUNKNOWN *)&lpstreamDst);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: Failure calling OpenProperty on subject Dst");
			fSetError = TRUE;
			goto openprop_cleanup;
		}

		// Copy the Subject header to the destination

		hr = lpstreamDst->lpVtbl->Write(lpstreamDst, lpszSubjectPrefix,
				lstrlenA(lpszSubjectPrefix), &cbWritten);

		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: OLE IStream Write failed");
			goto openprop_cleanup;
		}

		ASSERTERROR((LONG)cbWritten == lstrlenA(lpszSubjectPrefix), "Write failed");

		// Tell OLE ISTREAM to copy all of it

		uliSize.HighPart = (ULONG) -1;
		uliSize.LowPart  = (ULONG) -1;

		hr = lpstreamSrc->lpVtbl->CopyTo(lpstreamSrc, lpstreamDst, uliSize,
				&uliRead, &uliWritten);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: OLE IStream CopyTo failed");
			goto openprop_cleanup;
		}

		ASSERTERROR(uliWritten.LowPart == uliRead.LowPart, "Write failed");

		hr = lpstreamDst->lpVtbl->Commit(lpstreamDst, 0);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: OLE IStream Commit failed");
			goto openprop_cleanup;
		}

		// Handle PR_ORIGINAL_SUBJECT

		UlRelease(lpstreamDst);
		lpstreamDst = NULL;

		hr = lpReadReceipt->lpVtbl->OpenProperty(lpReadReceipt,
				PR_ORIGINAL_SUBJECT_A,  &IID_IStream, 0,
				MAPI_CREATE | MAPI_MODIFY, (LPUNKNOWN *)&lpstreamDst);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: Failure calling OpenProperty on Orig Subject Dst");
			fSetError = TRUE;
			goto openprop_cleanup;
		}

		// rewind the source

		liMove.HighPart = 0;
		liMove.LowPart  = 0;

		hr = lpstreamSrc->lpVtbl->Seek(lpstreamSrc, liMove, STREAM_SEEK_SET, NULL);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: Failure calling Seek on subject Src stream");
			goto openprop_cleanup;
		}

		// Tell OLE ISTREAM to copy all of it

		uliSize.HighPart = (ULONG) -1;
		uliSize.LowPart  = (ULONG) -1;

		hr = lpstreamSrc->lpVtbl->CopyTo(lpstreamSrc, lpstreamDst, uliSize,
				&uliRead, &uliWritten);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: OLE IStream CopyTo failed");
			goto openprop_cleanup;
		}

		ASSERTERROR(uliWritten.LowPart == uliRead.LowPart, "Write failed");

		hr = lpstreamDst->lpVtbl->Commit(lpstreamDst, 0);
		if (FAILED(hr))
		{
			MODULE_ERROR("HrReadReceipt: OLE IStream Commit failed");
			goto openprop_cleanup;
		}

		fSubjectOpenProperty = TRUE;

openprop_cleanup:

		UlRelease(lpstreamSrc);
		UlRelease(lpstreamDst);

		if (FAILED(hr))
		{
			goto exit;
		}
	}
	else
		lpszSubjOrig = &chNull;

	if (!fSubjectOpenProperty)
	{
		ulSize = lstrlenA (lpszSubjOrig) + lstrlenA (lpszSubjectPrefix) + 1;
		sc = MAPIAllocateBuffer(ulSize, (LPVOID *) &lpszReadSubject);
		if (FAILED(sc))
		{
			hr = HR_LOG(ResultFromScode(sc));
			MODULE_ERROR("HrReadReceipt: OOM");
			goto exit;
		}

		wsprintfA (lpszReadSubject,
			"%s%s",
			lpszSubjectPrefix,
			lpszSubjOrig);
	}

	// Generate the Report Message Class from the existing message class

	ASSERTERROR(
	    lpOrigProps[IMSGCLASS].ulPropTag == PR_MESSAGE_CLASS_A,
	    "Message class is missing");

	ulSize = cchReportClass + lstrlenA(lpOrigProps[IMSGCLASS].Value.lpszA) + 1;
	sc = MAPIAllocateBuffer(ulSize, (LPVOID *)&lpszMessageClass);
	if (FAILED(sc))
	{
		hr = HR_LOG(ResultFromScode(sc));
		MODULE_ERROR("HrReadReceipt: OOM for RRN report message class");
        goto exit;
	}

	wsprintfA(lpszMessageClass,
		"%s%s%s",
		lpszReport,
		lpOrigProps[IMSGCLASS].Value.lpszA,
		(ulFlags & MAPI_NON_READ) ? (LPSTR) lpszIPNNRN : (LPSTR) lpszIPNRN);

	//
	// Setup the "must" prop vals
	//

	rgMsgVals[outIREPORTTEXT].ulPropTag  		= PR_REPORT_TEXT_A;
	rgMsgVals[outIREPORTTEXT].Value.lpszA 		= lpszReportText;

	rgMsgVals[outIMESSAGECLASS].ulPropTag 		= PR_MESSAGE_CLASS_A;
	rgMsgVals[outIMESSAGECLASS].Value.lpszA		= lpszMessageClass;

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);

	rgMsgVals[outIREPORTTIME].ulPropTag			= PR_REPORT_TIME;
	rgMsgVals[outIREPORTTIME].Value.ft			= ft;

	// PR_ORIGINAL_AUTHOR_?? is set from PR_SENDER_??

	rgMsgVals[outIORIGAUTHOREID].ulPropTag 		= PR_ORIGINAL_AUTHOR_ENTRYID;
	rgMsgVals[outIORIGAUTHOREID].Value.bin		= lpOrigProps[ISENDEREID].Value.bin;

	rgMsgVals[outIORIGDELIVERYTIME].ulPropTag  	= PR_ORIGINAL_DELIVERY_TIME;
	rgMsgVals[outIORIGDELIVERYTIME].Value.ft 	= lpOrigProps[IMSGDELTIME].Value.ft;

	// Set PR_PARENT_KEY with PR_MESSAGE_KEY of the original message.

	rgMsgVals[outIPARENTKEY].ulPropTag 			= PR_PARENT_KEY;
	rgMsgVals[outIPARENTKEY].Value.bin			= lpOrigProps[ISEARCH].Value.bin;

	rgMsgVals[outIDELETEAFTERSUBMIT].ulPropTag 	= PR_DELETE_AFTER_SUBMIT;
	rgMsgVals[outIDELETEAFTERSUBMIT].Value.b 	= TRUE;

	iNumProp = outCMAXIDX;

	//
	// Setup the variable Prop Vals
	//

	if (lpOrigProps[ISENDERNAME].ulPropTag == PR_SENDER_NAME_A)
	{
		rgMsgVals[iNumProp].ulPropTag 	= PR_ORIGINAL_AUTHOR_NAME_A;
		rgMsgVals[iNumProp].Value.lpszA	= lpOrigProps[ISENDERNAME].Value.lpszA;
		iNumProp++;
	}

	// Check to see if we handled Subject props by OpenProperty...

	if (!fSubjectOpenProperty)
	{
		rgMsgVals[iNumProp].ulPropTag 	= PR_SUBJECT_A;
		rgMsgVals[iNumProp].Value.lpszA = lpszReadSubject;
		iNumProp++;

		if (lpOrigProps[ISUBJECT].ulPropTag == PR_SUBJECT_A)
		{
			rgMsgVals[iNumProp].ulPropTag	= PR_ORIGINAL_SUBJECT_A;
			rgMsgVals[iNumProp].Value.lpszA	= lpOrigProps[ISUBJECT].Value.lpszA;
			iNumProp++;
		}
		else
		{
			MODULE_ERROR("HrReadReceipt: PR_SUBJECT missing");
			rgMsgVals[iNumProp].ulPropTag	= PR_ORIGINAL_SUBJECT_A;
			rgMsgVals[iNumProp].Value.lpszA	= &chNull;
			iNumProp++;
		}
	}

	//	The ordering here is slightly important.  PR_SUBJECT
	//	needs to be either first or last to aid in EMS processing
	//
	rgMsgVals[iNumProp].ulPropTag = PR_SUBJECT_PREFIX_A;
	rgMsgVals[iNumProp].Value.lpszA = lpszSubjectPrefix;
	iNumProp++; 
	rgMsgVals[iNumProp].ulPropTag = PR_NORMALIZED_SUBJECT_A;
	rgMsgVals[iNumProp].Value.lpszA = lpszSubjOrig;
	iNumProp++; 

	// If PR_SENT_REPRESENTING_?? exists copy to PR_RCVD_REPRESENTING_??

	if (lpOrigProps[ISENTREPNAME].ulPropTag == PR_SENT_REPRESENTING_NAME_A)
	{
		rgMsgVals[iNumProp].ulPropTag 	= PR_RCVD_REPRESENTING_NAME_A;
		rgMsgVals[iNumProp].Value.lpszA	= lpOrigProps[ISENTREPNAME].Value.lpszA;
		iNumProp++;
	}

	if (lpOrigProps[ISENTREPEID].ulPropTag == PR_SENT_REPRESENTING_ENTRYID)
	{
		rgMsgVals[iNumProp].ulPropTag 	= PR_RCVD_REPRESENTING_ENTRYID;
		rgMsgVals[iNumProp].Value.bin	= lpOrigProps[ISENTREPEID].Value.bin;
		iNumProp++;
	}

	// If PR_RCVD_REPRESENTING_?? exists copy to PR_SENT_REPRESENTING_??

	if (lpOrigProps[IRCVDREPNAME].ulPropTag == PR_RCVD_REPRESENTING_NAME_A)
	{
		rgMsgVals[iNumProp].ulPropTag  	= PR_SENT_REPRESENTING_NAME_A;
		rgMsgVals[iNumProp].Value.lpszA	= lpOrigProps[IRCVDREPNAME].Value.lpszA;
		iNumProp++;
	}

	if (lpOrigProps[IRCVDREPEID].ulPropTag == PR_RCVD_REPRESENTING_ENTRYID)
	{
		rgMsgVals[iNumProp].ulPropTag  	= PR_SENT_REPRESENTING_ENTRYID;
		rgMsgVals[iNumProp].Value.bin	= lpOrigProps[IRCVDREPEID].Value.bin;
		iNumProp++;
	}

	if (lpOrigProps[ISUBMITTIME].ulPropTag == PR_CLIENT_SUBMIT_TIME)
	{
		rgMsgVals[iNumProp].ulPropTag  	= PR_ORIGINAL_SUBMIT_TIME;
		rgMsgVals[iNumProp].Value.ft   	= lpOrigProps[ISUBMITTIME].Value.ft;
		iNumProp++;
	}

	if (lpOrigProps[IDISPTO].ulPropTag == PR_DISPLAY_TO_A)
	{
		rgMsgVals[iNumProp].ulPropTag	= PR_ORIGINAL_DISPLAY_TO_A;
		rgMsgVals[iNumProp].Value.lpszA = lpOrigProps[IDISPTO].Value.lpszA;
		iNumProp++;
	}

	if (lpOrigProps[IDISPCC].ulPropTag == PR_DISPLAY_CC_A)
	{
		rgMsgVals[iNumProp].ulPropTag	= PR_ORIGINAL_DISPLAY_CC_A;
		rgMsgVals[iNumProp].Value.lpszA = lpOrigProps[IDISPCC].Value.lpszA;
		iNumProp++;
	}

	if (lpOrigProps[IDISPBCC].ulPropTag == PR_DISPLAY_BCC_A)
	{
		rgMsgVals[iNumProp].ulPropTag	= PR_ORIGINAL_DISPLAY_BCC_A;
		rgMsgVals[iNumProp].Value.lpszA = lpOrigProps[IDISPBCC].Value.lpszA;
		iNumProp++;
	}

	if (lpOrigProps[IPRIORITY].ulPropTag == PR_PRIORITY)
		rgMsgVals[iNumProp++] = lpOrigProps[IPRIORITY];

	if (lpOrigProps[IIMPORTANCE].ulPropTag == PR_IMPORTANCE)
		rgMsgVals[iNumProp++] = lpOrigProps[IIMPORTANCE];
		
	if (lpOrigProps[ISENSITIVITY].ulPropTag == PR_SENSITIVITY)
		rgMsgVals[iNumProp++] = lpOrigProps[ISENSITIVITY];
		
	if (lpOrigProps[ICONVERSATION].ulPropTag == PR_CONVERSATION_KEY)
		rgMsgVals[iNumProp++] = lpOrigProps[ICONVERSATION];
		
	if (lpOrigProps[ICONVERSATIONTOPIC].ulPropTag == PR_CONVERSATION_TOPIC_A)
		rgMsgVals[iNumProp++] = lpOrigProps[ICONVERSATIONTOPIC];
	
	if (lpOrigProps[ICONVERSATIONIDX].ulPropTag == PR_CONVERSATION_INDEX)
		rgMsgVals[iNumProp++] = lpOrigProps[ICONVERSATIONIDX];

	if (lpOrigProps[IREPORT].ulPropTag == PR_REPORT_TAG)
		rgMsgVals[iNumProp++] = lpOrigProps[IREPORT];

	//	Turn off any and all report requests
	//
	rgMsgVals[iNumProp].ulPropTag = PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED;
	rgMsgVals[iNumProp].Value.b = FALSE;
	iNumProp++;
	rgMsgVals[iNumProp].ulPropTag = PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
	rgMsgVals[iNumProp].Value.b = FALSE;
	iNumProp++;
	rgMsgVals[iNumProp].ulPropTag = PR_READ_RECEIPT_REQUESTED;
	rgMsgVals[iNumProp].Value.b = FALSE;
	iNumProp++;

	// Fill in recipient properties

    sc = MAPIAllocateBuffer(sizeof(SPropValue) * RRN_RECIP_PROP_MAX, (LPVOID *)&lpRecipVals);
	if (FAILED(sc))
	{
		hr = HR_LOG(ResultFromScode(sc));
		MODULE_ERROR("HrReadReceipt: OOM for recipient props");
        goto exit;
	}
	
	// If PR_REPORT_NAME & EID exists, use that as the MAPI_TO recipient
	// else use PR_SENDER_NAME & EID.

	lpRecipVals[IRECIPTYPE].ulPropTag 	= PR_RECIPIENT_TYPE;
	lpRecipVals[IRECIPTYPE].Value.l 		= MAPI_TO;

	lpRecipVals[IRECIPDISPNM].ulPropTag	= PR_DISPLAY_NAME_A;
	lpRecipVals[IRECIPEID].ulPropTag	= PR_ENTRYID;

	if (lpOrigProps[IREPORTNAME].ulPropTag == PR_REPORT_NAME_A
	  && lpOrigProps[IREPORTEID].ulPropTag == PR_REPORT_ENTRYID)
  	{
		lpRecipVals[IRECIPDISPNM].Value.lpszA	= lpOrigProps[IREPORTNAME].Value.lpszA;
		lpRecipVals[IRECIPEID].Value.bin		= lpOrigProps[IREPORTEID].Value.bin;
		lpRecipVals[IRECIPADRTYPE].ulPropTag	= PR_NULL;
		lpRecipVals[IRECIPEMAIL].ulPropTag		= PR_NULL;
	}
	else
	{
		lpRecipVals[IRECIPDISPNM].Value.lpszA	= lpOrigProps[ISENDERNAME].Value.lpszA;
		lpRecipVals[IRECIPEID].Value.bin		= lpOrigProps[ISENDEREID].Value.bin;

		lpRecipVals[IRECIPADRTYPE].ulPropTag	= PR_ADDRTYPE_A;
		lpRecipVals[IRECIPADRTYPE].Value.lpszA	= lpOrigProps[ISENDADRTYPE].Value.lpszA;

		lpRecipVals[IRECIPEMAIL].ulPropTag		= PR_EMAIL_ADDRESS_A;
		lpRecipVals[IRECIPEMAIL].Value.lpszA	= lpOrigProps[ISENDEMAIL].Value.lpszA;
	}

	AdrList.cEntries = 1;
	AdrList.aEntries[0].cValues = RRN_RECIP_PROP_MAX;
	AdrList.aEntries[0].rgPropVals = lpRecipVals;

	// SetProps and ModifyRecips.

#ifdef DEBUG
	hr = lpReadReceipt->lpVtbl->SetProps(lpReadReceipt,
			(ULONG)iNumProp, rgMsgVals, &lpProblem);
#else
	hr = lpReadReceipt->lpVtbl->SetProps(lpReadReceipt,
			(ULONG)iNumProp, rgMsgVals, NULL);
#endif
	if (FAILED(hr))
	{
		MODULE_ERROR("HrReadReceipt: Failure setting a slew of props");
		fSetError = TRUE;
		goto exit;
	}

#ifdef DEBUG
	if (lpProblem)
	{
		MAPIFreeBuffer(lpProblem);
	}
#endif

	hr = lpReadReceipt->lpVtbl->ModifyRecipients(
			lpReadReceipt, 0, &AdrList);
	if (FAILED(hr))
	{
		MODULE_ERROR("HrReadReceipt: Failure modifying recipients");
		fSetError = TRUE;
		goto exit;
	}

exit:
	MAPIFreeBuffer(lpOrigProps);
	MAPIFreeBuffer(lpszMessageClass);
	MAPIFreeBuffer(lpszReadSubject);
	MAPIFreeBuffer(AdrList.aEntries[0].rgPropVals);

	return(hr);
}

//$--HrEDKCreateReadReceipt-----------------------------------------------------
//  Create a RN/NRN report.
// -----------------------------------------------------------------------------
static HRESULT HrEDKCreateReadReceipt(      // RETURNS: return code
    IN ULONG ulFlags,                       // flags
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpMessage,                 // pointer to message
    IN LPTSTR lpszSubjectPrefix,            // pointer to subject prefix
    IN LPTSTR lpszReportText,               // pointer to report text
    OUT LPMESSAGE *lppReportEnvelope,       // pointer to report envelope
    OUT LPMESSAGE *lppReport)               // pointer to report
{
    HRESULT      hr                = NOERROR;
    LPTSTR       lpszMessageClass  = NULL;
    LPMESSAGE    lpReportEnvelope  = NULL;
    ULONG        ulAttachmentNum   = 0;
    LPATTACH     lpAttach          = NULL;
    LPMESSAGE    lpReport          = NULL;
    HRESULT      hrT               = 0;
    ULONG        cValues           = 0;
    LPSPropValue lpProps           = NULL;
    LPSPropValue lpPropT           = NULL;

    ULONG        cNewProps         = 0;
    LPSPropValue lpNewProps        = NULL;

    LPMAPITABLE  lpTable           = NULL;
    LPADRLIST    lpAdrList         = NULL;

    LPADRLIST    lpEnvelopeAdrList = NULL;

    ULONG        i                 = 0;
    ULONG        iRecip            = 0;

    SPropValue   RecipNumProp[1]   = {0};
    SPropValue   rgProps[1]        = {0};

	SYSTEMTIME   st                = {0};
	FILETIME     ft                = {0};

    SizedSPropTagArray(6,rgReportTags) =
    {
        6,
        {
            PR_SENT_REPRESENTING_NAME,
            PR_SENT_REPRESENTING_ENTRYID,
            PR_MESSAGE_CLASS,
            PR_SUBJECT,
            PR_PRIORITY,
            PR_DELETE_AFTER_SUBMIT
        }
    };

    DEBUGPRIVATE("HrEDKCreateReadReceipt()\n");

    hr = CHK_HrEDKCreateReadReceipt(
        ulFlags,
        lpFolder,
        lpMessage,
        lpszSubjectPrefix,
        lpszReportText,
        lppReportEnvelope,
        lppReport);

    if(FAILED(hr))
        RETURN(hr);

    if(ulFlags == MAPI_NON_READ)
    {
        hr = HrMAPISetPropBoolean(
            (LPMAPIPROP)lpMessage,
            PR_NON_RECEIPT_NOTIFICATION_REQUESTED,
            TRUE);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }
    else
    {
        hr = HrMAPISetPropBoolean(
            (LPMAPIPROP)lpMessage,
            PR_READ_RECEIPT_REQUESTED,
            TRUE);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    *lppReportEnvelope = NULL;
    *lppReport = NULL;

    //
    // Create a message
    //

    hr = MAPICALL(lpFolder)->CreateMessage(
        lpFolder,
        NULL,
        (ULONG)0,
        &lpReportEnvelope);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Create an embedded message
    //

    hr = MAPICALL(lpReportEnvelope)->CreateAttach(
        lpReportEnvelope,
        NULL,
        (ULONG)0,
        &ulAttachmentNum,
        &lpAttach);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
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
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = MAPICALL(lpAttach)->OpenProperty(
        lpAttach,
        PR_ATTACH_DATA_OBJ,
        (LPIID)&IID_IMessage,
        0,
        MAPI_CREATE|MAPI_MODIFY,
        (LPUNKNOWN *)&lpReport);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //--------------------------------------------------------------------------

    hrT = HrReadReceipt(
        ulFlags,
	    lpszReportText,
	    lpszSubjectPrefix,
        lpMessage,
        lpReport);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);

	rgProps[0].ulPropTag    = PR_CLIENT_SUBMIT_TIME;
	rgProps[0].Value.ft     = ft;

    hrT = MAPICALL(lpReport)->SetProps(
        lpReport,
        1,
        rgProps,
        NULL);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpReport)->GetProps(
        lpReport,
        (SPropTagArray *)&rgReportTags,
        fMapiUnicode,
        &cValues,
        &lpProps);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	if((lpProps[0].ulPropTag != PR_SENT_REPRESENTING_NAME) ||
	   (lpProps[1].ulPropTag != PR_SENT_REPRESENTING_ENTRYID) ||
	   (lpProps[2].ulPropTag != PR_MESSAGE_CLASS))
	{
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

    lpProps[0].ulPropTag  = PR_ORIGINATOR_NAME;
    lpProps[1].ulPropTag  = PR_ORIGINATOR_ENTRYID;

    hr = HrEDKEnvelopeMessageClass(
        lpProps[2].Value.LPSZ,
        &lpszMessageClass);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lpProps[2].Value.LPSZ = lpszMessageClass;

    hrT = MAPICALL(lpReportEnvelope)->SetProps(
        lpReportEnvelope,
        6,
        lpProps,
        NULL);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Create recipient table for report envelope.
    //

    // -------------------------------------------------------------------------

    //
	// Get the current recipient table from the report.
    //

	hrT = MAPICALL(lpReport)->GetRecipientTable(lpReport, 0, &lpTable);

	if(FAILED(hrT))
	{
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

	//
	// Query all the rows.
	//

	hrT = HrQueryAllRows(
	    lpTable,
		NULL,
		NULL,
		NULL,
		0,
		&(LPSRowSet)lpAdrList);

	if(FAILED(hrT))
	{
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

    hr = HrMAPICreateSizedAddressList(
        lpAdrList->cEntries,
        &lpEnvelopeAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0, iRecip = 0; i < lpAdrList->cEntries; i++)
    {
        RecipNumProp[0].ulPropTag = PR_RECIPIENT_NUMBER;
        RecipNumProp[0].Value.ul  = iRecip+1;

        cNewProps  = 0;
        lpNewProps = NULL;

        hr = HrMAPIAppendSPropValues(
            lpAdrList->aEntries[i].cValues,
            lpAdrList->aEntries[i].rgPropVals,
            1,
            RecipNumProp,
            &cNewProps,
            &lpNewProps);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrMAPISetAddressList(
            iRecip,
            cNewProps,
            lpNewProps,
            lpEnvelopeAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        MAPIFREEBUFFER(lpNewProps);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        iRecip++;
    }

    lpEnvelopeAdrList->cEntries = iRecip;

    if(iRecip == 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpReportEnvelope)->ModifyRecipients(
        lpReportEnvelope,
        0,
        lpEnvelopeAdrList);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // -------------------------------------------------------------------------

    hrT = MAPICALL(lpReport)->SaveChanges(lpReport, KEEP_OPEN_READWRITE);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hrT = MAPICALL(lpAttach)->SaveChanges(lpAttach, KEEP_OPEN_READWRITE);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Save changes to the report envelope
    hrT = MAPICALL(lpReportEnvelope)->SaveChanges(lpReportEnvelope, KEEP_OPEN_READWRITE);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    *lppReportEnvelope = lpReportEnvelope;
    *lppReport = lpReport;

cleanup:

    MAPIFREEBUFFER(lpNewProps);

    ULRELEASE(lpTable);

    FREEPADRLIST(lpAdrList);

    FREEPADRLIST(lpEnvelopeAdrList);

    MAPIFREEBUFFER(lpszMessageClass);

    ULRELEASE(lpAttach);

    RETURN(hr);
}

//$--HrEDKCreateReadNotificationReport------------------------------------------
//  Create a read notification report.
// -----------------------------------------------------------------------------
HRESULT HrEDKCreateReadNotificationReport(  // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpMessage,                 // pointer to message
    IN LPTSTR lpszReportText,               // pointer to report text
    OUT LPMESSAGE *lppReportEnvelope,       // pointer to report envelope
    OUT LPMESSAGE *lppReport)               // pointer to report
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrEDKCreateReadNotificationReport()\n");

    hr = CHK_HrEDKCreateReadNotificationReport(
        lpFolder,
        lpMessage,
        lpszReportText,
        lppReportEnvelope,
        lppReport);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrEDKCreateReadReceipt(
        0,
        lpFolder,
        lpMessage,
        TEXT("Read: "),
        lpszReportText,
        lppReportEnvelope,
        lppReport);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

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
    OUT LPMESSAGE *lppReport)                   // pointer to report
{
    HRESULT hr  = NOERROR;
    HRESULT hrT = 0;

    DEBUGPUBLIC("HrEDKCreateNonReadNotificationReport()\n");

    hr = CHK_HrEDKCreateNonReadNotificationReport(
        lpFolder,
        lpMessage,
        lpszReportText,
        ulNonReceiptReason,
        ulDiscardReason,
        lppReportEnvelope,
        lppReport);

    if(FAILED(hr))
        RETURN(hr);

    hr = HrEDKCreateReadReceipt(
        MAPI_NON_READ,
        lpFolder,
        lpMessage,
        TEXT("Unread: "),
        lpszReportText,
        lppReportEnvelope,
        lppReport);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetPropLong(
        (LPMAPIPROP)*lppReport,
        PR_DISCARD_REASON,
        ulDiscardReason);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetPropLong(
        (LPMAPIPROP)*lppReport,
        PR_NON_RECEIPT_REASON,
        ulNonReceiptReason);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Save changes to the report
    hrT = MAPICALL(*lppReport)->SaveChanges(*lppReport, KEEP_OPEN_READWRITE);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}
