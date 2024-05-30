#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Samples                   **#
#**                   WinTyp Application                    **#
#**       Copyright 1992 - 1999 Microsoft Corporation       **#
#**                                                         **#
#** This is the makefile used to make the Client and the    **#
#** Server for the WinTyp sample program where the Client   **#
#** sends a bitmap to the Server for either flipping or     **#
#** edge detection. The bitmap is thensent back to the      **#
#** Client.                                                 **#
#** This file will compile for ANSI characters, to compile  **#
#** for UNICODE, type nmake /f makefile.uni at command line **#
#*************************************************************#
# FILE : MAKEFILE

!include <Win32.Mak>

# Let the compiler know what version we are running
cflags=$(cflags) -D_WIN32_WINNT=0x400

all: Client Server

Client : Client.Exe
Client.Exe : Client.Obj WinTyp_c.Obj Client.Res
    $(link) $(linkdebug) $(guiflags) -out:Client.Exe -map:Client.Map \
      Client.Obj Client.Res WinTyp_c.Obj rpcrt4.Lib $(olelibsdll)

Client.Obj : Client.c Client.h WinTyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

WinTyp_c.Obj : WinTyp_c.c WinTyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

Server : Server.Exe
Server.Exe : Server.Obj WinTyp_s.Obj Remote.Obj
    $(link) $(linkdebug) $(conflags) -out:Server.Exe -map:Server.Map\
      Server.Obj WinTyp_s.Obj Remote.Obj rpcrt4.Lib  $(conlibsdll) \
      $(olelibsdll) 


Server.Obj : Server.c Common.h WinTyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

Remote.Obj : Remote.c Common.h WinTyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

WinTyp_s.Obj : WinTyp_s.c WinTyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
WinTyp.h WinTyp_c.c WinTyp_s.c : WinTyp.Idl
    midl $(midlflags) -cpp_cmd $(cc) WinTyp.Idl


# Compile the resource file, and then convert it to an object file to include
Client.Res : Client.Rc CliRes.h
    $(RC) -r -DWIN32 -DWINVER=0x400  Client.Rc

clean:
    -del Client.Exe
    -del Server.Exe

cleanall:  clean
    -del *.Obj
    -del *.Map
    -del *.Res
    -del WinTyp_*.c
    -del WinTyp.h
