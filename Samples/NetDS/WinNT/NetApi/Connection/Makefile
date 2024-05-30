#*************************************************************#
#**                                                         **#
#**          Microsoft NCEnum Example                       **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NCEnum

# Make NCEnum application
NCEnum : NCEnum.exe
NCEnum.exe : NCEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NCEnum.exe\
    NCEnum.obj $(libs)
NCEnum.obj : NCEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe