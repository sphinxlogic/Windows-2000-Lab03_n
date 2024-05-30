# **************************************************************************
# Copyright (c) 1997-1999 Microsoft Corporation.
#
# File:  MAKEFILE
#
# Description:
#    nmake make file for WMI Permanent Event Consumer sample
#
# History:
#
# **************************************************************************

TARGET  = WBEMPermEvents
OUTFILE = WBEMPermEvents.exe

#
#obj list.
#

#if DEBUG  :)
!ifndef NODEBUG

OUTDIR=.\Debug   # where to put the exe.
INTDIR=.\Debug   # where to put the objs.

LINK = oleaut32.lib ole32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\WBEMPermEvents.pdb" /debug\
 /out:"$(OUTDIR)\WBEMPermEvents.exe" /pdbtype:sept

CFLAGS = /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_WIN32_DCOM" /Fp"$(INTDIR)\WBEMPermEvents.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!else

OUTDIR=.\Release
INTDIR=.\Release

LINK = oleaut32.lib ole32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\WBEMPermEvents.pdb"\
 /out:"$(OUTDIR)\WBEMPermEvents.exe"
  
CFLAGS = /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_WIN32_DCOM" /Fp"$(INTDIR)\WBEMPermEvents.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!endif #NODEBUG

OBJS = Consumer.obj \
	factory.obj \
	provider.obj \
	StdAfx.obj \
	WBEMPermEvents.obj \
	WBEMPermEvents.res \
	WBEMPermEventsDlg.obj \

LINK_OBJS = $(INTDIR)\Consumer.obj \
	$(INTDIR)\factory.obj \
	$(INTDIR)\Provider.obj \
	$(INTDIR)\StdAfx.obj \
	$(INTDIR)\WBEMPermEvents.obj \
	WBEMPermEvents.res \
	$(INTDIR)\WBEMPermEventsDlg.obj \

LIBS = kernel32.lib user32.lib gdi32.lib comdlg32.lib \
 advapi32.lib uuid.lib wbemuuid.lib

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

Consumer.obj : Consumer.cpp Consumer.h StdAfx.h
factory.obj : factory.cpp Provider.h factory.h stdAfx.h
Provider.obj : provider.cpp Provider.h consumer.h stdAfx.h
StdAfx.cpp : StdAfx.h
WBEMPermEvents.obj : WBEMPermEvents.cpp factory.h StdAfx.h WBEMPermEvents.h WBEMPermEventsDlg.h
WBEMPermEvents.res : WBEMPermEvents.rc
WBEMPermEventsDlg.obj : WBEMPermEventsDlg.cpp factory.h StdAfx.h WBEMPermEvents.h WBEMPermEventsDlg.h


