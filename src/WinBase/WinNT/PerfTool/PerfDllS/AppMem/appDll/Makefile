# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1995-1999  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps

TARGETOS = WINNT
APPVER = 4.0

!include <win32.mak>

PROJ = appmema

all: $(PROJ).dll

# Define project specific macros
PROJ_OBJS  = $(PROJ).obj dllinit.obj $(PROJ).res
BASE_OBJS  =
EXTRA_LIBS = advapi32.lib ..\perfdll\sharemem.obj
GLOBAL_DEP = $(PROJ).h
RC_DEP     =


# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for DLL
$(PROJ).DLL: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) $(ldebug) $(dlllflags) $(BASE_OBJS) $(PROJ_OBJS) \
    $(guilibsdll) $(EXTRA_LIBS) \
    -out:..\pub\$(PROJ).dll /DEF:$(PROJ).def



# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc *.lst *.err
