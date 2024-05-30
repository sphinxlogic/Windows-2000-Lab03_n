Proj=  Chat2000

Use_MFC=1

CL= $(CL) "/D_WIN32_IE=0x0400" 

!include <BkOffice.mak>
 
ObjList =  $(ObjDir)\$(Proj).obj    \
	   $(ObjDir)\BanDlg.obj     \
	   $(ObjDir)\c2Doc.obj	    \
	   $(ObjDir)\c2view.obj     \
	   $(ObjDir)\ChildFrm.obj   \
	   $(ObjDir)\EnterDlg.obj   \
	   $(ObjDir)\InfoDlg.obj    \
	   $(ObjDir)\Kickban.obj    \
	   $(ObjDir)\MainFrm.obj    \
	   $(ObjDir)\MSChat.obj     \
	   $(ObjDir)\Partic.obj     \
	   $(ObjDir)\StdAfx.obj     \
           $(ObjDir)\topicDlg.obj   \
           $(ObjDir)\$(Proj).res

all: $(ObjDir)\$(Proj).exe 

$(ObjDir)\$(Proj).exe: $(ObjList) 
