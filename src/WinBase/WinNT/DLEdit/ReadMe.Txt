Assign Drive Letter Sample
==========================

Summary
=======
This sample consists of a command-line tool to create new drive letter
assignments and delete drive letter assignments in Windows 2000.  The drive
letter assignments created by this sample are persistent across system
reboots.

This code is useful when you want to change the drive letter that is assigned
to an NT device such as a hard disk partition or a CD-ROM drive.  It is also
useful to assign a drive letter to a newly-formatted hard disk partition


Code Techniques
===============
The Windows 2000 Mount Manager tracks drive letter to device assignments.  It
permits one drive letter assignment per NT device.  Thus, if you want to
change an existing drive's or partition's letter, you must first delete the
current letter and then you can assign the new letter.

Applications must use the Volume Mount Point API to make or remove persistent
drive letter assignments to devices.  While DefineDosDevice can make or remove
a drive letter assignment, its effect lasts only until the machine is rebooted.
As will be explained later, DefineDosDevice is used to help make persistent
drive letter assignments.

API functions demonstrated:
   DefineDosDevice
   DeleteVolumeMountPoint
   GetVolumeNameForVolumeMountPoint
   SetVolumeMountPoint

It should be noted that the volume mount point APIs all require drive letters
to have a colon and trailing backslash (e.g. X:\).  However, DefineDosDevice
requires that only the drive letter and colon be present; the trailing
backslash must not be included.

Adding a Drive Letter Assignment
--------------------------------
To assign a new drive letter to a device, use the following steps:

1) Use DefineDosDevice to make the drive letter that refers to the NT device
   name.  This defines a symbolic link from the drive letter to the NT
   device.  At this point, applications can use the drive letter to refer
   to the device.  However, this symbolic link exists only until the machine
   is rebooted.

2) Use the newly-defined drive letter to call GetVolumeNameForVolumeMountPoint
   to get the unique volume name of the NT device. This volume name has the
   format:
      \\?\Volume{GUID}\

3) Use DefineDosDevice to delete the symbolic link created in step 1.  This
   is necessary because the Mount Manager allows only a single reference to
   the device being assigned a drive letter.

4) Call SetVolumeMountPoint with the drive letter used in step 1 and the unique
   volume name obtained in step 2.  When it completes, the drive letter will
   be assigned to the drive.  This assignment will remain even when the
   machine is rebooted.

Removing a Drive Letter Assignment
----------------------------------
To delete a drive letter assignment, use DeleteVolumeMountPoint with the
drive letter to remove.


Using DLEDIT
============

How to use the utility:
   dledit <drive letter> <NT device name>    -- Adds a new drive letter
   dledit -r <drive letter>                  -- Removes a drive letter

Example usage:
   dledit e:\ \Device\CdRom0
   dledit -r f:\

This utility runs only on Windows 2000 because it uses the Volume Mount Point
API, which is available only on Windows 2000.

To run this utility, you must be logged on as a member of the Administrators
group.  If you are logged on as any other type of user, you'll get an access
denied error (5).

Building DLEDIT
===============

Use nmake from the command line.  The makefile for this sample creates
DLEDIT.EXE.


THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 Microsoft Corporation.  All rights reserved.

