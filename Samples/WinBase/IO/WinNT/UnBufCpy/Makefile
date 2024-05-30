# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1994-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Windows 32-Bit apps
#

APPVER = 4.0
TARGETOS=WINNT

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

ALLEXES = unbufcp1.exe unbufcp2.exe

all: $(ALLEXES)

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

$(ALLEXES): $*.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj user32.lib $(conlibsmt)
