// --tnefdec.c------------------------------------------------------------------
//
//  Converter that decodes a TNEF copy of the message as an embedded message.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#define _MEMLOG_H           // skip mem logging stuff until it works in UNICODE.

#define USES_IID_IMessage
#include "edk.h"
#include "tnefdec.chk"

//
//  TNEF global variables.
//

// Note: OpenTnefStreamEx doesn't have exported wide and ansi versions.
// Thus, must let the compiler set the pszTNEFStreamName type.
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
// OUTPUT:  pfAmCandidate   --  TRUE if can be converted, FALSE otherwise
//
// RETURNS: HRESULT --  NOERROR if function call overall is successful
//                      E_INVALIDARG if bad input
//
// -----------------------------------------------------------------------------
static HRESULT HrCnvQueryCapability(    
    IN LPCWSTR pszOptions,                  // options passed from conversion engine
    IN LPCWSTR pszClass,                    // class of object to be converted.
    IN PVOID pContent,                      // object to be covnerted.
    IN PEDKCNVENV pEnv,                     // environment for conversion.
    OUT BOOL * pfAmCandidate)               // can convert?
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPRIVATE("HrConvQueryCapability\n");

    // Check input parameters
    hr = CHK_HrCnvQueryCapability(pszOptions, pszClass, pContent,
                                  pEnv, pfAmCandidate);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pfAmCandidate = TRUE ;             // yes, we can process it.

    RETURN(hr);

}


//$--HrCnvConvert---------------------------------------------------------------
//
//  DESCRIPTION: Perform the conversion.
//
//  INPUT:  
//          pszOptions  --  options
//          pszClass    --  object class to be converted
//          pContent    --  object to be converted (GW message envelope pointer)
//          pEnv    --  environment for conversion
//          pContentOut --  converted object (stream pointer)
//
//  OUTPUT: 
//          pcr --  result of conversion
//
//  RETURNS:    HRESULT --  NOERROR if function call overall if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
static HRESULT HrCnvConvert(      
    IN LPCWSTR pszOptions,                  // options.
    IN LPCWSTR pszClass,                    // object class to be converted.
    IN PVOID pContent,                      // object to be converted.
    IN PVOID pContentOut,                   // where to put the result.
    IN PEDKCNVENV pEnv,                     // environment for conversion.
    OUT EDKCNVRES * pcr)                    // result of conversion
{
    HRESULT     hr          =   NOERROR; 
    LPMESSAGE   pEnvelope   =   NULL;       // gateway envelope pointer
    LPMESSAGE   pMessage    =   NULL;       // envelope content pointer
    LPATTACH    pAttach     =   NULL;       // envelope attachment pointer
    LPSTREAM    lpStream    =   NULL;       // stream to write to
    LPITNEF     lpTnef      =   NULL;       // pointer to TNEF object.
    WORD        wKey        =   0;          // magic text tag cookie.
    ULONG       ulAttachNum =   0;          // attachment number
    SPropValue  rgProps[2]  =   {0};        // attachment properties

    //
    //  Declare an empty prop tag array to contain the
    //  list of properties that should not be included.
    //  I.e.:  include all properties in the TNEF.
    //  MAPI requires a list of properites that should not
    //  be copied to the TNEF.  By giving a zero length list
    //  for the list of properties to be excluded, all props
    //  will be included.
    //
    static SPropTagArray propEmptyPropTagArray  = {0, } ;

    DEBUGPRIVATE("HrCnvConvert()\n");

    // Check input parameters
    hr = CHK_HrCnvConvert(pszOptions, pszClass, pContent,
                          pContentOut, pEnv, pcr);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // The output is a gateway message envelope pointer
    pEnvelope = (LPMESSAGE) pContentOut;

    // The input is a stream pointer.
    lpStream = (LPSTREAM) pContent;

    // Get the envelope's content.
    hr = MAPICALL(pEnvelope)->CreateAttach(
                pEnvelope,      // message envelope pointer
                NULL,           // interface ID
                MAPI_DEFERRED_ERRORS, // MAPI flags
                &ulAttachNum,
                &pAttach);      // pointer to attachment pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    rgProps[0].ulPropTag = PR_ATTACH_METHOD;
    rgProps[0].Value.ul  = ATTACH_EMBEDDED_MSG;
    rgProps[1].ulPropTag = PR_RENDERING_POSITION;
    rgProps[1].Value.l   = 0;

    hr = MAPICALL(pAttach)->SetProps(pAttach, 2, rgProps, 0);

    if(FAILED(hr)) 
    {
	    goto cleanup;
	}

    // Open a message interface on the attachment.
    hr = MAPICALL(pAttach)->OpenProperty(
                pAttach,            // attachment pointer
                PR_ATTACH_DATA_OBJ, // property tag
                &IID_IMessage,       // interface ID reference
                0,                  // interface flags
                MAPI_CREATE | MAPI_MODIFY | MAPI_DEFERRED_ERRORS, // MAPI flags
                (LPUNKNOWN *) &pMessage);         // message pointer pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    //
    //  Setup TNEF.  Create a TNEF object to encode the message into
    //    lpStream (an attachment of the message.)
    // 
    // Note that there are no exported wide and ansi versions of OpenTnef
    // StreamEx.  Thus, pszTNEFStreamName's type must be set by the compiler.
    hr = OpenTnefStreamEx(
        NULL,
        lpStream, 
        pszTNEFStreamName,
        TNEF_DECODE,
        pMessage,
        0x01AF,       // magic number
                      // used to ID the TNEF
                      // attachment.
		pEnv->lpAB,
        &lpTnef);

    if (FAILED (hr))
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup ;
    }

    ASSERTERROR(lpTnef != NULL,"NULL lpTnef variable") ;

    //
    //  Specify which properties not to include. The list is empty,
    //  so no properties are excluded. All props are included.
    //

    hr = lpTnef->lpVtbl->ExtractProps(
        lpTnef,
        TNEF_PROP_EXCLUDE,
        &propEmptyPropTagArray,
        NULL);

    if (FAILED (hr))
    {
        goto cleanup ;
    }

	hr = MAPICALL(pMessage)->SaveChanges(pMessage, KEEP_OPEN_READWRITE);

	if(FAILED(hr))
	{
	    goto cleanup;
	}

	hr = MAPICALL(pAttach)->SaveChanges(pAttach, KEEP_OPEN_READWRITE);
    
    if(FAILED (hr)) 
    {
	    goto cleanup;
	}

	hr = MAPICALL(pEnvelope)->SaveChanges(pEnvelope, KEEP_OPEN_READWRITE);

	if(FAILED(hr))
	{
	    goto cleanup;
	}

    //
    //  We're done.  Tell the converter we did OK.
    //

    *pcr = GCR_OK ;

cleanup:

    // Release OLE and MAPI objects
    ULRELEASE(pAttach);
    ULRELEASE(pMessage);
    ULRELEASE(lpTnef);

    RETURN(hr) ;

}

//structure that points to all routines exported by this converter.
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
// OUTPUT:  ppConvDLLVect    --  pointer to export vector structure
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input.
//
// -----------------------------------------------------------------------------
extern HRESULT HrGetExportVector(        // RETURNS: HRESULT
    IN DWORD dwVersionRequired,             // desired version number
    OUT PCONVDLLVECT FAR * ppConvDLLVect)  // pointer to export vector structure
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPUBLIC("HrGetExportVector()\n");

    // Check input parameters
    hr = CHK_HrGetExportVector(dwVersionRequired, ppConvDLLVect);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *ppConvDLLVect = &cdExportVector;

    RETURN(hr);

}
