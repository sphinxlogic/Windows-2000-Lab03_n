# Microsoft Developer Studio Generated NMAKE File, Based on VListVw.dsp
!IF "$(CFG)" == ""
CFG=VListVw - Win32 Release
!MESSAGE No configuration specified. Defaulting to VListVw - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "VListVw - Win32 Release" && "$(CFG)" != "VListVw - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VListVw.mak" CFG="VListVw - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VListVw - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VListVw - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "VListVw - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VListVw.exe"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VListVw.obj"
	-@erase "$(INTDIR)\VListVw.res"
	-@erase "$(OUTDIR)\VListVw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\VListVw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VListVw.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VListVw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\VListVw.pdb" /machine:I386 /out:"$(OUTDIR)\VListVw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\VListVw.obj" \
	"$(INTDIR)\VListVw.res"

"$(OUTDIR)\VListVw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VListVw - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VListVw.exe" "$(OUTDIR)\VListVw.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VListVw.obj"
	-@erase "$(INTDIR)\VListVw.res"
	-@erase "$(INTDIR)\VListVw.sbr"
	-@erase "$(OUTDIR)\VListVw.bsc"
	-@erase "$(OUTDIR)\VListVw.exe"
	-@erase "$(OUTDIR)\VListVw.ilk"
	-@erase "$(OUTDIR)\VListVw.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VListVw.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VListVw.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VListVw.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\VListVw.sbr"

"$(OUTDIR)\VListVw.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\VListVw.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VListVw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\VListVw.obj" \
	"$(INTDIR)\VListVw.res"

"$(OUTDIR)\VListVw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("VListVw.dep")
!INCLUDE "VListVw.dep"
!ELSE 
!MESSAGE Warning: cannot find "VListVw.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VListVw - Win32 Release" || "$(CFG)" == "VListVw - Win32 Debug"
SOURCE=.\VListVw.c

!IF  "$(CFG)" == "VListVw - Win32 Release"


"$(INTDIR)\VListVw.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "VListVw - Win32 Debug"


"$(INTDIR)\VListVw.obj"	"$(INTDIR)\VListVw.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\VListVw.rc

"$(INTDIR)\VListVw.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

