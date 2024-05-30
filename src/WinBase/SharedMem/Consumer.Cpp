/*---------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 Microsoft Corporation.  All rights reserved.

consumer.cpp

Contents:
   The consumer process of the producer/consumer sample.  This sample shows
   how to use file mappings to implement a shared memory solution for the
   bounded-buffer producer/consumer problem.

Usage:
   To run this application, specify the shared memory name as a command-line
   parameter as follows:

      consumer memname

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



void ConsumeItem (int nItem);

BOOL WINAPI CtrlHandler (DWORD dwCtrlType);


bool g_fDone = false;

/*---------------------------------------------------------------------------
main (argc, argv)

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
   int   fResult = FAILURE;

   HANDLE       hMap           = 0;
   const char * pSharedMemName = 0;

   QUEUE<int> * pQueue;
   HANDLE       hFullSem   = 0,
                hEmptySem  = 0;
   HANDLE       hMutexLock = 0;

   int          item; /* used to hold data that's removed from queue */


   /*
      Validate command-line arguments. The last argument is the shared
      memory name.
   */
   if (argc != 2)
   {
      std::cerr << "usage: consumer <sharedmemname>\n";
      return FAILURE;
   }
   pSharedMemName = argv[argc-1];


   /*
      Open shared memory and producer/consumer synchronization objects.  If
      can't, exit.
   */
   hMap =  OpenFileMapping (FILE_MAP_WRITE, 0, pSharedMemName);
   if (!hMap)
      goto DONE;

   pQueue = (QUEUE<int> *)MapViewOfFile (hMap, FILE_MAP_WRITE, 0, 0, 0);
   if (!pQueue)
      goto DONE;

   hFullSem   = OpenSemaphore (SEMAPHORE_ALL_ACCESS, FALSE, FULL_SEM_NAME);
   hEmptySem  = OpenSemaphore (SEMAPHORE_ALL_ACCESS, FALSE, EMPTY_SEM_NAME);
   hMutexLock = OpenMutex (MUTEX_ALL_ACCESS, FALSE, QUEUE_LOCK_NAME);

   if (!hFullSem || !hEmptySem || !hMutexLock)
      goto DONE;


   /*
      Remove items from the queue and consume them until the user says stop.
      Use a console control handler to signal it's time to stop
   */
   SetConsoleCtrlHandler (CtrlHandler, TRUE);
   std::cerr << "Type Ctrl-C to exit\n";

   while (!g_fDone)
   {
      // if queue is empty and we time out, see if we should exit.
      if (WaitForSingleObject (hEmptySem, 1000) != WAIT_OBJECT_0)
         continue;

      WaitForSingleObject (hMutexLock, INFINITE);

      if (!QueueRemoveItem (pQueue, &item))
         std::cout << "couldn't remove item from queue!\n";

      ReleaseMutex (hMutexLock);
      ReleaseSemaphore (hFullSem, 1, 0);  // signal producer that queue has empty slot.

      ConsumeItem (item);
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
      printf ("couldn't share memory named %s\n", pSharedMemName);

   return (fResult);
}


/*---------------------------------------------------------------------------
ConsumeItem( nItem )

Consumes a single item by printing it to stdout.

Parameters
   nItem
      Item to be consumed.
---------------------------------------------------------------------------*/
void ConsumeItem (int nItem)
{
   std::cout << nItem << "\n";
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

