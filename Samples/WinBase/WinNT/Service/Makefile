# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993-1999.  Microsoft Corporation.  All rights reserved.
#

APPVER = 4.0
TARGETOS=WINNT

!include <Win32.Mak>


all: simple.exe client.exe

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c


## Simple dependencies

simple.obj: simple.c service.h

service.obj: service.c service.h

simple_objs = simple.obj service.obj

simple.exe: $(simple_objs)
    $(link) $(ldebug) $(conlflags) $(simple_objs) \
    -out:simple.exe  $(conlibsmt) advapi32.lib shell32.lib

## Client dependencies

client.exe: client.obj
    $(link) $(ldebug) $(conlflags) -out:client.exe client.obj $(conlibsmt)

