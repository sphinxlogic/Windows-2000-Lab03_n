# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1999 Microsoft Corporation.  All Rights Reserved.
#
# Processor independent makefile

!include <ntwin32.mak>

all: lsasamp.exe

lsasamp.obj: lsasamp.c
    $(cc) $(cflags) $(cvars) -I..\include -Zi -Od lsasamp.c

lsasamp.exe: lsasamp.obj
    $(link) $(linkdebug) $(conflags) -out:lsasamp.exe lsasamp.obj $(conlibs) user32.lib advapi32.lib
