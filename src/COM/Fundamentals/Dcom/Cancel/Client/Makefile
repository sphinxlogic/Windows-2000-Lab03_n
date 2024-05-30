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

PROJ = cancel


all: $(PROJ).exe 


CUSTOM_FLAGS = /D_WIN32_DCOM /DUNICODE /D_UNICODE



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
PROJ_OBJS  = cancel.obj 
RC_DEP     = resource.h
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for EXE
$(PROJ).EXE: $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(conlflags) /entry:WinMainCRTStartup \
    $(PROJ_OBJS) $(PROJ).res $(guilibsdll) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)
#    if not exist ..\bin mkdir ..\bin
#    if not exist ..\bin\$(PROJ) mkdir ..\bin\$(PROJ)
#    copy $(PROJ).exe ..\bin\$(PROJ)


# Rules for cleaning out those old files
clean:
    del *.obj *.exe *.res

