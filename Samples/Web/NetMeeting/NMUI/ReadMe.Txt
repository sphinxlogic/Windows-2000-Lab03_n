------------------------------------------------------------------
         Microsoft NetMeeting SDK 2.1 NMUI Readme File
                           November 1997
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1997

CONTENTS
========

OVERVIEW OF THE NMUI SAMPLE
BUILDING THE NMUI SAMPLE


OVERVIEW OF THE NMUI SAMPLE
===========================

NMUI is a Windows sample that demonstrates how easy it is to replace
the standard NetMeeting user interface with another.  This sample uses 
the NetMeeting OCX to provide conference management, file transfer, 
application sharing capabilites.  


BUILDING THE NMUI SAMPLE
========================

Building the sample application requires VC++ Version 5.0 or later.

To build the sample from Visual C++, open the project makefile (nmui.mak) 
as a Microsoft VC++ project, and build as usual.  The NetMeeting SDK 
directories must be added to your VC++ environment.

If your DOS environment is correctly configured, you can build the sample
from the command line by typing "nmake".  The DOS path, include and lib
environment variables must point to the VC installation and the 
NetMeeting SDK directories.


Notes: 

