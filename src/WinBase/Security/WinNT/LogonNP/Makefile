# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

APPVER = 4.0
TARGETOS=WINNT

!include <win32.mak>

all: logonnp.dll

logonnp.obj: logonnp.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

logonnp.dll: logonnp.obj
  $(link) $(ldebug) $(dlllflags) $(guilibsdll) \
  $** -out:logonnp.dll -def:logonnp.def netapi32.lib
