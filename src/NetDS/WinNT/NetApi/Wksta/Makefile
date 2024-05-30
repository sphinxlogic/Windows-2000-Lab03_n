#*************************************************************#
#**                                                         **#
#**             Microsoft NWXXX Examples                    **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NWGetInfo NWSetInfo NWUEnum NWUGetInfo NWUSetInfo

# Make NWGetInfo application
NWGetInfo : NWGetInfo.exe
NWGetInfo.exe : NWGetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NWGetInfo.exe\
    NWGetInfo.obj $(libs)
NWGetInfo.obj : NWGetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NWSetInfo application
NWSetInfo : NWSetInfo.exe
NWSetInfo.exe : NWSetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NWSetInfo.exe\
    NWSetInfo.obj $(libs)
NWSetInfo.obj : NWSetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NWUEnum application
NWUEnum : NWUEnum.exe
NWUEnum.exe : NWUEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NWUEnum.exe\
    NWUEnum.obj $(libs)
NWUEnum.obj : NWUEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NWUGetInfo application
NWUGetInfo : NWUGetInfo.exe
NWUGetInfo.exe : NWUGetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NWUGetInfo.exe\
    NWUGetInfo.obj $(libs)
NWUGetInfo.obj : NWUGetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NWUSetInfo application
NWUSetInfo : NWUSetInfo.exe
NWUSetInfo.exe : NWUSetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NWUSetInfo.exe\
    NWUSetInfo.obj $(libs)
NWUSetInfo.obj : NWUSetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe