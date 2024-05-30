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
// Copyright (C) 1999-97 Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   icp_serv.h
//
//  PURPOSE:  Sample ICP server type definitions.
//

#ifndef _ICP_SERVER_H_
#define _ICP_SERVER_H_

#ifndef NTLMSSP_MESSAGE_SIGNATURE_SIZE
#include <sspi.h>
#endif

#ifndef SICILY_PROTOCOL_VERSION_NUMBER
#define SICILY_PROTOCOL_VERSION_NUMBER  1
#endif

#ifndef SEALED_MSG_WRAPPER_SIZE
#define SEALED_MSG_WRAPPER_SIZE 0
#endif

#define MAX_CLIENT_BUF_LEN    1024      // Max. length of client message buffer
#define MAX_SESSION_KEY_LEN    128      // Max. length of session key
#define MAX_CLIENT_NAME_LEN    128      // Max. length of client name

//
//  Names of security DLL
//
#define SSP_NT_DLL          "security.dll"
#define SSP_WIN95_DLL       "secur32.dll"
#define SSP_SSPS_DLL        "msapssps.dll"

#define SSP_DLL_NAME_SIZE   16          // max. length of security DLL names


#define MAX_RESPONSE_BUFFER_SIZE 1024


//
// Types of blobs to send to the SSPI package 
//  based on the type of authentication we are using.
//
typedef enum _SSPI_BLOB_TYPE {
  GENERIC_BLOB,
  SIMPLE_BLOB_TWO_BUFFERS,
  COMPLEX_KNOWN_BLOB_1
} SSPI_INPUT_BLOB_TYPE;

//
// Types of socket IO between the server and the client
//
typedef enum _SRV_IO_TYPE {
    ServerRead,
    ServerWrite,
} SRV_IO_TYPE;


//
// This structure is used to specify which virtual server instance 
//  to use for authentication.
//
typedef struct _UCSTRUCT_{
    UNICODE_STRING  ucszVServer;
    WCHAR           szwVirtualServerID[64];
} VSERVER_SPEC_STRUC, *PVSERVER_SPEC_STRUC;


//
// Need a different overlapped struct in order to locate our read/write
// buffer when IO completes
//
typedef struct _BUFFER_INFO {
    PCHAR           pBuffer;            // Buffer for socket read or write
    SRV_IO_TYPE     type;               // The kind of IO performed in pBuffer
} BUFFER_INFO, *PBUFFER_INFO;

typedef struct  _CLIENT_OVERLAPPED_ {
    OVERLAPPED      Ovlp;
    BUFFER_INFO     bufInfo;        // The info. structure containing pointer 
                                    // to the buffer for the socket IO
} CLIENT_OVERLAPPED, *PCLIENT_OVERLAPPED;

//
// All important information related to client connected via Socket.
//
typedef struct _SENT_OVLP_LIST {
    PCLIENT_OVERLAPPED      pSendOvlp;// Points overlapped IO buffer for send
    struct _SENT_OVLP_LIST  *next;    // Points to next IO buffer of this client
} ListSentOvlp, *PListSentOvlp;

typedef struct _CLIENT_INFO {
    SOCKET          Socket;         // Socket connection to this client
    CLIENT_STATE    state;          // State of the connection
    CtxtHandle      hContext;       // Client's security context
    struct in_addr  client_addr;    // Client's IP address
    
    PCLIENT_OVERLAPPED pRecvOvlp;   // Points to the overlapped IO buffer
                                    //   for receiving messages from this client
    PListSentOvlp   pListOutOvlp;   // Points to a list of overlapped IO 
                                    //   buffers sent to this client.
    struct _CLIENT_INFO *next;      // point to the next client in list 
} CLIENT_INFO, *PCLIENT_INFO;

//
// Client/server message format definition
//
typedef struct _SAMPLE_MESSAGE {
    MSG_HDR hdr;            // Info on the message data in buffer.
    CHAR    buffer[1];      // The beginning of message data; the actual
                            // length of this data is in data_length of MSG_HDR
} SAMPLE_MSG, *PSAMPLE_MSG;



//
// Sample server's function prototypes 
//

BOOLEAN
InitServer (
    VOID
    );

SOCKET
InitializeSocketIO (
    PHANDLE phCompletionPort
    );

PCLIENT_INFO
CreateNewClientInfo (
    VOID
    );

PCLIENT_OVERLAPPED
CreateIOBuffer (
    DWORD dwBufLen
    );

VOID
FreeAllIOBuffers (
    PCLIENT_INFO pClient
    );

VOID
DeleteClientOutOvlp (
    PCLIENT_INFO pClientInfo, 
    PCLIENT_OVERLAPPED pOutOvlp
    );

VOID
WaitClientConnection (
    SOCKET sListener, 
    HANDLE hCompletionPort
    );

VOID
CloseClient (
    PCLIENT_INFO pInfo,
    BOOLEAN bGraceful
    );

VOID
ShowUsage (
    VOID
    );

VOID
ParseUserOption (
    int argc,
    char *argv[]
    );

PSAMPLE_MSG
UnsealClientMsg (
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG pSInMsg
    );

ULONG
SealOutputMsg (
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG pOutMsg, 
    PCLIENT_OVERLAPPED pOutOvlp
    );

#endif
