# Nmake macros for building Windows 32-Bit apps

!include <Win32.Mak>

all: simple.exe

simple.obj: simple.c
    $(cc) $(cflags) $(cvars) simple.c

simple.exe: simple.obj
    $(link) $(conflags) -out:simple.exe simple.obj $(conlibs)
