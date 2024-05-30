# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999 Microsoft Corporation.  All rights reserved.
#

APPVER = 4.0
TARGETOS = BOTH

!include <win32.mak>

PROJ = FCOPY

all: $(PROJ).exe

PROJ_OBJS = fcopy.obj

.cpp.obj:
   $(cc) $(cdebug) $(cflags) $(cvars) $<

$(PROJ).exe: $(PROJ_OBJS)
   $(link) $(ldebug) $(conlflags) $(PROJ_OBJS) $(conlibs) -out:$(PROJ).exe

clean:
   del *.obj
   del *.bak

