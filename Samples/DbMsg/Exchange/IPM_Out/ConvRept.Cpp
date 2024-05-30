// --convrept.cpp------------------------------------------------
//
// CIPMConvert source code for IPM reports.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// --------------------------------------------------------------

#include "edk.h"
#include "ipmconv.h"
#include "msgemit.h"
#include "convcls.h"
#include "tagnames.h"
#include "convrept.chk"

//$--CIPMConvert::HrReportTo822Format---------------------------
//
// DESCRIPTION: Handle convertion of IPM reports to 822-style header
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_OUTOFMEMORY if memory problems
//                      E_NOTIMPL if unknown report type is received
//                      E_FAIL otherwise
//
// -------------------------------------------------------------
HRESULT CIPMConvert::HrReportTo822Format()  // RETURNS: HRESULT
{
    HRESULT hr  =   NOERROR;

    DEBUGPRIVATE("CIPMConvert::HrReportTo822Format()\n");

    // switch off of report's type
    switch ( m_MsgType )
    {
        case mtNDR:
            // non-delivery report

            // Handle the report's envelope.
            hr = HrConvertReport();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Handle non-recipient table.
            hr = HrConvertNonRecipients();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            break;

        case mtDR:
            // delivery report

            // Handle the report's envelope.
            hr = HrConvertReport();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Handle recipient table
            hr = HrConvertRecipients();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            break;

        case mtNRN:
        case mtRN:
            // non-read notification &
            // read notification

            // Handle notification envelope
            // (appears to be essentially the same
            // as a regular IPM envelope.
            hr = HrConvertEnvelope();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Handle read/non-read notification content.
            hr = HrConvertNotifyContent();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            break;

        default:
            // shouldn't happen
            hr = HR_LOG(E_FAIL);

            goto cleanup;

    }   // end switch

    // we are done

cleanup:

    RETURN(hr);

}

//$--CIPMConvert::HrConvertReport--------------------------------
//
// DESCRIPTION: Handle conversion of REPORT.[N]DR delivery/non-delivery
//              report envelope
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_OUTOFMEMORY if memory problems,
//                      E_NOTIMPL if don't support report type
//                      E_FAIL otherwise.
//
//----------------------------------------------------------------
HRESULT CIPMConvert::HrConvertReport()   // RETURNS: HRESULT
{
    HRESULT         hr              =   NOERROR;
    LPTSTR          lpTempString    =   NULL;       // temporary string pointer
    BOOL            fReportXID      =   TRUE;       // FALSE if report does not have XID property
    LPTRACEINFO     lpTraceInfo     =   NULL;       // trace information structure pointer
    ULONG           iLoop           =   0;          // loop index
    LPTRACEENTRY    lpTraceEntry    =   NULL;       // trace entry pointer
    BOOL            fTraceInfo      =   TRUE;       // FALSE if no trace information
    ULONG           ulObjType       =   0;          // MAPI object type
    LPMAILUSER      lpReportToUser  =   NULL;       // report to recipient pointer
    LPSPropValue    lpRecipProps    =   NULL;       // recipient property value array pointer

    PINTTRACEINFO   lpIntTraceInfo  =   NULL;       // trace information structure pointer
    PINTTRACEENTRY  lpIntTraceEntry =   NULL;       // trace entry pointer
    BOOL            fIntTraceInfo   =   TRUE;       // FALSE if no trace information

    // Report property indices
    const UINT  iClass       =    0;  // index of message class value    
    const UINT  iFromAddr    =    1;  // index of sender address
    const UINT  iXID         =    2;  // index of X-message identifier
    const UINT  iTrace       =    3;  // index of trace information
    const UINT  iSentTime    =    4;  // index of sent time value
    const UINT  iImportance  =    5;  // index of importance value
    const UINT  iPriority    =    6;  // index of priority value
    const UINT  iSubject     =    7;  // index of the subject value
    const UINT  iReportToEID =    8;  // index of report destination entry ID
    const UINT  iSubjectXID  =    9;  // index of report subject X-message ID value
    const UINT  iIntTrace    =   10;  // index of trace information

    // number of report properties
    const ULONG     nProps          =   11;

    // Properties to retrieve for the report envelope
    SizedSPropTagArray(nProps, sPropTagArray) =
    {
        nProps,  // number of properties
        {
            PR_MESSAGE_CLASS,   // report class property ID
            PR_SENDER_EMAIL_ADDRESS,    // report from address
            PR_MESSAGE_SUBMISSION_ID,   // report X-identifier
            PR_TRACE_INFO,      // report trace information
            PR_CREATION_TIME,   // report creation time
            PR_IMPORTANCE,      // report importance
            PR_PRIORITY,        // report priority
            PR_SUBJECT,         // report subject
            PR_REPORT_DESTINATION_ENTRYID,  // report destination entry identifier
            PR_MTS_SUBJECT_ID,  // report's subject X-identifier
            PR_INTERNAL_TRACE_INFO,  // report internal trace information
        }
    };

    // indices into the recipient property array.
    const UINT  iEmailAddr  =   0;      // recipient's email address
    
    const ULONG nRecipProps =   1;      // # of recipient properties

    // Array of recipient properties to retrieve
    SizedSPropTagArray(nRecipProps, sRecipProps) =
    {
        nRecipProps,      // # recipient properties to retrieve
        {
            PR_EMAIL_ADDRESS    // recipient's email address
        }
    };

    DEBUGPRIVATE("CIPMConvert::HrConvertReport()\n");

    // consistency checks
    ASSERT_IUNKNOWN_PTR(m_lpAB, "Bad m_lpAB");

    // Retieve the properties needed on the report envelope.
    hr = HrRetrieveProps(m_lpEnvelope,
                          (LPSPropTagArray) &sPropTagArray,
                          &m_lpEnvProps);

    // Delivery reports may not have the PR_MESSAGE_SUBMISSION_ID
    // nor the PR_MTS_SUBJECT_ID property.  This is a bug.  For the time
    // being, however, we shall not fail because of this.
    if ( hr == EDK_E_NOT_FOUND )
    {
        UINT    iPropIndex  =   0;
        for ( iPropIndex = 0; iPropIndex < sPropTagArray.cValues;
              iPropIndex++ )
        {
            if ( PROP_TYPE(m_lpEnvProps[iPropIndex].ulPropTag) == 
                 PT_ERROR )
            {
                if ( iPropIndex == iXID )
                {
                    fReportXID = FALSE;

                    hr = HR_LOG(NOERROR);   // not treated as an error
                }

                // It's also O.K. for there to be no trace
                // information.
                else if ( iPropIndex == iTrace )
                {
                    // no trace information
                    fTraceInfo = FALSE; 

                    hr = HR_LOG(NOERROR);

                }   // end if no PR_TRACE_INFO

                else if ( iPropIndex == iIntTrace )
                {
                    // no internal trace information
                    fIntTraceInfo = FALSE; 

                    hr = HR_LOG(NOERROR);

                }   // end if no PR_INTERNAL_TRACE_INFO

                else
                {
                    hr = HR_LOG(E_FAIL);    // another property isn't set

                    goto cleanup;
                }
            }
        }   // end for
    }

    // Test for other errors
    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build and emit the "X-Tnef-Attach" tag and data line.
    // The TNEF data file name is always "MAPIMAIL.DAT" if
    // we are doing TNEF encoding and null otherwise.
    hr = HrEmitTagDataLine(
        lpszTagTnefAttach,      // tag
        (LPTSTR) (m_fTNEFEncode ? lpszTagTnefHdr : lpszNullData),  // data
        m_lpStream);            // stream pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // build and emit the "MAIL FROM" line.  
    // from the sender's address string.
    hr = HrEmitTagDataLine(
            lpszTagMailFrom,        // tag
            m_lpEnvProps[iFromAddr].Value.LPSZ,  // sender's Email address
            m_lpStream);              // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Emit the "RCPT TO" tag and data line.
    // First, we must open the address book entry associated with the 
    // destination entry identifier and retrieve the entry's email
    // address.
    hr = m_lpAB->OpenEntry(
        m_lpEnvProps[iReportToEID].Value.bin.cb,    // # bytes in entry ID
        (LPENTRYID) m_lpEnvProps[iReportToEID].Value.bin.lpb,   // entry identifier
        NULL,                                       // interface identifer
        MAPI_DEFERRED_ERRORS,                       // reduces RPCs
        &ulObjType,                                 // MAPI object type
        (LPUNKNOWN *) &lpReportToUser);             // report to recipient pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(ulObjType == MAPI_MAILUSER, "Bad ulObjType");
    ASSERT_IUNKNOWN_PTR(lpReportToUser, "Bad lpReportToUser.");

    // Retrieve the email address of the report recipient.
    hr = HrRetrieveProps(
        lpReportToUser,     // MAPI recipient pointer
        (LPSPropTagArray) &sRecipProps,   // property tag array
        &lpRecipProps);     // property value array pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the recipient's address for the "RCPT_TO" tag
    hr = HrEmitTagDataLine(
            lpszTagRcptTo,          // tag
            lpRecipProps[iEmailAddr].Value.LPSZ, // report destination
            m_lpStream);          // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Emit the "DATA" marker
    hr = m_lpStream->Write(
            lpszTagData,        // data
            lstrlen(lpszTagData) * sizeof(TCHAR),   // length (no terminator)
            NULL);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Print out the "X-Message-Class:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
            lpszTagMsgClass,        // tag
            m_lpEnvProps[iClass].Value.LPSZ,  // report class                              
            m_lpStream);          // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build the date and time string
    hr = HrCreateDateTimeString(
                  &(m_lpEnvProps[iSentTime].Value.ft),  // PR_CLIENT_SUBMIT_TIME property value
                  &lpTempString);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "Date:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
                lpszTagDate, 
                lpTempString, 
                m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    MAPIFREEBUFFER(lpTempString);

    // Print out the "X-Message-ID:" tag and data line to the stream
    // The X-Message ID string is null terminated.
    if ( fReportXID )
    {
        hr = HrEmitTagDataLine(
            lpszTagMsgID,
            (LPTSTR) m_lpEnvProps[iXID].Value.bin.lpb,   // really a null-terminated string
            m_lpStream);
    }

    else
    {
        // Delivery reports may not have a PR_MESSAGE_SUBMISSION_ID
        // nor a PR_MTS_SUBJECT_ID.  
        // We will print out a "null" XID in this case.
        hr = HrEmitTagDataLine(
            lpszTagMsgID,            // tag
            (LPTSTR) lpszNullData,   // blank data
            m_lpStream);
    }

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "X-Message-Subject-ID:" tag and data line to the stream
    // The X-Message ID string is already null terminated.
    hr = HrEmitTagDataLine(
        lpszTagSubjectID, 
        (LPTSTR) m_lpEnvProps[iSubjectXID].Value.bin.lpb,    // really a null-terminated string
        m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build the trace information string, if any
    if ( fTraceInfo == TRUE )
    {
        // have trace information
        lpTraceInfo = (LPTRACEINFO) (m_lpEnvProps[iTrace].Value.bin.lpb);

        // Print out trace entry data
        for ( iLoop = 0; iLoop < lpTraceInfo->cEntries; iLoop++ )
        {
            // retrieve trace entry.
            lpTraceEntry = &(lpTraceInfo->rgtraceentry[iLoop]);

            // Create "External-Received-By" string
            hr = HrCreateExternalTraceString(
                lpTraceEntry->lAction,          // trace action
                lpTraceEntry->rgchCountryName,  // country name
                lpTraceEntry->rgchADMDName,     // ADMD name
                lpTraceEntry->rgchPRMDId,       // PRMD identifier
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "External-Received-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagExternalRcvdBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "External-Received-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpTraceEntry->ftArrivalTime), // trace arrival time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out External-Received-At date and time string
            hr = HrEmitTagDataLine(
                lpszTagExternalRcvdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Create "External-Attempted-By" string
            hr = HrCreateExternalTraceString(
                lpTraceEntry->lAction,              // trace action
                lpTraceEntry->rgchAttCountryName,   // country name
                lpTraceEntry->rgchAttADMDName,      // ADMD name
                lpTraceEntry->rgchAttPRMDId,        // PRMD identifier
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "External-Attempted-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagExternalAttmBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "External-Deferred-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpTraceEntry->ftDeferredTime), // trace deferal time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out External-Deferred-At data and time string
            hr = HrEmitTagDataLine(
                lpszTagExternalDefdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

        }   // end for each trace entry
    }   // end if any trace information

    // Build the internal trace information string, if any
    if ( fIntTraceInfo == TRUE )
    {
        // have trace information
        lpIntTraceInfo = (PINTTRACEINFO) (m_lpEnvProps[iIntTrace].Value.bin.lpb);

        // Print out trace entry data
        for ( iLoop = 0; iLoop < lpIntTraceInfo->cEntries; iLoop++ )
        {
            // retrieve trace entry.
            lpIntTraceEntry = &(lpIntTraceInfo->rgIntTraceEntry[iLoop]);

            // Create "Internal-Received-By" string
            hr = HrCreateInternalTraceString(
                lpIntTraceEntry->lAction,          // trace action
                lpIntTraceEntry->rgchCountryName,  // country name
                lpIntTraceEntry->rgchADMDName,     // ADMD name
                lpIntTraceEntry->rgchPRMDId,       // PRMD identifier
                lpIntTraceEntry->rgchMTAName,      // ADMD name
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "Internal-Received-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagInternalRcvdBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "Internal-Received-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpIntTraceEntry->ftArrivalTime), // trace arrival time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out Internal-Received-At date and time string
            hr = HrEmitTagDataLine(
                lpszTagInternalRcvdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Create "Internal-Attempted-By" string
            hr = HrCreateInternalTraceString(
                lpIntTraceEntry->lAction,              // trace action
                lpIntTraceEntry->rgchAttCountryName,   // country name
                lpIntTraceEntry->rgchAttADMDName,      // ADMD name
                lpIntTraceEntry->rgchAttPRMDId,        // PRMD identifier
                lpIntTraceEntry->rgchAttMTAName,       // MTA name
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "Internal-Attempted-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagInternalAttmBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "Internal-Deferred-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpIntTraceEntry->ftDeferredTime), // trace deferal time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out Internal-Deferred-At data and time string
            hr = HrEmitTagDataLine(
                lpszTagInternalDefdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

        }   // end for each internal trace entry
    }   // end if any internal trace information

    // Print out the "From:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
            lpszTagFrom,     // tag
            m_lpEnvProps[iFromAddr].Value.LPSZ,    // report creator
            m_lpStream);                // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "TO:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
            lpszTagTo,     // tag
            lpRecipProps[iEmailAddr].Value.LPSZ,    // report destination
            m_lpStream);                // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out a blank line
    hr = m_lpStream->Write(
            lpszNewLine,            // data
            lstrlen(lpszNewLine) * sizeof(TCHAR),   // length (no terminator)
            NULL);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Print out the "Subject:" tag and data line to the stream
    hr = HrEmitTagDataLine(
            lpszTagSubject,                // tag
            m_lpEnvProps[iSubject].Value.LPSZ,  // PR_SUBJECT property value
            m_lpStream);                    // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build priority string.
    hr = HrCreatePriorityString(
                m_lpEnvProps[iPriority].Value.ul,  // PR_PRIORITY property value
                &lpTempString);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "Priority:" tag and data line to the stream
    hr = HrEmitTagDataLine(
            lpszTagPriority, 
            lpTempString, 
            m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    MAPIFREEBUFFER(lpTempString);

    // Build the importance string
    hr = HrCreateImportanceString(
                m_lpEnvProps[iImportance].Value.ul,    // PR_IMPORTANCE property value
                &lpTempString);                             // buffer pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "Importance:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
                lpszTagImportance, 
                lpTempString, 
                m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }
   
    MAPIFREEBUFFER(lpTempString);

cleanup:

    // Release MAPI objects
    ULRELEASE(lpReportToUser);

    // Release MAPI buffers
    MAPIFREEBUFFER(lpTempString);
    MAPIFREEBUFFER(lpRecipProps);

    RETURN(hr);

}

//$--CIPMConvert::HrConvertNonRecipients--------------------------
//
// DESCRIPTION: Handle NDR report's non-recipient table
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ------------------------------------------------------------
HRESULT CIPMConvert::HrConvertNonRecipients()    // RETURNS: HRESULT
{
    HRESULT     hr                  =   NOERROR;
    LPSRowSet   lpRows              =   NULL;       // recipient table rows pointer
    ULONG       iRowCount           =   0;          // row counter

    // temporary string buffer
    TCHAR       szTempBuffer[ulMaxOutStringLen + 1]    =   TEXT("");

    // Columns needed from the report's recipient table
    SizedSPropTagArray(4, sRecipProps)  =   
    {
        4,      // number of properties (columns) desired
        {
            PR_EMAIL_ADDRESS,   // non-recipient Email address
            PR_REPORT_TEXT,     // report text
            PR_NDR_DIAG_CODE,   // diagnostic failure code
            PR_NDR_REASON_CODE  // reason failure code
        }
    };

    // indices into the property values array
    const UINT  iRecipient      =   0;  // non-recipient email address
    const UINT  iText           =   1;  // report text
    const UINT  iDiagCode       =   2;  // diagnostic reason code
    const UINT  iNDRCode        =   3;  // non-delivery reason code

    DEBUGPRIVATE("CIPMConvert::HrConvertNonRecipients()\n");

    // Retrieve the rows from the NDR's recipient table
    hr = HrGetRecipientList(
                m_lpEnvelope,   // report pointer
                (LPSPropTagArray) &sRecipProps, // columns to retrieve
                &lpRows);       // pointer to rows array pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Make sure that we have at least one non-recipient
    if ( lpRows->cRows == 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Process each non-recipient
    for ( iRowCount = 0; iRowCount < lpRows->cRows; 
          iRowCount++ )
    {
        // Emit the "Your message was not delivered to" tag and 
        // data line.
        hr = HrEmitTagDataLine(
                lpszTagNotSentTo,   // tag
                lpRows->aRow[iRowCount].lpProps[iRecipient].Value.LPSZ, // data
                m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Emit the "for the following reason" tag and data line.
        hr = HrEmitTagDataLine(
                lpszTagReason,      // tag
                lpRows->aRow[iRowCount].lpProps[iText].Value.LPSZ, // data
                m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Format the diagnostic code
        wsprintf(
            szTempBuffer, 
            TEXT("%ld"), 
            lpRows->aRow[iRowCount].lpProps[iDiagCode].Value.ul);

        // Emit the "Diagnostic code" tag and data line.
        hr = HrEmitTagDataLine(
            lpszTagDiagCode,        // tag
            szTempBuffer,           // data
            m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Format the NDR reason code
        wsprintf(
            szTempBuffer, 
            TEXT("%ld"), 
            lpRows->aRow[iRowCount].lpProps[iNDRCode].Value.ul);

        // Emit the "Diagnostic reason" tag and data line.
        hr = HrEmitTagDataLine(
            lpszTagNDRCode,         // tag
            szTempBuffer,           // data
            m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // done with this recipient

    }   // end for

cleanup:

    // Free MAPI buffers
    FREEPROWS(lpRows);

    RETURN(hr);

}

//$--CIPMConvert::HrConvertRecipients--------------------------
//
// DESCRIPTION: Handle DR report's recipient table
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ------------------------------------------------------------
HRESULT CIPMConvert::HrConvertRecipients()    // RETURNS: HRESULT
{
    HRESULT     hr                  =   NOERROR;
    LPSRowSet   lpRows              =   NULL;       // recipient table rows pointer
    ULONG       iRowCount           =   0;          // row counter
    LPTSTR      lpTempString        =   NULL;       // temporary string pointer

    // Columns needed from the report's recipient table
    SizedSPropTagArray(2, sRecipProps)  =   
    {
        2,      // number of properties (columns) desired
        {
            PR_EMAIL_ADDRESS,   // non-recipient Email address
            PR_DELIVER_TIME     // delivery time
        }
    };

    // indices into the property values array
    const UINT  iRecipient      =   0;  // recipient email address
    const UINT  iTime           =   1;  // delivery time

    DEBUGPRIVATE("CIPMConvert::HrConvertRecipients()\n");

    // Retrieve the rows from the DR's recipient table
    hr = HrGetRecipientList(
                m_lpEnvelope,   // report pointer
                (LPSPropTagArray) &sRecipProps, // columns to retrieve
                &lpRows);       // pointer to rows array pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Make sure that we have at least one recipient
    if ( lpRows->cRows == 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    for ( iRowCount = 0; iRowCount < lpRows->cRows; 
          iRowCount++ )
    {
        // Emit the "Your message was successfully delivered to"
        // tag and data line.
        hr = HrEmitTagDataLine(
                    lpszTagSentTo,      // tag
                    lpRows->aRow[iRowCount].lpProps[iRecipient].Value.LPSZ, // data
                    m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Create the delivery time string
        hr = HrCreateDateTimeString(
                    &(lpRows->aRow[iRowCount].lpProps[iTime].Value.ft),   // delivery time
                    &lpTempString);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Emit the "at" time tag and data line.
        hr = HrEmitTagDataLine(
                    lpszTagAtTime,      // tag
                    lpTempString,       // data
                    m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free temporary buffer
        MAPIFREEBUFFER(lpTempString);

        // We are done with this recipient

    }   // end for

cleanup:

    // Free MAPI buffers
    FREEPROWS(lpRows);
    
    MAPIFREEBUFFER(lpTempString);

    RETURN(hr);

}

//$--CIPMConvert::HrConvertNotifyContent--------------------------
//
// DESCRIPTION: Handles read and non-read notification report's content
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ------------------------------------------------------------
HRESULT CIPMConvert::HrConvertNotifyContent()    // RETURNS: HRESULT
{
    HRESULT         hr              =   NOERROR;
    LPTSTR          lpTempString    =   NULL;   // temporary string pointer
    LPSRowSet       lpRecipRows     =   NULL;   // recipient table rows pointer
    LPTRACEINFO     lpTraceInfo     =   NULL;   // trace information structure pointer
    ULONG           iLoop           =   0;      // loop index
    LPTRACEENTRY    lpTraceEntry    =   NULL;   // trace entry pointer

    PINTTRACEINFO   lpIntTraceInfo  =   NULL;   // trace information structure pointer
    PINTTRACEENTRY  lpIntTraceEntry =   NULL;   // trace entry pointer

    // temporary string buffer
    TCHAR           szTempBuf[ulMaxOutStringLen + 1]   =   TEXT("");

    // common notification property indices
    const UINT  iClass       =    0;  // index of message class value    
    const UINT  iFromAddr    =    1;  // index of sender address
    const UINT  iXID         =    2;  // index of X-message identifier
    const UINT  iSentTime    =    3;  // index of sent time value
    const UINT  iImportance  =    4;  // index of importance value
    const UINT  iPriority    =    5;  // index of priority value
    const UINT  iSubject     =    6;  // index of the subject value
    const UINT  iSubjectXID  =    7;  // index of X-message subject ID
    const UINT  iReportTime  =    8;  // index of report time

    // Number of read-notification properties
    const ULONG nRNProps     =    9;  

    // properties unique to non read notifications
    const UINT  iDiscardCode =    9;  // PR_DISCARD_REASON
    const UINT  iNonRcptCode =    10; // PR_NON_RECEIPT_REASON

    // number of non-read notification content properties
    const ULONG     nNRNProps    =   11;

    // Properties needed from the NRN report's content
    SizedSPropTagArray(nNRNProps, sPropsNotify)  =   
    {
        nNRNProps,   // number of properties (columns) desired
        {
            PR_MESSAGE_CLASS,       // report class property ID
            PR_SENDER_EMAIL_ADDRESS,// content's sender's email address, index iFromAddr
            PR_SEARCH_KEY,          // dummy--acutally use PR_MESSAGE_SUBMISSION_ID on from
                                    // the envelope
            PR_CLIENT_SUBMIT_TIME,  // content's sent time, index iSentTime
            PR_IMPORTANCE,          // report importance
            PR_PRIORITY,            // report priority
            PR_SUBJECT,             // report subject
            // Notifications use PR_PARENT_KEY instread of
            // PR_MTS_SUBJECT_ID for the X-message subject identifier
            PR_PARENT_KEY,          // X-message-subject identifier
            PR_REPORT_TIME,         // report time
            PR_DISCARD_REASON,      // reason why message was discarded
            PR_NON_RECEIPT_REASON   // reson why message wansn't read
        }
    };

    // indices used into envelope property array
    const UINT  iTrace       =    3;  // PR_TRACE_INFO
    const UINT  iIntTrace    =    4;  // PR_INTERNAL_TRACE_INFO

    // Columns needed from the report content's recipient table
    SizedSPropTagArray(1, sRecipProps)  =   
    {
        1,      // number of properties (columns) desired
        {
            PR_EMAIL_ADDRESS   // notification "TO" Email address
        }
    };

    // indices into the recipient table property values
    const UINT  iRecipient  =   0;  // PR_EMAIL_ADDRESS

    DEBUGPRIVATE("CIPMConvert::HrConvertNotifyContent()\n");

    // consistency checking
    ASSERTERROR((m_MsgType == mtNRN || m_MsgType == mtRN),
                "Bad m_MsgType");

    // Open the envelope's content.
    hr = HrOpenContent();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    if ( m_MsgType == mtRN )
    {
        // Adjust number of properties to retrieve for read notifications.
        sPropsNotify.cValues = nRNProps;
    }

    // Retrieve the desired properties from the NRN or RN's
    // content
    hr = HrRetrieveProps(
                m_lpContent,    // report pointer
                (LPSPropTagArray) &sPropsNotify,  // Properties to retrieve
                &m_lpCntProps); // pointer to property array pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "X-Message-Class:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
            lpszTagMsgClass,        // tag
            m_lpCntProps[iClass].Value.LPSZ,  // report class                              
            m_lpStream);          // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build the date and time string
    hr = HrCreateDateTimeString(
                  &(m_lpCntProps[iSentTime].Value.ft),  // PR_CLIENT_SUBMIT_TIME property value
                  &lpTempString);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "Date:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
                lpszTagDate, 
                lpTempString, 
                m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    MAPIFREEBUFFER(lpTempString);

    // Print out the "X-Message-ID:" tag and data line to the stream
    // The X-Message ID string is null terminated.
    // Note:  The PR_MESSAGE_SUBMISSION_ID is really on the
    // envelope.
    hr = HrEmitTagDataLine(
            lpszTagMsgID,
            (LPTSTR) m_lpEnvProps[iXID].Value.bin.lpb,   // really a null-terminated string
            m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "X-Message-Subject-ID:" tag and data line to the stream
    // The X-Message ID string is already null terminated.
    // This is the binary PR_PARENT_KEY property for notifications,
    // so we shall need to convert it to ASCII.

    // Check that we have enough room in our output buffer.
    ASSERTERROR((m_lpCntProps[iSubjectXID].Value.bin.cb * 2 <= ulMaxOutStringLen),
                "Bad cbParentKey");
    HexFromBin(
            m_lpCntProps[iSubjectXID].Value.bin.lpb,    // binary data
            m_lpCntProps[iSubjectXID].Value.bin.cb,     // # bytes of binary data
            szTempBuf);                                 // string buffer

    ASSERTERROR(!IsBadStringPtr(szTempBuf, INFINITE), "Bad szTempBuf");

    hr = HrEmitTagDataLine(
            lpszTagSubjectID,       // tag
            szTempBuf,              // data            
            m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the trace information, if any.
    if ( PROP_TYPE(m_lpEnvProps[iTrace].ulPropTag) != PT_ERROR )
    {
        // We have valid trace information
        lpTraceInfo = (LPTRACEINFO) (m_lpEnvProps[iTrace].Value.bin.lpb);

        // Print out trace entries
        for ( iLoop = 0; iLoop < lpTraceInfo->cEntries; iLoop++ )
        {
            // retrieve trace entry.
            lpTraceEntry = &(lpTraceInfo->rgtraceentry[iLoop]);

            // Create "External-Received-By" string
            hr = HrCreateExternalTraceString(
                lpTraceEntry->lAction,          // trace action
                lpTraceEntry->rgchCountryName,  // country name
                lpTraceEntry->rgchADMDName,     // ADMD name
                lpTraceEntry->rgchPRMDId,       // PRMD identifier
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "External-Received-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagExternalRcvdBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "External-Received-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpTraceEntry->ftArrivalTime), // trace arrival time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out External-Received-At data and time string
            hr = HrEmitTagDataLine(
                lpszTagExternalRcvdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Create "External-Attempted-By" string
            hr = HrCreateExternalTraceString(
                lpTraceEntry->lAction,              // trace action
                lpTraceEntry->rgchAttCountryName,   // country name
                lpTraceEntry->rgchAttADMDName,      // ADMD name
                lpTraceEntry->rgchAttPRMDId,        // PRMD identifier
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "External-Attempted-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagExternalAttmBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "External-Deferred-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpTraceEntry->ftDeferredTime), // trace deferal time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out External-Deferred-At data and time string
            hr = HrEmitTagDataLine(
                lpszTagExternalDefdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

        }   // end for each trace entry
    }   // end if trace information

    // Print out the internal trace information, if any.
    if ( PROP_TYPE(m_lpEnvProps[iIntTrace].ulPropTag) != PT_ERROR )
    {
        // We have valid trace information
        lpIntTraceInfo = (PINTTRACEINFO) (m_lpEnvProps[iIntTrace].Value.bin.lpb);

        // Print out trace entries
        for ( iLoop = 0; iLoop < lpIntTraceInfo->cEntries; iLoop++ )
        {
            // retrieve trace entry.
            lpIntTraceEntry = &(lpIntTraceInfo->rgIntTraceEntry[iLoop]);

            // Create "Internal-Received-By" string
            hr = HrCreateInternalTraceString(
                lpIntTraceEntry->lAction,          // trace action
                lpIntTraceEntry->rgchCountryName,  // country name
                lpIntTraceEntry->rgchADMDName,     // ADMD name
                lpIntTraceEntry->rgchPRMDId,       // PRMD identifier
                lpIntTraceEntry->rgchMTAName,      // MTA name
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "Internal-Received-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagInternalRcvdBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "Internal-Received-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpIntTraceEntry->ftArrivalTime), // trace arrival time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out Internal-Received-At data and time string
            hr = HrEmitTagDataLine(
                lpszTagInternalRcvdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Create "Internal-Attempted-By" string
            hr = HrCreateInternalTraceString(
                lpIntTraceEntry->lAction,              // trace action
                lpIntTraceEntry->rgchAttCountryName,   // country name
                lpIntTraceEntry->rgchAttADMDName,      // ADMD name
                lpIntTraceEntry->rgchAttPRMDId,        // PRMD identifier
                lpIntTraceEntry->rgchAttMTAName,       // MTA name
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out the "Internal-Attempted-By:" tag and data line to the stream.
            hr = HrEmitTagDataLine(
                lpszTagInternalAttmBy, 
                lpTempString, 
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

            // Build "Internal-Deferred-At" date and time string
            hr = HrCreateDateTimeString(
                &(lpIntTraceEntry->ftDeferredTime), // trace deferal time
                &lpTempString);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Print out Internal-Deferred-At data and time string
            hr = HrEmitTagDataLine(
                lpszTagInternalDefdAt,  // tag
                lpTempString,       // data
                m_lpStream);        // stream

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            MAPIFREEBUFFER(lpTempString);

        }   // end for each internal trace entry
    }   // end if internal trace information

    // Print out the "From:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
            lpszTagFrom,     // tag
            m_lpCntProps[iFromAddr].Value.LPSZ,    // report creator
            m_lpStream);                // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build the "TO:" tag and data line from the
    // content's recipient table.
    hr = HrGetRecipientList(
            m_lpContent,        // MAPI message content pointer
            (LPSPropTagArray) &sRecipProps,        // property columns desired array
            &lpRecipRows);      // Rows retrieved from recipient table

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // There should only be one "TO" for a read or non-read
    // notification, since an IPM.NOTE message can have only one 
    // sender.
    if ( lpRecipRows->cRows != 1 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Print out the "TO:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
            lpszTagTo,     // tag
            lpRecipRows->aRow[0].lpProps[iRecipient].Value.LPSZ,    // report destination
            m_lpStream);                // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out a blank line
    hr = m_lpStream->Write(
            lpszNewLine,            // data
            lstrlen(lpszNewLine) * sizeof(TCHAR),   // length (no terminator)
            NULL);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Print out the "Subject:" tag and data line to the stream
    hr = HrEmitTagDataLine(
            lpszTagSubject,                // tag
            m_lpCntProps[iSubject].Value.LPSZ,  // PR_SUBJECT property value
            m_lpStream);                    // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build priority string.
    hr = HrCreatePriorityString(
                m_lpCntProps[iPriority].Value.ul,  // PR_PRIORITY property value
                &lpTempString);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "Priority:" tag and data line to the stream
    hr = HrEmitTagDataLine(
            lpszTagPriority, 
            lpTempString, 
            m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    MAPIFREEBUFFER(lpTempString);

    // Build the importance string
    hr = HrCreateImportanceString(
                m_lpCntProps[iImportance].Value.ul,    // PR_IMPORTANCE property value
                &lpTempString);                             // buffer pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the "Importance:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
                lpszTagImportance, 
                lpTempString, 
                m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }
   
    MAPIFREEBUFFER(lpTempString);

    // The output for the two notifications diverges
    // here.
    if ( m_MsgType == mtNRN )    // non-read notification
    {
        // Emit the "Your message was not read by" tag
        // and data line
        hr = HrEmitTagDataLine(
                lpszTagNotReadBy,   // tag
                m_lpCntProps[iFromAddr].Value.LPSZ,    // data
                m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Create the report time string.
        hr = HrCreateDateTimeString(
            &(m_lpCntProps[iReportTime].Value.ft),    // time
            &lpTempString);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Emit the "at" tag and data line
        hr = HrEmitTagDataLine(
                lpszTagAtTime,      // tag
                lpTempString,       // data
                m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // free temporary string buffer
        MAPIFREEBUFFER(lpTempString);

        // Format the discard code data
        wsprintf(
                szTempBuf,      // buffer
                TEXT("%ld"),    // format string
                m_lpCntProps[iDiscardCode].Value.ul);   // discard code

        // Emit the "Discard code" tag and data line.
        hr = HrEmitTagDataLine(
                lpszTagDiscCode,    // tag
                szTempBuf,          // data
                m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Format the non-receipt code data
        wsprintf(
                szTempBuf,      // buffer
                TEXT("%ld"),    // format string
                m_lpCntProps[iNonRcptCode].Value.ul);   // code

        // Emit the "Non-receipt code" tag and data line
        hr = HrEmitTagDataLine(
                lpszTagNRNCode,     // tag
                szTempBuf,          // buffer
                m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

    }   // end if NRN

    else if ( m_MsgType == mtRN )    // read notification
    {
        // Emit the "Your message was read by" tag and
        // data line.
        hr = HrEmitTagDataLine(
                lpszTagReadBy,          // tag
                m_lpCntProps[iFromAddr].Value.LPSZ,    // data
                m_lpStream);

        // Create the receipt time string.
        hr = HrCreateDateTimeString(
            &(m_lpCntProps[iReportTime].Value.ft),    // time
            &lpTempString);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Emit the "at" tag and data line
        hr = HrEmitTagDataLine(
                lpszTagAtTime,      // tag
                lpTempString,       // data
                m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // free temporary string buffer
        MAPIFREEBUFFER(lpTempString);
    }

    else
    {
        // shouldn't happen
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // we are done.

cleanup:

    // Free MAPI buffers
    FREEPROWS(lpRecipRows);

    MAPIFREEBUFFER(lpTempString);

    RETURN(hr);

}
