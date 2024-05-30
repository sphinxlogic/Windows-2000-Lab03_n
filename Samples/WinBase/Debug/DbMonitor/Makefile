# Makefile - DbMonitor.Exe
#
# Copyright 1998 Microsoft Corporation.
#
# requires: ImageHlp.Lib
#
!Include <Win32.Mak>

all: DbMonitor.Exe

DbMonitor.Obj: DbMonitor.c
    $(cc) $(cflags) $(cvars)c DbMonitor.c

DbMonitor.Exe: DbMonitor.Obj
    $(link) $(conflags) -out:DbMonitor.Exe DbMonitor.Obj $(conlibs) ImageHlp.Lib
