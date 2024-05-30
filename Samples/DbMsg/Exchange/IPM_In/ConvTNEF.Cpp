// --convtnef.cpp--------------------------------------------------------------
//
// Code for messages whose content is to be TNEFed.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All Rights Reserved.
// All rights reserved.
//
// ----------------------------------------------------------------------------

#include "edk.h"
#include "convcls.h"
#include "tagnames.h"
#include "msgemit.h"
#include "ipmcdefs.h"

//$--CIPMConvert::HrTnefToContent---------------------------------------------------------------
//
// DESCRIPTION: TNEF decodes TNEFed data from the input stream.
// to the envelope content.
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrTnefToContent()
{
    HRESULT             hr              =   NOERROR;
    LPTSTR              lpszTag         =   NULL;   // tag string pointer
    LPTSTR              lpszData        =   NULL;   // data string pointer
    LPITNEF             lpTnef          =   NULL;   // TNEF interface pointer
    LPSTnefProblemArray lpsProblems     =   NULL;   // property problem array
    ULONG               cbRead          =   0;      // # bytes read
    SPropTagArray       sNoPropTags     =   {0};    // property tag array

    DEBUGPRIVATE("CIPMConvert::HrTnefToContent()\n");

    // consistency checks
    ASSERTERROR(!FBadUnknown(m_lpStream), "Bad m_lpStream");
    ASSERTERROR(!FBadUnknown(m_lpAB), "Bad m_lpAB");
    ASSERTERROR(!FBadUnknown(m_lpEnvelope), "Bad m_lpEnvelope");

    // TNEF decode the saved TNEFed data.
    // This data contains the properties for the
    // envelope's content and all of its attachments.

    // First, read in the "MAPIMAIL.DAT" TNEF tag and data
    // from the input stream. (The data will be null).
    hr = HrParseTagAndData(
                m_lpStream,     // stream pointer
                &cbRead,        // # bytes read
                &lpszTag,       // tag pointer
                &lpszData);     // data pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Check the tag read
    if ( lstrcmp(lpszTag, lpszTagTnefHdr) != 0 )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Next, open a TNEF interface on the input stream
    // which we shall decode to the envelope content.
  	hr = OpenTnefStreamEx(
            NULL,
    	    m_lpStream,         // input stream pointer
    	    (LPTSTR) szTnefFileName,    // file name associated with TNEFed data
    		TNEF_DECODE,        // decode the message properties
    		m_lpEnvelope,       // destination message pointer
    		wTnefKey,           // "unique" TNEF key
    		m_lpAB,             // address book pointer
    		&lpTnef);           // TNEF interface object pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(!FBadUnknown(lpTnef), "Bad lpTnef");

    // Decode all properties to the envelope content
    hr = lpTnef->ExtractProps(
            TNEF_PROP_EXCLUDE,      // exclude
            (LPSPropTagArray) &sNoPropTags, // no properties to exclude
            &lpsProblems);          // property problem array pointer

    if ( FAILED(hr) )       // Don't care about MAPI_W_ERRORS_RETURNED in this case
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // we are done!

cleanup:

    // Release all OLE and MAPI objects
    ULRELEASE(lpTnef);

    // Free MAPI buffers
    MAPIFREEBUFFER(lpsProblems);
    MAPIFREEBUFFER(lpszTag);
    MAPIFREEBUFFER(lpszData);

    RETURN(hr);

}
