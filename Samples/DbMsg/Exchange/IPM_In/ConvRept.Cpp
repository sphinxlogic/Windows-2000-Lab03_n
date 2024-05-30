// --convrept.cpp------------------------------------------------
//
// CIPMConvert source code for IPM reports.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// --------------------------------------------------------------

#include "edk.h"
#include "tagnames.h"
#include "msgemit.h"
#include "convcls.h"
#include "convrept.chk"

//$--CIPMConvert::HrParseReportSpecific------------------------------------------
//
// DESCRIPTION: Parses [non]delivery report-specific tag and data lines
//              and constructs RCPT TO recipient list from them
//
// INPUT:   none
//
// OUTPUT:  pnRecipients    --  number of [non]recipients
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_OUTOFMEMORY if memory problems
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseReportSpecific(
            OUT ULONG * pnRecipients)   // # of [non]recipients
{
    HRESULT hr  =   NOERROR;
    LPTSTR          lpTag           =   NULL;       // tag string
    LPTSTR          lpData          =   NULL;       // data string
    ULONG           cbRead          =   0;          // # bytes read
    LPSPropValue    lpsRecipProps   =   NULL;       // property value array pointer
    ULONG           nRecipProps     =   0;          // number of property values in array
    ULONG           cbEid           =   0;          // number of bytes in entry identifier
    LPENTRYID       lpEid           =   NULL;       // entry identifier
    ULONG           cbName          =   0;          // # bytes in email address
    DWORD           cbSize          =   0;          // sizeof of property value array
    LARGE_INTEGER   sRetreat        =   {0};        // # of bytes to back up
	LONGLONG		cbRetreat		=	0;			// # of bytes to back up

    // report RCPT TO recipient list property indices
    // These properties are common to both delivery reports
    // and non-delivery reports.
    const UINT      iEmailAddr      =   0;          // email address
    const UINT      iRecipType      =   1;          // recipient type
    const UINT      iName           =   2;          // display name
    const UINT      iEID            =   3;          // recipient entry identifier
    const UINT      iAddrType       =   4;          // address type
    const UINT      iRecipNumber    =   5;          // recipient number
    const UINT      iReportTime     =   6;          // time report was generated

    // NDR-specific non-recipient properties
    const UINT      iReportText     =   7;          // report text
    const UINT      iDiagCode       =   8;          // NDR diagnostic code
    const UINT      iReasonCode     =   9;          // NDR reason code

    // # of NDR non-recipient properties
    const ULONG     nNDRRecipProps  =   10;

    // DR-specific recipient properties
    const UINT      iDeliverTime    =   7;          // DR delivery time
        
    // # of DR recipient properties
    const ULONG     nDRRecipProps   =   8;

    DEBUGPRIVATE("CIPMConvert::HrParseReportSpecific()\n");
    
    // consistency checking
    ASSERTERROR(!FBadUnknown(m_lpStream), "Bad m_lpStream");
    ASSERTERROR((m_MsgType == mtNDR || m_MsgType == mtDR), 
                "Bad m_MsgType");
    ASSERTERROR(!FBadUnknown(m_lpAB), "Bad m_lpAB");
    ASSERTERROR(!IsBadStringPtr(m_lpszAddrType, INFINITE),
                "Bad lpszAddrType");

    // Check the input parameters.
    hr = CHK_CIPMConvert_HrParseReportSpecific(pnRecipients);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // initialize the output parameter
    *pnRecipients = 0;

    // Initialize number of recipient properties
    if ( m_MsgType == mtNDR )   // non-delivery report
    {
        nRecipProps = nNDRRecipProps;
    }

    else    // delivery report
    {
        nRecipProps = nDRRecipProps;
    }

    // Handle recipient data per [non]recipient.
    while ( TRUE )
    {
        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);
        MAPIFREEBUFFER(lpEid);

        MAPIFREEBUFFER(lpsRecipProps);

        // Parse the "Your message was not delivered to" tag and data
        // or the "Your message was successfully delivered to" tag and data
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        // Check for end of file condition
        if ( hr == EDK_E_END_OF_FILE )
        {
            // Have reached the end of the file,  This
            // is not an error.
            hr = NOERROR;

            break;
        }

        if ( FAILED(hr) )
        {
            // general failure
            goto cleanup;
        }

        // Check the tag read against the tag expected
        if ( ( (m_MsgType == mtNDR) && 
               (lstrcmp(lpTag, lpszTagNotSentTo) != 0) ) ||
             ( (m_MsgType == mtDR) && 
                  (lstrcmp(lpTag, lpszTagSentTo) != 0) ) )
        {
            // doing TNEF decoding, we have read ahead too far.
            // Back up to where we were before.
            if ( m_fTNEFEncode == TRUE )
            {
                cbRetreat = ((LONGLONG) (-1)) * cbRead;

				sRetreat.LowPart = LOWLONG(cbRetreat);
				sRetreat.HighPart = HILONG(cbRetreat);

                hr = m_lpStream->Seek(
                            sRetreat,   // negative offset
                            STREAM_SEEK_CUR,    // from current position
                            NULL);      // don't care

                if ( FAILED(hr) )
                {
                    hr = HR_LOG(E_FAIL);

                    goto cleanup;
                }

                // This is not an error.
                hr = HR_LOG(NOERROR);

                break;  // we are done

            }   // end if doing TNEF decoding

            else    // not doing TNEF decoding
            {
                // general error
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

        }   // end if tag is not what we expect

        // Allocate memory for this recipient's properties.
        // (Must do dynamic allocation, as IMessage::ModifyRecipients
        // may reallocate property array buffer.).
        cbSize = sizeof(SPropValue) * nRecipProps;      // sizeof property value array
        hr = MAPIAllocateBuffer(
                    cbSize,   // # bytes to allocate
                    (VOID **) &lpsRecipProps);                    // pointer to array pointer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_OUTOFMEMORY);

            goto cleanup;
        }

        // Initialize property value array
        ZeroMemory(
                    lpsRecipProps,      // buffer
                    cbSize);            // size of buffer
        
        // save data for this non-recipient in the RCPT TO recipient property array.

        // Allocate additional memory for the e-mail address.
        cbName = cbStrLen(lpData);
        hr = MAPIAllocateMore(
                    cbName,                                 // # additional bytes
                    lpsRecipProps,                          // original buffer
                    (VOID **) &(lpsRecipProps[iEmailAddr].Value.LPSZ));        // email address buffer

        if ( FAILED(hr) )
        {   
            hr = HR_LOG(E_OUTOFMEMORY);

            goto cleanup;
        }
        
        // Set up properties for this recipient.

        // Set up the e-mail address
        lpsRecipProps[iEmailAddr].ulPropTag = PR_EMAIL_ADDRESS;   // e-mail address
        lstrcpy(
                lpsRecipProps[iEmailAddr].Value.LPSZ,
                lpData);

        // Set up the recipient type
        lpsRecipProps[iRecipType].ulPropTag = PR_RECIPIENT_TYPE;  // recipient type
        lpsRecipProps[iRecipType].Value.l = MAPI_TO;

        // Allocate more memory for display name
        hr = MAPIAllocateMore(
                    cbName,                            
                    lpsRecipProps,
                    (VOID **) &(lpsRecipProps[iName].Value.LPSZ));     // display name buffer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_OUTOFMEMORY);

            goto cleanup;
        }

        lpsRecipProps[iName].ulPropTag = PR_DISPLAY_NAME;   // display name
        lstrcpy(
                lpsRecipProps[iName].Value.LPSZ,
                lpData);

        // Create an entry identifier for this "one off" address
        hr = m_lpAB->CreateOneOff(
                    lpData,         // PR_DISPLAY_NAME
                    (LPTSTR) m_lpszAddrType,   // PR_ADDRTYPE
                    lpData,         // PR_EMAIL_ADDRESS
                    0,              // flags
                    &cbEid,         // #bytes in entry ID
                    &lpEid);        // entry identifier

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Allocate more memory for entry identifier
        hr = MAPIAllocateMore(
                    cbEid,              // # bytes to add
                    lpsRecipProps,
                    (VOID **) &(lpsRecipProps[iEID].Value.bin.lpb));         // entry identifier buffer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_OUTOFMEMORY);

            goto cleanup;
        }

        lpsRecipProps[iEID].ulPropTag = PR_ENTRYID;        // entry identifier
        lpsRecipProps[iEID].Value.bin.cb = cbEid;
        CopyMemory(
               lpsRecipProps[iEID].Value.bin.lpb,   // destination buffer
               lpEid,                               // source buffer
               cbEid);                              // count bytes

        // Allocate more memory for address type
        hr = MAPIAllocateMore(
                    cbStrLen(m_lpszAddrType),   // # bytes to add
                    lpsRecipProps,
                    (VOID **) &(lpsRecipProps[iAddrType].Value.LPSZ));    // address type buffer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_OUTOFMEMORY);

            goto cleanup;
        }

        lpsRecipProps[iAddrType].ulPropTag = PR_ADDRTYPE;
        lstrcpy(
                lpsRecipProps[iAddrType].Value.LPSZ,
                m_lpszAddrType);

        lpsRecipProps[iRecipNumber].ulPropTag = PR_RECIPIENT_NUMBER;
        lpsRecipProps[iRecipNumber].Value.l = -1;

        // Allocate additional memory for the report time.
        hr = MAPIAllocateMore(
                    sizeof(FILETIME),  // # bytes to add
                    lpsRecipProps,
                    (VOID **) &(lpsRecipProps[iReportTime].Value.ft));    // address type buffer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_OUTOFMEMORY);

            goto cleanup;
        }

        // Report time
        lpsRecipProps[iReportTime].ulPropTag = PR_REPORT_TIME;

        // Determine and fill in the report time
        hr = HrParseDateTimeString(
                m_rgszData[iDate],        // date time string
                &(lpsRecipProps[iReportTime].Value.ft));   // file time pointer

        if ( FAILED(hr) )
        {
            // Use a default value.
            GetSystemTimeAsFileTime( &(lpsRecipProps[iReportTime].Value.ft));
        }

        // Free tag and data string
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Handle NDR-specific properties
        if ( m_MsgType == mtNDR )
        {
            // Parse "for the following reason" tag and data line.
            hr = HrParseTagAndData(
                        m_lpStream,     // stream pointer                        
                        &cbRead,        // # bytes read
                        &lpTag,         // tag pointer
                        &lpData);       // data pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Check the tag read against the one expected
            if ( lstrcmp(lpTag, lpszTagReason) != 0 )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            // Allocate more memory for the report text
            hr = MAPIAllocateMore(
                    cbStrLen(lpData),   // # bytes to add
                    lpsRecipProps,
                    (VOID **) &(lpsRecipProps[iReportText].Value.LPSZ));    // address type buffer

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_OUTOFMEMORY);

                goto cleanup;
            }

            lpsRecipProps[iReportText].ulPropTag = PR_REPORT_TEXT;
            lstrcpy(
                lpsRecipProps[iReportText].Value.LPSZ,  // buffer
                lpData);                                // value

            // Free tag and data strings
            MAPIFREEBUFFER(lpTag);
            MAPIFREEBUFFER(lpData);

            // Parse the "Diagnostic code" tag and data line
            hr = HrParseTagAndData(
                        m_lpStream,     // stream pointer                        
                        &cbRead,        // # bytes read
                        &lpTag,         // tag pointer
                        &lpData);       // data pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Check the tag read against the one expected
            if ( lstrcmp(lpTag, lpszTagDiagCode) != 0 )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            // save data in the RCPT TO recipient property array.
            lpsRecipProps[iDiagCode].ulPropTag = PR_NDR_DIAG_CODE;
            lpsRecipProps[iDiagCode].Value.l = atol(lpData);

            // Free tag and data strings
            MAPIFREEBUFFER(lpTag);
            MAPIFREEBUFFER(lpData);

            // Parse the "NDR code" tag and data line.
            hr = HrParseTagAndData(
                        m_lpStream,     // stream pointer                        
                        &cbRead,        // # bytes read
                        &lpTag,         // tag pointer
                        &lpData);       // data pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Check tag read against one expected
            if ( lstrcmp(lpTag, lpszTagNDRCode) != 0 )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            // save data in the RCPT TO recipient property array.
            lpsRecipProps[iReasonCode].ulPropTag = PR_NDR_REASON_CODE;
            lpsRecipProps[iReasonCode].Value.l = atol(lpData);

            // Free tag and data string
            MAPIFREEBUFFER(lpTag);
            MAPIFREEBUFFER(lpData);

        }   // end if have an NDR

        // Handle DR specific properties
        else    
        {
            // Read in the "at" tag and data
            hr = HrParseTagAndData(
                        m_lpStream,     // stream pointer                        
                        &cbRead,        // # bytes read
                        &lpTag,         // tag pointer
                        &lpData);       // data pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Check the tag read against the one expected
            if ( lstrcmp(lpTag, lpszTagAtTime) != 0 )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            // Allocate additional memory for the delivery time.
            hr = MAPIAllocateMore(
                    sizeof(FILETIME),  // # bytes to add
                    lpsRecipProps,
                    (VOID **) &(lpsRecipProps[iDeliverTime].Value.ft));

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_OUTOFMEMORY);

                goto cleanup;
            }

            // Determine and set the delivery time.
            lpsRecipProps[iDeliverTime].ulPropTag = PR_DELIVER_TIME;

            hr = HrParseDateTimeString(
                lpData,        // date time string
                &(lpsRecipProps[iDeliverTime].Value.ft));   // file time pointer

            if ( FAILED(hr) )
            {
                // Use a default value.
                GetSystemTimeAsFileTime( &(lpsRecipProps[iDeliverTime].Value.ft));
            }

            // Free tag and data string
            MAPIFREEBUFFER(lpTag);
            MAPIFREEBUFFER(lpData);

        }   // end if have a DR

        // Add the property array to the RCPT TO recipient list.
        if ( m_lpReportToList == NULL )
        {
            // Create the recipient list
            hr = HrMAPICreateAddressList(
                nRecipProps,        // # of properties for address
                lpsRecipProps,      // recipient properties
                &m_lpReportToList);  // target address list pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if recipient list doesn't exist

        else
        {
            // Append to the recipient list
            hr = HrMAPIAppendAddressList(
                nRecipProps,        // # of properties for address
                lpsRecipProps,      // recipient properties
                &m_lpReportToList);  // target address list pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if recipient list does exist

        // increment [non]recipient count
        (*pnRecipients)++;

        // Process next [non]recipient

    }   // end while

    // we are done.

cleanup:

    // Free MAPI buffers
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);
    MAPIFREEBUFFER(lpEid);

    // HrMAPICreateAddressList makes a duplicate of the
    // property value array passed into it.  Thus, free
    // property value array here.
    MAPIFREEBUFFER(lpsRecipProps);

    RETURN(hr);

}

//$--$CIPMConvert::HrSetReportProps-------------------------------------------
//
// DESCRIPTION: Sets delivery and non-delivery report properties.
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrSetReportProps()
{
    HRESULT             hr                  =   NOERROR;
    ULONG               ulImportance        =   0;      // importance value
    ULONG               ulPriority          =   0;      // priority value
    LPSPropProblemArray lpsProblems         =   NULL;   // problem array pointer
    ULONG               nReportProps        =   0;      // # of report properties
    ULONG               cbDestEid           =   0;      // # dest entry ID bytes
    LPENTRYID           lpDestEid           =   NULL;   // destination entry ID
    LPTSTR              lpszSubjectPrefix   =   NULL;   // subject prefix
    LPTSTR              lpszNormSubject     =   NULL;   // normalized subject
    SYSTEMTIME          st                  =   {0};    // current system time
    FILETIME            ftArrival           =   {0};    // arrival time
    FILETIME            ftSubmit            =   {0};    // submission time
    LPTSTR              lpDestAddr          =   NULL;   // destination address

    // property value array indices
    const UINT  iClassVal       =   0;
    const UINT  iImportanceVal  =   1;
    const UINT  iPriorityVal    =   2;
    const UINT  iSubjectVal     =   3;
    const UINT  iDestNameVal    =   4;
    const UINT  iDestEidVal     =   5;
    const UINT  iSubjectXIDVal  =   6;
    const UINT  iSubPrefixVal   =   7;
    const UINT  iNormSubjectVal =   8;
    const UINT  iDeleteVal      =   9;
    const UINT  iArrivalTimeVal =   10;
    const UINT  iOrigSubmitVal  =   11;
    const UINT  iReportReqVal   =   12;
	const UINT	iContentRetVal	=	13;

    // minimum number of report properties
    const ULONG nMinRptProps    =   14;

    // maximum # of report properties.
    // Note: There may not be any trace information or any X message
    // identifier information.  Thus, the maximum number of 
    // properties is three more than the minimum number of properties.
    const ULONG nMaxRptProps    =   nMinRptProps + 3;

    // Property value array
    SPropValue  rgReportProps[nMaxRptProps] =   {0};

    // index of email address in the envelope recipient address
    // list property value array.
    const UINT      iEmailAddr  =   0;          // email address

    DEBUGPRIVATE("CIPMConvert::HrSetReportProps()\n");

    // consistency checking
    ASSERTERROR(!FBadUnknown(m_lpEnvelope), "Bad m_lpEnvelope");
    ASSERTERROR((m_MsgType == mtNDR || m_MsgType == mtDR), 
                "Bad m_MsgType");
    ASSERTERROR((!IsBadReadPtr(m_lpRcptToList, sizeof(ADRLIST))), 
                "Bad m_lpRcptToList");

    // Initialize number of report properties to be the minimum
    // number of report properties.
    nReportProps = nMinRptProps;

    // Fill in the properties to be set.
    rgReportProps[iClassVal].ulPropTag = PR_MESSAGE_CLASS;
    rgReportProps[iClassVal].Value.LPSZ = m_rgszData[iClass];

    // Retrieve importance value.
    hr = HrParseImportanceString(
                m_rgszData[iImportance],    // importance string
                &ulImportance);             // importance value
    
    if ( FAILED(hr) )
    {
        goto cleanup;
    }
        
    rgReportProps[iImportanceVal].ulPropTag = PR_IMPORTANCE;
    rgReportProps[iImportanceVal].Value.l = ulImportance;

    // Retrieve priority value
    hr = HrParsePriorityString(
                m_rgszData[iPriority],      // priority string
                &ulPriority);               // priority value

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgReportProps[iPriorityVal].ulPropTag = PR_PRIORITY;
    rgReportProps[iPriorityVal].Value.l = ulPriority;

    rgReportProps[iSubjectVal].ulPropTag = PR_SUBJECT;
    rgReportProps[iSubjectVal].Value.LPSZ = m_rgszData[iSubject];

    // Retrieve the report destination name.
    // The report destination name is actually in the 
    // "RCPT TO" line, which was stored in the m_lpRcptToList.
    lpDestAddr = m_lpRcptToList->aEntries[0].rgPropVals[iEmailAddr].Value.LPSZ;
    rgReportProps[iDestNameVal].ulPropTag = PR_REPORT_DESTINATION_NAME;
    rgReportProps[iDestNameVal].Value.LPSZ = lpDestAddr;

    // Create an entry identifier for this "one off" address
    hr = m_lpAB->CreateOneOff(
                    lpDestAddr,     // name
                    (LPTSTR) m_lpszAddrType,    // address type
                    lpDestAddr,     // address
                    0,              // flags
                    &cbDestEid,     // #bytes in entry ID
                    &lpDestEid);    // entry identifier

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    rgReportProps[iDestEidVal].ulPropTag = PR_REPORT_DESTINATION_ENTRYID;
    rgReportProps[iDestEidVal].Value.bin.cb = cbDestEid;
    rgReportProps[iDestEidVal].Value.bin.lpb = (BYTE *) lpDestEid;

    rgReportProps[iSubjectXIDVal].ulPropTag = PR_MTS_SUBJECT_ID;
    rgReportProps[iSubjectXIDVal].Value.bin.cb = 
        cbStrLen(m_rgszData[iSubjectXID]);
    rgReportProps[iSubjectXIDVal].Value.bin.lpb = 
        (BYTE *) m_rgszData[iSubjectXID];

    // Contruct subject prefix & normalized subject
    // (Prefix is everything up to and including first colon.
    // Normalized subject is everything else, except first space).
    hr = HrEDKParseSubjectPrefix(
                m_rgszData[iSubject],   // subject text
                &lpszSubjectPrefix,     // prefix
                &lpszNormSubject);      // normalized subject

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgReportProps[iSubPrefixVal].ulPropTag = PR_SUBJECT_PREFIX;
    rgReportProps[iSubPrefixVal].Value.LPSZ = lpszSubjectPrefix;

    rgReportProps[iNormSubjectVal].ulPropTag = PR_NORMALIZED_SUBJECT;
    rgReportProps[iNormSubjectVal].Value.LPSZ = lpszNormSubject;

    rgReportProps[iDeleteVal].ulPropTag = PR_DELETE_AFTER_SUBMIT;
    rgReportProps[iDeleteVal].Value.b = TRUE;

    // Determine the arrival time.  This is the current time!
    GetSystemTimeAsFileTime( &ftArrival);

    rgReportProps[iArrivalTimeVal].ulPropTag = PR_ARRIVAL_TIME;
    rgReportProps[iArrivalTimeVal].Value.ft = ftArrival;

    // Determine the original submission time.
    hr = HrParseDateTimeString(
                m_rgszData[iDate],      // date time string
                &ftSubmit);             // file time structure

    if ( FAILED(hr) )
    {
        // Use a default value.
        GetSystemTimeAsFileTime( &ftSubmit);
    }

    rgReportProps[iOrigSubmitVal].ulPropTag = PR_CLIENT_SUBMIT_TIME;
    rgReportProps[iOrigSubmitVal].Value.ft = ftSubmit;

    // Set the appropriate report requested property
    if ( m_MsgType == mtNDR )   // non-delivery report
    {
        rgReportProps[iReportReqVal].ulPropTag =
            PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED;
    }

    else    // delivery report
    {
        rgReportProps[iReportReqVal].ulPropTag =
            PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
    }

    rgReportProps[iReportReqVal].Value.b = TRUE;

	// Set the content return requested flag.  In general, we should
	// try to propagate the original message content with all delivery
	// and non-delivery reports.
	rgReportProps[iContentRetVal].ulPropTag = PR_CONTENT_RETURN_REQUESTED;
	// Evaluates to TRUE if TNEFed content data is available and FALSE otherwise.
	rgReportProps[iContentRetVal].Value.b = m_fTNEFEncode;	

    // Only fill in PR_MESSAGE_SUBMISSION_ID if it is not null.
    if ( *(m_rgszData[iXID]) != 0 )
    {
        // Fill in X-Message-ID
        rgReportProps[nReportProps].ulPropTag = PR_MESSAGE_SUBMISSION_ID;
        rgReportProps[nReportProps].Value.bin.cb = 
            cbStrLen(m_rgszData[iXID]);
        rgReportProps[nReportProps].Value.bin.lpb = (BYTE *) m_rgszData[iXID];

        // increment number of properties
        nReportProps++;
    }

    // Set the trace information, if any.
    if ( m_lpTraceInfo != NULL )
    {
        rgReportProps[nReportProps].ulPropTag = PR_TRACE_INFO;
        rgReportProps[nReportProps].Value.bin.cb = CbTRACEINFO(m_lpTraceInfo);
        rgReportProps[nReportProps].Value.bin.lpb = (BYTE *) m_lpTraceInfo;

        // increment the property count
        nReportProps++;

    }   // end if trace information

    // Set the internal trace information, if any.
    if ( m_lpIntTraceInfo != NULL )
    {
        rgReportProps[nReportProps].ulPropTag = PR_INTERNAL_TRACE_INFO;
        rgReportProps[nReportProps].Value.bin.cb = CbINTTRACEINFO(m_lpIntTraceInfo);
        rgReportProps[nReportProps].Value.bin.lpb = (BYTE *) m_lpIntTraceInfo;

        // increment the property count
        nReportProps++;

    }   // end if internal trace information

    // Set the PR_TRANSPORT_MESSAGE_HEADER property.
    hr = HrSetTransHdr();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Set the report properties.
    hr = m_lpEnvelope->SetProps(
                nReportProps,       // # of properties
                rgReportProps,      // property value array
                &lpsProblems);      // property problem array poniter

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        lpsProblems = NULL;     // so can safely release

        goto cleanup;
    }

    if ( lpsProblems != NULL )
    {
        // some properties weren't accepted
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Set properties on report's recipient table.
    hr = m_lpEnvelope->ModifyRecipients(
                0,                    // flags
                m_lpReportToList);    // address list        

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // we are done

cleanup:

    // Free MAPI buffers
    MAPIFREEBUFFER(lpDestEid);
    MAPIFREEBUFFER(lpszSubjectPrefix);
    MAPIFREEBUFFER(lpszNormSubject);
    MAPIFREEBUFFER(lpsProblems);

    RETURN(hr);

}

//$--CIPMConvert::HrParseNotificationSpecific------------------------------------------
//
// DESCRIPTION: Parses read/non read notification-specific tag and data lines.
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseNotificationSpecific()
{
    HRESULT hr  =   NOERROR;
    LPTSTR          lpTag           =   NULL;       // tag string
    ULONG           cbRead          =   0;          // # bytes read

    DEBUGPRIVATE("CIPMConvert::HrParseNotificaionSpecific()\n");

    // consistency checking
    ASSERTERROR(!FBadUnknown(m_lpStream), "Bad m_lpStream");
    ASSERTERROR((m_MsgType == mtNRN || m_MsgType == mtRN),
                "Bad m_MsgType");

    // Parse the "Your message was [not] read by" tag and data.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // # bytes read
                &lpTag,         // tag pointer
                &(m_rgszData[iReadBy]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check the tag read against the one expected.
    if ( (m_MsgType == mtNRN) &&
         (lstrcmp(lpTag, lpszTagNotReadBy) != 0) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    else if ( (m_MsgType == mtRN) &&
              (lstrcmp(lpTag, lpszTagReadBy) != 0) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Free tag string
    MAPIFREEBUFFER(lpTag);

    // Parse the "at" tag and data line.
    hr = HrParseTagAndData(
            m_lpStream,     // stream pointer
            &cbRead,        // #bytes read
            &lpTag,         // tag string
            &(m_rgszData[iNotifyTime]));    // data buffer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check tag read against tag expected.
    if ( lstrcmp(lpTag, lpszTagAtTime) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Free tag string
    MAPIFREEBUFFER(lpTag);

    // Handle non-read receipt-specific information.
    if ( m_MsgType == mtNRN )
    {
        // Parse "Discard Code" tag and data
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer
                    &cbRead,        // # bytes read
                    &lpTag,         // tag string
                    &(m_rgszData[iDiscardCode]));   // data buffer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag read against one expected.
        if ( lstrcmp(lpTag, lpszTagDiscCode) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // free tag string
        MAPIFREEBUFFER(lpTag);

        // Parse "Non-receipt code" tag and data
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer
                    &cbRead,        // # bytes read
                    &lpTag,         // tag string
                    &(m_rgszData[iNonRcptCode]));   // data buffer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag read against tag expected
        if ( lstrcmp(lpTag, lpszTagNRNCode) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Free tag string
        MAPIFREEBUFFER(lpTag);

    }   // end if NRN

    // we are done

cleanup:

    // Free MAPI buffers
    MAPIFREEBUFFER(lpTag);

    RETURN(hr);

}

//$--CIPMConvert::HrSetNotifyCntProps-----------------------------------------
//
// DESCRIPTION: Set content properties for read and non-read notifications
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrSetNotifyCntProps()
{
    HRESULT             hr                  =   NOERROR;
    LPSPropProblemArray lpsProblems         =   NULL;   // property problems
    FILETIME            ftSubmit            =   {0};    // submission time struct
    FILETIME            ftReport            =   {0};    // report time struct
    ULONG               ulImportance        =   0;      // importance value
    ULONG               ulPriority          =   0;      // priority value
    ULONG               nNotifyProps        =   0;      // # of properties
    ULONG               cbEid               =   0;      // # bytes in entry ID
    LPENTRYID           lpEid               =   NULL;   // entry identifier
    LPTSTR              lpszNormSubject     =   NULL;   // normalized subject
    LPTSTR              lpszSubjectPrefix   =   NULL;   // subject prefix
    LPTSTR              lpszFromAddr        =   NULL;   // from address
    ULONG               cbParentKey         =   0;      // # bytes in binary parent key

    // byte array for the binary parent key (PR_PARENT_KEY) property
    BYTE                rgbParentKey[ulMaxOutStringLen + 1] =   {0};

    // indices into the notification content's property value array
    const UINT  iClassVal       =   0;
    const UINT  iFromAddrVal    =   1;
    const UINT  iFromNameVal    =   2;
    const UINT  iFromEidVal     =   3;
    const UINT  iFromAddrTypeVal=   4;
    const UINT  iSubmitTimeVal  =   5;
    const UINT  iImportanceVal  =   6;
    const UINT  iPriorityVal    =   7;
    const UINT  iSubjectVal     =   8;
    const UINT  iReportTimeVal  =   9;
    const UINT  iSubPrefixVal   =   10;
    const UINT  iNormSubjectVal =   11;
    const UINT  iOrigSubjectVal =   12;
    const UINT  iOrigSubmitVal  =   13;
    const UINT  iOrigDestNamVal =   14;
    const UINT  iOrigDestEidVal =   15;
    const UINT  iOrigDestAddrVal=   16;
    const UINT  iOrigDestATypVal=   17;
    const UINT  iSubjectXIDVal  =   18;
    const UINT  iFromAddrVal2   =   19;
    const UINT  iFromNameVal2   =   20;
    const UINT  iFromEidVal2    =   21;
    const UINT  iFromAddrTypeVal2=  22;

    // Properties unique to non-read notifications
    const UINT  iDiscardCodeVal =   23;
    const UINT  iNonRcptCodeVal =   24;

    // The X-Message-Subject-ID property is not always
    // present for read and non-read notifications.
    // It's index will have to be computed.

    // number of read notification content properties
    const ULONG nRNNotifyProps  =   23;

    // number of non-read notification content properties
    const ULONG nNRNNotifyProps =   25;

    // Property value array
    SPropValue  rgNotifyProps[nNRNNotifyProps]  =   {0};
    
    DEBUGPRIVATE("CIPMConvert::HrSetNotifyCntProps()\n");

    // consistency checking
    ASSERTERROR((m_MsgType == mtNRN || m_MsgType == mtRN),
                "Bad m_MsgType");

    // If we are doing TNEF decoding, let TNEF
    // extract the content properties.
    if ( m_fTNEFEncode == TRUE )
    {
        goto cleanup;
    }

    // Initialize number of properties
    if ( m_MsgType == mtNRN )
    {
        // non-read notification
        nNotifyProps = nNRNNotifyProps;
    }

    else
    {
        // read notification
        nNotifyProps = nRNNotifyProps;
    }

    // Set up notification content properties
    rgNotifyProps[iClassVal].ulPropTag = PR_MESSAGE_CLASS;
    rgNotifyProps[iClassVal].Value.LPSZ = m_rgszData[iClass];

	// PR_SENDER_* and PR_SENT_REPRESENTING_* properties
    lpszFromAddr = m_rgszData[iFrom];
    rgNotifyProps[iFromAddrVal].ulPropTag = PR_SENDER_EMAIL_ADDRESS;
    rgNotifyProps[iFromAddrVal].Value.LPSZ = lpszFromAddr;

    rgNotifyProps[iFromNameVal].ulPropTag = PR_SENDER_NAME;
    rgNotifyProps[iFromNameVal].Value.LPSZ = lpszFromAddr;

    // Create an entry identifier for this "one off" address
    hr = m_lpAB->CreateOneOff(
                    lpszFromAddr,   // name
                    (LPTSTR) m_lpszAddrType,    // address type
                    lpszFromAddr,   // address
                    0,              // flags
                    &cbEid,         // #bytes in entry ID
                    &lpEid);        // entry identifier

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    rgNotifyProps[iFromEidVal].ulPropTag = PR_SENDER_ENTRYID;
    rgNotifyProps[iFromEidVal].Value.bin.cb = cbEid;
    rgNotifyProps[iFromEidVal].Value.bin.lpb = (BYTE *) lpEid;

    rgNotifyProps[iFromAddrTypeVal].ulPropTag = PR_SENDER_ADDRTYPE;
    rgNotifyProps[iFromAddrTypeVal].Value.LPSZ = (LPTSTR) m_lpszAddrType;

    rgNotifyProps[iFromAddrVal2].ulPropTag = PR_SENT_REPRESENTING_EMAIL_ADDRESS;
    rgNotifyProps[iFromAddrVal2].Value.LPSZ = lpszFromAddr;

    rgNotifyProps[iFromNameVal2].ulPropTag = PR_SENT_REPRESENTING_NAME;
    rgNotifyProps[iFromNameVal2].Value.LPSZ = lpszFromAddr;

    rgNotifyProps[iFromEidVal2].ulPropTag = PR_SENT_REPRESENTING_ENTRYID;
    rgNotifyProps[iFromEidVal2].Value.bin.cb = cbEid;
    rgNotifyProps[iFromEidVal2].Value.bin.lpb = (BYTE *) lpEid;

    rgNotifyProps[iFromAddrTypeVal2].ulPropTag = PR_SENT_REPRESENTING_ADDRTYPE;
    rgNotifyProps[iFromAddrTypeVal2].Value.LPSZ = (LPTSTR) m_lpszAddrType;

    // Parse client submit time.
    hr = HrParseDateTimeString(
                m_rgszData[iDate],      // date time string
                &ftSubmit);             // file time structure

    if ( FAILED(hr) )
    {
        // Use a default value.
        GetSystemTimeAsFileTime( &ftSubmit);
    }

    rgNotifyProps[iSubmitTimeVal].ulPropTag = 
        PR_CLIENT_SUBMIT_TIME;
    rgNotifyProps[iSubmitTimeVal].Value.ft = ftSubmit;

    // Determine importance value.
    hr = HrParseImportanceString(
                m_rgszData[iImportance],    // importance string
                &ulImportance);             // importance value

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgNotifyProps[iImportanceVal].ulPropTag = PR_IMPORTANCE;
    rgNotifyProps[iImportanceVal].Value.l = ulImportance;

    // Determine priority value.
    hr = HrParsePriorityString(
                m_rgszData[iPriority],  // priority string
                &ulPriority);           // priority value

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgNotifyProps[iPriorityVal].ulPropTag = PR_PRIORITY;
    rgNotifyProps[iPriorityVal].Value.l = ulPriority;

    rgNotifyProps[iSubjectVal].ulPropTag = PR_SUBJECT;
    rgNotifyProps[iSubjectVal].Value.LPSZ = m_rgszData[iSubject];

    // Parse report time.
    hr = HrParseDateTimeString(
                m_rgszData[iNotifyTime],    // date time string
                &ftReport);                 // file time structure

    if ( FAILED(hr) )
    {
        // Use a default value.
        GetSystemTimeAsFileTime( &ftReport);
    }

    rgNotifyProps[iReportTimeVal].ulPropTag = PR_REPORT_TIME;
    rgNotifyProps[iReportTimeVal].Value.ft = ftReport;

    // Construct subject prefix
    // The subject prefix is everything up until the first colon
    // of the subject (and the next space, if any).  The normalized
    // subject is everything else.
    hr = HrEDKParseSubjectPrefix(
                m_rgszData[iSubject],   // subject text
                &lpszSubjectPrefix,     // prefix
                &lpszNormSubject);      // normalized subject

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgNotifyProps[iSubPrefixVal].ulPropTag = PR_SUBJECT_PREFIX;
    rgNotifyProps[iSubPrefixVal].Value.LPSZ = lpszSubjectPrefix;

    rgNotifyProps[iNormSubjectVal].ulPropTag = PR_NORMALIZED_SUBJECT;
    rgNotifyProps[iNormSubjectVal].Value.LPSZ = lpszNormSubject;

    // Must set original subject after have computed normalized
    // subject.
    rgNotifyProps[iOrigSubjectVal].ulPropTag = PR_ORIGINAL_SUBJECT;
    rgNotifyProps[iOrigSubjectVal].Value.LPSZ = lpszNormSubject;
    
    rgNotifyProps[iOrigSubmitVal].ulPropTag = PR_ORIGINAL_SUBMIT_TIME;
    rgNotifyProps[iOrigSubmitVal].Value.ft = ftSubmit;

    // Note:  PR_ORIGINALLY_INTENDED_RECIPIENT_NAME is an
    // entry identifier, NOT a string!
    // Must be filled in after original destination EID is determined
    rgNotifyProps[iOrigDestNamVal].ulPropTag = 
            PR_ORIGINALLY_INTENDED_RECIPIENT_NAME;
    rgNotifyProps[iOrigDestNamVal].Value.bin.cb = cbEid;
    rgNotifyProps[iOrigDestNamVal].Value.bin.lpb = (BYTE *) lpEid;

    rgNotifyProps[iOrigDestEidVal].ulPropTag = 
            PR_ORIGINALLY_INTENDED_RECIP_ENTRYID;
    rgNotifyProps[iOrigDestEidVal].Value.bin.cb = cbEid;
    rgNotifyProps[iOrigDestEidVal].Value.bin.lpb = (BYTE *) lpEid;

    rgNotifyProps[iOrigDestAddrVal].ulPropTag = 
            PR_ORIGINALLY_INTENDED_RECIP_EMAIL_ADDRESS;
    rgNotifyProps[iOrigDestAddrVal].Value.LPSZ = lpszFromAddr;

    rgNotifyProps[iOrigDestATypVal].ulPropTag =
            PR_ORIGINALLY_INTENDED_RECIP_ADDRTYPE;
    rgNotifyProps[iOrigDestATypVal].Value.LPSZ = (LPTSTR) m_lpszAddrType;

    // Handle non-read notification specific properties.
    if ( m_MsgType == mtNRN )
    {
        rgNotifyProps[iDiscardCodeVal].ulPropTag = PR_DISCARD_REASON;
        rgNotifyProps[iDiscardCodeVal].Value.l = atol(m_rgszData[iDiscardCode]);

        rgNotifyProps[iNonRcptCodeVal].ulPropTag = PR_NON_RECEIPT_REASON;
        rgNotifyProps[iNonRcptCodeVal].Value.l = atol(m_rgszData[iNonRcptCode]);
    }

    // Read notifications use the PR_PARENT_KEY property to
    // hold the IPM subject identifier.
    // Determine the PR_PARENT_KEY.
    ASSERTERROR(lstrlen(m_rgszData[iSubjectXID]) <= ulMaxOutStringLen,
                "Bad m_rgszData[iSubjectXID]");

    // compute # bytes of binary data expected
    cbParentKey = lstrlen(m_rgszData[iSubjectXID])/2;

    hr = ScBinFromHexBounded(   
            m_rgszData[iSubjectXID],    // ASCII representation of binary key
            rgbParentKey,               // Binary parent key pointer
            cbParentKey);               // # bytes of binary data

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    rgNotifyProps[iSubjectXIDVal].ulPropTag = PR_PARENT_KEY;
    rgNotifyProps[iSubjectXIDVal].Value.bin.cb = cbParentKey;   // # bytes 
    rgNotifyProps[iSubjectXIDVal].Value.bin.lpb = rgbParentKey; // binary value

    ASSERTERROR(!FBadUnknown(m_lpContent), "Bad m_lpContent");

    // Set notification content properties.
    hr = m_lpContent->SetProps(
                nNotifyProps,       // # of properties
                rgNotifyProps,      // array of property values
                &lpsProblems);      // problem array pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        lpsProblems = NULL;

        goto cleanup;
    }

    // Check for property problems
    if ( lpsProblems )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Modify content's recipient table
    hr = m_lpContent->ModifyRecipients(
                MODRECIP_ADD,       // flags
                m_lpContentRecips); // address list        

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // save the changes to the message content
    hr = m_lpContent->SaveChanges(
                0);                     // we are done with the message content

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // save changes to the envelope attachment
    hr = m_lpAttach->SaveChanges(
                0);                     // we are done with the envelope attachment

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // we are done
    
cleanup:

    // Free MAPI buffers
    MAPIFREEBUFFER(lpEid);
    MAPIFREEBUFFER(lpszSubjectPrefix);
    MAPIFREEBUFFER(lpszNormSubject);
    MAPIFREEBUFFER(lpsProblems);

    RETURN(hr);

}
