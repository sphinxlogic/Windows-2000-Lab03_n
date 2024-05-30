Use_MFC = 1
Proj = c_draw



ObjList = $(ObjDir)\disdraw.obj   \
          $(ObjDir)\drawarea.obj  \
          $(ObjDir)\drawdlg.obj   \
          $(ObjDir)\logindlg.obj  \
          $(ObjDir)\StdAfx.obj    \
          $(ObjDir)\disdraw.res

!include <bkoffice.mak>

ALL : $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList)
    $(LINK) $(LFLAGS) $(linkflags) $** mqrt.lib
