StackWalk Sample
==============

This sample demonstrates how an application can use ImageHlp APIs to
obtain stack trace information. The LogStackWalk() function in callstack.cpp
is a helper function to display the stack trace. This utility does not take any
command line parameters.

CallStack.exe
-------------------
This command line tool outputs the following information.
* Stack Trace of a function call
* Stack Trace of an exception caught using Structured Exception Handling
* Stack Trace of an exception caught by UnhandledExceptionFilter

The stack trace will have more than one stack frame with the following output.

     Return PC Address : 00401968
     Parameter 1 : 00000006
     Parameter 2 : 00000004
     Parameter 3 : 00000002
     Parameter 4 : 00000002
     ModuleName : callstack
     Function Name : f4
     File Name : callstack.cpp
     Line Number : 502

Building CallStack.exe
----------------------------
Use nmake from the command line.  The makefile for this sample creates
CallStack.exe with debug information.

Usage notes
--------------
The sample code does the following.

(a) Demonstrates how an application can enumerate all the loaded modules
     in a process and call SymLoadModule. This will work on Windows9x
     and WindowsNT platforms.

(b) Demonstrates how an application can obtain a stack trace in the following cases.
     1. For tracing a function call
     2. In an exception caught using Structured Exception Handling
     3. In an exception caught by unhandled exception filter

(c) Demonstrates the new Windows 2000 SymGetLineFromAddr API to fetch the
     line number information. The sample will get this information only if the API is
     available in imagehlp.dll


THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.
