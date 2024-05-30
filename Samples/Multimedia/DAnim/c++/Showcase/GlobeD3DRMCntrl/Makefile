# Microsoft Developer Studio Generated NMAKE File, Based on globeD3DRMCntrl.dsp
!IF "$(CFG)" == ""
CFG=globeD3DRMCntrl - Win32 Release
!MESSAGE No configuration specified. Defaulting to globeD3DRMCntrl - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "globeD3DRMCntrl - Win32 Release" && "$(CFG)" !=\
 "globeD3DRMCntrl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "globeD3DRMCntrl.mak" CFG="globeD3DRMCntrl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "globeD3DRMCntrl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "globeD3DRMCntrl - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "globeD3DRMCntrl - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\globeD3DRMCntrl.exe"

!ELSE 

ALL : "$(OUTDIR)\globeD3DRMCntrl.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ctlhost.obj"
	-@erase "$(INTDIR)\ctlhost.res"
	-@erase "$(INTDIR)\dactl.obj"
	-@erase "$(INTDIR)\globeD3DRM.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\globeD3DRMCntrl.exe"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\globeD3DRMCntrl.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ctlhost.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\globeD3DRMCntrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=d3drm.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\globeD3DRMCntrl.pdb" \
 /out:"$(OUTDIR)\globeD3DRMCntrl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ctlhost.obj" \
	"$(INTDIR)\ctlhost.res" \
	"$(INTDIR)\dactl.obj" \
	"$(INTDIR)\globeD3DRM.obj"

"$(OUTDIR)\globeD3DRMCntrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "globeD3DRMCntrl - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\globeD3DRMCntrl.exe"

!ELSE 

ALL : "$(OUTDIR)\globeD3DRMCntrl.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ctlhost.obj"
	-@erase "$(INTDIR)\ctlhost.res"
	-@erase "$(INTDIR)\dactl.obj"
	-@erase "$(INTDIR)\globeD3DRM.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\globeD3DRMCntrl.exe"
	-@erase "$(OUTDIR)\globeD3DRMCntrl.ilk"
	-@erase "$(OUTDIR)\globeD3DRMCntrl.pdb"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\globeD3DRMCntrl.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ctlhost.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\globeD3DRMCntrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=d3drm.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\globeD3DRMCntrl.pdb" /debug \
 /out:"$(OUTDIR)\globeD3DRMCntrl.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ctlhost.obj" \
	"$(INTDIR)\ctlhost.res" \
	"$(INTDIR)\dactl.obj" \
	"$(INTDIR)\globeD3DRM.obj"

"$(OUTDIR)\globeD3DRMCntrl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "globeD3DRMCntrl - Win32 Release" || "$(CFG)" ==\
 "globeD3DRMCntrl - Win32 Debug"
SOURCE=.\ctlhost.cpp
DEP_CPP_CTLHO=\
	".\ctlhost.h"\
	".\dactl.h"\
	

"$(INTDIR)\ctlhost.obj" : $(SOURCE) $(DEP_CPP_CTLHO) "$(INTDIR)"


SOURCE=.\ctlhost.rc
DEP_RSC_CTLHOS=\
	".\dxm.ico"\
	

"$(INTDIR)\ctlhost.res" : $(SOURCE) $(DEP_RSC_CTLHOS) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\dactl.cpp
DEP_CPP_DACTL=\
	".\dactl.h"\
	

"$(INTDIR)\dactl.obj" : $(SOURCE) $(DEP_CPP_DACTL) "$(INTDIR)"


SOURCE=.\globeD3DRM.cpp
DEP_CPP_GLOBE=\
	".\ctlhost.h"\
	".\dactl.h"\
	

"$(INTDIR)\globeD3DRM.obj" : $(SOURCE) $(DEP_CPP_GLOBE) "$(INTDIR)"



!ENDIF 

