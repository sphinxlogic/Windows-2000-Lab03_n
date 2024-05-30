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

!include <Win32.Mak>

all: proclist.exe

proclist.obj: proclist.c
    $(cc) $(cdebug) $(cflags)  $(cvars) proclist.c

proclist.res: proclist.rc
    $(rc) $(rcflags) $(rcvars) proclist.rc

proclist.exe: proclist.obj proclist.res
    $(link) $(ldebug) $(conlflags) -out:proclist.exe proclist.obj proclist.res $(conlibs) pdh.lib
