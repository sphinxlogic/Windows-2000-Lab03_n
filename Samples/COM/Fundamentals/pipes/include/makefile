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

PROJ = proxy

all: $(PROJ).dll pipe.obj

CUSTOM_FLAGS = /D_WIN32_DCOM /D_UNICODE /DUNICODE /DREGISTER_PROXY_DLL


!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif

.cpp.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<


# Define project specific macros

dlldata.c : pipesample.idl
	midl /h ISimpleInterface.h /iid guids.c /proxy proxy.c /char unsigned pipesample.idl

PROXYSTUB_OBJS = dlldata.obj proxy.obj guids.obj

PROXYSTUB_LIBS = kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib uuid.lib
 
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib

# Build rule for PROXYSTUBDLL
$(PROJ).dll: $(PROXYSTUB_OBJS) $(GLOBAL_OBJS)
    $(link) $(linkdebug) $(guilflags) -DLL -DEF:proxy.def\
    $(PROXYSTUB_OBJS) $(PROXYSTUB_LIBS) $(EXTRA_LIBS) \
    -out:$(PROJ).dll $(MAPFILE)
	regsvr32 /s proxy.dll

#
# Pipe stuff
#

#CPP_FLAGS = /c /MTd /Zi /Od /D_DEBUG /D_WIN32_DCOM
pipe.obj : pipe.cxx pipe.hxx
#	cl $(CPP_FLAGS) pipe.cxx

# Rules for cleaning out those old files

clean:
	del -f *.obj *.pdb *.dll *.exp *.lib *.tlb dlldata.c
