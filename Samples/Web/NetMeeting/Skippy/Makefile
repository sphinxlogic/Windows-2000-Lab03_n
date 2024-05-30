Proj= Skippy

!include <BkOffice.mak>
 
ObjList =  $(ObjDir)\$(Proj).obj    \
           $(ObjDir)\Attrib.obj     \
	   $(ObjDir)\Filter.obj     \
	   $(ObjDir)\ils.obj        \
	   $(ObjDir)\Notify.obj     \
	   $(ObjDir)\ObList.obj     \
	   $(ObjDir)\Proto.obj      \
	   $(ObjDir)\SvrInfo.obj    \
	   $(ObjDir)\Users.obj      \
	   $(ObjDir)\UsrInfo.obj    \
	   $(ObjDir)\Utils.obj      \
           $(ObjDir)\$(Proj).res

libs= $(libs) comctl32.lib oleaut32.lib shell32.lib

all: $(ObjDir)\$(Proj).exe 

$(ObjDir)\$(Proj).exe: $(ObjList) 


$(ObjDir)\$(Proj).obj: $(ObjDir)\Main.obj  
  copy $(ObjDir)\Main.obj $(ObjDir)\$(Proj).obj

$(ObjDir)\Main.obj: $(ObjDir)\ils.h 

$(ObjDir)\ils.obj: $(@B).c 

$(ObjDir)\ils.h $(ObjDir)\ils.c: $(@B).Idl
    $(MkDest)
    midl /iid $(@B).c /header $(ObjDir)\$(@B).h $? $(LogCmd) 






