# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

APPVER = 4.0
TARGETOS = BOTH

!include <win32.mak>

PROJ = SparsMem

all: $(PROJ).exe

PROJ_OBJS = sparsmem.obj
RC_DEP    = resource.h
EXTRA_LIBS = advapi32.lib

sparsmem.obj: sparsmem.c resource.h

.c.obj:
   $(cc) $(cdebug) $(cflags) $(cvars) $<


$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) -fo $(PROJ).res $(PROJ).rc


$(PROJ).exe: $(PROJ_OBJS) $(PROJ).res
    $(link) $(ldebug) $(guilflags) $(PROJ_OBJS) \
    -out:$(PROJ).exe  \
    $(PROJ).res $(guilibs) $(EXTRA_LIBS)
