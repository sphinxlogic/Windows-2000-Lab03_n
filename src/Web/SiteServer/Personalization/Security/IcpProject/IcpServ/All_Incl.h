//====================================================================
//                                                                     
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//=====================================================================
//
// Copyright (C) 1996-97  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   all_incl.h
//
//  PURPOSE:  The precompiled headers file.
//

#ifndef _SICILY_SAMPLE_S_H_
#define _SICILY_SAMPLE_S_H_


//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//



#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#define SEC_E_OK                         ((HRESULT)0x00000000L)
#define SEC_E_NO_CREDENTIALS             ((HRESULT)0x8009030EL)

#include <sspi.h>

//  The following was copied from ntdef.h from the NT SDK.
//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
#else // MIDL_PASS
    PWSTR  Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
#define UNICODE_NULL ((WCHAR)0) // winnt

// end of copied from ntdef.h from NT SDK





//
// This structure is copied from ntlmsp.h
// Signature structure
//
typedef struct _NTLMSSP_MESSAGE_SIGNATURE {
    ULONG   Version;
    ULONG   RandomPad;
    ULONG   CheckSum;
    ULONG   Nonce;
} NTLMSSP_MESSAGE_SIGNATURE, * PNTLMSSP_MESSAGE_SIGNATURE;

#define NTLMSSP_MESSAGE_SIGNATURE_SIZE sizeof(NTLMSSP_MESSAGE_SIGNATURE)

//
// The commdef.h defines definitions which are common to the client and server
//
#include "..\include\commdef.h"
#include "icp_serv.h"

//
//  The following files are copied from NT SDK include ntsecapi.h & ntdef.h
//
typedef LONG NTSTATUS;
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

BOOLEAN
CreateThreadsForIoCompletion (
    HANDLE hCompletionPort
);

VOID
FreeClientInfo (
    PCLIENT_INFO pInfo
);

VOID
FreeIOBuffer (
    PCLIENT_OVERLAPPED pIOBuf
);

VOID
ProcessClientMsg (
    PCLIENT_INFO pClientInfo, 
    DWORD dwTotalBytesRead, 
    PCLIENT_OVERLAPPED pClientOvlp
);

#endif
