------------------------------------------------------------------
         Microsoft NetMeeting SDK 2.1 Instcodc Readme File
                           November 1997            
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1997

CONTENTS
========

OVERVIEW OF THE SKIPPY! SAMPLE
BUILDING THE SKIPPY! SAMPLE


OVERVIEW OF THE INSTCODC SAMPLE
===============================

Instcodc demonstrates the addition, removal, and enumeration of an installed
audio NetMeeting codec, using the API provided for this purpose.


BUILDING THE INSTCODC SAMPLE
============================

Building the sample application requires VC++ Version 5.0 or later.

To build the sample from Visual C++, open the project makefile 
(instcodc.mak) as a Microsoft VC++ project, and build as usual.
The NetMeeting SDK directories must be added to your VC++ environment.

If your DOS environment is correctly configured, you can build the sample
from the command line by typing "nmake".  The DOS path, include and lib
environment variables must point to the VC installation and the 
NetMeeting SDK directories.

Notes:

1) INSTCODC.EXE must be executed in the directory where NetMeeting is 
installed.  

2) This sample should not be run while NetMeeting is running.

