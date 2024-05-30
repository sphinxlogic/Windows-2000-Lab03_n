# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile
APPVER=5.0

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = RENDSAM

all: $(PROJ).exe 

# Define project specific macros
PROJ_OBJS  = rendsam.obj
BASE_OBJS  =
EXTRA_LIBS = version.lib ole32.lib oleaut32.lib  wsock32.lib rendid.lib sdpblbid.lib
GLOBAL_DEP = 
RC_DEP     = 



# Inference rule for updating the object files
.cpp.obj:
  $(cc) $(cdebug) $(cflags) -GX $(cvars) $*.cpp

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(conlflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(conlibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)


# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc
