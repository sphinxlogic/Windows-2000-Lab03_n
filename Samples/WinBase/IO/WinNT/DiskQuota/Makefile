# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.


APPVER = 5.0
TARGETOS = WINNT

!include <win32.mak>

PROJ1 = DskQuota
cflags = $(cflags) /D_UNICODE /DUNICODE
conlflags = $(conlflags) ole32.lib

all: $(PROJ1).exe

PROJ1_OBJS = DskQuota.obj Commands.obj PrintMenu.obj ProcessMenu.obj

DskQuota.obj: DskQuota.cpp ProcessMenu.h PrintMenu.h Commands.h
Commands.obj: Commands.cpp Commands.h
PrintMenu.obj: PrintMenu.cpp
ProcessMenu.obj: ProcessMenu.cpp ProcessMenu.h PrintMenu.h Commands.h

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $<

$(PROJ1).exe: $(PROJ1_OBJS)
    $(link) $(ldebug) $(conlflags)\
    $(PROJ1_OBJS) \
    -out:$(PROJ1).exe \
    $(conlibs)

clean:
    del *.bak
    del *.opt
    del *.pdb
    del *.obj

cleaner: clean
    del *.exe
