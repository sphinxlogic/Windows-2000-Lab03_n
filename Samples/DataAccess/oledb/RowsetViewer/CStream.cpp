//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CSTREAM.CPP
//
//-----------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
// Includes
//
//////////////////////////////////////////////////////////////////////////////
#include "Headers.h"


///////////////////////////////////////////////////////////////////////////////
// Class CStream
// 
///////////////////////////////////////////////////////////////////////////////
CStream::CStream(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild) 
	: CAsynchBase(eCStream, pCMainWindow, pCMDIChild)
{
	//Storage Interfaces	
	m_pISequentialStream	= NULL;
	m_pIStream				= NULL;
	m_pIStorage				= NULL;
	m_pILockBytes			= NULL;
}


///////////////////////////////////////////////////////////////////////////////
// ~CStream
// 
///////////////////////////////////////////////////////////////////////////////
CStream::~CStream()
{
	ReleaseObject(0);
}


/////////////////////////////////////////////////////////////////
// IUnknown** CStream::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CStream::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(ISequentialStream);
	HANDLE_GETINTERFACE(IStream);
	HANDLE_GETINTERFACE(IStorage);
	HANDLE_GETINTERFACE(ILockBytes);

	//Otherwise delegate
	return CAsynchBase::GetInterfaceAddress(riid);
}


/////////////////////////////////////////////////////////////////
// CStream::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CStream::AutoRelease()
{
	//Stream
	RELEASE_INTERFACE(ISequentialStream);
	RELEASE_INTERFACE(IStream);
	RELEASE_INTERFACE(IStorage);
	RELEASE_INTERFACE(ILockBytes);

	//Delegate
	return CAsynchBase::AutoRelease();
}


////////////////////////////////////////////////////////////////
// CStream::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CStream::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First so we have base interfaces
	CAsynchBase::AutoQI(dwCreateOpts);

	//[MANDATORY]
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(ISequentialStream);
	}

	//AutoQI
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
		//[OPTIONAL]
		OBTAIN_INTERFACE(IStream);
		OBTAIN_INTERFACE(IStorage);
		OBTAIN_INTERFACE(ILockBytes);
	}

	return S_OK;
}



////////////////////////////////////////////////////////////////
// CStream::OnDefOperation
//
/////////////////////////////////////////////////////////////////
void CStream::OnDefOperation() 
{ 
//TODO
//	CEditValueDlg editValueDlg(IDD_VIEWDATA, L"Stream Data");
//	if(editValueDlg.DoModal(GetFocus()) == IDOK)
//	{
//	}
}


////////////////////////////////////////////////////////////////
// CStream::ReadObject
//
/////////////////////////////////////////////////////////////////
HRESULT CStream::ReadObject(REFIID riid, DBTYPE wBackendType, WCHAR* pwszBuffer, ULONG ulMaxSize)
{
	ASSERT(pwszBuffer && ulMaxSize);
	HRESULT hr = S_OK;
	
	WCHAR pBuffer[MAX_COL_SIZE] = {0};
	ULONG cBytes = min(sizeof(pBuffer), ulMaxSize*sizeof(WCHAR));
	ULONG cbActRead = 0;
	pwszBuffer[0] = wEOL;
	DWORD	dwConvFlags = GetOptions()->m_dwConvFlags; 

	BOOL bUseDefault = FALSE;
	if(riid != IID_ISequentialStream && riid != IID_ILockBytes && riid != IID_IStream)
		bUseDefault = TRUE;
	
	//IID_ISequentialStream
	if((riid == IID_ISequentialStream && m_pISequentialStream) || (bUseDefault && m_pISequentialStream))
	{
		//Read the Data into our buffer
		//ISequentialStream::Read
		XTEST(hr = m_pISequentialStream->Read(pBuffer, cBytes, &cbActRead));
		TESTC(TRACE_METHOD(hr, L"ISequentialStream::Read(0x%p, %d, &%d)", pBuffer, cBytes, cbActRead));
	}
	//IID_ILockBytes
	else if((riid == IID_ILockBytes && m_pILockBytes) || (bUseDefault && m_pILockBytes))
	{
		//Read the Data into our buffer
		ULARGE_INTEGER ulOffset = {0};
		
		//ILockBytes::ReadAt
		XTEST(hr = m_pILockBytes->ReadAt(ulOffset, pBuffer, cBytes, &cbActRead));
		TESTC(TRACE_METHOD(hr, L"ILockBytes::ReadAt(%d, 0x%p, %d, &%d)", ulOffset, pBuffer, cBytes, cbActRead));
	}
	//IID_IStream
	else if((riid == IID_IStream && m_pIStream) || (bUseDefault && m_pIStream))
	{
		//Read the Data into our buffer
		//IStream::Read
		XTEST(hr = m_pIStream->Read(pBuffer, cBytes, &cbActRead));
		TESTC(TRACE_METHOD(hr, L"IStream::Read(0x%p, %d, &%d)", pBuffer, cBytes, &cbActRead));
	}
//	else if(m_pIStorage)
//	{
		//TODO
//	}
	else
	{
		TESTC(hr = E_FAIL);
	}

	//What type of data are we reading
	switch(wBackendType)
	{
		case DBTYPE_WSTR:
		case DBTYPE_STR:
			break;

		default:
			wBackendType = DBTYPE_BYTES;
			break;
	};

	//Now that we have read the data, coerce it into a string for display purposes...
	XTESTC_(hr = DataConvert
		(
			DBSTATUS_S_OK,
			cbActRead,
			sizeof(pBuffer),	
			wBackendType,
			pBuffer,
			0,
			0,
			
			DBTYPE_WSTR,
			NULL,
			NULL,
			pwszBuffer,
			ulMaxSize*sizeof(WCHAR),
			dwConvFlags
		),S_OK);

CLEANUP:
	return hr;
}


////////////////////////////////////////////////////////////////
// CStream::Stat
//
/////////////////////////////////////////////////////////////////
HRESULT CStream::Stat()
{
	HRESULT hr = S_OK;
	WCHAR* pwszProgID = NULL;

	if(m_pIStream)
	{	
		STATSTG statstg;
		DWORD	grfStatFlag = STATFLAG_DEFAULT;
		memset(&statstg, 0, sizeof(STATSTG));

		//IStream::Stat
		XTEST(hr = m_pIStream->Stat(&statstg, grfStatFlag));

		pwszProgID = GetProgID(statstg.clsid);
		TESTC(TRACE_METHOD(hr, L"IStream::Stat(&{\"%s\", %d, %d, 0x%08x, 0x%08x, 0x%08x, %d, %d, \"%s\", 0x%08x, %d}, %d)", statstg.pwcsName, statstg.type, (ULONG)statstg.cbSize.QuadPart, &statstg.mtime, &statstg.ctime, &statstg.atime, statstg.grfMode, statstg.grfLocksSupported, pwszProgID, statstg.grfStateBits, statstg.reserved, grfStatFlag));
	}

CLEANUP:
	SAFE_FREE(pwszProgID);
	return hr;
}



///////////////////////////////////////////////////////////////////////////////
// Class CStorageBuffer
// 
// My implementation of storage interfaces
///////////////////////////////////////////////////////////////////////////////
CStorageBuffer::CStorageBuffer(CMainWindow* pCMainWindow) 
{
	ASSERT(pCMainWindow);
	m_pCMainWindow = pCMainWindow;
	
	m_iPos		= 0;
	m_cRef		= 1;
	
	m_pBuffer   = NULL;
	m_cMaxSize  = 0;
}


CStorageBuffer::~CStorageBuffer()
{
	SAFE_FREE(m_pBuffer);
}

ULONG	CStorageBuffer::AddRef()
{
	m_cRef++;
	return m_cRef;
}

ULONG	CStorageBuffer::Release()
{
	ASSERT(m_cRef);
	m_cRef--;
	
	if(m_cRef)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT CStorageBuffer::QueryInterface(REFIID riid, void** ppv)
{
	if(!ppv)
		return E_INVALIDARG;
	*ppv = NULL;
	HRESULT hr = E_NOINTERFACE;

	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)(ISequentialStream*)this;
	else if (riid == IID_ISequentialStream)
		*ppv = (ISequentialStream*)this;
	else if (riid == IID_IStream)
		*ppv = (IStream*)this;
	else if (riid == IID_ILockBytes)
		*ppv = (ILockBytes*)this;
//	else if (riid == IID_IStorage)
//		*ppv = (IStorage*)this;
	
	if(*ppv)
	{
		//Avoid internal notiifcations
		m_cRef++;
		hr = S_OK;
	}

	return hr;
}


HRESULT CStorageBuffer::ReadBuffer(ULONG ulOffset, void *pv, ULONG cb, ULONG* pcbRead)
{
	//Parameter checking
	if(pcbRead)
		*pcbRead = 0;

	if(!pv)
		return STG_E_INVALIDPOINTER;

	if(cb == 0)
		return S_OK;

	//Actual code
	ULONG cBytesLeft = m_cMaxSize > ulOffset ? m_cMaxSize - ulOffset : 0;
	ULONG cBytesRead = cb > cBytesLeft ? cBytesLeft : cb;

	//if no more bytes to retrive return 
	if(cBytesLeft == 0)
		return S_FALSE; 

	//Copy to users buffer the number of bytes requested or remaining
	memcpy(pv, (void*)((BYTE*)m_pBuffer + ulOffset), cBytesRead);

	if(pcbRead)
		*pcbRead = cBytesRead;

	if(cb != cBytesRead)
		return S_FALSE; 

	return S_OK;
}


HRESULT CStorageBuffer::WriteBuffer(ULONG ulOffset, const void *pv, ULONG cb, ULONG* pcbWritten)
{
	//Parameter checking
	if(!pv)
		return STG_E_INVALIDPOINTER;

	if(pcbWritten)
		*pcbWritten = 0;

	if(cb == 0)
		return S_OK;

	//May need to Enlarge the current buffer
	if(ulOffset + cb >= m_cMaxSize)
	{
		//Need to append to the end of the stream
		ULARGE_INTEGER largeSize = { ulOffset + cb };
		if(FAILED(SetSize(largeSize)))
			return E_OUTOFMEMORY;
	}
	
	//Copy to the buffer
	memcpy((void*)((BYTE*)m_pBuffer + ulOffset), pv, cb);

	if(pcbWritten)
		*pcbWritten = cb;

	return S_OK;
}

	
HRESULT CStorageBuffer::Read(void *pv, ULONG cb, ULONG* pcbRead)
{
	ULONG cbRead = 0;
	HRESULT hr = S_OK;

	//Delegate, reading from the current position
	XTEST(hr = ReadBuffer(m_iPos, pv, cb, &cbRead));
	TRACE_METHOD(hr, L"\tISequentialStream::Read(0x%p, %d, &%d)", pv, cb, cbRead);

	if(SUCCEEDED(hr))
		m_iPos += cbRead;

	if(pcbRead)
		*pcbRead = cbRead;

	return hr;
}
      

HRESULT CStorageBuffer::Write(const void *pv, ULONG cb, ULONG* pcbWritten)
{
	ULONG cbWritten = 0;
	HRESULT hr = S_OK;

	//Delegate, writting to the current position
	XTEST(hr = WriteBuffer(m_iPos, pv, cb, &cbWritten));
	TRACE_METHOD(hr, L"\tISequentialStream::Write(0x%p, %d, &%d)", pv, cb, cbWritten);

	if(SUCCEEDED(hr))
		m_iPos += cbWritten;

	if(pcbWritten)
		*pcbWritten = cbWritten;

	return hr;
}
	

HRESULT CStorageBuffer::Seek(LONG lOffset)
{
	//Make sure the new offset is within the range, for some reason ::Seek
	//allows going off the end of the stream...
	LONG iNewPos = m_iPos + lOffset;

	if(iNewPos<0 || (ULONG)iNewPos>m_cMaxSize)
		return STG_E_INVALIDFUNCTION; //No good return code for this situaiton?

	//Reset the current buffer position
	m_iPos = iNewPos;
	return S_OK;
}

//IStream interfaces
HRESULT CStorageBuffer::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER * plibNewPosition)
{
	HRESULT hr = S_OK;

	DWORDLONG lOffset = 0;
	
	//Determine with respect to what the origin is...
	switch(dwOrigin)
	{
		case STREAM_SEEK_SET:
			lOffset = dlibMove.QuadPart;
			break;

		case STREAM_SEEK_CUR:
			lOffset = m_iPos + dlibMove.QuadPart;
			break;

		case STREAM_SEEK_END:
			lOffset = m_cMaxSize + dlibMove.QuadPart;
			break;

		default:
			//The value of the dwOrigin parameter is not valid
			hr = STG_E_INVALIDFUNCTION;
			goto CLEANUP;
			break;
	};

	//Delegate to the simplier version
	hr = Seek((LONG)lOffset);

CLEANUP:						  
	if(plibNewPosition)
	   plibNewPosition->QuadPart = m_iPos;
	TRACE_METHOD(hr, L"\tIStream::Seek(%d, %d, &%d)", dlibMove.QuadPart, dwOrigin, m_iPos);
	return hr;
}


HRESULT CStorageBuffer::SetSize(	ULARGE_INTEGER libNewSize)		//Specifies the new size of the stream object
{
	HRESULT hr = STG_E_MEDIUMFULL;
	void* pBuffer = m_pBuffer;

	//The value of the libNewSize parameter is not valid. 
	//Since streams cannot be greater than 2^32 bytes in the COM-provided 
	//implementation, the high DWORD of libNewSize must be 0. 
	//If it is nonzero, this parameter is not valid. 
	if(libNewSize.QuadPart > ULONG_MAX)
	{
		hr = STG_E_INVALIDFUNCTION;
		goto CLEANUP;
	}
	
	//Use a copy variable, incase allocations fail...
	SAFE_REALLOC(pBuffer, BYTE, libNewSize.QuadPart);

	m_pBuffer = pBuffer;
	m_cMaxSize = (ULONG)libNewSize.QuadPart;
	hr = S_OK;

CLEANUP:
	TRACE_METHOD(hr, L"\tIStream::SetSize(%d)", (ULONG)libNewSize.QuadPart);
	return hr;
}

HRESULT CStorageBuffer::CopyTo(	IStream * pIStream,				//Points to the destination stream
							ULARGE_INTEGER cb,				//Specifies the number of bytes to copy
							ULARGE_INTEGER * pcbRead,		//Pointer to the actual number of bytes read from the source
							ULARGE_INTEGER * pcbWritten)	//Pointer to the actual number of bytes written to the destination
{
	HRESULT hr = S_OK;

	//This is equivlent of doing Read from our stream then Write into the destination.
	//It also moves the seek position.  Bug this would require allocating a temp buffer...
	//Just access our stream directly...
	
	//Parameter checking
	if(pcbRead)
		pcbRead->QuadPart = 0;
	if(pcbWritten)
		pcbWritten->QuadPart = 0;

	//Actual code
	ULONG cBytesLeft = m_cMaxSize - m_iPos;
	ULONG cBytesRead = (ULONG)cb.QuadPart > cBytesLeft ? cBytesLeft : (ULONG)cb.QuadPart;
	ULONG cBytesWritten = 0;

	if(!pIStream)
	{
		hr = STG_E_INVALIDPOINTER;
		goto CLEANUP;
	}

	if(cb.QuadPart == 0)
	{
		hr = S_OK;
		goto CLEANUP;
	}

	//if no more bytes to retrive return 
	if(cBytesLeft == 0)
	{
		hr = S_FALSE; 
		goto CLEANUP;
	}

	//Copy to users buffer the number of bytes requested or remaining
	pIStream->Write((BYTE*)m_pBuffer + m_iPos, cBytesRead, &cBytesWritten);
	m_iPos += cBytesRead;

	if(pcbRead)
		pcbRead->QuadPart = cBytesRead;
	if(pcbWritten)
		pcbWritten->QuadPart = cBytesWritten;

	if(cb.QuadPart != cBytesRead)
		hr = S_FALSE; 

CLEANUP:
	TRACE_METHOD(hr, L"\tIStream::CopyTo(0x%p, %d, &%d, &%d)", pIStream, cb, cBytesRead, cBytesWritten);
	return hr;
}

HRESULT CStorageBuffer::Commit(	DWORD grfCommitFlags)			//Specifies how changes are committed
{
	HRESULT hr = S_OK;
	TRACE_METHOD(hr, L"\tIStream::Commit()");
	return hr;
}

HRESULT CStorageBuffer::Revert(	)
{
	HRESULT hr = S_OK;
	TRACE_METHOD(hr, L"\tIStream::Revert()");
	return hr;
}

HRESULT CStorageBuffer::LockRegion(ULARGE_INTEGER libOffset,		//Specifies the byte offset for the beginning of the range
							ULARGE_INTEGER cb,				//Specifies the length of the range in bytes
							DWORD dwLockType)				//Specifies the restriction on accessing the specified range
{
	//Locking is optional
	HRESULT hr = STG_E_INVALIDFUNCTION;
	TRACE_METHOD(hr, L"\tIStream::LockRegion()");
	return hr;
}

HRESULT CStorageBuffer::UnlockRegion(  ULARGE_INTEGER libOffset,	//Specifies the byte offset for the beginning of the range
								ULARGE_INTEGER cb,			//Specifies the length of the range in bytes
								DWORD dwLockType)			//Specifies the access restriction previously placed on the range);
{
	//Locking is optional
	HRESULT hr = STG_E_INVALIDFUNCTION;
	TRACE_METHOD(hr, L"\tIStream::UnlockRegion()");
	return hr;
}

HRESULT CStorageBuffer::Stat(		STATSTG * pstatstg,				//Location for STATSTG structure
							DWORD grfStatFlag)				//Values taken from the STATFLAG enumeration
{
	HRESULT hr = S_OK;
	ULARGE_INTEGER largeInteger = { m_cMaxSize };

	if(!pstatstg)
	{
		hr = STG_E_INVALIDPOINTER;
		goto CLEANUP;
	}
	
	//Initialize the struct
	memset(pstatstg, 0, sizeof(STATSTG));

	//Set the string...
	switch(grfStatFlag)
	{
		case STATFLAG_NONAME:
			pstatstg->pwcsName = NULL;
			break;

		case STATFLAG_DEFAULT:
			pstatstg->pwcsName = wcsDuplicate(L"OLE DB Test Storage Object...");
			break;
		
		default:
			hr = STG_E_INVALIDFLAG;
			goto CLEANUP;
	};

	//type
	pstatstg->type = STGTY_STREAM;
	pstatstg->grfMode = STGM_READ;
	pstatstg->grfLocksSupported = 0; 
	pstatstg->cbSize = largeInteger;
	
CLEANUP:
	TRACE_METHOD(hr, L"\tIStream::Stat(0x%p, 0x%08x)", pstatstg, grfStatFlag);
	return hr;
}

HRESULT CStorageBuffer::Clone(IStream** ppIStream)				//Points to location for pointer to the new stream object
{
	HRESULT hr = E_NOTIMPL;
	TRACE_METHOD(hr, L"\tILockBytes::Clone()");
	return hr;
}

	
HRESULT CStorageBuffer::ReadAt( 
							ULARGE_INTEGER ulOffset,
            /* [out] */		void* pv,
            /* [in] */		ULONG cb,
            /* [out] */		ULONG* pcbRead)
{
	HRESULT hr = S_OK;
	ULONG cbRead = 0;

	//Delegate, reading from the current position
	XTEST(hr = ReadBuffer((ULONG)ulOffset.QuadPart, pv, cb, &cbRead));
	TRACE_METHOD(hr, L"\tILockBytes::ReadAt(%d, 0x%p, %d, &%d)", (ULONG)ulOffset.QuadPart, pv, cb, cbRead);

	if(pcbRead)
		*pcbRead = cbRead;
	return hr;
}
        
HRESULT CStorageBuffer::WriteAt( 
							ULARGE_INTEGER ulOffset,
            /* [in] */		const void* pv,
            /* [in] */		ULONG cb,
            /* [out] */		ULONG* pcbWritten)
{
	HRESULT hr = S_OK;
	ULONG cbWritten = 0;

	//Delegate, reading from the current position
	XTEST(hr = WriteBuffer((ULONG)ulOffset.QuadPart, pv, cb, &cbWritten));
	TRACE_METHOD(hr, L"\tILockBytes::WriteAt(%d, 0x%p, %d, &%d)", (ULONG)ulOffset.QuadPart, pv, cb, cbWritten);

	if(pcbWritten)
		*pcbWritten = cbWritten;
	return hr;
}

HRESULT CStorageBuffer::Flush()
{
	HRESULT hr = S_OK;
	TRACE_METHOD(hr, L"\tILockBytes::Flush()");
	return hr;
}


///////////////////////////////////////////////////////////////////////////////
// Class CFileStream
// 
// My implementation of stream interface on top of a file
///////////////////////////////////////////////////////////////////////////////
CFileStream::CFileStream()
{
	m_pFile = NULL;
	m_cRef	= 1;
}

CFileStream::~CFileStream()
{
	CloseFile();
}

HRESULT	CFileStream::OpenFile(WCHAR* pwszFile, WCHAR* pwszMode)
{
	if(IsUnicodeOS())
	{
		m_pFile = _wfopen(pwszFile, pwszMode);
	}
	else
	{
		CHAR szFileName[MAX_NAME_LEN];
		ConvertToMBCS(pwszFile, szFileName, MAX_NAME_LEN);
		CHAR szMode[MAX_NAME_LEN];
		ConvertToMBCS(pwszMode, szMode, MAX_NAME_LEN);

		m_pFile = fopen(szFileName, szMode);
	}

	return m_pFile ? S_OK : STG_E_ACCESSDENIED;
}


HRESULT	CFileStream::CloseFile()
{
	if(m_pFile)
		fclose(m_pFile);

	return S_OK;
}


ULONG	CFileStream::AddRef()
{
	m_cRef++;
	return m_cRef;
}

ULONG	CFileStream::Release()
{
	ASSERT(m_cRef);
	m_cRef--;
	
	if(m_cRef)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT CFileStream::QueryInterface(REFIID riid, void** ppv)
{
	ASSERT(ppv);
	HRESULT hr = E_NOINTERFACE;

	*ppv = NULL;

	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if (riid == IID_ISequentialStream)
		*ppv = (ISequentialStream*)this;
	else if (riid == IID_IStream)
		*ppv = (IStream*)this;
	
	if(*ppv)
	{
		m_cRef++;
		hr = S_OK;
	}

	return hr;
}


STDMETHODIMP CFileStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	ULONG cbRead = 0;

	//Parameter checking
	if(!m_pFile)
		return STG_E_INVALIDHANDLE;
	if(!pv)
		return STG_E_INVALIDPOINTER;
	if(cb == 0)
		return S_OK;

	//Read from the file...
	cbRead = fread(pv, sizeof(BYTE), cb, m_pFile);

	//Results..
	if(pcbRead)
		*pcbRead = cbRead;
	return cbRead==cb ? S_OK : S_FALSE;
}


STDMETHODIMP CFileStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
	ULONG cbWritten = 0;

	//Parameter checking
	if(!m_pFile)
		return STG_E_INVALIDHANDLE;
	if(!pv)
		return STG_E_INVALIDPOINTER;
	if(cb == 0)
		return S_OK;

	//Read from the file...
	cbWritten = fwrite(pv, sizeof(BYTE), cb, m_pFile);

	//Results..
	if(pcbWritten)
		*pcbWritten = cbWritten;
	return cbWritten==cb ? S_OK : S_FALSE;
}

//IStream interfaces
HRESULT CFileStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER * plibNewPosition)
{
	//Parameter checking
	if(!m_pFile)
		return STG_E_INVALIDHANDLE;

	//Seek
	LONG lNewPosition = fseek(m_pFile, dlibMove.LowPart, dwOrigin);
	if (lNewPosition >= 0 && plibNewPosition)
		plibNewPosition->LowPart = lNewPosition;

	return (lNewPosition >= 0) ? S_OK : E_FAIL;		
}


HRESULT CFileStream::SetSize(	ULARGE_INTEGER libNewSize)		//Specifies the new size of the stream object
{
	return E_NOTIMPL;
}

HRESULT CFileStream::CopyTo(	IStream * pIStream,				//Points to the destination stream
							ULARGE_INTEGER cb,				//Specifies the number of bytes to copy
							ULARGE_INTEGER * pcbRead,		//Pointer to the actual number of bytes read from the source
							ULARGE_INTEGER * pcbWritten)	//Pointer to the actual number of bytes written to the destination
{
	return E_NOTIMPL;
}

HRESULT CFileStream::Commit(	DWORD grfCommitFlags)			//Specifies how changes are committed
{
	return E_NOTIMPL;
}

HRESULT CFileStream::Revert(	)
{
	return E_NOTIMPL;
}

HRESULT CFileStream::LockRegion(ULARGE_INTEGER libOffset,		//Specifies the byte offset for the beginning of the range
							ULARGE_INTEGER cb,				//Specifies the length of the range in bytes
							DWORD dwLockType)				//Specifies the restriction on accessing the specified range
{
	return E_NOTIMPL;
}

HRESULT CFileStream::UnlockRegion(  ULARGE_INTEGER libOffset,	//Specifies the byte offset for the beginning of the range
								ULARGE_INTEGER cb,			//Specifies the length of the range in bytes
								DWORD dwLockType)			//Specifies the access restriction previously placed on the range);
{
	return E_NOTIMPL;
}

HRESULT CFileStream::Stat(		STATSTG * pstatstg,				//Location for STATSTG structure
							DWORD grfStatFlag)				//Values taken from the STATFLAG enumeration
{
	return E_NOTIMPL;
}

HRESULT CFileStream::Clone(IStream** ppIStream)				//Points to location for pointer to the new stream object
{
	return E_NOTIMPL;
}

	



	
