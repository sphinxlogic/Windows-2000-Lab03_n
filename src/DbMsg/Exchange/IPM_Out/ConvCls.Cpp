// --convcls.cpp--------------------------------------------------------------
//
// IPM to 822 conversion class source file.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include "edk.h"
#include "ipmconv.h"
#include "msgemit.h"
#include "convcls.h"
#include "tagnames.h"
#include "convcls.chk"

//$--CIPMConvert::CIPMConvert------------------------------------------------
//
// DESCRIPTION: CIPMConvert conversion class constructor
//
// INPUT:   none
//
// RETURNS: nothing
//
// ---------------------------------------------------------------------------
CIPMConvert::CIPMConvert()
{
    DEBUGPRIVATE("CIPMConvert::CIPMConvert()\n");

    // Initialize data members
    m_lpwszMsgClass = NULL;
    m_lpStream = NULL;
    m_fTNEFEncode = FALSE;
    m_lpAB = NULL;
    m_lpEnvelope = NULL;
    m_lpContent = NULL;
    m_lpEnvProps = NULL;
    m_lpCntProps = NULL;
    m_MsgType = mtNone;
    m_lpAttach = NULL;
}

//$--CIPMConvert::~CIPMConvert------------------------------------------------
//
// DESCRIPTION: CIPMConvert conversion class destructor
//
// INPUT:   none
//
// RETURNS: nothing
//
// ---------------------------------------------------------------------------
CIPMConvert::~CIPMConvert()
{
    DEBUGPRIVATE("CIPMConvert::~CIPMConvert()\n");

    // Free all MAPI buffers and release all MAPI objects
    Reset();

}

//$--CIPMConvert::fCheckInit--------------------------------------------------
//
// DESCRIPTION: Inline function to check to see if conversion class instance has
//              been initialized via HrInitialize().
//
// INPUT:       none
//
// RETURNS:     BOOL    --  TRUE if initialized, FALSE otherwise.
//
// ----------------------------------------------------------------------------
inline BOOL CIPMConvert::fCheckInit()   // RETURNS: BOOL
{
    return (m_lpwszMsgClass && m_lpEnvelope && m_lpStream && m_lpAB);
};

// $--CIPMConvert::HrInitialize-----------------------------------
//
// DESCRIPTION: Initializes conversion class instance
//
// INPUT:   lpwszMsgClass   --  message class
//          lpAddrBook  --  address book pointer
//          lpEnvelope  --  message envelope pointer
//          fTNEFEncode --  TNEF encode attachments flag
//          lpStream    --  Stream to write output to
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      EDK_E_ALREADY_EXISTS if already in use
//                      E_NOTIMPL if not yet implemented
//
// ----------------------------------------------------------------
HRESULT CIPMConvert::HrInitialize(   
    IN LPCWSTR lpwszMsgClass,           // message class
    IN BOOL fTNEFEncode,                // TNEF encode attachments flag
    IN LPADRBOOK lpAddrBook,            // address book pointer
    IN LPMESSAGE lpEnvelope,            // message envelope pointer
    IN LPSTREAM lpStream)               // stream to write output to
{
    HRESULT hr      =   NOERROR;    // return code
    BOOL    fInUse  =   FALSE;      // TRUE if instance is in use

    DEBUGPRIVATE("CIPMConvert::HrInitialize()\n");

    // check input parameters
    hr = CHK_CIPMConvert_HrInitialize(lpwszMsgClass, fTNEFEncode, 
                                      lpAddrBook, lpEnvelope,
                                      lpStream);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // make sure that this instance isn't already in use
    fInUse = fCheckInit();
    
    if ( fInUse )
    {
        hr = HR_LOG(EDK_E_ALREADY_EXISTS);

        goto cleanup;
    }
        
    // Set mesage class, envelope, TNEF, address book 
    // and stream data members
    m_lpwszMsgClass = lpwszMsgClass;
    m_fTNEFEncode = fTNEFEncode;
    m_lpAB = lpAddrBook;
    m_lpEnvelope = lpEnvelope;
    m_lpStream = lpStream;    

    // Determine the report type of the message, if any
    hr = HrSetMsgType(lpwszMsgClass);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

cleanup:

    RETURN(hr);

}

//$--CIPMConvert::HrSetMsgType-------------------------------
//
// DESCRIPTION: Sets a message's type.
//
// INPUT:   lpwszReportClass    --  report class
//
// RETURNS: HRESULT --  NOERROR if successful & is a report.
//                      E_INVALIDARG if bad input
//                            
// -------------------------------------------------------------
HRESULT CIPMConvert::HrSetMsgType(       // RETURNS: HRESULT
        IN LPCWSTR lpwszMsgClass)        // message class
{
    HRESULT         hr                  =   NOERROR;
    LPWSTR          lpwClassCaps        =   NULL;       // upper-case version of class
    
    // Report types supported.
    const LPWSTR    lpwszNDRClass   =   L".NDR";
    const LPWSTR    lpwszDRClass    =   L".DR";
    const LPWSTR    lpwszNRNClass   =   L".IPNNRN";
    const LPWSTR    lpwszRNClass    =   L".IPNRN";

    DEBUGPRIVATE("CIPMConvert::HrSetMsgType()\n");

    // Check input parameters.
    hr = CHK_CIPMConvert_HrSetMsgType(lpwszMsgClass);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Convert the class passed in to upper case.
    lpwClassCaps = CharUpperW((LPWSTR) lpwszMsgClass);

    if ( (lpwClassCaps == NULL) || 
         IsBadStringPtrW(lpwClassCaps, INFINITE) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // See if this is an IPM message.
    if ( wcsstr(lpwClassCaps, IPMENVELOPECLASS) != NULL )
    {
        m_MsgType = mtIPM;  // interpersonal message

        goto cleanup;
    }

    // Check to make sure that we have a report
    if ( wcsstr(lpwClassCaps, IPMREPORTCLASS) == NULL )
    {
        // Not a report or an IPM!
        m_MsgType = mtNone;

        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Have a report.
    // Determine report type based on message class
    if ( wcsstr(lpwClassCaps, lpwszNDRClass) != NULL )
    {
        // non-delivery report
        m_MsgType = mtNDR;

        goto cleanup;
    }

    if ( wcsstr(lpwClassCaps, lpwszDRClass) != NULL )
    {
        // delivery report
        m_MsgType = mtDR;

        goto cleanup;
    }

    if ( wcsstr(lpwClassCaps, lpwszNRNClass) != NULL )
    {
        // non-read notification
        m_MsgType = mtNRN;

        goto cleanup;
    }

    if ( wcsstr(lpwClassCaps, lpwszRNClass) != NULL )
    {
        // read notification
        m_MsgType = mtRN;

        goto cleanup;
    }

    // If we get to here, we have an unrecognized report.
    m_MsgType = mtNone;

    hr = HR_LOG(E_FAIL);

    goto cleanup;

cleanup:

    RETURN(hr);

}

//$--CIPMConvert::HrConvert------------------------------------
//
// DESCRIPTION: Converts a MAPI REPORT.IPM message to a "822-style"
//              stream output.
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_OUTOFMEMORY if memory problems
//                          E_FAIL if API problems
//                          E_NOTIMPL if conversion not supported
//
// ----------------------------------------------------------------
HRESULT CIPMConvert::HrConvert()    // RETURNS: HRESULT
{
    HRESULT hr              =   NOERROR;
    BOOL    fInitialized    =   FALSE;  // TRUE if conversion instance has been initialized

    DEBUGPRIVATE("CIPMConvert::HrConvert()\n");

    // Check to make sure that we have been initialized
    fInitialized = fCheckInit();

    if ( !fInitialized )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Call the appropriate conversion, based on the message
    // class.
    if ( m_MsgType == mtIPM )
    {
        // have an ENVELOPE.IPM.* message
        hr = HrIPMTo822Format();

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }

    else if ( m_MsgType != mtNone )
    {
        // have some kind of supported REPORT.IPM.* message
        hr = HrReportTo822Format();

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }

    else
    {
        // we have something we don't support
        hr = HR_LOG(E_NOTIMPL);

        goto cleanup;
    }

    // Append the TNEFed envelope content and attachments to the
    // stream if this is desired.
    if ( m_fTNEFEncode == TRUE )
    {
        // want to TNEF encode everthing attached to the envelope.
        hr = HrContentToTnef();

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

    }   // end if TNEF encoding desired

    // commit the changes to the output stream.
    hr = m_lpStream->Commit(STGC_DEFAULT);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    // Release and free MAPI objects used for conversion now.  
    // Don't keep them in memory any longer than necessary.  
    // (Also allows for re-use of thread.)
    Reset();

    RETURN(hr);
}    

//$--CIPMConvert::HrIPMto822Format--------------------------------------------------------
//
// DESCRIPTION: Converts a MAPI ENVELOPE.IPM message to a "822-style" stream output
//
// INPUT:       none
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL if API function call failure,
//
// ---------------------------------------------------------------------------

HRESULT CIPMConvert::HrIPMTo822Format()   //  RETURNS:    HRESULT
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPRIVATE("CIPMConvert::HrIPMTo822Format()\n");

    // Convert the message envelope.
    hr = HrConvertEnvelope();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Convert the message.
    hr = HrConvertContent();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Write out each attachment.
    hr = HrConvertAttachments();
    
    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // we are done.

cleanup:
    
    RETURN(hr);
}

//$--CIPMConvert::HrConvertEnvelope--------------------------------------------------------
//
// DESCRIPTION: Handles the MAPI IPM or notification envelope conversion.
//
// INPUT:       none
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL if API function call failure,
//
// ---------------------------------------------------------------------------

HRESULT CIPMConvert::HrConvertEnvelope()   //  RETURNS:    HRESULT
{
    HRESULT     hr              =   NOERROR;        // return code
    ULONG       ulNumRecips     =   0;              // number of recipients
    ULONG       ulCount         =   0;              // loop counter
    LPSRowSet   lpRecipRows     =   NULL;           // envelope's recipient table rows pointer
    ULONG       iProp           =   0;              // property index

    // indices into the envelope property tag array
    const UINT  iClass       =    0;  // index of message class value    
    const UINT  iFromAddr    =    1;  // index of sender address
    const UINT  iXID         =    2;  // index of X-message identifier
    const UINT  iTrace       =    3;  // index of external trace information
    const UINT  iIntTrace    =    4;  // index of internal trace information

    const ULONG nEnvProps    =    5;  // number of envelope properties to retrieve

    // property values needed for the envelope
    SizedSPropTagArray(nEnvProps, sPropTagArray) =
    {
        nEnvProps,  // number of properties
        {
            PR_MESSAGE_CLASS,       // envelope message class, index iClass
            PR_ORIGINATOR_ADDR,     // envelope sender's email address, index iFromAddr
            PR_MESSAGE_SUBMISSION_ID,	// content's X-Message-ID
            PR_TRACE_INFO,          // external trace information
			PR_INTERNAL_TRACE_INFO, // internal trace information
        }
    };

    // indices into the recipient addresses property values array
    const UINT  iRecipient  =   0;  // PR_EMAIL_ADDRESS
    const UINT  iType       =   1;  

    const ULONG nRecipProps =   2;  // number of recipient properties

    // property columns needed from the envelope's recipient table
    SizedSPropTagArray(nRecipProps, sRecipProps) =
    {
        nRecipProps,  // number of columns (properties)
        {
            PR_EMAIL_ADDRESS,       // recipient Email address
            PR_RECIPIENT_TYPE       // recipient address type
        }
    };

    DEBUGPRIVATE("HrConvertEnvelope()\n");

    // Retrieve all of the properties which we need for the
    // envelope now (currently, there are two.)
    hr = HrRetrieveProps(m_lpEnvelope, 
                         (LPSPropTagArray) &sPropTagArray,
                         &m_lpEnvProps);

    // It's O.K. if we cannot retrieve the trace information property.
    if ( hr == EDK_E_NOT_FOUND )
    {
        for ( iProp = 0; iProp < nEnvProps; iProp++ )
        {
            if ( PROP_TYPE(m_lpEnvProps[iProp].ulPropTag) == PT_ERROR )
            {
                if ( iProp == iTrace )
                {
                    // Not finding external trace information is not fatal.
                    hr = HR_LOG(NOERROR);
                }

                else if ( iProp == iIntTrace )
                {
                    // Not finding internal trace information is not fatal.
                    hr = HR_LOG(NOERROR);
                }

                else
                {
                    // some other, unexpected error.
                    hr = HR_LOG(E_FAIL);

                    goto cleanup;
                }

            }   // end if found a property problem
        }   // end for each property tag
    }   // end if one or more properties not found

    // check for other failures
    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Print out the name of the TNEF data file, if any.
    // (Note: If we are doing TNEF encoding, the name of the attached
    // TNEF data is always MAPIMAIL.DAT.)
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

    // Build and emit the "RCPT TO" line for each recipient.
    // First, Retrieve the envelope's recipient table rows.
    hr = HrGetRecipientList(
                m_lpEnvelope,       // MAPI message envelope pointer
                (LPSPropTagArray) &sRecipProps, // array of property columns to retrieve
                &lpRecipRows);      // pointer to recipient array pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Find and print out each MAPI_TO recipient
    ulNumRecips = 0;    // initialize number of "TO" recipients.
    for ( ulCount = 0; ulCount < lpRecipRows->cRows; ulCount++ )
    {
        if ( lpRecipRows->aRow[ulCount].lpProps[iType].Value.ul ==
             MAPI_TO )
        {
            // found a "RCPT TO" recipient
            ulNumRecips++;  // increment count

            hr = HrEmitTagDataLine(
                lpszTagRcptTo,      // tag
                lpRecipRows->aRow[ulCount].lpProps[iRecipient].Value.LPSZ,  // data
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if found a to recipient
    }   // end for MAPI_TO recipients

    // There had better be at least one "RCPT TO" recipient!
    if ( ulNumRecips == 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Emit the "DATA:" marker
    hr = m_lpStream->Write(
                lpszTagData,        // data
                lstrlen(lpszTagData) * sizeof(TCHAR), // length (no terminator)
                NULL);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // We are done.

cleanup:

    // Free structures
    FREEPROWS(lpRecipRows);
    
    RETURN(hr);

}

//$--CIPMConvert::HrConvertContent--------------------------------------------------------
//
// DESCRIPTION: Handles the MAPI IPM envelope content (original mesage) conversion.
//
// INPUT:       none
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL if API function call failure,
//
// ---------------------------------------------------------------------------

HRESULT CIPMConvert::HrConvertContent()   //  RETURNS:    HRESULT
{
    HRESULT         hr              =   NOERROR;        // return code
    LPTSTR          lpTempString    =   NULL;   // data string
    ULONG           ulCount         =   0;      // temporary count variable
    ULONG           ulNumRecips     =   0;      // number of recipients
    LPSRowSet       lpRecipRows     =   NULL;   // content's recipient table rows pointer
    LPTRACEINFO     lpTraceInfo     =   NULL;   // external trace information
    LPTRACEENTRY    lpTraceEntry    =   NULL;   // external trace entry
    PINTTRACEINFO   lpIntTraceInfo  =   NULL;   // internal trace information
    PINTTRACEENTRY  lpIntTraceEntry =   NULL;   // internal trace entry
    ULONG           cbBodyText      =   0;      // # bytes in body text
    LPSTREAM        lpTextBody      =   NULL;   // ANSI text body stream
    BOOL            fBody           =   TRUE;   // FALSE if no body text
    ULARGE_INTEGER  scbStream       =   {0};    // # bytes to copy
    LARGE_INTEGER   sOffsetZero     =   {0};    // zero offset
    ULONG           iProp           =   0;      // index into property value array
    BOOL            fPriority       =   TRUE;   // FALSE if message has no priority

    // temporary file name buffer
    TCHAR           szFileName[MAX_PATH + 1]    =   TEXT(".\\");

    // temporary string buffer
    TCHAR           szTempBuf[ulMaxOutStringLen + 1]   =   TEXT("");

    // temporary file name prefix
    const LPTSTR    szPrefix    =   TEXT("CNV");

    // indices into content properties
    const UINT  iClass       =    0;  // index of message class value    
    const UINT  iFromAddr    =    1;  // index of sender address
    const UINT  iXID         =    2;  // index of X-message identifier
    const UINT  iSentTime    =    3;  // index of sent time value
    const UINT  iImportance  =    4;  // index of importance value
    const UINT  iPriority    =    5;  // index of priority value
    const UINT  iSubject     =    6;  // index of the subject value

    const ULONG nCntProps    =    7;  // # of message content properties

    // property values needed for the message content
    SizedSPropTagArray(nCntProps, sPropTagArray) =
    {
        nCntProps,  // number of properties
        {
            PR_MESSAGE_CLASS,       // content's message class, index iClass
            PR_SENDER_EMAIL_ADDRESS,// content's sender's email address, index iFromAddr
            PR_SEARCH_KEY,          // dummy--acutally use PR_MESSAGE_SUBMISSION_ID on from
                                    // the envelope
            PR_CLIENT_SUBMIT_TIME,  // content's sent time, index iSentTime
            PR_IMPORTANCE,          // content's importance value, index iImportance
            PR_PRIORITY,            // content's priority value, index iPriority
            PR_SUBJECT              // content's subject, index iSubject
        }
    };

    // indices needed from envelope properties array
    const UINT  iTrace       =    3;  // index of external trace information
    const UINT  iIntTrace    =    4;  // index of internal trace information

    // indices into the recipient addresses property values array
    const UINT  iRecipient  =   0;  // PR_EMAIL_ADDRESS
    const UINT  iType       =   1;  // PR_RECIPIENT_TYPE

    const ULONG nRecipProps =   2;  // # of recipient properties

    // property columns needed from the content's recipient table
    SizedSPropTagArray(nRecipProps, sRecipProps) =
    {
        nRecipProps,  // number of columns (properties)
        {
            PR_EMAIL_ADDRESS,       // recipient Email address
            PR_RECIPIENT_TYPE       // recipient address type
        }
    };

    // "Spread" between importance values and their corresponding 
    // priority values
    const ULONG nPriorityImportanceSpread   =   1;

    DEBUGPRIVATE("CIPMConvert::HrConvertContent()\n");

    // Open the envelope's content
    hr = HrOpenContent();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Retrieve and store the content properties needed.
    hr = HrRetrieveProps(m_lpContent,
                         (LPSPropTagArray) &sPropTagArray,
                         &m_lpCntProps);

    // The PR_PRIORITY property may not be available for Schedule+
    // "ENVELOPE.IPM.Schedule.Meeting.Request" messages.
    if ( hr == EDK_E_NOT_FOUND )
    {
        for ( iProp == 0; iProp < sPropTagArray.cValues; iProp++ )
        {
            if ( PROP_TYPE(m_lpCntProps[iProp].ulPropTag) == PT_ERROR )
            {
                if ( iProp == iPriority )   // no PR_PRIORITY property
                {
                    // This isn't an error for some types of IPM
                    // messages.  Merely compute the priority from
                    // the importance.
                    fPriority = FALSE;  // message has no priority

                    hr = HR_LOG(NOERROR);
                }

                else    // some other error
                {
                    hr = HR_LOG(E_FAIL);

                    goto cleanup;
                }
            }   // end if found bad property tag
        }   // end for
    }   // end if property not found

    if ( FAILED(hr) )
    {
        // general error case
        goto cleanup;
    }

    // Print out the "X-Message-Class:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
                    lpszTagMsgClass, 
                    m_lpCntProps[iClass].Value.LPSZ,
                    m_lpStream);

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
    // The X message ID is already null-terminated.
    hr = HrEmitTagDataLine(
                lpszTagMsgID, 
                (LPTSTR) m_lpEnvProps[iXID].Value.bin.lpb,  // really a null-terminated string
                m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build the trace information string, if any.
    if ( PROP_TYPE(m_lpEnvProps[iTrace].ulPropTag) != PT_ERROR )
    {
        // have valid trace information
        lpTraceInfo = (LPTRACEINFO) (m_lpEnvProps[iTrace].Value.bin.lpb);

        // Print out trace information data
        // Note:  It's O.K. for there to be no trace information
        // on NDR's just created by the gateway.
        for ( ulCount = 0; ulCount < lpTraceInfo->cEntries; ulCount++ )
        {
            // retrieve trace entry.
            lpTraceEntry = &(lpTraceInfo->rgtraceentry[ulCount]);

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

        }   // end for trace entries
    }   // end if any trace information

    // Build the internal trace information string, if any.
    if ( PROP_TYPE(m_lpEnvProps[iIntTrace].ulPropTag) != PT_ERROR )
    {
        // have valid trace information
        lpIntTraceInfo = (PINTTRACEINFO) (m_lpEnvProps[iIntTrace].Value.bin.lpb);

        // Print out trace information data
        // Note:  It's O.K. for there to be no trace information
        // on NDR's just created by the gateway.
        for ( ulCount = 0; ulCount < lpIntTraceInfo->cEntries; ulCount++ )
        {
            // retrieve trace entry.
            lpIntTraceEntry = &(lpIntTraceInfo->rgIntTraceEntry[ulCount]);

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
                lpIntTraceEntry->rgchMTAName,      // MTA name
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

        }   // end for trace entries
    }   // end if any trace information

    // Print out the "From:" tag and data line to the stream.
    hr = HrEmitTagDataLine(
        lpszTagFrom,     // tag
        m_lpCntProps[iFromAddr].Value.LPSZ,    // PR_SENDER_EMAIL_ADDRESS property value
        m_lpStream);                // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Get the recipients from the recipient table's rows.
    hr = HrGetRecipientList(
                m_lpContent,        // message content pointer
                (LPSPropTagArray) &sRecipProps, // columns/properties desired
                &lpRecipRows);      // pointer to recipient table row pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Find and print out the MAPI_TO recipients.
    ulNumRecips = 0;    // initialize count of to recipients
    for ( ulCount = 0; ulCount < lpRecipRows->cRows; ulCount++ )
    {
        if ( lpRecipRows->aRow[ulCount].lpProps[iType].Value.ul == 
             MAPI_TO )
        {
            // found a "TO" recipient
            ulNumRecips++;  // increment count

            // Print out "TO" tag and data line
            hr = HrEmitTagDataLine(
                lpszTagTo,          // tag
                lpRecipRows->aRow[ulCount].lpProps[iRecipient].Value.LPSZ, // data
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if found a to recipient
    }   // end for

    // It is O.K. for an IPM message content to have no "To" recipients.
    // (The envelope, however, must have "RCPT TO" recipients

    // Find and print out the MAPI_CC recipients.
    for ( ulCount = 0; ulCount < lpRecipRows->cRows; ulCount++ )
    {
        if ( lpRecipRows->aRow[ulCount].lpProps[iType].Value.ul == 
             MAPI_CC )
        {
            // found a "CC" recipient
            // Print out "CC" tag and data line
            hr = HrEmitTagDataLine(
                lpszTagCC,          // tag
                lpRecipRows->aRow[ulCount].lpProps[iRecipient].Value.LPSZ, // data
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if found a cc recipient
    }   // end for

    // find and print out BCC recipients
    for ( ulCount = 0; ulCount < lpRecipRows->cRows; ulCount++ )
    {
        if ( lpRecipRows->aRow[ulCount].lpProps[iType].Value.ul == 
             MAPI_BCC )
        {
            // found a "BCC" recipient
            // Print out "BCC" tag and data line
            hr = HrEmitTagDataLine(
                lpszTagBCC,          // tag
                lpRecipRows->aRow[ulCount].lpProps[iRecipient].Value.LPSZ, // data
                m_lpStream);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if found a bcc recipient
    }   // end for

    // Print out a blank line
    hr = m_lpStream->Write(
            lpszNewLine,        // data
            lstrlen(lpszNewLine) * sizeof(TCHAR),   // length (no terminator)
            NULL);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Print out the "Subject:" tag and data line to the stream
    hr = HrEmitTagDataLine(
            lpszTagSubject,
            m_lpCntProps[iSubject].Value.LPSZ,  // PR_SUBJECT property value
            m_lpStream);                    // stream

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Build priority string.
    // First, check to see if a priority was assigned.
    if ( fPriority == FALSE )
    {
        // Set the priority based on the message's importance.
        m_lpCntProps[iPriority].Value.ul =
            m_lpCntProps[iImportance].Value.ul - nPriorityImportanceSpread;

    }   // end if no priority

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

    // Write the ANSI body text header and data information
    // to the stream.
    // This means that we must first convert the compressed
    // rich text format body to ANSI.

    // Create a temporary, buffered stream to hold the ANSI text.
    hr = OpenStreamOnFile(
        MAPIAllocateBuffer,     // allocation routine
        MAPIFreeBuffer,         // deallocation routine
        STGM_READWRITE | STGM_CREATE | SOF_UNIQUEFILENAME | 
        STGM_DELETEONRELEASE | STGM_SHARE_EXCLUSIVE,   // interface flags
        szFileName,             // temporary file name
        szPrefix,               // file prefix
        &lpTextBody);           // stream pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(!FBadUnknown(lpTextBody), "Bad lpTextBody");

    // Convert the RTF compressed stream data to ANSI text
    // data.
    hr = HrRTFCompressedToText(
                    m_lpContent,        // MAPI message pointer
                    lpTextBody,         // stream to copy ANSI text to
					0,					// use current code page
                    &cbBodyText);       // # bytes copied to stream

    // It is O.K. for there to be no RTF body text  
	// (Note:  The MAPI error code MAPI_E_NOT_FOUND is returned in this
	// case.)
    if ( hr == MAPI_E_NOT_FOUND )
    {
        // no message body
        fBody = FALSE;

        // not an error
        hr = HR_LOG(NOERROR);
    }

    // Test for other errors
    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    ASSERTERROR(!FBadUnknown(lpTextBody), "Bad lpTextBody.");

    // Format the number of bytes in the message body data.
    wsprintf(
            szTempBuf,      // buffer
            TEXT("%ld"),    // format string
            cbBodyText);    // data length (in bytes)

    // Emit the body text "----beginbody" tag and data.
    hr = HrEmitTagDataLine(
            lpszTagBodyHdr,     // tag
            szTempBuf,          // data
            m_lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    if ( fBody == TRUE )    // There is body text
    {
        // Go back to the begging of the ANSI body text
        // source stream.
        hr = lpTextBody->Seek(
                    sOffsetZero,        // 0 offset
                    STREAM_SEEK_SET,    // from beginning
                    NULL);              // don't care

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Copy all the ANSI body text to the output stream
        scbStream.LowPart = cbBodyText;  // # bytes to copy
        hr = lpTextBody->CopyTo(
                    m_lpStream, // output stream pointer
                    scbStream,  // # bytes to copy
                    NULL,       // don't care
                    NULL);      // don't care

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

    }   // end if body

    // Emit the body text footer.
    hr = m_lpStream->Write(
            lpszTagBodyEnd,         // data
            lstrlen(lpszTagBodyEnd) * sizeof(TCHAR), // data length (no terminator)
            NULL);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // We are done.

cleanup:

    // Release MAPI and OLE objects
    ULRELEASE(lpTextBody);      // Deletes temporary file as a side-effect

    // Free buffers
    MAPIFREEBUFFER(lpTempString);

    FREEPROWS(lpRecipRows);

    RETURN(hr);

}

//$--CIPMConvert::HrConvertAttachments--------------------------------------------------------
//
// DESCRIPTION: Handles the MAPI IPM original message attachments conversion.
//
// INPUT:       none
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL if API function call failure,
//
// ---------------------------------------------------------------------------

HRESULT CIPMConvert::HrConvertAttachments()   //  RETURNS:    HRESULT
{
    HRESULT         			hr              =   NOERROR;
    LPMAPITABLE     			lpTable         =   NULL;   // attachments table pointer
    LPSRowSet       			lpRows          =   NULL;   // table rows
    ULONG           			iLoopCounter    =   0;      // loop counter index
    LPATTACH        			lpAttachment    =   NULL;   // message attachment pointer
    ULONG           			nProps          =   0;      // # of properties
    LPSPropValue    			lpPropVals      =   NULL;   // property value array pointer
    LPTSTR          			lpFileName      =   NULL;   // file name pointer
    ULONG           			cbAttachSize    =   0;      // # bytes in attachment
    PVIRTUALSTREAMONPROPERTY	lpStreamAtData  =   NULL;   // buffered attachment data stream
	STATSTG						sStatStg		=	{0};	// stream statistics

    // temporary string buffer
    TCHAR           szTempBuffer[ulMaxOutStringLen + 1] =   TEXT("");
    // Attachment header buffer
    TCHAR           szAttachHdr[ulMaxOutStringLen + 1]  =   TEXT("");

    // property tag array for attachment number
    SizedSPropTagArray(1, sPropAttachNum)   =   
    {
        1,  // one property
        {
            PR_ATTACH_NUM   // property tag
        }
    };

    // indices into the property value array
    const UINT  iAttachMethod   =   0;
    const UINT  iFileName       =   1;

    const ULONG nAttachProps    =   2;  // # of attachment properties

    // properties to retrieve per attachment
    SizedSPropTagArray(nAttachProps, sAttachPropTags) =  
    {
        nAttachProps,      // number of properties to retrieve
        {
            PR_ATTACH_METHOD,       // attachment "type"
            PR_ATTACH_FILENAME      // attachment 8.3 file name
        }
    };

    DEBUGPRIVATE("CIPMConvert::HrConvertAttachments()\n");

    // Handle the attachment for the message contents.
    // First open the attachments table.
    hr = m_lpContent->GetAttachmentTable(MAPI_DEFERRED_ERRORS, &lpTable);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERT_IUNKNOWN_PTR(lpTable, "Bad lpTable");

    // Retrieve the desired rows.
    // (HrQueryAllRows does a SetColumns for us)
    hr = HrQueryAllRows(lpTable,        // MAPI table pointer
                        (LPSPropTagArray) &sPropAttachNum,  // columns to retrieve
                        NULL,           // restriction pointer
                        NULL,           // order set pointer
                        0,              // max rows, defaults to all    
                        &lpRows);       // pointer to row array pointer

    if ( FAILED(hr) || (hr == MAPI_W_POSITION_CHANGED) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup; 

    }

    ASSERT_READ_PTR(lpRows, sizeof(SRowSet), "Bad lpRows");

    // handle each attachment
    for ( iLoopCounter = 0; iLoopCounter < lpRows->cRows; iLoopCounter++ )
    {
        // Release objects from previous iteration
        ULRELEASE(lpAttachment);
        ULRELEASE(lpStreamAtData);

        // Free MAPI memory from previous iteration.
        MAPIFREEBUFFER(lpPropVals);

        // Open the attachment
        hr = m_lpContent->OpenAttach(
            lpRows->aRow[iLoopCounter].lpProps[0].Value.ul,  // attachment #
            &IID_IAttachment,    // interface 
            MAPI_DEFERRED_ERRORS, // reduces RPCs
            &lpAttachment);

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Get the desired properties for this attachment.

        // Notes:
        // If the attachment is not a binary attachment, this function may fail, 
        // because the PR_ATTACH_FILENAME property won't be there.
        hr = lpAttachment->GetProps(
                            (LPSPropTagArray) &sAttachPropTags,   // property tags
                            fMapiUnicode,   // flags                                
                            &nProps,        // number of properties
                            &lpPropVals);   // pointer to property value arrray

        ASSERTERROR(nProps == sAttachPropTags.cValues,
                    "Bad nProps");
        ASSERTERROR(!IsBadReadPtr(lpPropVals, sizeof(SPropValue) * nProps),
                    "Bad lpPropVals");

        if ( hr == MAPI_W_ERRORS_RETURNED )
        {
            // Not an error if the PR_ATTACH_FILENAME property
            // doesn't exist.  (This just isn't a binary attachment!)
            if ( (PROP_TYPE(lpPropVals[iFileName].ulPropTag) == PT_ERROR) &&
                 (lpPropVals[iFileName].Value.l == MAPI_E_NOT_FOUND) )
            {
                // We have a non-binary attachment.
                // This is not really an error.  
                // We just drop this attachment and
                // continue with the next.
                hr = HR_LOG(NOERROR);

                continue;
            }
        }   // end if problems getting binary attachment properties

        if ( FAILED(hr) || ( hr == MAPI_W_ERRORS_RETURNED) )
        {
            // If things are O.K., hr should be NOERROR now.
            // general failure
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Determine if this attachment is a binary attachment 
        // (i.e. if it has binary data in the PR_ATTACH_DATA_BIN
        // property).  The only types of attachments which we
        // handle are binary attachments (PR_ATTACH_METHOD == ATTACH_BY_VALUE).  
        // All unresolved,
        // OLE and embedded message attachments will be dropped.
        if ( lpPropVals[iAttachMethod].Value.l != ATTACH_BY_VALUE )
        {
            // We don't have a resolved, binary attachment.
            // Just drop this attachment and continue.
            continue;

        }   // end if not a resolved, binary attachment

        // Open a buffered stream on the binary attachment data property.
		hr = HrOpenVirtualStreamOnProperty(
			lpAttachment,			// MAPI property object pointer
            PR_ATTACH_DATA_BIN, 	// binary attachment
            MAPI_DEFERRED_ERRORS,   // flags (reduces RPCs)
            &lpStreamAtData); 		// buffered stream pointer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERT_IUNKNOWN_PTR(lpStreamAtData, "Bad lpStreamAtData");

        // Determine the number of bytes of binary attachment
        // data.
        hr = lpStreamAtData->Stat(
			&sStatStg,			// stream statistics structure pointer
			STATFLAG_NONAME);	// statistics flags

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // See if data is too long for us to handle
        if ( sStatStg.cbSize.HighPart != 0 )
        {
            hr = HR_LOG(E_NOTIMPL);

            goto cleanup;
        }

        cbAttachSize = sStatStg.cbSize.LowPart;    // # bytes of data

        // Make sure that the file name isn't NULL.
        lpFileName = lpPropVals[iFileName].Value.LPSZ;
        if ( (lpFileName == NULL) || (*lpFileName == 0) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Create the attachment header from the attachment
        // file name and the # bytes in the attachment.
        //
        // Format:   FileName:#bytes
        //
        // e.g.      FILE1.TMP:54
        lstrcpy(szAttachHdr, lpFileName);
        AddColon(szAttachHdr);   
        lstrcat(szAttachHdr, _ultoa(cbAttachSize, szTempBuffer, 10));
                
        // Emit the attachments "----beginattach" tag and data line
        hr = HrEmitTagDataLine(
                    lpszTagAttachHdr, 
                    szAttachHdr, 
                    m_lpStream);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Copy the binary attachment data from the input
        // stream to the output stream.
        hr = lpStreamAtData->CopyTo(
            m_lpStream,     	// destination stream
            sStatStg.cbSize,    // number of bytes to copy
            NULL,           	// don't care
            NULL);          	// don't care
                        
        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Emit the attachment's footer "----endattach" text.
        hr = m_lpStream->Write(
                lpszTagAttachEnd,           // data
                lstrlen(lpszTagAttachEnd) * sizeof(TCHAR),// length (no terminator)
                NULL);

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // We are done with this attachment.  Do the next

    }   // end for

cleanup:

    // Free all MAPI structures
    FREEPROWS(lpRows);
    MAPIFREEBUFFER(lpPropVals);

    // Release all MAPI  object
    ULRELEASE(lpTable);
    ULRELEASE(lpAttachment);
    ULRELEASE(lpStreamAtData);

    RETURN(hr);

}

//$--CIPMConvert::HrRetrieveProps--------------------------------
//
// DESCRIPTION: Retrieves and stores properties desired on specified object
//
// INPUT:       lpObject    --  pointer to message object
//              lpPropTags  --  property tag array pointer
//
//
// OUTPUT:      lppPropVals --  pointer to property value array pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          EDK_E_NOT_FOUND if one or more
//                          properties not found,
//                          E_FAIL otherwise
//
// -------------------------------------------------------------
HRESULT CIPMConvert::HrRetrieveProps(       // RETURNS: HRESULT
    IN LPMAPIPROP lpObj,                    // MAPI object pointer
    IN LPSPropTagArray lpPropTags,          // counted property tag array pointer
    OUT LPSPropValue * lppPropVals)     // pointer to property value array pointer
{
    HRESULT hr      =   NOERROR;
    ULONG   ulCount =   0;      // count of properties retrieved

    DEBUGPRIVATE("CIPMConvert::HrRetrieveProps()\n");

    // check input parameters
    hr = CHK_CIPMConvert_HrRetrieveProps(lpObj, lpPropTags, 
                                         lppPropVals);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    hr = lpObj->GetProps(lpPropTags,    // properties to retrieve
                         fMapiUnicode,  // flags
                         &ulCount,      // number of properties retrieved
                         lppPropVals);  // array of property values

    switch ( hr )
    {
        case MAPI_W_ERRORS_RETURNED:

            hr = HR_LOG(EDK_E_NOT_FOUND);

            goto cleanup;

        default:

            if ( FAILED(hr) || (ulCount != lpPropTags->cValues) )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }
    }   // end switch

    // more consistency checks
    ASSERTERROR(!IsBadReadPtr(lppPropVals, sizeof(LPSPropValue)), 
                "Bad lppPropVals");
    ASSERTERROR(!IsBadReadPtr(*lppPropVals, sizeof(SPropValue) * ulCount), 
                "Bad *lppPropVals");

cleanup:

    RETURN(hr);

}

//$--CIPMConvert::Reset----------------------------------------
//
// DESCRIPTION: resets all of the conversion class' data members
//              and frees all MAPI memory allocated by the class.
//              This allow the thread's class instance to be re-used
//              for another conversion (if desired).
//
// INPUT:       none
//
// RETURNS:     VOID
//
// ----------------------------------------------------------------
VOID CIPMConvert::Reset()        // RETURNS: VOID
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPRIVATE("CIPMConvert::Reset()\n");

    // Reset all of the conversion class' data members.
    // This allows the class instance to be re-used by this
    // thread (Also frees MAPI memory).
    m_lpwszMsgClass = NULL;
    m_fTNEFEncode = FALSE;
    m_lpAB = NULL;
    m_lpEnvelope = NULL;
    m_lpStream = NULL;
    m_MsgType = mtNone;

    // Release OLE objects
    ULRELEASE(m_lpContent);
    ULRELEASE(m_lpAttach);

    MAPIFREEBUFFER(m_lpEnvProps);
    MAPIFREEBUFFER(m_lpCntProps);

    return;

}
