THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999  Microsoft Corporation.  All rights reserved.

CabView Sample


The CABVIEW sample demonstrates parsing and extracting component files from
Cabinet (.CAB) files. The library for working with Cabinet files is provided
for x86 only.


Steps to run sample
===================

Start CabView.exe.
Select File | Open to open Cabinet files with .CAB extension.
Select one or more files from the list of files.
Select File | Extract | Selected Files or File | Extract | All Files to extract
  files from the Cabinet file.


Notes
=====

This CabView sample replaced another CabView sample available in previous
versions of the Platform SDK. That sample allowed to user to view the contents
of a Cabinet file through Explorer by implementing a shell namespace extension.
For a sample namespace extension, see the SampView sample in 
%MSSDK%\Samples\WinUI\Shell\SampView, where MSSDK is the installation path of
the Platform SDK.
