Proj= WBAddrbook

libs=$(libs) wininet.lib shell32.lib -def:$(Proj).Def

dll=1
  
ObjList =  $(ObjDir)\$(Proj).Obj       \
           $(ObjDir)\WBWAB.Obj         \
           $(ObjDir)\StdAfx.Obj     


!include <BkOffice.Mak>

all: $(ObjDir)\$(Proj).dll 

$(ObjDir)\$(Proj).dll: $(ObjList) 

$(ObjDir)\$(Proj).Obj: $(ObjDir)\$(Proj).h

$(ObjDir)\$(Proj).h: $(Proj).Idl
    $(MkDest)
    midl /Oicf /h $(Proj).h $? $(LogCmd) 