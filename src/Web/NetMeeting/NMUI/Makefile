Proj=  NMUI

!include <BkOffice.mak>


ObjList = $(ObjDir)\$(Proj).obj   \
          $(ObjDir)\CCall.obj     \
          $(ObjDir)\CChan.obj     \
          $(ObjDir)\CConf.obj     \
          $(ObjDir)\cData.obj     \
          $(ObjDir)\clUtil.obj    \
          $(ObjDir)\Cmd.obj       \
          $(ObjDir)\cMemb.obj     \
          $(ObjDir)\cMgr.obj      \
          $(ObjDir)\cvideo.obj    \
          $(ObjDir)\Debug.obj     \
          $(ObjDir)\Dlg.obj       \
	  $(ObjDir)\imsconf2.obj  \
          $(ObjDir)\Init.obj      \
          $(ObjDir)\Msg.obj       \
          $(ObjDir)\rtns.obj      \
          $(ObjDir)\sBar.obj      \
          $(ObjDir)\Util.obj      \
          $(ObjDir)\Res.res

libs= $(libs) comctl32.lib oleaut32.lib shell32.lib

all: $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList)

$(ObjDir)\$(Proj).obj: $(ObjDir)\Main.obj  
  copy $(ObjDir)\Main.obj $(ObjDir)\$(Proj).obj

$(ObjDir)\Main.obj: $(ObjDir)\imsconf2.h 

$(ObjDir)\imsconf2.obj: $(@B).c 

$(ObjDir)\imsconf2.h $(ObjDir)\imsconf2.c: $(@B).Idl
    $(MkDest)
    midl /iid $(@B).c /header $(ObjDir)\$(@B).h $? $(LogCmd) 
