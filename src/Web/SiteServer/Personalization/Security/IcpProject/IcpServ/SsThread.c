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
//  MODULE:   ssthread.s
//
//  PURPOSE:  This file contains all thread related functions for the
//            Sample Server.
//

#include "all_incl.h"

extern BOOLEAN g_bVerbose;
extern BOOLEAN g_bExit;
extern PSecurityFunctionTable g_pFuncTbl;
extern CRITICAL_SECTION    g_ContextSection;

DWORD WINAPI WorkerThread (LPVOID WorkContext);

//+----------------------------------------------------------------------------
//
//  Function:   CreateThreadsForIoCompletion
//
//  Synopsis:   This function creates twice as many threads as the number
//              of the system processor(s). These threads are created to work
//              on any completed IO with the clients.
//
//  Arguments:  hCompletionPort -   The CompletionPort handle to pass to 
//                                  the worker threads
//
//  Returns:    TRUE if at least one thread is created successfully. The server
//              is still function with at least one thread although it'll be
//              slower.
//              FALSE if no thread can be created.
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
BOOLEAN
CreateThreadsForIoCompletion (
    HANDLE hCompletionPort
    )
{
    HANDLE hThreadHandle;
    DWORD dwThreadId;
    DWORD ii;
    SYSTEM_INFO systemInfo;
    int thread_cnt = 0; // used to determine whether at least 1 thread created

    //
    // Determine how many processors there are on the system.
    //

    GetSystemInfo (&systemInfo);

    //
    // Create worker threads that will service the actual overlapped
    // I/O requests.  Create two worker threads for each processor
    // on the system.
    //

    for (ii = 0; ii < systemInfo.dwNumberOfProcessors*2; ii++)
    {
        hThreadHandle = CreateThread (NULL, 0, WorkerThread, hCompletionPort,
                    0, &dwThreadId);
        if (hThreadHandle == NULL)
        {
            CloseHandle (hCompletionPort);
            if (thread_cnt > 0)
            {
                printf (
                "ICPSERV: CreateThread Failed [%d]- Continue with %d threads\n",
                            GetLastError (), thread_cnt);
                break;
            }
            else
            {
                printf ( "ICPSERV: Failed to Create Thread [%d]\n", 
                            GetLastError ());
                return FALSE;   // return if no thread is created
            }
        }

        //
        // Close each thread handle as we open them.  We do not need
        // the thread handles.  Note that each thread will continue
        // executing.
        //
        CloseHandle (hThreadHandle);

        thread_cnt++;                  // one more threads created successfully
    }

    if (g_bVerbose)
    {
        printf ("\nICPSERV: ... Created %d threads\n", thread_cnt);
    }

    //
    // At least one thread was created successful.
    //

    return TRUE;
}

//+----------------------------------------------------------------------------
//
//  Function:   WorkerThread
//
//  Synopsis:   This function defines the processing of each worker thread.
//              Each thread waits for completed socket read or write and 
//              processes the completed I/O accordingly.
//
//  Arguments:  WorkerContext - handle to the IO Completion Port
//
//  History:    LucyC       Created                             13 July 1995
//
//-----------------------------------------------------------------------------
DWORD WINAPI
WorkerThread (
    LPVOID WorkContext
    )
{
    PCLIENT_OVERLAPPED pClientOvlp;
    HANDLE hCompletionPort = WorkContext;
    BOOL bSuccess;
    DWORD dwIoSize;
    LPOVERLAPPED lpOverlapped;
    PCLIENT_INFO pClientInfo;

    //
    // Loop servicing I/O completions.
    //
    while (TRUE)
    {
        //
        // Wait for a completed IO operation.
        //

        bSuccess = GetQueuedCompletionStatus (hCompletionPort, &dwIoSize,
                    (LPDWORD)&pClientInfo, &lpOverlapped, (DWORD)-1);

        if (g_bExit)    // Still need to work on how to make this better ???
        {
            if (g_bVerbose)
            {
                printf ("\nICPSERV: Exiting threads due to user request\n");
            }
            break;
        }

        if (!bSuccess && !lpOverlapped)
        {
            printf ("ICPSERV: GetQueuedCompletionStatus() failed [%d]\n",
                    GetLastError());
            break;
        }

        //
        // If the Client wishes to close the socket let us do so
        // Let us also release this buffer
        // BUGBUG??? Any kind of statistical data needs to be collected now.
        //
        if (dwIoSize == 0)
        {
            EnterCriticalSection(&g_ContextSection);

            if (g_bVerbose)
            {
                printf ("ICPSERV: Client <sock %d> closed connection\n\n",
                        pClientInfo->Socket);
            }

            CloseClient (pClientInfo, FALSE);
            FreeClientInfo (pClientInfo);

            LeaveCriticalSection(&g_ContextSection);

            continue;
        }

        //
        // If the IO failed, close the socket and free all client related
        // buffers and structures.
        //
        if (!bSuccess)
        {
            EnterCriticalSection(&g_ContextSection);

            if (g_bVerbose)
            {
                printf ("ICPSERV: IO Failed on Client Connection [%d]\n\n",
                        GetLastError());
            }

            CloseClient (pClientInfo, FALSE);
            FreeClientInfo (pClientInfo);

            LeaveCriticalSection(&g_ContextSection);

            continue;
        }

        pClientOvlp = (PCLIENT_OVERLAPPED) lpOverlapped;

        if (pClientOvlp->bufInfo.type == ServerRead)
        {
            //
            // A Read has completed.  Process the client message.
            // Now we go off and process the request with this thread itself
            // Will this thread Block BUGBUG???
            //

            if (g_bVerbose)
            {
                printf (
                "ICPSERV: ... Received %d bytes from client <socket %d>\n",
                        dwIoSize, pClientInfo->Socket);
            }

            ProcessClientMsg (pClientInfo, dwIoSize, pClientOvlp);
        }
        else if (pClientOvlp->bufInfo.type == ServerWrite)
        {
            if (g_bVerbose)
            {
                printf ( "ICPSERV: WriteFile Completed on sock %d\n",
                         pClientInfo->Socket);
            }

            //
            // A Write has completed.  Free up the buffer and go back to wait
            // for the next completed IO
            //
            DeleteClientOutOvlp (pClientInfo, 
                        (PCLIENT_OVERLAPPED) lpOverlapped);
        }
        else
        {
            EnterCriticalSection(&g_ContextSection);

            //
            // Absolutely unknown buffer type. This is FATAL, disconnect client
            //
            printf ("Unknown BufType: pClientInfo 0x%08x, pOvlp 0x%08x\n",
                pClientInfo, pClientOvlp);

            //
            // Close the socket and free all client related buffers and 
            // structures.
            //
            CloseClient (pClientInfo, FALSE);
            FreeClientInfo (pClientInfo);

            LeaveCriticalSection(&g_ContextSection);
        }
    }

    return 0;
}
