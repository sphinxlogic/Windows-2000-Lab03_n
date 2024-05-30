Proj=MQApiTst

Use_MFC=1
crtdll=1

ObjList=$(@R).Obj          \
        $(@D)\ClosQDlg.Obj \
        $(@D)\CRQDlg.Obj   \
        $(@D)\DelQDlg.Obj  \
        $(@D)\LocatDlg.Obj \
        $(@D)\MainFrm.Obj  \
        $(@D)\MQApiTst.Res \
        $(@D)\OpenQDlg.Obj \
        $(@D)\RecvMDlg.Obj \
        $(@D)\RecWDlg.Obj  \
        $(@D)\SendMDlg.Obj \
        $(@D)\StdAfx.Obj   \
        $(@D)\TestdOC.Obj  \
        $(@D)\TestView.Obj

!include $(BASEMAKE)

linkflags = $(linkflags) mqrt.Lib wsock32.Lib

all:	$(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe: $(ObjList)
