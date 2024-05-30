------------------------------------------------------------------
           Microsoft NetMeeting 2.1 SDK Readme File
                         November 1997            
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1997


HOW TO USE THIS DOCUMENT
========================

To view Readme.txt on screen in Windows Notepad, maximize the Notepad 
window.

To print Readme.txt, open the file in Notepad or another word processor,
and then on the File menu, click Print.


CONTENTS
========

ABOUT THIS RELEASE OF THE NETMEETING SDK
INSTALLING AND USING THE NETMEETING SDK
OVERVIEW OF THE NETMEETING SDK SAMPLES
KNOWN ISSUES


ABOUT THIS RELEASE OF THE NETMEETING SDK
========================================
This is the final release of the NetMeeting 2.1 SDK.

This release includes documentation and sample code for the following:

· A new set of objects based on the OLE Component Object Model (COM) 
  that allow developers to access the functionality of the Microsoft NetMeeting 
  platform from within COM applications.

· A new set of COM objects that allow developers to access the functionality of LDAP
  directories, including the one used by Microsoft NetMeeting.   Use these objects to add
  directory capabilities to your NetMeeting application.

· A new set of COM objects that allow developers to install and uninstall audio and video codecs.
  Use these objects in a setup program for your codec so that NetMeeting users
  can install your codecs. 

· An ActiveX Control that allows the functionality of the Microsoft 
  conferencing platform to be included in Web pages, Visual Basic 
  applications, and other OLE-enabled documents and applications.


INSTALLING AND USING THE NETMEETING SDK
=======================================
To install, or re-install, the NetMeeting SDK, execute the NM21SDK.EXE self-
extracting installation program.   This .EXE was created for Windows NT 4.0 and
Windows 95.  It  will copy the SDK to a directory you specify and place
shortcuts to the NetMeeting SDK documentation, readme, and folder, in the
Start, Programs menu on your task bar.

Note that if you install on NT 4.0 and you do not have administrator privelege,
no items will be installed on the Start, Programs Menu for the NetMeeting 2.1 SDK.

To use this SDK you will need the final version of NetMeeting 2.1.
This version of the NetMeeting is available at http://www.microsoft.com/netmeeting.

NOTE: Do not install the NetMeeting 1.0 or 1.0a SDK on a machine with NetMeeting
2.1.  If you do you will be required to re-install NetMeeting 2.1.


OVERVIEW OF THE NETMEETING SDK SAMPLES
======================================

The Samples directory contains the following sample code:

· Four Visual C++ applications, NMFT, NMCHAT, NMSHARE, and NMUI, that use the INm* COM objects
  to leverage enhanced NetMeeting 2.1 platform capabilities.

· One Visual C++ application, SKIPPY, that uses the ILS COM objects to demonstrate application
  use of LDAP directory services.

· One Visual C++ application, INSTCODC, that uses codec installation objects to demonstrate the
  installation, deinstallation, and reordering of codec priorities.

· A Visual C++ application, AVPHONE, that demonstrates the manipulation of
  the audio & video API in Microsoft NetMeeting.

· A Visual Basic application that uses the ActiveX Control

· A HTML Web page with VBScript that uses the Control



For more information on the samples, see the Sample.txt file in the root
directory of the SDK.  This file contains information on all of the samples
in the SDK.  In addition, some of the samples have specific readme files
located in their respective directories.


KNOWN ISSUES
==============
1.  While browsing the HTML documentation, occasionally links to specific
functions will stop working.  You will know this has happened if you click on
a object::method link and it simply becomes grey instead of taking you to the
method in question.

To fix this go to the top of the section you are looking at and select
"INDEX" from the black toolbar.  When the Index appears find the function you
were looking for in the Index and click the link. This forces the links to
start working again.

2.  Note that there are 2 makefiles in each sample directory.  One is of the
type SAMPLE.MAK (i.e. NMCHAT.MAK), and another is of the type MAKEFILE.
The *.MAK version is to be used with VC++ 5.0.  The MAKEFILE is for use 
with NMAKE.

3.  The following will not implemented for NM 2.1, but we will support them in the
next release of NetMeeting.
INmSysInfo::GetUserData
INmSysInfo::SetUserData
INmCall::GetUserData

4.  For users of the ActiveX Control, we no longer support the CNF_FILE_INTIALIZING
notification on ConfFileExchangeNotify::FileSent.

5. To place a 323 gateway call you establish a call in the standard fashion
(ConfMgr::CreateCall) specifying that it is a NM_CALL_H323 call with a
NM_ADDR_H323_GATEWAY address type.  The address is of the form
"www.xxx.yyy.zzz/18005551212" where www.xxx.yyy.zzz is the IP address of the
gateway, and the 1800... number is the outgoing phone number to be dialed.
The 1800.. is actually whatever address the gateway will use to place the
outgoing call from the gateway.  It could be something specific to your
gateway, but must not contain characters other than the following:
0123456789#*,

