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
//  MODULE:   client.c
//
//  PURPOSE:    Sample ICP Client.  This client will connect itself to
//              the ICP server and go through authentication process with
//              the server.  After successful authentication, it will 
//              send a message to the server to request reply from server.
//              The server will reply with a ascii string which the client
//              will print to the screen.
//
//


#include "sampincl.h"
 
BOOLEAN g_bVerbose = FALSE;
BOOLEAN g_bEncrypt = TRUE;
#ifndef WIN16_BUILD
BOOLEAN g_bLoadDirect = FALSE;      // By default, load through security DLL
#else // WIN16_BUILD
BOOLEAN g_bLoadDirect = TRUE;      // By default, load through MSAPSP16.DLL
#endif // WIN16_BUILD
IN_ADDR g_RemoteIpAddress;
DWORD g_dwDelay = 0;
DWORD g_dwIterations = 1;
ULONG g_uActionCode = MY_HELLO_MSG;

BOOLEAN g_bDefaultUser = TRUE;
CHAR g_ClientName[80];
CHAR g_ClientDomain[80];
CHAR g_ClientPassword[80];
CHAR g_szPkgName[40];
CHAR g_szFileToAccess[512];

ULONG g_AclMsgType = 0;
LONG  g_Token = 0;
LONG  g_Ar4Token = 0;

PSecurityFunctionTable	g_pFuncTbl = NULL;

#ifdef WIN16_BUILD
char g_szDbgString[1024];
#define OUTPUTMSG0(a) wsprintf(g_szDbgString,a)
#define OUTPUTMSG1(a,b) wsprintf(g_szDbgString,a,b)
#define OUTPUTMSG2(a,b,c) wsprintf(g_szDbgString,a,b,c)
#define OUTPUTMSG3(a,b,c,d) wsprintf(g_szDbgString,a,b,c,d)
#define OUTPUTMSG() OutputDebugString(g_szDbgString);
#define OUTPUTMSGUSER() MessageBox(NULL,g_szDbgString,"Result",MB_OK);
DWORD GetLastError(){ return 0;}
#else
#define OUTPUTMSG0(a) printf(a)
#define OUTPUTMSG1(a,b) printf(a,b)
#define OUTPUTMSG2(a,b,c) printf(a,b,c)
#define OUTPUTMSG3(a,b,c,d) printf(a,b,c,d)
#define OUTPUTMSG()
#define OUTPUTMSGUSER() 
#endif

void InitClient (
    int argc,
    char *argv[],
    PCredHandle phCredential
);

//+----------------------------------------------------------------------------
//
//  Function:   main
//
//  Synopsis:   This is the main program of the sample client.
//
//  History:    LucyC       Created                             18 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
int 
#ifndef WIN16_BUILD
_CRTAPI1
#endif // WIN16_BUILD
main (
    int argc,
    char *argv[],
    char *envp[]
    )
{
    CredHandle hCredential;
    CtxtHandle hContext;
    CLIENT_MSG OutMsg;
    CLIENT_MSG MyMsg;
    PCLIENT_MSG pInMsg;
//    INT BytesSent;
    SOCKET sIcpServer;       // socket handle of our connection to ICP server
    BOOLEAN bSuccess;
//    ULONG ulBytesSent;
    ULONG ii;
    ULONG fReq = 0;
    int   ret;
    BOOL  bFirst = TRUE;

    //
    // Initializes the client 
    //
    InitClient (argc, argv, &hCredential);

    do
    {
        //
        // Get a socket connection to the ICP server
        //
        if ((sIcpServer = ConnectToServer ()) == INVALID_SOCKET)
        {
            exit (1);
        }

        //
        // Get ourself, the client, authenticated by the ICP server
        //
        ret = AuthenticateClient (sIcpServer, &hCredential, &hContext, fReq);

        //
        //  As long as authentication did not succeed, close the connection
        //
        if (ret != ICPOK)
            closesocket (sIcpServer);

        //
        //  If authentication failed, re-prompt the user for credential
        //
        if (ret == ICPAUTHFAIL)
            fReq = ISC_REQ_PROMPT_FOR_CREDS;
    }
    while (ret == ICPAUTHFAIL);

    if (ret == ICPERROR)
    {
        (*(g_pFuncTbl->FreeCredentialHandle)) (&hCredential);
        exit (1);
    }

    //
    // Yeah! We've been authenticated (granted access) by the ICP server!!!
    //
    // Now we can start the real work - for this client, it is simply sending
    // a "hello" message to the server and waiting for the server to send a 
    // greeting message back.
    //
    for (ii = 0; ii < g_dwIterations; ii++)
    {
#ifdef WIN16_BUILD
        _fmemset (&OutMsg, 0,sizeof (OutMsg));
#else // WIN16_BUILD
        ZeroMemory (&OutMsg,sizeof (OutMsg));
#endif // WIN16_BUILD

        // Initialize the message based on the action code.
        if (g_uActionCode == MY_HELLO_MSG){ 
          strcpy (OutMsg.buffer, HELLO_SERVER);
          OutMsg.hdr.msg_type = MY_HELLO_MSG;
        }else{
          strcpy (OutMsg.buffer, g_szFileToAccess);
          OutMsg.hdr.msg_type = GET_FILE_MSG;
        }//endif
    
        OutMsg.hdr.version = SICILY_PROTOCOL_VERSION_NUMBER;
        OutMsg.hdr.data_length = strlen (OutMsg.buffer) + 1;

        bSuccess = SendIcpMsg (sIcpServer, &hContext, (PMSG_HDR) &OutMsg);
        if (!bSuccess)
        {
            (void)OUTPUTMSG1("ICPClient: Send Msg Failed: error = %d\n",GetLastError ());
            OUTPUTMSG();
            (*(g_pFuncTbl->DeleteSecurityContext)) (&hContext);
            (*(g_pFuncTbl->FreeCredentialHandle)) (&hCredential);
            closesocket (sIcpServer);
            exit (1);
        }

        pInMsg = ReceiveIcpMsg (sIcpServer, &hContext, &MyMsg, 
                    sizeof (MyMsg));
        if (pInMsg == NULL)
        {
            (void)OUTPUTMSG0( 
                "ICPClient: Attempt To Receive Response From Server Failed\n");
            OUTPUTMSG();
            (*(g_pFuncTbl->DeleteSecurityContext)) (&hContext);
            (*(g_pFuncTbl->FreeCredentialHandle)) (&hCredential);
            closesocket (sIcpServer);
            exit (1);
        }
    
        switch(pInMsg->hdr.msg_type){
        case MY_HELLO_MSG:
            (void)OUTPUTMSG1("HELLO MESSAGE RECEIVED\n\nSERVER MESSAGE:%s\n", MyMsg.buffer);
            OUTPUTMSG();
          break;
        case FILE_ACCESS_GRANTED:
            (void)OUTPUTMSG1("FILE ACCESS GRANTED MESSAGE RECEIVED\n\nSERVER MESSAGE:%s\n", MyMsg.buffer);
            OUTPUTMSG();
            break;

        case FILE_ACCESS_DENIED:
            (void)OUTPUTMSG1("FILE ACCESS DENIED MESSAGE RECEIVED\n\nSERVER MESSAGE:%s\n", MyMsg.buffer);
            OUTPUTMSG();
            break;
        default:
            if (pInMsg->hdr.data_length > 0){
              pInMsg->buffer[pInMsg->hdr.data_length] = (CHAR) NULL;
              (void)OUTPUTMSG1 ("\n\nUnknown message type contained: %s\n\n", pInMsg->buffer);
	            if (g_bVerbose){
                OUTPUTMSGUSER();
	            }
              OUTPUTMSG();
            }//endif
            break;
        }//endswitch


#ifndef WIN16_BUILD
		//
		// Win16 version doesn't support sleeping
		//
        if (g_dwDelay > 0)
        {
            if (g_bVerbose){
                (void)OUTPUTMSG1 (
                        "\nICPClient: Sleep %lu After Each Send\n", g_dwDelay);
                OUTPUTMSG();
            }
            Sleep (g_dwDelay);
        }
#endif // WIN16_BUILD
    }

    (*(g_pFuncTbl->DeleteSecurityContext)) (&hContext);
    (*(g_pFuncTbl->FreeCredentialHandle)) (&hCredential);
    closesocket (sIcpServer);
    return 1;
}


//+----------------------------------------------------------------------------
//
//  Function:   ConnectToServer
//
//  Synopsis:   This function opens a socket connection to the ICP server.
//
//  Arguments:  void
//
//  Returns:    The handle of the socket connection to the ICP server.
//
//  History:    LucyC       Created                             18 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
SOCKET
ConnectToServer (
    VOID
    )
{
    SOCKET sock;
    SOCKADDR_IN remoteAddr;
    INT status;
    INT ReceiveBufferSize;
    INT SendBufferSize;

    //
    // Open a socket using the Internet Address family and TCP
    //
    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        (void)OUTPUTMSG1 ("ICPClient: Failed to Open Socket: %ld\n",
                    GetLastError ());
              OUTPUTMSG();
        return (INVALID_SOCKET);
    }

    //
    // Set the receive buffer size...
    //
    ReceiveBufferSize = MAX_BUFFER_SIZE + MSG_HDR_SIZE;
    status = setsockopt (sock, SOL_SOCKET, SO_RCVBUF, 
                (char *) &ReceiveBufferSize, sizeof (ReceiveBufferSize));
    if (status == SOCKET_ERROR)
    {
        (void)OUTPUTMSG1("ICPClient: setsockopt(SO_RCVBUF) Failed: %ld\n",
                    GetLastError ());
        OUTPUTMSG();
        closesocket (sock);
        return (INVALID_SOCKET);
    }

    //
    // Disable send buffering on the socket. Setting SO_SNDBUF to 0 causes 
    // winsock to stop buffering sends and perform sends directly from our
    // buffers, thereby reducing CPU usage.
    //
    SendBufferSize = 0;
    status = setsockopt (sock, SOL_SOCKET, SO_SNDBUF, (char *) &SendBufferSize,
                sizeof (SendBufferSize));
    if (status == SOCKET_ERROR)
    {
        (void)OUTPUTMSG1("ICPClient: setsockopt(SO_SNDBUF) Failed: %ld\n",
                    GetLastError ());
        OUTPUTMSG();
        closesocket (sock);
        return (INVALID_SOCKET);
    }

    //
    // Connect to an agreed upon port on the host.  See the
    // commdef.h file for the actual port number
    //
#ifdef WIN16_BUILD
    _fmemset (&remoteAddr, 0, sizeof (remoteAddr));
#else // WIN16_BUILD
     ZeroMemory (&remoteAddr,sizeof (remoteAddr));
#endif // WIN16_BUILD

    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons (SICILY_SERVER_PORT);
    remoteAddr.sin_addr = g_RemoteIpAddress;

    if (g_bVerbose)
    {
        (void)OUTPUTMSG1("ICPClient: Server host = 0x%x\n", 
            g_RemoteIpAddress.s_addr);
        OUTPUTMSG();
    }

    status = connect (sock, (PSOCKADDR) &remoteAddr, sizeof (remoteAddr));
    if (status == SOCKET_ERROR)
    {
        OUTPUTMSG1("DoEcho: connect failed: %ld\n", GetLastError ());
        OUTPUTMSG();
        closesocket (sock);
        return (INVALID_SOCKET);
    }

    return (sock);
}

//+----------------------------------------------------------------------------
//
//  Function:   SendMsg
//
//  Synopsis:   This function converts the message header to network byte order
//              and sends the message to the socket peer.
//
//  Arguments:  sock - the handle of the socket connection to send message to.
//              pOutMsg - pointer to the outgoing message.
//              dwSize - the size of the buffer to send.
//
//  Returns:    The number of bytes sent.  On error, it returns SOCKET_ERROR.
//
//  History:    LucyC       Created                             27 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
INT
SendMsg (
    SOCKET sock,
    PMSG_HDR pOutMsg,
    DWORD dwSize
    )
{
    return (send (sock, (CHAR *) pOutMsg, (INT)dwSize, 0));
}

//+----------------------------------------------------------------------------
//
//  Function:   ReceiveMessage
//
//  Synopsis:   This function call the ReceiveBuffer function to receive a full
//              message from server.  It first waits to receive the message
//              header from the server.  Then base on the message header, it 
//              decides whether there's data attached to this message.  If not,
//              it simply returns the message header back to the caller.
//              Otherwise, it will wait for the data portion of this message to 
//              arrive; then it returns the full message back to the caller.
//
//  Arguments:  sock - the socket handle to receive message from
//              pMsg - pointer to a buffer space to store the incoming message.
//              MaxBufferSize - maximum size of the buffer pointed to by pMsg.
//
//  Returns:    On success, the total number of bytes received is returned.
//              Otherwise, negative one is returned.
//
//  History:    LucyC       Created                             19 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
INT
ReceiveMessage (
    SOCKET sock,
    PCLIENT_MSG pMsg,
    ULONG MaxBufferSize
    )
{
    int bytesReceived;

    if (ReceiveBuffer (sock, (PCHAR) &pMsg->hdr, (ULONG) MSG_HDR_SIZE) < 0)
    {
        return (-1);
    }

    if (pMsg->hdr.data_length == 0)
    {
        if (g_bVerbose)
        {
            (void)OUTPUTMSG2("ICPClient: Received type= %d, length= %d\n",
                    pMsg->hdr.msg_type, MSG_HDR_SIZE);
            OUTPUTMSG();
        }
        return (MSG_HDR_SIZE);
    }

    MaxBufferSize -= MSG_HDR_SIZE;

    if (pMsg->hdr.data_length > MaxBufferSize)
    {
        (void)OUTPUTMSG1("ICPClient: Received a huge message, size %d\n",
            pMsg->hdr.data_length);
        OUTPUTMSG();
        return (-1);
    }

    if ((bytesReceived = ReceiveBuffer (sock, pMsg->buffer, 
                pMsg->hdr.data_length)) < 0)
    {
        return (-1);
    }

    if (g_bVerbose)
    {
        (void)OUTPUTMSG2("ICPClient: Received type = %d, length = %d\n",
                    pMsg->hdr.msg_type, MSG_HDR_SIZE + bytesReceived);
        OUTPUTMSG();
    }

    return (MSG_HDR_SIZE + bytesReceived);
}


//+----------------------------------------------------------------------------
//
//  Function:   ReceiveBuffer
//
//  Synopsis:   This function waits to receive buffer of the specified size  
//              on the specified socket. It calls recv() repeatedly until
//              the number of bytes expected are received. In order to avoid
//              eating up CPU from other process, this function forces this
//              process to sleep 1/10 sec every 1000th recv call.
//
//  Arguments:  sock - the socket handle to receive data from
//              pReceiveBuffer - pointer to buffer for store the incoming data.
//              ExpectedSize - no. of bytes to receive from the socket.
//
//  Returns:    On success, the total number of bytes received (which should 
//              always be the same as DataSize) is returned.
//              Otherwise, negative one is returned.  If socket connection has
//              been closed by the peer, zero is returned; then it is up to the
//              caller to clean up accordingly.
//
//  History:    LucyC       Created                             19 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
INT
ReceiveBuffer (
    SOCKET sock,
    PCHAR pReceiveBuffer,
    ULONG ExpectedSize
    )
{
    INT ret;
    INT bytesToRead = (INT)ExpectedSize;     // no. of bytes to read from socket.
    INT cnt = 0;

    do
    {
        //
        // Read as much as the remote host should echo
        //
        ret = recv (sock, pReceiveBuffer, bytesToRead, 0);
        if (ret == SOCKET_ERROR)
        {
            (void)OUTPUTMSG1("ICPClient: Socket Receive Failed: %d\n", 
                WSAGetLastError ());
            OUTPUTMSG();
            return (-1);
        }
        else if (ret == 0 && bytesToRead != 0)
        {
            (void)OUTPUTMSG0("ICPClient: Socket Closed Prematurely By Server.\n");
            OUTPUTMSG();
            return (-1);
        }
        bytesToRead -= ret;

        //
        // In case that we are waiting too long, we don't want to eat up CPU
        // So every 1000 reads, sleep 1/10 second
        //
        if (bytesToRead && cnt++ == 1000)
        {
#ifndef WIN16_BUILD
            SleepEx (100, FALSE);
#else // WIN16_BUILD
			Yield();
#endif // WIN16_BUILD
            cnt = 0;
        }
    }
    while (bytesToRead > 0);

    return ((INT)ExpectedSize);
}


//+----------------------------------------------------------------------------
//
//  Function:   GenerateAuthMsg
//
//  Synopsis:   This function calls InitializeSecurityContext to generate 
//              an authentication message and sends it to the ICP server.  
//              It generates different authentication messages depending on 
//              whether there's security token from the server to be used 
//              as input message or not (i.e. whether pInMsg is NULL).
//
//  Arguments:  phCredential - pointer to this client's credential handle.
//              phMyContext - pointer to this client's security context.
//              pInMsg - pointer to the server's authentication message '
//                       containing the security token.
//
//  Returns:    TRUE, if the authentication message is generated and sent 
//                    successfully.
//              FALSE, if any error prevented the authentication message to
//                     be generated or sent.
//
//  History:    LucyC       Created                             19 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
BOOLEAN
GenerateAuthMsg (
    SOCKET sIcpServer, 
    PCredHandle phCredential,
    PCtxtHandle phMyContext,
    PCLIENT_MSG pInMsg,
    ULONG       fContextReq
    )
{
    PCtxtHandle phCurrContext;
    CLIENT_MSG OutMsg;
    DWORD out_msg_type;
    SecBufferDesc inSecDesc, outSecDesc;
    SecBuffer     inSecBuffer, outSecBuffer;
    PSecBufferDesc pInSecDesc;
    ULONG     fContextAttrib;
    TimeStamp tsExpireTime;
    SECURITY_STATUS status;
    INT dwTransferSize;
    INT BytesSent;

    if (pInMsg == NULL)
    {
        //
        // This is the first time this GenerateAuthMsg() is called, so the
        // message generated will be a NEGOTIATE_MSG.
        //
        phCurrContext = NULL;
        out_msg_type = NEGOTIATE_MSG;
        pInSecDesc = NULL;
    }
    else
    {
        //
        // Since we have received a CHALLENGE_MSG from the server, we should
        // generate a AUTHENTICATE_MSG to send to server.
        //
        phCurrContext = phMyContext;
        out_msg_type = AUTHENTICATE_MSG;

        //
        // Setup API's input security buffer to pass the client's negotiate
        // message to the SSPI.
        //
        inSecDesc.ulVersion = 0;
        inSecDesc.cBuffers = 1;
        inSecDesc.pBuffers = &inSecBuffer;

        inSecBuffer.cbBuffer = pInMsg->hdr.data_length;
        inSecBuffer.BufferType = SECBUFFER_TOKEN;
        inSecBuffer.pvBuffer = pInMsg->buffer;

        pInSecDesc = &inSecDesc;
    }

    //
    // Setup API's output security buffer for receiving challenge message
    // from the SSPI.
    // Pass the client message buffer to SSPI via pvBuffer.
    //

    outSecDesc.ulVersion = 0;
    outSecDesc.cBuffers = 1;
    outSecDesc.pBuffers = &outSecBuffer;

    outSecBuffer.cbBuffer = MAX_BUFFER_SIZE;
    outSecBuffer.BufferType = SECBUFFER_TOKEN;
    outSecBuffer.pvBuffer = OutMsg.buffer;

    fContextReq |= ISC_REQ_CONFIDENTIALITY | ISC_REQ_USE_SESSION_KEY;
    //
    //  If user credential has been supplied, and if 'prompt user' flag has not 
    //  been set, tell SSPI to use the supplied credential
    //
    if ((fContextReq & ISC_REQ_PROMPT_FOR_CREDS) == 0 && !g_bDefaultUser)
            fContextReq |= ISC_REQ_USE_SUPPLIED_CREDS;

    //
    // Generate a negotiate/authenticate message to be sent to the server.
    //    
    status = (*(g_pFuncTbl->InitializeSecurityContext)) (
                                phCredential,       // phCredential
                                phCurrContext,      // phContext
                                NULL,               // pszTargetName
                                fContextReq,        // fContextReq
                                0L,                 // reserved1
                                SECURITY_NATIVE_DREP,   // TargetDataRep
                                pInSecDesc,         // pInput
                                0L,                 // reserved2
                                phMyContext,        // phNewContext
                                &outSecDesc,        // pOutput negotiate msg
                                &fContextAttrib,    // pfContextAttribute
                                &tsExpireTime);     // ptsLifeTime

    //
    //  If SSPI does not have user credential, and if we have not prompt 
    //  user for credential
    //
    if (status == SEC_E_NO_CREDENTIALS && 
        (fContextReq & (ISC_REQ_PROMPT_FOR_CREDS | 
                        ISC_REQ_USE_SUPPLIED_CREDS)) == 0)
           
    {
        fContextReq = ISC_REQ_CONFIDENTIALITY | ISC_REQ_USE_SESSION_KEY |  
                      ISC_REQ_PROMPT_FOR_CREDS;

        //
        //  Call SSPI again, but this time ask SSPI to prompt 
        //  for user credentials
        //
        status = (*(g_pFuncTbl->InitializeSecurityContext)) (
                                phCredential,       // phCredential
                                phCurrContext,      // phContext
                                NULL,               // pszTargetName
                                fContextReq,        // fContextReq
                                0L,                 // reserved1
                                SECURITY_NATIVE_DREP,   // TargetDataRep
                                pInSecDesc,         // pInput
                                0L,                 // reserved2
                                phMyContext,        // phNewContext
                                &outSecDesc,        // pOutput negotiate msg
                                &fContextAttrib,    // pfContextAttribute
                                &tsExpireTime);     // ptsLifeTime
        //
        //  NOTE: This time SSPI will not return SEC_E_NO_CREDENTIALS again 
        //  unless the user does not wish to supply any credential (i.e. user 
        //  hits CANCEL button on the UI box).  So if SSPI returns 
        //  SEC_E_NO_CREDENTIALS again, we definitely do not want to ask 
        //  SSPI to prompt for user credentials.
        //
    }

    if (!(status >= 0))
    {
        (void)OUTPUTMSG2("ICPClient: %s Message Generation Failed [0x%x]\n", 
            ((out_msg_type == NEGOTIATE_MSG) ? "Negotiate" : "Authenticate"),
            (unsigned long)status);
        OUTPUTMSG();
        return (FALSE);
    }

    dwTransferSize = (INT)MSG_HDR_SIZE + (INT)outSecBuffer.cbBuffer;

    OutMsg.hdr.version = SICILY_PROTOCOL_VERSION_NUMBER;
    OutMsg.hdr.msg_type = out_msg_type;
    OutMsg.hdr.data_length = outSecBuffer.cbBuffer;
    
    if (g_bVerbose)
    {
        (void)OUTPUTMSG2("ICPClient: Sending type = %d, length = %d\n",
                    OutMsg.hdr.msg_type, dwTransferSize);
        OUTPUTMSG();
    }

    //
    // Send negotiate message to the server
    //
    BytesSent = SendMsg (sIcpServer, (PMSG_HDR) &OutMsg, dwTransferSize);
                
    if (BytesSent != dwTransferSize)
    {
        (void)OUTPUTMSG3("ICPClient: Send %s Msg Failed: ret = %ld, error = %ld\n",
            ((out_msg_type == NEGOTIATE_MSG) ? "Negotiate" : "Authenticate"),
            BytesSent, GetLastError ());
        OUTPUTMSG();
        return (FALSE);
    }

    return (TRUE);
}

//+----------------------------------------------------------------------------
//
//  Function:   AuthenticateClient
//
//  Synopsis:   This function takes care of all the authentication process 
//              with the ICP server. The authentication process involves:
//
//                  1. Acquires a credential handle for the client
//                  2. Generate and send a negotiate message to the server.
//                  3. Wait for a challenge message from the server.
//                  4. Generate and send a authenticate message to the server.
//                  5. Wait for authentication response from the server.
//
//              This function does not return until either the entire 
//              authentication process is complete or the process is aborted 
//              due to errors.
//
//  Arguments:  sIcpServer - handle to the ICP server socket connection 
//              phContext - pointer to the client's security context.
//
//  Returns:    TRUE if client is successfully authenticated by the server.
//              FALSE if client authentication failed for any reason.
//
//  History:    LucyC       Created                             19 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
int
AuthenticateClient (
    SOCKET sIcpServer, 
    PCredHandle phCredential, 
    PCtxtHandle phContext,
    ULONG       fReq
    )
{
    CLIENT_MSG MyMsg;
    BOOLEAN bNotDone = TRUE;
    int retstat = ICPERROR;

    //
    // Generate and send a Negotiate message to the ICP server.
    //
    if (!GenerateAuthMsg (sIcpServer, phCredential, phContext, NULL, fReq))
    {
        (void)OUTPUTMSG0("ICPClient: Authentication Process Aborted\n");
        OUTPUTMSG();
        return (ICPERROR);
    }

    while (bNotDone)
    {
        //
        // Wait for server's message
        // ReceivedFromServer() will not return until either a full message is 
        // received from the server or error is encountered.
        //
        if (ReceiveMessage (sIcpServer, &MyMsg, sizeof (MyMsg)) < 0)
        {
            (*(g_pFuncTbl->DeleteSecurityContext)) (phContext);
            return (ICPERROR);
        }

        //
        // Process server's message 
        //
        switch (MyMsg.hdr.msg_type)
        {
        case CHALLENGE_MSG:
            if (!GenerateAuthMsg (sIcpServer, phCredential, phContext, 
                                  &MyMsg, fReq))
            {
                (void)OUTPUTMSG0("ICPClient: Authentication Process Aborted\n");
                OUTPUTMSG();
                bNotDone = FALSE;
            }
            break;

        case ACCESS_GRANTED:
            //
            // Receive server's OK on our authication request
            //
            bNotDone = FALSE;

            //
            // Initialize the random generator for data encryption
            //
            srand (1);
            retstat = ICPOK;
            break;

        case ACCESS_DENIED:
            bNotDone = FALSE;
            (void)OUTPUTMSG0("ICPClient: Server Access Denied\n");
            OUTPUTMSG();

            retstat = ICPAUTHFAIL;
            break;

        case AUTH_ERROR:
            bNotDone = FALSE;
            (void)OUTPUTMSG1(
                "ICPClient: Server Access Denied - Sever Protocol Verson %d\n",
                MyMsg.hdr.version);
            OUTPUTMSG();
            break;

        default:
            bNotDone = FALSE;
            (void)OUTPUTMSG0("ICPClient: Authentication Failed\n");
            OUTPUTMSG();
            break;
        }

    }

    if (retstat != ICPOK)
        (*(g_pFuncTbl->DeleteSecurityContext)) (phContext);

    return (retstat);
}

//+----------------------------------------------------------------------------
//
//  Function:   ShowUsage
//
//  Synopsis:   This function shows usage information of this program.
//
//  Arguments:  void
//
//  Returns:    void
//
//  History:    LucyC       Created                             17 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
VOID
ShowUsage (
    VOID
    )
{
#ifndef WIN16_BUILD
    printf ("usage: ICPCLient [switches]\n"
        "               [-?] show this message\n"
        "               [-d milliseconds] delay after sending a message\n"
        "               [-k SSPI-package] specify SSPI package to use\n"
        "               [-h hostname] specify the remote server\n"
        "               [-n] No encryption - do not send sealed message\n"
        "               [-u AccountName] specify user account name\n"
        "               [-l] specify to load msapsspc.dll directly\n"
        "               [-m DomainName] specify user domain name\n"
        "               [-p Password] specify user account password\n"
        "               [-f filename] specifies the remote file to attempt to access\n"
        "               [-v] verbose output\n" );
#else // WIN16_BUILD
    MessageBox (NULL,"usage: ICPCLient [switches]\n"
        "               [-?] show this message\n"
        "               [-d milliseconds] delay after sending a message\n"
        "               [-h hostname] specify the remote server\n"
        "               [-n] No encryption - do not send sealed message\n"
        "               [-u AccountName] specify user account name\n"
//        "               [-l] specify to load msapsspc.dll directly\n"
        "               [-m DomainName] specify user domain name\n"
        "               [-p Password] specify user account password\n"
        "               [-f filename] specifies the remote file to attempt to access\n"
        "               [-v] verbose output\n","Sampler Server Usage",MB_OK|MB_ICONEXCLAMATION );
#endif // WIN16_BUILD

    exit (1);
}


//+----------------------------------------------------------------------------
//
//  Function:   ParseUserOption
//
//  Synopsis:   This function parses user options specified in command switch.
//
//  Arguments:  argc - the no. of arguments passed in argv.
//              argv - the argument list passed from the command line.
//
//  Returns:    void
//
//  History:    LucyC       Created                             17 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
VOID
ParseUserOption (
    int argc,
    char *argv[]
    )
{
    PHOSTENT pHost;
    char *pchChar;
    char chChar;

    strcpy( g_szPkgName, "DPA");    // default to DPA package

    while (--argc)
    {
        pchChar = *++argv;
        if (*pchChar == '/' || *pchChar == '-')
        {
            while (chChar = *++pchChar)
            {
                switch (toupper (chChar))
                {
                case '?':
                    ShowUsage ();
                    break;
             
                case 'V':
                    g_bVerbose = TRUE;
                    break;

                case 'L':
                    g_bLoadDirect = TRUE;
                    break;
                case 'N':
                    g_bEncrypt = FALSE;
                    break;

                case 'K':
                    if (--argc == 0)  // If user did not specify package name
                    {
                        ShowUsage ();
                    }
                    argv++;
                    strcpy (g_szPkgName, *argv);
                    break;

                case 'U':
                    if (--argc == 0)  // If user did not specify user name
                    {
                        ShowUsage ();
                    }
                    g_bDefaultUser = FALSE;

                    argv++;
                    strcpy (g_ClientName, *argv);
                    break;

                case 'M':
                    if (--argc == 0)  // If user did not specify domain name
                    {
                        ShowUsage ();
                    }
                    g_bDefaultUser = FALSE;

                    argv++;
                    strcpy (g_ClientDomain, *argv);
                    break;

                case 'P':
                    if (--argc == 0)  // If user did not specify password
                    {
                        ShowUsage ();
                    }
                    g_bDefaultUser = FALSE;

                    argv++;
                    strcpy (g_ClientPassword, *argv);
                    break;

                case 'D':
                    if (--argc == 0)  // If user did not specify delay period
                        ShowUsage ();

                    argv++;
                    g_dwDelay = strtoul (*argv, NULL, 10);
                    break;

                case 'I':
                    if (--argc == 0)  // If no. of interation not specified
                        ShowUsage ();

                    argv++;
                    g_dwIterations = strtoul (*argv, NULL, 10);
                    if (g_bVerbose)
                    {
                        (void)OUTPUTMSG1(
                            "IcpClient: %lu Hello Messages Will Be Sent\n", 
                            g_dwIterations);
                            OUTPUTMSG();
                    }
                    break;
 
                case 'F':  // Test access to a file.
                    if (--argc == 0)  
                    {
                        ShowUsage ();
                    }
                    argv++;
                    strcpy (g_szFileToAccess, *argv);
                    g_uActionCode = GET_FILE_MSG;
                    break;

                case 'H':       // User specified remote host name

                    if (--argc == 0)  // If user did not specify hostname
                    {
                        ShowUsage ();
                    }

                    argv++;
                    if (g_bVerbose){
                        (void)OUTPUTMSG1("ICPClient: Server host %s\n", *argv);
                        OUTPUTMSG();
                    }
                    //
                    // Assumed host is specified by name
                    //
                    pHost = gethostbyname (*argv);
                    if (pHost == NULL)
                    {
                        //
                        // See if the host is specified in "dot address" form
                        //
                        g_RemoteIpAddress.s_addr = inet_addr (*argv);
                        if (g_RemoteIpAddress.s_addr == -1)
                        {
                            (void)OUTPUTMSG1(
                                "ICPClient: Unknown remote host: %s\n", *argv);
                            OUTPUTMSG();
                            exit (1);
                        }
                    }
                    else
                    {
#ifdef WIN16_BUILD
                        _fmemcpy ((char *) &g_RemoteIpAddress, pHost->h_addr, 
                                    pHost->h_length);
#else // WIN16_BUILD
					     CopyMemory ((char *) &g_RemoteIpAddress, pHost->h_addr, 
                                    pHost->h_length);
#endif // WIN16_BUILD
                    }
                    break;

                default:
                    (void)OUTPUTMSG1("ICPClient: Invalid switch - /%c\n", chChar);
                    OUTPUTMSG();
                    ShowUsage ();
                    break;
                }
            }
        }
        else
        {
            (void)OUTPUTMSG1("ICPClient: Invalid argument - %s\n", pchChar);
            OUTPUTMSG();
            ShowUsage ();
        }
    }
}

//+----------------------------------------------------------------------------
//
//  Function:   LoadSSP
//
//  Synopsis:   This function loads MSN SSPI DLL through the security DLL
//
//  Arguments:  void
//
//  Returns:    Pointer to the security function table if successful.
//              Otherwise, NULL is returned.
//
//  History:    LucyC       Created                             17 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
PSecurityFunctionTable
LoadSSP (
    VOID
    )
{
#ifndef WIN16_BUILD
    OSVERSIONINFO   VerInfo;
#endif // WIN16_BUILD
    UCHAR lpszDLL[SSP_DLL_NAME_SIZE];
    HINSTANCE hSecLib = NULL;
    PSecurityFunctionTable	pFuncTbl = NULL;
    INIT_SECURITY_INTERFACE	addrProcISI = NULL;

    //
    //  If loading msapsspc dll through security dll
    //
    if (!g_bLoadDirect)
    {
#ifndef WIN16_BUILD
        //
        //  Find out which security DLL to use, depending on 
        //  whether we are on NT or Win95
        //
        VerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
        if (!GetVersionEx (&VerInfo))   // If this fails, something gone wrong
        {
            OUTPUTMSG0("ICPClient: GetVersionEx() failed\n");
            OUTPUTMSG();
            return NULL;
        }

        if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
        {
            strcpy (lpszDLL, SSP_NT_DLL);
        }
        else if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
        {
            strcpy (lpszDLL, SSP_WIN95_DLL);
        }
        else
        {
            OUTPUTMSG1("ICPClient: Plateform %d not supported by MSN SSPI\n", 
                    VerInfo.dwPlatformId);                                    
            OUTPUTMSG();
            return NULL;
        }

        if (g_bVerbose){
            OUTPUTMSG1("ICPClient: Try to load %s\n", lpszDLL);
            OUTPUTMSG();
		}
        //
        //  Load Security DLL
        //
        hSecLib = LoadLibrary (lpszDLL);
        if (hSecLib == NULL)
        {
            OUTPUTMSG2("ICPClient: Cannot LoadLibrary %s [%d]!\n", 
                   lpszDLL, GetLastError());
            OUTPUTMSG();
        }
        else if (g_bVerbose){
            OUTPUTMSG1("ICPClient: Loaded %s\n", lpszDLL);
            OUTPUTMSG();
        }
#endif // WIN16_BUILD
    }

    //
    //  If user specified to load msapsspc dll directly or 
    //  if can not load security dll
    //
    if (g_bLoadDirect || hSecLib == NULL)
    {
        hSecLib = LoadLibrary (SSP_SSPC_DLL);
#ifdef WIN16_BUILD
        if (hSecLib<HINSTANCE_ERROR){
            OUTPUTMSG2("ICPClient: Cannot LoadLibrary %s [%d]... Exit!\n", 
                    SSP_SSPC_DLL, HINSTANCE_ERROR);
#else // WIN16_BUILD
        if (hSecLib == NULL)
        {
            OUTPUTMSG2("ICPClient: Cannot LoadLibrary %s [%d]... Exit!\n", 
                    SSP_SSPC_DLL, GetLastError());
#endif // WIN16_BUILD
            OUTPUTMSG();
            return NULL;
        }

        if (g_bVerbose){
            OUTPUTMSG1("ICPClient: Loaded %s\n", SSP_SSPC_DLL);
            OUTPUTMSG();
        }
    }

    addrProcISI = (INIT_SECURITY_INTERFACE) GetProcAddress( hSecLib, 
                    SECURITY_ENTRYPOINT);       
    if (addrProcISI == NULL)
    {
        OUTPUTMSG1(
           "ICPClient: GetProcAddress() of InitSecurityInterface failed [%d]\n",
            GetLastError());
        OUTPUTMSG();
        return NULL;
    }

    //
    // Get the SSPI function table
    //
    pFuncTbl = (*addrProcISI)();
    if (pFuncTbl == NULL)
    {
        OUTPUTMSG1("ICPClient: InitSecurityInterface() failed [%d]\n", 
                GetLastError());
        OUTPUTMSG();
    }

    return (pFuncTbl);
}


//+----------------------------------------------------------------------------
//
//  Function:   InitClient
//
//  Synopsis:   This function initializes the client:  initialize its data 
//              structures, loading dynamic library, and so forth.
//
//  Arguments:  argc - the no. of arguments passed in argv.
//              argv - the argument list passed from the command line.
//
//  Returns:    void
//
//  History:    LucyC       Created                             17 July 1995
//              Dave Crocco Modified                            October 1997
//
//-----------------------------------------------------------------------------
void
InitClient (
    int argc,
    char *argv[],
    PCredHandle phCredential
    )
{
    INT status;
    WSADATA WsaData;
    TimeStamp tsLifeTime;
    SEC_WINNT_AUTH_IDENTITY AuthData;
    PSEC_WINNT_AUTH_IDENTITY pAuthDataPtr = NULL;
    SECURITY_STATUS SecStatus;

    //
    // Default to the loopback address for the Benchmark
    //
    g_RemoteIpAddress.s_addr = htonl (INADDR_LOOPBACK);

    g_ClientName[0] = (CHAR) NULL;
    g_ClientDomain[0] = (CHAR) NULL;
    g_ClientPassword[0] = (CHAR) NULL;

    //
    // Initialize Windows Sockets and request version 1.1
    //
    status = WSAStartup (0x0101, &WsaData);
    if (status == SOCKET_ERROR)
    {
        (void)OUTPUTMSG1("ICPClient: WSAStartup() failed: %ld\n", GetLastError ());
        OUTPUTMSG();
        exit (1);
    }

    //
    // Process user specified options 
    //
    ParseUserOption (argc, argv);

    //
    //  Load security DLL
    //
    g_pFuncTbl = LoadSSP();
    if (g_pFuncTbl == NULL)
    {
        (void)OUTPUTMSG0("ICPClient: Cannot load security library... Exit!\n");
        OUTPUTMSG();
        exit (1);
    }

    // 
    // Get a credential handle for this client to use in future SSPI calls.
    //
    if (!g_bDefaultUser)
    {
        AuthData.User = g_ClientName;
        AuthData.UserLength = strlen (g_ClientName);
        AuthData.Domain = g_ClientDomain;
        AuthData.DomainLength = strlen (g_ClientDomain);
        AuthData.Password = g_ClientPassword;
        AuthData.PasswordLength = strlen (g_ClientPassword);
        AuthData.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
        pAuthDataPtr = &AuthData;
    }

    SecStatus = (*(g_pFuncTbl->AcquireCredentialsHandle)) (NULL, g_szPkgName, 
                      SECPKG_CRED_OUTBOUND,  NULL, pAuthDataPtr, NULL, NULL, 
                      phCredential, &tsLifeTime);
    if (SecStatus != SEC_E_OK)
    {
        (void)OUTPUTMSG1("ICPClient: Acquire Credential Handle Failed [0x%x]\n", 
                       SecStatus);
        OUTPUTMSG();
        exit (1);
    }
}
