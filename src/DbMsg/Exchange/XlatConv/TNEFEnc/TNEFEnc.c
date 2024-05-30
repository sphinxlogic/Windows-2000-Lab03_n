// --tnefenc.c------------------------------------------------------------------
//
//  Converter that Adds a TNEF copy of the message as an attachment.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#define _MEMLOG_H           // skip mem logging stuff until it works in UNICODE.

#define USES_IID_IMessage
#include "edk.h"
#include "tnefenc.chk"

//
//  TNEF global variables.
//
// Note:  OpenTnefStreamEx does not export separate wide character and
// ansi versions.  Thus, we must let the compiler set the pszTNEFStreamName
// type.
static LPTSTR pszTNEFStreamName = TEXT("MAPIDATA.DAT");

//$--HrCnvQueryCapability-------------------------------------------------------
//
// DESCRIPTION: Routine called by the conversion engine to determine whether the converter
// can handle a particular message.
//
// INPUT:   
//          pszOptions  --  options passed from conversion
//          pszClass    --  class of object to be converted
//          pContent    --  object to be converted
//          pEnv    --  environment for conversion
//
// OUTPUT:  pfAmCandidate   --  TRUE if can convert, FALSE otherwise
//
// RETURNS: HRESULT --  NOERROR if overall success,.
//                      E_INVALIDARG if bad input.
//
// -----------------------------------------------------------------------------
static HRESULT HrCnvQueryCapability(     
    IN LPCWSTR pszOptions,                  // options passed from conversion engine
    IN LPCWSTR pszClass,                    // class of object to be converted.
    IN PVOID pContent,                      // object to be covnerted.
    IN PEDKCNVENV pEnv,                     // environment for conversion.
    OUT BOOL * pfAmCandidate)               // can convert?
{
    HRESULT hr  =   NOERROR;        // return code

    DEBUGPRIVATE("HrCnvQueryCabability()\n");

    // check input parameters
    hr = CHK_HrCnvQueryCapability(pszOptions, pszClass, pContent,
                                  pEnv, pfAmCandidate);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pfAmCandidate = TRUE ;             // yes, we can process it.

    RETURN(hr) ;

}


//$--HrCnvConvert---------------------------------------------------------------
//
//  DESCRIPTION: Perform the conversion.
//
//  INPUT:  
//          pszOptions  --  options
//          pszClass    --  class of object to convert
//          pContent    --  object to be converted (GW message envelope pointer)
//          pEnv    --  environment for conversion
//          pContentOut --  converted object ( stream pointer)
//
//  OUTPUT: 
//          pcr --  result of conversion
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
static HRESULT HrCnvConvert(     
    IN LPCWSTR pszOptions,                  // options.
    IN LPCWSTR pszClass,                    // object class to be converted.
    IN PVOID pContent,                      // object to be covnerted.
    IN PVOID pContentOut,                   // where to put the result.
    IN PEDKCNVENV pEnv,                     // environment for conversion.
    OUT EDKCNVRES * pcr)                    // result of conversion
{
    HRESULT     hr          =   NOERROR;
    LPMESSAGE   pEnvelope   =   NULL;       // gateway envelope pointer
    LPMESSAGE   pMessage    =   NULL;       // content is an IMessage.
    LPATTACH    pAttach     =   NULL;       // envelope attachment pointer
    LPSTREAM    lpStream    =   NULL;       // stream to be opened on attachment content.   
    ULONG       i           =   0;
    ULONG       cValues     =   0;
    ULONG       ulPropTag   =   0;
    LPITNEF     lpTnef      =   NULL;       // pointer to TNEF object.
    WORD        wKey        =   0;          // magic text tag cookie.

    //
    //  Declare an property tag array to contain the
    //  list of properties that should not be included.
    //
    SPropTagArray *lpPropTagArray = NULL;

    DEBUGPRIVATE("HrCnvConvert()\n");

    // check input
    hr = CHK_HrCnvConvert(pszOptions, pszClass, pContent,
                          pContentOut, pEnv, pcr);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // The input is a gateway message envelope pointer
    pEnvelope = (LPMESSAGE) pContent;

    // The output is a stream pointer.
    lpStream = (LPSTREAM) pContentOut;

    // Get the envelope's content.
    hr = MAPICALL(pEnvelope)->OpenAttach(
                pEnvelope,      // message envelope pointer
                0,              // attachment number
                NULL,           // interface ID reference
                MAPI_DEFERRED_ERRORS, // MAPI flags
                &pAttach);      // pointer to attachment pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Open a message interface on the attachment.
    hr = MAPICALL(pAttach)->OpenProperty(
                pAttach,            // attachment pointer
                PR_ATTACH_DATA_OBJ, // property tag
                &IID_IMessage,       // interface ID reference
                0,                  // interface flags
                MAPI_DEFERRED_ERRORS,             // MAPI flags
                (LPUNKNOWN *) &pMessage);         // message pointer pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Note:  OpenTnefStreamEx does not have exported versions for
    // wide character and ansi.  Thus, must let compiler set the pszTNEFStreamName
    // type.
	hr = OpenTnefStreamEx(
	    NULL,
	    lpStream,
	    pszTNEFStreamName, 
		TNEF_ENCODE,
		pMessage,
		0x01AF,
		pEnv->lpAB,
		&lpTnef);

	if(FAILED(hr))
	{
        hr = HR_LOG(E_FAIL);

        goto cleanup;
	}

    ASSERTERROR(lpTnef != NULL,"NULL lpTnef variable") ;

	hr = pMessage->lpVtbl->GetPropList(
	    pMessage,
	    0,
		&lpPropTagArray);

	if(FAILED(hr))
	{
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

	// Build a new prop tag array containing only non-transmittable properties.

	cValues = 0;

	for(i = 0; i < lpPropTagArray->cValues; i++)
	{
		ulPropTag = lpPropTagArray->aulPropTag[i];

		if ((!FIsTransmittable(ulPropTag)) &&
			(ulPropTag != PR_MESSAGE_RECIPIENTS) &&
			(ulPropTag != PR_MESSAGE_ATTACHMENTS))
		{
			lpPropTagArray->aulPropTag[cValues++] = ulPropTag;
		}
	}

	lpPropTagArray->cValues = cValues;

	// Exclude selected properties from the TNEF encapsulation.

	hr = lpTnef->lpVtbl->AddProps(
	    lpTnef,
		TNEF_PROP_EXCLUDE,
		0,
		NULL,
		lpPropTagArray);

	if(FAILED(hr))
	{
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

	hr = lpTnef->lpVtbl->Finish(lpTnef, 0, &wKey, NULL);

	if(FAILED(hr))
	{        
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

    // Commit changes to stream.
	hr = lpStream->lpVtbl->Commit(lpStream, STGC_DEFAULT);

	if(FAILED(hr))
	{        
        hr = HR_LOG(E_FAIL);
        goto cleanup;
	}

    //
    //  We're done.  Tell the converter we did OK.
    //
    *pcr = GCR_OK ;

cleanup:

    MAPIFREEBUFFER(lpPropTagArray);

    ULRELEASE(pAttach);
    ULRELEASE(pMessage);

    ULRELEASE(lpTnef);

    RETURN(hr);

}

// structure that points to all routines exported by this converter.
static CONVDLLVECT cdExportVector = 
{ 
    1, 
    HrCnvQueryCapability, 
    HrCnvConvert
} ;

//$--HrGetExportVector---------------------------------------------------------
//
// DESCRIPTION: Called by conversion engine to get the vector of conversion entry points.
//
// INPUT:   dwVersionRequired   --  desired version number
//
// OUTPUT:  ppConvDLLVect   --  pointer to conversion vector structure
//
// RETURNS: HRESULT --  NOERROR if successful
//                      E_INVALIDARG if bad input
//
// -----------------------------------------------------------------------------
extern HRESULT HrGetExportVector(        // RETURNS: HRESULT
    IN DWORD dwVersionRequired,             // desired versioin number
    OUT PCONVDLLVECT FAR *ppConvDLLVect)    //  pointer to conversion vector structure
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPUBLIC("HrGetExportVector()\n");

    // check input parameters
    hr = CHK_HrGetExportVector(dwVersionRequired, ppConvDLLVect);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *ppConvDLLVect = &cdExportVector;

    RETURN(hr);

}
