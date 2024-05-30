#*************************************************************#
#**                                                         **#
#**             Microsoft NRTOD Example                     **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NRTOD

# Make NRTOD application
NRTOD : NRTOD.exe
NRTOD.exe : NRTOD.obj
    $(link) $(linkdebug) $(conflags) -out:NRTOD.exe\
    NRTOD.obj $(libs)
NRTOD.obj : NRTOD.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe