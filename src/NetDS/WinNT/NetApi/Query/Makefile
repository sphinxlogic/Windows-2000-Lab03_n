#*************************************************************#
#**                                                         **#
#**                Microsoft NQDInfo Example                **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NQDInfo

# Make NQDInfo application
NQDInfo : NQDInfo.exe
NQDInfo.exe : NQDInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NQDInfo.exe\
    NQDInfo.obj $(libs)
NQDInfo.obj : NQDInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe