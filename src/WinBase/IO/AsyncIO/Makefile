# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1992-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Win32 apps

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!endif

all: AsyncIO.Exe

AsyncIO.Obj: AsyncIO.c AsyncIO.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) AsyncIO.c

AsyncIO.Exe: AsyncIO.Obj
    $(link) $(ldebug) $(conlflags) -out:AsyncIO.Exe AsyncIO.Obj $(conlibsmt)
