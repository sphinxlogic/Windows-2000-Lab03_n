//--vsop.cpp---------------------------------------------------------------
//
// Stream wrapper class for large MAPI properties.
//
// Copyright (C) Microsoft Corp, 1986-1996.  All rights reserved.
//
//-----------------------------------------------------------------------------

#include "edk.h"
#include "_vsop.h"
#include "vsop.chk"

//$--HrOpenVirtualStreamOnProperty------------------------------------------
//
// DESCRIPTION:
// API to open a buffered stream on a binary or string property
// Callable from "C" or "C++"
//
// INPUT:	pPropObject	--	MAPI property object pointer
//			ulPropTag	--	property tag to open stream on
//			ulFlags		--	MAPI property flags (MAPI_MODIFY, MAPI_CREATE)
//
// OUTPUT:	ppVirtualStreamOnProperty	--	 pointer to buffered stream on property
//
// RETURNS:	HRESULT	--	NOERROR if successful,
//						E_INVALIDARG if bad input,
//						E_OUTOFMEMORY if memory problems,
//						E_FAIL otherwise
//
//-----------------------------------------------------------------------------
STDAPI HrOpenVirtualStreamOnProperty(
    IN LPMAPIPROP pPropObject,	// MAPI property object pointer
    IN ULONG ulPropTag,     	// property tag to open virtual stream on
	IN ULONG ulFlags,			// MAPI property flags
    OUT PVIRTUALSTREAMONPROPERTY * ppVirtualStreamOnProperty)  // pointer buffered stream
{
	// Implemented by local C++ function _HrOpenVirtualStreamOnProperty().
	// Doing this allows us to declare _HrOpenVirtualStreamOnProperty() as
	// a friend of the CEDKVitrualStreamOnProperty class.
	RETURN(_HrOpenVirtualStreamOnProperty(pPropObject, ulPropTag, ulFlags, ppVirtualStreamOnProperty));
}

//$--_HrOpenVirtualStreamOnProperty---------------------------------------------
//
// DESCRIPTION:  same as for _HrOpenVirtualStreamOnProperty, but its a local
//				 C++ function instead of an exported "C" function.
//
// INPUT:		ditto
//
// OUTPUT:		ditto
//
// RETURNS:		ditto
//
//-----------------------------------------------------------------------------
HRESULT _HrOpenVirtualStreamOnProperty(
    IN LPMAPIPROP pPropObject,	// MAPI property object pointer
    IN ULONG ulPropTag,     	// property tag to open virtual stream on
	IN ULONG ulFlags,			// MAPI property flags
    OUT PVIRTUALSTREAMONPROPERTY * ppVirtualStreamOnProperty)  // pointer buffered stream
{
    HRESULT             hr              =   NOERROR;
    CEDKVirtualStreamOnProperty * pVirtualStreamOnProperty    =   NULL;       // stream wrapper pointer

    DEBUGPUBLIC("HrOpenVirtualStreamOnProperty()");

    // check input parameters
    hr = CHK_HrOpenVirtualStreamOnProperty(pPropObject, ulPropTag, ulFlags,
    										  ppVirtualStreamOnProperty);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // initialize output parameters.
    *ppVirtualStreamOnProperty = NULL;

    // Instantiate a new virtual stream on property object
    pVirtualStreamOnProperty = new CEDKVirtualStreamOnProperty();
    
    if ( pVirtualStreamOnProperty == NULL )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERT_IUNKNOWN_PTR(pVirtualStreamOnProperty, "Bad pVirtualStreamOnProperty");

    // pVirtualStreamOnProperty reference count is now 1.

    // Initialize VSOP instance.
    hr = pVirtualStreamOnProperty->HrInitialize(
    	pPropObject,// property object pointer
    	ulPropTag,	// property tag
    	ulFlags);	// MAPI property flags

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Retrieve an IEDKVirtualStreamOnProperty interface.
    hr = pVirtualStreamOnProperty->QueryInterface(
        IID_IEDKVirtualStreamOnProperty,          // interfac ID reference
        (LPVOID *) ppVirtualStreamOnProperty);      // IEDKVirtualStreamOnProperty interface pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    ASSERT_READ_PTR(ppVirtualStreamOnProperty, sizeof(PVIRTUALSTREAMONPROPERTY), 
        "Bad ppVirtualStreamOnProperty");
    ASSERT_IUNKNOWN_PTR(*ppVirtualStreamOnProperty, "Bad *ppVirtualStreamOnProperty");

    // pVirtualStreamOnProperty reference count is now 2.

    // we are done

cleanup:

    // Release our copy of the pVirtualStreamOnProperty pointer.
    ULRELEASE(pVirtualStreamOnProperty);

    // pVirtualStreamOnProperty reference count is now 1 in success case.

    RETURN(hr);

}

//--$CEDKVirtualStreamOnProperty::CEDKVirtualStreamOnProperty---------------------------------------
//
// DESCRIPTION: Constructor for CEDKVirtualStreamOnProperty.
//
// INPUT: none
//
// RETURNS: nothing
//
//-----------------------------------------------------------------------------
CEDKVirtualStreamOnProperty::CEDKVirtualStreamOnProperty()
{
    DEBUGPRIVATE("CEDKVirtualStreamOnProperty::CEDKVirtualStreamOnProperty()\n");

	// initialize data members
	m_pStream = NULL;		// unbuffered stream pointer (if any)
	m_pPropObject = NULL;
	m_ulPropTag = 0;
	m_ulFlags = 0;			// MAPI property flags
	m_rgbBuffer = NULL;
	m_pbBuffer = NULL;	// pointer into the character buffer
	m_cbBuffer = 0;		// current size of character buffer
	m_fDataInitialized = FALSE;	// TRUE if data buffer has been initialized

    ZeroMemory(
    	&m_StatStg,
		sizeof(m_StatStg));

	// increment reference count        
    m_refs = 1;

}

//--$CEDKVirtualStreamOnProperty::~CEDKVirtualStreamOnProperty---------------------------------------
//
// DESCRIPTION: Destructor for CEDKVirtualStreamOnProperty.
//
// INPUT: none
//
// RETURNS: nothing
//
//-----------------------------------------------------------------------------
CEDKVirtualStreamOnProperty::~CEDKVirtualStreamOnProperty()
{
    DEBUGPRIVATE("CEDKVirtualStreamOnProperty::~CEDKVirtualStreamOnProperty()\n");

	// consistency check
	ASSERTERROR(m_refs == 0, "Bad m_refs.");

	// Release "real" stream, if any	
	ULRELEASE(m_pStream);

	m_ulFlags = 0;			// MAPI property flags
	m_pPropObject = NULL;
	m_ulPropTag = 0;

	// Free data buffer memory, if any.
	MAPIFREEBUFFER(m_rgbBuffer);

	m_pbBuffer = NULL;	// pointer into the character buffer
	m_cbBuffer = 0;		// current size of character buffer
	m_fDataInitialized = FALSE;

    ZeroMemory(
    	&m_StatStg,
		sizeof(m_StatStg));
	
    m_refs = 0;

}

//--$CEDKVirtualStreamOnProperty::HrInitialize-------------------------------------------
//
// DESCRIPTION:  Initialize CEDKVirtualStreamOnProperty instance.
//
// INPUT:   pPropObject	--	pointer to MAPI property object
//          ulPropTag	--	property tag
//			ulFlags		--	MAPI property access flags
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//						E_FAIL otherwise.
//
//-----------------------------------------------------------------------------
HRESULT CEDKVirtualStreamOnProperty::HrInitialize(
	IN LPMAPIPROP pPropObject,	// pointer to MAPI property object
	IN ULONG ulPropTag,			// property tag
	IN ULONG ulFlags)			// MAPI property access flags
{
    HRESULT     hr          =   NOERROR;
    SYSTEMTIME  sSystemTime =   {0};        // System Time structure
    BOOL        fRetVal     =   FALSE;      // Win32 error code.

    DEBUGPRIVATE("CEDKVirtualStreamOnProperty::HrInitialize()\n");

    // check input parameters
    hr = CHK_CEDKVirtualStreamOnProperty_HrInitialize(pPropObject, ulPropTag,
    	ulFlags);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	// Save options
	m_ulFlags = ulFlags;
	m_pPropObject = pPropObject;
	m_ulPropTag = ulPropTag;

	// Zero out storage statistics function.
	ZeroMemory(&m_StatStg, sizeof(STATSTG));
                
	// Set storage type for streams.
    m_StatStg.type = STGTY_STREAM;

	// Set mode in storage statistics structure to
	// lowest common denominator (for reads).
    SetMode(STGM_READ | STGM_SHARE_EXCLUSIVE);

    // Don't care about or support other stream statistics.

    // we are done

    RETURN(hr);

}

//$--CEDKVirtualStreamOnProperty::HrOpenUnderlyingStream--------------------------------
//
// DESCRIPTION:	Open or create an underlying stream for reading or writing.
//
// INPUT:		none
//
// RETURNS:		HRESULT	--	NOERROR if successful,
//							E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CEDKVirtualStreamOnProperty::HrOpenUnderlyingStream()
{
	HRESULT	hr			=	NOERROR;
	ULONG	ulIIDFlags	=	STGM_SHARE_EXCLUSIVE;	// default stream mode flags

	DEBUGPRIVATE("CEDKVirtualStreamOnProperty::HrOpenUnderlyingStream()\n");

	// consistency check
	ASSERT_IUNKNOWN_PTR(m_pPropObject, "Bad m_pPropObject");
	
	// Determine if need stream modification (writing)
	if ( fIsWriteProperty() == TRUE )
	{
		ulIIDFlags |= STGM_WRITE;
	}
				
	// Determine if need stream creation.
	if ( fIsNewProperty() == TRUE )
	{
		ulIIDFlags |= STGM_CREATE;
	}

	// Open/create a stream on the property
	hr = m_pPropObject->OpenProperty(
		m_ulPropTag,		// property tag
		&IID_IStream,		// interface identifier reference
		ulIIDFlags,			// interface flags
		m_ulFlags | MAPI_DEFERRED_ERRORS,	// MAPI property creation flags
		(LPUNKNOWN *) &m_pStream);	// stream pointer

	if ( FAILED(hr) )
	{
		// Return the MAPI error code

		goto cleanup;
	}

	// Adjust mode in the storage statistics structure
	SetMode(ulIIDFlags);

 	// we are done.

cleanup:

	RETURN(hr);

}

//$--CEDKVirtualStreamOnProperty::HrFlushWriteBuffer---------------------------
//
// DESCRIPTION:	Flushes data in write buffer to the underlying stream.
//
// INPUT:		fCleanOutWriteBuffer	--	TRUE if should zero out the write buffer
//
// RETURNS:		HRESULT	--	NOERROR if successful,
//							E_FAIL otherwise.
//
//-----------------------------------------------------------------------------
HRESULT CEDKVirtualStreamOnProperty::HrFlushWriteBuffer(
	IN BOOL fCleanWriteBuffer)	// TRUE if should zero out the write buffer
{
	HRESULT			hr				=	NOERROR;
	ULONG			cbWrite			=	0;		// # bytes to flush
	ULONG			cbWritten		=	0;		// # bytes written
	LARGE_INTEGER	cbWriteStream	=	{0};	// # bytes to write to underlying stream

	DEBUGPRIVATE("CEDKVirtualStreamOnProperty::HrFlushWriteBuffer()\n");

	// See if we have an underlying stream to write to.
	if ( m_pStream == NULL )
	{
		// Open stream on property & write contents
		// of buffer to it & readjust buffer data members.
		hr = HrOpenUnderlyingStream();

		if ( FAILED(hr) )
		{
			// Return any possible MAPI error code due to property access errors.

			goto cleanup;
		}
	}	// end if no underlying stream

	// By the time we get here, we should have an underlying
	// stream
	ASSERT_IUNKNOWN_PTR(m_pStream, "Bad m_pStream");

	// Determine number of bytes which need to be flushed from buffer.
	cbWrite = GetBytesWritten();

	// Flush contents of buffer to the stream
	hr = m_pStream->Write(
		m_rgbBuffer,		// Source buffer
		cbWrite,			// # bytes to write
		&cbWritten);		// # bytes written

	if ( FAILED(hr) )
	{
		goto cleanup;
	}

	// Check # of bytes written
	if ( cbWritten != cbWrite )
	{
		hr = HR_LOG(E_FAIL);

		goto cleanup;
	}

	// Adjust size of stream in the storage statistics
	// structure.
	cbWriteStream.LowPart = cbWritten;
	IncrementStreamSize(cbWriteStream);

	// Clean out write buffer, if requested
	if ( fCleanWriteBuffer == TRUE )
	{
		InitBufferSize(m_cbBuffer);
	}

	// We are done

cleanup:

	RETURN(hr);

}

//---------------------------------------------------------------------
//                        IUnknown methods
//---------------------------------------------------------------------

// $--CEDKVirtualStreamOnProperty::QueryInterface------------------------------------------
//
// DESCRIPTION:	Return pointer to object which implements the desired
//				interface, if this object supports the interface.
//
// INPUT:
//
//  [riid]	-- Reference to interface identifier of desired interface.
//
//  [ppv]	-- Ptr to object which supports interface.  NULL if none.
//
// RETURNS:     NOERROR if successful;
//				E_INVALIDARG if bad input.
//				E_NOINTERFACE if interface isn't supported.
//
//  Interfaces supported:
//      
//      IUnknown
//      IEDKVirtualStreamOnProperty
//
//---------------------------------------------------------------------------

STDMETHODIMP CEDKVirtualStreamOnProperty::QueryInterface(
	IN REFIID riid,   // interface ID reference
	OUT	LPVOID * ppvObj)    // pointer to interface pointer
{
    HRESULT hr =	NOERROR;

    DEBUGPRIVATE("CEDKVirtualStreamOnProperty::QueryInterface().\n");

    hr = CHK_CEDKVirtualStreamOnProperty_QueryInterface(riid, ppvObj);

    if (FAILED(hr))
    {
        RETURN(hr);
    }

    // initialize output parameter
    *ppvObj = NULL;

    // See if we support the requested interface.

    if (IsEqualIID(riid, IID_IUnknown))   // IUnknown interface is ourself
	{
	    *ppvObj = this;    // Return ourself
	}

    else if (IsEqualIID(riid, IID_IEDKVirtualStreamOnProperty))
    {
        // User wants our programatic interface, which is ourselves.
	    *ppvObj = this;
    }
    else 
    {
        // We don't support the requested interface.
        hr = HR_LOG(E_NOINTERFACE);                 

        goto cleanup;
    }

    // If we reach this point, no error occurred.  Increment reference count.
    AddRef();

cleanup:

    RETURN(hr);
}

//$--CEDKVirtualStreamOnProperty::AddRef--------------------------------------------------
//
// DESCRIPTION:	Increment the reference count on this object.
//
// INPUT:		None.
//
// RETURNS:     New reference count.
//
//---------------------------------------------------------------------------

STDMETHODIMP_(ULONG) CEDKVirtualStreamOnProperty::AddRef()	// RETURNS: ULONG
{
    DEBUGPRIVATE("CEDKVirtualStreamOnProperty::AddRef().\n");

    ASSERTERROR(m_refs, "Bad m_refs.");

    m_refs++;

    return m_refs;
}

//$--CEDKVirtualStreamOnProperty::Release-------------------------------------------------
//
// DESCRIPTION:	Decrement the reference count on this object.  If the
//				reference count reaches 0, destroy this object.
//
// INPUT:		None.
//
// RETURNS:     New reference count.
//
//---------------------------------------------------------------------------

STDMETHODIMP_(ULONG) CEDKVirtualStreamOnProperty::Release()	// RETURNS: ULONG
{
    ULONG   ulRefCount =	0;

    DEBUGPRIVATE("CEDKVirtualStreamOnProperty::Release().\n");

    ASSERTERROR(m_refs, "Bad m_refs.");

    m_refs--;

    if ( m_refs == 0 )
    {
        delete this;
        ulRefCount = 0;
    }
    else
    {
        ulRefCount = m_refs;
    }

    return ulRefCount;
}

//$--CEDKVirtualStreamOnProperty::HrComputeCurrentSize-------------------------
//
// DESCRIPTION:	Calculates current stream size
//
// IN:			pcbSize	--	unsigned large integer structure pointer
//
// RETURNS:		HRESULT	--	NOERROR if successful,
//							E_INVALIDARG if bad input,
//							E_FAIL otherwise.
//
//-----------------------------------------------------------------------------
HRESULT CEDKVirtualStreamOnProperty::HrComputeCurrentSize(
		IN ULARGE_INTEGER * pcbSize)	// unsigned large integer pointer
{
	HRESULT			hr			=	NOERROR;
	DWORDLONG		cbTotal		=	0;			// total size of virtual stream
	DWORDLONG		cbStream	=	0;			// size of underlying stream

	DEBUGPRIVATE("CEDKVirtualStreamOnProperty()\n");

	// check input parameters
	hr = CHK_CEDKVirtualStreamOnProperty_HrComputeCurrentSize(pcbSize);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Intialize output parameter
	ZeroMemory(pcbSize, sizeof(ULARGE_INTEGER));

	// Check to see that data buffer is initialized
	if ( fDataInitialized() == FALSE )
	{
		// First data buffer has not been initialized.
		if ( fIsWriteProperty() == TRUE )
		{
			// Have a write property.
			// Currently, virtual write stream is zero bytes.
			// We are done.
			goto cleanup;
		}

		else
		{
			// Have a read property.
			// Need to set up underlying data.
			// Do this by reading 0 bytes from the property.
			hr = Read(
				NULL,
				0,
				NULL);

			if ( FAILED(hr) )
			{
				goto cleanup;
			}

			ASSERT_IUNKNOWN_PTR(m_pStream, "Bad m_pStream");

		}	// end if read property
	}	// end if underlying data hasn't been initialized

	// By the time we get to here, the underlying data has
	// been initialize.
	ASSERTERROR(fDataInitialized() == TRUE, "Bad state");

	// See if there is an uderlying stream.
	if ( m_pStream == NULL )
	{
		if ( fIsReadProperty() == TRUE )
		{
			// have a read property
			// size of stream is size of property buffer.
			cbTotal = m_cbBuffer;
		}

		else	// have a write property
		{
			// size of stream is number of bytes written to write buffer.
			cbTotal = GetBytesWritten();
		}
	}	// end if no underlying stream

	else	// have an underlying stream
	{
		// Stream size if the size of the underlying stream
		// (which is maintained in the stream statistics structure for
		// write buffers and must be read directly from stream for
		// read buffers)
		// plus the size of the write data buffer.
		cbStream = MAKEDWORDLONG(	// Size of underlying stream
	 		m_StatStg.cbSize.LowPart,
			m_StatStg.cbSize.HighPart);

		// See if we have a read or a write stream
		if ( (fIsWriteProperty() == TRUE) )
		{
			// have a write stream 
			cbTotal = cbStream + GetBytesWritten();
		}	

		else	// have a read stream
		{
			// See if we need to retrieve the stream size
			if ( cbStream == 0 )
			{
				// need to retrieve read stream size.
				hr = m_pStream->Stat(
					&m_StatStg,			// storage statistics structure pointer
					STATFLAG_NONAME);	// statistics flags

				if ( FAILED(hr) )
				{
					goto cleanup;
				}
			}	

		 	// Size of virtual read stream is just size of underlying stream.
			cbTotal = MAKEDWORDLONG(
				m_StatStg.cbSize.LowPart,
				m_StatStg.cbSize.HighPart);

		}	// end if have a read stream
	}	// end if there is an underlying buffer

	// Set output variables.
	pcbSize->LowPart = LOWDWORD(cbTotal);
	pcbSize->HighPart = HIDWORD(cbTotal);

	// We are done

cleanup:

	RETURN(hr);

}

// IStream methods

//$--CEDKVirtualStreamOnProperty::Read---------------------------------------------------
//
// DESCRIPTION: Read the number of bytes requested from our "stream" to the
//              output buffer.
//
// INPUT:       pv  --  pointer to output buffer
//              cb  --  maximum number of bytes to read
//
// OUTPUT:      pcb --  number of bytes actually read, may be NULL.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          STG_E_INVALIDPARAMETER if bad input,
//							STG_E_ACCESSDENIED if not read stream,
//							STG_E_INSUFFICIENTMEMORY if memory problems,
//							MAPI_E_* if property access fails,
//							STG_E_UNKNOWN if unexpected error,
//                          STG_E_READFAULT otherwise.
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::Read(
        IN LPVOID pv,       // output buffer pointer
        IN ULONG cb,        // maximum # of bytes to read
        OUT ULONG * pcb)    // # of bytes read
{
    HRESULT 		hr      	=   NOERROR;
	LPSPropValue	lpsProp		=	NULL;		// property array pointer
	ULONG			nProps		=	0;			// # of properties
	ULONG			cbProp		=	0;			// # bytes in property
	BYTE *			pbData		=	NULL;		// data pointer
	ULONG			cbUnread	=	0;			// # bytes unread in buffer
	ULONG			cbRead		=	0;			// # bytes to read from buffer
	BYTE *			pbDest		=	NULL;		// pointer into output buffer
	ULONG			cbTotalRead	=	0;			// Total # bytes read

	SizedSPropTagArray(1, sPropTag) =			// property tag array
	{
		1,					// number of properties
		{
			m_ulPropTag		// property tag desired
		}
	};

    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::Read()\n");

    // check input parameters
    hr = CHK_CEDKVirtualStreamOnProperty_Read(pv, cb, pcb);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Initialize output variables
	if ( pcb != NULL )
	{
    	*pcb = 0;
	}

    ZeroMemory(pv, cb);
        
	pbDest = (BYTE *) pv;			// pointer into output buffer

	// Read is only valid for properties opened for reading
	if ( fIsReadProperty() == FALSE )
	{
		hr = HR_LOG(STG_E_ACCESSDENIED);

		goto cleanup;
	}

	// Algorithm: (simplified for clarity).  These steps may correspond
	// to helper methods yet to be written.
	//
	// 1) If data buffer is empty, try to retrieve entire property at once
	// via the IMAPIProp::GetProps() method.
	// If this succeeds, read cb bytes out of data buffer into
	// output buffer and goto cleanup.
	//
	// 2) If data buffer is empty, then 
	// open a "real" stream on the property and copy 8K bytes from the
	// stream to the data buffer.  Read cb bytes out of the data buffer
	// into the output buffer and goto cleanup.
	//
	// 3) If data buffer is not empty and we have not reached the end of the data
	// buffer, then read the next cb bytes out of the data buffer into the
	// output buffer and goto cleanup.
	//
	// 4) If we have reached the end of the data buffer and there is no underlying
	// stream, then read 0 bytes from the data buffer and goto cleanup.
	//
	// 5) Otherwise, we have reached the end of the data buffer and there is
	// an underlying stream. Retrieve the next 8K bytes from the stream and 
	// copy these to the data buffer.  Read cb bytes from the data buffer to the
	// output buffer and goto cleanup.
	// 

	// Check to see if data buffer is empty because
	// we haven't retrieved any data yet.
	if ( fDataInitialized() == FALSE )
	{
		// data buffer is empty.
		// Try to retrieve whole property into 8K buffer.
		hr = m_pPropObject->GetProps(
			(LPSPropTagArray) &sPropTag,	// property tag array pointer
			fMapiUnicode,					// MAPI flags
			&nProps,						// number of properties retrieved
			&lpsProp);						// property array pointer

		// Check to see if property is too big to fit in buffer
		if ( FAILED(hr) || (hr == MAPI_W_ERRORS_RETURNED) )
		{
			// Check to see if property is to big to retrieve
			// via GetProps()
			if ( ( (hr == MAPI_W_ERRORS_RETURNED) &&
		    	   (lpsProp[0].Value.l == MAPI_E_NOT_ENOUGH_MEMORY) ) ||
				 (hr == MAPI_E_NOT_ENOUGH_MEMORY) )
			{
				// Open a stream on the property.
				ASSERT_IUNKNOWN_PTR(m_pPropObject, "Bad m_pPropObject");

				hr = m_pPropObject->OpenProperty(
					m_ulPropTag,				// property tag
					&IID_IStream,				// stream interface
					STGM_READ | STGM_SHARE_EXCLUSIVE,	// interface flags
					MAPI_DEFERRED_ERRORS,		// reduces RPCs
					(LPUNKNOWN *) &m_pStream);	// stream pointer

				if ( FAILED(hr) )
				{
					// Return MAPI error code.

					goto cleanup;
				}

				ASSERT_IUNKNOWN_PTR(m_pStream, "Bad m_pStream");

				// Allocate 8K buffer to hold some of the stream data.
				hr = MAPIAllocateBuffer(
					cbMaxBuffered,				// # bytes to allocate
					(LPVOID *) &m_rgbBuffer);	// data buffer pointer

				if ( FAILED(hr) )
				{
					hr = HR_LOG(STG_E_INSUFFICIENTMEMORY);

					goto cleanup;
				}

				ASSERT_READ_PTR(m_rgbBuffer, cbMaxBuffered, "Bad m_rgbBuffer");
						
				// Read 8K of stream data into the data buffer and
				hr = m_pStream->Read(
					m_rgbBuffer,		// destination buffer pointer
					cbMaxBuffered,		// # bytes to read
					&cbRead);			// # bytes read
								
				if ( FAILED(hr) )
				{
					goto cleanup;
				}			
		
				// set data buffer members.
				InitBufferSize(cbRead);

			}	// end if property too big

			// Otherwise, we have a fatal error
			else
			{
				// Return MAPI error code.

				goto cleanup;

			}	// end if have other error
		}	// end if error on GetProps() call

		else if ( SUCCEEDED(hr) )
		{
			// Property can be retrieved via GetProps().
			// Do some checks
			ASSERTERROR(nProps == 1, "Bad nProps");
			ASSERT_READ_PTR(lpsProp, sizeof(SPropTagArray), "Bad lpsProp");

			// Make sure that property will fit in our buffer.
			if ( PROP_TYPE(m_ulPropTag) == PT_BINARY )
			{
				// have a binary property
				cbProp = lpsProp[0].Value.bin.cb;
				pbData = lpsProp[0].Value.bin.lpb;	// data pointer
			}

			else if ( PROP_TYPE(m_ulPropTag) == PT_TSTRING )
			{
				// have a string property
				cbProp = lstrlen(lpsProp[0].Value.LPSZ) * sizeof(CHAR);
				pbData = (BYTE *) lpsProp[0].Value.LPSZ;	// data pointer
			}

			else
			{
				// This shouldn't happen
				ASSERTERROR(FALSE, "Bad m_ulPropTag");

				hr = HR_LOG(STG_E_UNKNOWN);

				goto cleanup;
			}

			// Set data buffer members
			// First, copy property data to our local data buffer
			hr = MAPIAllocateBuffer(
				cbProp,						// number of bytes to allocate
				(LPVOID *) &m_rgbBuffer);	// data buffer pointer

			if ( FAILED(hr) )
			{
				hr = HR_LOG(STG_E_INSUFFICIENTMEMORY);

				goto cleanup;
			}

			ASSERT_READ_PTR(m_rgbBuffer, cbProp, "Bad m_rgbBuffer");

			CopyMemory(
				m_rgbBuffer,		// destination buffer
				pbData,				// source buffer
				cbProp);			// number of bytes

			// Set data buffer members
			InitBufferSize(cbProp);

		}	// end if property can fit in our data buffer

		// Test for real failures
		else if ( FAILED(hr) || (hr == MAPI_W_ERRORS_RETURNED) )
		{
			// Return MAPI error code.

			goto cleanup;
		}
	}	// end if haven't gotten any data yet.
	
	ASSERT_READ_PTR(m_rgbBuffer, m_cbBuffer, "Bad m_rgbBuffer");

	// When we get to here, we will have data in the buffer.
	// Try to read the desired number of bytes from the buffer.
	while ( cbTotalRead < cb )
	{
		// First, determine the number of unread bytes in the buffer.
		cbUnread = GetBytesUnread();

		// Check to see if we need to refill the data buffer
		if ( cbUnread == 0 )
		{
			// We need to refill the data buffer.
			// See if there is an underlying stream to read more
			// data from.  If not, then we are done.
			if ( m_pStream == NULL )
			{
				// No more data. 
				// We are done.
				break;
			}

			ASSERT_IUNKNOWN_PTR(m_pStream, "Bad m_pStream");

			// Read more data from underlying stream
			hr = m_pStream->Read(
				m_rgbBuffer,		// data buffer pointer
				cbMaxBuffered,		// # bytes to read				
				&cbRead);			// # bytes read

			if ( FAILED(hr) )
			{
				goto cleanup;
			}

			// Set up data buffer members
			InitBufferSize(cbRead);

			// Re-calculate the number of unread data bytes
			cbUnread = GetBytesUnread();

			// Re-test for end of data condition
			if ( cbUnread == 0 )
			{
				// we are done.
				break;
			}

		}	// end if need to refill data buffer

		// Determine number of bytes to read from buffer.
		cbRead = min(cbUnread, cb);

		// Read data from data buffer to output buffer
		CopyMemory(
			pbDest,		// destination buffer pointer
			m_pbBuffer,	// source buffer
			cbRead);	// # bytes to copy

		// Adjust data buffer pointers
		IncrementBytesRead(cbRead);
		pbDest += cbRead;

		// increment number of bytes read
		cbTotalRead += cbRead;

	}	// end while

    // we are done

cleanup:

	// Set output variables (handles case of partial reads)
	if ( pcb != NULL )
	{
		(*pcb) = cbTotalRead;
	}

	// Free MAPI buffers
	MAPIFREEBUFFER(lpsProp);

    RETURN(hr);

}

//$--CEDKVirtualStreamOnProperty::Write---------------------------------------------------
//
// DESCRIPTION: Write the number of bytes requested from the buffer to the
//              "stream".
//
// INPUT:       pv  --  pointer to buffer
//              cb  --  number of bytes to write
//
// OUTPUT:      pcb --  number of bytes written -- may be NULL
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          STG_E_INVALIDPARAMETER if bad input,
//							STG_E_ACCESSDENIED if not write stream,
//							STG_E_INSUFFICIENTMEMORY if memory problems,
//							MAPI_E_* if property access fails,
//                          STG_E_WRITEFAULT otherwise.
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::Write(
        IN VOID const * pv, // data to write
        IN ULONG cb,        // # bytes to write
        OUT ULONG *pcb)     // # bytes written
{
	HRESULT 		hr			=	NOERROR;
	BYTE *			pbSource	=	NULL;		// pointer into source buffer
	ULONG			cbUnwritten	=	0;			// # of unwritten bytes in buffer
	ULONG			cbWrite		=	0;			// # of bytes to write
	ULONG			cbTotalWrite=	0;			// total # bytes written

    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::Write()\n");

	// Check input parameters
	hr = CHK_CEDKVirtualStreamOnProperty_Write(pv, cb, pcb);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Initialize output paramters.
	if ( pcb != NULL )
	{
		*pcb = 0;
	}

	pbSource = (BYTE *) pv;	// pointer into source buffer

	// If we don't have a write buffer, then we fail.
	if ( fIsWriteProperty() == FALSE )
	{
		hr = HR_LOG(STG_E_ACCESSDENIED);

		goto cleanup;
	}

	// Algorithm:
	//
	// 1) If data buffer isn't full, copy cb bytes from input buffer
	// to the data buffer.  If data buffer becomes full during this process,
	// goto step 2).  Otherwise, goto cleanup.
	//
	// 2) If data buffer is full or has become full in step and there is
	// no underlying stream, then open or create
	// the underlying stream on the property, as appropriate (based on m_ulFlags).
	//
	// 3) If the data buffer is full, write the contents of the data buffer
	// to the underlying stream.  Then, if there is still any additional data
	// to be written, copy it to the now empty data buffer.  Goto cleanup.

	// If no current data buffer, make one.
	if ( fDataInitialized() == FALSE )
	{
		// Create a data buffer to write to.
		// Buffer includes "extra" room for null-termination of exactly 8K
		// string.
		hr = MAPIAllocateBuffer(
			cbMaxBuffered + sizeof(CHAR),	// # bytes to allocate
			(LPVOID *) &m_rgbBuffer);		// data buffer pointer

		if ( FAILED(hr) )
		{
			hr = HR_LOG(STG_E_INSUFFICIENTMEMORY);

			goto cleanup;
		}

		// Set data buffer members
		InitBufferSize(cbMaxBuffered);

	}	// end if no data buffer	

	ASSERT_READ_PTR(m_rgbBuffer, m_cbBuffer, "Bad m_rgbBuffer");

	// Copy data to data buffer,
	while ( cbTotalWrite < cb )
	{
		// Determine number of unwritten bytes left in buffer.
		cbUnwritten = GetBytesUnwritten();

		// See if we need to flush out the write buffer.
		if ( cbUnwritten == 0 )
		{
			// Flush data written to the underlying stream,
			// making sure to reset the write buffer.
			hr = HrFlushWriteBuffer(TRUE);

			if ( FAILED(hr) )
			{
				// Return possbile MAPI error code due to property access failure

				goto cleanup;
			}

			// continue on to handle writing of pv input data
			continue;

		}	// end if need to flush write buffer
		
		ASSERTERROR(cbUnwritten != 0, "Bad cbUnwritten");

		// Compute number of byte to write to data buffer
		cbWrite = min(cb, cbUnwritten);

		// Write the desired number of bytes
		CopyMemory(
			m_pbBuffer,			// destination buffer pointer
			pbSource,			// source buffer
			cbWrite);			// # bytes to copy

		// Update the number of bytes written
		IncrementBytesWritten(cbWrite);
		pbSource += cbWrite;

		// increment total number of bytes written
		cbTotalWrite += cbWrite;

	}	// end while

	// We are done.

cleanup:

	// Set output variables (handles case of partial writes)
	if ( pcb != NULL )
	{
		(*pcb) = cbTotalWrite;
	}

    RETURN(hr);

}

//$--CEDKVirtualStreamOnProperty::CopyTo---------------------------------------------------
//
// DESCRIPTION: Copy the number of bytes requested from the "source" stream to the
//              destination stream.
//
// INPUT:       pStrm  --  destination stream pointer
//              cb  --  number of bytes to copy
//
// OUTPUT:      pcbRead --  number of bytes read -- may be NULL
//              pcbWritten  --  number of bytes written -- may be NULL
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          STG_E_INVALIDPARAMETER if bad input,
//							error codes from Read() and Write(),
//                          E_FAIL otherwise.
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::CopyTo(
        IN LPSTREAM pStrm,              // destination stream pointer
        IN ULARGE_INTEGER cb,           // # bytes to copy
        OUT ULARGE_INTEGER * pcbRead,   // # bytes read
        OUT ULARGE_INTEGER * pcbWritten)// # bytes written
{
    HRESULT 		hr          =   NOERROR;
    ULONG   		cbRead      =   0;          // # bytes read from source
    ULONG   		cbWritten   =   0;          // # bytes written to destination
	ULONG			cbDesired	=	0;			// # bytes desired
	DWORDLONG		cbTemp1		=	0;			// temporary byte count
	DWORDLONG		cbTotalRead	=	0; 			// # bytes read so far
	DWORDLONG		cbTotalWrite=	0;			// # bytes written so far
	DWORDLONG		cbTotalReq	=	0;			// # total bytes desired

	CHAR	rgchBuffer[cbMaxBuffered]	=	{0};	// data buffer

    DEBUGPUBLIC("CEDKStreamWrappr::CopyTo()\n");

    // check input parameters
    hr = CHK_CEDKVirtualStreamOnProperty_CopyTo(pStrm, cb, pcbRead, pcbWritten);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Initialize output variables
	if ( pcbRead != NULL )
	{
		ZeroMemory(pcbRead, sizeof(ULARGE_INTEGER));
	}

	if ( pcbWritten != NULL )
	{
		ZeroMemory(pcbWritten, sizeof(ULARGE_INTEGER));
	}

	// _int64s are easier to do arithmetic on than LARGE_INTEGER structures
	cbTotalReq = MAKEDWORDLONG(cb.LowPart, cb.HighPart);

	while ( cbTotalRead < cbTotalReq )
	{
    	// Read up to 8K bytes from the source stream (using IStream::Read() method)

		// First, determine # bytes to read.
		cbTemp1 = cbTotalReq - cbTotalRead;

		if ( HIDWORD(cbTemp1) != 0 )
		{
			cbDesired = cbMaxBuffered;	// read 8K bytes
		}

		else
		{
			cbDesired = min(cbMaxBuffered, LOWDWORD(cbTemp1));
		}

		hr = Read(
			rgchBuffer,		// data buffer
			cbDesired,		// # bytes to read
			&cbRead);		// # bytes read

		if ( FAILED(hr) )
		{
			goto cleanup;
		}
	
		// compute current total number of bytes read.
		cbTotalRead += cbRead;

		// Check for end of stream
		if ( cbRead == 0 )
		{
			// we are done
			break;
		}

		ASSERTERROR(cbRead == cbDesired, "Bad cbRead");

	    // Write cb bytes to the destination stream (using IStream::Write() method)
		hr = pStrm->Write(
			rgchBuffer,		// data buffer
			cbRead,			// # bytes just read
			&cbWritten);	// # bytes written

		if ( FAILED(hr) )
		{
			goto cleanup;
		}

		// Compute current total number of bytes written
		cbTotalWrite += cbWritten;

		ASSERTERROR(cbWritten == cbRead, "Bad cbWritten");

	}	// end while

    // We are done
        
cleanup:

	// Set output paremeters (handles case of partial read or write)
	if ( pcbRead != NULL )
	{
		pcbRead->LowPart = LOWDWORD(cbTotalRead);
		pcbRead->HighPart = HIDWORD(cbTotalRead);
	}

	if ( pcbWritten != NULL )
	{
		pcbWritten->LowPart = LOWDWORD(cbTotalWrite);
		pcbWritten->HighPart = HIDWORD(cbTotalWrite);
	}

    RETURN(hr);

}

//$--CEDKVirtualStreamOnProperty::Commit---------------------------------------------------
//
// DESCRIPTION: Save changes to the stream.
//
// INPUT:       dwFlags --  flags
//
// OUTPUT:      None
//
// RETURNS:     HRESULT --  NOERROR if successful,
//							STG_E_WRITEFAULT if problems writting,
//							MAPI_E_* if property access fails,
//							STG_E_UNKNOWN if unexpected problem.
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::Commit( 
        IN DWORD dwFlags)   // flags
{
	HRESULT				hr			=	NOERROR;
	SPropValue			sPropValue	=	{0};		// property value
	LPSPropProblemArray	lpsProblems	=	NULL;		// property problem array pointer
	ULONG				cbWrite		=	0;			// # bytes to write to stream
	ULONG				iProp		=	0;			// property problem index

    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::Commit()");

	// Check to see if are only doing reads on the property/
	if ( fIsReadProperty() == TRUE )
	{
		// nothing to do.
		MODULE_WARNING("Commit() does nothing when called on a read stream.");

		goto cleanup;
	}
		
	// Algorithm:
	//
	// 1) If there is no underlying stream and there is data in the buffer,
	// then try to write the data to the property via the IMAPIPROP::SetProps() method.
	// If this succeeds, then save the changes to the property object and
	// go to cleanup.
	//
	// 2) If the SetProps() in step 1) failed, then open or create a stream
	// on the underlying property.
	//
	// 3) Write any data in the buffer to the underlying stream.  Commit the
	// changes to the underlying stream and save the changes to the 
	// property object.  Go to cleanup.

	// See if there is any unflushed data in the data buffer.
	cbWrite = GetBytesWritten();

	if ( cbWrite > 0 )
	{
		// If we have no underlying stream, try a SetProps()
		// first.
		if ( m_pStream == NULL )
		{
			ASSERT_IUNKNOWN_PTR(m_pPropObject, "Bad m_pPropObject");

			// Set up property value structure.
			sPropValue.ulPropTag = m_ulPropTag;	// property tag

			if ( PROP_TYPE(m_ulPropTag) == PT_BINARY )
			{
				// have a binary property
				sPropValue.Value.bin.cb = cbWrite;		// property size
				sPropValue.Value.bin.lpb = m_rgbBuffer;	// property value				
			}

			else if ( PROP_TYPE(m_ulPropTag) == PT_TSTRING )
			{
				// have a string property
				sPropValue.Value.LPSZ = (LPSTR) m_rgbBuffer;	// property value
			}

			else
			{
				// This shouldn't happen
				ASSERTERROR(FALSE, "Bad property tag type");

				hr = HR_LOG(STG_E_UNKNOWN);

				goto cleanup;
			}

			hr = m_pPropObject->SetProps(
				1,				// # of properties
				&sPropValue,	// property value pointer
				&lpsProblems);	// property problem array pointer

			if ( SUCCEEDED(hr) && (lpsProblems == NULL) )
			{
				// We are done!
				goto cleanup;
			}

			// Check for errors other than not enough memory
			if ( FAILED(hr) && (hr != MAPI_E_NOT_ENOUGH_MEMORY) )
			{
				// fatal error
				// Return MAPI error code

				goto cleanup;
			}

			// Check property problem array
			if ( lpsProblems != NULL )
			{
				ASSERT_READ_PTR(lpsProblems, sizeof(SPropProblemArray), 
					"Bad lpsProblems");

				for ( iProp = 0; iProp < lpsProblems->cProblem; iProp++ )
				{
					if ( lpsProblems->aProblem[iProp].scode != 
					     MAPI_E_NOT_ENOUGH_MEMORY )
					{
						// fatal error
						// Return MAPI error code
						hr = HR_LOG(lpsProblems->aProblem[iProp].scode);

						goto cleanup;
					}
				}	// end for each problem			 	
			}

			// Otherwise, there is too much
			// data to use SetProps.
			// Open a stream on the property.
			hr = HrOpenUnderlyingStream();

			if ( FAILED(hr) )
			{
				// Return possible MAPI error code due to property access problem.

				goto cleanup;
			}
		}	// end if no underlying stream

		// If we get to here, we 
		// have an underlying stream.
		ASSERT_IUNKNOWN_PTR(m_pStream, "Bad m_pStream");

		// Flush buffered data to the underlying stream.
		// making sure that we do NOT reset the write buffer.
		hr = HrFlushWriteBuffer(FALSE);

		if ( FAILED(hr) )
		{
			// Return possible MAPI error code due to property access failure

			goto cleanup;
		}   	
	}	// end if unflushed data in the buffer

	// If there is an underlying stream, commit the changes to it now.
	if ( m_pStream != NULL )
	{
		ASSERT_IUNKNOWN_PTR(m_pStream, "Bad m_pStream");

		hr = m_pStream->Commit(dwFlags);

		if ( FAILED(hr) )
		{
			goto cleanup;
		}

	}	// end if underlying stream

	// We are done.

cleanup:

	// Free MAPI buffers
	MAPIFREEBUFFER(lpsProblems);

    RETURN(hr);

}

//$--CEDKVirtualStreamOnProperty::Stat---------------------------------------------------
//
// DESCRIPTION: Return "stream" statistics
//
// INPUT:       
//              dwFlags --  flags
//
// OUTPUT:      pStatStg    --  statistics buffer pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise.
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::Stat(
        OUT STATSTG * pStatStg,     // stream statistic pointer
        IN DWORD dwFlags)           // flags
{   
    HRESULT 		hr  	=   NOERROR;
	ULARGE_INTEGER	cbSize	=	{0};	// virtual stream size

    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::Stat()\n");

    // Check parameters
    hr = CHK_CEDKVirtualStreamOnProperty_Stat(pStatStg, dwFlags);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Initialize output buffer
    ZeroMemory(
        pStatStg,
        sizeof(STATSTG));

    // Get the current size of the stream
	hr = HrComputeCurrentSize(
		&cbSize);	// large integer structure pointer

	if ( FAILED(hr) )
	{
		goto cleanup;
	}

    // Note:  last modification and access time are not supported.

    // copy of the default stream statistics to the output buffer
    CopyMemory(
        pStatStg,           // destination buffer
        &m_StatStg,         // source buffer
        sizeof(m_StatStg)); // # bytes to copy

	// Set the current size of the virtual stream
	pStatStg->cbSize.LowPart = cbSize.LowPart;
	pStatStg->cbSize.HighPart = cbSize.HighPart;

    // we are done

cleanup:

    RETURN(hr);
}

// Methods not currently supported for our stream wrapper class:
//
// Seek, Clone, Revert, SetSize, UnlockRegion, LockRegion.
//
// These methods all return STG_E_INVALIDFUNCTION.

//$--CEDKVirtualStreamOnProperty::Seek---------------------------------------------------
//
// DESCRIPTION: Go to the specified position in the "stream".
//
// INPUT:       cbOffset    --  offset
//              dwOrigin    --  origin
//                  
// OUTPUT:      pcbPos  --  new position pointer -- may be NULL
//
// RETURNS:     HRESULT --  STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::Seek(
        IN LARGE_INTEGER cbOffset,      // byte offset
        IN DWORD dwOrigin,              // origin
        OUT ULARGE_INTEGER * pcbPos)    // new position
{
    HRESULT         hr      =   NOERROR;

	DEBUGPUBLIC("CEDKVirtualStreamOnProperty::Seek()\n");

	// check input parameters
	hr = CHK_CEDKVirtualStreamOnProperty_Seek(cbOffset, dwOrigin, pcbPos);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// not implemented.
    RETURN(STG_E_INVALIDFUNCTION);

}

//$--CEDKVirtualStreamOnProperty::Clone---------------------------------------------------
//
// DESCRIPTION: Duplicate "stream"
//
// INPUT:       ppStrm  --  duplicate stream pointer
//
// OUTPUT:      None
//
// RETURNS:     HRESULT --  STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::Clone(
        OUT LPSTREAM * ppStrm)      // pointer to new stream
{
    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::Clone()\n");

    RETURN(STG_E_INVALIDFUNCTION);
}

//$--CEDKVirtualStreamOnProperty::Revert---------------------------------------------------
//
// DESCRIPTION: Undo changes to stream
//
// INPUT:       None
//
// OUTPUT:      None
//
// RETURNS:     HRESULT --  STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::Revert()
{
    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::Revert()\n");

    RETURN(STG_E_INVALIDFUNCTION);
}

//$--CEDKVirtualStreamOnProperty::SetSize---------------------------------------------------
//
// DESCRIPTION: Grow or shrink "stream"
//
// INPUT:       nSize   --  new size
//
// OUTPUT:      None
//
// RETURNS:     HRESULT --  STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::SetSize(
        IN ULARGE_INTEGER nSize)    // new size
{
    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::SetSize()\n");

    RETURN(STG_E_INVALIDFUNCTION);
}

//$--CEDKVirtualStreamOnProperty::UnlockRegion---------------------------------------------------
//
// DESCRIPTION: Unlock section of "stream"
//
// INPUT:       cbOffset    --  offset
//              cbLength    --  length
//              dwFlags     --  flags
//
// OUTPUT:      None
//
// RETURNS:     HRESULT --  STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::UnlockRegion(
        IN ULARGE_INTEGER cbOffset, // offset
        IN ULARGE_INTEGER cbLength, // length
        IN DWORD dwFlags)           // flags
{
    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::UnlockRegion()\n");

    RETURN(STG_E_INVALIDFUNCTION);
}

//$--CEDKVirtualStreamOnProperty::LockRegion---------------------------------------------------
//
// DESCRIPTION: lock section of "stream"
//
// INPUT:       cbOffset    --  offset
//              cbLength    --  length
//              dwFlags     --  flags
//
// OUTPUT:      None
//
// RETURNS:     HRESULT --  STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP CEDKVirtualStreamOnProperty::LockRegion(
        IN ULARGE_INTEGER cbOffset, // offset
        IN ULARGE_INTEGER cbLength, // length
        IN DWORD dwFlags)           // flags
{
    DEBUGPUBLIC("CEDKVirtualStreamOnProperty::LockRegion()\n");

    RETURN(STG_E_INVALIDFUNCTION);
}
