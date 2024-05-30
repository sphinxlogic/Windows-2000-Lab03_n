Proj= printsdi

Use_MFC=1

CL= $(CL) "/D_WIN32_IE=0x0400" 



!include <BkOffice.mak>

libs=$(libs) winfax.lib

ObjList =  $(ObjDir)\$(Proj).obj   \
           $(ObjDir)\faxdlg.obj   \
           $(ObjDir)\mainfrm.obj   \
           $(ObjDir)\newdocdlg.obj   \
           $(ObjDir)\printsdi.res   \
           $(ObjDir)\printsdivw.obj   \
           $(ObjDir)\sdidoc.obj   \
           $(ObjDir)\stdafx.obj
 

all: $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList) 

