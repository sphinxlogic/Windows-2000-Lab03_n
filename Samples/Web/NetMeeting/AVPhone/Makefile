# NetMeeting AVPhone makefile
# Copyright 1995 - 1998 Microsoft Corporation

Proj = AVPhone

ObjList =  $(@D)\Main.Obj $(@D)\Main.Res $(@D)\CallNtfy.Obj $(@D)\ClUtil.Obj \
           $(@D)\CnfNtfy.Obj $(@D)\ImsConf2.Obj $(@D)\MgrNtfy.Obj $(@D)\Conf.Obj

!include <INetSDK.Mak>

All: $(ObjDir)\Main.Exe
  Copy $? $(ObjDir)\$(Proj).Exe

$(ObjDir)\Main.Exe: $(ObjList)

$(ObjDir)\CallNtfy.Obj: $(@B).Cpp $(@D)\IMSConf2.h

$(ObjDir)\ClUtil.Obj: $(@B).Cpp $(@D)\IMSConf2.h

$(ObjDir)\CnfNtfy.Obj: $(@B).Cpp $(@D)\IMSConf2.h

$(ObjDir)\Conf.Obj: $(@B).Cpp $(@D)\IMSConf2.h

$(ObjDir)\IMSConf2.Obj: $(@R).C $(@D)\IMSConf2.h

$(ObjDir)\Main.Obj: $(@B).Cpp $(@D)\IMSConf2.h

$(ObjDir)\MgrNtfy.Obj: $(@B).Cpp $(@D)\IMSConf2.h

$(ObjDir)\IMSConf2.h $(ObjDir)\IMSConf2.c: IMSConf2.Idl
    $(MkDest)
!if "$(LOG)"=="YES"
    @echo midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata\
           $(@D)\dlldata.rpc /proxy $(@R).rpc /header $(@R).h /iid $(@R).c $? $(LogCmd)
!endif
  midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata\
      $(@D)\dlldata.rpc /proxy $(@R).rpc /header $(@R).h /iid $(@R).c $?

# C Targets
{$(ObjDir)\}.c{$(ObjDir)\}.obj:
    $(MkDest)
!if "$(LOG)"=="YES"
    @echo $(CC) $(CL) $(crtflags) $(cDefines) $< $(LogCmd)
!endif
    $(CC) $(CL) $(crtflags) $(cDefines) $< $(LogCmd)
