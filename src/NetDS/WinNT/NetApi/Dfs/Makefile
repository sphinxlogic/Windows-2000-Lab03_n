#*************************************************************#
#**                                                         **#
#**             Microsoft NDXXX Examples                    **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NDAdd NDEnum NDGetInfo NDRemove NDSetInfo

# Make NDAdd application
NDAdd : NDAdd.exe
NDAdd.exe : NDAdd.obj
    $(link) $(linkdebug) $(conflags) -out:NDAdd.exe\
    NDAdd.obj $(libs)
NDAdd.obj : NDAdd.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NDEnum application
NDEnum : NDEnum.exe
NDEnum.exe : NDEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NDEnum.exe\
    NDEnum.obj $(libs)
NDEnum.obj : NDEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NDGetInfo application
NDGetInfo : NDGetInfo.exe
NDGetInfo.exe : NDGetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NDGetInfo.exe\
    NDGetInfo.obj $(libs)
NDGetInfo.obj : NDGetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NDRemove application
NDRemove : NDRemove.exe
NDRemove.exe : NDRemove.obj
    $(link) $(linkdebug) $(conflags) -out:NDRemove.exe\
    NDRemove.obj $(libs)
NDRemove.obj : NDRemove.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NDSetInfo application
NDSetInfo : NDSetInfo.exe
NDSetInfo.exe : NDSetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NDSetInfo.exe\
    NDSetInfo.obj $(libs)
NDSetInfo.obj : NDSetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe