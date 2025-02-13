#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   inout Application                     **#
#**       Copyright 1992 - 1999 Microsoft Corporation       **#
#**                                                         **#
#*************************************************************#

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : inoutc inouts

# Make the inout client
inoutc : inoutc.exe
inoutc.exe : inoutc.obj inout_c.obj
    $(link) $(linkdebug) $(conflags) -out:inoutc.exe \
      inoutc.obj inout_c.obj \
      rpcrt4.lib $(conlibsdll)

# inout client main program
inoutc.obj : inoutc.c inout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# inout client stub
inout_c.obj : inout_c.c inout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the inout server
inouts : inouts.exe
inouts.exe : inouts.obj inoutp.obj inout_s.obj
    $(link) $(linkdebug) $(conflags) -out:inouts.exe \
      inouts.obj inout_s.obj inoutp.obj \
      rpcrt4.lib $(conlibsdll)

# inout server main loop
inouts.obj : inouts.c inout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
inoutp.obj : inoutp.c inout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# inout server stub file
inout_s.obj : inout_s.c inout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
inout.h inout_c.c inout_s.c : inout.idl inout.acf
    midl -oldnames -no_cpp inout.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del inout_c.c
    -del inout_s.c
    -del inout.h
