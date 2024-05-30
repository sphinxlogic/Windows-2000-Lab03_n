#======================================================================
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
# PURPOSE.
#
# Copyright 1998-1999. Microsoft Corporation. All Right Reserved.
#
# File: MAKEFILE
#
# NMAKE description file for the CreateCert sample
#
#======================================================================
APPVER = 4.0
TARGETOS = WINNT

!include <win32.mak>

PROJ = CreateCert

all: $(PROJ).exe


#======================================================================
# Define project specific macros
#======================================================================
PROJ_OBJS  = $(PROJ).obj
EXTRA_LIBS = crypt32.lib rpcrt4.lib


#======================================================================
# Define UNICODE if you want this.  UNICODE does not work on Win9x
#======================================================================
# EXTRA_DEFS = -DUNICODE -D_UNICODE

# DEF_FILE = -def:$(PROJ).def


#======================================================================
# Inference rule for updating the object files
#======================================================================
$(PROJ).obj : $(PROJ).c
   $(cc) $(cdebug) $(cflags) $(cvars) $(EXTRA_DEFS) $(PROJ).c


#======================================================================
# Build Rules for EXE
#======================================================================
$(PROJ).EXE : $(BASE_OBJS) $(PROJ_OBJS)
   $(link) $(ldebug) $(conlflags) $(PROJ_OBJS)\
   $(conlibs) $(EXTRA_LIBS) -out:$(PROJ).exe

