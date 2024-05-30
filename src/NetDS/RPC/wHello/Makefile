#*******************************************************#
#**                                                   **#
#**           Microsoft RPC Examples                  **#
#**              WHello Application                   **#
#**    Copyright 1991 - 1999 Microsoft Corporation    **#
#**                                                   **#
#*******************************************************#

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

.c.Obj:
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $<

all: WHelloS WHelloC

# Update the resource if necessary
WHello.Res: WHello.Rc WHello.h RPC.Ico WHello.Dlg
    rc -r WHello.Rc

# Update the executable file if necessary, and if so, add the resource back in.
WHelloC : WHelloC.Exe
WHelloC.Exe : WHelloC.Obj WHello.Def WHello_c.Obj WHello.Res
    $(link) $(linkdebug) $(guiflags) -out:WHelloC.Exe -map:WHelloC.Map \
      WHelloC.Obj WHello_c.Obj WHello.Res \
      RPCrt4.lib $(guilibsdll)

WHelloC.Obj : WHelloC.c WHelloC.h WHello.h

WHello_c.Obj : WHello_c.c WHello.h

# Make the WHelloS
WHelloS : WHelloS.Exe
WHelloS.Exe : WHelloS.Obj WHelloP.Obj WHello_s.Obj
    $(link) $(linkdebug) $(conflags) -out:WHelloS.Exe -map:WHelloS.Map \
      WHelloS.Obj WHelloP.Obj WHello_s.Obj \
      RPCrt4.lib $(conlibsdll)

WHelloS.Obj : WHelloS.c WHello.h

WHelloP.Obj : WHelloP.c WHello.h

WHello_s.Obj : WHello_s.c WHello.h

# Make the stubs source
WHello.h WHello_c.c WHello_s.c : WHello.Idl WHello.Acf
    midl -oldnames -cpp_cmd $(cc) -cpp_opt "-E" WHello.Idl

# Clean up everything
cleanall : clean
    -del *.Exe

# Clean up everything but the .Exes
clean :
    -del *.Obj
    -del *.Map
    -del WHello.Res
    -del WHello_c.c
    -del WHello_s.c
    -del WHello.h
