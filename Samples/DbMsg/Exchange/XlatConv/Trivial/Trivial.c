// --trivial.c------------------------------------------------------------------
// 
// Module demonstrates simplest message converter.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#define EDK_USES_IID
#include "edk.h"
#include "trivial.chk"

//$--HrCnvQueryCapability-------------------------------------------------------
//
// DESCRIPTION: Routine called by the conversion engine to determine whether the converter
// can handle a particular message.
//
// INPUT:   
//          pszOptions  --  options passed from conversion (may be null)
//          pszClass    --  class of object to be converted
//          pContent    --  object to be converted
//          pEnv    --  environment for conversion
//
// OUTPUT:  pfAmCandidate   --  TRUE if can convert, FALSE otherwise.
//
// RETURNS: HRESULT --  NOERROR if call if successful,
//                      E_INVALIDARG if bad input,
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

    DEBUGPRIVATE("HrCnvQueryCapability()\n");

    // check input parameters
    hr = CHK_HrCnvQueryCapability(pszOptions, pszClass, pContent,
                                  pEnv, pfAmCandidate);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pfAmCandidate = TRUE ;                 // say that we can take it.

    RETURN(hr) ;

}

//$--HrWriteToStreamA-----------------------------------------------------------
//
//  DESCRIPTION: Write an ANSI string to a stream.
//
//  INPUT:  lpStream --  stream to write to
//          lpsz    --  string to write
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise.
//
// -----------------------------------------------------------------------------
static HRESULT HrWriteToStreamA(         // RETURNS: HRESULT
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

//$--HrCnvConvert---------------------------------------------------------------
//
//  DESCRIPTION: Perform the conversion.
//
//  INPUT:  
//          pszOptions  --  options         (may be null)
//          pszClass    --  object class to be converted
//          pContent    --  object to convert (GW message envelope)
//          pEnv    --  environment for conversion
//          pContentOut --  converted object (stream  pointer)
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
    HRESULT     hr          =   NOERROR;    // return code
    LPMESSAGE   pEnvelope   =   NULL;       // gateway message envelope pointer
    LPATTACH    pAttach     =   NULL;       // envelope attachment pointer
    LPMESSAGE   pMessage    =   NULL;       // envelope content pointer
    LPSTREAM    lpStream    =   NULL;       // output stream pointer

    DEBUGPRIVATE("HrCnvConvert()\n");

    // check input paramters
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

    //
    //  Write a header to the attachment via the lpStream.
    //
    hr = HrWriteToStreamA(lpStream, "This attachment is intentionally empty.\r\n") ;

    if (FAILED(hr))
    {
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

    ULRELEASE(pAttach);
    ULRELEASE(pMessage);    

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
// INPUT:  dwVersion    --  version of conversion requested.
//
// OUTPUT: ppConvDLLVect --  pointer to export vector structure
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG otherwise
//
// -----------------------------------------------------------------------------
extern  HRESULT HrGetExportVector(         // RETURNS: HRESULT
        IN DWORD dwVersion,                   // version requested
        OUT PCONVDLLVECT FAR * ppConvDLLVect) // pointert to export vector structure
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPUBLIC("HrGetExportVector()\n");

    // Check input parameters
    hr = CHK_HrGetExportVector(dwVersion, ppConvDLLVect);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *ppConvDLLVect = &cdExportVector;

    RETURN(hr);

}
