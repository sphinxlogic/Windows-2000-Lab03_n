/*----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.

EXPDIR.H
----------------------------------------------------------------------------*/

#ifndef EXPDIR_INCLUDED
#define EXPDIR_INCLUDED

BOOL ExpDir(LPCINFO);
VOID ExpDirExit(LPCINFO, HANDLE);
BOOL ConstructDirName(LPCINFO, LONG_PTR, LPTSTR);
LONG GetDirDepth(LPTSTR, LPTSTR*);
BOOL CollapseDir(LPCINFO, LONG_PTR, LONG);
VOID ConstructLBEntry(LONG, LPTSTR, LPTSTR);
BOOL FullExpand(LPCINFO);

#endif
