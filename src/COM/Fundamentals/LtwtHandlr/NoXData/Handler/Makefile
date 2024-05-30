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

PROJ = handler
ROOTPROJ = NoXData

all: Server$(PROJ).dll

CUSTOM_FLAGS = /D_WIN32_DCOM


!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif

.cpp.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

GLOBAL_OBJS = guid.obj debug.obj ..\..\NumtxtPS\ServerPS.dll
# Define project specific macros
PROJ_OBJS  = classfact.obj NumToText.obj handler.obj 
GLOBAL_DEP = NumToText.h ..\..\common\guid.h ..\..\common\debug.h ..\..\NumToTextPS\server.h
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib

guid.obj : ..\..\common\guid.cpp
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c ..\..\common\guid.cpp
debug.obj : ..\..\common\debug.cpp
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c ..\..\common\debug.cpp

..\..\NumtxtPS\ServerPS.dll:
!include <sdkbld.mak>

# Build rule for EXE
Server$(PROJ).dll: $(GLOBAL_OBJS) $(PROJ_OBJS)
    $(link) $(linkdebug) $(guilflags) -DLL -DEF:$(PROJ).def\
    $(PROJ_OBJS) guid.obj debug.obj $(guilibs) $(EXTRA_LIBS) \
    -out:Server$(PROJ).dll $(MAPFILE)
    if not exist ..\..\bin mkdir ..\..\bin
    if not exist ..\..\bin\$(ROOTPROJ) mkdir ..\..\bin\$(ROOTPROJ)
    copy Server$(PROJ).dll ..\..\bin\$(ROOTPROJ)

# Rules for cleaning out those old files
clean:
    @-del *.obj
    @-del *.dll
    @-del *.lib
    @-del *.exp
