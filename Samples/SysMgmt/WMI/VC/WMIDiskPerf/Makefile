# **************************************************************************
# Copyright (c) 1998 Microsoft Corporation.
#
# File:  makefile.
#
# Description:
#    WMIDiskPerf
#
# History:
#
# **************************************************************************

TARGET  = WMIDiskPerf
OUTFILE = WMIDiskPerf.exe

!if "$(CPU)"=="ALPHA"
MACHINE=ALPHA
!else
MACHINE=I386
!endif


!ifdef DEBUG

OUTDIR=.\Debug   # where to put the exe.
INTDIR=.\Debug   # where to put the objs.

LINK = oleaut32.lib ole32.lib msvcrtd.lib /nologo /NOD /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)\WMIDiskPerf.pdb" /debug /machine:$(MACHINE)\
 /out:"$(OUTDIR)\WMIDiskPerf.exe" /pdbtype:sept 

CFLAGS  = /nologo -I..\..\..\include /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WIN32_DCOM" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

!else

OUTDIR=.\Release
INTDIR=.\Release

LINK = oleaut32.lib ole32.lib msvcrt.lib /nologo /NOD /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)\WMIDiskPerf.pdb" /machine:$(MACHINE)\
 /out:"$(OUTDIR)\WMIDiskPerf.exe" 

CFLAGS = /nologo -I..\..\..\include /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 /D "_WIN32_DCOM" /Fp"$(INTDIR)\WMIDiskPerf.pch" /YX\ /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c /Zl

!endif #DEBUG


#
#obj list.
#

OBJS = WMIDiskPerf.obj \
	dpdetail.obj \

LINK_OBJS = $(INTDIR)\WMIDiskPerf.obj \
	$(INTDIR)\dpdetail.obj \

LIBS = kernel32.lib user32.lib \
 advapi32.lib uuid.lib ..\..\..\lib\wbemuuid.lib

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

WMIDiskPerf.obj : WMIDiskPerf.cpp
dpdetail.obj : dpdetail.cpp

