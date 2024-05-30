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
//  MODULE:   proc_msg.c
//
//  PURPOSE:  This file contains all client message processing, including
//            authentication messages.
//

#include "all_incl.h"

extern BOOLEAN g_bVerbose;
extern CredHandle g_hCredential;
extern PCLIENT_INFO g_pListClients;
extern PSecurityFunctionTable g_pFuncTbl;
extern CRITICAL_SECTION    g_ContextSection;
extern VSERVER_SPEC_STRUC g_ucVserverID;

extern char *g_szVirtualServerName;          // Name of the Site Server Virtual Server.
extern SSPI_INPUT_BLOB_TYPE g_eAuthBlobType; // BLOB type passed to SSPI.



BOOLEAN
SendAuthResponse (
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG  pInMsg
    );

BOOLEAN
SendMessageToClient (
    PCLIENT_INFO pClientInfo, 
    PMSG_HDR pOutMsg, 
    BOOLEAN bEncrypt
    );

BOOLEAN
AuthenticateUsingBasic(
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG  pInMsg
    );


//+----------------------------------------------------------------------------
//
//  Function:   GetNextClientMsg
//
//  Synopsis:   This function looks for a complete client message starting
//              at the beginning of the IO buffer (pointed to by pBuffer).
//              If it finds a complete message, it returns the complete message
//              to the caller function via the pNextMsg pointer, updates 
//              the number of bytes left in pBuffer (which is pdwBytesRemain), 
//              and returns the address of the remaining IO buffer to be read 
//              back to the caller function.  If this function does not find 
//              a complete client message, it will start a read on the socket
//              (stored in the client's info. structure) to finish reading the 
//              incompleted message.  And if there's no more message left in 
//              the IO buffer, it will start a read on the socket to receive 
//              the next client message.
//
//  Arguments:  pBuffer - Points to the IO buffer containing client messages.
//              pdwBytesRemain - Points to the number of bytes left in pBuffer.
//              pNextMsg - Output only. This is the pointer to the address of 
//                         the next client message to be returned to the caller.
//              pClientInfo - points to the client's info. structure
//              pClientOvlp - points to the client overlapped IO buffer for read
//
//  Returns:    The address of the remaining IO buffer so the caller can use
//              that address to get the next client message.  This function 
//              will return NULL if there's no more complete message left in 
//              the IO buffer (pBuffer).
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
PCHAR
GetNextClientMsg (
    PCHAR pBuffer, 
    DWORD *pdwBytesRemain, 
    PSAMPLE_MSG  *pNextMsg,        // pointer to pointer
    PCLIENT_INFO pClientInfo, 
    PCLIENT_OVERLAPPED pClientOvlp
    )
{
    DWORD ii;
    PSAMPLE_MSG pMsg;
    PCHAR pNewBuffer;
    DWORD dwBytesRead;
    BOOLEAN bSuccess;
    static CHAR  InMsg[512];

    //
    // Check if there's any complete message left in pBuffer
    //
    if (*pdwBytesRemain >= sizeof (MSG_HDR))
    {
        pMsg = (PSAMPLE_MSG) pBuffer;

        //
        // Check if the client message is received in its entirety
        //
        if (*pdwBytesRemain >= (pMsg->hdr.data_length + sizeof (MSG_HDR)))
        {
            //
            // Return this completed client message back to the caller
            //
            // If message in pBuffer does not start on long word bondary
            // copy it to a static buffer to void alignment problem
            //
            if (((long)pBuffer) % sizeof(long))
            {
                RtlCopyMemory (InMsg, pBuffer, 
                               sizeof (MSG_HDR) + pMsg->hdr.data_length);
                *pNextMsg = (PSAMPLE_MSG) InMsg;
            }
            else
            {
                *pNextMsg = (PSAMPLE_MSG) pBuffer;
            }

            pBuffer += sizeof (MSG_HDR) + pMsg->hdr.data_length;

            *pdwBytesRemain -= (sizeof (MSG_HDR) + pMsg->hdr.data_length);

            return (pBuffer);
        }
    }

    //
    // This means either there's no more message left in pBuffer or 
    // that pBuffer contains only a partial client message.
    // So it's time to post another read on the socket.
    //
    // We can pretty much use the same buffer since the first read issued on a 
    // socket already allocated its own buffer; so all subsequent reads can
    // basically use that same buffer.  We just have to be careful in handling
    // buffer containing partial message.
    // 

    pMsg = NULL;

    pNewBuffer = pClientOvlp->bufInfo.pBuffer;

    //
    // If there's partial message left in pBuffer, we need to check whether
    // this partial message is already at the beginning of the current buffer.
    // If not, we need to move it up.
    //
    if (*pdwBytesRemain > 0)
    {
        //
        // If the partial message is not the first message in current buffer,
        // copy it to the beginning of the current buffer.  In order to make 
        // sure they are copied correctly for this case, we won't call
        // CopyMemory (pNewBuffer, pBuffer, *pdwBytesRemain);
        //
        if (pBuffer != pNewBuffer)
        {
            for (ii = 0; ii < *pdwBytesRemain; ii++)
            {
                pNewBuffer[ii] = pBuffer[ii];
            }
        }
        pNewBuffer += *pdwBytesRemain;
    }

    //
    // Start an overlapped read on the socket.  This read will
    // complete in one of the worker threads, which will continue
    // processing of the client.
    //
    bSuccess = ReadFile ((HANDLE)pClientInfo->Socket, 
                pNewBuffer, MAX_CLIENT_BUF_LEN - *pdwBytesRemain,
                &dwBytesRead, (LPOVERLAPPED) pClientOvlp);
    //
    // If failed to issue another read on the socket, close connection and
    // remove client
    //
    if (!bSuccess && GetLastError () != ERROR_IO_PENDING)
    {
        printf ("ICPSERV: ReadFile Failed on %d [%d]\n",
                    pClientInfo->Socket, GetLastError ());

        CloseClient (pClientInfo, FALSE);
        FreeClientInfo (pClientInfo);
    }

    return (NULL);
}




//-----------------------------------------------------------------------------
// Function HandleClientFileRequest.  This function is called from 
//  HandleClientRequest to specifically handle the GET_FILE_MSG.
//
//  Parameters:
//        pClientInfo:  A pointer to a client info structure.
//        pInMsg:       A pointer to the message structure containing the 
//                      client request information.
//        pBuffer:      A pointer to a fixed size buffer that will receive
//                      data if a return message is to be sent from the calling
//                      function.
//
//  History:    Dave Crocco Created                             12/10/97
//
//-----------------------------------------------------------------------------
VOID HandleClientFileRequest(
                       PCLIENT_INFO    pClientInfo, 
                       PSAMPLE_MSG     pInMsg,
                       PSAMPLE_MSG     pOutMsg
                      ){

  HANDLE *hFile;

  if (g_bVerbose)
  {
      printf ( 
              "Accessing file: %s\n",
              pInMsg->buffer
             );
  }

  // Impersonate the user context.
  (*(g_pFuncTbl->ImpersonateSecurityContext))(&pClientInfo->hContext);


  
  // Attempt to access the file.
  hFile = CreateFile(pInMsg->buffer,
                     GENERIC_READ,
                     FILE_SHARE_READ,
                     NULL,
                     OPEN_EXISTING,
                     0,
                     NULL
                    );
  if(hFile != INVALID_HANDLE_VALUE){
    pOutMsg->hdr.msg_type = FILE_ACCESS_GRANTED;
    (void)sprintf( 
                   pOutMsg->buffer, 
                   "You have access to file: %s\n",
                   pInMsg->buffer
                 );
    if (g_bVerbose){
      printf( "Access to the requested file was granted.\n" );
    }//endif
  }else{
    if (g_bVerbose)  printf("CreateFile(%s) failed: %ld\n", pInMsg->buffer, GetLastError());
    pOutMsg->hdr.msg_type = FILE_ACCESS_DENIED;
    (void)sprintf( 
                   pOutMsg->buffer, 
                   "You do not have access to file: %s\n",
                   pInMsg->buffer
                 );
      if (g_bVerbose){
        printf( "Access to the requested file was denied.\n" );
      }//endif
  }//endif

  // Close the file.
  CloseHandle(hFile);

  // End impersonation of the user context.
  (*(g_pFuncTbl->RevertSecurityContext))(&pClientInfo->hContext);

  pOutMsg->hdr.data_length = strlen (pOutMsg->buffer);
  if (!SendMessageToClient (pClientInfo, (PMSG_HDR) pOutMsg, 
                            FALSE)){
      printf ( 
          "ICPSERV: Send Message Failed, sock %d, msg= \"%s\"\n",
          pClientInfo->Socket, pOutMsg->buffer);
  }//endif

} // end HandleClientFileRequest


//-----------------------------------------------------------------------------
// Function HandleClientHello.  This function is called from 
//  HandleClientRequest to specifically handle the MY_HELLO_MESSAGE. 
//
//  Parameters:
//        pClientInfo:  A pointer to a client info structure.
//        pInMsg:       A pointer to the message structure containing the 
//                      client request information.
//        pBuffer:      A pointer to a fixed size buffer that will receive
//                      data if a return message is to be sent from the calling
//                      function.
//
//  History:    Dave Crocco Created                             12/10/97
//
//-----------------------------------------------------------------------------
VOID HandleClientHello(
                       PCLIENT_INFO    pClientInfo, 
                       PSAMPLE_MSG     pInMsg,
                       PSAMPLE_MSG     pOutMsg
                      ){

  SECURITY_STATUS SecStatus;
  SecPkgContext_Names     pkgName;

  //
  // If the client sent a string with the hello, we'll print it on the screen.
  //
  if (pInMsg->hdr.data_length > 0){
      printf ( "\n<socket %d>\t\"%.*s\"\n\n",
          pClientInfo->Socket, pInMsg->hdr.data_length, 
          pInMsg->buffer);
  }//endif

  SecStatus = (*(g_pFuncTbl->QueryContextAttributes)) (&pClientInfo->hContext, 
                                      SECPKG_ATTR_NAMES, &pkgName);
  if (!SSPI_SUCCESS(SecStatus)){
      (void)sprintf (pOutMsg->buffer, 
              "Hello Client! Sorry Cannot Query Account ID [0x%08x]\n",
              SecStatus);
      return;
  }//endif

  //
  //  Build ordinary Hello response.
  //
  pOutMsg->hdr.msg_type = MY_HELLO_MSG;
  (void)sprintf (pOutMsg->buffer, "Hello Client %s! <IP %s>", pkgName.sUserName, 
              inet_ntoa (pClientInfo->client_addr));
  (*(g_pFuncTbl->FreeContextBuffer)) (pkgName.sUserName);
  pOutMsg->hdr.data_length = strlen (pOutMsg->buffer);

  //
  //  Send the message to the client.
  //
  if (!SendMessageToClient (pClientInfo, 
                            (PMSG_HDR) pOutMsg, 
                            FALSE
                           )
     ){
    printf ( 
            "ICPSERV: Send Message Failed, sock %d, msg= \"%s\"\n",
            pClientInfo->Socket, pOutMsg->buffer
           );
  }//endif

  // Thats all we do for a client hello.

} // end HandleClientHello

//-----------------------------------------------------------------------------
// Function HandleBadRequest.  This function is called from 
//  HandleClientRequest to specifically handle the case where the request
//  type was not recognized. 
//
//  Parameters:
//        pClientInfo:  A pointer to a client info structure.
//        pInMsg:       A pointer to the message structure containing the 
//                      client request information.
//        pBuffer:      A pointer to a fixed size buffer that will receive
//                      data if a return message is to be sent from the calling
//                      function.
//
//  History:    Dave Crocco Created                             12/10/97
//
//-----------------------------------------------------------------------------
VOID HandleBadRequest(
                      PCLIENT_INFO    pClientInfo, 
                      PSAMPLE_MSG     pInMsg,
                      PSAMPLE_MSG     pOutMsg
                     ){


  printf ( "ICPSERV: Invalid Message Type %d\n", pInMsg->hdr.msg_type);

  (void)sprintf (pOutMsg->buffer, "Hey Client... What!  Invalid Request Type or Format!");
  pOutMsg->hdr.msg_type = INVALID_REQUEST;
  pOutMsg->hdr.data_length = strlen (pOutMsg->buffer);

  //
  //  Send the message to the client.
  //
  if (!SendMessageToClient (pClientInfo, 
                            (PMSG_HDR) pOutMsg, 
                            FALSE
                           )
     ){
    printf ( 
            "ICPSERV: Send Message Failed, sock %d, msg= \"%s\"\n",
            pClientInfo->Socket, pOutMsg->buffer
           );
  }//endif

  // Thats all we do for a client hello.

} // end HandleBadRequest


//-----------------------------------------------------------------------------
// Function HandleClientRequest.  This function handles the supplied client
//  request message.
// 
//  Parameters:
//        pClientInfo:  A pointer to a client info structure.
//        pInMsg:       A pointer to the message structure containing the 
//                      client request information.
//        pBuffer:      A pointer to a fixed size buffer that will receive
//                      data if a return message is to be sent from the calling
//                      function.
//
//  History:    Dave Crocco Created                             12/10/97
//
//-----------------------------------------------------------------------------
VOID
HandleClientRequest (
                     PCLIENT_INFO    pClientInfo, 
                     PSAMPLE_MSG     pInMsg,
                     PSAMPLE_MSG     pOutMsg
                    ){

    //
    // For sample server, only the MY_HELLO_MSG is supported
    //
    switch (pInMsg->hdr.msg_type)
    {
    case MY_HELLO_MSG:
      HandleClientHello(
                        pClientInfo, 
                        pInMsg,
                        pOutMsg
                       );
      break;
    case GET_FILE_MSG:
      HandleClientFileRequest(
                              pClientInfo, 
                              pInMsg,
                              pOutMsg
                             );
      break;

    default:
      HandleBadRequest(
                       pClientInfo, 
                       pInMsg,
                       pOutMsg
                      );
      return;
    }

} // end HandleClientRequest


//+----------------------------------------------------------------------------
//
//  Function:   ProcessClientMsg
//
//  Synopsis:   This function processes the client message received from the 
//              socket.  Once a client is authenticated, every message 
//              received from the client determines whether the response sent 
//              for that message is encrypted.  That means if a message 
//              received is not encrypted, the response for that message will 
//              not be encrypted.  Otherwise, the response is encrypted.
//              
//
//  Arguments:  pClientInfo - Points to client's information structure 
//              dwTotalBytesRead - Number of bytes received in the IO buffer
//              pClientOvlp - Points to client's overlapped IO buffer.
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//              Dave Crocco Modified                            12/10/97
//
//-----------------------------------------------------------------------------
VOID
ProcessClientMsg (
    PCLIENT_INFO pClientInfo, 
    DWORD dwTotalBytesRead, 
    PCLIENT_OVERLAPPED pClientOvlp
    )
{
    PSAMPLE_MSG   pInMsg;
    PCHAR         pInBuf;
    struct _out_msg {
        MSG_HDR hdr;
        CHAR buffer[MAX_RESPONSE_BUFFER_SIZE];
    } OutMsg;
    DWORD       dwBytesRemain = dwTotalBytesRead;
    BOOLEAN     bEncryptMsg;

    if (g_bVerbose)
    {
        printf ( 
            "ICPSERV: <socket %d> Received total of %d bytes\n",
            pClientInfo->Socket, dwBytesRemain);
    }

    //
    // For now, this function assumes one message is received at a time
    // Unless the client is sending out a lot of messages in a short time, 
    // the server will pretty much get one message at a time. So theoretically, 
    // in the authentication phase, the server will only receive one message 
    // at a time.
    //

    pInBuf = pClientOvlp->bufInfo.pBuffer;

    //
    // For every complete client message queued in the IO buffer
    //
    while (pInBuf = GetNextClientMsg (pInBuf, &dwBytesRemain, &pInMsg,
                                    pClientInfo, pClientOvlp))
    {
        if (g_bVerbose)
        {
            printf ( 
                "ICPSERV: <socket %d> Received msg_type= %d, data_length= %d\n",
                pClientInfo->Socket, pInMsg->hdr.msg_type,
                pInMsg->hdr.data_length);
        }

        if (pClientInfo->state == in_Authentication)
        {
            //
            // Process client authentication request
            //
            switch (pInMsg->hdr.msg_type)
            {
            case NEGOTIATE_MSG:
                if (!SendAuthResponse (pClientInfo, pInMsg))
                {
                    printf ( 
                        "ICPSERV: Send Negotiate Message Failed on socket %d\n",
                        pClientInfo->Socket);
                }
                break;

            case AUTHENTICATE_MSG:
                if (SendAuthResponse (pClientInfo, pInMsg))
                {
                    //
                    // The client has been successfully authenticated, so
                    // change client state to start secured session.
                    //
                    pClientInfo->state = in_Session;
                }
                else
                {
                    printf ( 
                        "ICPSERV: Send Response Message Failed on socket %d\n",
                        pClientInfo->Socket);
                }
                break;

            case BASIC_AUTHENTICATE_MSG:
                if (AuthenticateUsingBasic(pClientInfo, pInMsg))
                {
                    //
                    // The client has been successfully authenticated, so
                    // change client state to start secured session.
                    //
                    pClientInfo->state = in_Session;
                }
                else
                {
                    printf ( "ICPSERV: Basic authentication failed.\n");
                }
                break;

            default:
                printf (
                    "ICPSERV: Unrecognized Authentication Message: %d\n",
                    pInMsg->hdr.msg_type);

                OutMsg.hdr.msg_type = ACCESS_DENIED;
                OutMsg.hdr.data_length = 0;

                if (!SendMessageToClient (pClientInfo, (PMSG_HDR) &OutMsg, 
                                            FALSE))
                {
                    printf ( 
                        "ICPSERV: Send Error Message Failed on socket %d\n",
                        pClientInfo->Socket);
                }
                break;

            }       // end switch pInMsg->hdr.msg_type

        }
        else if (pClientInfo->state == in_Session)
        {
            //
            // The message received was sealed and wrapped.
            // Need to unseal it first.
            // 
            if (pInMsg->hdr.msg_type == SICILY_SEALED_MSG)
            {
                bEncryptMsg = TRUE;
                if ((pInMsg = UnsealClientMsg (pClientInfo, pInMsg)) == NULL)
                {
                    printf ("ICPSERV: Message Decryption Failed\n");
                    continue;
                }
            }
            else
            {
                bEncryptMsg = FALSE;
            }

            if (g_bVerbose)
            {
                printf ( 
                    "                    ... msg_type= %d, data_length= %d\n",
                    pInMsg->hdr.msg_type, pInMsg->hdr.data_length);
            }

            //
            // Handle the client request.
            //
            HandleClientRequest (pClientInfo, pInMsg, (PSAMPLE_MSG)&OutMsg);

        }
        else
        {
            //
            // This should never happens! Otherwise, something terribly wrong 
            //
            printf ("ICPSERV: Bad Client State %d\n", (int)pClientInfo->state);
        }

    }       // end while GetNextClientMsg()

    //
    // NOTE: the next ReadFile on the client socket is started by 
    // GetNextClientMsg() when it reaches the end of the IO buffer.
    //
}

//+----------------------------------------------------------------------------
//
//  Function:   SendAuthResponse
//
//  Synopsis:   This function generates and sends an authentication response 
//              to the client.  It will generate and send either a challenge 
//              or the final authentication result to client depending on 
//              the type of client message (pointed to by pInMsg) passed 
//              to this function.
//
//  Arguments:  pClientInfo - Points to the client info. structure.
//              pInMsg - Points to the client authentication message received.
//
//  Returns:    TRUE if authentication response is both generated and sent 
//              successfully.  Otherwise, FALSE is returned.
//
//  History:    LucyC       Created                             14 July 1995
//              Dave Crocco Modified                            12/10/97
//
//-----------------------------------------------------------------------------
BOOLEAN
SendAuthResponse (
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG  pInMsg
    )
{
    PCtxtHandle    phContext;
    struct _out_auth_msg {
        MSG_HDR hdr;
        CHAR buffer[MAX_CLIENT_BUF_LEN];
    } OutMsg;
    SecBufferDesc inSecDesc, outSecDesc;
    SecBuffer     inSecBuffer[2], outSecBuffer;
    ULONG         fContextReq;
    ULONG         fAttribute;
    TimeStamp     tsExpireTime;
    SECURITY_STATUS status;
//    DWORD         next_msg_type;
    VSERVER_SPEC_STRUC ucVserverID;

    //
    // Check to make sure the client is using same SICILY SSPI version
    //
    if (pInMsg->hdr.version != SICILY_PROTOCOL_VERSION_NUMBER)
    {
        printf ("ICPSERV: Client Protocol Version Mismatch: sock %d\n",
                pClientInfo->Socket);
        //
        // Send failure response to the client
        // 
        OutMsg.hdr.msg_type = AUTH_ERROR;
        OutMsg.hdr.data_length = 0;

        return (SendMessageToClient (pClientInfo, (PMSG_HDR)&OutMsg, FALSE));
    }

    if (pInMsg->hdr.msg_type == NEGOTIATE_MSG)
        phContext = NULL;
    else
        phContext = &pClientInfo->hContext;

    //
    // Setup API's input security buffer(s) to pass the client's negotiate
    // message to the SSPI.
    //

    // Get a local copy of the global virtual server selection structure.
    ucVserverID = g_ucVserverID;

    // Description buffer.
    inSecDesc.ulVersion = SECBUFFER_VERSION;
    inSecDesc.cBuffers = 2;
    inSecDesc.pBuffers = inSecBuffer;

    // Information buffer(s).
    inSecBuffer[0].BufferType = SECBUFFER_TOKEN;
    inSecBuffer[0].cbBuffer = pInMsg->hdr.data_length;
    inSecBuffer[0].pvBuffer = pInMsg->buffer;
    inSecBuffer[1].cbBuffer   = sizeof(ucVserverID);
    inSecBuffer[1].BufferType = SECBUFFER_PKG_PARAMS;
    inSecBuffer[1].pvBuffer   = &ucVserverID;



    //
    // Setup API's output security buffer for receiving challenge message
    // from the SSPI.
    //
    outSecDesc.ulVersion = SECBUFFER_VERSION;
    outSecDesc.cBuffers = 1;
    outSecDesc.pBuffers = &outSecBuffer;

    outSecBuffer.cbBuffer = MAX_CLIENT_BUF_LEN;
    outSecBuffer.BufferType = SECBUFFER_TOKEN;
    outSecBuffer.pvBuffer = OutMsg.buffer;
    fContextReq = ASC_REQ_CONFIDENTIALITY | ASC_REQ_USE_SESSION_KEY | ASC_REQ_DELEGATE;


    status = 
      (*(g_pFuncTbl->AcceptSecurityContext)) (&g_hCredential, 
                                              phContext, 
                                              &inSecDesc,
                                              fContextReq,
                                              SECURITY_NATIVE_DREP, 
                                              &pClientInfo->hContext, 
                                              &outSecDesc, 
                                              &fAttribute, 
                                              &tsExpireTime
                                             );
    if (!SSPI_SUCCESS(status))
    {
        printf ( 
            "ICPSERV: Process Authenticate Request Failed [%d]: sock %d\n",
            status, pClientInfo->Socket);
        //
        // Send failure response to the client
        // 
        OutMsg.hdr.msg_type = ACCESS_DENIED;
        OutMsg.hdr.data_length = 0;
    }
    else
    {
        //
        // Build message header for sending challenge message to client
        //
        if (pInMsg->hdr.msg_type == NEGOTIATE_MSG)
        {
            OutMsg.hdr.msg_type = CHALLENGE_MSG;
            OutMsg.hdr.data_length = outSecBuffer.cbBuffer;
        }
        else
        {
            OutMsg.hdr.msg_type = ACCESS_GRANTED;
            OutMsg.hdr.data_length = 0;
        }
    }

    return (SendMessageToClient (pClientInfo, (PMSG_HDR)&OutMsg, FALSE));
}

//+----------------------------------------------------------------------------
//
//  Function:   DeleteClientOutOvlp
//
//  Synopsis:   This function removes the IO buffer from the client's outgoing
//              overlapped IO buffer list.
//
//  Arguments:  pClientInfo - pointe to client's info structure.
//              pOutOvlp - points to the overlapped IO buffer to be added
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
VOID
DeleteClientOutOvlp (
    PCLIENT_INFO pClientInfo, 
    PCLIENT_OVERLAPPED pOutOvlp
    )
{
    PListSentOvlp   pCurr, pLast;

    if (pClientInfo == NULL)
        return;

    EnterCriticalSection(&g_ContextSection);

    for (pCurr = pClientInfo->pListOutOvlp, pLast = NULL; 
        pCurr != NULL; pLast = pCurr, pCurr = pCurr->next)
    {
        if (pCurr->pSendOvlp == pOutOvlp)
        {
            if (pLast == NULL)
            {
                pClientInfo->pListOutOvlp = pCurr->next;
            }
            else
            {
                pLast->next = pCurr->next;
            }

            if (g_bVerbose)
            {
                printf (
        "ICPSERV: Deallocate Client <sock %d> Outbound IO Buffer 0x%x (0x%x)\n",
               pClientInfo->Socket, (ULONG)pCurr->pSendOvlp, (ULONG)pCurr);
            }

            FreeIOBuffer (pCurr->pSendOvlp);
            LocalFree (pCurr);
            break;
        }
    }

    //
    //  If connection has been closed and all IO have completed, delete client
    //
    if (!pClientInfo->pListOutOvlp && pClientInfo->state == connection_closed)
    {
        FreeClientInfo (pClientInfo);
    }

    LeaveCriticalSection(&g_ContextSection);
}

//+----------------------------------------------------------------------------
//
//  Function:   AddClientOutOvlp
//
//  Synopsis:   This function adds a given IO buffer to the client's outgoing
//              overlapped IO buffer list.  If LocalAlloc() failed to allocate 
//              memory for ListSentOvlp, the IO buffer will not be added. 
//              Consequently the IO buffer will not be deleted if (and only if)
//              the server exits before WriteFile() completes on this buffer.
//
//  Arguments:  pOutOvlp - points to the overlapped IO buffer to be added
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
VOID
AddClientOutOvlp (
    PCLIENT_INFO pClientInfo, 
    PCLIENT_OVERLAPPED pOutOvlp
    )
{
    PListSentOvlp   pNew;

    pNew = (PListSentOvlp) LocalAlloc (LMEM_ZEROINIT, sizeof (ListSentOvlp));
    if (pNew == NULL)
    {
        printf ("ICPSERV: Memory Allocation for ListSentOvlp Failed\n");
        return;
    }

    //
    // Add it to the beginning of the client's outgoing IO buffer list
    //
    pNew->pSendOvlp = pOutOvlp;

    EnterCriticalSection(&g_ContextSection);

    if (pClientInfo->pListOutOvlp == NULL)
    {
        pNew->next = NULL;
    }
    else
    {
        pNew->next = pClientInfo->pListOutOvlp;
    }
    pClientInfo->pListOutOvlp = pNew;

    if (g_bVerbose)
    {
        printf (
          "ICPSERV: <sock %d> Created pListSentOvlp 0x%08x, pOutOvlp 0x%08x\n",
          pClientInfo->Socket, pNew, pOutOvlp);
    }

    LeaveCriticalSection(&g_ContextSection);
}

//+----------------------------------------------------------------------------
//
//  Function:   SendMessageToClient
//
//  Synopsis:   This function packages the outgoing message and sends it out
//              to the client.  Packaging the message involves allocating an
//              overlapped IO buffer and copying message into the overlapped IO
//              buffer.  If the client has been authenticated, the message 
//              copied to the overlapped IO will be further encrypted by 
//              SealOutputMsg(); in this case, the message will not be 
//              sent if encryption failed for any reason.
//
//  Arguments:  pClientInfo - Points to client's information structure 
//              pOutMsg - Points to the un-encrypted outgoing message.
//              bEncrypt - Flag indicating whether to encrypt the outgoing
//                         message if the client has been authenticated.
//
//  Returns:    TRUE if message is packaged and sent successfully.  Otherwise,
//              FALSE is returned.
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
BOOLEAN
SendMessageToClient (
    PCLIENT_INFO pClientInfo, 
    PMSG_HDR pOutMsg, 
    BOOLEAN bEncrypt
    )
{
    PCLIENT_OVERLAPPED pOutOvlp;
    BOOLEAN bSuccess;
    DWORD dwIoSize, dwWriteLength, dwErr;

    pOutMsg->version = SICILY_PROTOCOL_VERSION_NUMBER;

    dwWriteLength = sizeof (MSG_HDR) + pOutMsg->data_length;
    if (pClientInfo->state == in_Session && bEncrypt)
    {
        //
        // We'll do encryption right in the overlapped IO buffer.
        // So allocate enough buffer space to store the encrypted message
        //
        dwWriteLength += SEALED_MSG_WRAPPER_SIZE;
    }

    //
    // Create new IO overlapped buffer for the message to be sent.
    //
    pOutOvlp = CreateIOBuffer (dwWriteLength);
    if (pOutOvlp == NULL)
    {
        printf ( 
            "ICPSERV: Overlapped Buffer Memory Allocation Failed: client %s\n",
            inet_ntoa (pClientInfo->client_addr));
        return (FALSE);
    }
    pOutOvlp->bufInfo.type = ServerWrite;

    //
    // Add to client's outgoing IO buffer list
    //
    AddClientOutOvlp (pClientInfo, pOutOvlp);

    if (pClientInfo->state == in_Session && bEncrypt)
    {
        //
        // Copy the outgoing message into the overlapped buffer and encrypt
        // t(he message.
        //
        if (!(dwWriteLength = SealOutputMsg (pClientInfo, (PSAMPLE_MSG) pOutMsg,
                    pOutOvlp)))
        {
            printf ( 
                "ICPSERV: Message Encryption Failed, msg_type %d length %d\n",
                pOutMsg->msg_type, pOutMsg->data_length);
            DeleteClientOutOvlp (pClientInfo, pOutOvlp);
            return (FALSE);
        }

        if (g_bVerbose)
        {
            pOutMsg = (PMSG_HDR) pOutOvlp->bufInfo.pBuffer;
            printf ("ICPSERV: <socket %d> Sending msg_type= %d, length= %d\n",
                    pClientInfo->Socket, pOutMsg->msg_type, 
                    dwWriteLength);
        }
    }
    else
    {
        //
        // Copy the message to be sent to the overlapped buffer
        //
        CopyMemory (pOutOvlp->bufInfo.pBuffer, pOutMsg, dwWriteLength);

        if (g_bVerbose)
            printf ("ICPSERV: <socket %d> Sending msg_type= %d, length= %d\n",
                    pClientInfo->Socket, pOutMsg->msg_type, 
                    dwWriteLength);
    }

    bSuccess = WriteFile ((HANDLE) pClientInfo->Socket, 
                pOutOvlp->bufInfo.pBuffer, dwWriteLength, 
                &dwIoSize, (OVERLAPPED *) pOutOvlp);

    if (!bSuccess & ((dwErr = GetLastError ()) != ERROR_IO_PENDING))
    {
        printf ("ICPSERV: WriteFile Failed on %d [%d]: type= %d length=%d\n",
                pClientInfo->Socket, GetLastError (), 
                pOutMsg->msg_type, dwWriteLength);
        DeleteClientOutOvlp (pClientInfo, pOutOvlp);
        return (FALSE);
    }

    return (TRUE);
}



//+----------------------------------------------------------------------------
//
//  Function:   AuthenticateUsingBasic
//
//  Synopsis:   This function performs a Basic authentication attempt for the
//              supplied user credentials.
//
//  Arguments:  pClientInfo - Points to client's information structure 
//              pInMsg - Points to the users 
//
//  Returns:    TRUE if message is packaged and sent successfully.  Otherwise,
//              FALSE is returned.
//
//  History:    Dave Crocco       Created  11/17/97
//
//-----------------------------------------------------------------------------
BOOLEAN
AuthenticateUsingBasic(
    PCLIENT_INFO pClientInfo, 
    PSAMPLE_MSG  pInMsg
    )
{
    TimeStamp       tsLifeTime;
    SECURITY_STATUS SecStatus;
    SecBuffer       SecBufferSrv[2];
    SecBufferDesc   SecDescSrv;
    ULONG           fContextAttrib;

    struct _out_auth_msg {
        MSG_HDR hdr;
        CHAR buffer[MAX_CLIENT_BUF_LEN];
    } OutMsg;

    VSERVER_SPEC_STRUC ucVserverID;

    CHAR szUserNamePassword[1024];

    // Get a local copy of the global virtual server selection structure.
    ucVserverID = g_ucVserverID;

    // Copy the username:password string.
    strcpy(szUserNamePassword, pInMsg->buffer);

    SecDescSrv.ulVersion    = 0;
    SecDescSrv.cBuffers     = 2;
    SecDescSrv.pBuffers     = SecBufferSrv;

    SecBufferSrv[0].cbBuffer   = strlen(szUserNamePassword) + 1;
    SecBufferSrv[0].BufferType = SECBUFFER_TOKEN;
    SecBufferSrv[0].pvBuffer   = szUserNamePassword;
    SecBufferSrv[1].cbBuffer   = sizeof(ucVserverID);
    SecBufferSrv[1].BufferType = SECBUFFER_PKG_PARAMS;
    SecBufferSrv[1].pvBuffer   = &ucVserverID;
    
    // Try to authenticate the user.
    SecStatus = (*(g_pFuncTbl->AcceptSecurityContext))(
                                                       &g_hCredential,
                                                       NULL, 
                                                       &SecDescSrv,
                                                       0,
                                                       SECURITY_NATIVE_DREP,
                                                       &pClientInfo->hContext,
                                                       NULL,
                                                       &fContextAttrib,
                                                       &tsLifeTime
                                                      );
    if (!SSPI_SUCCESS(SecStatus))
    {
      if (g_bVerbose){
        printf("ICPSERV: Basic Authenticate Request Failed [%d]: sock %d\n",
                SecStatus, pClientInfo->Socket
              );
      }//endif
      OutMsg.hdr.msg_type = ACCESS_DENIED;
      OutMsg.hdr.data_length = 0;
    } else {
      if (g_bVerbose){
        printf("ICPSERV: Basic Authenticate Request Succeeded\n");
      }//endif
      OutMsg.hdr.msg_type = ACCESS_GRANTED;
      OutMsg.hdr.data_length = 0;
    }//endif

    return (SendMessageToClient (pClientInfo, (PMSG_HDR)&OutMsg, FALSE));

} // end AuthenticateUsingBasic



