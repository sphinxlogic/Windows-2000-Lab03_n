# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.


APPVER = 5.0
TARGETOS = WINNT

!include <win32.mak>

PROJ = CheckSFP

all: $(PROJ).exe

PROJ_OBJS = Checksfp.obj
EXTRA_LIBS =  sfc.lib

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) -D UNICODE -D _UNICODE $<

$(PROJ).exe: $(PROJ_OBJS)
    $(link) $(ldebug) $(conlflags) \
    $(PROJ_OBJS) \
    -out:$(PROJ).exe -entry:wmainCRTStartup \
    $(conlibs)  $(EXTRA_LIBS)
