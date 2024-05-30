////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// Copyright (c) 1999  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//--------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////




#ifndef _FILESTREAM_HXX
#define _FILESTREAM_HXX

#include <stdio.h>

class FileStream : public IStream
{
public:
	FileStream() 
	{ 
        _ulRefs = 1;
        _hFile = NULL;
        _fRead = true;
	}

	~FileStream() 
	{ 
		::CloseHandle(_hFile);
	}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject)
    {
        if (riid == IID_IUnknown)
        {
            *ppvObject = static_cast<IUnknown*>(this);
        }
        else if (riid == IID_IStream)
        {
            *ppvObject = static_cast<IStream*>(this);
        }
        reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();
        return S_OK;
    }

    ULONG STDMETHODCALLTYPE AddRef( void)
    {
        return InterlockedIncrement(&_ulRefs);
    }

    ULONG STDMETHODCALLTYPE Release( void)
    {
        if (InterlockedDecrement(&_ulRefs) == 0)
        {
            delete this;
            return 0;
        }
        return _ulRefs;
    }

    bool open(WCHAR* name, bool read = true)
    {
        _fRead = read;
        char szName[100];
        ULONG cb;

        cb = ::WideCharToMultiByte(CP_ACP, 0, name, lstrlenW(name), szName, 99, NULL, NULL);
        if (cb == 0)
            return false;

        szName[cb] = 0;
    
        if (read)
        {
		    _hFile = ::CreateFileA( 
                szName,
			    GENERIC_READ,
			    FILE_SHARE_READ,
			    NULL,
			    OPEN_EXISTING,
			    FILE_ATTRIBUTE_NORMAL,
			    NULL);
        }
        else
        {
		    _hFile = ::CreateFileA(
			    szName,
			    GENERIC_WRITE,
			    FILE_SHARE_READ,
			    NULL,
			    CREATE_ALWAYS,
			    FILE_ATTRIBUTE_NORMAL,
			    NULL);
        }
        return (_hFile == INVALID_HANDLE_VALUE) ? false : true;
    }

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Read( 
        /* [out] */ void __RPC_FAR *pv,
        /* [in] */ ULONG cb,
        /* [out] */ ULONG __RPC_FAR *pcbRead)
	{	
        if (! _fRead) return E_FAIL;

        DWORD len;
		BOOL rc = ReadFile(
			_hFile,	// handle of file to read 
			pv,	// address of buffer that receives data  
			cb,	// number of bytes to read 
			&len,	// address of number of bytes read 
			NULL 	// address of structure for data 
		   );
        if (pcbRead)
            *pcbRead = len;
        if (! rc)        // ReadFile returns FALSE if there is an error.
            return E_FAIL;
        
        return len > 0 ? S_OK : S_FALSE; 
	}
    
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Write( 
        /* [size_is][in] */ const void __RPC_FAR *pv,
        /* [in] */ ULONG cb,
        /* [out] */ ULONG __RPC_FAR *pcbWritten)
	{
        if (_fRead) return E_FAIL;

		BOOL rc = WriteFile(
			_hFile,	// handle of file to write 
			pv,	// address of buffer that contains data  
			cb,	// number of bytes to write 
			pcbWritten,	// address of number of bytes written 
			NULL 	// address of structure for overlapped I/O  
		   );

		return (rc) ? S_OK : E_FAIL;
	}

    virtual /* [local] */ HRESULT STDMETHODCALLTYPE Seek( 
        /* [in] */ LARGE_INTEGER dlibMove,
        /* [in] */ DWORD dwOrigin,
        /* [out] */ ULARGE_INTEGER __RPC_FAR *plibNewPosition) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE SetSize( 
        /* [in] */ ULARGE_INTEGER libNewSize) { return E_FAIL; }
    
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE CopyTo( 
        /* [unique][in] */ IStream __RPC_FAR *pstm,
        /* [in] */ ULARGE_INTEGER cb,
        /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbRead,
        /* [out] */ ULARGE_INTEGER __RPC_FAR *pcbWritten) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Commit( 
        /* [in] */ DWORD grfCommitFlags) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Revert( void) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE LockRegion( 
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE UnlockRegion( 
        /* [in] */ ULARGE_INTEGER libOffset,
        /* [in] */ ULARGE_INTEGER cb,
        /* [in] */ DWORD dwLockType) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Stat( 
        /* [out] */ STATSTG __RPC_FAR *pstatstg,
        /* [in] */ DWORD grfStatFlag) { return E_FAIL; }
    
    virtual HRESULT STDMETHODCALLTYPE Clone( 
        /* [out] */ IStream __RPC_FAR *__RPC_FAR *ppstm) { return E_FAIL; }
private:
	HANDLE _hFile;
    bool _fRead;
    LONG _ulRefs;
};

#endif // _FILESTREAM_HXX
