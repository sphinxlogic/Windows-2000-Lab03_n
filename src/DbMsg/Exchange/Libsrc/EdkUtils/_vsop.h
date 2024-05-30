//--_vsop.h--------------------------------------------------------------------
//
// CEDKVirtualStreamOnProperty class header file.
//
// Copyright Microsoft Corp., 1986-1996.  All rights reserved.
//
//-----------------------------------------------------------------------------

#ifndef __VSOP_H
#define __VSOP_H

// maximum number of stream characters to buffer
const ULONG	cbMaxBuffered	=	8192;	// 8K data bytes

//--$CEDKVirtualStreamOnProperty---------------------------------------------------------
//
// Class which buffers stream access to a binary or string property.
//
//-----------------------------------------------------------------------------

class CEDKVirtualStreamOnProperty : public IUnknown
{
public:

	// The HrOpenVirtualStreamOnProperty() function is CEDKVirtualStreamOnProperty
	// friend.
	friend HRESULT _HrOpenVirtualStreamOnProperty(
    	IN LPMAPIPROP pPropObject,	// MAPI property object pointer
    	IN ULONG ulPropTag,     	// property tag to open virtual stream on
		IN ULONG ulFlags,			// MAPI property flags
    	OUT PVIRTUALSTREAMONPROPERTY * ppVirtualStreamOnProperty);  // pointer buffered stream

    // methods

    // Note:  Order IS important.  The CEDKVirtualStreamOnProperty interface
    // must have the same vtable order as the IStream interface.

    // IUnknown methods
	STDMETHOD(QueryInterface)(
		IN REFIID riid,         // interface identifier reference
		OUT LPVOID * ppvObj);   // pointer to object pointer

	STDMETHOD_(ULONG, AddRef)();

	STDMETHOD_(ULONG, Release)();

    // IStream Methods.
    // 
    // Note: Some methods are not currrently suppoerted.
    // These methods all return STG_E_INVALIDFUNCTION:
    // Seek, Clone, Revert, SetSize, UnlockRegion & LockRegion.
    //
    STDMETHOD(Read)(
        IN LPVOID pv,       // output buffer pointer
        IN ULONG cb,        // maximum # of bytes to read
        OUT ULONG * pcb);   // # of bytes read

    STDMETHOD(Write)(
        IN VOID const * pv, // data to write
        IN ULONG cb,        // # bytes to write
        OUT ULONG *pcb);    // # bytes written

    STDMETHOD(Seek)(
        IN LARGE_INTEGER cbOffset,      // byte offset
        IN DWORD dwOrigin,              // origin
        OUT ULARGE_INTEGER * pcbPos);   // new position

    STDMETHOD(SetSize)(
        IN ULARGE_INTEGER nSize);    // new size

    STDMETHOD(CopyTo)(
        IN LPSTREAM pStrm,              // destination stream pointer
        IN ULARGE_INTEGER cb,           // # bytes to copy
        OUT ULARGE_INTEGER * pcbRead,   // # bytes read
        OUT ULARGE_INTEGER * pcbWritten);// # bytes written

    STDMETHOD(Commit)( 
        IN DWORD dwFlags);   // flags

    STDMETHOD(Revert)();

    STDMETHOD(LockRegion)(
        IN ULARGE_INTEGER cbOffset, // offset
        IN ULARGE_INTEGER cbLength, // length
        IN DWORD dwFlags);          // flags

    STDMETHOD(UnlockRegion)(
        IN ULARGE_INTEGER cbOffset, // offset
        IN ULARGE_INTEGER cbLength, // length
        IN DWORD dwFlags);          // flags

    STDMETHOD(Stat)(
        OUT STATSTG * pStatStg,     // stream statistic pointer
        IN DWORD dwFlags);          // flags

    STDMETHOD(Clone)(
        OUT LPSTREAM * ppStrm);      // pointer to new stream

protected:

    // constructor
    CEDKVirtualStreamOnProperty();

    // destructor
    ~CEDKVirtualStreamOnProperty();

    // Initialize virtual stream on property data
    HRESULT HrInitialize(
    	IN LPMAPIPROP pPropObject,	// MAPI property object pointer
    	IN ULONG ulPropTag,     	// property tag to open virtual stream on
		IN ULONG ulFlags);			// MAPI property flags

private:

	// Utility functions

	// Sets mode in the storage statistics structure
	inline VOID SetMode(
		IN ULONG ulMode)	// stream mode
	{
		m_StatStg.grfMode = ulMode;
	}

	// returns TRUE if property opened for writing
	inline BOOL fIsWriteProperty()	
	{
		return ( ((m_ulFlags & MAPI_MODIFY) == MAPI_MODIFY) );
	}

	// returns TRUE if property to be created
	inline BOOL fIsNewProperty()	
	{
		return ( ((m_ulFlags & MAPI_CREATE) == MAPI_CREATE) );
	}

	// returns TRUE if property not opened for writing	    	
	inline BOOL fIsReadProperty()
	{
		return ( ((m_ulFlags & MAPI_MODIFY) == 0) && 
		         ((m_ulFlags & MAPI_CREATE) == 0) );
	}

	// calculates current size of stream.
	HRESULT HrComputeCurrentSize(
		IN ULARGE_INTEGER * pcbSize);

	// Initializes newly created data buffer to a particular size
	inline VOID InitBufferSize(
		IN ULONG cbSize)		// new buffer size
	{
		ASSERT_READ_PTR(m_rgbBuffer, cbSize, "Bad m_rgbBuffer");

		m_cbBuffer = cbSize;		// new buffer size
		m_pbBuffer = m_rgbBuffer;	// current data pointer
		m_fDataInitialized = TRUE;	// have read data

		// If buffer is a write buffer,
		// then zero fill write buffer, including
		// the extra space left for null-terminating
		// exactly 8K long strings. (Read
		// buffers will already be filled with data read.)
		if ( fIsWriteProperty() == TRUE )
		{
			ASSERTERROR(cbSize == cbMaxBuffered, "Bad cbSize");

			ZeroMemory(
				m_rgbBuffer,
				cbSize + sizeof(CHAR));
		}
	}

	// Retrieves number of unread bytes in local data buffer
	inline ULONG GetBytesUnread()
	{
		return (m_cbBuffer - (m_pbBuffer - m_rgbBuffer));
	}

	// Retrieves number of unwritten bytes in local data buffer
	inline ULONG GetBytesUnwritten()
	{
		return (m_cbBuffer - (m_pbBuffer - m_rgbBuffer));
	}

	inline ULONG GetBytesWritten()
	// Retrieves number of bytes written to local data buffer
	{
		return (m_pbBuffer - m_rgbBuffer);
	}

	// Increments number of bytes read in local data buffer
	inline VOID IncrementBytesRead(
		IN ULONG cbRead)		// number of bytes read
	{
		m_pbBuffer += cbRead;
	}

	// Increments number of bytes written to local data buffer
	inline VOID IncrementBytesWritten(
		IN ULONG cbWritten)		// number of bytes written
	{
		m_pbBuffer += cbWritten;
	}

	// Increments size of underlying stream
	inline VOID IncrementStreamSize(
		IN LARGE_INTEGER cbAdd)		// number of bytes to add to stream size
	{
		DWORDLONG	cbCurrent	=	0;	// current size
		DWORDLONG	cbIncrement	=	0;	// amount ot add

		// Determine current stream size
		cbCurrent = MAKEDWORDLONG(m_StatStg.cbSize.LowPart,
								  m_StatStg.cbSize.HighPart);

		// Determine amount to increase stream size by.
		cbIncrement = MAKEDWORDLONG(cbAdd.LowPart,cbAdd.HighPart);

		// Increment current stream size
		cbCurrent += cbIncrement;

		// Set size in storage statistics structure
		m_StatStg.cbSize.LowPart = LOWDWORD(cbCurrent);
		m_StatStg.cbSize.HighPart = HIDWORD(cbCurrent);;

	}

	// Retrieves value of data initialized flag
	inline BOOL fDataInitialized()
	{
		return m_fDataInitialized;
	}

	// Opens/Creates an underlying property stream for reading or writing.
	HRESULT HrOpenUnderlyingStream();

	// Flushes the data in the write buffer to the underlying stream.
	HRESULT HrFlushWriteBuffer(
		IN BOOL fCleanWriteBuffer);	// TRUE if should zero out write buffer also

	// data members

	LPMAPIPROP	m_pPropObject;	// MAPI property object pointer
	ULONG		m_ulFlags;		// MAPI property flags
	ULONG		m_ulPropTag;	// MAPI property tag (must be string or binary)

	// underlying stream structures (if there is an underlying stream)
	LPSTREAM	m_pStream;		// unbuffered stream pointer (if any)
    STATSTG 	m_StatStg;      // stream statistics

	// buffered read or write data (exclusive OR)
	BYTE *		m_rgbBuffer;
	BYTE *		m_pbBuffer;		// pointer into the data buffer
	ULONG		m_cbBuffer;		// current size of data buffer
	BOOL		m_fDataInitialized;	// TRUE if data buffer has been initialized

    ULONG   	m_refs;         // reference count

};

#endif
