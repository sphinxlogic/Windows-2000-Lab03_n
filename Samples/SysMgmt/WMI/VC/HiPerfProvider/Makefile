# Microsoft Developer Studio Generated NMAKE File, Based on BasicHiPerf.dsp
!IF "$(CFG)" == ""
CFG=BasicHiPerf - Win32 Debug
!MESSAGE No configuration specified. Defaulting to BasicHiPerf - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "BasicHiPerf - Win32 Release" && "$(CFG)" != "BasicHiPerf - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BasicHiPerf.mak" CFG="BasicHiPerf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BasicHiPerf - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BasicHiPerf - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "BasicHiPerf - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\BasicHiPerf.dll"


CLEAN :
	-@erase "$(INTDIR)\BasicHiPerf.obj"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\server.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\BasicHiPerf.dll"
	-@erase "$(OUTDIR)\BasicHiPerf.exp"
	-@erase "$(OUTDIR)\BasicHiPerf.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\BasicHiPerf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BasicHiPerf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\BasicHiPerf.pdb" /machine:I386 /def:".\BasicHiPerf.def" /out:"$(OUTDIR)\BasicHiPerf.dll" /implib:"$(OUTDIR)\BasicHiPerf.lib" 
DEF_FILE= \
	".\BasicHiPerf.def"
LINK32_OBJS= \
	"$(INTDIR)\BasicHiPerf.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\server.obj"

"$(OUTDIR)\BasicHiPerf.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\BasicHiPerf.dll"
   regsvr32 Release\BasicHiPerf.dll
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "BasicHiPerf - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\BasicHiPerf.dll" "$(OUTDIR)\BasicHiPerf.bsc"


CLEAN :
	-@erase "$(INTDIR)\BasicHiPerf.obj"
	-@erase "$(INTDIR)\BasicHiPerf.sbr"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\Factory.sbr"
	-@erase "$(INTDIR)\server.obj"
	-@erase "$(INTDIR)\server.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\BasicHiPerf.bsc"
	-@erase "$(OUTDIR)\BasicHiPerf.dll"
	-@erase "$(OUTDIR)\BasicHiPerf.exp"
	-@erase "$(OUTDIR)\BasicHiPerf.ilk"
	-@erase "$(OUTDIR)\BasicHiPerf.lib"
	-@erase "$(OUTDIR)\BasicHiPerf.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\idl" /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\BasicHiPerf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BasicHiPerf.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BasicHiPerf.sbr" \
	"$(INTDIR)\Factory.sbr" \
	"$(INTDIR)\server.sbr"

"$(OUTDIR)\BasicHiPerf.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wbemuuid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\BasicHiPerf.pdb" /debug /machine:I386 /def:".\BasicHiPerf.def" /out:"$(OUTDIR)\BasicHiPerf.dll" /implib:"$(OUTDIR)\BasicHiPerf.lib" /pdbtype:sept /libpath:"..\..\..\lib" /libpath:"..\..\idl\objindd" 
DEF_FILE= \
	".\BasicHiPerf.def"
LINK32_OBJS= \
	"$(INTDIR)\BasicHiPerf.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\server.obj"

"$(OUTDIR)\BasicHiPerf.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("BasicHiPerf.dep")
!INCLUDE "BasicHiPerf.dep"
!ELSE 
!MESSAGE Warning: cannot find "BasicHiPerf.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "BasicHiPerf - Win32 Release" || "$(CFG)" == "BasicHiPerf - Win32 Debug"
SOURCE=.\BasicHiPerf.cpp

!IF  "$(CFG)" == "BasicHiPerf - Win32 Release"


"$(INTDIR)\BasicHiPerf.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "BasicHiPerf - Win32 Debug"


"$(INTDIR)\BasicHiPerf.obj"	"$(INTDIR)\BasicHiPerf.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Factory.cpp

!IF  "$(CFG)" == "BasicHiPerf - Win32 Release"


"$(INTDIR)\Factory.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "BasicHiPerf - Win32 Debug"


"$(INTDIR)\Factory.obj"	"$(INTDIR)\Factory.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\server.cpp

!IF  "$(CFG)" == "BasicHiPerf - Win32 Release"


"$(INTDIR)\server.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "BasicHiPerf - Win32 Debug"


"$(INTDIR)\server.obj"	"$(INTDIR)\server.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

