# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#

TARGETOS=WINNT
APPVER=4.0

!include <Win32.Mak>

all: signfile.exe verifile.exe

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

signfile.exe: signfile.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(conlibsdll) advapi32.lib

verifile.exe: verifile.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(conlibsdll) advapi32.lib
