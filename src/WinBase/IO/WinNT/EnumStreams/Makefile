# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.
#


# nmake macros for building Windows 32-Bit apps included with the Platform SDK

TARGETOS=WINNT

!include <win32.mak>

all: enumstreams.exe

.c.obj:
    $(cc) $(cflags) $(cdebug) $(cvars) $*.c

enumstreams.obj: enumstreams.c findstream.h

findstream.obj: findstream.c findstream.h

enumstreams.exe: enumstreams.obj findstream.obj
    $(link) $(ldebug) $(conlflags) \
           enumstreams.obj findstream.obj \
           $(conlibs) \
           -out:enumstreams.exe 
