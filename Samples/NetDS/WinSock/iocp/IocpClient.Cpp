// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      iocpclient.cpp
//
// Abstract:
//      Use the -? commandline switch to determine available options.
//
//      This application is a very simple minded program that sends buffers of
//      data to a server and waits for the server to echo the data back and then
//      compares the first and last byte of the buffers.  The destination server
//      can be specified using the (-n) option and the destination port using the 
//      (-e) option.  The size of the buffer to send is specified using the (-b)
//      option which is in 1k increments.  Multiple threads can be spawned to hit
//      the server.
//
//      Please note that spawning multiple threads is not a scalable way
//      to handle multiple socket connections.  This sample was built for the
//      express purpose of providing a simple and easy to understand client to 
//      pound on the iocp socket server.  
//
//      Another point worth noting is that the Win32 API CreateThread does not 
//      initialize the C Runtime and therefore, C runtime functions such as 
//      printf have been avoid or rewritten (see myprintf) to use just Win32 APIs.
//
// Entry Points:
//      main - this is where it all starts
//
// Build:
//      Use the headers and libs from the Jan98 Platform SDK or later.
//      Link with ws2_32.lib
//      
//  Author: Wei Hua, Barry Butterklee - Microsoft Developer Support
//
//


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define MAXTHREADS 64


typedef struct _OPTIONS
    {
    CHAR            szHostname[64];
    unsigned short  port;
    int             nTotalThreads;
    int             nBufSize;
    BOOL            bVerbose;
    } OPTIONS;

typedef struct THREADINFO
    {
    HANDLE hThread[MAXTHREADS];
    SOCKET sd[MAXTHREADS];
    } THREADINFO;


static OPTIONS default_options = {"localhost", 5001, 1, 4096, FALSE};
static OPTIONS g_Options;
static THREADINFO g_ThreadInfo;
static BOOL         g_bEndClient = FALSE;


static BOOL WINAPI CtrlHandler (DWORD dwEvent);
static BOOL ValidOptions(char *argv[], int argc);
static VOID Usage(CHAR *szProgramname, OPTIONS *pOptions);
static DWORD WINAPI EchoThread(LPVOID lpParameter);
static BOOL CreateConnectedSocket(int nThreadNum);
static BOOL SendBuffer(int nThreadNum, CHAR *outbuf);
static BOOL RecvBuffer(int nThreadNum, CHAR *inbuf);
static int myprintf(const char *lpFormat, ...);



int main(int argc, char *argv[])
    {
    OSVERSIONINFO   verInfo = {0};
    WSADATA WSAData; 
    DWORD   dwThreadId;
    DWORD   dwRet;
    BOOL    bInitError = FALSE;
    int     nThreadNum[MAXTHREADS];
    int     i, nRet;


    verInfo.dwOSVersionInfoSize = sizeof(verInfo);
    GetVersionEx(&verInfo);
    if (VER_PLATFORM_WIN32_WINDOWS == verInfo.dwPlatformId)
        {
        // Since this application can heavily stress system resources
        // we decided to limit running it on NT.
        myprintf("Please run %s only on NT, thank you\n", argv[0]);
        exit(0);
        }

    for (i=0; i<MAXTHREADS; i++)
        {
        g_ThreadInfo.sd[i] = INVALID_SOCKET;
        g_ThreadInfo.hThread[i] = NULL;
        }

    if (!ValidOptions(argv, argc))
        exit(1);

    if ((nRet = WSAStartup(MAKEWORD(2,2), &WSAData)) != 0)
        {
        myprintf("WSAStartup failed: %d", nRet);
        exit(1);
        }

    // be able to gracefully handle CTRL-C and close handles
    if (!SetConsoleCtrlHandler (CtrlHandler, TRUE))
        {
        myprintf ("SetConsoleCtrlHandler: %d\n", GetLastError());
        WSACleanup();
        exit(1);
        }

    // spawn the threads 
    for (i=0; i<g_Options.nTotalThreads && !bInitError; i++)
        {
        // if CTRL-C is pressed before all the sockets have connected, closure of
        // the program could take a little while, especially if the server is 
        // down and we have to wait for connect to fail.  Checking for this
        // global flag allows us to shortcircuit that.
        if (g_bEndClient)
            break;
        else if (CreateConnectedSocket(i))
            {
            // a unique memory location needs to be passed into each thread, 
            // otherwise the value would change by the time all the threads 
            // get a chance to run.
            nThreadNum[i] = i;
            g_ThreadInfo.hThread[i] = CreateThread(NULL, 0, EchoThread, (LPVOID)&nThreadNum[i], 0, &dwThreadId);
            if (NULL == g_ThreadInfo.hThread[i]) 
                {
                myprintf("CreateThread(%d): %d\n", i, GetLastError());
                bInitError = TRUE;
                break;
                }
            }
        }

    if (!bInitError)
        {
        // wait for the threads to exit
        dwRet = WaitForMultipleObjects(g_Options.nTotalThreads, g_ThreadInfo.hThread, TRUE, INFINITE);
        if (WAIT_FAILED == dwRet)
            myprintf("WaitForMultipleObject: %d\n", GetLastError());
        }

    myprintf("Closing handles and sockets\n");
    for (i=0; i<g_Options.nTotalThreads; i++)
        {
        if (INVALID_SOCKET != g_ThreadInfo.sd[i])
            {
            // force the subsequent closesocket to be abortative.
            LINGER  lingerStruct;

            lingerStruct.l_onoff = 1;
            lingerStruct.l_linger = 0;
            setsockopt(g_ThreadInfo.sd[i], SOL_SOCKET, SO_LINGER,
                    (char *)&lingerStruct, sizeof(lingerStruct));
            closesocket(g_ThreadInfo.sd[i]);
  
            dwRet = WaitForSingleObject(g_ThreadInfo.hThread[i], INFINITE);
        
            if (WAIT_FAILED == dwRet)
                myprintf("WaitForSingleObject: %d\n", GetLastError());
            if (NULL != g_ThreadInfo.hThread[i])
                CloseHandle(g_ThreadInfo.hThread[i]);
            }
        }
    WSACleanup();
    return(0);
    }




// Abstract:
//     This is the thread that continually sends and receives a specific size
//     buffer to the server.  Upon receipt of the echo from the server, a
//     simple check is performed to check the integrity of the transfer.
//
static DWORD WINAPI EchoThread(
    LPVOID lpParameter
    )
    {
    CHAR *inbuf  = NULL;
    CHAR *outbuf = NULL;
    int *pArg = (int *)lpParameter;
    int nThreadNum = *pArg;


    myprintf("Starting thread %d\n", nThreadNum);

    if ((inbuf = (char *)HeapAlloc(GetProcessHeap(), 0, g_Options.nBufSize)) &&
        (outbuf = (char *)HeapAlloc(GetProcessHeap(), 0, g_Options.nBufSize)))
        {
        FillMemory(outbuf, g_Options.nBufSize, nThreadNum);

        while (TRUE)
            {
            // just continually send and wait for the server to echo the data
            // back.  Just do a simple minded comparison.
            if (SendBuffer(nThreadNum, outbuf) && 
                RecvBuffer(nThreadNum, inbuf))
                {
                if ((inbuf[0] == outbuf[0]) && 
                    (inbuf[g_Options.nBufSize-1] == outbuf[g_Options.nBufSize-1]))
                    {
                    if (g_Options.bVerbose)
                        myprintf("ack(%d)\n", nThreadNum);
                    }
                else
                    {
                    myprintf("nak(%d) in[0]=%d, out[0]=%d in[%d]=%d out[%d]%d\n", 
                            nThreadNum,
                            inbuf[0], outbuf[0], 
                            g_Options.nBufSize-1, inbuf[g_Options.nBufSize-1], 
                            g_Options.nBufSize-1, outbuf[g_Options.nBufSize-1]);
                    break;
                    }
                }
            else
                break;
            }
        }

    if (inbuf)
        HeapFree(GetProcessHeap(), 0, inbuf);
    if (outbuf)
        HeapFree(GetProcessHeap(), 0, outbuf);

    return(TRUE);
    }




// Abstract:
//     Create a socket and connect to the server process.
//
static BOOL CreateConnectedSocket(
    int nThreadNum
    )
    {
    BOOL bRet = TRUE;
    int nRet;
    SOCKADDR_IN addr_srv;
    LPHOSTENT   lpHostEnt;


    g_ThreadInfo.sd[nThreadNum] = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == g_ThreadInfo.sd[nThreadNum])
        {
        myprintf("socket %d", WSAGetLastError());
        bRet = FALSE;
        }
    else
        {
        ZeroMemory((PVOID)&addr_srv, sizeof(addr_srv));
        addr_srv.sin_family = PF_INET;
        addr_srv.sin_port = htons(g_Options.port);
        addr_srv.sin_addr.s_addr = inet_addr(g_Options.szHostname);
        if (INADDR_NONE == addr_srv.sin_addr.s_addr)
            {
            // the host name for the server is not in dot format,
            // therefore try it just as a string
            if (NULL == (lpHostEnt = gethostbyname(g_Options.szHostname)))
                myprintf("gethostbyname %d for %s", WSAGetLastError(), g_Options.szHostname);
            else
                CopyMemory(&addr_srv.sin_addr, 
                       lpHostEnt->h_addr_list[0],
                       lpHostEnt->h_length);
            }

        nRet = connect(g_ThreadInfo.sd[nThreadNum], (LPSOCKADDR)&addr_srv, sizeof(addr_srv));
        if (SOCKET_ERROR == nRet)
            {
            myprintf("connect(thread %d) %d\n", nThreadNum, WSAGetLastError());
            bRet = FALSE;
            }
        else
            myprintf("connected(thread %d)\n", nThreadNum);
        }

    return(bRet);
    }




// Abstract:
//     Send a buffer - keep send'ing until the requested amount of
//     data has been sent or the socket has been closed or error.
//
static BOOL SendBuffer(
    int nThreadNum,
    CHAR *outbuf
    )
    {
    BOOL bRet = TRUE;
    CHAR *bufp = outbuf;
    int nTotalSend = 0;
    int nSend;

    while (nTotalSend < g_Options.nBufSize)
        {
        nSend = send(g_ThreadInfo.sd[nThreadNum], bufp, g_Options.nBufSize - nTotalSend, 0);
        if (SOCKET_ERROR == nSend)
            {
            myprintf("send(thread=%d) %d\n", nThreadNum, WSAGetLastError());
            bRet = FALSE;
            break;
            }
        else if (nSend == 0)
            {
            myprintf("connection closed\n");
            bRet = FALSE;
            break;
            }
        else
            {
            nTotalSend += nSend;
            bufp += nSend;
            }
        }
    
    return(bRet);
    }



// Abstract:
//     Receive a buffer - keep recv'ing until the requested amount of
//     data has been received or the socket has been closed or error.
//
static BOOL RecvBuffer(
    int nThreadNum,
    CHAR *inbuf
    )
    {
    BOOL bRet = TRUE;
    CHAR *bufp = inbuf;
    int nTotalRecv = 0;
    int nRecv;

    
    while (nTotalRecv < g_Options.nBufSize)
        {
        nRecv = recv(g_ThreadInfo.sd[nThreadNum], bufp, g_Options.nBufSize - nTotalRecv, 0);
        if (SOCKET_ERROR == nRecv)
            {
            myprintf("recv(thread=%d) %d\n", nThreadNum, WSAGetLastError());
            bRet = FALSE;
            break;
            }
        else if (nRecv == 0)
            {
            myprintf("connection closed\n");
            bRet = FALSE;
            break;
            }
        else
            {
            nTotalRecv += nRecv;
            bufp += nRecv;
            }
        }
    
    return(bRet);
    }




// Abstract:
//      Verify options passed in and set options structure accordingly.
//
static BOOL ValidOptions(
    char *argv[], 
    int argc
    )
    {


    g_Options = default_options;

    for (int i=1; i<argc; i++)
        {
        if ((argv[i][0] == '-') || (argv[i][0] == '/') ) 
            {
            switch(tolower(argv[i][1])) 
                {
                case 'b' :
                    if (lstrlen(argv[i]) > 3)
                        g_Options.nBufSize = 1024*atoi(&argv[i][3]);
                    break;

                case 'e' :
                    if (lstrlen(argv[i]) > 3)
                        g_Options.port = atoi(&argv[i][3]);
                    break;

                case 'n' : 
                    if (lstrlen(argv[i]) > 3)
                        lstrcpy(g_Options.szHostname, &argv[i][3]);
                    break;

                case 't' :
                    if (lstrlen(argv[i]) > 3)
                        g_Options.nTotalThreads = min(MAXTHREADS, atoi(&argv[i][3]));
                    break;

                case 'v' :
                    g_Options.bVerbose = TRUE;
                    break;

                case '?' :
                    Usage(argv[0], &default_options);
                    return(FALSE);
                    break;

                default:
                    myprintf("  unknown options flag %s\n", argv[i]);
                    Usage(argv[0], &default_options);
                    return(FALSE);
                    break;
                }
            }
        else
            {
            myprintf("  unknown option %s\n", argv[i]);
            Usage(argv[0], &default_options);
            return(FALSE);
            }
        }

    return(TRUE);
    }





// Abstract:
//      Print out usage table for the program
//
static VOID Usage(CHAR *szProgramname, OPTIONS *pOptions)
    {
    myprintf("usage:\n%s [-b:#] [-e:#] [-n:host] [-t:#] [-v]\n",
        szProgramname);
    myprintf("%s -?\n", szProgramname);
    myprintf("  -?\t\tDisplay this help\n");
    myprintf("  -b:bufsize\tSize of send/recv buffer; in 1K increments (Def:%d)\n",
        pOptions->nBufSize);
    myprintf("  -e:port\tEndpoint number (port) to use (Def:%d)\n",
        pOptions->port);
    myprintf("  -n:host\tAct as the client and connect to 'host' (Def:%s)\n",
        pOptions->szHostname);
    myprintf("  -t:#\tNumber of threads to use\n");
    myprintf("  -v\t\tVerbose, print an ack when echo received and verified\n");
    return;
    }




static BOOL WINAPI CtrlHandler (
    DWORD dwEvent
    )
    {
    int i;

    switch (dwEvent) 
        {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
        case CTRL_CLOSE_EVENT:
            g_bEndClient = TRUE;
            for (i=0; i<g_Options.nTotalThreads; i++)
                {
                // force the subsequent closesocket to be abortative.
                LINGER  lingerStruct;

                lingerStruct.l_onoff = 1;
                lingerStruct.l_linger = 0;
                setsockopt(g_ThreadInfo.sd[i], SOL_SOCKET, SO_LINGER,
                    (char *)&lingerStruct, sizeof(lingerStruct));
                closesocket(g_ThreadInfo.sd[i]);
                g_ThreadInfo.sd[i] = INVALID_SOCKET;
                }
            break;

        default:
            // unknown type--better pass it on.
            return (FALSE);
        }
    return (TRUE);
    }




static int myprintf ( 
    const char *lpFormat, 
    ... 
    )
    {
    int     nLen, nRet ;
    char        cBuffer[512] ;
    va_list     arglist ;
    HANDLE  hOut ;  

    va_start(arglist, lpFormat);

    nLen = lstrlen( lpFormat ) ;
    nRet = wvsprintf( cBuffer, lpFormat, arglist );
    
    if(nRet >= nLen || GetLastError() == 0)
        {           
        hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
        if( hOut != INVALID_HANDLE_VALUE  )
            WriteConsole( hOut, cBuffer, lstrlen(cBuffer), (LPDWORD)&nLen, NULL ) ; 
        }
    
    return nLen ;
    }
