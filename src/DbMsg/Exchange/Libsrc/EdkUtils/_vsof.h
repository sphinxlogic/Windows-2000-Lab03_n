//--_vsof.h--------------------------------------------------------------------
//
// This file contains methods and #define's for implementing an OLE 2.0
// storage stream (as defineed in the OLE 2.0 specs) on top of OS file.
//
// Copyright 1986-1996.  Microsoft Corporation.  All Rights Reserved.
//
//-------------------------------------------------------------------------------

#ifndef __VSOF_H
#define __VSOF_H

#define BUFFER_SIZE 4096
#define VIRTUAL_BUFFER_SIZE 16384L
#define VBUFF_ENV_NAME "virtual_stream_on_file_buffer_size"
#define VSOF_DEFAULT_PREFIX "VSF"

#define SET_FILE_POINTER_ERROR 0xffffffff

/*	IStream Interface ------------------------------------------------ */

//Warning:  This is not multithread safe with respect to clones.

#define MAPI_ISTREAM_METHODS(IPURE)										\
	MAPIMETHOD(Read)													\
		(THIS_	OUT VOID HUGEP *				lpv,						\
				IN ULONG						cb,							\
				OUT ULONG FAR *					lpcbRead) IPURE;			\
	MAPIMETHOD(Write)													\
		(THIS_	IN VOID const HUGEP *			lpv,						\
				IN ULONG						cb,							\
				OUT ULONG FAR *					lpcbWritten) IPURE;			\
	MAPIMETHOD(Seek)													\
		(THIS_	IN LARGE_INTEGER				libMove,					\
				IN DWORD						dwOrigin,					\
				OUT ULARGE_INTEGER FAR *		lplibNewPosition) IPURE;	\
	MAPIMETHOD(SetSize)													\
		(THIS_	IN ULARGE_INTEGER				libNewSize) IPURE;			\
	MAPIMETHOD(CopyTo)													\
		(THIS_	IN IStream FAR *				lpstm,						\
				IN ULARGE_INTEGER				cb,							\
				OUT ULARGE_INTEGER FAR *		lpcbRead,					\
				OUT ULARGE_INTEGER FAR *		lpcbWritten) IPURE;			\
	MAPIMETHOD(Commit)													\
		(THIS_	IN DWORD						dwCommitFlags) IPURE;		\
	MAPIMETHOD(Revert)													\
		(THIS)								IPURE;						\
	MAPIMETHOD(LockRegion)												\
		(THIS_	IN ULARGE_INTEGER				libOffset,					\
				IN ULARGE_INTEGER				cb,							\
				IN DWORD						dwLockType) IPURE;			\
	MAPIMETHOD(UnlockRegion)											\
		(THIS_	IN ULARGE_INTEGER				ulibOffset,					\
				IN ULARGE_INTEGER				cb,							\
				IN DWORD						dwLockType) IPURE;			\
	MAPIMETHOD(Stat)													\
		(THIS_	IN STATSTG FAR *				lpstatstg,					\
				IN DWORD						dwStatFlag) IPURE;			\
	MAPIMETHOD(Clone)													\
		(THIS_	OUT IStream FAR * FAR *			lppstm) IPURE;				\

/*	VSOF Interface -------------------------------------------------- */

#undef	INTERFACE
#define	INTERFACE struct _VSOF
#undef	MAPIMETHOD_
#define	MAPIMETHOD_(type, method)	MAPIMETHOD_DECLARE(type, method, VSOF_)
		MAPI_IUNKNOWN_METHODS(IMPL)
		MAPI_ISTREAM_METHODS(IMPL)
#undef	MAPIMETHOD_
#define	MAPIMETHOD_(type, method)	MAPIMETHOD_TYPEDEF(type, method, VSOF_)
		MAPI_IUNKNOWN_METHODS(IMPL)
		MAPI_ISTREAM_METHODS(IMPL)
#undef	MAPIMETHOD_
#define	MAPIMETHOD_(type, method)	STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(VSOF_)
{
	BEGIN_INTERFACE
	MAPI_IUNKNOWN_METHODS(IMPL)
	MAPI_ISTREAM_METHODS(IMPL)
};

//$--_VSOF---------------------------------------------------------------------
//
// Virtual Stream On File internal structure.
//
//-----------------------------------------------------------------------------
typedef struct _VSOF
{
	VSOF_Vtbl FAR *		lpVtbl;
	LONG				lcInit;
	ULONG				ulFlags;
	CHAR				rgchFile[MAX_PATH];
	HANDLE				hf;         // == INVALID_HANDLE_VALUE if in virutal mode.
	LPALLOCATEBUFFER	lpfnAlloc;
	LPFREEBUFFER		lpfnFree;
    DWORD               dwVirtualBufferSize;
    ULONG               ulFileSize;     // for virtual mode.
    ULONG               ulFilePointer;  // for virtual mode.
    LPVOID              lpvVBuff;    	//  Virtual buffer.  NULL if not in virtual mode.
    struct _VSOF *      lpVSOFOrig;  	// Original.  we are a clone if this is non-NULL.
	BOOL                fDirty;			// stream dirty flag

} VSOF, FAR * LPVSOF;

typedef struct _VSOF *VSOF_HANDLE;

DWORD
VSOF_SetFilePointer(
    VSOF_HANDLE vhFile,
    LONG lDistanceToMove,
    PLONG lpDistanceToMoveHigh,
    DWORD dwMoveMethod
    );

BOOL
VSOF_SetEndOfFile(
    VSOF_HANDLE vhFile
    );

BOOL
VSOF_FlushFileBuffers(
    VSOF_HANDLE vhFile
    );

BOOL
VSOF_ReadFile(
    VSOF_HANDLE vhFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    );

BOOL
VSOF_WriteFile(
    VSOF_HANDLE vhFile,
    LPCVOID lpBuffer,
    DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    );

DWORD
VSOF_GetFileSize(
    VSOF_HANDLE vhFile,
    LPDWORD lpFileSizeHigh
    );

BOOL
VSOF_CloseHandle(
    VSOF_HANDLE vhObject
    );

VSOF_HANDLE
VSOF_CreateFile(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );

BOOL
VSOF_DeleteFile(
    VSOF_HANDLE vhFile
    );

STDMETHODIMP_(VOID) InvalidateVSOF (LPVSOF);

//$--VSOF_Vtbl-----------------------------------------------------------------
//
// Virtual function table for the Virtual Stream On File interface.
//
//-----------------------------------------------------------------------------
const VSOF_Vtbl VtblVSOF =
{
	VSOF_QueryInterface,
	VSOF_AddRef,
	VSOF_Release,
	VSOF_Read,
	VSOF_Write,
	VSOF_Seek,
	VSOF_SetSize,
	VSOF_CopyTo,
	VSOF_Commit,
	VSOF_Revert,
	VSOF_LockRegion,
	VSOF_UnlockRegion,
	VSOF_Stat,
	VSOF_Clone
};

#endif	// __VSOF_H
