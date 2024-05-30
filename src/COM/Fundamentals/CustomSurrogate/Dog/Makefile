# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1998 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>
#!include <dogps.mk>
PROJ = dog


all: $(PROJ)PS.dll $(PROJ).dll 

.cpp.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

# Define project specific macros
PROJ_OBJS  = dog.obj dogcf.obj idog.obj
GLOBAL_DEP = dogcf.h cdog.h 
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib


# Build rule for EXE
$(PROJ).dll: $(PROJ_OBJS) 
    $(link) $(linkdebug) $(guilflags) -DLL -DEF:$(PROJ).def\
    $(PROJ_OBJS) $(guilibsdll) $(EXTRA_LIBS) \
    -out:$(PROJ).dll $(MAPFILE)


dogps.dll: i$(PROJ).h dlldata.obj idog_p.obj idog_i.obj
	link /dll /out:dogps.dll /def:dogps.def /entry:DllMain dlldata.obj idog_p.obj idog_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

# Rules for cleaning out those old files
clean:
    @-del *.obj
    @-del *.dll
    @-del *.lib
    @-del *.exp
    @-del *.tlb
    @-del idog.h
    @-del dlldata.c
    @-del idog_?.*


!ifndef MIDL
MIDL            = midl
!endif

MIDLFLAGS    = /Oicf

CUSTOM_FLAGS = /DREGISTER_PROXY_DLL /D_WIN32_DCOM

!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif

# run midl to produce the header files and the proxy file
idog.h : idog.idl 
    $(MIDL) $(MIDLFLAGS) idog.idl
