------------------------------------------------------------------------------------------
             Microsoft Chat Control 1.0 & Microsoft Chat Protocol Control 2.0 Readme File         
------------------------------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1997


HOW TO USE THIS DOCUMENT
========================

To view Readme.txt on screen in Windows Notepad, maximize the Notepad 
window.

To print Readme.txt, open the file in Notepad or another word processor,
and then on the File menu, click Print.


CONTENTS
========

INSTALLING THE CHAT CONTROLS
OVERVIEW OF THE MICROSOFT CHAT CONTROL SAMPLES
KNOWN PROBLEMS


INSTALLING THE CHAT CONTROLS
============================

The Samples will work only with Windows 95 and Windows NT 4.0. 

To install the chat control, run the chatcntl.exe in the \complib\i386 directory.
This executable program will:

1. Copy the binaries (chatsock.dll, mschat.ocx and mschatpr.ocx) to your 
   System directory. 

2. Register the controls as an OCX.

OVERVIEW OF THE MICROSOFT CHAT CONTROL SAMPLES
==============================================

The chatocx directory contains the following sample code, which 
demonstrates the use of the control in web pages, Microsoft Visual Basic 
Scripting and Visual Basic:

· Four Visual Basic applications that use the Chat Control 1.1

· Five HTML web pages that use the chat control 1.1 and use Visual Basic Scripting

· One MFC chat application that uses chat control 1.1

· 5 samples that use Chat Control 2.0 beta 1

For more information on the samples, see the Sample.txt file in this directory. 
In addition, each subdirectory under Chatocx contains a text file with more 
detailed information on that sample.

The samples requires that you have Visual Basic 4.0 runtime, mschat.ocx and 
chatsock.dll installed on your system. If you have problems running any of the 
applications you can use the Application Setup Wizard in Visual Basic 4.0 to create 
a setup program, which will create an installation program that installs all the 
required files for the samples. The Application setup wizard will not detect that 
the applications need to install chatsock.dll, you will need to add this to the 
list of files to install, when you run the wizard.

KNOWN PROBLEMS
==============
If you experience any problems connecting to the chat server with any of
the demos, please try to connect again, since the chat server might be down 
at this time.  If you continue to experience this problem, you may not be 
able to connect to the chat server if you are using a proxy server or firewall 
that doesn't pass port "6667". The system administrator for your Internet
Service Provider or your company can tell you if they allow pass through for
port "6667". 

