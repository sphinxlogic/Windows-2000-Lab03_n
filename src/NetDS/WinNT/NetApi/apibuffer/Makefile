#*************************************************************#
#**                                                         **#
#**            Microsoft NApiBuffer Example                 **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NApiBuffer

# Make NApiBuffer application
NApiBuffer : NApiBuffer.exe
NApiBuffer.exe : NApiBuffer.obj
    $(link) $(linkdebug) $(conflags) -out:NApiBuffer.exe\
    NApiBuffer.obj $(libs)
NApiBuffer.obj : NApiBuffer.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe