# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
#Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Windows 32-Bit apps

APPVER = 4.0
TARGETOS = WINNT

!include <Win32.Mak>

all: typeperf.exe

typeperf.obj: typeperf.c
    $(cc) $(cflags) $(cvars) typeperf.c

typeperf.res: typeperf.rc
    $(rc) $(rcflags) $(rcvars) typeperf.rc

typeperf.exe: typeperf.obj typeperf.res
    $(link) $(ldebug) $(conlflags) -out:typeperf.exe typeperf.obj typeperf.res $(conlibs) pdh.lib
