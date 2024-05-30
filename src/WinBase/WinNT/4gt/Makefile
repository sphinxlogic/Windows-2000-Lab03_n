# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.


APPVER = 4.0
TARGETOS = WINNT

!include <win32.mak>

PROJ = 4GT

all: $(PROJ).exe

PROJ_OBJS = 4gt.obj
EXTRA_LIBS = imagehlp.lib

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $<

$(PROJ).exe: $(PROJ_OBJS)
    $(link) $(ldebug) $(conlflags) /LARGEADDRESSAWARE \
    $(PROJ_OBJS) \
    -out:$(PROJ).exe \
    $(conlibs) $(EXTRA_LIBS)

