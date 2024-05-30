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

//$--CIPMConvert::HrContentToTnef---------------------------------------------------------------
//
// DESCRIPTION: TNEF encodes everything below the envelope.
// (e.g. the content and its attachments)
//
// INPUT:       none
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrContentToTnef()
{
    HRESULT             hr          =   NOERROR;
    LPITNEF             lpTnef      =   NULL;   // TNEF interface pointer
    WORD                wKey        =   0;      // attachments key
    LPSPropTagArray     lpsPropTags =   NULL;   // property tag array pointer
    ULONG               ulPropTag   =   0;      // property tag
    ULONG               iPropTag    =   0;      // index into the property tag array
    ULONG               cExclude    =   0;      // count of properties to exclude
    LPSTnefProblemArray lpsProblems =   NULL;   // problem array pointer

    // Want to include the recipient properites in the TNEF data.
    SizedSPropTagArray(1, sRecipPropTag)    =
    {
        1,
        {
            PR_MESSAGE_RECIPIENTS
        }
    };

    DEBUGPRIVATE("CIPMConvert::HrContentToTnef()\n");

    // consistency checks
    ASSERTERROR(!FBadUnknown(m_lpStream), "Bad m_lpStream");
    ASSERTERROR(!FBadUnknown(m_lpAB), "Bad m_lpAB");
    ASSERTERROR(!FBadUnknown(m_lpEnvelope), "Bad m_lpEnvelope");

    // TNEF the envelope's content and all of its attachments.

    // First, write out the "MAPIMAIL.DAT" TNEF section header
    // to the output stream.
    hr = HrEmitTagDataLine(
                lpszTagTnefHdr,     // tag
                (LPTSTR) lpszNullData,  // data
                m_lpStream);        // stream pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Next, open a TNEF interface on the envelope which writes its
    // output to the output stream.
  	hr = OpenTnefStreamEx(
            NULL,
    	    m_lpStream,         // output stream pointer
    	    (LPTSTR) szTnefFileName,    // file name associated with TNEFed data
    		TNEF_ENCODE,        // encode the message properties
    		m_lpEnvelope,       // source message pointer
    		wTnefKey,           // "unique" TNEF key
    		m_lpAB,             // address book pointer
    		&lpTnef);           // TNEF interface object pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(!FBadUnknown(lpTnef), "Bad lpTnef");

    // Encode all transmittable properties for the envelope content and
    // its attachments to the TNEFed stream.
    // First, get a list of all properties on the source message.
    hr = m_lpEnvelope->GetPropList(
            fMapiUnicode,       // MAPI flags
            &lpsPropTags);

    if ( FAILED(hr) )   // don't care about MAPI_W_ERRORS_RETURNED in this case
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERTERROR(!IsBadReadPtr(lpsPropTags, sizeof(LPSPropTagArray)), 
                "Bad lpsPropTags.");

    // Now, build a new list of non-transmittable properties
    // which we wish to exclude from the TNEF data.
    for ( iPropTag = 0; iPropTag < lpsPropTags->cValues; iPropTag++ )
    {
        ulPropTag = lpsPropTags->aulPropTag[iPropTag];

        // See if we have a property which is transmittable, but
        // we still wish to exclude (gateway can't set some
        // transmittable properties)
  		if ((ulPropTag == PR_SENT_REPRESENTING_NAME) ||
   			(ulPropTag == PR_SENT_REPRESENTING_ADDRTYPE) ||
   			(ulPropTag == PR_SENT_REPRESENTING_EMAIL_ADDRESS) ||
   			(ulPropTag == PR_SENT_REPRESENTING_SEARCH_KEY) ||
   			(ulPropTag == PR_SENT_REPRESENTING_ENTRYID))
        {
            lpsPropTags->aulPropTag[cExclude] = ulPropTag;
            cExclude++;

        }   // end property transmittable but not wanted

        // See if we have a non-transmittable property which we
        // really wish to exclude
   		else if ((!FIsTransmittable(ulPropTag)) &&
    			(ulPropTag != PR_TRACE_INFO) &&
    			(ulPropTag != PR_MTS_SUBJECT_ID) &&
    			(ulPropTag != PR_ORIGINATOR_NAME) &&
    			(ulPropTag != PR_ORIGINATOR_ADDRTYPE) &&
    			(ulPropTag != PR_ORIGINATOR_ADDR) &&
    			(ulPropTag != PR_ORIGINATOR_ENTRYID) &&
    			(ulPropTag != PR_REPORT_DESTINATION_NAME) &&
    			(ulPropTag != PR_REPORT_DESTINATION_ENTRYID) &&
    			(ulPropTag != PR_MESSAGE_RECIPIENTS) &&
    			(ulPropTag != PR_MESSAGE_ATTACHMENTS))
        {
            lpsPropTags->aulPropTag[cExclude] = ulPropTag;
            cExclude++;

        }   // end if property is non-transmittable & not wanted
    }   // end for

    // Exclude the list of properties just built from the TNEFed
    // data.
    lpsPropTags->cValues = cExclude;    // # of properties to exclude
    hr = lpTnef->AddProps(
            TNEF_PROP_EXCLUDE | // wish to exclude these properties
            TNEF_PROP_ATTACHMENTS_ONLY, // only want to encode the attachments
            0,              // attachemnt ID (not used)
            NULL,           // no special attachment data
            lpsPropTags);   // property tag array pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Include the message recipient properties.
    hr = lpTnef->AddProps(
            TNEF_PROP_INCLUDE | // wish to include these properties
            TNEF_PROP_ATTACHMENTS_ONLY, // only want to encode the attachments
            0,              // attacment ID (not used)
            NULL,           // special attachment data
            (LPSPropTagArray) &sRecipPropTag);  // property tag array pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Save the TNEFed information to the output stream.
    hr = lpTnef->Finish(
                0,      // flags
                &wKey,  // attachments key
                &lpsProblems);  // problem array pointer

    if ( FAILED(hr) )   // don't care about MAPI_W_ERRORS_RETURNED in this case
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    // Release all OLE and MAPI objects
    ULRELEASE(lpTnef);

    // Free MAPI buffers
    MAPIFREEBUFFER(lpsProblems);
    MAPIFREEBUFFER(lpsPropTags);

    RETURN(hr);

}

//$--CIPMConvert::HrOpenContent------------------------------------------------
//
// DESCRIPTION: Utility function to open the envelope's content.
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CIPMConvert::HrOpenContent()
{
    HRESULT         hr              =   NOERROR;

    DEBUGPRIVATE("CIPMConvert::HrOpenContent()\n");

    // consistency checks
    ASSERT_IUNKNOWN_PTR(m_lpEnvelope, "Bad m_lpEnvelope");
    ASSERTERROR(m_lpAttach == NULL, "MEMORY LEAK of m_lpAttach");
    ASSERTERROR(m_lpContent == NULL, "MEMORY LEAK of m_lpContent");

    // Open the message content which is attached to the envelope.
    // The content's attachment number is always 0.        
    hr = m_lpEnvelope->OpenAttach(
        0,      // attachment #
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
    hr = m_lpAttach->OpenProperty(PR_ATTACH_DATA_OBJ,
                                    &IID_IMessage,  // interface identifier
                                    0,              // interface flags
                                    MAPI_DEFERRED_ERRORS,   // reduces RPCs
                                    (LPUNKNOWN *) &m_lpContent);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    ASSERT_IUNKNOWN_PTR(m_lpContent, "Bad m_lpContent");

cleanup:

    // m_lpContent & m_lpAttachment are released by Reset().

    RETURN(hr);

}
