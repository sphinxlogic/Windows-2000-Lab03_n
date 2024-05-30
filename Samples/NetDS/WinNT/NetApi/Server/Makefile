#*************************************************************#
#**                                                         **#
#**             Microsoft NSXXX Examples                    **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NSDiskEnum NSEnum NSGetInfo NSSetInfo NSTransEnum

# Make NSDiskEnum application
NSDiskEnum : NSDiskEnum.exe
NSDiskEnum.exe : NSDiskEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NSDiskEnum.exe\
    NSDiskEnum.obj $(libs)
NSDiskEnum.obj : NSDiskEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NSEnum application
NSEnum : NSEnum.exe
NSEnum.exe : NSEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NSEnum.exe\
    NSEnum.obj $(libs)
NSEnum.obj : NSEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NSGetInfo application
NSGetInfo : NSGetInfo.exe
NSGetInfo.exe : NSGetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NSGetInfo.exe\
    NSGetInfo.obj $(libs)
NSGetInfo.obj : NSGetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NSSetInfo application
NSSetInfo : NSSetInfo.exe
NSSetInfo.exe : NSSetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NSSetInfo.exe\
    NSSetInfo.obj $(libs)
NSSetInfo.obj : NSSetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NSTransEnum application
NSTransEnum : NSTransEnum.exe
NSTransEnum.exe : NSTransEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NSTransEnum.exe\
    NSTransEnum.obj $(libs)
NSTransEnum.obj : NSTransEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe