#*************************************************************#
#**                                                         **#
#**             Microsoft NUXXX Examples                    **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all :   NUAdd NUChPwd NUDel\
        NUEnum NUGetGroups NUGetInfo\
        NUGetLGroups NUModalsGet\
        NUModalsSet NUSetGroups NUSetInfo

# Make NUAdd application
NUAdd : NUAdd.exe
NUAdd.exe : NUAdd.obj
    $(link) $(linkdebug) $(conflags) -out:NUAdd.exe\
    NUAdd.obj $(libs)
NUAdd.obj : NUAdd.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUChPwd application
NUChPwd : NUChPwd.exe
NUChPwd.exe : NUChPwd.obj
    $(link) $(linkdebug) $(conflags) -out:NUChPwd.exe\
    NUChPwd.obj $(libs)
NUChPwd.obj : NUChPwd.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c
    
# Make NUDel application
NUDel : NUDel.exe
NUDel.exe : NUDel.obj
    $(link) $(linkdebug) $(conflags) -out:NUDel.exe\
    NUDel.obj $(libs)
NUDel.obj : NUDel.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c
    
# Make NUEnum application
NUEnum : NUEnum.exe
NUEnum.exe : NUEnum.obj
    $(link) $(linkdebug) $(conflags) -out:NUEnum.exe\
    NUEnum.obj $(libs)
NUEnum.obj : NUEnum.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUGetGroups application
NUGetGroups : NUGetGroups.exe
NUGetGroups.exe : NUGetGroups.obj
    $(link) $(linkdebug) $(conflags) -out:NUGetGroups.exe\
    NUGetGroups.obj $(libs)
NUGetGroups.obj : NUGetGroups.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUGetInfo application
NUGetInfo : NUGetInfo.exe
NUGetInfo.exe : NUGetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NUGetInfo.exe\
    NUGetInfo.obj $(libs)
NUGetInfo.obj : NUGetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUGetLGroups application
NUGetLGroups : NUGetLGroups.exe
NUGetLGroups.exe : NUGetLGroups.obj
    $(link) $(linkdebug) $(conflags) -out:NUGetLGroups.exe\
    NUGetLGroups.obj $(libs)
NUGetLGroups.obj : NUGetLGroups.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUModalsGet application
NUModalsGet : NUModalsGet.exe
NUModalsGet.exe : NUModalsGet.obj
    $(link) $(linkdebug) $(conflags) -out:NUModalsGet.exe\
    NUModalsGet.obj $(libs)
NUModalsGet.obj : NUModalsGet.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUModalsSet application
NUModalsSet : NUModalsSet.exe
NUModalsSet.exe : NUModalsSet.obj
    $(link) $(linkdebug) $(conflags) -out:NUModalsSet.exe\
    NUModalsSet.obj $(libs)
NUModalsSet.obj : NUModalsSet.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUSetGroups application
NUSetGroups : NUSetGroups.exe
NUSetGroups.exe : NUSetGroups.obj
    $(link) $(linkdebug) $(conflags) -out:NUSetGroups.exe\
    NUSetGroups.obj $(libs)
NUSetGroups.obj : NUSetGroups.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NUSetInfo application
NUSetInfo : NUSetInfo.exe
NUSetInfo.exe : NUSetInfo.obj
    $(link) $(linkdebug) $(conflags) -out:NUSetInfo.exe\
    NUSetInfo.obj $(libs)
NUSetInfo.obj : NUSetInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


clean:
   -del *.obj


cleanall: clean
   -del *.exe