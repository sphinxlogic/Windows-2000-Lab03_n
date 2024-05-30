This module illustrates the Win32 fiber APIs.

This example implements a fiber based file copy operation.  Note that
a number of different techiques exists for copying files programmatically;
this sample simply illustrates the fiber APIs.

This example makes use of a fiber data structure which is used to
determine the behavior and state of the fiber.  One data structure
exists for each fiber; the pointer to the data structure is passed
to the fiber at fiber creation time via the lpParameter fiber parameter.

The executing thread in the process makes a call to ConvertThreadToFiber,
which allows fibers to be scheduled by the caller.  This also allows
the resultant fiber to be scheduled by another fiber.

Next, two additional fibers are created, one fiber which performs read
operations against a specified file, and another fiber which performs
the write operations against a specified file.

The primary fiber then schedules the read fiber.  After a succesful
read, the read fiber schedules the write fiber.  After a succesful write
in the write fiber, the write fiber schedules the read fiber.  When
the read/write cycle has completed, the primary fiber is scheduled,
which results in the display of the read/write status. If an error occurs
during the read or write fibers, the primary fiber is scheduled and status
of the read/write is displayed.

The fibers, fiber data structures, and file handles are then freed
prior to process termination.

