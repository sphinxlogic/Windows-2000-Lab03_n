SHAREDMEM Bounded-Buffer Sample to Demonstrate Shared Memory Using File Mappings

Description
-----------
This sample demonstrates how to use file mappings to implement a shared memory
solution for the bounded-buffer producer/consumer problem.  It specifcally
shows you how to use the following Win32 APIs to implement code that creates
memory that can be shared by multiple processes, and how to synchronize access
to that shared memory:

   CreateFile
   CreateFileMapping
   MapViewOfFile
   UnmapViewOfFile
   CloseHandle
   CreateMutex
   CreateSemaphore
   WaitForSingleObject

This sample allows any number of producers and consumers to access a
single queue in shared memory.


Design Notes:
-------------
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

   See QUEUE.H for queue implementation details.

   This sample will not compile for C; it requires C++ even though it does
   not use classes.  It uses template functions to implement a generic queue
   data structure.


Using Shared Memory via File Mappings
-------------------------------------

In a nutshell, file mappings allow processes to create a region of virtual
memory that is backed by a specific file or the system pagefile.
The contents of the region can be paged in and out on demand just like any
other vitual memory, but will always be paged in or out of the file being
mapped.  The process that created/opened the file mapping object uses
pointers to this region to access the file's data, just as it would use
pointers to access a block of dynamically-allocated memory.

File mappings can be used for two purposes:

   1) Accessing a file's contents as though it were memory
   2) Sharing memory between processes

This sample shows an application of purpose #2

To share memory through file mappings, processes must map views of the same
file mapping object.  These views must also map the same region of the file
mapping object.

If you don't want to create a file for shared memory, use the system page file
by specifying INVALID_HANDLE_VALUE in place of the file handle in the call to
CreateFileMapping.

When each process maps a view, it will get back the base address of the view.
This base address may or may not be the same in all process's address spaces
because each process's address space is in a unique state depending on the
memory allocations it has already made, and on the DLLs it has loaded.
Therefore, don't store pointers into the shared memory unless you know that
all processes sharing the memory are using the same base address and view
length.

Since handles to Win32 objects are process-specific, don't store them in
shared memory unless each process plans to use DuplicateHandle() to make a
copy for itself.

Once two or more processes share memory, they are responsible for enforcing
their own mutually exclusive access as necessary.  Synchronization objects such
as mutexes and semaphores are good choices.  Critical sections are not objects
and are not sharable across processes, so they are not good choices.


How to Build SHAREDMEM
----------------------

Debug build:
   nmake

Release build:
   nmake "nodebug=1"


How to Execute SHAREDMEM
------------------------

From the command line:

   1) Start the producer with the shared memory name.  Use the "start" command
      as to make the producer run in a new console:
         start producer memname

   2) Start the consumer with the same shared memory name used for the
      producer.  Use the "start" command as to make the producer run in a
      new console:
         start consumer memname

   3) Start any number of producers and consumers with the shared memory name
      to have them join memory sharing.  All will use the same queue.

   4) Type Ctrl-C to stop each producer and consumer.


