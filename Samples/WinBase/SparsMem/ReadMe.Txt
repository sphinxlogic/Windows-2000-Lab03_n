Sparsely Committed Memory Demo

SUMMARY
=======

The SparsMem sample demonstrates the use of sparsely committed memory in
Windows NT and Windows 95. Sparsely committed memory is useful for applications
in which two or more processes share data through a file-mapping object backed
by the paging file. It is particularly useful if the size of the shared memory
is not known and might grow to be very large.

FILES
=====

MakeFile
ReadMe.txt
Resource.h
SparsMem.c
SparsMem.ico
SparsMem.rc

MORE INFORMATION
================

This sample consists of a single application that can be run multiple times.
All instances share the same memory via a named file-mapping object. The paging
file backs the shared memory. This is an ideal situation in which to use
sparsely committed memory since the required amount of memory is not known
until runtime.

Normally, when a call is made to CreateFileMapping(), the entire block of
memory is reserved and committed all at once. However, if the SEC_RESERVE flag
is included in the protection attributes parameter, the memory is only
reserved. It can then be committed as necessary using VirtualAlloc(). (Note
that this only makes sense for memory backed by the paging file. Physical
files must have a definite size in order to be used by file-mapping objects.)

In this sample, a section of memory large enough to store 125,000 pages of data
is reserved. Assuming a page size of 4K, this is equivalent to 1/2GB of memory.
By monitoring the size of the paging file, you can verify that the memory is
only being reserved, not committed.

A dialog box serves as the user-interface for the application. The user can
commit "chunks" of data by clicking a button on this dialog box.  The CHUNK
structure consists of a BOOL which marks the block as used, a DWORD which
identifies the process ID of the process which committed the block, and a 1K
block of byte-data (although no real data is being stored in this sample).

When a process is closed, all of the chunks that it committed are zeroed. By
zeroing the memory, the BOOL variable of the CHUNK structure is false,
indicating that the block is no longer in use. Thus, when another attempt is
made to commit a chunk, the shared-memory can be scanned, and the process
making the attempt can pick up the unused block.

A "control chunk" is used to coordinate the shared memory. The CONTROLCHUNK
structure consists of a DWORD which stores the number of committed chunks and
a DWORD that stores the tick count of the last change to the shared memory.

Since we are dealing with inter-process communication, it is necessary to have
some means of coordinating write-access to the shared memory. This sample
uses a mutex for coordinating this access. Before a thread can write to any
portion of the shared memory, it must obtain ownership of the mutex.

To display results, each instance of the application scans through the
committed memory at a regular interval (1/2 second) and displays the status of
the memory in a listbox. For efficiency, the listbox is only updated if the
shared memory has changed (ie., the dwLastChange member of the control chunk
has been updated since the last refresh).
