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
//  MODULE:   client.h
//
//  PURPOSE:    Definitions For Sample ICP Client
//

#ifndef _CLIENT_H_
#define _CLIENT_H_

//
//  Names of secruity DLL
//
#ifndef WIN16_BUILD
#define SSP_NT_DLL          "security.dll"
#define SSP_WIN95_DLL       "secur32.dll"
#define SSP_SSPC_DLL        "msapsspc.dll"
#else // WIN16_BUILD
#define SSP_SSPC_DLL        "msapsp16.dll"
#endif // WIN16_BUILD

#define SSP_DLL_NAME_SIZE   16          // max. length of security DLL names


#define SICILY_PROTOCOL_VERSION_NUMBER  1

#define ICPERROR    (-1)
#define ICPOK       0
#define ICPAUTHFAIL 1

#define MAX_BUFFER_SIZE  512

#define HELLO_SERVER    (char *)"Hello Server\0"

typedef struct client_msg {

    MSG_HDR hdr;
    CHAR buffer[MAX_BUFFER_SIZE];
} CLIENT_MSG, *PCLIENT_MSG;


SOCKET
ConnectToServer (
    VOID
    );

INT
SendMsg (
    SOCKET sock,
    PMSG_HDR pOutMsg,
    DWORD dwSize
    );

INT 
ReceiveMessage (
    SOCKET sock,
    PCLIENT_MSG pMsg,
    ULONG MaxBufferSize
    );

INT
ReceiveBuffer (
    SOCKET sock, 
    PCHAR pReceiveBuffer, 
    ULONG ExpectedSize
    );

BOOLEAN
GenerateAuthMsg (
    SOCKET sIcpServer, 
    PCredHandle phCredential,
    PCtxtHandle phMyContext,
    PCLIENT_MSG pInMsg,
    ULONG       fContextReq
    );

int
AuthenticateClient (
    SOCKET sIcpServer, 
    PCredHandle phCredential, 
    PCtxtHandle phContext,
    ULONG       fReq
    );

PCLIENT_MSG
ReceiveIcpMsg (
    SOCKET sock,
    PCtxtHandle phContext,
    PCLIENT_MSG pRecvBuffer,
    ULONG ulMaxBufSize
    );

BOOLEAN
SendIcpMsg (
    SOCKET sock, 
    PCtxtHandle phContext, 
    PMSG_HDR pOutMsg
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

#endif
