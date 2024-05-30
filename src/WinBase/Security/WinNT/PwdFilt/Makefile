# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.
#


APPVER = 4.0
TARGETOS=WINNT
!include <win32.mak>

all: pwdfilt.dll

pwdfilt.obj: pwdfilt.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

pwdfilt.lib: pwdfilt.obj pwdfilt.def
  $(implib) -machine:$(CPU) -def:pwdfilt.def -out:pwdfilt.lib

pwdfilt.dll: pwdfilt.obj
  $(link) $(ldebug) $(dlllflags) $(guilibsdll) \
  $** -out:pwdfilt.dll -def:pwdfilt.def user32.lib
