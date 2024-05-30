Use_MFC = 1
Proj = imp_draw

ObjList = $(ObjDir)\DRAWAREA.obj       \
          $(ObjDir)\Imp_Draw.obj       \
          $(ObjDir)\Imp_DrawDlg.obj    \
          $(ObjDir)\LOGINDLG.obj       \
          $(ObjDir)\MQEventHandler.obj \
          $(ObjDir)\StdAfx.obj         \
          $(ObjDir)\imp_draw.res

!include <bkoffice.mak>

ALL : $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList)
    $(LINK) $(LFLAGS) $(linkflags) $**
