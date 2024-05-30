# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1990-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

PROJ = wdbgexts

all: $(PROJ).dll

# Update the object files if necessary

$(PROJ).obj: $(PROJ).c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(scall) -I. -I..\..\sdktools\image\include $*.c

# Update the import library

$(PROJ).lib: $(PROJ).obj $(PROJ).def
    $(implib) -machine:$(CPU) \
    -def:$*.def \
    $*.obj \
    -out:$*.lib

# Update the dynamic link library

$(PROJ).dll: $(PROJ).obj $(PROJ).def $(PROJ).lib
    $(link) $(ldebug) $(dlllflags) \
    -base:0x1C000000 \
    -out:$*.dll \
    $*.exp $*.obj $(conlibsdll)
