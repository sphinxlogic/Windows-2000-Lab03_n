// --toupper.c------------------------------------------------------------------
// 
// Converter that renders a message body to an attachment
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#define _MEMLOG_H           // skip mem logging stuff until it works in UNICODE.

#define EDK_USES_IID
#include "edk.h"
#include "vsop.h"
#include "toupper.chk"

//$--HrCnvQueryCapability-------------------------------------------------------
//
// DESCRIPTION: Routine called by the conversion engine to determine whether the converter
// can handle a particular message.
//
// INPUT:   
//          pszOptions  --  options passed from conversion
//          pszClass    --  class of object to be converted
//          pContent    --  object oto be converted.
//          pEnv    --  environment for conversion
//
// OUTPUT:  pfAmCandidate   --  TRUE if can convert, FALSE otherwise
//
// RETURNS: HRESULT --  NOERROR if successful,
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

    DEBUGPRIVATE("HrCnvQueryCapability()\n");

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

//$--HrConvertStreamToUpperCase-----------------------------------------------
//
// DESCRIPTION: Convert data in input stream to upper-case
//              equivalent in output stream.
//
// INPUT:       lpStreamIn  --  input stream to convert
//              lpStreamOut --  output stream to convert to
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// -----------------------------------------------------------------------------
static HRESULT HrConvertStreamToUpperCase(
        IN LPSTREAM lpStreamIn,         // input stream
        IN LPSTREAM lpStreamOut)        // output stream
{
// maximum # characters to read at a time
#define	MAX_CHARS_READ	8192

    HRESULT hr          =   NOERROR;
    ULONG   cbRead      =   0;          // # bytes read
	DWORD	cchUpper	=	0;			// # chars converted to upper case

    const ULONG cbWanted    =   8192 * sizeof(CHAR);   // # bytes wanted

	CHAR	rgchBuffer[MAX_CHARS_READ]	=	"";	// text buffer

    DEBUGPRIVATE("HrConvertStreamToUpperCase()\n");

    // check input parameters
    hr = CHK_HrConvertStreamToUpperCase(lpStreamIn, lpStreamOut);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    while ( TRUE )
    {
        // Read a block of characters from the input stream
        // & write the uppercase version to the output
        // stream.
        hr = OLECALL(lpStreamIn)->Read(
                    lpStreamIn,     // object pointer
                    rgchBuffer,     // data buffer
                    cbWanted,       // # bytes to read
                    &cbRead);       // # bytes read
                            
        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);
            
            goto cleanup;
        }

        // Test for end of data
        if ( cbRead == 0 )
        {
            // we are done.
            goto cleanup;
        }        

        ASSERTERROR(cbRead <= cbWanted, "Bad cbRead");

        // convert character buffer to upper case
        cchUpper = CharUpperBuffA(
        	rgchBuffer,				// character buffer
        	cbRead/sizeof(CHAR));	// # characters in buffer

		ASSERTERROR((cchUpper == cbRead * sizeof(CHAR)), "Bad cchUpper");

        // Write the upper-cased character to the output
        // stream
        hr = OLECALL(lpStreamOut)->Write(
                lpStreamOut,        // object pointer
                rgchBuffer,         // upper cased data
                cbRead,             // # bytes to write
                NULL);              // don't care

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

    }   // end while

    // we are done

cleanup:

    RETURN(hr);

}

//$--HrWriteToStreamA-----------------------------------------------------------
//
//  DESCRIPTION: Write an ANSI string to a stream.
//
//  INPUT:  lpStream    --  stream to write to
//          lpsz    --  string to write to stream
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
static HRESULT HrWriteToStreamA(  // RETURNS: HRESULT
    IN LPSTREAM lpStream,                   // stream to write to.    
    IN LPSTR lpsz)                          // ANSI string to write.
{
    HRESULT hr  =   NOERROR;        // return code
    ULONG ulBytesWritten = 0 ;
    ULONG ulBytesToWrite = 0;

    DEBUGPRIVATE("HrWriteToStreamA()\n");

    // check input parameters
    hr = CHK_HrWriteToStreamA(lpStream, lpsz);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    ulBytesToWrite = lstrlenA(lpsz) * sizeof(CHAR) ;

    hr = OLECALL(lpStream)->Write(lpStream, lpsz, ulBytesToWrite, &ulBytesWritten);
    
    if ( FAILED(hr) || (ulBytesWritten != ulBytesToWrite) )
    {
        hr = HR_LOG(E_FAIL);
        
        goto cleanup;
    }

cleanup:

    RETURN(hr);

}

//$--HrWriteToStreamW-----------------------------------------------------------
//
//  DESCRIPTION: Write a wide string to a stream.
//
//  INPUT:  lpStream    --  stream to write to
//          lpsz    --  string to write
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
static HRESULT HrWriteToStreamW(     // RETURNS: HRESULT
    IN LPSTREAM lpStream,                   // stream to write to.    
    IN LPWSTR lpsz)                         // wide string to write.
{
    HRESULT hr  =   NOERROR;        // return code
    ULONG ulBytesWritten = 0 ;
    ULONG ulBytesToWrite = 0;

    DEBUGPRIVATE("HrWriteToStreamW()\n");

    // Check input parameters
    hr = CHK_HrWriteToStreamW(lpStream, lpsz);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    ulBytesToWrite = lstrlenW(lpsz) * sizeof(WCHAR) ;

    hr = OLECALL(lpStream)->Write(lpStream, lpsz, ulBytesToWrite, &ulBytesWritten);
    
    if ( FAILED(hr) || (ulBytesWritten != ulBytesToWrite) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:
    
    RETURN(hr);

}

//$--HrCnvConvert---------------------------------------------------------------
//
//  DESCRIPTION: Perform the conversion.
//
//  INPUT:  
//          pszOptions  --  options (may be null)
//          pszClass    --  object class to be converted
//          pContent    --  objec to convert (GW message envelope pointer)
//          pEnv    --  environment for conversion
//          pContentOut --  converted object (stream pointer)
//
//  OUTPUT: 
//          pcr --  result of conversion
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
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
    HRESULT     				hr          = NOERROR;
    LPMESSAGE   				pEnvelope   = NULL; // gateway message envelope pointer
    LPATTACH    				pAttach     = NULL; // envelope's attachment
    LPMESSAGE   				pMessage    = NULL; // content is an IMessage.
    LPSTREAM 					lpStream    = NULL;	// output stream pointer
    PVIRTUALSTREAMONPROPERTY	pStrmBody	= NULL;	// buffered body text stream
   
    DEBUGPRIVATE("HrCnvConvert()\n");

    // check input parameters
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

    ASSERTERROR(!FBadUnknown(pAttach), "Bad lpAttach");

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

    ASSERTERROR(!FBadUnknown(pMessage), "Bad pMessage");

    //
    //  Write a header to the the lpStream.
    //
    hr = HrWriteToStreamA(lpStream, "Message body follows:\r\n") ;

    if (FAILED(hr))
    {
        goto cleanup ;
    }

    //
    // Get a buffered stream on the ASCII body of the message.from the PR_BODY
    // property.  (We really want PR_BODY for this
    // sample, since we want to print out a human-readable
    // body text.)
	hr = HrOpenVirtualStreamOnProperty(
		(LPMAPIPROP) pMessage,	// object pointer
		PR_BODY_A,				// property tag
		MAPI_DEFERRED_ERRORS,	// reduces RPCs
		&pStrmBody);			// buffered body stream pointer
                    
    if (SUCCEEDED(hr))
    {
        ASSERT_IUNKNOWN_PTR(pStrmBody, "Bad pStrmBody");

        //
        // There was a body.
        //

        //
        //  Convert the message to upper case.
        //
        hr = HrConvertStreamToUpperCase(
            (LPSTREAM) pStrmBody,   // buffered input stream
            lpStream);   			// output stream

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }
    else if (hr == MAPI_E_NOT_FOUND)
    {
        //
        //  No body.  Put in a fake body.
        // write fake body to stream
        hr = HrWriteToStreamA(
                lpStream, 
                "No Body") ;

        if (FAILED(hr))
        {
            goto cleanup ;
        }

        hr = HR_LOG(NOERROR);
    }
    else
    {
        //
        //  Other error, die.
        //
        hr = HR_LOG(E_FAIL);

        goto cleanup ;
    }

    // Commit changes to the stream.
    hr = OLECALL(lpStream)->Commit(
                lpStream,       // stream pointer
                STGC_DEFAULT);  // commit flags

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    //
    //  We're done.  Tell the converter we did OK.
    //
    *pcr = GCR_OK ;

cleanup:

    // Release MAPI objects.
    ULRELEASE(pMessage);
    ULRELEASE(pAttach);
    ULRELEASE(pStrmBody);

    RETURN(hr) ;

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
// OUTPUT:  ppConvDLLVect   --  pointer to conversion vector structure
//
// -----------------------------------------------------------------------------
extern HRESULT HrGetExportVector( // RETURNS: HRESULT
    IN DWORD dwVersionRequired,             // desired conversion DLL version number
    OUT PCONVDLLVECT FAR * ppConvDLLVect)   // pointer to conversion vector structure
{
    HRESULT hr  =   NOERROR;

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

