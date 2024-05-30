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

SERVER = Server

!ifndef MIDL
MIDL            = midl
!endif

MIDLFLAGS    = /Oicf

CUSTOM_FLAGS = /DREGISTER_PROXY_DLL /D_WIN32_DCOM

!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif


.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

all:  $(SERVER)PS.dll 

# Clean up everything
cleanall: clean


# Clean up everything
clean:
        @-del *.obj
        @-del $(SERVER)PS.dll
        @-del $(SERVER).h
        @-del $(SERVER)PS.lib
        @-del $(SERVER)PS.exp
        @-del dlldata.c
        @-del $(SERVER)_?.*
        @-del *.pdb
        @-del *.ilk

DLLOBJS= $(SERVER)_p.obj $(SERVER)_i.obj dlldata.obj


# build proxy dll
$(SERVER)PS.dll: $(SERVER).h $(DLLOBJS) $(SERVER).def 
        $(link) $(linkdebug) -DLL -OUT:$(SERVER)PS.dll -DEF:$(SERVER).def \
        $(DLLOBJS) rpcrt4.lib $(ole2libsdll)
    if not exist ..\bin mkdir ..\bin
    copy $(SERVER)PS.dll ..\bin


# run midl to produce the header files and the proxy file
$(SERVER).h : Server.idl 
    $(MIDL) $(MIDLFLAGS) Server.idl

