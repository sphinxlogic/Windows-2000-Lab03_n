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

PROJ = mta

all: $(PROJ).exe 

CUSTOM_FLAGS = /D_UNICODE /DUNICODE /D_WIN32_DCOM



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
PROJ_OBJS  = sserver.obj
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib

# Build rule for EXE
$(PROJ).EXE: $(PROJ_OBJS) $(GLOBAL_OBJS)
    $(link) $(linkdebug) $(conlflags) \
    $(PROJ_OBJS) $(guilibsdll) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)

# Rules for cleaning out those old files
clean:
    del *.obj *.exe

