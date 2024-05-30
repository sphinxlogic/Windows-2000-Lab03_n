# Microsoft Developer Studio Generated NMAKE File, Based on ReBar.dsp
!IF "$(CFG)" == ""
CFG=ReBar - Win32 Release
!MESSAGE No configuration specified. Defaulting to ReBar - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ReBar - Win32 Release" && "$(CFG)" != "ReBar - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ReBar.mak" CFG="ReBar - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ReBar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ReBar - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "ReBar - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ReBar.exe"


CLEAN :
	-@erase "$(INTDIR)\ReBar.obj"
	-@erase "$(INTDIR)\ReBar.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ReBar.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_IE=0x0400 /Fp"$(INTDIR)\ReBar.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ReBar.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ReBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ReBar.pdb" /machine:I386 /out:"$(OUTDIR)\ReBar.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ReBar.obj" \
	"$(INTDIR)\ReBar.res"

"$(OUTDIR)\ReBar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ReBar - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ReBar.exe" "$(OUTDIR)\ReBar.bsc"


CLEAN :
	-@erase "$(INTDIR)\ReBar.obj"
	-@erase "$(INTDIR)\ReBar.res"
	-@erase "$(INTDIR)\ReBar.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ReBar.bsc"
	-@erase "$(OUTDIR)\ReBar.exe"
	-@erase "$(OUTDIR)\ReBar.ilk"
	-@erase "$(OUTDIR)\ReBar.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_IE=0x0400 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ReBar.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ReBar.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ReBar.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ReBar.sbr"

"$(OUTDIR)\ReBar.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ReBar.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ReBar.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ReBar.obj" \
	"$(INTDIR)\ReBar.res"

"$(OUTDIR)\ReBar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ReBar.dep")
!INCLUDE "ReBar.dep"
!ELSE 
!MESSAGE Warning: cannot find "ReBar.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ReBar - Win32 Release" || "$(CFG)" == "ReBar - Win32 Debug"
SOURCE=.\ReBar.c

!IF  "$(CFG)" == "ReBar - Win32 Release"


"$(INTDIR)\ReBar.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ReBar - Win32 Debug"


"$(INTDIR)\ReBar.obj"	"$(INTDIR)\ReBar.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ReBar.rc

"$(INTDIR)\ReBar.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

