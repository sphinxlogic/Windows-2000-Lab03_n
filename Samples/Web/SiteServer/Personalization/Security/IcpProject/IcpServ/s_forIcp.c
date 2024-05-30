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
//  MODULE:   s_foricp.c
//
//  PURPOSE:  This file contains all client message processing, including
//            authentication messages.
//

#include "all_incl.h"

//+----------------------------------------------------------------------------
//
//  Function:   UnsealClientMsg
//
//  Synopsis:   This function decrypts the client message passed in the 
//              parameter.
//
//  Arguments:  pClientInfo - pointer to client information structure containing
//                            the client's security context handle
//              pSInMsg - pointer to the encrypted client message
//
//  Returns:    If message decryption is successful, this function returns the 
//              pointer to the decrypted message, which is the actual message.
//              Otherwise, NULL is returned.
//
//  History:    LucyC       Created                             23 July 1995
//
//-----------------------------------------------------------------------------
//
PSAMPLE_MSG
UnsealClientMsg (
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG pSInMsg
    )
{
    return (NULL);
}

//+----------------------------------------------------------------------------
//
//  Function:   SealOutputMsg
//
//  Synopsis:   This function encrypts an outgoing message.
//
//  Returns:    If the message is successfully encrypted, this function 
//              returns the total number of bytes to be sent to the client.
//              Otherwise, zero is returned.
//
//  History:    LucyC       Created                             24 July 1995
//
//-----------------------------------------------------------------------------
ULONG
SealOutputMsg (
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG pOutMsg, 
    PCLIENT_OVERLAPPED pOutOvlp
    )
{
    return (0);
}

