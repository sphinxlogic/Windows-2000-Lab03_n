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

!ifndef MIDL
MIDL            = midl
!endif

MIDLFLAGS    = 

CUSTOM_FLAGS = /DREGISTER_PROXY_DLL /DUNICODE /D_UNICODE

!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif


.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

all:  PS.dll 

# Clean up everything
cleanall: clean


# Clean up everything but the .EXEs
clean:  
	del *.obj
        del PS.dll
        del ps.h
        del PS.lib
        del PS.exp
        del dlldata.c
        del *.ilk
        del *.pdb
        del ?.* 

DLLOBJS= p.obj i.obj dlldata.obj


# build proxy dll
PS.dll: ps.h $(DLLOBJS) PS.def
        $(link) $(linkdebug) -DLL -OUT:PS.dll -DEF:PS.def \
        $(DLLOBJS) rpcrt4.lib $(ole2libsdll)
#    if not exist ..\bin mkdir ..\bin
#    copy $(Server)PS.dll ..\bin


# run midl to produce the header files and the proxy file
ps.h  : Server.idl 
    $(MIDL) $(MIDLFLAGS) /h ps.h /iid i.c /proxy p.c Server.idl

