# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1999 Microsoft Corporation.  All Rights Reserved.
#
# Processor independent makefile

# Nmake macros for building Win32 apps
APPVER = 4.0
TARGETOS = BOTH

!include <win32.mak>

# This is a unicode project, so make it as such.
cflags=$(cflags) -D UNICODE -D _UNICODE
conflags=$(conflags) -entry:wmainCRTStartup

PROJ = SAMPLE1

all: $(PROJ).exe

# Define project specific macros
PROJ_OBJS  = stdafx.obj sample1.obj iauth.obj guids.obj
EXTRA_LIBS = msdasc.lib ole32.lib oledb.lib uuid.lib user32.lib

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS)
    $(link) $(ldebug) $(conflags) $(conlibsdll)\
    $(BASE_OBJS) $(PROJ_OBJS) $(conlibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe
