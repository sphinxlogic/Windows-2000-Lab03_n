// --edkrtf.c------------------------------------------------------------------
//
// EDK utility functions to help with creating the PR_RTF_COMPRESSED
// message property.
//
// Copyright (C) Microsoft Corp. 1986-1996, All rights reserved.
//
// ----------------------------------------------------------------------------

#include "edk.h"
#include "edkrtf.chk"

//$--HrTextToRTFCompressed------------------------------------------------
//
// DESCRIPTION: Convert plain ANSI text to its RTF compressed 
//              equivalent for a MAPI message.
// 
// INPUT:       cchText --  number of text character to convert
//              lpText  --  plain ANSI text to convert
//                              cAttachments    --      # of message attachments
//                              rgiRendering    --      array of attachment rendering positions
//              lpMsg   --  MAPI message pointer for which to create
//                          the compressed rich text
//              cpid    --  code page of the text stream
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                                                      MAPI_E_* if IMAPIProp::OpenProperty() fails during RTF 
//                                                              property creation,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrTextToRTFCompressed(
	    IN ULONG cchText,       // # characters of text
	    IN LPSTREAM lpText,     // plain text stream pointer
		IN ULONG cAttachments,  // # of message attachments
		IN ULONG * rgiRendering,// array of attachment rendering positions
	    IN LPMESSAGE lpMsg,     // MAPI message pointer
		IN ULONG cpid)
{
    HRESULT         hr                      =  NOERROR;
    LPSTREAM        lpText2                 =  NULL;// text stream
	LPSTREAM        lpRTFText               =  NULL;// uncompressed RTF stream
    LPSTREAM        lpRTFComp               =  NULL;// RTF compressed stream
    LPSTREAM        lpRTFUnComp             =  NULL;// uncompressed RTF stream
	ULONG           iAttach                 =  0;   // attachment index
	ULARGE_INTEGER  cbBlockSize             =  {INT_MAX,0};
	ULARGE_INTEGER  cbTextSize              =  {cchText,0};
    ULARGE_INTEGER  scbRead                 =  {0}; // # bytes read from stream
    ULARGE_INTEGER  scbWritten              =  {0}; // # bytes written to stream
    LARGE_INTEGER   cbTopOfFile             =  {0};
    // MAPI property creation flags
    const ULONG ulFlags = MAPI_CREATE | MAPI_MODIFY | MAPI_DEFERRED_ERRORS;

    DEBUGPUBLIC("HrTextToRTFCompressed()\n");
    
	// check input parameters
    hr = CHK_HrTextToRTFCompressed(cchText, lpText, cAttachments, 
							      rgiRendering, lpMsg, cpid);
	if (FAILED(hr))
	{
		RETURN(hr);
	}

    // Create another stream and copy only the bytes we want to it.
    // We do this since we don't know the number of RTF compressed
    // bytes to copy to the message.
    // 1.) Create lpTextStream2
    // 2.) Copy the correct number of bytes over
    
	hr = CreateStreamOnHGlobal(
            NULL,   // it will allocate the memory
            TRUE,   // free memory on release
            &lpText2);
	
	if (FAILED(hr))
    {
        goto cleanup;
    }

    hr = OLECALL(lpText)->CopyTo(lpText, lpText2, cbTextSize, &scbRead, &scbWritten);

    if (FAILED(hr))
    {
        goto cleanup;
    }

	hr = OLECALL(lpText2)->Commit(lpText2, STGC_DEFAULT);
	
	if (FAILED(hr))
	{
		goto cleanup;
	}

    hr = OLECALL(lpText2)->Seek(lpText2, 
								cbTopOfFile,    
								STREAM_SEEK_SET,
								NULL);

	if (FAILED(hr))
		goto cleanup;

    hr  = HrRTFFromTextStream(lpText2, &lpRTFText, cpid, cAttachments, rgiRendering);

	if (FAILED(hr))
	{
		goto cleanup;
	}

    ASSERT_IUNKNOWN_PTR(lpRTFText, "Bad lpRTFText");

    // Open a stream on the newly created PR_RTF_COMPRESSED
    // message property.
    hr = MAPICALL(lpMsg)->OpenProperty(
	    lpMsg,                  // message pointer
	    PR_RTF_COMPRESSED,      // property tag
	    &IID_IStream,           // interface ID reference
	    STGM_CREATE | STGM_WRITE,   // interface flags
	    ulFlags,                // MAPI flags
	    (LPUNKNOWN *) &lpRTFComp);  // stream pointer

	if (FAILED(hr))
	{
		// Return MAPI error.

		goto cleanup;
	}

    ASSERT_IUNKNOWN_PTR(lpRTFComp, "Bad lpRTFComp");

	hr = WrapCompressedRTFStream (lpRTFComp, MAPI_CREATE | MAPI_MODIFY, &lpRTFUnComp);
	
	if (FAILED(hr))
	{
		goto cleanup;
	}

	hr = OLECALL(lpRTFText)->CopyTo(lpRTFText,
								lpRTFUnComp,
								cbBlockSize,
								&scbRead,
								&scbWritten);
	if (FAILED(hr))
	{
		goto cleanup;
	}


	hr = OLECALL(lpRTFUnComp)->Commit(lpRTFUnComp, STGC_DEFAULT);
	
	if (FAILED(hr))
	{
		goto cleanup;
	}

cleanup:

    // Release MAPI & OLE objects
    ULRELEASE(lpText2);
    ULRELEASE(lpRTFText);
    ULRELEASE(lpRTFComp);
	ULRELEASE(lpRTFUnComp);

    RETURN(hr);

}

//$--HrRTFCompressedToText--------------------------------------------------
//
// DESCRIPTION: Convert message's compressed RTF to its ANSI 
//              equivalent.
// 
// INPUT:       lpMsg   --  MAPI message pointer for which to retrieve
//                          the ANSI text.
//              pText   --  pointer to stream to copy ANSI text to.
//              cpid    --  code page for the text stream
//
// OUTPUT:      pcb     --  # bytes copied to stream
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          MAPI_E_* if IMAPIProp::OpenProperty() fails during RTF
//                                                              property open,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrRTFCompressedToText(
	    IN LPMESSAGE lpMsg,         // MAPI message pointer
	    IN LPSTREAM pText,          // stream to copy ANSI text to
			IN ULONG cpid,                          // code page
	    OUT ULONG * pcb)            // # bytes copied to stream
{
    HRESULT         hr          =   NOERROR;
    LPSTREAM        lpRTFComp   =   NULL;   // RTF compressed stream
    LPSTREAM        lpTextWrap  =   NULL;   // "wrapper" stream pointer
    RTFSYNCINFO     sRtfSync    =   {0};    // RTFSYNCINFO structure
    ULARGE_INTEGER  scbInfinite =   {0};    // "infinite" large integer
    ULARGE_INTEGER  scbWritten  =   {0};    // # bytes written to stream

    DEBUGPUBLIC("HrRTFCompressedToText()\n");

    // check input parameters
    hr = CHK_HrRTFCompressedToText(lpMsg, pText, cpid, pcb);

    if ( FAILED(hr) )
    {
	RETURN(hr);
    }

    // initialize output parameters
    *pcb = 0;

    // Open a stream interface on the message's RFT compressed
    // message text property.
    hr = MAPICALL(lpMsg)->OpenProperty(
		lpMsg,                  // message pointer
		PR_RTF_COMPRESSED,      // property tag
		&IID_IStream,           // interface ID reference
		STGM_READ,              // interface flags
		MAPI_DEFERRED_ERRORS,   // reduces RPCs
		(LPUNKNOWN *) &lpRTFComp);  // stream pointer

    if ( FAILED(hr) )
    {
	// Return MAPI error.

	goto cleanup;
    }

    ASSERT_IUNKNOWN_PTR(lpRTFComp, "Bad lpRTFComp");

    // Convert RTF compressed stream data to ANSI "wrapper" stream.
    // The ANSI wrapper stream supports only the CopyTo and Read
    // methods.
    hr = HrTextFromCompressedRTFStreamEx(
		lpRTFComp,  // RTF compressed stream pointer
		&lpTextWrap,// pointer to wrapper stream pointer
		&sRtfSync,  // RTFSYNCINFO pointer
		cpid,       // code page (use default)
		0,          // zero attachments
		NULL);      // no attachment array

    if ( FAILED(hr) )
    {
	goto cleanup;
    }

    ASSERT_IUNKNOWN_PTR(lpTextWrap, "Bad lpTextWrap");

    // Copy the contents of the "wrapper" stream (which only supports
    // the Read & CopyTo methods) to the stream provided.
    scbInfinite.LowPart = INFINITE; // want to copy all data
    hr = OLECALL(lpTextWrap)->CopyTo(
		lpTextWrap,     // stream pointer
		pText,          // destination stream
		scbInfinite,    // # bytes to copy
		NULL,           // don't care
		&scbWritten);   // # bytes copied

    if ( FAILED(hr) )
    {
	goto cleanup;
    }

    // check that number of bytes written is less than
    // what we can handle.
    if ( (scbWritten.LowPart == INFINITE) ||
	 (scbWritten.HighPart != 0) )
    {
	hr = HR_LOG(E_NOTIMPL);

	goto cleanup;
    }

    // Fill in number of bytes copied
    *pcb = scbWritten.LowPart;

    // we are done

cleanup:

    // Release MAPI and OLE objects
    ULRELEASE(lpRTFComp);
    ULRELEASE(lpTextWrap);

    RETURN(hr);

}
