
/******************************************************************************\
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1992-1999.  Microsoft Corporation.  All rights reserved.

This source code is only intended as a supplement to
Microsoft Development Tools and/or WinHelp documentation.
See these sources for detailed information regarding the
Microsoft samples programs.

File:       popfile.h
----------------------------------------------------------------------------*/

#ifndef __POPFILE_H__
#define __POPFILE_H__





HANDLE
LockMailDirectory(
                 HANDLE          hUserToken,         // Token of user
                 PCHAR           pszPath);           // Path to mail directory

BOOL
UnlockMailDirectory(
                   HANDLE          hLockFile);

PPopMailDirectory
ReadMailDirectory(
                 HANDLE          hUserToken,
                 PCHAR           pszPath);

BOOL
CommitMailDirectory(
                   PPopMailDirectory   pDir,
                   HANDLE              hUserToken);

void
FreeMailDirectory(
                 PPopMailDirectory   pDir);


HANDLE
OpenMailMessage(
               DWORD               MessageId,
               PPopMailDirectory   pDir,
               HANDLE              hUserToken);

#endif
