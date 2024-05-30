#
# MAKEFILE
# WBEMSample 
#
# Copyright (c) 1997-1999 Microsoft Corporation.
#


TARGET  = WBEMSample
OUTFILE = WBEMSample.exe

#
#obj list.
#

!ifndef NODEBUG

OUTDIR=.\Debug   # where to put the exe.
INTDIR=.\Debug   # where to put the objs.

LINK = oleaut32.lib ole32.lib mfco42d.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\WBEMSample.pdb" /debug\
 /out:"$(OUTDIR)\WBEMSample.exe" /pdbtype:sept

CFLAGS  = /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_WIN32_DCOM" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c /Zl

!else

OUTDIR=.\Release
INTDIR=.\Release

LINK = oleaut32.lib ole32.lib mfc42.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\WBEMSample.pdb" /NODEFAULTLIB:MSVCRT.LIB\
 /out:"$(OUTDIR)\WBEMSample.exe"
 
  
CFLAGS  = /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_WIN32_DCOM" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!endif #NODEBUG

OBJS = OfficeDlg.obj \
	OnAddEquipment.obj \
	OnAsync.obj \
	OnConnect.obj \
	OnDiskDetails.obj \
	OnDiskPropsDescriptions.obj \
	OnEnumDisks.obj \
	OnEnumSvcs.obj \
	OnPerm.obj \
	OnRegister.obj \
	OnTemp.obj \
	StdAfx.obj \
	UserInfo.obj \
	WBEMSamp.obj \
	WBEMSampdlg.obj \
	WBEMSample.res \

LINK_OBJS = $(INTDIR)\OfficeDlg.obj \
	$(INTDIR)\OnAddEquipment.obj \
	$(INTDIR)\OnAsync.obj \
	$(INTDIR)\OnConnect.obj \
	$(INTDIR)\OnDiskDetails.obj \
	$(INTDIR)\OnDiskPropsDescriptions.obj \
	$(INTDIR)\OnEnumDisks.obj \
	$(INTDIR)\OnEnumSvcs.obj \
	$(INTDIR)\OnPerm.obj \
	$(INTDIR)\OnRegister.obj \
	$(INTDIR)\OnTemp.obj \
	$(INTDIR)\StdAfx.obj \
	$(INTDIR)\UserInfo.obj \
	$(INTDIR)\WBEMSamp.obj \
	$(INTDIR)\WBEMSampdlg.obj \
	WBEMSample.res \


LIBS = kernel32.lib uuid.lib wbemuuid.lib

.SUFFIXES: .h .obj .dll .cpp  

!ifdef CLEAN
goal:   clean
!else
goal:   $(OUTFILE)
!endif #CLEAN

clean:
    if exist *.pch del *.pch
    if exist *.obj del *.obj
    if exist *.exe del *.exe
    if exist *.dll del *.dll
    if exist *.pdb del *.pdb
    if exist *.exp del *.exp
    if exist *.lib del *.lib
    if exist *.ilk del *.ilk
    if exist *.map del *.map
    if exist *.vcp del *.vcp

.cpp.obj:
	if not exist $(INTDIR) md $(INTDIR)
    cl $(CFLAGS) $*.cpp


$(OUTFILE) : $(OBJS) $(DEFFILE)
    link @<<    
    $(LINK)
    $(LINK_OBJS)
    $(LIBS) 
<<

##### Dependencies #####

OfficeDlg.obj : OfficeDlg.cpp officedlg.h StdAfx.h wbemsamp.h
OnAddEquipment.obj : OnAddEquipment.cpp officedlg.h StdAfx.h wbemsampdlg.h
OnAsync.obj : OnAsync.cpp onasync.h StdAfx.h wbemsampdlg.h
OnConnect.obj : OnConnect.cpp StdAfx.h wbemsampdlg.h
OnDiskDetails.obj : OnDiskDetails.cpp StdAfx.h wbemsampdlg.h
OnEnumDisks.obj : OnEnumDisks.cpp StdAfx.h wbemsampdlg.h
OnEnumSvcs.obj : OnEnumSvcs.cpp StdAfx.h wbemsampdlg.h
OnPerm.obj : OnPerm.cpp StdAfx.h wbemsampdlg.h
OnRegister.obj : OnRegister.cpp StdAfx.h userinfo.h wbemsampdlg.h
OnTemp.obj : OnTemp.cpp ontemp.h StdAfx.h wbemsampdlg.h
StdAfx.obj      : StdAfx.cpp StdAfx.h
UserInfo.obj : UserInfo.cpp StdAfx.h userinfo.h wbemsamp.h
WBEMSamp.obj : WBEMSamp.cpp stdAfx.h wbemsamp.h wbemsampdlg.h
WBEMSampdlg.obj : WBEMSampdlg.cpp onasync.h ontemp.h StdAfx.h wbemsamp.h wbemsampdlg.h
WBEMSample.res : WBEMSample.rc
