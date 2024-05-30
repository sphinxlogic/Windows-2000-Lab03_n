Proj = InvokObj

!include <Win32.Mak>

All: InvokObj.Dll

InvokObj.Obj: InvokObj.cpp
  $(cc) $(cdebug) $(cflags) $(cvarsdll) InvokObj.cpp

InvokObj.Dll: $*.Obj $*.Exp
     $(link) $(linkdebug) $(dlllflags) -base:0x1C000000 -out:InvokObj.dll  \
      InvokObj.Obj InvokObj.Exp  $(guilibsdll) comsupp.lib ole32.lib oleaut32.lib uuid.lib

InvokObj.Exp: InvokObj.Def InvokObj.Obj
  $(implib) -machine:$(CPU) -nologo -Def:InvokObj.Def -Out:InvokObj.Lib \
    InvokObj.Obj

Clean:
    -@for %a in (*.obj *.exp *.lib *.ncb *.opt *.plg *.tlh *.tli) do del %a

Cleanall:
    -@for %a in (*.obj *.exp InvokObj.dll *.lib *.ncb *.opt *.plg *.tlh *.tli) do del %a

