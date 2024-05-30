/*---------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 Microsoft Corporation.  All rights reserved.

queue.h

The queue is a ring buffer of N items.  The queue is a bounded size and cannot
grow.

Contents:
   QueueCreate        - Initializes a piece of memory into a queue
   QueueComputeSize   - Returns the size of the memory needed to hold a
                        queue of N items
   QueueAddItem       - Adds an item to the queue
   QueueRemoveItem    - Removes an item from the queue

Design notes:
   This queue interface is templatized so that the queue can take a variety
   of data types.

   Queues can reside in shared memory so they can be shared between processes.
   This implies they can be in multiple address spaces, and at a different base
   address in each process.  Therefore:

      1) This implementation uses an array-based implementation instead of a
         pointer implementation.

      2) This implementation does not use C++ objects.  The C++ compiler does
         not guarantee that entire objects will be placed entirely within the
         shared memory.  Specifically, vtables will not be.

   These queues are not reentrant and this implementation does not serialize
   access because enforcing any locking behavior may result in unnecessary
   overhead.  (i.e. when the queue is not shared, then no locking is needed)
   If these queues can be reentered (such as by multiple threads or processes),
   the calling code must provide synchronization tailored to its needs.
   Examples of such synchronization include mutexes, critical sections, or
   spin locks.
---------------------------------------------------------------------------*/

#if !defined (INC_QUEUE_H)
#define INC_QUEUE_H


#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>

template<class T> struct QUEUE
{
   int  nNumItems;    // 0
   int  nMaxItems;    // N items
   int  in;           // 0
   int  out;          // 0
   T    data[1];      // first element of queue data, full size will be N items
};


/*----------------------------------------------------------------------------
QueueCreate( pQueueBase, nNumQueueItems )

Creates a queue than can hold nNumQueueItems at once.  The caller must supply
the memory to hold the queue.  It is advised that the caller first call
QueueComputeSize to determine how much memory will be needed by the queue.

Parameters
   pQueueBase
      A pointer to memory that will contain the new queue.  This memory must
      be allocated by the caller.

   nNumQueueItems
      The maximum number of items that can be in the queue at any one time.

Return Value
   true if successfully created a queue, false if couldn't.

Notes
   This queue can be in shared memory.  It is not serialized so if multiple
   threads or processes can use the queue simultaneously, they need to
   synchronize access to the queue.
----------------------------------------------------------------------------*/
template<class T> bool QueueCreate (QUEUE<T> *pQueueBase, int nNumQueueItems)
{
   bool fResult;

   __try
   {
      pQueueBase->nNumItems = 0;
      pQueueBase->nMaxItems = nNumQueueItems;
      pQueueBase->in  = 0;
      pQueueBase->out = 0;

      fResult = true;
   }
   __except (EXCEPTION_EXECUTE_HANDLER)
   {
      fResult = false;
   }

   return fResult;
}


/*----------------------------------------------------------------------------
QueueComputeSize( pQueue, nNumQueueItems )

Computes the size in bytes of a queue that can hold nNumQueueItems.

Parameters
   pQueue
      Pointer of the queue to compute the size of.  Note that this pointer
      is not dereferenced, and does not need to point to allocated memory.
      It is used only to get the type (and therefore the size) of the items
      that will be stored in the queue.

   nNumQueueItems
      Maximum number of items to put into the queue.

Return Value
   The size in bytes of a queue that can hold nNumQueueItems.
----------------------------------------------------------------------------*/
template<class T> int QueueComputeSize (const QUEUE<T> *pQueue,
                                        int nNumQueueItems)
{
   return sizeof(QUEUE<T>) + ((nNumQueueItems-1) * sizeof(T));
}


/*----------------------------------------------------------------------------
QueueAddItem (pQueue, pItem )

Adds an item to the queue.  If the queue is full, this function returns
immediately (no waiting) without adding the item.

Parameters
   pQueue
      Pointer to the queue to which the item should be added.

   pItem
      Pointer to the item to add to the queue.

Return Value
   true if the item added to the queue, false if not.
----------------------------------------------------------------------------*/
template<class T> bool QueueAddItem (QUEUE<T> *pQueue, const T * pItem)
{
   // If the queue is full, return.
   if (pQueue->nNumItems == pQueue->nMaxItems)
      return false;

   /*
      Insert item, then advance in pointer to next empty slot, then update
      number of items in the queue.
   */
   pQueue->data[pQueue->in] = *pItem;
   pQueue->in = (pQueue->in +1) % pQueue->nMaxItems;
   ++pQueue->nNumItems;

   return true;
}


/*----------------------------------------------------------------------------
QueueRemoveItem( pQueue, pItem )

Removes an item from a queue.  If the queue is empty, this function returns
immediately.

Parameters
   pQueue
      Pointer to the queue from which the item should be removed.

   pItem
      Pointer to memory that will receive the item removed from the queue.

Return Value
   true if the item added to the queue, false if not.
----------------------------------------------------------------------------*/
template<class T> bool QueueRemoveItem (QUEUE<T> * pQueue, T * pItem)
{
   // if queue empty, return
   if (pQueue->nNumItems == 0)
      return false;

   // remove item, then advance out pointer to next item to remove
   *pItem = pQueue->data[pQueue->out];
   pQueue->out = (pQueue->out + 1) % pQueue->nMaxItems;
   --pQueue->nNumItems;

   return true;
}

#endif

