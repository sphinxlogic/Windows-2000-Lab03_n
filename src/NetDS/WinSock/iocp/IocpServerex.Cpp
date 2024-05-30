// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      iocpserverex.cpp
//
// Abstract:
//      This program is a Winsock echo server program that demonstrates the usage
//      of AcceptEx with IOCP. The AcceptEx function accepts a new connection, 
//      returns the local and remote address, and receives the first block of data 
//      sent by the client application. The design of this program is based on that 
//      in the iocpserver.cpp. But it uses overlapped AcceptEx on the IOCP also. 
//      AcceptEx allows data to be "returned" from an accepted connection.
//
//  Usage:
//      Start the server and wait for connections on port 6001
//          iocpserverex -e:6001
//
//  Build:
//      Use the headers and libs from the April98 Platform SDK or later.
//      Link with ws2_32.lib and mswsock.lib
//      
//  Author: Wei Hua, Barry Butterklee - Microsoft Developer Support
//
//


#include <windows.h>
#include <winsock2.h>
#include <mswsock.h>
#include <stdio.h>
#include <stdlib.h>

#include "iocpserver.h"


unsigned short  g_Port          = DEFAULT_PORT;

BOOL            g_bEndServer    = FALSE;            // set to TRUE on CTRL-C

BOOL            g_bRestart      = TRUE;             // set to TRUE to CTRL-BRK

BOOL            g_bVerbose      = FALSE;

HANDLE          g_hIOCP         = NULL;

SOCKET          g_sdListen      = INVALID_SOCKET;

HANDLE          g_ThreadHandles[MAX_WORKER_THREAD];

HANDLE          g_hCleanupEvent         = NULL;

PPER_SOCKET_CONTEXT g_pCtxtListenSocket = NULL;

PPER_SOCKET_CONTEXT g_pCtxtList = NULL;     // linked list of context info structures
                                            // maintained to allow the the cleanup 
                                            // handler to cleanly close all sockets and 
                                            // free resources.

CRITICAL_SECTION    g_CriticalSection;      // guard access to the global context list



 
void main (int argc, char *argv[])
    {
    SYSTEM_INFO         systemInfo;
    WSADATA             wsaData;
    DWORD               dwThreadCount;
	int                 nRet;


    if (!ValidOptions(argc, argv))
        return;

    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE)) 
        {
        printf ("SetConsoleCtrlHandler failed to install console handler: %d\n", 
        GetLastError());
        return;
        }

    GetSystemInfo(&systemInfo);
    dwThreadCount = systemInfo.dwNumberOfProcessors * 2;

    g_hCleanupEvent = CreateEvent( NULL, TRUE, FALSE, NULL);
    if (g_hCleanupEvent == NULL)
        {
        printf("CreateEvent failed: %d\n",GetLastError());
        return;
        }
    
    if ((nRet = WSAStartup(0x202, &wsaData)) != 0) 
        {
        printf("WSAStartup failed: %d\n",nRet);
        CloseHandle(g_hCleanupEvent);
        return;
        }
    
    InitializeCriticalSection(&g_CriticalSection);
    
    while (g_bRestart)
        {
        g_bRestart = FALSE;
        g_bEndServer = FALSE;
        ResetEvent(g_hCleanupEvent);

        __try 
            {

            // notice that we will create more worker threads (dwThreadCount) than 
            // the thread concurrency limit on the IOCP.
            g_hIOCP = CreateIoCompletionPort(       
                INVALID_HANDLE_VALUE, NULL, 0, 0);
            if (NULL == g_hIOCP) 
                {
                printf( "CreateIoCompletionPort failed to create I/O completion port: %d\n", 
                    GetLastError());
                __leave;
                }

            for (DWORD dwCPU=0; dwCPU<dwThreadCount; dwCPU++) 
                {
                // Create worker threads to service the overlapped I/O requests.  The decision
                // to create 2 worker threads per CPU in the system is a heuristic.  Also,
                // note that thread handles are closed right away, because we will not need them
                // and the worker threads will continue to execute.
                HANDLE  hThread;
                DWORD   dwThreadId;

                hThread = CreateThread(NULL, 0, WorkerThread, g_hIOCP, 0, &dwThreadId);
                if (hThread == NULL) 
                    {
                    printf("CreateThread failed to create worker thread: %d\n", 
                        GetLastError());
                    __leave;
                    }
                g_ThreadHandles[dwCPU] = hThread;
                }
            
            if (!CreateListenSocket())
                __leave;


            if (!CreateAcceptSocket(TRUE))
                __leave;

            WaitForSingleObject(g_hCleanupEvent, INFINITE);
            }

        __finally 
            {
            g_bEndServer = TRUE;
            // Cause worker threads to exit
            if (g_hIOCP)        
                {
                for (DWORD i = 0; i < dwThreadCount; i++)
                    PostQueuedCompletionStatus(g_hIOCP, 0, 0, NULL);
                }
            
            //Make sure worker threads exits.
            if (WAIT_OBJECT_0 != WaitForMultipleObjects(dwThreadCount,  g_ThreadHandles, TRUE, 1000))
                printf("WaitForMultipleObjects failed: %d\n", GetLastError());
            else
                for (DWORD i=0; i<dwThreadCount; i++)
                    {
                    if (g_ThreadHandles[i] != INVALID_HANDLE_VALUE) 
                        CloseHandle(g_ThreadHandles[i]);
                    g_ThreadHandles[i] = INVALID_HANDLE_VALUE;
                    }

            if (g_sdListen != INVALID_SOCKET) 
                {
                closesocket(g_sdListen);                                
                g_sdListen = INVALID_SOCKET;
                }
                
            if (g_pCtxtListenSocket)
                {
                while (!HasOverlappedIoCompleted((LPOVERLAPPED)&g_pCtxtListenSocket->pIOContext->Overlapped)) 
                    Sleep(0);
                
                if (g_pCtxtListenSocket->pIOContext->SocketAccept != INVALID_SOCKET) 
                    closesocket(g_pCtxtListenSocket->pIOContext->SocketAccept);
                g_pCtxtListenSocket->pIOContext->SocketAccept = INVALID_SOCKET;
            
                //We know there is only one overlapped I/O on the listening socket
                if (g_pCtxtListenSocket->pIOContext) 
                    HeapFree(GetProcessHeap(), 0, g_pCtxtListenSocket->pIOContext);

                if (g_pCtxtListenSocket) 
                    HeapFree(GetProcessHeap(), 0, g_pCtxtListenSocket);
                g_pCtxtListenSocket = NULL;
                }

            CtxtListFree();
   
            if (g_hIOCP)    
                {
                CloseHandle(g_hIOCP);
                g_hIOCP = NULL;
                }
            } //finally

        
        if (g_bRestart) 
            {
            printf("\niocpserverex is restarting...\n");
            }
        else 
            printf("\niocpserverex is exiting...\n");

        } //while (g_bRestart)
    
    DeleteCriticalSection(&g_CriticalSection);
    WSACleanup();
    CloseHandle(g_hCleanupEvent);
    SetConsoleCtrlHandler(CtrlHandler, FALSE);
    } //main

    


//  Just validate the command line options.
//
BOOL ValidOptions(int argc, char *argv[])
    {
    BOOL bRet = TRUE;


    for (int i=1; i<argc; i++)
        {
        if ((argv[i][0] =='-') || (argv[i][0] == '/'))
            {
            switch (tolower(argv[i][1]))
                {
                case 'e':
                    if (strlen(argv[i]) > 3)
                        g_Port = (unsigned short)atoi(&argv[i][3]);
                    break;

                case 'v':
                    g_bVerbose = TRUE;
                    break;

                case '?':
                    printf("Usage:\n  iocpserver [-p:port] [-v] [-?]\n");
                    printf("  -e:port\tSpecify echoing port number\n");        
                    printf("  -v\t\tVerbose\n");        
                    printf("  -?\t\tDisplay this help\n");
                    bRet = FALSE;
                    break;

                default:
                    printf("Unknown options flag %s\n", argv[i]);
                    bRet = FALSE;
                    break;
                }
            }
        }   

    return(bRet);
    }




//  Intercept CTRL-C or CTRL-BRK events and cause the server to initiate shutdown.
//  CTRL-BRK resets the restart flag, and after cleanup the server restarts.
BOOL WINAPI CtrlHandler (
    DWORD dwEvent
    )
    {    
    switch (dwEvent) 
        {
        case CTRL_BREAK_EVENT: 
            g_bRestart = TRUE;
        case CTRL_C_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
        case CTRL_CLOSE_EVENT:
            if (g_bVerbose)
                printf("CtrlHandler: closing listening socket\n");

            g_bEndServer = TRUE;

            SetEvent(g_hCleanupEvent);
            break;

        default:
            // unknown type--better pass it on.
            return(FALSE);
        }
    return(TRUE);
    }




// Create a socket with all the socket options we need, namely disable buffering
// and set linger.
//
SOCKET CreateSocket(void)
    {
    int         nRet;
    int         nZero = 0;
    LINGER      lingerStruct;
    SOCKET      sdSocket = INVALID_SOCKET;


    sdSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED); 
    if (INVALID_SOCKET == sdSocket)
        {
        printf("WSASocket(sdSocket): %d\n", WSAGetLastError());
        return(sdSocket);
        }

    // Disable send buffering on the socket.  Setting SO_SNDBUF
    // to 0 causes winsock to stop bufferring sends and perform
    // sends directly from our buffers, thereby save one memory copy.
    nZero = 0;
    nRet = setsockopt(sdSocket, SOL_SOCKET, SO_SNDBUF, (char *)&nZero, sizeof(nZero));
    if (SOCKET_ERROR == nRet) 
        {
        printf("setsockopt(SNDBUF): %d\n", WSAGetLastError());
        return(sdSocket);
        }

    // Disable receive buffering on the socket.  Setting SO_RCVBUF 
    // to 0 causes winsock to stop bufferring receive and perform
    // receives directly from our buffers, thereby save one memory copy.
    nZero = 0;
    nRet = setsockopt(sdSocket, SOL_SOCKET, SO_RCVBUF, (char *)&nZero, sizeof(nZero));
    if (SOCKET_ERROR == nRet) 
        {
        printf("setsockopt(SO_RCVBUF): %d\n", WSAGetLastError());
        return(sdSocket);
        }
        
    lingerStruct.l_onoff = 1;
    lingerStruct.l_linger = 0;
    nRet = setsockopt(sdSocket, SOL_SOCKET, SO_LINGER,
                  (char *)&lingerStruct, sizeof(lingerStruct));
    if (SOCKET_ERROR == nRet) 
        {
        printf("setsockopt(SO_LINGER): %d\n", WSAGetLastError());
        return(sdSocket);
        }

    return(sdSocket);
    }




//  Create a listening socket, bind, and set up its listening backlog.
//
BOOL CreateListenSocket(void)
    {
    SOCKADDR_IN si_addrlocal;
    int         nRet;
    LINGER      lingerStruct;

    lingerStruct.l_onoff = 1;
    lingerStruct.l_linger = 0;


    g_sdListen = CreateSocket();
    if (INVALID_SOCKET == g_sdListen)
        {
        return(FALSE);
        }

    si_addrlocal.sin_family = AF_INET;
    si_addrlocal.sin_port = htons(g_Port);
    si_addrlocal.sin_addr.s_addr = htonl(INADDR_ANY);       
    nRet = bind(g_sdListen, (struct sockaddr *)&si_addrlocal, sizeof(si_addrlocal));
    if (SOCKET_ERROR == nRet) 
        {
        printf("bind: %d\n", WSAGetLastError());
        return(FALSE);
        }

    nRet = listen(g_sdListen, 5);
    if (SOCKET_ERROR == nRet) 
        {
        printf("listen: %d\n", WSAGetLastError());
        return(FALSE);
        }

    return(TRUE);
    }




// Create a socket and invoke AcceptEx.  Only the original call to to this
// function needs to be added to the IOCP.
//
// If the expected behaviour of connecting client applications is to NOT
// send data right away, then only posting one AcceptEx can cause connection
// attempts to be refused if a client connects without sending some initial
// data (notice that the associated iocpclient does not operate this way 
// but instead makes a connection and starts sending data write away).  
// This is because the IOCP packet does not get delivered without the initial
// data (as implemented in this sample) thus preventing the worker thread 
// from posting another AcceptEx and eventually the backlog value set in 
// listen() will be exceeded if clients continue to try to connect.
//
// One technique to address this situation is to simply cause AcceptEx
// to return right away upon accepting a connection without returning any
// data.  This can be done by setting dwReceiveDataLength=0 when calling AcceptEx.
//
// Another technique to address this situation is to post multiple calls 
// to AcceptEx.  Posting multiple calls to AcceptEx is similar in concept to 
// increasing the backlog value in listen(), though posting AcceptEx is 
// dynamic (i.e. during the course of running your application you can adjust 
// the number of AcceptEx calls you post).  It is important however to keep
// your backlog value in listen() high in your server to ensure that the 
// stack can accept connections even if your application does not get enough 
// CPU cycles to repost another AcceptEx under stress conditions.
// 
// This sample implements neither of these techniques and is therefore
// susceptible to the behaviour described above.
//
BOOL CreateAcceptSocket(BOOL fUpdateIOCP)
    {
    int         nRet;
    DWORD       dwRecvNumBytes = 0;     


    //The context for listening socket uses the SockAccept member to store the
    //socket for client connection. 
    if (fUpdateIOCP)
        {
        g_pCtxtListenSocket = UpdateCompletionPort(g_sdListen, ClientIoAccept, FALSE);
        if (g_pCtxtListenSocket == NULL)
            {
            printf("failed to update listen socket to IOCP\n");
            return(FALSE);
            }
        }

    g_pCtxtListenSocket->pIOContext->SocketAccept = CreateSocket();
    if (INVALID_SOCKET == g_pCtxtListenSocket->pIOContext->SocketAccept)
        {
        printf("failed to create new accept socket\n");
        return(FALSE);
        }

    // pay close attention to these parameters and buffer lengths
    nRet = AcceptEx(
            g_sdListen, 
            g_pCtxtListenSocket->pIOContext->SocketAccept,
            (LPVOID)(g_pCtxtListenSocket->pIOContext->Buffer),
            MAX_BUFF_SIZE - (2 * (sizeof(SOCKADDR_IN) + 16)),
            sizeof(SOCKADDR_IN) + 16,
            sizeof(SOCKADDR_IN) + 16,
            &dwRecvNumBytes,
            (LPOVERLAPPED) &(g_pCtxtListenSocket->pIOContext->Overlapped)
            );
    if (nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError())) 
        {
        printf("AcceptEx Failed: %d\n", WSAGetLastError());
        return(FALSE);
        }

    return(TRUE);
    }


 

// Worker thread that handles all I/O requests on any socket handle added to the IOCP.
//
DWORD WINAPI WorkerThread (
    LPVOID WorkThreadContext
    )
    {
    HANDLE          hIOCP = (HANDLE)WorkThreadContext;
    BOOL            bSuccess = FALSE;
    int             nRet;
    LPOVERLAPPED    lpOverlapped = NULL;
    PPER_SOCKET_CONTEXT lpPerSocketContext = NULL;
    PPER_SOCKET_CONTEXT lpAcceptSocketContext = NULL;
    PPER_IO_CONTEXT     lpIOContext = NULL; 
    WSABUF          buffRecv;
    WSABUF          buffSend;
    DWORD           dwRecvNumBytes = 0;
    DWORD           dwSendNumBytes = 0;
    DWORD           dwFlags = 0;
    DWORD           dwIoSize;
   
    while (TRUE) 
        {

        // continually loop to service io completion packets
        bSuccess = GetQueuedCompletionStatus(
                       hIOCP,
                       &dwIoSize,
                       (PDWORD_PTR)&lpPerSocketContext,
                       &lpOverlapped,
                       INFINITE 
                       );
        if (!bSuccess) 
            printf("GetQueuedCompletionStatus: %d\n", GetLastError());


        if (lpPerSocketContext == NULL)
            {
            // CTRL-C handler used PostQueuedCompletionStatus to post an I/O packet with
            // a NULL CompletionKey (or if we get one for any reason).  It is time to exit.
            return(0);
            }

        if (g_bEndServer) 
            {
            // main thread will do all cleanup needed - see finally block
            return 0;
            }

        lpIOContext = (PPER_IO_CONTEXT)lpOverlapped;

        //We should never skip the loop and not post another AcceptEx if the current
        //completion packet is for previous AcceptEx
        if (lpIOContext->IOOperation != ClientIoAccept)
            {
            if (!bSuccess || (bSuccess && (0 == dwIoSize)) )
                {
                // client connection dropped, continue to service remaining (and possibly 
                // new) client connections
                CloseClient(lpPerSocketContext, FALSE); 
                continue;
                }
            }


        // determine what type of IO packet has completed by checking the PER_IO_CONTEXT 
        // associated with this socket.  This will determine what action to take.
        switch (lpIOContext->IOOperation)
            {
            case ClientIoAccept:
                // When the AcceptEx function returns, the socket sAcceptSocket is 
                // in the default state for a connected socket. The socket sAcceptSocket 
                // does not inherit the properties of the socket associated with 
                // sListenSocket parameter until SO_UPDATE_ACCEPT_CONTEXT is set on 
                // the socket. Use the setsockopt function to set the SO_UPDATE_ACCEPT_CONTEXT 
                // option, specifying sAcceptSocket as the socket handle and sListenSocket 
                // as the option value. 
                nRet = setsockopt(
                    lpPerSocketContext->pIOContext->SocketAccept, 
                    SOL_SOCKET,
                    SO_UPDATE_ACCEPT_CONTEXT,
                    (char *)&g_sdListen,
                    sizeof(g_sdListen)
                    );

                if (nRet == SOCKET_ERROR)
                    {
                    //just warn user here.
                    printf("setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed to update accept socket\n");
                    SetEvent(g_hCleanupEvent);
                    return 0;
                    }
                
                 lpAcceptSocketContext = UpdateCompletionPort(
                     lpPerSocketContext->pIOContext->SocketAccept, 
                     ClientIoAccept, TRUE);

                 if (lpAcceptSocketContext == NULL)
                    {
                    //just warn user here.
                    printf("failed to update accept socket to IOCP\n");
                    SetEvent(g_hCleanupEvent);
                    return 0;
                    }
                
                if (dwIoSize)
                    {
                    lpAcceptSocketContext->pIOContext->IOOperation = ClientIoWrite;
                    lpAcceptSocketContext->pIOContext->nTotalBytes  = dwIoSize;
                    lpAcceptSocketContext->pIOContext->nSentBytes   = 0;
                    lpAcceptSocketContext->pIOContext->wsabuf.len   = dwIoSize;
                    CopyMemory(lpAcceptSocketContext->pIOContext->Buffer, lpPerSocketContext->pIOContext->Buffer, sizeof(lpPerSocketContext->pIOContext->Buffer));
                    lpAcceptSocketContext->pIOContext->wsabuf.buf = lpAcceptSocketContext->pIOContext->Buffer;
                    
                    nRet = WSASend(
                        lpPerSocketContext->pIOContext->SocketAccept,
                        &lpAcceptSocketContext->pIOContext->wsabuf, 1,
                        &dwSendNumBytes,
                        0,
                        &(lpAcceptSocketContext->pIOContext->Overlapped), NULL);

                    if (SOCKET_ERROR == nRet && (ERROR_IO_PENDING != WSAGetLastError())) 
                        {
                        printf ("WSASend: %d\n", WSAGetLastError());
                        CloseClient(lpAcceptSocketContext, FALSE);
                        }
                    else if (g_bVerbose)
                        {
                        printf("WorkerThread %d: Socket(%d) AcceptEx completed (%d bytes), Send posted\n", 
                            GetCurrentThreadId(), lpPerSocketContext->Socket, dwIoSize);
                        }
                    }
                else 
                    {
                    // AcceptEx completes but doesn't read any data so we need to post
                    // an outstanding overlapped read.
                    lpAcceptSocketContext->pIOContext->IOOperation = ClientIoRead;
                    dwRecvNumBytes = 0;
                    dwFlags = 0;
                    buffRecv.buf = lpAcceptSocketContext->pIOContext->Buffer,
                    buffRecv.len = MAX_BUFF_SIZE;
                    nRet = WSARecv(
                        lpAcceptSocketContext->Socket,
                        &buffRecv, 1,
                        &dwRecvNumBytes,
                        &dwFlags,
                        &lpAcceptSocketContext->pIOContext->Overlapped, NULL);
                    if (SOCKET_ERROR == nRet && (ERROR_IO_PENDING != WSAGetLastError())) 
                        {
                        printf ("WSARecv: %d\n", WSAGetLastError());
                        CloseClient(lpAcceptSocketContext, FALSE);
                        }
                    }
                
                //Time to post another outstanding AcceptEx
                if (!CreateAcceptSocket(FALSE)) 
                    {
                    printf("Please shut down and reboot the server.\n");
                    SetEvent(g_hCleanupEvent);
                    return 0;
                    }               
                break;

            
            case ClientIoRead:
                // a read operation has completed, post a write operation to echo the
                // data back to the client using the same data buffer.
                lpIOContext->IOOperation = ClientIoWrite;
                lpIOContext->nTotalBytes = dwIoSize;
                lpIOContext->nSentBytes  = 0;
                lpIOContext->wsabuf.len  = dwIoSize;
                dwFlags = 0;
                nRet = WSASend(
                    lpPerSocketContext->Socket,
                    &lpIOContext->wsabuf, 1, &dwSendNumBytes,
                    dwFlags,
                    &(lpIOContext->Overlapped), NULL);
                if (SOCKET_ERROR == nRet && (ERROR_IO_PENDING != WSAGetLastError())) 
                    {
                    printf("WSASend: %d\n", WSAGetLastError());
                    CloseClient(lpPerSocketContext, FALSE);
                    }
                else if (g_bVerbose)
                    {
                    printf("WorkerThread %d: Socket(%d) Recv completed (%d bytes), Send posted\n", 
                        GetCurrentThreadId(), lpPerSocketContext->Socket, dwIoSize);
                    }
                break;

            case ClientIoWrite:
                // a write operation has completed, determine if all the data intended to be
                // sent actually was sent.
                lpIOContext->IOOperation = ClientIoWrite;
                lpIOContext->nSentBytes  += dwIoSize;
                dwFlags = 0;
                if (lpIOContext->nSentBytes < lpIOContext->nTotalBytes) 
                    {
                    // the previous write operation didn't send all the data,
                    // post another send to complete the operation
                    buffSend.buf = lpIOContext->Buffer + lpIOContext->nSentBytes;
                    buffSend.len = lpIOContext->nTotalBytes - lpIOContext->nSentBytes;
                    nRet = WSASend (
                        lpPerSocketContext->Socket,
                        &buffSend, 1, &dwSendNumBytes,
                        dwFlags,
                        &(lpIOContext->Overlapped), NULL);
                    if (SOCKET_ERROR == nRet && (ERROR_IO_PENDING != WSAGetLastError())) 
                        {
                        printf ("WSASend: %d\n", WSAGetLastError());
                        CloseClient(lpPerSocketContext, FALSE);
                        }
                    else if (g_bVerbose)
                        {
                        printf("WorkerThread %d: Socket(%d) Send partially completed (%d bytes), Recv posted\n", 
                            GetCurrentThreadId(), lpPerSocketContext->Socket, dwIoSize);
                        }
                    }
                else
                    {
                    // previous write operation completed for this socket, post another recv
                    lpIOContext->IOOperation = ClientIoRead; 
                    dwRecvNumBytes = 0;
                    dwFlags = 0;
                    buffRecv.buf = lpIOContext->Buffer,
                    buffRecv.len = MAX_BUFF_SIZE;
                    nRet = WSARecv(
                        lpPerSocketContext->Socket,
                        &buffRecv, 1, &dwRecvNumBytes,
                        &dwFlags,
                        &lpIOContext->Overlapped, NULL);
                    if (SOCKET_ERROR == nRet && (ERROR_IO_PENDING != WSAGetLastError())) 
                        {
                        printf ("WSARecv: %d\n", WSAGetLastError());
                        CloseClient(lpPerSocketContext, FALSE);
                        }
                    else if (g_bVerbose)
                        {
                        printf("WorkerThread %d: Socket(%d) Send completed (%d bytes), Recv posted\n", 
                            GetCurrentThreadId(), lpPerSocketContext->Socket, dwIoSize);
                        }
                    }
                break;

            } //switch
        } //while
    return(0);
    } 




//  Allocate a context structures for the socket and add the socket to the IOCP.  
//  Additionally, add the context structure to the global list of context structures.
//
PPER_SOCKET_CONTEXT UpdateCompletionPort(
    SOCKET sd,
    IO_OPERATION ClientIo,
    BOOL bAddToList
    )
    {
    PPER_SOCKET_CONTEXT lpPerSocketContext;

    
    lpPerSocketContext = CtxtAllocate(sd, ClientIo);
    if (lpPerSocketContext == NULL) 
        return(NULL);

    g_hIOCP = CreateIoCompletionPort((HANDLE)sd, g_hIOCP, (DWORD_PTR)lpPerSocketContext, 0);
    if (NULL == g_hIOCP) 
        {
        printf("CreateIoCompletionPort: %d\n", GetLastError());
        if (lpPerSocketContext->pIOContext)
            HeapFree(GetProcessHeap(), 0, lpPerSocketContext->pIOContext);
        HeapFree(GetProcessHeap(), 0, lpPerSocketContext);
        return(NULL);
        }

    //The listening socket context (bAddToList is FALSE) is not added to the list.
    //All other socket contexts are added to the list.
    if (bAddToList) CtxtListAddTo(lpPerSocketContext);

    if (g_bVerbose)
        printf("UpdateCompletionPort: Socket(%d) added to IOCP\n", lpPerSocketContext->Socket);

    return(lpPerSocketContext);
    }




//  Close down a connection with a client.  This involves closing the socket (when 
//  initiated as a result of a CTRL-C the socket closure is not graceful).  Additionally, 
//  any context data associated with that socket is free'd.
//
VOID
CloseClient (
    PPER_SOCKET_CONTEXT lpPerSocketContext,
    BOOL                bGraceful
    )
    {
    EnterCriticalSection(&g_CriticalSection);
    if (lpPerSocketContext) 
		{
		if (g_bVerbose)
			printf("CloseClient: Socket(%d) connection closing (graceful=%s)\n",
			lpPerSocketContext->Socket, (bGraceful?"TRUE":"FALSE"));
		if (!bGraceful) 
			{
			// force the subsequent closesocket to be abortative.
			LINGER  lingerStruct;

			lingerStruct.l_onoff = 1;
			lingerStruct.l_linger = 0;
			setsockopt(lpPerSocketContext->Socket, SOL_SOCKET, SO_LINGER,
						(char *)&lingerStruct, sizeof(lingerStruct) );
			}
		if (lpPerSocketContext->pIOContext->SocketAccept != INVALID_SOCKET)
			{
			closesocket(lpPerSocketContext->pIOContext->SocketAccept);
			lpPerSocketContext->pIOContext->SocketAccept = INVALID_SOCKET;
			};

		closesocket(lpPerSocketContext->Socket);
		CtxtListDeleteFrom(lpPerSocketContext);
		lpPerSocketContext = NULL;
		}
    else
        {
        printf("CloseClient: lpPerSocketContext is NULL\n");
        }
    LeaveCriticalSection(&g_CriticalSection);
    return;    
    } 




// Allocate a socket context for the new connection.  
//
PPER_SOCKET_CONTEXT CtxtAllocate(
    SOCKET          sd, 
    IO_OPERATION    ClientIO
    )
    {
    PPER_SOCKET_CONTEXT lpPerSocketContext;


    EnterCriticalSection(&g_CriticalSection);
    lpPerSocketContext = (PPER_SOCKET_CONTEXT)HeapAlloc(
        GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PER_SOCKET_CONTEXT));
    if ( lpPerSocketContext) 
		{
		lpPerSocketContext->pIOContext = (PPER_IO_CONTEXT)HeapAlloc(
			GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PER_IO_CONTEXT));
		if (lpPerSocketContext->pIOContext) 
			{
			lpPerSocketContext->Socket = sd;
			lpPerSocketContext->pCtxtBack = NULL;
			lpPerSocketContext->pCtxtForward = NULL;

			lpPerSocketContext->pIOContext->Overlapped.Internal = 0;
			lpPerSocketContext->pIOContext->Overlapped.InternalHigh = 0;
			lpPerSocketContext->pIOContext->Overlapped.Offset = 0;
			lpPerSocketContext->pIOContext->Overlapped.OffsetHigh = 0;
			lpPerSocketContext->pIOContext->Overlapped.hEvent = NULL;
			lpPerSocketContext->pIOContext->IOOperation = ClientIO;
			lpPerSocketContext->pIOContext->pIOContextForward = NULL;
			lpPerSocketContext->pIOContext->nTotalBytes = 0;
			lpPerSocketContext->pIOContext->nSentBytes  = 0;
			lpPerSocketContext->pIOContext->wsabuf.buf  = lpPerSocketContext->pIOContext->Buffer;
			lpPerSocketContext->pIOContext->wsabuf.len  = sizeof(lpPerSocketContext->pIOContext->Buffer);
			lpPerSocketContext->pIOContext->SocketAccept = INVALID_SOCKET;
			}
		else 
			{
			HeapFree(GetProcessHeap(), 0, lpPerSocketContext);
			printf("HeapAlloc PER_IO_CONTEXT Failed: %d\n", GetLastError());
			}

		}
    else
        {
        printf("HeapAlloc PER_SOCKET_CONTEXT Failed: %d\n", GetLastError());
        return(NULL);
        }


	LeaveCriticalSection(&g_CriticalSection);
	return(lpPerSocketContext);
    }





//  Add a client connection context structure to the globnal list of context structures.
//
VOID CtxtListAddTo (
    PPER_SOCKET_CONTEXT lpPerSocketContext
    )
    {
    PPER_SOCKET_CONTEXT     pTemp;


    EnterCriticalSection(&g_CriticalSection);
    if (g_pCtxtList == NULL) 
        {  
        // add the first node to the linked list
        lpPerSocketContext->pCtxtBack    = NULL;
        lpPerSocketContext->pCtxtForward = NULL;
        g_pCtxtList = lpPerSocketContext;
        }
    else 
        {
        // add node to head of list

        pTemp = g_pCtxtList;
        
        g_pCtxtList = lpPerSocketContext;
        lpPerSocketContext->pCtxtBack    = pTemp;
        lpPerSocketContext->pCtxtForward = NULL;    



        pTemp->pCtxtForward = lpPerSocketContext;
        }
    LeaveCriticalSection(&g_CriticalSection);
    return;
    }




//  Remove a client context structure from the global list of context structures.
//
VOID CtxtListDeleteFrom(
    PPER_SOCKET_CONTEXT lpPerSocketContext
    )
    {
    PPER_SOCKET_CONTEXT pBack;
    PPER_SOCKET_CONTEXT pForward;
    PPER_IO_CONTEXT     pNextIO     = NULL;
    PPER_IO_CONTEXT     pTempIO     = NULL;

    EnterCriticalSection(&g_CriticalSection);
    if (lpPerSocketContext) 
		{
		pBack       = lpPerSocketContext->pCtxtBack;
		pForward    = lpPerSocketContext->pCtxtForward;

		if (pBack == NULL && pForward == NULL) 
			{ 
			// This is the only node in the list to delete
			g_pCtxtList = NULL;
			}
		else if (pBack == NULL && pForward != NULL) 
			{ 
			// This is the start node in the list to delete
			pForward->pCtxtBack = NULL;
			g_pCtxtList = pForward;
			}
		else if (pBack != NULL && pForward == NULL) 
			{ 
			// This is the end node in the list to delete
			pBack->pCtxtForward = NULL;
			}
		else if (pBack && pForward) 
			{ 
			// Neither start node nor end node in the list
			pBack->pCtxtForward = pForward;
			pForward->pCtxtBack = pBack;
			}

		// Free all i/o context structures per socket
		pTempIO = (PPER_IO_CONTEXT)(lpPerSocketContext->pIOContext);
		do 
			{
			pNextIO = (PPER_IO_CONTEXT)(pTempIO->pIOContextForward);
			if (pTempIO) 
				{
				//The overlapped structure is safe to free when only the posted i/o has
				//completed. Here we only need to test those posted but not yet received 
				//by PQCS in the shutdown process.
				if (g_bEndServer) 
					while (!HasOverlappedIoCompleted((LPOVERLAPPED)pTempIO)) Sleep(0);
				HeapFree(GetProcessHeap(), 0, pTempIO);
				pTempIO = NULL;
				}
			pTempIO = pNextIO;
			} while (pNextIO);
    
		HeapFree(GetProcessHeap(), 0, lpPerSocketContext);
		lpPerSocketContext = NULL;
		}
    else 
        {
        printf("CtxtListDeleteFrom: lpPerSocketContext is NULL\n");
        }
    LeaveCriticalSection(&g_CriticalSection);

    return;
    }



//  Free all context structure in the global list of context structures.
//
VOID CtxtListFree()
    {
    PPER_SOCKET_CONTEXT     pTemp1, pTemp2;

    EnterCriticalSection(&g_CriticalSection);
    pTemp1 = g_pCtxtList; 
    while (pTemp1) 
        {
        pTemp2 = pTemp1->pCtxtBack;
        CloseClient(pTemp1, FALSE);
        pTemp1 = pTemp2;
        }
    LeaveCriticalSection(&g_CriticalSection);
    return;
    }




