/*----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.

FILLFILE.H
----------------------------------------------------------------------------*/

#ifndef FILLFILE_INCLUDED
#define FILLFILE_INCLUDED

LONG  GetLBText          (HWND, PTCHAR);
BOOL  myIsDirectory      (LPTSTR);
BOOL  SeparatePathName   (LPTSTR, LPTSTR, LPTSTR);
BOOL  SeparatePathName2  (LPTSTR, LPTSTR, LPTSTR);
BOOL  FillFile           (LPCINFO, HWND);
BOOL  CFilerIsDirectory  (LPTSTR);
BOOL  IsEncrypted        (LPTSTR);
BOOL  IsLegalToAdd       (LPTSTR);
BOOL  BuildSigTable      (TABLE);

#endif // #ifdef FILLFILE_INCLUDED
