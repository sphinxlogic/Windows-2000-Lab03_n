#*************************************************************#
#**                                                         **#
#**             Microsoft NetAlertXXX Examples              **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#

!include <win32.mak>

libs = $(conlibsdll) netapi32.lib

all : NARaise NARaiseEx

# Make NARaise application
NARaise : NARaise.exe
NARaise.exe : NARaise.obj
    $(link) $(linkdebug) $(conflags) -out:NARaise.exe\
    NARaise.obj $(libs)
NARaise.obj : NARaise.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make NARaiseEx application
NARaiseEx : NARaiseEx.exe
NARaiseEx.exe : NARaiseEx.obj
    $(link) $(linkdebug) $(conflags) -out:NARaiseEx.exe\
    NARaiseEx.obj $(libs)
NARaiseEx.obj : NARaiseEx.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

clean:
   -del *.obj

cleanall: clean
   -del *.exe