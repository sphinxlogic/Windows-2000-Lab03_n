#*************************************************************#
#**                                                         **#
#**             Microsoft NSeXXX Examples                   **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NSeDel NSeEnum NSeGetInfo

# Make NSeDel application
NSeDel : NSeDel.exe
NSeDel.exe : NSeDel.obj
    $(link) $(linkdebug) $(conflags) -out:NSeDel.exe\
    NSeDel.obj $(libs)
NSeDel.obj : NSeDel.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NSeEnum application
NSeEnum : NSeEnum.exe
NSeEnum.exe : NSeEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NSeEnum.exe\
    NSeEnum.obj $(libs)
NSeEnum.obj : NSeEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NSeGetInfo application
NSeGetInfo : NSeGetInfo.exe
NSeGetInfo.exe : NSeGetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NSeGetInfo.exe\
    NSeGetInfo.obj $(libs)
NSeGetInfo.obj : NSeGetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe