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
//  MODULE:   commdef.h
//
//  PURPOSE:  Common definitions for sample ICP server and client.
//

#ifndef _ICPSAMPLE_COMMON_H_
#define _ICPSAMPLE_COMMON_H_

#define SICILY_SERVER_PORT  12700

#define SSPI_SUCCESS(a)     NT_SUCCESS(a)

//
// Following message types are used during authentication process
//
#define NEGOTIATE_MSG           1
#define CHALLENGE_MSG           2
#define AUTHENTICATE_MSG        3
#define ACCESS_GRANTED          4
#define ACCESS_DENIED           5
#define AUTH_ERROR              6
#define BASIC_AUTHENTICATE_MSG  7

//
// Message types used after client has been authenticated
//
// BI-DIRECTIONAL
#define SICILY_SEALED_MSG   7 

// USER REQUESTS
#define MY_HELLO_MSG        8 
#define GET_FILE_MSG        9

// RESPONSES TO USER REQUESTS.
#define INVALID_REQUEST     10
#define FILE_ACCESS_GRANTED 11
#define FILE_ACCESS_DENIED  12


//
// The client has two states.  When it first connects up to the server, it is
// in in_Authentication state.  After server successfully authenticates the 
// client, it is changed to in_Session state.
//
typedef enum _CLIENT_STATE {
    in_Session,
    in_Authentication,
    connection_closed
} CLIENT_STATE, *PCLIENT_STATE;

//
// Client/server message header format definition
//
typedef struct _MESSAGE_HEADER {
    ULONG   version;                    // SSPI version used 
    ULONG   msg_type;                   // Type of client data in this message
    ULONG   data_length;                // Length of client data enclosed
} MSG_HDR, *PMSG_HDR;

#define MSG_HDR_SIZE    sizeof (MSG_HDR)

#endif
