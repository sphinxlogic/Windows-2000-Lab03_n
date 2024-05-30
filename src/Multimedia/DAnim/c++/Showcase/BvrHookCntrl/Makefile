# Microsoft Developer Studio Generated NMAKE File, Based on BvrHookCntrl.dsp
!IF "$(CFG)" == ""
CFG=BvrHookCntrl - Win32 Release
!MESSAGE No configuration specified. Defaulting to BvrHookCntrl - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "BvrHookCntrl - Win32 Release" && "$(CFG)" !=\
 "BvrHookCntrl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BvrHookCntrl.mak" CFG="BvrHookCntrl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BvrHookCntrl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BvrHookCntrl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BvrHookCntrl - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\BvrHookCntrl.exe"

!ELSE 

ALL : "$(OUTDIR)\BvrHookCntrl.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bvrhook.obj"
	-@erase "$(INTDIR)\ctlhost.obj"
	-@erase "$(INTDIR)\ctlhost.res"
	-@erase "$(INTDIR)\dactl.obj"
	-@erase "$(INTDIR)\notifiers.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\BvrHookCntrl.exe"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\BvrHookCntrl.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ctlhost.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BvrHookCntrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=daguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\BvrHookCntrl.pdb" \
 /out:"$(OUTDIR)\BvrHookCntrl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bvrhook.obj" \
	"$(INTDIR)\ctlhost.obj" \
	"$(INTDIR)\ctlhost.res" \
	"$(INTDIR)\dactl.obj" \
	"$(INTDIR)\notifiers.obj"

"$(OUTDIR)\BvrHookCntrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BvrHookCntrl - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\BvrHookCntrl.exe"

!ELSE 

ALL : "$(OUTDIR)\BvrHookCntrl.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bvrhook.obj"
	-@erase "$(INTDIR)\ctlhost.obj"
	-@erase "$(INTDIR)\ctlhost.res"
	-@erase "$(INTDIR)\dactl.obj"
	-@erase "$(INTDIR)\notifiers.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\BvrHookCntrl.exe"
	-@erase "$(OUTDIR)\BvrHookCntrl.ilk"
	-@erase "$(OUTDIR)\BvrHookCntrl.pdb"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\BvrHookCntrl.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ctlhost.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BvrHookCntrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=daguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\BvrHookCntrl.pdb" \
 /out:"$(OUTDIR)\BvrHookCntrl.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bvrhook.obj" \
	"$(INTDIR)\ctlhost.obj" \
	"$(INTDIR)\ctlhost.res" \
	"$(INTDIR)\dactl.obj" \
	"$(INTDIR)\notifiers.obj"

"$(OUTDIR)\BvrHookCntrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "BvrHookCntrl - Win32 Release" || "$(CFG)" ==\
 "BvrHookCntrl - Win32 Debug"
SOURCE=.\bvrhook.cpp
DEP_CPP_BVRHO=\
	".\ctlhost.h"\
	".\dactl.h"\
	".\notifiers.h"\
	

"$(INTDIR)\bvrhook.obj" : $(SOURCE) $(DEP_CPP_BVRHO) "$(INTDIR)"


SOURCE=.\ctlhost.cpp
DEP_CPP_CTLHO=\
	".\ctlhost.h"\
	".\dactl.h"\
	".\notifiers.h"\
	

"$(INTDIR)\ctlhost.obj" : $(SOURCE) $(DEP_CPP_CTLHO) "$(INTDIR)"


SOURCE=.\ctlhost.rc
DEP_RSC_CTLHOS=\
	".\Dxm.ico"\
	

"$(INTDIR)\ctlhost.res" : $(SOURCE) $(DEP_RSC_CTLHOS) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\dactl.cpp
DEP_CPP_DACTL=\
	".\dactl.h"\
	".\notifiers.h"\
	

"$(INTDIR)\dactl.obj" : $(SOURCE) $(DEP_CPP_DACTL) "$(INTDIR)"


SOURCE=.\notifiers.cpp
DEP_CPP_NOTIF=\
	".\notifiers.h"\
	

"$(INTDIR)\notifiers.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"



!ENDIF 

