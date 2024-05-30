#*************************************************************#
#**                                                         **#
#**             Microsoft NShXXX Examples                   **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NShAdd NShCheck NShDel NShEnum NShGetInfo NShSetInfo

# Make NShAdd application
NShAdd : NShAdd.exe
NShAdd.exe : NShAdd.obj
    $(link) $(linkdebug) $(conflags) -out:NShAdd.exe\
    NShAdd.obj $(libs)
NShAdd.obj : NShAdd.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NShCheck application
NShCheck : NShCheck.exe
NShCheck.exe : NShCheck.obj
    $(link) $(linkdebug) $(conflags) -out:NShCheck.exe\
    NShCheck.obj $(libs)
NShCheck.obj : NShCheck.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c
    
# Make NShDel application
NShDel : NShDel.exe
NShDel.exe : NShDel.obj
    $(link) $(linkdebug) $(conflags) -out:NShDel.exe\
    NShDel.obj $(libs)
NShDel.obj : NShDel.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c
    
# Make NShEnum application
NShEnum : NShEnum.exe
NShEnum.exe : NShEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NShEnum.exe\
    NShEnum.obj $(libs)
NShEnum.obj : NShEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NShGetInfo application
NShGetInfo : NShGetInfo.exe
NShGetInfo.exe : NShGetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NShGetInfo.exe\
    NShGetInfo.obj $(libs)
NShGetInfo.obj : NShGetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NShSetInfo application
NShSetInfo : NShSetInfo.exe
NShSetInfo.exe : NShSetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NShSetInfo.exe\
    NShSetInfo.obj $(libs)
NShSetInfo.obj : NShSetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


clean:
   -del *.obj


cleanall: clean
   -del *.exe