# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1995-1999.  Microsoft Corporation.  All rights reserved.
#
# Fibers are supported on Windows NT 3.51 service pack 3 and beyond.

TARGETOS=WINNT
APPVER=4.0
!include <win32.mak>

#detect build time environment
!IF "$(OS)" == "Windows_NT"
all: fibers.exe
!else
all: WARN_MSG
!endif

WARN_MSG:
    @echo "This sample will work only on Windows NT"



fibers.obj: fibers.c
    $(cc) $(cflags) $(cvars) $(cdebug) fibers.c

fibers.exe: fibers.obj
    $(link) $(ldebug) $(conlflags) -out:fibers.exe fibers.obj $(conlibs)
