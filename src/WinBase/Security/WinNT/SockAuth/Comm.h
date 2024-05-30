/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996 - 1999.  Microsoft Corporation.  All rights reserved.


Module Name:

    comm.h

Abstract:

    Some common functions for sockets

Revision History:

--*/

#if !defined (INC_COMM_H)
#define INC_COMM_H

BOOL InitWinsock ();
BOOL TermWinsock ();
BOOL SendMsg (SOCKET s, PBYTE pBuf, DWORD cbBuf);
BOOL ReceiveMsg (SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead);
BOOL SendBytes (SOCKET s, PBYTE pBuf, DWORD cbBuf);
BOOL ReceiveBytes (SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead);

#endif
