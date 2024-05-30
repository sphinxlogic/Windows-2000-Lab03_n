# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1999 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Win32 apps
!include <win32.mak>

PROJ = SmbSmp

all: $(PROJ).dll

# Define project specific macros
PROJ_OBJS  = SmbSmp.obj ClRes.obj
BASE_OBJS  =
EXTRA_LIBS = clusapi.lib resutils.lib netapi32.lib User32.lib
GLOBAL_DEP =
RC_DEP     =

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Inference rule for updating the object files
.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc


# Build rule for DLL
$(PROJ).dll: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(dllllflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(dlllibs) $(EXTRA_LIBS) \
    -out:$(PROJ).dll $(MAPFILE) \
    -def:$(PROJ).def

# Build rule for help file
$(PROJ).hlp: $(PROJ).rtf $(PROJ).hpj
    $(hc) $(PROJ).hpj


# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc *.idb *.dll *.lib *.ilk
