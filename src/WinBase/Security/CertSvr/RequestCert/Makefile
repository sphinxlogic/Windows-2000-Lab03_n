#===================================================================
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
# PURPOSE.
#
# Copyright 1998-1999. Microsoft Corporation. All Right Reserved.
#
# File: MAKEFILE
#
# NMAKE description file for the RequestCert sample
#
#===================================================================

APVER = 4.0
TARGETOS = WINNT

!include <win32.mak>

PROJ = RequestCert

all: $(PROJ).exe

#=====================================================
# Define project specific macros
#=====================================================
PROJ_OBJS  = requestcert.obj
EXTRA_LIBS = certidl.lib
myconflags = -subsystem:console,$(EXEVER)

#======================================================
# Inference rule for updating the object files
#======================================================
.c.obj:
   $(cc) $(cdebug) $(cflags) $(cvars) $<

$(PROJ).obj : $(PROJ).cpp
   $(cc) $(cdebug) $(cflags) $(cvars) $(PROJ).cpp

#=======================================================
# Build Rules for EXE
#=======================================================
$(PROJ).EXE : $(BASE_OBJS) $(PROJ_OBJS)
   $(link) $(ldebug) $(conlflags) $(PROJ_OBJS)\
   $(conlibs) $(olelibs) $(EXTRA_LIBS) -out:$(PROJ).exe

