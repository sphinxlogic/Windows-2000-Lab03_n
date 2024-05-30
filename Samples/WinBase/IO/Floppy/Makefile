# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Windows 32-Bit apps

APPVER = 4.0
TARGETOS=WINNT

!include <Win32.Mak>

all: mfmt.exe

mfmt.obj: mfmt.c
    $(cc) $(cflags) $(cvars) $(cdebug) mfmt.c

mfmt.exe: mfmt.obj
    $(link) $(ldebug) $(conlflags) -out:mfmt.exe mfmt.obj $(conlibs)
