# Microsoft Developer Studio Generated NMAKE File, Based on dmoping.dsp
!IF "$(CFG)" == ""
CFG=dmoping - Win32 Debug
!MESSAGE No configuration specified. Defaulting to dmoping - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "dmoping - Win32 Release" && "$(CFG)" !=\
 "dmoping - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dmoping.mak" CFG="dmoping - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dmoping - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "dmoping - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "dmoping - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dmoping.exe"

!ELSE 

ALL : "$(OUTDIR)\dmoping.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dmoping.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\dmoping.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)\dmoping.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dmoping.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\dmoping.pdb" /machine:I386 /out:"$(OUTDIR)\dmoping.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dmoping.obj"

"$(OUTDIR)\dmoping.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dmoping - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dmoping.exe" "$(OUTDIR)\dmoping.bsc"

!ELSE 

ALL : "$(OUTDIR)\dmoping.exe" "$(OUTDIR)\dmoping.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dmoping.obj"
	-@erase "$(INTDIR)\dmoping.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\dmoping.bsc"
	-@erase "$(OUTDIR)\dmoping.exe"
	-@erase "$(OUTDIR)\dmoping.ilk"
	-@erase "$(OUTDIR)\dmoping.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D\
 "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\dmoping.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dmoping.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dmoping.sbr"

"$(OUTDIR)\dmoping.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\dmoping.pdb" /debug /machine:I386 /out:"$(OUTDIR)\dmoping.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dmoping.obj"

"$(OUTDIR)\dmoping.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "dmoping - Win32 Release" || "$(CFG)" ==\
 "dmoping - Win32 Debug"
SOURCE=.\dmoping.cpp
DEP_CPP_DMOPI=\
	".\dmoping.h"\
	

!IF  "$(CFG)" == "dmoping - Win32 Release"


"$(INTDIR)\dmoping.obj" : $(SOURCE) $(DEP_CPP_DMOPI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dmoping - Win32 Debug"


"$(INTDIR)\dmoping.obj"	"$(INTDIR)\dmoping.sbr" : $(SOURCE) $(DEP_CPP_DMOPI)\
 "$(INTDIR)"


!ENDIF 


!ENDIF 

