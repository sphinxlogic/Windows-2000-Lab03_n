# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = ACDPROXY

all: $(PROJ).exe 

# Define project specific macros
PROJ_OBJS  = acdobjects.obj acdproxy.obj acdtapi.obj
BASE_OBJS  =
EXTRA_LIBS = version.lib ole32.lib oleaut32.lib tapi32.lib  t3iid.lib uuid.lib
GLOBAL_DEP = resource.h
RC_DEP     = resource.h

cflags = $(cflags) -DUNICODE

# Inference rule for updating the object files
.cpp.obj:
  $(cc) $(cdebug) $(cflags) -GX $(cvars) $*.cpp

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(guilflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(guilibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)


# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc
