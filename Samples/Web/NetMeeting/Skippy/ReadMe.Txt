------------------------------------------------------------------
         Microsoft NetMeeting SDK 2.1 SKIPPY! Readme File
                           November 1997
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1997

CONTENTS
========

OVERVIEW OF THE SKIPPY! SAMPLE
BUILDING THE SKIPPY! SAMPLE


OVERVIEW OF THE SKIPPY! SAMPLE
=============================

SKIPPY! is a COM based Internet Location Services application that allows
the user to query an ILS server for users and user information.  It 
demonstrates filtering the server results, creation of user objects and 
registration of users on a server.


BUILDING THE SKIPPY! SAMPLE
=============================

Building the sample application requires VC++ Version 5.0 or later.

To build the sample from Visual C++, open the project makefile (skippy.mak) 
as a Microsoft VC++ project, and build as usual.  The NetMeeting SDK 
directories must be added to your VC++ environment.

If your DOS environment is correctly configured, you can build the sample
from the command line by typing "nmake".  The DOS path, include and lib
environment variables must point to the VC installation and the 
NetMeeting SDK directories.


Notes: 

1) To run the SKIPPY! sample you do not need to have Microsoft 
   NetMeeting installed but you must install the ILS client support
   DLLs.  To do this, go to the REISTRB directory and run the ilsinst.exe 
   utility.  

2) User objects created on a server by this application will appear
   in a NetMeeting directory listing for that server but NetMeeting
   users will not be able to connect to them.

3) You do not need to specify IP address in the user information dialog.
   If you do not, the IP address for your machine will be used.  If you
   do, the IP Address you provide will be used.

4) User objects obtained via a call to EnumUsers cannot be used in calls to 
   EnumProtocols.  To work around this issue, call EnumUserNames and then
   GetUser on each name.

