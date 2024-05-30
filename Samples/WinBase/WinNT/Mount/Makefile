# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.


APPVER = 5.0
TARGETOS = WINNT

!include <win32.mak>

PROJ1 = mount
PROJ2 = unmount

all: $(PROJ1).exe $(PROJ2).exe

PROJ1_OBJS = mount.obj
PROJ2_OBJS = unmount.obj

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $<

$(PROJ1).exe: $(PROJ1_OBJS)
    $(link) $(ldebug) $(conlflags)\
    $(PROJ1_OBJS) \
    -out:$(PROJ1).exe \
    $(conlibs)


$(PROJ2).exe: $(PROJ2_OBJS)
    $(link) $(ldebug) $(conlflags)\
    $(PROJ2_OBJS) \
    -out:$(PROJ2).exe \
    $(conlibs)

clean:
    del *.bak
    del *.opt
    del *.pdb
    del *.obj

cleaner: clean
    del *.exe
