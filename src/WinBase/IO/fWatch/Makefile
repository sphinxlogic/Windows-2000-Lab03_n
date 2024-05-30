# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#

# Nmake macros for building Windows 32-Bit apps

APPVER = 4.0
TARGETOS = WINNT

!include <win32.mak>

all: fwatch.exe

fwatch.obj: fwatch.c
     $(cc) $(cflags) $(cdebug) $(cvars) fwatch.c

fwatch.exe: fwatch.obj
    $(link) $(ldebug) $(conlflags) -out:fwatch.exe fwatch.obj $(conlibs) user32.lib
