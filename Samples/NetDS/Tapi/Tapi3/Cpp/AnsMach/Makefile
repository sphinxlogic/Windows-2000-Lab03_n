# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997-1999  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile
APPVER=5.0

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = ANSMACH

all: $(PROJ).exe 

# Define project specific macros
PROJ_OBJS  = incoming.obj callnot.obj term.obj
BASE_OBJS  =
EXTRA_LIBS = version.lib ole32.lib oleaut32.lib t3iid.lib uuid.lib strmiids.lib amstrmid.lib
GLOBAL_DEP = resource.h
RC_DEP     = resource.h



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
