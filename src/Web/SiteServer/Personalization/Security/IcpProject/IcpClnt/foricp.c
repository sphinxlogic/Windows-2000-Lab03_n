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
//  MODULE:   foricp.c
//
//  PURPOSE:    Sample ICP Client.  This module contains functions which 
//              are delivered to a real ICP as sample code.
//

#include "sampincl.h"

extern IN_ADDR g_RemoteIpAddress;
extern CHAR g_ClientName[];
extern CHAR g_ClientDomain[];
extern CHAR g_ClientPassword[];
extern BOOLEAN g_bDefaultUser;

//+----------------------------------------------------------------------------
//
//  Function:   ReceiveIcpMsg
//
//  Synopsis:   This function waits to receive a message from the socket 
//              connection.
//
//  Arguments:  sock - Socket to receive message from 
//              phContext - My security context handle
//              pRecvBuffer - Pointer to buffer for receiving message.
//              ulMaxBufSize - Max. size of the buffer pointed to by pRecvBuffer
//
//  Returns:    If message is received successfully, this 
//              function returns the pointer to the received message, 
//              which is the actual message.  Otherwise, NULL is returned.
//
//  History:    LucyC       Created                             24 July 1995
//
//-----------------------------------------------------------------------------
//
PCLIENT_MSG
ReceiveIcpMsg (
    SOCKET sock,
    PCtxtHandle phContext,
    PCLIENT_MSG pRecvBuffer,
    ULONG ulMaxBufSize
    )
{
    if (ReceiveMessage (sock, pRecvBuffer, ulMaxBufSize) < 0)
    {
        return (NULL);
    }

    return (pRecvBuffer);
}

//+----------------------------------------------------------------------------
//
//  Function:   SendIcpMsg
//
//  Synopsis:   This function sends the message over the socket connection
//
//  Arguments:  sock - Socket connection to which final message will be sent.
//              phContext - My security context handle.
//              pOutMsg - Points to the un-encrypted outgoing message.
//
//  Returns:    TRUE if the message is sent.  Otherwise, 
//              FALSE is returned.
//
//  History:    LucyC       Created                             24 July 1995
//
//-----------------------------------------------------------------------------
BOOLEAN
SendIcpMsg (
    SOCKET sock, 
    PCtxtHandle phContext, 
    PMSG_HDR pOutMsg
    )
{
    int           ulMsgSize = (int)MSG_HDR_SIZE + (int)pOutMsg->data_length;

    if (SendMsg (sock, (PMSG_HDR) pOutMsg, ulMsgSize) != ulMsgSize)
        return (FALSE);

    return (TRUE);
}
