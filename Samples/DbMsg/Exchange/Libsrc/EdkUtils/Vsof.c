//--vsof.c---------------------------------------------------------------------
//
// This file contains methods and code for implementing an OLE 2.0
// storage stream (as defined in the OLE 2.0 specs) on top of OS file.
//
// Copyright 1986-1996.  Microsoft Corporation.  All Rights Reserved.
//
// Notes:
//
// Specifying STGM_DELETEONRELEASE makes the file opened a temporary file (It
// will be deleted when the stream is released).
//
// Specifying STGM_SHARE_EXCLUSIVE makes the file writable by only one application
// at a time.
//
//-----------------------------------------------------------------------------
#include "edk.h"
#include "_vsof.h"
#include "vsof.chk"

//$--ComputeShareFlags---------------------------------------------------------------
//
// DESCRIPTION:	computes the file share flags based on the stream share flags.
//
// INPUT:		ulFlags	--	stream flags
//
// RETURNS:		DWORD	--	file share flags
//
//-----------------------------------------------------------------------------
static __inline DWORD dwComputeShareFlags(
	IN ULONG ulFlags)		// stream flags
{
	// By default, the file created is shareable for reading & writing
	DWORD	fdwShare	=	FILE_SHARE_READ | FILE_SHARE_WRITE;

	// Determine if concurrent access to file is restricted
	if ( ulFlags & STGM_SHARE_EXCLUSIVE )
	{
		fdwShare = 0;	// file not to be shared at all
	}

	else 
	{
		if ( ulFlags & STGM_SHARE_DENY_WRITE )
		{
			fdwShare &= ~FILE_SHARE_WRITE;	// don't allow sharing on writes
		}

		if ( ulFlags & STGM_SHARE_DENY_READ )
		{
			fdwShare &= ~FILE_SHARE_READ;	// don't allow sharing on reads
		}
	}	// end if not exclusive access file

	// We are done
	
	return fdwShare;

}

//$--ScGetVSOFFilename---------------------------------------------------------------
//
// DESCRIPTION:	Get virtual stream on file file name
//
// INPUT:		lpszPath	--	file path
//				lpszPrefix	--	file prefix
//				lpszBuf	--	file name output buffer
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							E_INVALIDARG if bad input,
//							E_FAIL otherwise
//
//-----------------------------------------------------------------------------
HRESULT ScGetVSOFFilename (
	IN LPSTR lpszPath, 		// file path
	IN LPSTR lpszPrefix, 		// file name prefix
	IN LPSTR lpszBuf)			// file name output buffer
{
	HRESULT	hr					=	NOERROR;
	CHAR	rgchPath[MAX_PATH]	= 	{0};

	DEBUGPRIVATE("ScGetVSOFFilename()\n");

	// check input parameters
	hr = CHK_ScGetVSOFFilename(lpszPath, lpszPrefix, lpszBuf);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	if (lpszPrefix == NULL)
	{
		lpszPrefix = VSOF_DEFAULT_PREFIX;
	}

	if (!lpszPath)
	{
		if (!GetTempPath (MAX_PATH, rgchPath))
		{
			//	Init the Path to the current directory (".")
			//
			rgchPath[0] = '.';
			rgchPath[1] = 0;
		}
		lpszPath = rgchPath;
	}

	if (!GetTempFileName32 (lpszPath, lpszPrefix, 0, lpszBuf))
	{
		hr = HR_LOG(E_FAIL);

		goto cleanup;
	}

cleanup:

	RETURN(hr);

}

//$--MakeReal------------------------------------------------------------------
//
// DESCRIPTION:	Create a "real" temporary file.
//
// INPUT:	vhFile	--	virtual file handle
//
// RETURNS:	BOOL
//
// NOTES:	This function is only called when it is necessary to make a in-buffer
// 			temporary file real.
//
//-----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
BOOL MakeReal(				// RETURNS: BOOL
	IN VSOF_HANDLE vhFile)	// virtual file handle
{
	HRESULT		hr			 		=	NOERROR;
	BOOL		fMadeReal			=	FALSE;	// TRUE if file made real
    char		szPath[MAX_PATH]	=	"";
    char *		lpszPath			=	NULL;
    char   		szPrefix[MAX_PATH]	=	"";
    char *		lpszPrefix			=	NULL;
    char *		p					=	NULL;	
    DWORD 		dwSizeWritten		=	0;
	DWORD		fdwShare			=	0;		// share flags for created file

	const DWORD	fdwAttr				=	FILE_ATTRIBUTE_TEMPORARY | 
		FILE_FLAG_DELETE_ON_CLOSE | FILE_FLAG_SEQUENTIAL_SCAN;;

	DEBUGPRIVATE("MakeReal()\n");

    if (lstrlen(vhFile->rgchFile) >= MAX_PATH) 
    {
        SetLastError(ERROR_INVALID_PARAMETER);
		hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lstrcpy(szPath, vhFile->rgchFile);
    
    p = lstrlen(vhFile->rgchFile)+vhFile->rgchFile+1;
    if (lstrlen(p) >= MAX_PATH) 
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }
    lstrcpy(szPrefix, p);
    lpszPath = szPath;
    lpszPrefix = szPrefix;
    
    if (!lstrlen(szPath))
        lpszPath = NULL;
    if (!lstrlen(szPrefix))
        lpszPrefix = NULL;

    if (ScGetVSOFFilename (lpszPath, lpszPrefix, vhFile->rgchFile))
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Determine whether this file will have concurrent access.
	fdwShare = dwComputeShareFlags(vhFile->ulFlags);

	// Create a temporary file for writing (this function is only
	// called for temporary files!)    
    vhFile->hf = CreateFile (vhFile->rgchFile,
                             GENERIC_READ | GENERIC_WRITE,
							 fdwShare,
                             NULL,
                             CREATE_ALWAYS,
    						 fdwAttr,
                             NULL);

	if (vhFile->hf == INVALID_HANDLE_VALUE)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

    if (vhFile->ulFileSize) 
    {
        if (!WriteFile(vhFile->hf, vhFile->lpvVBuff, vhFile->ulFileSize,
                       &dwSizeWritten, NULL))
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
        else if (dwSizeWritten != vhFile->ulFileSize)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
    }
    
    if (SetFilePointer(vhFile->hf, vhFile->ulFilePointer, NULL, FILE_BEGIN) ==
        INVALID_SET_FILE_POINTER)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// The file is now real.
	fMadeReal = TRUE;
	
	// We are done.
		
cleanup:
    
    return fMadeReal;

}

//$--VSOF_SetFilePointer-------------------------------------------------------
//
// DESCRIPTION:	performs seek
//
// INPUT:	vhFile	--	virtual file handle
//			lDistanceToMove	--	distance to move
//			lpDistanceToMoveHigh	-- pointer to 64-bit distance to move
//			dwMoveMethod	--	origin
//
// RETURNS:	DWORD	-- new file position or error code
//
//-----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
DWORD VSOF_SetFilePointer(			// RETURNS: DWORD
	IN VSOF_HANDLE vhFile,			// file handle
    IN LONG lDistanceToMove,		// distance to move
    IN PLONG lpDistanceToMoveHigh,	// pointer to 64 bit distance to move
    IN DWORD dwMoveMethod			// origin
    )
{   
	HRESULT	hr		=	NOERROR;
	DWORD	posNew	=	SET_FILE_POINTER_ERROR;		// error code

	DEBUGPRIVATE("VSOF_SetFilePointer()\n");

	// check input parameters
	hr = CHK_VSOF_SetFilePointer(vhFile, lDistanceToMove, lpDistanceToMoveHigh, 
	                             dwMoveMethod);

	if ( FAILED(hr) )
	{
		SetLastError(ERROR_INVALID_PARAMETER);

		return SET_FILE_POINTER_ERROR;
	}

    if (vhFile->hf != INVALID_HANDLE_VALUE)
	{
        goto NonVirtual;
	}
    
    if (lpDistanceToMoveHigh && *lpDistanceToMoveHigh) 
    {
        if (!MakeReal(vhFile))
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}
        else
		{
            goto NonVirtual;
		}
    }
    
    switch (dwMoveMethod) 
    {
    case FILE_BEGIN:
        if (lDistanceToMove >= (long)vhFile->dwVirtualBufferSize) 
        {
            if (!MakeReal(vhFile))
			{
				hr = HR_LOG(E_FAIL);
				goto cleanup;
			}
            else
			{
                goto NonVirtual;            
			}
        } 
        else if (lDistanceToMove < 0) 
        {
            SetLastError(ERROR_INVALID_PARAMETER);
			hr = HR_LOG(E_FAIL);
			goto cleanup;
        }        
        vhFile->ulFilePointer = lDistanceToMove;
        break;
    case FILE_CURRENT:
        if ((lDistanceToMove+(long)vhFile->ulFilePointer) >= (long)vhFile->dwVirtualBufferSize) 
        {
            if (!MakeReal(vhFile))
			{
				hr = HR_LOG(E_FAIL);
				goto cleanup;
			}
            else
			{
                goto NonVirtual;            
			}
        } 
        else if ((lDistanceToMove+(long)vhFile->ulFilePointer) < 0) 
        {
			hr = HR_LOG(E_FAIL);
            SetLastError(ERROR_INVALID_PARAMETER);
			goto cleanup;
        }        
        vhFile->ulFilePointer = lDistanceToMove+(long)vhFile->ulFilePointer;
        break;
    case FILE_END:
        if ((lDistanceToMove+(long)vhFile->ulFileSize) >= (long)vhFile->dwVirtualBufferSize) 
        {
            if (!MakeReal(vhFile))
			{
				hr = HR_LOG(E_FAIL);
				goto cleanup;
			}
            else
			{
                goto NonVirtual;
			}
        } 
        else if ((lDistanceToMove+(long)vhFile->ulFileSize) < 0) 
        {
            SetLastError(ERROR_INVALID_PARAMETER);
			hr = HR_LOG(E_FAIL);
			goto cleanup;
        }
        vhFile->ulFilePointer = lDistanceToMove + (long)vhFile->ulFileSize;
        break;
    default:
        SetLastError(ERROR_INVALID_PARAMETER);
		hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

	// Return new file position.
	posNew = vhFile->ulFilePointer;

	goto cleanup;
    
NonVirtual:
	// real file
    posNew = SetFilePointer(
    	vhFile->hf,
        lDistanceToMove,
        lpDistanceToMoveHigh,
        dwMoveMethod);

	goto cleanup;

cleanup:

	return posNew;

}

//$--VSOF_SetEndOfFile---------------------------------------------------------
//
// DESCRIPTION:	set end of file
//
// INPUT:	vhFile	--	virtual file handle
//
// RETURNS:	BOOL
//
//-----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
BOOL VSOF_SetEndOfFile(			// RETURNS BOOL
    IN VSOF_HANDLE vhFile		// virtual file handle
    )
{
	BOOL	fSet	=	FALSE;	// TRUE if successful

	DEBUGPRIVATE("VSOF_SetEndOfFile()\n");

    if (vhFile->hf != INVALID_HANDLE_VALUE)
	{
        goto NonVirtual;
	}
    
    vhFile->ulFileSize = vhFile->ulFilePointer;

	fSet = TRUE;

    goto cleanup;
    
NonVirtual:
	// real file
    fSet = SetEndOfFile(vhFile->hf);

	goto cleanup;

cleanup:

	return fSet;

}

//$--VSOF_FlushFileBuffers-----------------------------------------------------
//
// DESCRIPTION:	Flushes buffered data to file.
//
// INPUT:	vhFile	--	virtual file handle
//
// RETURNS:	BOOL	--	 TRUE if successful, FALSE otherwise.
//
//-----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
BOOL VSOF_FlushFileBuffers(		// RETURNS: BOOL
    IN VSOF_HANDLE vhFile		// virtual file handle
    )
{
	HRESULT	hr			=	NOERROR;
	BOOL	fFlushed	=	FALSE;	// TRUE if flushed

	DEBUGPRIVATE("VSOF_FlushFileBuffers()\n");

    if (vhFile->hf != INVALID_HANDLE_VALUE)
	{
        goto NonVirtual;
	}
    if (!MakeReal(vhFile))
	{
		hr = HR_LOG(E_FAIL);

		goto cleanup;
	}

	// Fall through!

NonVirtual:
	// real file
    fFlushed = FlushFileBuffers(vhFile->hf);

	goto cleanup;

cleanup:

	return fFlushed;

}

//$--VSOF_ReadFile-------------------------------------------------------------
//
// DESCRIPTION:	Read from file/buffer
//
// INPUT:	vhFile	--	virtual file handle
//			lpBuffer	--	output buffer
//			nNumberOfBytesToRead	--	# bytes to read
//			lpNumberOfBytesRead	--	# bytes read
//			lpOverlapped
//
// RETURNS:	BOOL
//
//-----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
BOOL VSOF_ReadFile(						// RETURNS: BOOL
    IN VSOF_HANDLE vhFile,				// virtual file handle
    IN LPVOID lpBuffer,					// output buffer
    IN DWORD nNumberOfBytesToRead,		// # bytes to read
    OUT LPDWORD lpNumberOfBytesRead,	// # bytes read
    OUT LPOVERLAPPED lpOverlapped
    )
{	
	HRESULT	hr		=	NOERROR;
	BOOL	fRead	=	FALSE;			// TRUE if successful

	DEBUGPRIVATE("VSOF_ReadFile()");

	hr = CHK_VSOF_ReadFile(vhFile, lpBuffer, nNumberOfBytesToRead,
	                       lpNumberOfBytesRead, lpOverlapped);

	if ( FAILED(hr) )
	{
		SetLastError(ERROR_INVALID_PARAMETER);

		return FALSE;
	}

    if (vhFile->hf != INVALID_HANDLE_VALUE)
	{
        goto NonVirtual;
	}
    
	// Initialize output parameters
	*lpNumberOfBytesRead = 0;
	if ( lpOverlapped != NULL )
	{
		ZeroMemory(lpOverlapped, sizeof(OVERLAPPED));
	}
    
    if (!nNumberOfBytesToRead) 
    {
        *lpNumberOfBytesRead = 0;
        fRead = TRUE;
		goto cleanup;
    }
        
    if (vhFile->ulFilePointer >= vhFile->ulFileSize) 
    {
        *lpNumberOfBytesRead = 0;
		fRead = TRUE;		// EOF for synchronous read
		goto cleanup;
    }
        
    // Take which ever is less.
    *lpNumberOfBytesRead = nNumberOfBytesToRead <
        (vhFile->ulFileSize - vhFile->ulFilePointer) ?
        nNumberOfBytesToRead : (vhFile->ulFileSize - vhFile->ulFilePointer);
    
    CopyMemory(lpBuffer, ((unsigned char*)vhFile->lpvVBuff) +
               vhFile->ulFilePointer, 
               *lpNumberOfBytesRead);
    
    vhFile->ulFilePointer += *lpNumberOfBytesRead;  // update file pointer.

	fRead = TRUE;    

	goto cleanup;
    
NonVirtual:
	// real file
    fRead = ReadFile(
    	vhFile->hf,
        lpBuffer,
        nNumberOfBytesToRead,
        lpNumberOfBytesRead,
        lpOverlapped);

	goto cleanup;

cleanup:

	return fRead;

}

//$--VSOF_WriteFile------------------------------------------------------------
//
// DESCRIPTION:	Writes buffer to file.
//
// INPUT:	vhFile	--	file handle
//			lpBuffer	--	input buffer
//			nNumberOfBytesToWrite	--	# bytes to write
//			lpNumberOfBytesWritten	--	# bytes written
//			lpOverlapped	--	overlapped
//
// RETURNS:	BOOL	--	TRUE if successful
//
//-----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
BOOL VSOF_WriteFile(					// RETURNS: BOOL
    IN VSOF_HANDLE vhFile,				// file handle
    IN LPCVOID lpBuffer,				// input buffer
    IN DWORD nNumberOfBytesToWrite,		// # bytes to write
    OUT LPDWORD lpNumberOfBytesWritten,	// # bytes written
    OUT LPOVERLAPPED lpOverlapped		// overlapped
    )
{
	HRESULT	hr			=	NOERROR;
	BOOL	fWritten	=	FALSE;		// TRUE if successful

	DEBUGPRIVATE("VSOF_WriteFile()\n");

	// check input parameters
	hr = CHK_VSOF_WriteFile(vhFile, lpBuffer, nNumberOfBytesToWrite,
	                        lpNumberOfBytesWritten, lpOverlapped);

	if ( FAILED(hr) )
	{
		SetLastError(ERROR_INVALID_PARAMETER);

		return FALSE;
	}

	// Initialize output parameters
	*lpNumberOfBytesWritten = 0;
	if ( lpOverlapped != NULL )
	{
		ZeroMemory(lpOverlapped, sizeof(OVERLAPPED));
	}

    if (vhFile->hf != INVALID_HANDLE_VALUE)
	{
        goto NonVirtual;
	}
    
    if ((nNumberOfBytesToWrite+vhFile->ulFilePointer) >= vhFile->dwVirtualBufferSize) 
    {
        if (!MakeReal(vhFile))
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

        goto NonVirtual;
    }
    
    CopyMemory(((unsigned char *)vhFile->lpvVBuff)+vhFile->ulFilePointer, lpBuffer,
               nNumberOfBytesToWrite);
    
    *lpNumberOfBytesWritten = nNumberOfBytesToWrite;
    
    vhFile->ulFilePointer += nNumberOfBytesToWrite;  // Update file pointer.
    vhFile->ulFileSize = vhFile->ulFilePointer;      // Update file size.

	fWritten = TRUE;

	goto cleanup;
    
NonVirtual:
	// real file
    fWritten = WriteFile(
    	vhFile->hf,
        lpBuffer,
        nNumberOfBytesToWrite,
        lpNumberOfBytesWritten,
        lpOverlapped);

	goto cleanup;

cleanup:

	return fWritten;

}

//$--VSOF_GetFileSize----------------------------------------------------------
//
// DESCRIPTION:	Gets the file's files
//
// INPUT:	vhFile	--	file handle
//
// OUTPUT:	lpFileSizeHigh	--	pointer to 64-bit file size
//
// RETURNS:	DWORD	--	file size
//
//-----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
DWORD VSOF_GetFileSize(						// RETURNS: DWORD
    IN VSOF_HANDLE vhFile,					// file handle
    OUT LPDWORD lpFileSizeHigh				// high file size
    )
{
	HRESULT	hr				=	NOERROR;
	DWORD	dwFileSize		=	0;			// file size

	DEBUGPRIVATE("VSOF_GetFileSize()\n");

	hr = CHK_VSOF_GetFileSize(vhFile, lpFileSizeHigh);

	if ( FAILED(hr) )
	{
		SetLastError(ERROR_INVALID_PARAMETER);

		return 0;
	}

    if (vhFile->hf != INVALID_HANDLE_VALUE)
	{
        goto NonVirtual;
	}
    
    if (lpFileSizeHigh)
	{
        *lpFileSizeHigh = 0;
	}
    
	dwFileSize = vhFile->ulFileSize;

	goto cleanup; 
    
NonVirtual:
	// real file
    dwFileSize = GetFileSize(
    	vhFile->hf,
        lpFileSizeHigh);

	goto cleanup;

cleanup:

	return dwFileSize;

}

//$--VSOF_CloseHandle----------------------------------------------------------
//
// DESCRIPTION:	Close file.
//
// INPUT:	vhObject	--	file handle
//
// RETURNS:	BOOL	--	TRUE if successful.
//
//----------------------------------------------------------------------------
#ifndef DEBUG
__inline
#endif
BOOL VSOF_CloseHandle(			// RETURNS: BOOL
    VSOF_HANDLE vhObject		// file handle
    )
{
	BOOL	fClosed	=	FALSE;	// TRUE if successful

	DEBUGPRIVATE("VSOF_CloseHandle()\n");

    if (vhObject->hf != INVALID_HANDLE_VALUE)
	{
        goto NonVirtual;
	}
    
    fClosed = TRUE;

	goto cleanup;
    
NonVirtual:
	// real file
    fClosed = CloseHandle(vhObject->hf);

	goto cleanup;

cleanup:

	return fClosed;

}

// Special virtual stream interface extensions for performance...
// There are certain situations where knowing if the stream has changed can be
// used to make desicions that will improve performance.

//$--VSOF_SetClean-------------------------------------------------------------
//
// DESCRIPTION:	Unsets stream dirty flag
//
// INPUT:	lpStream	--	stream pointer
//
// RETURNS:	HRESULT	--	NOERROF if successful,
//						E_INVALIDARG if bad input.
//
//-----------------------------------------------------------------------------
HRESULT VSOF_SetClean(
	IN LPSTREAM lpStream)	// stream pointer
{
	HRESULT	hr	=	NOERROR;

	// check input parameters
	hr = CHK_VSOF_SetClean(lpStream);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Unset stream dirty flag
    if (((LPVSOF)lpStream)->lpVSOFOrig)
        ((LPVSOF)lpStream)->lpVSOFOrig->fDirty = FALSE;
    else
        ((LPVSOF)lpStream)->fDirty = FALSE;

	// we are done

	RETURN(hr);

}

//$--VSOF_IsDirty-------------------------------------------------------------
//
// DESCRIPTION:	Returns stream dirty flag
//
// INPUT:	lpStream	--	stream pointer
//
// RETURNS:	HRESULT	--	NOERROF if successful,
//						E_INVALIDARG if bad input.
//
//-----------------------------------------------------------------------------
HRESULT VSOF_IsDirty(			// RETURNS:	BOOL
	IN LPSTREAM lpStream,		// stream pointer
	OUT BOOL * pfDirty)			// dirty flag pointer
{
	HRESULT	hr		=	NOERROR;

	// check input parameters
	hr = CHK_VSOF_IsDirty(lpStream, pfDirty);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Return dirty flag
    if (((LPVSOF)lpStream)->lpVSOFOrig)
	{
        *pfDirty = ((LPVSOF)lpStream)->lpVSOFOrig->fDirty;
	}
    else
	{
        *pfDirty = ((LPVSOF)lpStream)->fDirty;
	}

	// we are done

	RETURN(hr);

}

//$--VSOF_SetDirty-------------------------------------------------------------
//
// DESCRIPTION:	Sets stream dirty flag macro
//
// INPUT:	lpStream	--	stream pointer
//
// RETURNS:	VOID
//
//-----------------------------------------------------------------------------
static __inline VOID VSOF_SetDirty(	// RETURNS:	VOID
	IN LPVSOF lpVSOF)				// Virtual Stream On File pointer
{
	// consistency checking
	ASSERT_WRITE_PTR(lpVSOF, sizeof(VSOF), "Bad lpVSOF");

	// Set dirty flag
    if (lpVSOF->lpVSOFOrig)
        lpVSOF->lpVSOFOrig->fDirty = TRUE;
    else
        lpVSOF->fDirty = TRUE;
}

/* Unimplemented methods. */

//$--VSOF_Revert---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Revert()
//
// INPUT:		Same as for IStream::Revert()
//
// RETURNS:		HRESULT	--	STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_Revert(
	IN LPVSOF lpVSOF)		// this
{
	HRESULT	hr	=	NOERROR;

    DEBUGPUBLIC("VSOF_Revert()\n");

	// Check input parameters
	hr = CHK_VSOF_Revert(lpVSOF);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}
	
	RETURN(STG_E_INVALIDFUNCTION);

}

//$--VSOF_LockRegion---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::LockRegion()
//
// INPUT:		Same as for IStream::LockRegion()
//
// RETURNS:		HRESULT	--	STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_LockRegion (
	IN LPVSOF lpVSOF, 				// this
	IN ULARGE_INTEGER uliOffset, 	// offset
	IN ULARGE_INTEGER uliSize, 		// size
	IN DWORD dwLockType)			// lock type
{
	HRESULT	hr	=	NOERROR;

    DEBUGPUBLIC("VSOF_LockRegion()\n");

	hr = CHK_VSOF_LockRegion(lpVSOF, uliOffset, uliSize, dwLockType);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}
	
	RETURN(STG_E_INVALIDFUNCTION);

}

//$--VSOF_UnlockRegion---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::UnlockRegion()
//
// INPUT:		Same as for IStream::UnlockRegion()
//
// RETURNS:		HRESULT	--	STG_E_INVALIDFUNCTION
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_UnlockRegion (
	IN LPVSOF lpVSOF, 				// this
	IN ULARGE_INTEGER uliOffset, 	// offset
	IN ULARGE_INTEGER uliSize, 		// length
	IN DWORD dwLockType)			// lock type
{
	HRESULT	hr	=	NOERROR;

    DEBUGPUBLIC("VSOF_UnlockRegion()\n");

	hr = CHK_VSOF_UnlockRegion(lpVSOF, uliOffset, uliSize, dwLockType);
	
	if ( FAILED(hr) )
	{
		RETURN(hr);
	}
		
	RETURN(STG_E_INVALIDFUNCTION);

}

// IUnknown methods:

//$--VSOF_QueryInterface---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::QueryInterface()
//
// INPUT:		Same as for IStream::QueryInterface()
//
// RETURNS:		HRESULT	--	NOERROR	if VSOF object supports interface,
//							E_NOINTERFACE if VSOF object doesn't support interface,
//							E_INVALIDARG if bad input.
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_QueryInterface(
	IN LPVSOF lpVSOF, 				// this
	IN REFIID riid, 				// interface identifier reference
	OUT LPVOID FAR * lppvObj)		// interface object pointer
{
	HRESULT	hr	=	NOERROR;

    DEBUGPUBLIC("VSOF_QueryInterface()\n");

	// check input parameters
	hr = CHK_VSOF_QueryInterface(lpVSOF, riid, lppvObj);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}
	
	// Initialize output parameters
	*lppvObj = NULL;

	if ( (IsEqualIID(riid, &IID_IUnknown) == FALSE) &&
		 ( IsEqualIID(riid, &IID_IStream) == FALSE) )
	{
		hr = HR_LOG(E_NOINTERFACE);

		goto cleanup;
	}

	lpVSOF->lcInit++;
	*lppvObj = lpVSOF;

	// we are done.

cleanup:

	RETURN(hr);

}


//$--VSOF_AddRef---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::AddRef()
//
// INPUT:		this
//
// RETURNS:		ULONG	--	reference count
//
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) VSOF_AddRef(	// RETURNS: ULONG
	IN LPVSOF lpVSOF)				// this
{
	HRESULT	hr	=	NOERROR;

	DEBUGPUBLIC("VSOF_AddRef()\n");

	hr = CHK_VSOF_AddRef(lpVSOF);

	if ( FAILED(hr) )
	{
		return 0;
	}
	
	return (++lpVSOF->lcInit);
}

//$--VSOF_Clone---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Clone()
//
// INPUT:		this,
//		
// OUTPUT:		virtual stream pointer
//
// RETURNS:		HRESULT	--	NOERROR if successful,
//							E_INVALIDARG if bad input,
//							E_ACCESSDENIED if no access,
//							EDK_E_NOT_FOUND if file not found,
//							E_FAIL otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_Clone (
	IN LPVSOF lpVSOF, 				// this
	OUT LPSTREAM FAR *lppStm)		// virtual stream pointer
{
    HRESULT			hr 			=	NOERROR;
    LPVSOF			lpVSOFClone	=	NULL;
	DWORD			fdwAccess	=	0;
	DWORD			fdwCreate	=	0;
    DWORD			fdwShare	=	0;
    DWORD			fdwAttr		=	0;
    LARGE_INTEGER	li 			=	{0};

	DEBUGPUBLIC("VSOF_Clone()\n");

	// check input parameters	
	hr = CHK_VSOF_Clone(lpVSOF, lppStm);
	    
	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// initialize output parameters	
    *lppStm = NULL;
    
    ASSERTERROR(lpVSOF->ulFlags & VSOF_CLONEABLE, "Bad lpVSOF->ulFlags");
    
    li.LowPart = VSOF_SetFilePointer(
    	lpVSOF,
        0,
        &li.HighPart,
        FILE_CURRENT);
    
    if (li.LowPart == 0xFFFFFFFF) 
    { 
    	// check for an error;
        hr = HRESULT_FROM_WIN32(GetLastError()); 
		if ( FAILED(hr) )
        {
            goto cleanup;
        }            
    }
                        
	hr = (*(lpVSOF->lpfnAlloc)) (sizeof(VSOF), &lpVSOFClone);
	if (FAILED (hr)) 
	{
		goto cleanup;
    }
    
	ZeroMemory(lpVSOFClone, sizeof(VSOF));
	lpVSOFClone->lpVtbl = (VSOF_Vtbl FAR *)&VtblVSOF;
	lpVSOFClone->lcInit = 1;
	lpVSOFClone->ulFlags = lpVSOF->ulFlags;
	lpVSOFClone->lpfnAlloc = lpVSOF->lpfnAlloc;
	lpVSOFClone->lpfnFree = lpVSOF->lpfnFree;
    
	lpVSOFClone->hf = INVALID_HANDLE_VALUE;
        
	fdwCreate = OPEN_EXISTING;

    fdwAttr = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN;
    if (lpVSOF->ulFlags & STGM_DELETEONRELEASE)
        fdwAttr = FILE_ATTRIBUTE_TEMPORARY;  // keeps more data in memory.
    
    if (lpVSOF->ulFlags & STGM_READWRITE) 
    {
		fdwAccess = GENERIC_READ | GENERIC_WRITE;
    } 
    else 
    {
		fdwAccess = GENERIC_READ;
    }

	// Determine level of concurrent access allowed for file.
	fdwShare = dwComputeShareFlags(lpVSOF->ulFlags);

    if (lpVSOF->lpVSOFOrig) 
    {
        lpVSOFClone->lpVSOFOrig = lpVSOF->lpVSOFOrig;
        lpVSOFClone->hf = CreateFile (
        	lpVSOF->lpVSOFOrig->rgchFile,
            fdwAccess,
            fdwShare,
            NULL,
            fdwCreate,
            fdwAttr,
            NULL);
    } 
    else 
    {
        lpVSOFClone->lpVSOFOrig = lpVSOF;
        lpVSOFClone->hf = CreateFile (
        	lpVSOF->rgchFile,
            fdwAccess,
            fdwShare,
            NULL,
            fdwCreate,
            fdwAttr,
            NULL);
    }
    
	if (lpVSOFClone->hf == INVALID_HANDLE_VALUE)
	{
		DWORD dwLastError = GetLastError();

		switch(dwLastError)
		{
			case ERROR_ACCESS_DENIED:
				hr = HR_LOG(E_ACCESSDENIED);
				goto cleanup;

			case ERROR_FILE_NOT_FOUND:
				hr = HR_LOG(EDK_E_NOT_FOUND);
				goto cleanup;

			default:
				hr = HR_LOG(E_FAIL);
				goto cleanup;
		}        
	}

    // Set the file position to match that of the file we're cloning.
    li.LowPart = VSOF_SetFilePointer(
    	lpVSOFClone,
        li.LowPart,
        &li.HighPart,
        FILE_BEGIN);

    if (li.LowPart == 0xFFFFFFFF) 
    { // check for an error;
		hr = HRESULT_FROM_WIN32(GetLastError());
		if ( FAILED(hr) )
		{            
            goto cleanup;
        }            
    }
    
    if (lpVSOF->lpVSOFOrig) 
    {
        lpVSOF->lpVSOFOrig->lpVtbl->AddRef(lpVSOF);  // for ourself.    
    } 
    else 
    {
        lpVSOF->lpVtbl->AddRef(lpVSOF);  // for ourself.    
    }
    *lppStm = (LPSTREAM)lpVSOFClone;
    
cleanup:

    if ( FAILED(hr) )
    {
        if (lpVSOFClone) 
        {
            if (lpVSOFClone->hf == INVALID_HANDLE_VALUE)
			{
                VSOF_CloseHandle(lpVSOFClone);
			}
            (*(lpVSOF->lpfnFree)) (lpVSOFClone);
        }
    }

	RETURN(hr);

}

//$--VSOF_Release---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Release()
//
// INPUT:		this,
//
// RETURNS:		ULONG	--	new reference count.
//
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) VSOF_Release (		// RETURNS:	ULONG
	IN LPVSOF lpVSOF)					// this
{
	HRESULT	hr			=	NOERROR;
	ULONG	nRefCount	=	0;	// new reference count

	DEBUGPUBLIC("VSOF_Release()\n");

	// Check input parameters
	hr = CHK_VSOF_Release(lpVSOF);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	if ((--lpVSOF->lcInit) == 0)
	{
		// last reference to object
        if (lpVSOF->lpVSOFOrig)  // This is a clone..
        {
            lpVSOF->lpVSOFOrig->lpVtbl->Release(lpVSOF->lpVSOFOrig);
            
			if (!VSOF_CloseHandle (lpVSOF))
			{
                HR_LOG(E_FAIL);

				lpVSOF->lcInit = 1;
				nRefCount = 0xFFFFFFFF;

				goto cleanup;
			}
        }
        else if (lpVSOF->hf != INVALID_HANDLE_VALUE) 
        {
			if (!VSOF_CloseHandle (lpVSOF))
			{
                HR_LOG(E_FAIL);

				lpVSOF->lcInit = 1;
				nRefCount = 0xFFFFFFFF;

				goto cleanup;
			}

			if (lpVSOF->ulFlags & (STGM_DELETEONRELEASE | VSOF_CLONEABLE))
			{
				DeleteFile (lpVSOF->rgchFile);
			}
		}
        if (lpVSOF->lpvVBuff)
		{
            (*lpVSOF->lpfnFree) (lpVSOF->lpvVBuff);
		}
		(*lpVSOF->lpfnFree) (lpVSOF);

		// It's gone!
		nRefCount = 0;

		goto cleanup;
	}

	// Still has references
	nRefCount = lpVSOF->lcInit;

cleanup:

	return nRefCount;

}

//$--VSOF_Read---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Read()
//
// INPUT:		lpVSOF	--	this,
//				lpvData	--	read buffer
//				cbSize	--	size of read buffer
//
// OUTPUT:		lpcbRead	--	# bytes read
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							STG_E_INVALIDPARAM if bad input,
//							STG_E_READFAULT otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_Read (
	IN LPVSOF lpVSOF,			// this
	IN VOID HUGEP * lpvData,	// buffer to read data into
	IN ULONG cbSize,			// # bytes to read
	OUT ULONG FAR * lpcbRead)	// # bytes read
{
	HRESULT hr 		= 	NOERROR;
	ULONG 	cbRead	=	0;			// # bytes read

    DEBUGPUBLIC("VSOF_Read()\n");

	// check input parameters
	hr = CHK_VSOF_Read(lpVSOF, lpvData, cbSize, lpcbRead);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Initialize output parameters
	if ( lpcbRead != NULL )
	{
		*lpcbRead = 0;
	}

	ASSERTERROR ((lpVSOF->hf != INVALID_HANDLE_VALUE) || (lpVSOF->lpvVBuff),
	    "Bad lpVSOF->hf or bad lpVSOF->lpvVBuff");
	if (!VSOF_ReadFile (lpVSOF, lpvData, cbSize, &cbRead, NULL))
	{
        hr = HR_LOG(STG_E_READFAULT);
		// don't exit early!
	}

	// Set output parameters
	if (lpcbRead != NULL)
	{
		*lpcbRead = cbRead;
	}

	RETURN(hr);
}

//$--VSOF_Write---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Write()
//
// INPUT:		lpVSOF	--	this,
//				lpvData	--	write buffer
//				cbSize	--	size of write buffer
//
// OUTPUT:		lpcbWritten	--	# bytes written
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							STG_E_INVALIDPARAM if bad input,
//							STG_E_MEDIUMFULL otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_Write(
	IN LPVSOF lpVSOF,				// this
	IN VOID HUGEP * lpvData,		// buffer to write data from
	IN ULONG cbSize,				// size of buffer
	OUT ULONG FAR * lpcbWritten)	// # bytes written
{
	HRESULT hr 			= 	NOERROR;
	ULONG 	cbWritten	=	0;		// # bytes written

    DEBUGPUBLIC("VSOF_Write()\n");

	// check input parameters
	hr = CHK_VSOF_Write(lpVSOF, lpvData, cbSize, lpcbWritten);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Initialize output parameters
	if ( lpcbWritten != NULL )
	{
		*lpcbWritten = 0;
	}

	// Set dirty flag on stream.
    VSOF_SetDirty(lpVSOF);

	ASSERTERROR ((lpVSOF->hf != INVALID_HANDLE_VALUE) || (lpVSOF->lpvVBuff),
	    "Bad lpVSOF->hf or bad lpVSOF->lpvVBuff");
	if (!VSOF_WriteFile (lpVSOF, lpvData, cbSize, &cbWritten, NULL))
	{
		hr = HR_LOG(STG_E_MEDIUMFULL);
		// don't exit early
	}

	// Set output parameters
	if (lpcbWritten != NULL)
	{
		*lpcbWritten = cbWritten;
	}

	RETURN (hr);
}

//$--VSOF_Seek---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Seek()
//
// INPUT:		lpVSOF	--	this,
//				liMOve	--	offset
//				dwMode	--	origin
//				
// OUTPUT:		lpliPos	--	new position
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							STG_E_INVALIDPARAM if bad input,
//							STG_E_SEEKERROR otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_Seek (
	IN LPVSOF lpVSOF,					// this
	IN LARGE_INTEGER liMove,			// offset
	IN DWORD dwMode,					// origin
	OUT ULARGE_INTEGER FAR * lpliPos)	// new position
{
	HRESULT	hr		=	NOERROR;
	ULONG	ibLow	=	0;
	ULONG	ibHigh	=	0;

    DEBUGPUBLIC("VSOF_Seek()\n");

	ASSERTERROR (STREAM_SEEK_SET == FILE_BEGIN, "Bad STREAM_SEEK_SET");
	ASSERTERROR (STREAM_SEEK_CUR == FILE_CURRENT, "Bad STREAM_SEEK_CUR");
	ASSERTERROR (STREAM_SEEK_END == FILE_END, "Bad STREAM_SEEK_END");	

	// Check input parameters
	hr = CHK_VSOF_Seek(lpVSOF, liMove, dwMode, lpliPos);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}
	
	// Initialize output parameters
	if ( lpliPos != NULL )
	{
		ZeroMemory(lpliPos, sizeof(ULARGE_INTEGER));
	}

	ASSERTERROR ((lpVSOF->hf != INVALID_HANDLE_VALUE) || (lpVSOF->lpvVBuff),
	    "Bad lpVSOF->hf or bad lpVSOF->lpvVBuff");
	
#ifdef CHICAGO

	//	Windows 95 doesn't support large seeks
	//
	ibHigh = liMove.HighPart;
	ibLow = VSOF_SetFilePointer (lpVSOF, liMove.LowPart, NULL, dwMode);
	ibHigh = 0;
	
#else
	
	ibHigh = liMove.HighPart;
	ibLow = VSOF_SetFilePointer (lpVSOF, liMove.LowPart, &ibHigh, dwMode);
	
#endif
	
	if ((ibLow == 0xFFFFFFFF) && GetLastError())
	{
		hr = HR_LOG(STG_E_SEEKERROR);
		
		goto cleanup;
	}

	// Set output parameters
	if (lpliPos)
	{
		lpliPos->LowPart = ibLow;
		lpliPos->HighPart = ibHigh;
	}

cleanup:

	RETURN(hr);

}

//$--VSOF_SetSize---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::SetSize()
//
// INPUT:		lpVSOF	--	this,
//				liSize	--	new size
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							STG_E_INVALIDPARAM if bad input,
//							STG_E_SEEKERROR otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_SetSize (
	IN LPVSOF lpVSOF, 				// this
	IN ULARGE_INTEGER liSize)		// new size
{
	HRESULT	hr		=	NOERROR;
	ULONG	ibLow	=	0;
	ULONG 	ibHigh	=	0;

    DEBUGPUBLIC("VSOF_SetSize()\n");

	// check input parameters
	hr = CHK_VSOF_SetSize(lpVSOF, liSize);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Set stream dirty flag.
	VSOF_SetDirty(lpVSOF);

	ibLow = VSOF_SetFilePointer (lpVSOF, 0, &ibHigh, FILE_CURRENT);
	if ((ibLow == 0xFFFFFFFF) && GetLastError())
	{
		hr = HR_LOG(STG_E_SEEKERROR);
		goto cleanup;
	}

	liSize.LowPart = VSOF_SetFilePointer (lpVSOF, liSize.LowPart, &liSize.HighPart, FILE_BEGIN);
	if ((liSize.LowPart == 0xFFFFFFFF) && GetLastError())
	{
		hr = HR_LOG(STG_E_SEEKERROR);
		goto cleanup;
	}

	if (!VSOF_SetEndOfFile (lpVSOF))
	{
		hr = HR_LOG(STG_E_WRITEFAULT);
		goto cleanup;
	}

cleanup:

	ibLow = VSOF_SetFilePointer (lpVSOF, ibLow, &ibHigh, FILE_BEGIN);
	if ((ibLow == 0xFFFFFFFF) && GetLastError())
	{
		hr = HR_LOG(STG_E_SEEKERROR);
		goto cleanup;
	}

	RETURN(hr);

}

//$--VSOF_CopyTo---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::CopyTo()
//
// INPUT:		lpVSOF	--	this,
//				lpStrmDest	--	destination stream pointer
//				cbCopy	--	# bytes to copy
//
// OUTPUT:		lpcbRead	--	# bytes read from source stream
//				lpcbWritten	--	# bytes written to destination stream
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							STG_E_INVALIDPARAM if bad input,
//							STG_E_MEDIUMFULL if disk full,
//							STG_E_READFAULT otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_CopyTo (
	IN LPVSOF lpVSOF,						// this
	IN LPSTREAM lpStrmDst,					// destination stream pointer
	IN ULARGE_INTEGER cbCopy,				// # bytes to copy
	OUT ULARGE_INTEGER FAR * lpcbRead,		// # bytes read
	OUT ULARGE_INTEGER FAR * lpcbWritten)	// # bytes written
{
	HRESULT hr			=	NOERROR;
	LPBYTE 	lpb 		= 	NULL;
	ULONG 	cbr			=	0;
	ULONG 	cbrTotal	=	0;
	ULONG 	cbw			=	0;
	ULONG 	cbwTotal 	= 	0;

    DEBUGPUBLIC("VSOF_CopyTo()\n");

	// Check input parameters
	hr = CHK_VSOF_CopyTo(lpVSOF, lpStrmDst, cbCopy, lpcbRead, lpcbWritten);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Initialixe output paramters
	if ( lpcbRead != NULL )
	{
		ZeroMemory(lpcbRead, sizeof(ULARGE_INTEGER));
	}

	if ( lpcbWritten != NULL )
	{
		ZeroMemory(lpcbWritten, sizeof(ULARGE_INTEGER));
	}

	//	Since we are really not supporting excessively large
	//	streams, we are not gonna deal with the high long
	//
	hr = (*lpVSOF->lpfnAlloc) (BUFFER_SIZE, &lpb);
	if (FAILED (hr))
	{
		goto cleanup;
	}

	while (cbCopy.LowPart)
	{
		ULONG cb = min (cbCopy.LowPart, BUFFER_SIZE);

		if (!VSOF_ReadFile (lpVSOF, lpb, cb, &cbr, NULL))
		{
			hr = HR_LOG(STG_E_READFAULT);
			goto cleanup;
		}

		hr = lpStrmDst->lpVtbl->Write (lpStrmDst, lpb, cbr, &cbw);
		if (FAILED (hr))
		{
			goto cleanup;
		}

		if (cbr != cbw)
		{
			ASSERTERROR (FALSE, "VSOF_CopyTo(), bytes read != bytes written\n");
			hr = HR_LOG(STG_E_MEDIUMFULL);
			goto cleanup;
		}

		cbrTotal += cbr;
		cbwTotal += cbw;

		//	They asked to copy more than available
		//
		if (cb != cbr)
		{
			break;
		}

		cbCopy.LowPart -= cb;
	}

cleanup:

	// Set output parameters
	if (lpcbRead != NULL)
	{
		lpcbRead->LowPart = cbrTotal;
		lpcbRead->HighPart = 0;
	}

	if (lpcbWritten != NULL)
	{
		lpcbWritten->LowPart = cbwTotal;
		lpcbWritten->HighPart = 0;
	}

	if (lpb)
	{
		(*lpVSOF->lpfnFree) (lpb);
	}

	RETURN (hr);

}

//$--VSOF_Commit---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Commit()
//
// INPUT:		lpVSOF	--	this,
//				ulFlags	--	flags
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							STG_E_INVALIDPARAM if bad input,
//							STG_E_WRITEFAULT otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_Commit(
	IN LPVSOF lpVSOF, 			// this
	IN ULONG ulFlags)			// flags
{
	HRESULT	hr	=	NOERROR;

    DEBUGPUBLIC("VSOF_Commit()\n");

	// check input parameters
	hr = CHK_VSOF_Commit(lpVSOF, ulFlags);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	//	There is no 16bit equivilent here
	//
	if (!VSOF_FlushFileBuffers (lpVSOF))
	{
		hr = HR_LOG(STG_E_WRITEFAULT);

		goto cleanup;
	}

cleanup:

	RETURN(hr);

}

//$--VSOF_Stat---------------------------------------------------------------
//
// DESCRIPTION:	Same as for IStream::Stat()
//
// INPUT:		lpVSOF	--	this,
//				lpStg	--	storage statistics pointer
//				ulFlags	--	flags
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							STG_E_INVALIDPARAM if bad input,
//							STG_E_INVALIDHEADER otherwise
//
//-----------------------------------------------------------------------------
STDMETHODIMP VSOF_Stat(
	IN LPVSOF lpVSOF,			// this
	IN STATSTG FAR * lpStg, 	// storage statistics pointer
	IN DWORD dwFlags)			// flags
{
	HRESULT	hr		=	NOERROR;
	ULONG	cbLow	=	0;
	ULONG	cbHigh	=	0;

    DEBUGPUBLIC("VSOF_Stat)\n");

	// check input parameters
	hr = CHK_VSOF_Stat(lpVSOF, lpStg, dwFlags);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

	// Initlialize output parameter	
	ZeroMemory(lpStg, sizeof(STATSTG));

	cbLow = VSOF_GetFileSize (lpVSOF, &cbHigh);
	if ((cbLow == 0xFFFFFFFF) && GetLastError())
	{
		hr = HR_LOG(STG_E_INVALIDHEADER);
		// don't return early!
	}

	lpStg->type = STGTY_STREAM;
	lpStg->cbSize.LowPart = cbLow;
	lpStg->cbSize.HighPart = cbHigh;
	lpStg->grfMode = lpVSOF->ulFlags;

	RETURN(hr);

}

//$--HrOpenVirtualStreamOnFile---------------------------------------------------------------
//
// DESCRIPTION:	Open/create a virtual stream on the specified file.
//
// INPUT:		lpfnAlloc	--	memory allocation routine
//				lpfnFree	--	memory deallocation routine
//				ulFlags		--	stream flags
//				lpszPath	--	fully pathed file name
//				lpszPrefix	--	file prefix
//
// OUTPUT:		lppStream	--	virtual stream pointer
//
// RETURNS:		HRESULT	--	NOERROR if sucessful,
//							E_INVALIDARG if bad input,
//							E_ACCESSDENIED if no access,
//							EDK_E_NOT_FOUND if file not found,
//							E_FAIL otherwise
//
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE HrOpenVirtualStreamOnFile(
	IN LPALLOCATEBUFFER lpfnAlloc,	// allocation routine
	IN LPFREEBUFFER lpfnFree,		// deallocation routine
	IN ULONG ulFlags,				// stream flags
	IN LPSTR lpszFile,				// fully-pathed file name
	IN LPSTR lpszPrefix,			// file prefix
	OUT LPSTREAM FAR * lppStrm)		// virtual stream pointer
{
	HRESULT hr						=	NOERROR;
	DWORD 	fdwAccess				=	0;
	DWORD 	fdwCreate				=	0;
    DWORD 	fdwShare				=	0;
    DWORD 	fdwAttr					=	0;
    DWORD 	dwVirtualBufferSize		=	0;
    char *	lpszVirtualBufferSize	=	0;
	LPVSOF 	lpVSOF 					= 	NULL;

    DEBUGPUBLIC("HrOpenVirtualStreamOnFile()\n");

	// Check input parameters
	hr = CHK_HrOpenVirtualStreamOnFile(lpfnAlloc, lpfnFree, ulFlags, lpszFile,
									 lpszPrefix, lppStrm);

	if ( FAILED(hr) )
	{
		RETURN(hr);
	}

    fdwAttr = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN;
    if (ulFlags & STGM_DELETEONRELEASE) 
    {
        fdwAttr = FILE_ATTRIBUTE_TEMPORARY;  // keeps more data in memory.
        if (!(ulFlags & VSOF_CLONEABLE))
		{
            fdwAttr |= FILE_FLAG_DELETE_ON_CLOSE;  // faster than DeleteFile()!
		}
    }
    
	if (ulFlags & STGM_READWRITE)
	{
		fdwAccess = GENERIC_READ | GENERIC_WRITE;
        
		if (ulFlags & STGM_CREATE)
		{
			fdwCreate = CREATE_ALWAYS;
		}
		else
		{
			fdwCreate = TRUNCATE_EXISTING;
		}
	}
	else
	{
		fdwCreate = OPEN_EXISTING;
		fdwAccess = GENERIC_READ;
	}

	// Determine level of concurrent access allowed for file.
	fdwShare = dwComputeShareFlags(ulFlags);

	hr = (*lpfnAlloc) (sizeof(VSOF), &lpVSOF);
	if (FAILED (hr))
	{
		goto cleanup;
	}

	ZeroMemory(lpVSOF, sizeof(VSOF));
	lpVSOF->hf = INVALID_HANDLE_VALUE;
	lpVSOF->lpVtbl = (VSOF_Vtbl FAR *)&VtblVSOF;
	lpVSOF->lcInit = 1;
	lpVSOF->ulFlags = ulFlags & ~VSOF_UNIQUEFILENAME;
	lpVSOF->lpfnAlloc = lpfnAlloc;
	lpVSOF->lpfnFree = lpfnFree;

    dwVirtualBufferSize = VIRTUAL_BUFFER_SIZE;
    if (lpszVirtualBufferSize = getenv(VBUFF_ENV_NAME))
	{
        dwVirtualBufferSize = atol(lpszVirtualBufferSize);
	}

	// Algorithm:
	// 1) Open "non-temporary" files for reading or writing.    
	// 2) Create a buffer for "temporary" file data.

	if (ulFlags & VSOF_UNIQUEFILENAME)
	{
        if ((ulFlags & STGM_DELETEONRELEASE) && !(ulFlags & VSOF_CLONEABLE) &&
            dwVirtualBufferSize) 
        {
			// User wants a temporary file.
            // We take the virtual fork in the road...
            if (!lpszFile)
			{
                lpszFile = "";
			}
            if (!lpszPrefix)
			{
                lpszPrefix = "";
			}
                
            hr = (*lpfnAlloc) (dwVirtualBufferSize, &lpVSOF->lpvVBuff);
            if ( FAILED(hr) )
			{
                goto cleanup;
			}
            
            if ((lstrlen(lpszFile) + lstrlen(lpszPrefix) + 2) >= MAX_PATH) 
            {
                ASSERTERROR(FALSE,"lpszFile and lpszPrefix are too long!");

                hr = HR_LOG(E_FAIL);
				goto cleanup;
            }

            // Copy the filename and prefix so we can create a temp file later.
            lstrcpy(lpVSOF->rgchFile, lpszFile);
            lstrcpy(lpVSOF->rgchFile + lstrlen(lpszFile) + 1, lpszPrefix);
            lpVSOF->dwVirtualBufferSize = dwVirtualBufferSize;

			// We are done with setup for a temporary (virtual) file.
            goto cleanup;
        }
        
		hr = ScGetVSOFFilename (lpszFile, lpszPrefix, lpVSOF->rgchFile);
		if (FAILED (hr))
		{
			goto cleanup;
		}
	}
	else
	{
		ASSERTERROR (lstrlen (lpszFile) <= MAX_PATH, "Bad lstrlen(lpszFile)");
		lstrcpy (lpVSOF->rgchFile, lpszFile);
	}

	// Want a non-temporary (real) file.
	lpVSOF->hf = CreateFile(
		lpVSOF->rgchFile,
		fdwAccess,
		fdwShare,
		NULL,
		fdwCreate,
		fdwAttr,
		NULL);

	if (lpVSOF->hf == INVALID_HANDLE_VALUE)
	{
		DWORD dwLastError = GetLastError();

		switch(dwLastError)
		{
			case ERROR_ACCESS_DENIED:

				hr = HR_LOG(E_ACCESSDENIED);
				goto cleanup;

			case ERROR_FILE_NOT_FOUND:

				hr = HR_LOG(EDK_E_NOT_FOUND);
				goto cleanup;

			default:

				hr = HR_LOG(E_FAIL);
				goto cleanup;
		}
	}

cleanup:

	if (FAILED (hr))
	{
		if (lpVSOF)
		{
			if (lpVSOF->hf != INVALID_HANDLE_VALUE)
			{
				VSOF_CloseHandle (lpVSOF);
				if (ulFlags & STGM_DELETEONRELEASE)
					DeleteFile (lpVSOF->rgchFile);
			}
			(*lpfnFree) (lpVSOF);
			lpVSOF = NULL;
		}
	}

	*lppStrm = (LPSTREAM)lpVSOF;

	RETURN(hr);
}

