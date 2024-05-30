/*-------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 Microsoft Corporation.  All rights reserved.

common.h

Purpose
   Contains code that is common to both the producer and consumer.

Contents
   Names of shared kernel objects:

      FULL_SEM_NAME     -- semaphore to make producers sleep when queue full
      EMPTY_SEM_NAME    -- semaphore to make consumers sleep when queue empty
      QUEUE_LOCK_NAME   -- mutex to enforce exclusive access to queue

   Return values for main():
      SUCCESS
      FAILURE

-------------------------------------------------------------------------*/

#if !defined (INC_COMMON_H)
#define INC_COMMON_H

/* Names of kernel objects shared between producers and consumers */
#define FULL_SEM_NAME   "PC_FULL_SEM"
#define EMPTY_SEM_NAME  "EMPTY_FULL_SEM"
#define QUEUE_LOCK_NAME "PC_LOCK_MUTEX"


/* Return values for main() */
const int   SUCCESS = 0;
const int   FAILURE = 1;



#endif
