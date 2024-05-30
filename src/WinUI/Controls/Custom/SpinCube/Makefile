!include <Win32.Mak>

all: SpinTest.Exe SpinCube.Dll

SpinTest.Obj: SpinTest.c
    $(cc) $(cdebug) $(cflags) $(cvarsdll) SpinTest.c

SpinCube.Obj: SpinCube.c SpinCube.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) SpinCube.c

Paint.Obj: Paint.c Paint.h SpinCube.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) Paint.c

SpinTest.Res: SpinTest.Rc SpinTest.h SpinTest.Dlg
    $(rc) $(rcvars) -r -fo SpinTest.Res SpinTest.Rc

SpinCube.Res: SpinCube.Rc
    $(rc) $(rcvars) -r -fo SpinCube.Res SpinCube.Rc

SpinCube.Lib: SpinCube.Obj Paint.Obj SpinCube.Def SpinCube.Res
     $(implib) -machine:$(CPU) \
     -def:SpinCube.Def   \
!IF "$(CPU)" == "i386"
     SpinCube.Obj Paint.Obj \
!ENDIF
     -out:SpinCube.Lib

SpinCube.Dll: SpinCube.Obj Paint.Obj SpinCube.Def SpinCube.Res
    $(link) $(linkdebug) $(dlllflags) \
    -base:0x1C000000     \
    -out:SpinCube.Dll    \
    SpinCube.Obj SpinCube.Exp SpinCube.Res Paint.Obj $(guilibsdll)

SpinTest.Exe: SpinTest.Obj SpinCube.Lib SpinTest.Res SpinTest.Def
    $(link) $(linkdebug) $(guiflags) -out:SpinTest.Exe SpinTest.Obj SpinTest.Res SpinCube.Lib $(guilibsdll)
