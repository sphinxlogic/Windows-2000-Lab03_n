# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999 Microsoft Corporation.  All rights reserved.


APPVER = 5.0
TARGETOS = WINNT

!include <win32.mak>

PROJ = DLEDIT

all: $(PROJ).exe

PROJ_OBJS = dledit.obj

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $<

$(PROJ).exe: $(PROJ_OBJS)
    $(link) $(ldebug) $(conlflags)\
    $(PROJ_OBJS) \
    -out:$(PROJ).exe \
    $(conlibs)

clean:
    del *.bak
    del *.opt
    del *.pdb
    del *.obj

cleaner: clean
    del *.exe
