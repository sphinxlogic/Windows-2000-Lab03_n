/*---------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 Microsoft Corporation.  All rights reserved.

producer.cpp

Contents:
   The producer process of the producer/consumer sample.  This sample shows
   how to use file mappings to implement a shared memory solution for the
   bounded-buffer producer/consumer problem.

Usage:
   To run this application, specify the shared memory name as a command-line
   parameter as follows:

      producer memname


Design Notes:
   This sample allows any number of producers and consumers to access a
   single queue in shared memory.

   The first producer creates the shared memory and sets up the queue.  The
   remaining producers and consumers open the memory and immediately start
   using the existing queue.

   When the queue is full, producers will block until the queue has an
   open slot.  When the queue is empty, consumers will block until the queue
   has an item.  In order to prevent the producers and consumers from blocking
   forever, each waits with a timeout.  If the timeout occurs, the producer
   or consumer will check to see if the user wants to exit.  If not, they
   go back to waiting.

   To determine if a user wants to exit, a console control handler looks
   for a signal.  If one occurs, it sets a flag that the producer/consumer
   loop checks.

   Since the queue is not mutually exclusive, the producers and consumers
   share a single mutex to serialize access to the queue.

Notes:
   See QUEUE.H for queue implementation details.

   This sample will not compile for C; it requires C++ even though it does
   not use classes.
---------------------------------------------------------------------------*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include "queue.h"
#include "common.h"


const int MAX_QUEUE_ITEMS = 50;

int ProduceItem (void);
BOOL WINAPI CtrlHandler (DWORD dwCtrlType);


bool g_fDone = false;


/*---------------------------------------------------------------------------
main (argc, argv)

The main program that implements the producer process of the producer/consumer
sample.

Parameters
   argc
      Count of command-line arguments, including the name of the program.
   argv
      Array of pointers to strings that contain individual command-line
      arguments.

Returns
   SUCCESS if program executed successfully, FAILURE otherwise.
---------------------------------------------------------------------------*/
int main (int argc, char **argv)
{
   int          fResult     = FAILURE;
   DWORD        dwMapResult;

   HANDLE       hMap           = 0;
   const char * pSharedMemName = 0;

   QUEUE<int> * pQueue     = 0;
   HANDLE       hFullSem   = 0,
                hEmptySem  = 0;
   HANDLE       hMutexLock = 0;

   int          item;  /* used to hold data that's put into the queue */

   /*
      Validate command-line arguments. The last argument is the shared
      memory name.
   */
   if (argc != 2)
   {
      std::cerr << "usage: producer <sharedmemname>\n";
      return FAILURE;
   }
   pSharedMemName = argv[argc-1];


   /*
      If the shared memory is not already created, create it and set up the
      queue. If the shared memory already exists, skip making the queue.

      Then, create or open the synchronization objects associated with the
      queue that are needed for an efficient solution to the producer/consumer
      with bounded buffer problem.  The initial state of producer/consumer
      synchronization objects must be:

         full semaphore count:   N for an N-item queue
         empty semaphore count:  0
         lock mutex:             unowned
   */
   hMap =  CreateFileMapping (INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0,
                              QueueComputeSize (pQueue, MAX_QUEUE_ITEMS),
                              pSharedMemName);
   dwMapResult = GetLastError();
   if (!hMap)
      goto DONE;

   pQueue = (QUEUE<int> *)MapViewOfFile (hMap, FILE_MAP_WRITE, 0, 0, 0);
   if (!pQueue)
      goto DONE;

   if (dwMapResult != ERROR_ALREADY_EXISTS)
      if (!QueueCreate (pQueue, MAX_QUEUE_ITEMS))
         goto DONE;

   hMutexLock = CreateMutex (NULL, FALSE, QUEUE_LOCK_NAME);
   hFullSem   = CreateSemaphore (NULL, pQueue->nMaxItems, pQueue->nMaxItems,
                                 FULL_SEM_NAME);
   hEmptySem  = CreateSemaphore (NULL, 0, pQueue->nMaxItems, EMPTY_SEM_NAME);
   if (!hFullSem || !hEmptySem || !hMutexLock)
      goto DONE;


   /*
      Produce items and add them to the queue until the user says stop.
      Use a console control handler to signal it's time to stop
   */
   SetConsoleCtrlHandler (CtrlHandler, TRUE);
   std::cerr << "Type Ctrl-C to exit\n";

   item = ProduceItem();

   while (!g_fDone)
   {
      // if queue is full and we time out, see if we should exit.
      if (WaitForSingleObject (hFullSem, 1000) != WAIT_OBJECT_0)
         continue;

      WaitForSingleObject (hMutexLock, INFINITE);

      QueueAddItem (pQueue, &item);

      ReleaseMutex (hMutexLock);

      ReleaseSemaphore (hEmptySem, 1, 0);  // signal consumer--queue not empty

      std::cout << item << "\n";   // print item just added but not inside lock
      item = ProduceItem();        // make next item
   }

   fResult = SUCCESS;

DONE:
   /* Clean up all opened resources before exiting. */

   if (!hFullSem)
      CloseHandle (hFullSem);

   if (!hEmptySem)
      CloseHandle (hEmptySem);

   if (!hMutexLock)
      CloseHandle (hMutexLock);

   if (pQueue)
      UnmapViewOfFile (pQueue);

   if (hMap)
      CloseHandle (hMap);

   if (fResult == FAILURE)
      std::cout << "couldn't share memory named " << pSharedMemName << "\n";

   return (fResult);
}


/*---------------------------------------------------------------------------
ProduceItem( )

Produces a single item.

Returns
   A new item.
---------------------------------------------------------------------------*/
int ProduceItem (void)
{
   int item;

   item = (int)GetCurrentProcessId();
   return (item);
}


/*---------------------------------------------------------------------------
CtrlHandler( dwCtrlType )

Captures the console control signals such as Ctrl+C or Ctrl+Break sent by
the user.  Then it signals the producer loop that the user would like to
exit.

Parameters
   dwCtrlType
      The console control signal that was generated.

Returns
   Always returns true because it handles all console control signals.
---------------------------------------------------------------------------*/
BOOL WINAPI CtrlHandler (DWORD dwCtrlType)
{
   /* For any event, signal producer loop that it's time to stop. */
   g_fDone = true;

   return TRUE;
}

