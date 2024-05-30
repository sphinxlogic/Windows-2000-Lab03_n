# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.


APPVER = 4.0
TARGETOS = BOTH

!include <win32.mak>

PROJ1 = debugHandler

all: $(PROJ1).exe

PROJ1_OBJS = debugHandler.obj

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $<

$(PROJ1).exe: $(PROJ1_OBJS)
    $(link) $(ldebug) $(conlflags)\
    $(PROJ1_OBJS) \
    -out:$(PROJ1).exe \
    $(conlibs) imagehlp.lib

clean:
    del *.bak
    del *.opt
    del *.pdb
    del *.obj

cleaner: clean
    del *.exe
