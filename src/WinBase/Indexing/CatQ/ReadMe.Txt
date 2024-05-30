//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) 1998-1999 Microsoft Corporation.  All Rights Reserved.
//
//  Sample Name:    CatQ - Sample OLE DB Provider Query Application
//
//--------------------------------------------------------------------------

Description
===========
  The CatQ sample is an example Windows application written in C++ that
  executes queries using the OLE DB Provider API.  The queries are on the
  catalog of the local computer and restrict the scope to text files in the
  Platform SDK by using the MSSDK environment variable.

Path
====
  Source: mssdk\samples\winbase\indexing\CatQ\
  
User's Guide
============
  * To build the example
      1. Set the Lib environment variable to "D:\mssdk\Lib;%Lib%" and the
         Include environment variable to "D:\mssdk\Include;%Include%",
         where D: is the drive on which you installed the Platform SDK.
      2. Correctly set the CPU environment variable to, for example, "i386".
      3. Open a command window and change the directory to the source path
         of the example.
      4. Build the example by entering, at the command-line prompt, "nmake".

  * To execute queries using the example
      1. XXXXX.
      2. XXXXX.
      3. XXXXX.

Programming Notes
=================
  When the CatQ sample starts, it checks the status of Indexing Service and
  starts it if it is not running.

  In the status bar at the bottom of the CatQ sample window, the progress of
  indexing is displayed as a fraction and as a blue "progress bar."  The
  numerator and denominator of this fraction are read as performance
  registry counters, which are written out by the CiSvc.exe process.

  The denominator in the progress display is the total number of files that
  Indexing Service must index in order for the catalog to be up-to-date.
  Unfortunately, this value is not known instantly at the time of Indexing
  Service startup, and in fact, it typically grows over time as the
  numerator grows.  For this reason, the progress percentage can decrease
  even as Indexing Service is making progress.  That is, Indexing Service
  is finding new files to index as fast as it is indexing files in its
  existing list.

