# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1999 Microsoft Corporation.  All Rights Reserved.
#
# Processor independent makefile

# Nmake macros for building Win32 apps
APPVER = 4.0
TARGETOS = BOTH

!include <win32.mak>

PROJ = SCQuery

all: $(PROJ).exe

# Define project specific macros
PROJ_OBJS  = SCQuery.obj
BASE_OBJS  = SCCommon.obj
EXTRA_LIBS = winscard.lib
GLOBAL_DEP = SCCommon.h
RC_DEP     =

# Inference rule for updating the object files
.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $<

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS)
    $(link) $(ldebug) $(conlflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(conlibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe
