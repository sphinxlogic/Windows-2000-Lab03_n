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

PROJ = SmbSmpEx

all: $(PROJ).dll

# Define project specific macros
PROJ_OBJS  = "BasePage.obj" \
	     "DDxDDv.obj"   \
	     "ExtObj.obj"   \
	     "PropList.obj" \
	     "RegExt.obj"   \
	     "ResProp.obj"  \
	     "SmbSmpEx.obj" \
	     "StdAfx.obj" 

BASE_OBJS  =
EXTRA_LIBS = clusapi.lib resutils.lib netapi32.lib User32.lib
GLOBAL_DEP =
RC_DEP     =
cflags= -GX  /D _AFXDLL  $(cflags)

BasePage.Obj: BasePage.Cpp ExtObjId.h

DDxDDv.Obj: DDxDDv.Cpp ExtObjId.h

ExtObj.Obj: ExtObj.Cpp ExtObjId.h

PropList.Obj: PropList.Cpp ExtObjId.h

RegExt.Obj: RegExt.Cpp ExtObjId.h

ResProp.Obj: ResProp.Cpp ExtObjId.h

SmbSmpEx.Obj: SmbSmpEx.Cpp ExtObjId.h

StdAfx.Obj: StdAfx.Cpp ExtObjId.h

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Inference rule for updating the object files
.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

$(PROJ).dll: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(dlllflags)  \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(dlllibs) $(EXTRA_LIBS) \
    -out:$(PROJ).dll $(MAPFILE) \
    -def:$(PROJ).def

# Build rule for help file
$(PROJ).hlp: $(PROJ).rtf $(PROJ).hpj
    $(hc) $(PROJ).hpj

# Build ExtObjID.h and ExtObjID.tlb from ExtObjID.idl
ExtObjId.Tlb ExtObjId.h: ExtObjId.Idl
    Midl /nologo /D "_DEBUG" /D "MIDL_PASS" /tlb ExtObjId.tlb /h ExtObjId.h /mktyplib203 /win32 ExtObjID.idl

# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc *.idb *.dll \
        *.lib *.ilk *.tlb *.pch ExtObjID.h

