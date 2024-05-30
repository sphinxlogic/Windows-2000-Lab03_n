# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1992-1999.  Microsoft Corporation.  All rights reserved.
#


APPVER = 4.0
TARGETOS=WINNT
!include <win32.mak>

!IFNDEF NODEBUG
cdebug = $(cdebug) -DDBG
debugobj = debug.obj
!ENDIF

all: pop3srv.exe

pop3evnt.h pop3evnt.rc msg00001.bin: pop3evnt.mc
    mc -v pop3evnt.mc

pop3evnt.res: pop3evnt.rc msg00001.bin pop3evnt.rc
    rc -r -fo pop3evnt.res pop3evnt.rc

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsmt) -DUNICODE -D_UNICODE -DRPC_NO_WINDOWS_H $*.c

pop3srv.exe: pop3evnt.res \
            pop3srv.obj \
            pop3.obj    \
            popfile.obj \
            service.obj \
            events.obj  \
            $(debugobj) \
            param.obj   \
            threads.obj \
            socket.obj
  $(link) $(ldebug) $(conlflags) -machine:$(CPU) -out:$*.exe $** $(conlibsmt) advapi32.lib rpcrt4.lib
