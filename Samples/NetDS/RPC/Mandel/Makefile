#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**               Mandelbrot RPC Application                **#
#**          Copyright 1991 - 1999 Microsoft Corporation    **#
#**                                                         **#
#*************************************************************#
# The same source code is used to build either a standalone
# or an RPC version of the Microsoft Windows (R) Mandelbrot
# sample application.  The flag RPC determines which version
# is built.  To build a standalone version, use the commands:
#     >nmake cleanall
#     >set NOTRPC=1
#     >nmake
# To build the RPC version, use the commands:
#     >nmake cleanall
#     >set NOTRPC=
#     >nmake
!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

!ifdef NOTRPC
RPCFLAG =
!else
RPCFLAG = -DRPC
!endif

.c.Obj:
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $(RPCFLAG) $<

# Targets
# The RPC version produces Client and Server executables.
# The standalone version produces a single exe file, "Mandel".

!ifndef NOTRPC
all: Client.Exe Server.Exe
!else
all: Mandel.Exe
!endif

Mandel.Exe: Mandel.Obj Remote.Obj Mandel.def Mandel.Res Calc.Obj
    $(link) $(linkdebug) $(guiflags) -out:Mandel.Exe -map:Mandel.Map \
      Mandel.Obj Remote.Obj Calc.Obj Mandel.Res $(guilibsdll)

Client.Exe: Mandel.Obj Remote.Obj Mandel.def Mandel.Res MdlRPC_c.Obj
    $(link) $(linkdebug) $(guiflags) -out:Client.Exe -map:Client.Map \
      Mandel.Obj Remote.Obj MdlRPC_c.Obj \
      Mandel.Res RPCrt4.lib $(guilibsdll)

Server.Exe: Server.Obj Calc.Obj MdlRPC_s.Obj
    $(link) $(linkdebug) $(conflags) -out:Server.Exe -map:Server.Map \
      Server.Obj Calc.Obj MdlRPC_s.Obj \
      RPCrt4.lib $(conlibsdll)

# Update the resource if necessary
Mandel.Res: Mandel.Rc Mandel.h
    rc -r Mandel.Rc

# Object file dependencies

# Server only built for RPC version; always needs MdlRPC.h
Server.Obj: Server.c Mandel.h MdlRPC.h

# Compile differently for RPC, standalone versions
!ifndef NOTRPC
Mandel.Obj: Mandel.c Mandel.h MdlRPC.h
Remote.Obj: Remote.c Mandel.h MdlRPC.h
Calc.Obj  : Calc.c Mandel.h MdlRPC.h
!else
Mandel.Obj: Mandel.c Mandel.h
Remote.Obj: Remote.c Mandel.h
Calc.Obj  : Calc.c Mandel.h
!endif

# Client stub
MdlRPC_c.Obj : MdlRPC_c.c MdlRPC.h

# Server stub file
MdlRPC_s.Obj : MdlRPC_s.c MdlRPC.h

# Stubs and header file from the IDL file
MdlRPC.h MdlRPC_c.c MdlRPC_s.c: MdlRPC.idl MdlRPC.acf
    midl -oldnames -cpp_cmd $(cc) -cpp_opt "-E" MdlRPC.idl

clean:
    -del Client.Exe
    -del Server.Exe
    -del Mandel.Exe

cleanall:  clean
    -del *.Obj
    -del *.Map
    -del *.Res
    -del MdlRPC_*.c
    -del MdlRPC.h
