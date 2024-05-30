# Microsoft Developer Studio Generated NMAKE File, Based on progress.dsp
!IF "$(CFG)" == ""
CFG=Progress - Win32 Release
!MESSAGE No configuration specified. Defaulting to Progress - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Progress - Win32 Release" && "$(CFG)" != "Progress - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "progress.mak" CFG="Progress - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Progress - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Progress - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Progress - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\progress.exe"


CLEAN :
	-@erase "$(INTDIR)\Progress.obj"
	-@erase "$(INTDIR)\Progress.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\progress.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\progress.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Progress.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\progress.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib urlmon.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\progress.pdb" /machine:I386 /out:"$(OUTDIR)\progress.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Progress.obj" \
	"$(INTDIR)\Progress.res"

"$(OUTDIR)\progress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Progress - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\progress.exe" "$(OUTDIR)\progress.bsc"


CLEAN :
	-@erase "$(INTDIR)\Progress.obj"
	-@erase "$(INTDIR)\Progress.res"
	-@erase "$(INTDIR)\Progress.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\progress.bsc"
	-@erase "$(OUTDIR)\progress.exe"
	-@erase "$(OUTDIR)\progress.ilk"
	-@erase "$(OUTDIR)\progress.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\progress.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Progress.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\progress.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Progress.sbr"

"$(OUTDIR)\progress.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib urlmon.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\progress.pdb" /debug /machine:I386 /out:"$(OUTDIR)\progress.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Progress.obj" \
	"$(INTDIR)\Progress.res"

"$(OUTDIR)\progress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("progress.dep")
!INCLUDE "progress.dep"
!ELSE 
!MESSAGE Warning: cannot find "progress.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Progress - Win32 Release" || "$(CFG)" == "Progress - Win32 Debug"
SOURCE=.\Progress.Cpp

!IF  "$(CFG)" == "Progress - Win32 Release"


"$(INTDIR)\Progress.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Progress - Win32 Debug"


"$(INTDIR)\Progress.obj"	"$(INTDIR)\Progress.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Progress.rc

"$(INTDIR)\Progress.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

