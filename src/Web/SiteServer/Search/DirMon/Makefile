# Microsoft Developer Studio Generated NMAKE File, Based on Dirmon.dsp
!IF "$(CFG)" == ""
CFG=Dirmon - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Dirmon - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dirmon - Win32 Release" && "$(CFG)" != "Dirmon - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dirmon.mak" CFG="Dirmon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dirmon - Win32 Release" (based on "Win32 Console Application")
!MESSAGE "Dirmon - Win32 Debug" (based on "Win32 Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dirmon - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "1" "$(OUTDIR)\Dirmon.exe"

!ELSE 

ALL : "1" "$(OUTDIR)\Dirmon.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dirmon.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Dirmon.exe"
	-@erase "1"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)\Dirmon.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Dirmon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\Dirmon.pdb" /out:"$(OUTDIR)\Dirmon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dirmon.obj" \
	"$(INTDIR)\main.obj"

"$(OUTDIR)\Dirmon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dirmon - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "1" "$(OUTDIR)\Dirmon.exe"

!ELSE 

ALL : "1" "$(OUTDIR)\Dirmon.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dirmon.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Dirmon.exe"
	-@erase "$(OUTDIR)\Dirmon.ilk"
	-@erase "$(OUTDIR)\Dirmon.pdb"
	-@erase "1"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_MBCS" /Fp"$(INTDIR)\Dirmon.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Dirmon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\Dirmon.pdb" /debug /out:"$(OUTDIR)\Dirmon.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dirmon.obj" \
	"$(INTDIR)\main.obj"

"$(OUTDIR)\Dirmon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "Dirmon - Win32 Release" || "$(CFG)" == "Dirmon - Win32 Debug"
SOURCE=.\dirmon.cpp
DEP_CPP_DIRMO=\
	".\gthrntfysdk.h"\
	

"$(INTDIR)\dirmon.obj" : $(SOURCE) $(DEP_CPP_DIRMO) "$(INTDIR)"


SOURCE=.\gthrntfysdk.idl

!IF  "$(CFG)" == "Dirmon - Win32 Release"

InputPath=.\gthrntfysdk.idl

"1"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl  gthrntfysdk.idl  /out  .\ 

!ELSEIF  "$(CFG)" == "Dirmon - Win32 Debug"

InputPath=.\gthrntfysdk.idl

"1"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl  gthrntfysdk.idl  /out  .\ 

!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "Dirmon - Win32 Release"

DEP_CPP_MAIN_=\
	".\gthrntfysdk.h"\
	".\gthrntfysdk_i.c"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dirmon - Win32 Debug"

DEP_CPP_MAIN_=\
	".\gthrntfysdk.h"\
	".\gthrntfysdk_i.c"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ENDIF 


!ENDIF 

