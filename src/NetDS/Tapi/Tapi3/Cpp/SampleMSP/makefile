# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>


PROJ = sampmsp

!ifndef MIDL
MIDL = midl
!endif

all: $(PROJ).dll 


MIDLFLAGS = /Oicf -char unsigned -ms_ext -c_ext -error all -header sampmsp.h  \
            -robust -cpp_cmd $(CC) -DMSPLOG -DUNICODE  -Di386 -D_X86_         \
            -D_WCHAR_T_DEFINED

#Run MIDL compiler to generate the header and definition files
sampmsp.h sampmsp_i.c : sampmsp.idl
    $(MIDL) $(MIDLFLAGS) sampmsp.idl

# Define project specific macros
PROJ_OBJS  = sampmsp.obj sampaddr.obj sampcall.obj sampstrm.obj
BASE_OBJS  =
EXTRA_LIBS = kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib \
             ole32.lib oleaut32.lib uuid.lib winmm.lib t3iid.lib \
             mspid.lib strmiids.lib tmuid.lib rtutils.lib strmbase.lib \
             mspbase.lib atl.lib 

GLOBAL_DEP = resource.h
RC_DEP     = resource.h

cflags = $(cflags) -DMSPLOG -DUNICODE -GR -GX

# Inference rule for updating the object files
.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

sampmsp.obj : sampmsp.h sampmsp_i.c


# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvarsdll) /fo $(PROJ).res $(PROJ).rc

# Build rule for DLL
$(PROJ).DLL: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) /DLL $(linkdebug) $(guilflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(EXTRA_LIBS) \
    -out:$(PROJ).dll $(MAPFILE)

# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc sampmsp.h sampmsp_i.c
