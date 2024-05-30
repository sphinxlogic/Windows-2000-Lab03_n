4GT RAM Tuning Demo

SUMMARY
=======

This sample consists of a Windows console application which demonstrates
4GT (4 Gigabyte Tuning) on Windows NT Server Enterprise Edition (NT Server EE)
version 4.0 with Service Pack 3 (or later).

FILES
=====

MakeFile
ReadMe.txt
4GT.c

MORE INFORMATION
================

With the standard Windows NT Server product, the per-process address limit is
2 GB. On NT Server EE, 4GT increases this limit to 3 GB without introducing new
APIs. 4GT does this by reducing the potential RAM allocated to the Windows NT
kernel from 2 GB to 1 GB. This feature benefits applications that run on
powerful computers with more than 2 GB of physical RAM and that can take
advantage of a larger address space.

NOTE: NT Server EE supports 4GT on Intel architecture servers only.

The changes to support 4GT are done at both the system and application
levels. On the system level, you must modify the Boot.ini file to enable 4GT
by adding the /3GB parameter to the startup line. On the application level,
executables that must see the 3 GB address space are required to have the bit
IMAGE_FILE_LARGE_ADDRESS_AWARE set in their image header. The Microsoft Visual
C++ 5.0 linker has a new switch (/LARGEADDRESSAWARE) to link executables with
this bit. The bit can also be set using the Imagecfg command-line tool that is
included in the Support folder on the NT Server EE compact disc. Simply type
the following at a command prompt:

   Imagecfg -l <filename>

For additional information on 4GT, refer to article Q171793 "Information on
Application Use of 4GT RAM Tuning" in the Microsoft Knowledge Base.

To verify that your linker supports the /LARGEADDRESSAWARE switch, type
link /? at the command prompt and verify that the version is at least 5.11.7351
and that the /LARGEADDRESSAWARE option appears in the list of linker options.

