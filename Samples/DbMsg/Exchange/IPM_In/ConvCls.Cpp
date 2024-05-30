// --convcls.cpp--------------------------------------------------------------
//
// IPM to 822 conversion class source file.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include "edk.h"
#include "msgemit.h"
#include "tagnames.h"   
#include "convcls.h"
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
    m_lpwszMsgClass =   NULL;
    m_lpStream = NULL;
    m_lpEnvelope = NULL;
    m_lpContent = NULL;
    m_lpAttach = NULL;
    m_fTNEFEncode = FALSE;
    m_lpszAddrType = NULL;
    m_lpAB = NULL;
    m_MsgType = mtNone;

    ZeroMemory(m_rgszData, sizeof(m_rgszData));

    m_lpRcptToList = NULL;
    m_lpContentRecips = NULL;
    m_lpReportToList = NULL;

    m_lpTraceInfo = NULL;
    m_lpIntTraceInfo = NULL;

	ZeroMemory( &m_sOffsetHeaders, sizeof( ULARGE_INTEGER));
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

    // Free up all memory allocated for this object
    Reset();
}

//$--CIPMConvert::HrInitialize-----------------------------------
//
// DESCRIPTION: Initializes conversion class instance
//
// INPUT:   lpwszMsgClass   --  message class
//          fTNEFEncode --  TNEF encode attachments flag
//          lpszAddrType--  address type
//          lpAddrBook  --  address book pointer
//          lpEnvelope  --  message envelope pointer
//          lpStream    --  stream pointer
// 
// NOTE:    The strings passed in as inputs are NOT duplicated.
//          Thus, they must stay around for the life of the
//          conversion.
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      EDK_E_ALREADY_EXISTS if already in use
//
// ----------------------------------------------------------------
HRESULT CIPMConvert::HrInitialize(      // RETURNS: HRESULT
    IN LPCWSTR lpwszMsgClass,           // message class
    IN BOOL fTNEFEncode,                // TNEF encode attachments flag
    IN LPCTSTR lpszAddrType,            // address type
    IN LPADRBOOK lpAddrBook,            // address book pointer
    IN LPMESSAGE lpEnvelope,            // message envelope pointer
    IN LPSTREAM lpStream)               // stream to write output to
{
    HRESULT hr      =   NOERROR;    // return code
    BOOL    fInUse  =   FALSE;      // TRUE if instance is in use

    DEBUGPRIVATE("CIPMConvert::HrInitialize()\n");

    // check input parameters
    hr = CHK_CIPMConvert_HrInitialize(lpwszMsgClass, fTNEFEncode,
                                      lpszAddrType, lpAddrBook,
                                      lpEnvelope, lpStream);

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
        
    // Set mesage class, envelope, TNEF, environment
    // and stream data members
    m_lpwszMsgClass = lpwszMsgClass;
    m_fTNEFEncode = fTNEFEncode;
    m_lpszAddrType = lpszAddrType;
    m_lpAB = lpAddrBook;
    m_lpEnvelope = lpEnvelope;
    m_lpStream = lpStream;    
    
cleanup:

    RETURN(hr);

}

//$--CIPMConvert::HrConvert------------------------------------
//
// DESCRIPTION: Converts an "822-style" header to
//              a MAPI IPM message
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
    ULONG   nRecipients     =   0;      // # of [non]delivery recipients

    DEBUGPRIVATE("CIPMConvert::HrConvert()\n");

    // Check to make sure that we have been initialized
    fInitialized = fCheckInit();

    if ( !fInitialized )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Parse message envelope and content common to
    // all message types and save the data.
    hr = HrParseEnvelopeAndContent();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Do processing which is specific to each message type.
    switch ( m_MsgType )
    {
        case mtIPM:     // interpersonal message

            // Create the message content container
            // This must be called before HrParseIPMSpecific().
            hr = HrCreateContent();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Parse message body.
            hr = HrParseIPMSpecific();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Parse file attachments.
            hr = HrParseAttachments();
            
            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // set content properties
            hr = HrSetContentProps();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // If we are doing TNEF decoding, let TNEF decode the
            // content properties.
            if ( m_fTNEFEncode == TRUE )
            {
                hr = HrTnefToContent();

                if ( FAILED(hr) )
                {
                    goto cleanup;
                }

            }   // end if doing TNEF decoding

            // Set envelope properties
            hr = HrSetEnvelopeProps();
            
            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // done with IPM
            break;

        case mtNDR:     // non-delivery report            
        case mtDR:      // delivery report
                    
            // Parse [non]recipient information
            hr = HrParseReportSpecific(
                        &nRecipients);  // # of [non]delivery recipients

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // A [non]delivery report must have at least one
            // recipient.
            if ( nRecipients < 1 )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            // If we are doing TNEF decoding, let TNEF decode the
            // content properties.
            if ( m_fTNEFEncode == TRUE )
            {
                hr = HrTnefToContent();

                if ( FAILED(hr) )
                {
                    goto cleanup;
                }

            }   // end if doing TNEF decoding

            // Set report properties.
            hr = HrSetReportProps();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // done with NDR or DR

            break;

        case mtNRN:
        case mtRN:
            // read/non-read notifications

            // Parse notification-specific data
            hr = HrParseNotificationSpecific();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Create the notification content container
            hr = HrCreateContent();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // If we are doing TNEF decoding, let TNEF decode the
            // content properties.
            if ( m_fTNEFEncode == TRUE )
            {
                hr = HrTnefToContent();

                if ( FAILED(hr) )
                {
                    goto cleanup;
                }

            }   // end if doing TNEF decoding

            // Set envelope properties
            hr = HrSetEnvelopeProps();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Set notification's content properties.
            hr = HrSetNotifyCntProps();

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Done with [non]read notification.

            break;

        default:
            // shouldn't happen
            hr = HR_LOG(E_FAIL);

            goto cleanup;
            
    }   // end switch

    // save the changes to the output message.
    hr = m_lpEnvelope->SaveChanges(
                KEEP_OPEN_READWRITE);       // we don't own envelope pointer

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

//$--CIPMConvert::HrParseAttachments------------------------------------------
//
// DESCRIPTION: Handle parsing & creation of binary file attachments
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseAttachments()
{
    HRESULT hr  =   NOERROR;

    DEBUGPRIVATE("CIPMConvert::HrParseAttachments()\n");

    // consistency checking
    ASSERTERROR(m_MsgType == mtIPM, "Bad m_MsgType");

    // Parse a binary file attachment at a time (if any)
    //  & create the attachment & its properties
    while ( TRUE )
    {
        hr = HrCreateNextAttachment();

        // Check to see if we have no more attachments.
        // This happens when we reach the end of the file
        // or when we hit the beginning of TNEFed data.
        if ( (hr == EDK_E_END_OF_FILE) ||
             ( (hr == EDK_E_NOT_FOUND) && (m_fTNEFEncode == TRUE) ) )
        {
            hr = NOERROR;       // not really an error

            break;              // get out of this loop
        }

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // parse next attachment

    }   // end while

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
    m_lpEnvelope = NULL;
    m_lpStream = NULL;
    m_fTNEFEncode = FALSE;
    m_lpszAddrType = NULL;
    m_lpAB = NULL;
    m_MsgType = mtNone;
	
	ZeroMemory( &m_sOffsetHeaders, sizeof(ULARGE_INTEGER));

    ULRELEASE(m_lpContent);
    ULRELEASE(m_lpAttach);

    // Free the data string member array
    (VOID)HrFreeData();

    // Free the address lists
    FREEPADRLIST(m_lpRcptToList);
    FREEPADRLIST(m_lpContentRecips);
    FREEPADRLIST(m_lpReportToList);
    
    // Free the trace entry list
    // Note: Trace information list is allocated as one big
    // block, so it can be deallocated with MAPIFREEBUFFER.
    MAPIFREEBUFFER(m_lpTraceInfo);

    // Free the internal trace entry list
    // Note: Internal trace information list is allocated as one big
    // block, so it can be deallocated with MAPIFREEBUFFER.
    MAPIFREEBUFFER(m_lpIntTraceInfo);

    return;

}

//$--CIPMConvert::FreeData----------------------------------------------------
//
// DESCRIPTION: Frees the memory used by the data string array member
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise
//
// ----------------------------------------------------------------------------
VOID CIPMConvert::HrFreeData()      // RETURNS: VOID
{
    UINT    iEntry  =   0;          // data entry index

    DEBUGPRIVATE("CIPMConvert::HrFreeData()\n");

    // Free all allocated data string entries
    for ( iEntry = 0; iEntry < nDataEntries; iEntry++ )
    {
        MAPIFREEBUFFER(m_rgszData[iEntry]);

    }   // end for

    return;

}

//$--CIPMConvert::HrParseEnvelopeAndContent-----------------------------------
//
// DESCRIPTION: Read 822-style envelope and common content text
//              from stream and saves data read
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_OUTOFMEMORY if memory problems
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseEnvelopeAndContent()
{
    HRESULT     hr      =   NOERROR;
    LPTSTR      lpTag   =   NULL;       // pointer to tag string
    LPTSTR      lpData  =   NULL;       // pointer to data string
    BOOL        fFound  =   FALSE;      // TRUE if tag is found
    ULONG       nRecips =   0;          // number of recipients
    ULONG       nTraces =   0;          // number of trace entries
    ULONG       nIntTraces = 0;         // number of internal trace entries
    ULONG       cbRead  =   0;          // number bytes read

    // temporary string buffer
    TCHAR       szTempBuffer[ulMaxOutStringLen] =   TEXT("");

    DEBUGPRIVATE("CIPMConvert::HrParseEnvelopeAndContent()\n");

    // consistency checks
    ASSERTERROR(!FBadUnknown(m_lpEnvelope), "Bad m_lpEnvelope");
    ASSERTERROR(!FBadUnknown(m_lpStream), "Bad m_lpStream");

    // Read the first tag and data line from the stream.
    // It should the the "X-Tnef-Attach" tag and data line.
    hr = HrParseTagAndData(
        m_lpStream,     // stream pointer
        &cbRead,        // # bytes read from stream
        &lpTag,         // pointer to tag string
        &lpData);       // poitner to data string

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check the tag read against the tag expected
    if ( lstrcmp(lpTag, lpszTagTnefAttach) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERT_STRING_PTR(lpData, "Bad lpData.");

    // Don't trust the TNEF flag passed in by the caller for inbound
    // conversions.  They may not know whether or not the inbound
    // file contains TNEF data.  (If there is TNEF data in the file,
    // then the X-Tnef-Attach line will have non-null data.  Otherwise,
    // the file doesn't contain TNEF data.)
    if ( *lpData == 0 ) // empty string
    {
        // Since no TNEF data file name, must not be doing
        // TNEF decoding.
        m_fTNEFEncode = FALSE;
    }

    else    // TNEF data file name specified
    {
        // Since TNEF data file name, must be doing TNEF
        // encoding.
        m_fTNEFEncode = TRUE;

        ASSERTERROR(lstrcmp(lpData, lpszTagTnefHdr) == 0, "Bad lpData.");
    }

    // Free tag and data strings
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);
            
    // Read the "MAIL FROM" data line.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                                
                &cbRead,        // number bytes read from stream
                &lpTag,         // pointer to tag string pointer
                &(m_rgszData[iMailFrom]));       // pointer to data string pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that the tag is what we expected.
    if ( lstrcmp(lpTag, lpszTagMailFrom) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Free the tag string
    MAPIFREEBUFFER(lpTag);

    // Read the "RCPT TO" data lines from the stream.
    hr = HrParseRecipients(
                lpszTagRcptTo,      // tag
                MAPI_TO,            // MAPI recipient type
                &m_lpRcptToList,    // target address list
                &nRecips);          // # recipients of type found

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check the number of "RCPT TO" recipients
    if ( nRecips == 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Read the "DATA:" marker from the stream.
    hr = m_lpStream->Read(
                szTempBuffer,           // data buffer
                lstrlen(lpszTagData) * sizeof(TCHAR),  // length (no terminator)
                &cbRead);               // # characters read.
                
    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Check that we have the "DATA" tag
    if ( lstrcmp(szTempBuffer, lpszTagData) != 0 )
    {
        hr = HR_LOG(E_FAIL);
            
        goto cleanup;
    }
        
    // Read the "X-Message-Class" data line from the stream.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iClass]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // check that the tag is what we expect
    if ( lstrcmp(lpTag, lpszTagMsgClass) != 0 )
    {
        // bad tag
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Free the tag
    MAPIFREEBUFFER(lpTag);

    // Set the message type
    hr = HrSetMessageType(m_rgszData[iClass]);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    ASSERTERROR(m_MsgType != mtNone, "Bad m_MsgType");
        
    // Read the "Date" tag and data line.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iDate]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that the tag is what we expect
    if ( lstrcmp(lpTag, lpszTagDate) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    // Free the tag
    MAPIFREEBUFFER(lpTag);

    // Read the "X-Message-ID" tag and data line
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iXID]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that the tag is what we expect
    if ( lstrcmp(lpTag, lpszTagMsgID) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    // Free the tag
    MAPIFREEBUFFER(lpTag);
 
    // If we have a report, read the "X-Message-Subject-ID"
    // tag and data line.
    if ( m_MsgType != mtIPM )
    {
        hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iSubjectXID]));       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Check that the tag is what we expect
        if ( lstrcmp(lpTag, lpszTagSubjectID) != 0 )
        {
            hr = HR_LOG(E_FAIL);
    
            goto cleanup;
        }
    
        // Free the tag
        MAPIFREEBUFFER(lpTag);            

    }   // end if report

    // Read trace data (if any).
    hr = HrParseExternalTraceData(&nTraces);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Read internal trace data (if any).
    hr = HrParseInternalTraceData(&nIntTraces);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Read the FROM tag and data line.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iFrom]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that the tag is what we expect
    if ( lstrcmp(lpTag, lpszTagFrom) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    // Free the tag
    MAPIFREEBUFFER(lpTag);

    // Parse the "To" recipients and store the addresses.
    hr = HrParseRecipients(
                lpszTagTo,              // tag
                MAPI_TO,                // MAPI recipient type
                &m_lpContentRecips,      // target address list
                &nRecips);              // # recipients of type found

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Note:
    // An IPM message content is allowed to have no "To" recipients.
    if ( (m_MsgType != mtIPM) && (nRecips < 1) )
    {
        // Notifications should have a "To" recipient
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Parse the "CC" recipients and store the addresses.
    hr = HrParseRecipients(
                lpszTagCC,              // tag
                MAPI_CC,                // MAPI recipient type
                &m_lpContentRecips,     // target address list
                &nRecips);              // # recipients of type found

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Parse the "BCC" recipients and store the addresses.
    hr = HrParseRecipients(
                lpszTagBCC,             // tag
                MAPI_BCC,               // MAPI recipient type
                &m_lpContentRecips,     // target address list
                &nRecips);              // # recipients of type found

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Read in the blank line which separates the recipients from
    // the subject.
    // First, zero out the temporary array
    ZeroMemory(
                szTempBuffer,       // buffer
                ulMaxOutStringLen);

    hr = m_lpStream->Read(
                szTempBuffer,       // temporary buffer
                lstrlen(lpszNewLine) * sizeof(TCHAR),  // length (no terminator)
                &cbRead);           // number of bytes read

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Check that we read in a new line.
    if ( lstrcmp(szTempBuffer, lpszNewLine) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    // Parse the "Subject" tag and data line.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iSubject]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that the tag is what we expect
    if ( lstrcmp(lpTag, lpszTagSubject) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    // Free the tag
    MAPIFREEBUFFER(lpTag);

    // Parse the "Priority" tag and data line.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iPriority]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that the tag is what we expect
    if ( lstrcmp(lpTag, lpszTagPriority) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    // Free the tag
    MAPIFREEBUFFER(lpTag);

    // Parse the "Importance" tag and data line.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &(m_rgszData[iImportance]));       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that the tag is what we expect
    if ( lstrcmp(lpTag, lpszTagImportance) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }
    
    // Free the tag
    MAPIFREEBUFFER(lpTag);

	// this location marks the end of the headers
	{
		LARGE_INTEGER	sOffsetZero = {0};
		hr = m_lpStream->Seek(
			sOffsetZero,        // offset
			STREAM_SEEK_CUR,    // from current
			&m_sOffsetHeaders);

		if ( FAILED(hr) )
		{
			hr = HR_LOG(E_FAIL);

			goto cleanup;
		}
	}

    // we are done.

cleanup:

    // Free MAPI buffers
    MAPIFREEBUFFER(lpData);
    MAPIFREEBUFFER(lpTag);

    RETURN(hr);
   
}    

//$--CIPMConvert::HrSetMessageType--------------------------------------------
//
// DESCRIPTION: Sets a message's type, based on the message class
//              property.
//
// INPUT:   lpMessageClass  --  message class.
//
// RETURNS: HRESULT --  NOERROR if successful & is a supported message
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise
//                            
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrSetMessageType(
        IN LPTSTR lpszMessageClass)        // message class
{
    HRESULT         hr                  =   NOERROR;

    // upper-case message class
    TCHAR           pszClassCaps[ulMaxOutStringLen] =   TEXT("");

    // Message class supported
    const LPTSTR    lpszIPMClass    =   TEXT("IPM");
    const LPTSTR    lpszReport      =   TEXT("REPORT.");

    // Report types supported.
    const LPTSTR    lpszNDR         =   TEXT(".NDR");
    const LPTSTR    lpszDR          =   TEXT(".DR");
    const LPTSTR    lpszNRN         =   TEXT(".IPNNRN");
    const LPTSTR    lpszRN          =   TEXT(".IPNRN");

    DEBUGPRIVATE("CIPMConvert::HrSetMessageType()\n");

    // Check input parameters.
    hr = CHK_CIPMConvert_HrSetMessageType(lpszMessageClass);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Convert the class passed in to upper case.
    lstrcpyn(pszClassCaps, lpszMessageClass, ulMaxOutStringLen);
    (VOID)CharUpper(pszClassCaps);

    if ( !TEST_STRING_PTR(pszClassCaps) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Make sure that this is an IPM message of some sort.
    if ( _tcsstr(pszClassCaps, lpszIPMClass) == NULL )
    {
        // Message is not of type IPM.
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // See if this is a report.
    if ( _tcsstr(pszClassCaps, lpszReport) != NULL )
    {
        // We have a report.  See what kind it is.
        if ( _tcsstr(pszClassCaps, lpszNDR) != NULL )
        {
            // we have an NDR.
            m_MsgType = mtNDR;

            goto cleanup;
        }

        if ( _tcsstr(pszClassCaps, lpszDR) != NULL )
        {
            // we have a DR.
            m_MsgType = mtDR;

            goto cleanup;
        }

        if ( _tcsstr(pszClassCaps, lpszNRN) != NULL )
        {
            // we have a NRN.
            m_MsgType = mtNRN;

            goto cleanup;
        }

        if ( _tcsstr(pszClassCaps, lpszRN) != NULL )
        {
            // we have an RN.
            m_MsgType = mtRN;

            goto cleanup;
        }

        // Otherwise, we have an unknown report type
        hr = HR_LOG(E_FAIL);

        goto cleanup;

    }   // end if have an IPM REPORT.

    // Otherwise, we have an IPM message.
    m_MsgType = mtIPM;
    
    // We are done.

cleanup:

    RETURN(hr);

}

//$--CIPMConvert::HrParseIPMSpecific----------------------------------------
//
// DESCRIPTION: Parses IPM specific tag and data lines.
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_OUTOFMEMORY if memory problems,
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseIPMSpecific()
{
    HRESULT         hr          =   NOERROR;
    LPTSTR          lpTag       =   NULL;   // tag string
    LPTSTR          lpData      =   NULL;   // data string
    ULONG           cb          =   0;      // byte count
    ULONG           cbRead      =   0;      // number of bytes read
    LARGE_INTEGER   sAdvance    =   {0};    // byte offset

    // temporary buffer
    TCHAR   szTempBuffer[ulMaxOutStringLen] =   TEXT("");

    // MAPI property creation flags
    const ULONG ulFlags     =   MAPI_CREATE | MAPI_MODIFY | 
                                MAPI_DEFERRED_ERRORS;

    DEBUGPRIVATE("CIPMConvert::HrParseIPMSpecific()\n");

    // consistency checks
    ASSERTERROR(!FBadUnknown(m_lpStream), "Bad m_lpStream");   
    ASSERTERROR(m_MsgType == mtIPM, "Bad m_MsgType");

    // Parse the "----beginbody" tag and data line.
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // number bytes read from stream
                &lpTag,         // tag pointer
                &lpData);       // data pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Check that we have the expected tag
    if ( lstrcmp(lpTag, lpszTagBodyHdr) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Determine number of bytes in body.
    cb = atol(lpData);

    if ( cb )
    {
        if ( m_fTNEFEncode == TRUE )
        {
            // don't create the PR_RTF_COMPRESSED property
            // on the content.  Let the TNEF decoding function
            // do this for us.
            // Merely skip over the message body text in the
            // input stream.
            sAdvance.LowPart = cb;  // # of bytes to advance
            hr = m_lpStream->Seek(
                        sAdvance,   // # bytes to advance
                        STREAM_SEEK_CUR,    // from current position
                        NULL);      // don't care

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

        }   // end if doing TNEF encoding

        else    // not doing TNEF encoding
        {
            // Consistency checking
            ASSERTERROR(!FBadUnknown(m_lpContent), "Bad m_lpContent");

            // Create the RTF compressed text data in the message
            // from the ANSI body text.
            hr = HrTextToRTFCompressed(
                cb/sizeof(CHAR),// # characters of ANSI text
                m_lpStream,     // ANSI text stream pointer
				0,				// don't save attachment rendering positions
				NULL,			// don't save attachment rendering positions
                m_lpContent,    // MAPI message pointer
				0);             // use current code page

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if not doing TNEF encoding
    }   // end if body text

    // Free the tag and data
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);

    // Read in the "\n----endbody\n" marker
    hr = m_lpStream->Read(
                szTempBuffer,   // marker
                lstrlen(lpszTagBodyEnd) * sizeof(TCHAR), // length (no terminator)
                &cbRead);       // number of bytes read.

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Check that the tag is what we expect.
    if ( lstrcmp(szTempBuffer, lpszTagBodyEnd) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // we are done (attachments are handled by HrCreateNextAttachment().

cleanup:

    // Free tag and data
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);

    RETURN(hr);

}

//$--CIPMConvert::HrParseRecipients-------------------------------------------
//
// DESCRIPTION: Parses recipient tag and data lines & saves addresses
//
// INPUT:   lpszTag --  expected tag
//
// INPUT/OUTPUT:    lppAdrList   --  target address list pointer
//          
// OUTPUT:  pnRecips    --  number of recipients of type found
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_OUTOFMEMORY if memory problems,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseRecipients(
        IN LPCTSTR lpszTag,     // expected tag
        IN ULONG ulType,        // MAPI recipient type
        IN OUT LPADRLIST * lppAdrList, // target address list
        OUT ULONG * pnRecips)   // # recipients found of type
{
    HRESULT         hr              =   NOERROR;
    LPTSTR          lpTag           =   NULL;       // tag string
    LPTSTR          lpData          =   NULL;       // data string
    ULONG           cbRead          =   0;          // # bytes read
    LARGE_INTEGER   sOffsetBack     =   {0};        // # bytes to back up by
	LONGLONG		cbBack			=	0;			// # bytes to back up by
    LPSPropValue    lpsRecipProps   =   NULL;       // property value array pointer
    ULONG           cbEid           =   0;          // number of bytes in entry identifier
    LPENTRYID       lpEid           =   NULL;       // entry identifier
    ULONG           cbName          =   0;          // # bytes in email address
    DWORD           cbSize          =   0;          // sizeof of property value array

    // recipient property array indices
    const UINT      iEmailAddr      =   0;          // email address
    const UINT      iRecipType      =   1;          // recipient type
    const UINT      iName           =   2;          // display name
    const UINT      iEID            =   3;          // recipient entry identifier
    const UINT      iAddrType       =   4;          // address type
    const UINT      iRecipNumber    =   5;          // recipient number

    // # of recipient properties
    const ULONG     nRecipProps     =   6;          

    DEBUGPRIVATE("CIPMConvert::HrParseRecipients()\n");

    // consistency checking

    // check input paramters
    hr = CHK_CIPMConvert_HrParseRecipients(lpszTag, ulType, 
                                           lppAdrList, pnRecips);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // initialize input parameters.
    *pnRecips = 0;

    while ( TRUE )
    {
        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);
        MAPIFREEBUFFER(lpEid);

        MAPIFREEBUFFER(lpsRecipProps);

        // Parse one recipient tag and data line at a time.
        hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // #bytes read
                &lpTag,         // tag pointer
                &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Check that tag is of expected type.
        if ( lstrcmp(lpTag, lpszTag) != 0 )
        {
            // Have run out of recipients of desired type.
            // This is not an error.
            // Back up to beginning of line just read.
            cbBack = ((LONGLONG) (-1)) * cbRead;

			sOffsetBack.LowPart = LOWLONG(cbBack);
			sOffsetBack.HighPart = HILONG(cbBack);

            hr = m_lpStream->Seek(
                sOffsetBack,        // number of bytes to back up by
                STREAM_SEEK_CUR,    // from current position
                NULL);

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            goto cleanup;

        }   // end if look ahead data not what we want

        // Have found a recipient.
        (*pnRecips)++;    // increment count

        // Allocate memory for this recipients properties.
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
        lpsRecipProps[iEmailAddr].ulPropTag = PR_EMAIL_ADDRESS;   // e-mail address
        lstrcpy(
                lpsRecipProps[iEmailAddr].Value.LPSZ,
                lpData);

        lpsRecipProps[iRecipType].ulPropTag = PR_RECIPIENT_TYPE;  // recipient type
        lpsRecipProps[iRecipType].Value.l = ulType;

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

        ASSERTERROR(!FBadUnknown(m_lpAB), "Bad m_lpAB");
        ASSERTERROR(!IsBadStringPtr(m_lpszAddrType, INFINITE),
                    "Bad lpszAddrType");

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

        if ( *lppAdrList == NULL )
        {
            // Create a new address list.
            hr = HrMAPICreateAddressList(
                nRecipProps,    // number of properties for address
                lpsRecipProps,  // recipient properties
                lppAdrList);    // target address list pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }

        else
        {
            // Append recipient to address list.
            hr = HrMAPIAppendAddressList(
                nRecipProps,    // number of properties for address
                lpsRecipProps,  // recipient properties
                lppAdrList);    // target address list pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if already have address list
    }   // end while

    // we are done

cleanup:

    // Free MAPI buffers
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);
    MAPIFREEBUFFER(lpEid);

    // HrMAPICreateAddressList makes a duplicate of the
    // property value array passed into it.  Thus, free
    // property value array here.
    MAPIFREEBUFFER(lpsRecipProps);

    // caller "owns" address list.

    RETURN(hr);

}

//$--CIPMConvert::HrParseExternalTraceData--------------------------------------
//
// DESCRIPTION: Parse trace tag and data lines and store data.
//
// OUTPUT:  pnEntries   --  # of trace entries found
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseExternalTraceData(
        OUT ULONG * pnEntries)   // # trace entries found
{
    HRESULT         hr          =   NOERROR;
    LPTSTR          lpTag       =   NULL;       // tag string
    LPTSTR          lpData      =   NULL;       // data string
    ULONG           cbRead      =   0;          // # bytes read from stream
    LARGE_INTEGER   sOffsetBack =   {0};        // number of bytes to seek
	LONGLONG		cbBack		=	0;			// number of bytes to seek

    LONG        lAction     =   0;          // trace action
    FILETIME    ftArrival   =   {0};        // arrival time structure
    FILETIME    ftDeferred  =   {0};        // deferred time structure

    TCHAR       pszADMD[MAX_ADMD_NAME_SIZ]         = TEXT(""); // ADMD name
    TCHAR       pszCountry[MAX_COUNTRY_NAME_SIZ]   = TEXT(""); // country name
    TCHAR       pszPRMDId[MAX_PRMD_NAME_SIZ]       = TEXT(""); // PRMD ID
    TCHAR       pszAttADMD[MAX_ADMD_NAME_SIZ]      = TEXT(""); // attempted ADMD name
    TCHAR       pszAttCountry[MAX_COUNTRY_NAME_SIZ]= TEXT(""); // attempted country name
    TCHAR       pszAttPRMDId[MAX_PRMD_NAME_SIZ]    = TEXT(""); // attempted PRMD ID

    DEBUGPRIVATE("CIPMConvert::HrParseExternalTraceData()\n");

    // check input parameters
    hr = CHK_CIPMConvert_HrParseExternalTraceData(pnEntries);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pnEntries = 0;     // initialize output

    while ( TRUE )
    {
        // Parse "External-Received-By" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag.
        if ( lstrcmp(lpTag, lpszTagExternalRcvdBy) != 0 )
        {
            // There are no more trace entries.
            // This isn't an error.
            // Rewind back to before this string.
            cbBack = ((LONGLONG) (-1)) * cbRead;

			sOffsetBack.LowPart = LOWLONG(cbBack);
			sOffsetBack.HighPart = HILONG(cbBack);

            hr = m_lpStream->Seek(
                    sOffsetBack,        // offset
                    STREAM_SEEK_CUR,    // from current position
                    NULL);

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            goto cleanup;
        }

        // Parse the external trace data into its individual components.
        hr = HrParseExternalTraceString(
                lpData,     // trace data string
                &lAction,   // trace action
                pszCountry, // country name
                pszADMD,    // ADMD name
                pszPRMDId); // PRMD identifier

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffer
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Parse "External-Received At" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag.
        if ( lstrcmp(lpTag, lpszTagExternalRcvdAt) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Convert the date/time string to a file time
        // structure.
        hr = HrParseDateTimeString(
                lpData,         // date time string
                &ftArrival);    // file time structure

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Parse "External-Attempted-By" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check the tag
        if ( lstrcmp(lpTag, lpszTagExternalAttmBy) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Parse the data into its individual components
        hr = HrParseExternalTraceString(
                lpData,         // trace data string
                &lAction,       // trace action
                pszAttCountry,  // attempted country name
                pszAttADMD,     // attempted ADMD name
                pszAttPRMDId);  // attempted PRMD identifier

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Parse "External-Deferred-At" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag.
        if ( lstrcmp(lpTag, lpszTagExternalDefdAt) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Convert the date/time string to a file time
        // structure.
        hr = HrParseDateTimeString(
                lpData,         // date time string
                &ftDeferred);   // file time structure

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Append this trace entry information to the
        // trace information list.
        if ( m_lpTraceInfo == NULL )
        {
            // create list with entry.
            hr = HrTraceCreateEntryList(
                    lAction,        // trace action
                    ftArrival,      // arrival time
                    ftDeferred,     // deferred time
                    pszADMD,        // ADMD name
                    pszCountry,     // country name
                    pszPRMDId,      // PRMD identifier
                    pszAttADMD,     // attempted ADMD
                    pszAttCountry,  // attempted country
                    pszAttPRMDId,   // attempted PRMD ID
                    &m_lpTraceInfo);    // pointer to trace information pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }

        else
        {
            // append entry to list
            hr = HrTraceAppendEntryList(
                    lAction,        // trace action
                    ftArrival,      // arrival time
                    ftDeferred,     // deferred time
                    pszADMD,        // ADMD name
                    pszCountry,     // country name
                    pszPRMDId,      // PRMD identifier
                    pszAttADMD,     // attempted ADMD
                    pszAttCountry,  // attempted country
                    pszAttPRMDId,   // attempted PRMD ID
                    &m_lpTraceInfo);    // pointer to trace information pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if trace information list exists

        (*pnEntries)++;   // increment # of entries found

    }   // end while

    // we are done.
        
cleanup:
    
    // free MAPI buffers
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);

    RETURN(hr);

}

//$--CIPMConvert::HrParseInternalTraceData--------------------------------------
//
// DESCRIPTION: Parse trace tag and data lines and store data.
//
// OUTPUT:  pnEntries   --  # of trace entries found
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
HRESULT CIPMConvert::HrParseInternalTraceData(
        OUT ULONG * pnEntries)   // # trace entries found
{
    HRESULT         hr          =   NOERROR;
    LPTSTR          lpTag       =   NULL;       // tag string
    LPTSTR          lpData      =   NULL;       // data string
    ULONG           cbRead      =   0;          // # bytes read from stream
    LARGE_INTEGER   sOffsetBack =   {0};        // number of bytes to seek
	LONGLONG		cbBack		=	0;			// number of bytes to seek

    LONG        lAction     =   0;          // trace action
    FILETIME    ftArrival   =   {0};        // arrival time structure
    FILETIME    ftDeferred  =   {0};        // deferred time structure

    TCHAR       pszADMD[MAX_ADMD_NAME_SIZ]         = TEXT(""); // ADMD name
    TCHAR       pszCountry[MAX_COUNTRY_NAME_SIZ]   = TEXT(""); // country name
    TCHAR       pszPRMDId[MAX_PRMD_NAME_SIZ]       = TEXT(""); // PRMD ID
    TCHAR       pszMTA[MAX_ADMD_NAME_SIZ]          = TEXT(""); // MTA name
    TCHAR       pszAttADMD[MAX_ADMD_NAME_SIZ]      = TEXT(""); // attempted ADMD name
    TCHAR       pszAttCountry[MAX_COUNTRY_NAME_SIZ]= TEXT(""); // attempted country name
    TCHAR       pszAttPRMDId[MAX_PRMD_NAME_SIZ]    = TEXT(""); // attempted PRMD ID
    TCHAR       pszAttMTA[MAX_MTA_NAME_SIZ]        = TEXT(""); // attempted MTA name

    DEBUGPRIVATE("CIPMConvert::HrParseInternalTraceData()\n");

    // check input parameters
    hr = CHK_CIPMConvert_HrParseInternalTraceData(pnEntries);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pnEntries = 0;     // initialize output

    while ( TRUE )
    {
        // Parse "Internal-Received-By" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag.
        if ( lstrcmp(lpTag, lpszTagInternalRcvdBy) != 0 )
        {
            // There are no more trace entries.
            // This isn't an error.
            // Rewind back to before this string.
            cbBack = ((LONGLONG) (-1)) * cbRead;

			sOffsetBack.LowPart = LOWLONG(cbBack);
			sOffsetBack.HighPart = HILONG(cbBack);

            hr = m_lpStream->Seek(
                    sOffsetBack,        // offset
                    STREAM_SEEK_CUR,    // from current position
                    NULL);

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            goto cleanup;
        }

        // Parse the internal trace data into its individual components.
        hr = HrParseInternalTraceString(
                lpData,     // trace data string
                &lAction,   // trace action
                pszCountry, // country name
                pszADMD,    // ADMD name
                pszPRMDId,  // PRMD identifier
                pszMTA);    // MTA name

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffer
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Parse "Internal-Received At" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag.
        if ( lstrcmp(lpTag, lpszTagInternalRcvdAt) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Convert the date/time string to a file time
        // structure.
        hr = HrParseDateTimeString(
                lpData,         // date time string
                &ftArrival);    // file time structure

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Parse "Internal-Attempted-By" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check the tag
        if ( lstrcmp(lpTag, lpszTagInternalAttmBy) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Parse the data into its individual components
        hr = HrParseInternalTraceString(
                lpData,         // trace data string
                &lAction,       // trace action
                pszAttCountry,  // attempted country name
                pszAttADMD,     // attempted ADMD name
                pszAttPRMDId,   // attempted PRMD identifier
                pszAttMTA);     // attempted MTA name

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Parse "Internal-Deferred-At" tag and data line.
        hr = HrParseTagAndData(
                    m_lpStream,     // stream pointer                    
                    &cbRead,        // # bytes read
                    &lpTag,         // tag pointer
                    &lpData);       // data pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // check tag.
        if ( lstrcmp(lpTag, lpszTagInternalDefdAt) != 0 )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Convert the date/time string to a file time
        // structure.
        hr = HrParseDateTimeString(
                lpData,         // date time string
                &ftDeferred);   // file time structure

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Free MAPI buffers
        MAPIFREEBUFFER(lpTag);
        MAPIFREEBUFFER(lpData);

        // Append this trace entry information to the
        // trace information list.
        if ( m_lpIntTraceInfo == NULL )
        {
            // create list with entry.
            hr = HrInternalTraceCreateEntryList(
                    lAction,        // trace action
                    ftArrival,      // arrival time
                    ftDeferred,     // deferred time
                    pszADMD,        // ADMD name
                    pszCountry,     // country name
                    pszPRMDId,      // PRMD identifier
                    pszMTA,         // MTA name
                    pszAttADMD,     // attempted ADMD
                    pszAttCountry,  // attempted country
                    pszAttPRMDId,   // attempted PRMD ID
                    pszAttMTA,      // attempted MTA
                    &m_lpIntTraceInfo);    // pointer to trace information pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }

        else
        {
            // append entry to list
            hr = HrInternalTraceAppendEntryList(
                    lAction,        // trace action
                    ftArrival,      // arrival time
                    ftDeferred,     // deferred time
                    pszADMD,        // ADMD name
                    pszCountry,     // country name
                    pszPRMDId,      // PRMD identifier
                    pszMTA,         // MTA name
                    pszAttADMD,     // attempted ADMD
                    pszAttCountry,  // attempted country
                    pszAttPRMDId,   // attempted PRMD ID
                    pszAttMTA,      // attempted MTA
                    &m_lpIntTraceInfo);    // pointer to trace information pointer

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
        }   // end if trace information list exists

        (*pnEntries)++;   // increment # of entries found

    }   // end while

    // we are done.
        
cleanup:
    
    // free MAPI buffers
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);

    RETURN(hr);

}

//$--CIPMConvert::HrCreateContent---------------------------------------------
//
// DESCRIPTION: Create an envelope content message.
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrCreateContent()
{
    HRESULT             hr              =   NOERROR;
    ULONG               ulAttachNum     =   0;      // attachment number
    LPSPropProblemArray lpsProblems     =   NULL;   // problem array pointer

    // MAPI flags
    const ULONG ulFlags                 =   
        MAPI_CREATE | MAPI_MODIFY | MAPI_DEFERRED_ERRORS;

    // property array indices
    const UINT  iMethod                 =   0;      
    const UINT  iPosition               =   1;

    const UINT  nProps                  =   2;      // # of properties

    SPropValue  rgAttachProps[nProps]   =   {0};    // array of properties

    DEBUGPRIVATE("CIPMConvert::HrCreateContent()\n");

    // consistency checks
    ASSERTERROR(!FBadUnknown(m_lpEnvelope), "Bad m_lpEnvelope");
    ASSERTERROR((m_MsgType == mtIPM || m_MsgType == mtRN || m_MsgType == mtNRN),
                "Bad m_MsgType");

    // If we are doing TNEF decoding, let TNEF create
    // the envelope attachment & content.
    if ( m_fTNEFEncode == TRUE )
    {
        goto cleanup;
    }

    hr = m_lpEnvelope->CreateAttach(
                NULL,           // interface ID pointer
                MAPI_DEFERRED_ERRORS,   // MAPI flags (reduces RPC calls)
                &ulAttachNum,   // attachment number
                &m_lpAttach);   // pointer to attachment pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(!FBadUnknown(m_lpAttach), "Bad m_lpAttach");

    // Set the appropriate attachment properties for a 
    // content message.
    rgAttachProps[iMethod].ulPropTag = PR_ATTACH_METHOD;  // property tag
    rgAttachProps[iMethod].Value.l = ATTACH_EMBEDDED_MSG; // value

    rgAttachProps[iPosition].ulPropTag = PR_RENDERING_POSITION;
    rgAttachProps[iPosition].Value.l = INFINITE;  // default

    // Set attachment properties
    hr = m_lpAttach->SetProps(
                nProps,         // # of properties
                rgAttachProps,  // array of properties
                &lpsProblems);  // problem array pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        lpsProblems = NULL;     // so we can safely release it

        goto cleanup;
    }

    // check problem array
    if ( lpsProblems )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Create a message attachment.
    hr = m_lpAttach->OpenProperty(
                PR_ATTACH_DATA_OBJ,     // for a message object
                &IID_IMessage,          // MAPI message interface
                0,                      // interface flags
                ulFlags,                // MAPI property creation flags
                (LPUNKNOWN *) &m_lpContent);          // envelope content pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(!FBadUnknown(m_lpContent), "Bad m_lpContent");

    // we are done.

cleanup:

    // FREE MAPI buffers
    MAPIFREEBUFFER(lpsProblems);

    RETURN(hr);

}

//$--CIPMConvert::HrCreateNextAttachment--------------------------------------
//
// DESCRIPTION: Parse and create next envelope content attachment.
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      EDK_E_NOT_FOUND if no more attachments
//                      E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrCreateNextAttachment()
{
    HRESULT         			hr              =   NOERROR;
    LPTSTR          			lpTag           =   NULL;   // tag string
    LPTSTR          			lpData          =   NULL;   // data string
    ULONG           			cb              =   0;      // # of bytes in attachment
    LPTSTR          			lpszFileName    =   NULL;   // file name string
    ULONG           			cbRead          =   0;      // # bytes read from stream
    LPATTACH        			lpAttach        =   NULL;   // attachment pointer
    ULONG           			ulAttachNum     =   0;      // attachment number
    PVIRTUALSTREAMONPROPERTY	lpAttachStream  =   NULL;   // buffered stream
    LARGE_INTEGER   			sOffset         =   {0};    // # bytes to retreat
	LONGLONG					cbOffset		=	0;		// # bytes to retreat
    ULARGE_INTEGER  			sSize           =   {0};    // # bytes in attachment

    // temporary string buffer
    TCHAR       szTempBuffer[ulMaxOutStringLen] =   TEXT("");

   // MAPI property creation flags
    const ULONG ulFlags     =   MAPI_CREATE | MAPI_MODIFY |
                                MAPI_DEFERRED_ERRORS;   // reduces RPCs

    const UINT  cProps      =   5;      // number of properties in array
    const UINT  iFileName   =   0;      // file name property index
    const UINT  iLongName   =   1;      // long file name property index
    const UINT  iMethod     =   2;      // attachment method property index
    const UINT  iPosition   =   3;      // renderning position property index
    const UINT  iName       =   4;      // display name property index

    // Property tag array for an attachment
    SPropValue  sAttachProps[cProps]    =   {0};

    // property problem array pointer
    LPSPropProblemArray lpProblems      =   NULL;   

    DEBUGPRIVATE("CIPMConvert::HrCreateNextAttachment()\n");

    // Parse "----beginattach" tag and data
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer                
                &cbRead,        // # bytes read
                &lpTag,         // tag pointer
                &lpData);       // data pointer

    if ( FAILED(hr) )
    {                
        goto cleanup;
    }

    // Check the tag.
    if ( lstrcmp(lpTag, lpszTagAttachHdr) != 0 )
    {
        // We have read ahead to far.
        // (TNEF data may follow)
        // Back up to where we were before.
        cbOffset = ((LONGLONG) (-1)) * cbRead; // negative offset

		sOffset.LowPart = LOWLONG(cbOffset);
		sOffset.HighPart = HILONG(cbOffset);

        hr = m_lpStream->Seek(
                    sOffset,    // # bytes to retreat
                    STREAM_SEEK_CUR,    // from current position
                    NULL);      // don't care

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Let caller know that there are no more attachments
        hr = HR_LOG(EDK_E_NOT_FOUND);

        goto cleanup;
    }

    // Parse attachment header data into file name
    // and file size (in bytes) components.
    hr = HrParseAttachmentHeader(
                lpData,     // attachment header data
                &lpszFileName,// file name
                &cb);       // number of bytes in attachment

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    ASSERTERROR(lpszFileName != NULL, "Bad lpszFileName");

    // check to make sure that attachment file name isn't empty.
    if ( *lpszFileName == 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Note: Only support binary attachments at this time.

    // free MAPI buffers
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);

    if ( m_fTNEFEncode == FALSE )   // If not doing TNEF decoding
    {
        // consistency check
        ASSERT_IUNKNOWN_PTR(m_lpContent, "Bad m_lpContent");

        // Create attachment
        hr = m_lpContent->CreateAttach(
                NULL,           // interface ID pointer
                MAPI_DEFERRED_ERRORS,   // flags (reduces RPCs)
                &ulAttachNum,   // attachment number
                &lpAttach);     // pointer to attachment pointer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERT_IUNKNOWN_PTR(lpAttach, "Bad lpAttach");

        // Create a buffered stream on the attachment's binary data and
        // read the attachment data into it.
		hr = HrOpenVirtualStreamOnProperty(
			lpAttach,			// MAPI property object pointer
            PR_ATTACH_DATA_BIN, // property tag
            ulFlags,            // MAPI property creation flags
            &lpAttachStream); 	// buffered stream pointer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERT_IUNKNOWN_PTR(lpAttachStream, "Bad lpAttachStream");

        // Read the attachment data into the attachment stream.
        sSize.LowPart = cb;         	// # bytes in attachment
        hr = m_lpStream->CopyTo(    	// source stream
            (LPSTREAM) lpAttachStream,	// destination stream
            sSize,                 	 	// # bytes to copy
            NULL,
            NULL);

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

		// Commit changes to the attachment data stream.
		// We must do this, since the stream is buffered.
		hr = lpAttachStream->Commit(
			0);			// not going to do anything else with it

		if ( FAILED(hr) )
		{
			hr = HR_LOG(E_FAIL);

			goto cleanup;
		}
    }   // end if not doing TNEF decoding

    else    // are doing TNEF decoding
    {
        // Let TNEF extract the attachments.
        // Merely skip over the attachment data for now.
        sOffset.LowPart = cb;    // # of bytes
        hr = m_lpStream->Seek(
                    sOffset,    // # bytes to advance
                    STREAM_SEEK_CUR,    // from current position,
                    NULL);      // don't care

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

    }   // end if doing TNEF decoding

    // Read in "----endattach" marker
    hr = m_lpStream->Read(
            szTempBuffer,   // data buffer
            lstrlen(lpszTagAttachEnd) * sizeof(TCHAR), // length (no terminator)
            &cbRead);       // number of bytes read

    // test the marker
    if ( lstrcmp(szTempBuffer, lpszTagAttachEnd) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    if ( m_fTNEFEncode == FALSE )
    {
        // Set attachment properties.
        sAttachProps[iFileName].ulPropTag = PR_ATTACH_FILENAME;     // property tag
        sAttachProps[iFileName].Value.LPSZ = lpszFileName;            // file name

        sAttachProps[iLongName].ulPropTag = PR_ATTACH_LONG_FILENAME;// property tag
        sAttachProps[iLongName].Value.LPSZ = lpszFileName;            // file name

        sAttachProps[iMethod].ulPropTag = PR_ATTACH_METHOD; // property tag
        sAttachProps[iMethod].Value.l = ATTACH_BY_VALUE;    // value

        sAttachProps[iPosition].ulPropTag = PR_RENDERING_POSITION;
        sAttachProps[iPosition].Value.l = INFINITE;         // default

        sAttachProps[iName].ulPropTag = PR_DISPLAY_NAME;    // property tag
        sAttachProps[iName].Value.LPSZ = lpszFileName;        // file name

        // Set properties.
        hr = lpAttach->SetProps(
            cProps,                 // # property values
            (LPSPropValue) &sAttachProps,   // property value array
            &lpProblems);           // problem array pointer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            lpProblems = NULL;
        
            goto cleanup;
        }

        // Fail if not all properties were set.
        if ( lpProblems )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Save changes to the attachment
        hr = lpAttach->SaveChanges(
                MAPI_DEFERRED_ERRORS);      // save's RPCs

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }
    }   // end if not doing TNEF decoding

    // we are done with this attachment

cleanup:

    // Release MAPI objects
    ULRELEASE(lpAttach);
    ULRELEASE(lpAttachStream);

    // free MAPI buffers
    MAPIFREEBUFFER(lpTag);
    MAPIFREEBUFFER(lpData);
    MAPIFREEBUFFER(lpszFileName);
    MAPIFREEBUFFER(lpProblems);

    RETURN(hr);

}

//$--HrSetEnvelopeProps-------------------------------------------------------
//
// DESCRIPTION: Sets IPM envelope properties
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrSetEnvelopeProps()
{
    HRESULT             hr                  =   NOERROR;
    LPSPropProblemArray lpsProblems         =   NULL;   // property problem array
    ULONG               cbEid               =   0;      // # bytes in entry ID
    LPENTRYID           lpEid               =   NULL;   // entry identifier
    LPTSTR              lpszSubjectPrefix   =   NULL;   // subject prefix
    LPTSTR              lpszNormSubject     =   NULL;   // normalized subject
    FILETIME            ftArrival           =   {0};    // arrival time
    LPTSTR              lpMailFromAddr      =   NULL;   // Mail from address
    ULONG               nEnvProps           =   0;      // # of envelope properties
    BOOL                fDRRequested        =   FALSE;  // TRUE if DRs requeted for IPM

    // message envelope class
    TCHAR               pszMsgClass[ulMaxOutStringLen * 2]  =   TEXT("");

    // Property value array indices
    const UINT  iClassVal               =   0;
    const UINT  iFromAddrVal            =   1;
    const UINT  iFromNameVal            =   2;
    const UINT  iFromEidVal             =   3;
    const UINT  iFromAddrTypeVal        =   4;
    const UINT  iXIDVal                 =   5;
    const UINT  iSubjectVal             =   6;
    const UINT  iDeleteVal              =   7;
    const UINT  iArrivalTimeVal         =   8;

    // properties specific to IPMs
    const UINT  iDRRequested            =   9;

    // minimum number of IPM envelope properties
    const ULONG nIPMEnvProps            =   10;

    // properties specific to notifications
    const UINT  iNotifyReqVal           =   9;

    // minimum number of notification properties
    const ULONG nNotifyEnvProps         =   10;

    // property value array
    // NOTE:  The PR_TRACE_INFO and the PR_INTERNAL_TRACE_INFO properties
    // are optional. Thus, the maximum number of envelope properties
    // is two more than the minimum number of notify properties.
    SPropValue  rgEnvProps[nNotifyEnvProps + 2] =   {0}; 

    const LPCTSTR   lpszEnvClass        =   TEXT("ENVELOPE.");

    DEBUGPRIVATE("CIPMConvert::HrSetEnvelopeProps()\n");

    // consistency checking
    ASSERTERROR(!FBadUnknown(m_lpEnvelope), "Bad m_lpEnvelope");
    ASSERTERROR((m_MsgType == mtIPM || m_MsgType == mtNRN || m_MsgType == mtRN),
                 "Bad m_MsgType");

    // have an IPM envelope
    lstrcpy(pszMsgClass, lpszEnvClass);

    // Append message class to envelope class.
    lstrcat(pszMsgClass, m_rgszData[iClass]);

    // Set properties on envelope.
    rgEnvProps[iClassVal].ulPropTag = PR_MESSAGE_CLASS;
    rgEnvProps[iClassVal].Value.LPSZ = pszMsgClass;

    lpMailFromAddr = m_rgszData[iMailFrom]; // mail from address
    rgEnvProps[iFromAddrVal].ulPropTag = PR_ORIGINATOR_ADDR;
    rgEnvProps[iFromAddrVal].Value.LPSZ = lpMailFromAddr;

    rgEnvProps[iFromNameVal].ulPropTag = PR_ORIGINATOR_NAME;
    rgEnvProps[iFromNameVal].Value.LPSZ = lpMailFromAddr;

    // Create an entry identifier for this "one off" address
    hr = m_lpAB->CreateOneOff(
                    lpMailFromAddr,     // name
                    (LPTSTR) m_lpszAddrType,   // address type
                    lpMailFromAddr,     // address
                    0,              // flags
                    &cbEid,         // #bytes in entry ID
                    &lpEid);        // entry identifier

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    rgEnvProps[iFromEidVal].ulPropTag = PR_ORIGINATOR_ENTRYID;
    rgEnvProps[iFromEidVal].Value.bin.cb = cbEid;
    rgEnvProps[iFromEidVal].Value.bin.lpb = (BYTE *) lpEid;

    rgEnvProps[iFromAddrTypeVal].ulPropTag = PR_ORIGINATOR_ADDRTYPE;
    rgEnvProps[iFromAddrTypeVal].Value.LPSZ = (LPTSTR) m_lpszAddrType;

    rgEnvProps[iXIDVal].ulPropTag = PR_MESSAGE_SUBMISSION_ID;
    rgEnvProps[iXIDVal].Value.bin.cb = 
        cbStrLen(m_rgszData[iXID]);
    rgEnvProps[iXIDVal].Value.bin.lpb = (BYTE *) m_rgszData[iXID];

    rgEnvProps[iSubjectVal].ulPropTag = PR_SUBJECT;       // same as for content
    rgEnvProps[iSubjectVal].Value.LPSZ = m_rgszData[iSubject];

    rgEnvProps[iDeleteVal].ulPropTag = PR_DELETE_AFTER_SUBMIT;
    rgEnvProps[iDeleteVal].Value.b = TRUE;

    // Determine the arrival time.  This is the current time!

    GetSystemTimeAsFileTime( &ftArrival);

    rgEnvProps[iArrivalTimeVal].ulPropTag = PR_ARRIVAL_TIME;
    rgEnvProps[iArrivalTimeVal].Value.ft = ftArrival;

    // Set the properties unique to notifications
    // and set the number of properties to set
    if ( m_MsgType == mtIPM )
    {
        // Set the PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED property,
        // when available, so that delivery reports will be generated.
        if ( m_fTNEFEncode == TRUE )
        {
            // Value of PR_ORIGINATORY_DELIVERY_REPORT_REQUESTED is
            // in the TNEF-decoded message content.
            // First, open the content.
            hr = m_lpEnvelope->OpenAttach(
                0,  // attachment #
                NULL,   // interface (whatever is appropriate)
                MAPI_DEFERRED_ERRORS,   // reduces RPCs
                &m_lpAttach);         // attachment pointer

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_FAIL);
            
                goto cleanup;
            }

            ASSERT_IUNKNOWN_PTR(m_lpAttach, "Bad m_lpAttach");

            // Open the attachment as a message.
            hr = m_lpAttach->OpenProperty(
                PR_ATTACH_DATA_OBJ, // property tag
                &IID_IMessage,  // interface identifier
                0,              // interface flags
                MAPI_DEFERRED_ERRORS,   // reduces RPCs
                (LPUNKNOWN *) &m_lpContent);

            if ( FAILED(hr) )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            ASSERT_IUNKNOWN_PTR(m_lpContent, "Bad m_lpContent.");

            // Retrive the content's delivery report request value.
            hr = HrMAPIGetPropBoolean(
                m_lpContent,        // message content poitner
                PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED,    // property tag
                &fDRRequested);     // property value

            // If the PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED property
            // doesn't exist in the content, just set leave it at to the default
            // value of false.
            if ( hr == MAPI_E_NOT_FOUND )   // does NOT return EDK_E_NOT_FOUND!
            {
                // Not an error.  Just set delivery report
                // requested value to FALSE.
                fDRRequested = FALSE;

                hr = HR_LOG(NOERROR);
            }

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

        }   // end if doing TNEF decoding

        // Set the delivery report requested value.
        rgEnvProps[iDRRequested].ulPropTag = 
            PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
        rgEnvProps[iDRRequested].Value.b = fDRRequested;

        // set number of envelope properties
        nEnvProps = nIPMEnvProps;
    }

    else    // have a notification
    {
        // Set the appropriate notification requested property.
        if ( m_MsgType == mtNRN )   // have a non-read notification
        {
            rgEnvProps[iNotifyReqVal].ulPropTag = 
                PR_NON_RECEIPT_NOTIFICATION_REQUESTED;
        }
    
        else    // have a read notification
        {
            rgEnvProps[iNotifyReqVal].ulPropTag =
                PR_READ_RECEIPT_REQUESTED;
        }

        rgEnvProps[iNotifyReqVal].Value.b = TRUE;

        // set number of envelope properties
        nEnvProps = nNotifyEnvProps;

    }   // end if notification

    // Set the trace information, if any.
    if ( m_lpTraceInfo != NULL )
    {
        rgEnvProps[nEnvProps].ulPropTag = PR_TRACE_INFO;
        rgEnvProps[nEnvProps].Value.bin.cb = CbTRACEINFO(m_lpTraceInfo);
        rgEnvProps[nEnvProps].Value.bin.lpb = (BYTE *) m_lpTraceInfo;

        // increment the property count
        nEnvProps++;

    }   // end if trace information

    // Set the internal trace information, if any.
    if ( m_lpIntTraceInfo != NULL )
    {
        rgEnvProps[nEnvProps].ulPropTag = PR_INTERNAL_TRACE_INFO;
        rgEnvProps[nEnvProps].Value.bin.cb = CbINTTRACEINFO(m_lpIntTraceInfo);
        rgEnvProps[nEnvProps].Value.bin.lpb = (BYTE *) m_lpIntTraceInfo;

        // increment the property count
        nEnvProps++;

    }   // end if trace information

    // Set the PR_TRANSPORT_MESSAGE_HEADER property
    hr = HrSetTransHdr();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }
                        
    hr = m_lpEnvelope->SetProps(
                nEnvProps,      // # of properties values
                rgEnvProps,     // property value array
                &lpsProblems);  // problem array

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        lpsProblems = NULL;

        goto cleanup;
    }

    if ( lpsProblems != NULL )
    {
        // problems with property values
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Set properties on envelope's recipient table.
    hr = m_lpEnvelope->ModifyRecipients(
                MODRECIP_ADD,       // flags
                m_lpRcptToList);    // address list        

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

//$--CIPMConvert::HrSetContentProps-------------------------------------------
//
// DESCRIPTION: Sets IPM content properties
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrSetContentProps()
{
    HRESULT             hr                      =   NOERROR;
    LPSPropProblemArray lpsProblems             =   NULL;   // problems array pointer
    ULONG               ulPriority              =   0;      // priority value
    ULONG               ulImportance            =   0;      // importance value
    FILETIME            ftClientSubmit          =   {0};    // file time structure
    ULONG               cbEid                   =   0;      // # bytes in entry identifier
    LPENTRYID           lpEid                   =   NULL;   // entry identifier

    // Property value array indices
    const UINT          iClassVal               =   0;
    const UINT          iFromAddrVal            =   1;
    const UINT          iFromNameVal            =   2;
    const UINT          iFromEidVal             =   3;
    const UINT          iFromAddrTypeVal        =   4;
    const UINT          iSubmitTimeVal          =   5;
    const UINT          iImportanceVal          =   6;
    const UINT          iPriorityVal            =   7;
    const UINT          iSubjectVal             =   8;
	const UINT			iFromAddrVal2			=	9;
	const UINT			iFromNameVal2			=	10;
	const UINT			iFromEidVal2			=	11;
	const UINT			iFromAddrTypeVal2		=	12;

    // # of property values
    const ULONG         nCntProps               =   13;

    // property value arrray
    SPropValue          rgCntProps[nCntProps]   =   {0};    

    DEBUGPRIVATE("CIPMConvert::HrSetContentProps()\n");

    // consistency checking
    ASSERTERROR(m_MsgType == mtIPM,
                "Bad m_MsgType");

    // If TNEF decoding is desired, let TNEF extract the content
    // properties
    if ( m_fTNEFEncode == TRUE )
    {
        goto cleanup;
    }

    // Set up the content properties.
    rgCntProps[iClassVal].ulPropTag = PR_MESSAGE_CLASS;
    rgCntProps[iClassVal].Value.LPSZ = m_rgszData[iClass];
    
	// PR_SENDER_* and PR_SENT_REPRESENTING_* properties
    rgCntProps[iFromAddrVal].ulPropTag = PR_SENDER_EMAIL_ADDRESS;
    rgCntProps[iFromAddrVal].Value.LPSZ = m_rgszData[iFrom];

    rgCntProps[iFromNameVal].ulPropTag = PR_SENDER_NAME;
    rgCntProps[iFromNameVal].Value.LPSZ = m_rgszData[iFrom];

    // Create an entry identifier for this "one off" address
    hr = m_lpAB->CreateOneOff(
                    m_rgszData[iFrom],          // name
                    (LPTSTR) m_lpszAddrType,    // address type
                    m_rgszData[iFrom],          // address
                    0,              // flags
                    &cbEid,         // #bytes in entry ID
                    &lpEid);        // entry identifier

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    rgCntProps[iFromEidVal].ulPropTag = PR_SENDER_ENTRYID;
    rgCntProps[iFromEidVal].Value.bin.cb = cbEid;
    rgCntProps[iFromEidVal].Value.bin.lpb = (BYTE *) lpEid;

    rgCntProps[iFromAddrTypeVal].ulPropTag = PR_SENDER_ADDRTYPE;
    rgCntProps[iFromAddrTypeVal].Value.LPSZ = (LPTSTR) m_lpszAddrType;

    rgCntProps[iFromAddrVal2].ulPropTag = PR_SENT_REPRESENTING_EMAIL_ADDRESS;
    rgCntProps[iFromAddrVal2].Value.LPSZ = m_rgszData[iFrom];

    rgCntProps[iFromNameVal2].ulPropTag = PR_SENT_REPRESENTING_NAME;
    rgCntProps[iFromNameVal2].Value.LPSZ = m_rgszData[iFrom];

    rgCntProps[iFromEidVal2].ulPropTag = PR_SENT_REPRESENTING_ENTRYID;
    rgCntProps[iFromEidVal2].Value.bin.cb = cbEid;
    rgCntProps[iFromEidVal2].Value.bin.lpb = (BYTE *) lpEid;

    rgCntProps[iFromAddrTypeVal2].ulPropTag = PR_SENT_REPRESENTING_ADDRTYPE;
    rgCntProps[iFromAddrTypeVal2].Value.LPSZ = (LPTSTR) m_lpszAddrType;

    // Determine the client submit file time
    hr = HrParseDateTimeString(
                m_rgszData[iDate],        // date time string
                &ftClientSubmit);       // file time structure pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgCntProps[iSubmitTimeVal].ulPropTag = PR_CLIENT_SUBMIT_TIME;
    rgCntProps[iSubmitTimeVal].Value.ft = ftClientSubmit;

    // Determine importance
    hr = HrParseImportanceString(
                m_rgszData[iImportance],      // importance string
                &ulImportance);             // importance value

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgCntProps[iImportanceVal].ulPropTag = PR_IMPORTANCE;
    rgCntProps[iImportanceVal].Value.l = ulImportance;

    // Determine priority
    hr = HrParsePriorityString(
                m_rgszData[iPriority],        // priority string
                &ulPriority);               // priority value

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    rgCntProps[iPriorityVal].ulPropTag = PR_PRIORITY;
    rgCntProps[iPriorityVal].Value.l = ulPriority;

    rgCntProps[iSubjectVal].ulPropTag = PR_SUBJECT;
    rgCntProps[iSubjectVal].Value.LPSZ = m_rgszData[iSubject];

    // more consistency checks
    ASSERTERROR(!FBadUnknown(m_lpContent), "Bad m_lpContent");

    // Set properties on the content.
    hr = m_lpContent->SetProps(
                nCntProps,      // # properties
                rgCntProps,     // property value array
                &lpsProblems);  // problems array pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        lpsProblems = NULL;

        goto cleanup;
    }

    if ( lpsProblems != NULL )
    {
        // problems with property values
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Modify the content's recipient table.
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
                MAPI_DEFERRED_ERRORS);      // saves RPCs

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
    MAPIFREEBUFFER(lpsProblems);

    RETURN(hr);

}

//$--CIPMConvert::HrSetTransHdr------------------------------------------------
//
// DESCRIPTION: Set the PR_TRANSPORT_MESSAGE_HEADER property
//              on the envelope.
//
// ASSUMPTIONS: The entire input stream has been read when this
//              function is called.  (i.e.  This function will only
//              set the PR_TRANSPORT_MESSAGE_HEADERS property equal
//              to the contents of the beginning of the stream to its
//              current position.)
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrSetTransHdr()
{
    HRESULT         			hr              =   NOERROR;
    PVIRTUALSTREAMONPROPERTY	lpTransHdrStrm  =   NULL;   // buffered stream pointer
    LARGE_INTEGER   			sOffsetBegin    =   {0};    // begin position

    // MAPI property creation flags
    const ULONG ulFlags         =   MAPI_CREATE | MAPI_MODIFY |
                                    MAPI_DEFERRED_ERRORS;

    DEBUGPRIVATE("CIPMConvert::HrSetTransHdr()\n");

    // consistency checking
    ASSERT_IUNKNOWN_PTR(m_lpEnvelope, "Bad m_lpEnvelope");
	ASSERTERROR( m_sOffsetHeaders.LowPart != 0, "No headers detected");

    // The PR_TRANSPORT_MESSAGE_HEADERS envelope property is
    // merely a copy of the input "header" read by the inbound
    // conversion DLL.
    // Create this property now via a virtual (e.g. buffered) stream
	hr = HrOpenVirtualStreamOnProperty(
		m_lpEnvelope,					// MAPI object pointer
		PR_TRANSPORT_MESSAGE_HEADERS,	// property tag
		ulFlags,						// MAPI property flags
		&lpTransHdrStrm);				// virtual (buffered) stream pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERT_IUNKNOWN_PTR(lpTransHdrStrm, "Bad lpTransHdrStrm");

    // Seek to begining of input stream
    hr = m_lpStream->Seek(
        sOffsetBegin,   // offset
        STREAM_SEEK_SET,// from beginning
        NULL);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Copy input stream to transport header stream
    hr = m_lpStream->CopyTo(
                (LPSTREAM) lpTransHdrStrm,     // destination stream
                m_sOffsetHeaders,   // should be size of headers
                NULL,               // don't care
                NULL);              // don't care

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // save changes to the PR_TRANSPORT_MESSAGE_HEADER data stream.
    hr = lpTransHdrStrm->Commit(
            0);     // not going to do anything else but free it

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    // release the PR_TRANSPORT_MESSAGE_HEADER data strem
    ULRELEASE(lpTransHdrStrm);

    RETURN(hr);

}
