# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1995-1999  Microsoft Corporation.  All Rights Reserved.
#

APPVER = 4.0
TARGETOS = WINNT

!include <win32.mak>

PROJ = LEAKYBIN

all: $(PROJ).exe $(PROJ).hlp

# Define project specific macros
PROJ_OBJS  = leakybin.obj
BASE_OBJS  =
EXTRA_LIBS = version.lib
GLOBAL_DEP = leakybin.h resource.h
RC_DEP     = resource.h


# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) $(ldebug) $(guilflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(guilibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe

# Build rule for help file
$(PROJ).hlp: $(PROJ).rtf $(PROJ).hpj
    $(hc) $(PROJ).hpj



# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc *.lst *.err
