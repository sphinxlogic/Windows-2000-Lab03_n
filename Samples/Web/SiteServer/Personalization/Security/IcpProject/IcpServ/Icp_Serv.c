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
// Copyright (C) 1996-97 Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   icp_serv.c
//
//  PURPOSE:  Sample ICP Server which listens on a well-known port for
//            client connection.  Once a client is connected, the server
//            will authenticate the client by ICP's authentication 
//            mechanism.  Once a client is authenticated successfully, 
//            the client will send a message to the server.  The server 
//            then output the client's message to the STDERR and 
//            send another messages back to the client.
//

#include "all_incl.h"

BOOLEAN g_bExit = FALSE;
BOOLEAN g_bVerbose = FALSE;
BOOLEAN g_bLoadDirect = FALSE;          // by default, always load security DLL
CredHandle g_hCredential;
CRITICAL_SECTION    g_ContextSection;
char g_szPkgName[40];
PCLIENT_INFO g_pListClients = NULL;     // List of all clients connected 

VSERVER_SPEC_STRUC g_ucVserverID;   // Structure used to specify the virtual auth server.


PSecurityFunctionTable	g_pFuncTbl = NULL;

//+----------------------------------------------------------------------------
//
//  Function:   ServiceExitRequest
//
//  Synopsis:   This function services exit requests entered by CTRL-C or 
//              CTRL-BREAK.  To do this, this function must be added to the 
//              process's list of handler functions by calling 
//              SetConsoleCtrlHandler().  This function will closes all client
//              connections before it exits and deallocate all client buffers.
//
//  Arguments:  uiKeyEntered - This value is zero if CTRL-C is entered and
//                             one if CTRL-BREAK is entered.
//
//  Returns:    TRUE if the process should continue running after this function
//              returns.  Otherwise, FALSE is returned to 'signal' immediate 
//              termination.
//
//  History:    LucyC       Created                             27 July 1995
//
//-----------------------------------------------------------------------------
BOOLEAN
ServiceExitRequest (
    UINT uiKeyEntered
    )
{
    PCLIENT_INFO pClient;
    PCLIENT_INFO pPrev = NULL;

    if (g_bVerbose)
        printf("\nICPSERV: Received CTRL-C !\n");

    g_bExit = TRUE;

    //
    // For each clients connected to the server, close its sockect connection
    // and deallocates all of its pending IO buffers.
    //
    while (g_pListClients)
    {
        pClient = g_pListClients;
        g_pListClients = g_pListClients->next;

        if (g_bVerbose)
            printf("... Closing Client Socket %d\n", pClient->Socket);

        CloseClient (pClient, FALSE);

        //
        // Deallocates all overlapped IO buffers of current client 
        //
        FreeAllIOBuffers (pClient);

        LocalFree (pClient);
    }

    DeleteCriticalSection(&g_ContextSection);

    return FALSE;
}

//+----------------------------------------------------------------------------
//
//  Function:   main
//
//  Synopsis:   This is the main function of the sample server.  The main 
//              will perform all the initializations required (including 
//              creating threads, and then call WaitClientConnection 
//              routine to accept client connections.  Once a client is 
//              connected, all client message processing is handled by the 
//              threads created.
//
//  History:    LucyC       Created                             13 July 1995
//              Dave Crocco Modified                            12/10/97
//
//-----------------------------------------------------------------------------
int _CRTAPI1 
main (
    int argc,
    char *argv[],
    char *envp[]
    )
{
    SOCKET sListener;
    HANDLE hCompletionPort;
 
    
    //
    // Process user specified options 
    //
    ParseUserOption (argc, argv);

    if (!InitServer ())
    {
        DeleteCriticalSection(&g_ContextSection);
        exit (1);
    }

    //
    // Initialize socket, start listening on the socket for client connections,
    // and create IO CompletionPort for all future socket connection.
    //
    if ((sListener = InitializeSocketIO (&hCompletionPort)) == SOCKET_ERROR)
    {
        DeleteCriticalSection(&g_ContextSection);
        exit (1);
    }

    //
    // Create worker thread(s) to handle client messages.  
    //
    if (! CreateThreadsForIoCompletion (hCompletionPort))
    {
        DeleteCriticalSection(&g_ContextSection);
        exit (1);
    }

    //
    // Wait for clients to connect.  Once connected, the first ReadFile() is
    // issued on the connection.  Then worker threads will take care of all 
    // IO activities on that connection from there on.
    //
    WaitClientConnection (sListener, hCompletionPort);

    exit (1);
    return 1;
}

//+----------------------------------------------------------------------------
//
//  Function:   LoadSSPS
//
//  Synopsis:   This function loads MSN SSPI DLL through the security DLL
//
//  Arguments:  void
//
//  Returns:    Pointer to the security function table if successful.
//              Otherwise, NULL is returned.
//
//  History:    LucyC       Created                             17 July 1995
//              Dave Crocco Modified                            12/10/97
//
//-----------------------------------------------------------------------------
PSecurityFunctionTable
LoadSSPS (
    VOID
    )
{
    OSVERSIONINFO   VerInfo;
    UCHAR lpszDLL[SSP_DLL_NAME_SIZE];
    HINSTANCE hSecLib;
    PSecurityFunctionTable	pFuncTbl = NULL;
    INIT_SECURITY_INTERFACE	addrProcISI = NULL;

    //
    //  If loading msapssps dll through security dll
    //
    if (!g_bLoadDirect)
    {
        //
        //  Find out which security DLL to use, depending on 
        //  whether we are on NT or Win95
        //
        VerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
        if (!GetVersionEx (&VerInfo))   // If this fails, something gone wrong
        {
            printf ("ICPSERV: GetVersionEx() failed\n");
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
            printf ("ICPSERV: Plateform %d not supported by MSN SSPI\n", 
                    VerInfo.dwPlatformId);
            return NULL;
        }

        if (g_bVerbose)
            printf ("ICPSERV: Try to load %s\n", lpszDLL);

        //
        //  Load Security DLL
        //
        hSecLib = LoadLibrary (lpszDLL);
        if (hSecLib == NULL)
        {
            printf ("ICPSERV: Cannot LoadLibrary %s [%d]!\n", 
                   lpszDLL, GetLastError());
        }
        else if (g_bVerbose)
            printf ("ICPSERV: Loaded %s\n", lpszDLL);
    }

    //
    //  If user specified to load msapssps dll directly or 
    //  if can not load security dll
    //
    if (g_bLoadDirect || hSecLib == NULL)
    {
        hSecLib = LoadLibrary (SSP_SSPS_DLL);
        if (hSecLib == NULL)
        {
            printf ("ICPSERV: Cannot LoadLibrary %s [%d]... Exit!\n", 
                    SSP_SSPS_DLL, GetLastError());
            return NULL;
        }

        if (g_bVerbose)
            printf ("ICPSERV: Loaded %s\n", SSP_SSPS_DLL);
    }

    addrProcISI = (INIT_SECURITY_INTERFACE) GetProcAddress( hSecLib, 
                    SECURITY_ENTRYPOINT);       
    if (addrProcISI == NULL)
    {
        printf (
           "ICPSERV: GetProcAddress() of InitSecurityInterface failed [%d]\n",
            GetLastError());
        return NULL;
    }

    //
    // Get the SSPI function table
    //
    pFuncTbl = (*addrProcISI)();
    if (pFuncTbl == NULL)
    {
        printf ("ICPSERV: InitSecurityInterface() failed [%d]\n", 
                GetLastError());
    }

    return (pFuncTbl);
}


//+----------------------------------------------------------------------------
//
//  Function:   InitServer
//
//  Synopsis:   This function specifies the version of Windows Sockets API 
//              required, registers ServiceExitRequest function to handle
//              CTRL-C and CTRL-BREAK, creates server's security credential 
//              handle, and initializes the random generator for message 
//              encryption.
//
//  Arguments:  void.
//
//  Returns:    TRUE if all initialization are successful.  Otherwise, FALSE
//              is returned if any critical initialization fails.
//
//  History:    LucyC       Created                             13 July 1995
//              Dave Crocco Modified                            12/10/97
//
//-----------------------------------------------------------------------------
BOOLEAN
InitServer (
    VOID
    )
{
    WSADATA WsaData;
    int status;
    TimeStamp tsLifeTime;

    if (g_bVerbose)
        printf ("ICPSERV: Calling WSAStartup()\n");

    //
    // Specifies the version of Windows Sockets API required by the server
    //
    status = WSAStartup (0x0101, &WsaData);
    if (status == SOCKET_ERROR)
    {
        printf("ICPSERV: Startup Winsock Failed [%d]\n", 
                    status);
        return FALSE;
    }

    if (g_bVerbose)
        printf ("ICPSERV: Calling SetConsoleCtrlHandler()\n");

    InitializeCriticalSection(&g_ContextSection);

    //
    // Setup handler to handle CTRL-C and CTRL-BREAK so that the server
    // will be terminated gracefully
    //
    if (!SetConsoleCtrlHandler ((PHANDLER_ROUTINE) ServiceExitRequest, TRUE))
    {
        printf("ICPSERV: Cannot Set Console Ctrl Handler\n");
    }

    if (g_bVerbose)
        printf ("ICPSERV: Calling LoadSSPS()\n");

    //
    //  Load security DLL
    //
    g_pFuncTbl = LoadSSPS();
    if (g_pFuncTbl == NULL)
    {
        (void)printf ("ICPSERV: Cannot load security library\n");
        return FALSE;
    }

    if (g_bVerbose)
        printf ("ICPSERV: Calling AcquireCredentialsHandle()\n");

    if ((status = (*(g_pFuncTbl->AcquireCredentialsHandle)) (NULL, 
                                                             g_szPkgName, 
                                                             SECPKG_CRED_INBOUND, 
                                                             NULL, 
                                                             NULL, 
                                                             NULL, 
                                                             NULL, 
                                                             &g_hCredential, 
                                                             &tsLifeTime
                                                            )) != SEC_E_OK)
    {
        printf ("ICPSERV: Acquire Credential Handle Failed [%d]\n", status);
        return FALSE;
    }

    if (g_bVerbose)
        printf ("ICPSERV: Finished AcquireCredentialsHandle()\n");

    return TRUE;
}

//+----------------------------------------------------------------------------
//
//  Function:   InitializeSocketIO
//
//  Synopsis:   This function initializes the server's listerner socket, 
//              and create an IO CompletionPort for all server's socket IO,
//
//  Arguments:  phCompletionPort - points to the created completionPort handle 
//                                 to be returned
//
//  Returns:    The socket handle which will be used to listen for client 
//              connection.  If any error is encountered, INVALID_SOCKET
//              is returned.
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
SOCKET
InitializeSocketIO (
    PHANDLE phCompletionPort
    )
{
    SOCKADDR_IN sin;
    SOCKET sListener;
    int status;

    //
    // Create a listening socket that we'll use to accept incoming
    // conections.
    //

    sListener = socket (AF_INET, SOCK_STREAM, 0);
    if (sListener == INVALID_SOCKET)
    {
        printf("ICPSERV: Failed to Create Socket[%d]\n", WSAGetLastError ());
        return (INVALID_SOCKET);
    }

    //
    // Bind the socket to the ICP Server port
    //

    sin.sin_family = AF_INET;
    sin.sin_port = htons (SICILY_SERVER_PORT);
    sin.sin_addr.s_addr = INADDR_ANY;

    status = bind (sListener, (LPSOCKADDR)&sin, sizeof (sin));
    if (status == SOCKET_ERROR)
    {
        printf("ICPSERV: Failed to Bind Sample ICP Server [%d]\n",
                    WSAGetLastError ());
        closesocket (sListener);
        return (INVALID_SOCKET);
    }

    //
    // Listen for incoming connections on the socket.
    //
    status = listen (sListener, 5);
    if (status == SOCKET_ERROR)
    {
        closesocket (sListener);
        printf("ICPSERV: Listen on Socket Failed [%d]\n", WSAGetLastError ());
        return (INVALID_SOCKET);
    }

    //
    // Create the completion port that will be used by all the worker threads
    //

    *phCompletionPort = CreateIoCompletionPort ((HANDLE)sListener, NULL, 0, 0);
    if  (*phCompletionPort == NULL)
    {
        closesocket (sListener);
        printf("ICPSERV: CreateIoCompletionPort Failed [%d]\n",
                    GetLastError ());
        return (INVALID_SOCKET);
    }

    if (g_bVerbose)
        printf("... Created socket listener %d on port %d\n", 
                    sListener, SICILY_SERVER_PORT);

    //
    // Initialize the random generator for the purpose of sealing messages
    //
    srand (1);

    return (sListener);
}


//+----------------------------------------------------------------------------
//
//  Function:   CreateNewClientInfo
//
//  Synopsis:   This function allocates memory for a new client information 
//              structure, initializes the structure, and add the client 
//              information structure to the server's client list for house-
//              keeping purposes.
//
//  Arguments:  void
//
//  Returns:    The pointer to the new client info. structure allocated.
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
PCLIENT_INFO
CreateNewClientInfo (
    VOID
    )
{
    PCLIENT_INFO pLastClient;
    PCLIENT_INFO pNewClient;

    pNewClient = (PCLIENT_INFO)LocalAlloc (0, sizeof (CLIENT_INFO));
    if (pNewClient == (PCLIENT_INFO) NULL)
        return (NULL);

    ZeroMemory (pNewClient, sizeof (CLIENT_INFO));

    pNewClient->state = in_Authentication;

    //
    // Add new client to the end of the server's client list for housekeeping
    //
    if (g_pListClients == NULL)
        g_pListClients = pNewClient; 
    else
    {
        for (pLastClient = g_pListClients; pLastClient->next != NULL; 
            pLastClient = pLastClient->next);
        pLastClient->next = pNewClient;
    }

    return (pNewClient);
}

//+----------------------------------------------------------------------------
//
//  Function:   CreateIOBuffer
//
//  Synopsis:   This function allocates memory for a new overlapped IO buffer,
//              and initializes the buffer as a read buffer.
//
//  Arguments:  dwBufLen - size of the actual IO buffer to be allocated.
//
//  Returns:    The pointer to the new overlapped IO buffer.
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
PCLIENT_OVERLAPPED
CreateIOBuffer (
    DWORD dwBufLen
    )
{
    PCLIENT_OVERLAPPED pIOBuf;

    pIOBuf = (PCLIENT_OVERLAPPED)LocalAlloc (0, sizeof (CLIENT_OVERLAPPED));
    if (pIOBuf == NULL)
    {
        return (NULL);
    }
    ZeroMemory ((PVOID) pIOBuf, sizeof (CLIENT_OVERLAPPED));

    pIOBuf->bufInfo.pBuffer = LocalAlloc (0, dwBufLen);
    if (pIOBuf->bufInfo.pBuffer == NULL)
    {
        LocalFree (pIOBuf);
        return (NULL);
    }

    ZeroMemory ((PVOID) pIOBuf->bufInfo.pBuffer, dwBufLen);

    pIOBuf->bufInfo.type = ServerRead;

    return (pIOBuf);
}

//+----------------------------------------------------------------------------
//
//  Function:   FreeClientInfo
//
//  Synopsis:   This function deletes the client info. structure from the 
//              server's client list and frees memory allocated for the 
//              structure.
//
//  Arguments:  pInfo - points to the client info. structure to be deleted
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
VOID
FreeClientInfo (
    PCLIENT_INFO pInfo
    )
{
    PCLIENT_INFO pClient;
    PCLIENT_INFO pPrev = NULL;

    //
    //  Do not delete the client if there's still output pending on the socket
    //
    if (pInfo == NULL || pInfo->pListOutOvlp)
        return;

    if (g_bVerbose)
        printf("ICPSERV: Enter FreeClientInfo()\n");

    //
    // Delete this client from server's client list
    //
    for (pClient = g_pListClients; pClient != NULL;
        pPrev = pClient, pClient = pClient->next)
    {
        if (pClient == pInfo)       // found the client in the server's list
        {
            if (g_bVerbose)
            {
                printf("ICPSERV: Removing Client <sock %d> from client list\n", 
                    pInfo->Socket);
            }

            if (pPrev == NULL)
                g_pListClients = pClient->next;
            else
                pPrev->next = pClient->next;

            (*(g_pFuncTbl->DeleteSecurityContext)) (&pInfo->hContext);

            //
            // Deallocate client's receiving IO buffer.
            //
            FreeIOBuffer (pInfo->pRecvOvlp);

            if (g_bVerbose)
            {
                printf("ICPSERV: Deallocate Client Info Struct 0x%x\n",
                            (ULONG)pInfo);
            }
            LocalFree (pInfo);

            break;
        }
    }

    if (g_bVerbose)
        printf("ICPSERV: Exit FreeClientInfo()\n");
}

//+----------------------------------------------------------------------------
//
//  Function:   FreeIOBuffer
//
//  Synopsis:   This function frees memory allocated for the specified 
//              overlapped IO buffer.
//
//  Arguments:  pIOBuf - points to the overlapped IO buffer to be deleted
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
VOID
FreeIOBuffer (
    PCLIENT_OVERLAPPED pIOBuf
    )
{
    if (pIOBuf != NULL)
    {
        if (pIOBuf->bufInfo.pBuffer != NULL)
            LocalFree (pIOBuf->bufInfo.pBuffer);
        LocalFree (pIOBuf);
    }
}

//+----------------------------------------------------------------------------
//
//  Function:   FreeAllIOBuffers
//
//  Synopsis:   This function deallocates all overlapped IO buffers of a 
//              specific client.
//
//  Arguments:  pClient - points to the client info. structure.
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
VOID
FreeAllIOBuffers (
    PCLIENT_INFO pClient
    )
{
    PListSentOvlp pCurrOvlp;

    //
    // Deallocate client's receiving IO buffer.
    //
    FreeIOBuffer (pClient->pRecvOvlp);

    //
    // Deallocate client's pending outgoing IO buffers
    //
    while (pClient->pListOutOvlp)
    {
        pCurrOvlp = pClient->pListOutOvlp;
        pClient->pListOutOvlp = pClient->pListOutOvlp->next;

        if (g_bVerbose)
        {
            printf ( 
            "ICPSERV: Deallocate Client <sock %d> Outbound IO Buffer 0x%x\n",
                    pClient->Socket, (ULONG)pCurrOvlp->pSendOvlp);
        }

        FreeIOBuffer (pCurrOvlp->pSendOvlp);

        LocalFree (pCurrOvlp);
    }
}

//+----------------------------------------------------------------------------
//
//  Function:   WaitClientConnection
//
//  Synopsis:   This function loops for client connections.  For every client 
//              connected, it will create a client info. structure and an 
//              overlapped IO buffer for read, and initiate a read on the 
//              client socket.  Then it go back to wait for the next client
//              connection.
//
//  Arguments:  sListener - handle to the listener's socket.
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
VOID
WaitClientConnection (
    SOCKET sListener, 
    HANDLE hCompletionPort
    )
{
    SOCKET              client_sock;
    SOCKADDR_IN         acc_sin;
    int                 acc_sin_len;
    BOOLEAN             bSuccess;
    PCLIENT_INFO        pClientInfo;
    PCLIENT_OVERLAPPED  pOverlapped;
    PCHAR               pBuffer;
    
    DWORD dwBytesRead;
    int status;
    int zero;

    while (TRUE)
    {
        //
        // Wait to accept connection from client
        //
        acc_sin_len = sizeof (acc_sin);
        client_sock = accept (sListener, (struct sockaddr FAR *)&acc_sin, 
                    (int FAR *)&acc_sin_len);
        if (client_sock == INVALID_SOCKET)
        {
            closesocket (sListener);
            printf ( 
                        "ICPSERV: Failed To Accept Client Connection [%d]\n", 
                        WSAGetLastError ());
            return;
        }

        if (g_bExit)
        {
            closesocket (sListener);
            //
            // should we close all the client sockets and free all the 
            // allocated memory before we go ???
            //
            if (g_bVerbose)
            {
                printf (  "\nICPSERV: Exiting mainloop due to user request\n");
            }
            return;
        }
 
        if (g_bVerbose)
        {
            printf (  "\nICPSERV: New client connection from %s - socket %d\n",
                inet_ntoa (acc_sin.sin_addr), client_sock);
        }

        //
        // Allocate memory for keeping all information on this client.
        // And initialize the ClientInfo structure after creation.
        //
        pClientInfo = CreateNewClientInfo ();
        if (pClientInfo == NULL)
        {
            printf (  "ICPSERV: Memory Allocation for ClientInfo Failed\n");
            closesocket (client_sock);
            continue;
        }
    
        pClientInfo->Socket = client_sock;

        CopyMemory (&pClientInfo->client_addr, &acc_sin.sin_addr, 
                    sizeof (acc_sin.sin_addr));

        hCompletionPort = CreateIoCompletionPort ((HANDLE)client_sock, 
                    hCompletionPort, (DWORD)pClientInfo, 0);
        if (hCompletionPort == NULL)
        {
            printf (  "ICPSERV: CreateIoCompletionPort Failed [%d]\n",
                        GetLastError ());
            CloseClient (pClientInfo, FALSE);
            FreeClientInfo (pClientInfo);
            closesocket (sListener);
            return;
        }
    
        //
        // Disable send bufferring on the socket.  Setting SO_SNDBUF
        // to 0 causes winsock to stop bufferring sends and perform
        // sends directly from our buffers, thereby reducing CPU
        // usage.
        //
    
        zero = 0;
        status = setsockopt (client_sock, SOL_SOCKET, SO_SNDBUF, (char *)&zero, 
                    sizeof (zero));
        if (status == SOCKET_ERROR)
        {
            printf ( "ICPSERV: SetSockOpt Failed [%d]\n",
                        WSAGetLastError ());
            CloseClient (pClientInfo, FALSE);
            FreeClientInfo (pClientInfo);
            closesocket (sListener);
            return;
        }
    
        //
        // Create and initialize client's Overlapped and IO buffer
        //
        pOverlapped = CreateIOBuffer (MAX_CLIENT_BUF_LEN);
        if (pOverlapped == NULL)
        {
            printf ( 
                        "ICPSERV: Memory Allocation for Overlapped Failed\n");
            CloseClient (pClientInfo, FALSE);
            FreeClientInfo (pClientInfo);
            continue;
        }

        //
        // Setup client info structure to point to this overlapper IO buffer.
        //
        pClientInfo->pRecvOvlp = pOverlapped;
                    
        pBuffer = pOverlapped->bufInfo.pBuffer;

        //
        // Start an overlapped read on the socket.  This read will
        // complete in one of the worker threads, which will continue
        // processing of the client.
        //
        bSuccess = ReadFile ((HANDLE)client_sock, (LPVOID) pBuffer, 
                    MAX_CLIENT_BUF_LEN, &dwBytesRead, (LPOVERLAPPED) 
                    pOverlapped);
    
        if (!bSuccess && GetLastError () != ERROR_IO_PENDING)
        {
            printf ( "ICPSERV: First ReadFile Failed [%d]\n",
                        GetLastError ());
            CloseClient (pClientInfo, FALSE);
            FreeClientInfo (pClientInfo);
            continue;
        }

        if (g_bVerbose)
            printf ( "... Issued first read on client <socket %d>\n", 
                        client_sock);
    }
}

//+----------------------------------------------------------------------------
//
//  Function:   ShowUsage
//
//  Synopsis:   This function prints out summary of the command syntax and 
//              options.
//
//  Arguments:  void
//
//  Returns:    void
//
//  History:    LucyC       Created                             12 July 1995
//              Dave Crocco Modified                            12/10/97
//
//-----------------------------------------------------------------------------
VOID
ShowUsage (
    VOID
    )
{
    printf("usage: ICPSERV [switches]\n"
           "               [-?] show this message\n"
           "               [-l] load msapssps.dll directly\n"
           "               [-k SSPI-pkg-name] specifies the SSPI pkg to use\n"
           "               [-v] verbose output\n"
           "               [-s U2-Virtual-Server-ID-Number]\n"
          );
    exit (1);
}

//+----------------------------------------------------------------------------
//
//  Function:   ParseUserOption
//
//  Synopsis:   This function parses user options specified in command switch.
//
//  Arguments:  argc -  
//              argv -     
//
//  Returns:    void
//
//  History:    LucyC       Created                             12 July 1995
//              Dave Crocco Modified                            12/10/97
//
//-----------------------------------------------------------------------------
VOID
ParseUserOption (
    int argc,
    char *argv[]
    )
{
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

                case 'S':
                    if (--argc == 0)  // If user did not specify virtual server ID NUMBER.
                    {
                        ShowUsage (); // This will exit the program.
                    } else {
                        INT iVServerID;
                        argv++;
                        iVServerID = atoi(*argv);
                        _itow(iVServerID, 
                              g_ucVserverID.szwVirtualServerID, 
                              10
                             );
                        g_ucVserverID.ucszVServer.Length = (wcslen(g_ucVserverID.szwVirtualServerID)+1) * sizeof(WCHAR);
                        g_ucVserverID.ucszVServer.MaximumLength = g_ucVserverID.ucszVServer.Length;
                        g_ucVserverID.ucszVServer.Buffer = (unsigned short *)sizeof(UNICODE_STRING);
                    }//endif
                    break;
             
                case 'L':
                    g_bLoadDirect = TRUE;
                    break;

                case 'K':
                    if (--argc == 0)  // If user did not specify package name
                    {
                        ShowUsage ();
                    }
                    argv++;
                    strcpy (g_szPkgName, *argv);
                    break;

                default:
                    printf ( "ICPSERV: Invalid switch - /%c\n", 
                                chChar);
                    ShowUsage ();
                    break;
                }
            }
        }
        else
        {
            printf ( "ICPSERV: Invalid argument - %s\n", pchChar);
            ShowUsage ();
        }
    }
}

//+----------------------------------------------------------------------------
//
//	Function:	CloseClient
//
//	Synopsis:	This function cleans up all sturctures associated with a 
//              particular client and closes its socket.
//
//  Arguments:  pInfo - Points to the client information structure
//              bGraceful - Flag indicating whether we should close the 
//                          socket connection gracefully or not.
//
//  Returns:    void
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
VOID
CloseClient (
    PCLIENT_INFO pInfo,
    BOOLEAN bGraceful
    )
{
    LINGER lingerStruct;

    if (pInfo->state == connection_closed)
        return;

    //
    // If we're supposed to abort the connection
    //
    if (!bGraceful)
    {
        //
        // Set the linger value on the socket to 0 to abort the connection -
        // i.e. any unsent data on the socket will be lost.
        //
        lingerStruct.l_onoff = 1;
        lingerStruct.l_linger = 0;
        setsockopt (pInfo->Socket, SOL_SOCKET, SO_LINGER,
                    (char *)&lingerStruct, sizeof(lingerStruct));
    }

    //
    // Now close the socket handle.  This will do an abortive or 
    // graceful close, as requested.  
    //

    closesocket (pInfo->Socket);

    pInfo->state = connection_closed;

} // CloseClient
