# Microsoft Developer Studio Generated NMAKE File, Based on SamplCli.dsp
!IF "$(CFG)" == ""
CFG=SampleCli - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SampleCli - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SampleCli - Win32 Release" && "$(CFG)" != "SampleCli - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SamplCli.mak" CFG="SampleCli - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SampleCli - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SampleCli - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "SampleCli - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SamplCli.exe"


CLEAN :
	-@erase "$(INTDIR)\RefClint.obj"
	-@erase "$(INTDIR)\SamplCli.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SamplCli.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SamplCli.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SamplCli.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SamplCli.pdb" /machine:I386 /out:"$(OUTDIR)\SamplCli.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SamplCli.obj" \
	"$(INTDIR)\RefClint.obj"

"$(OUTDIR)\SamplCli.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SampleCli - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SamplCli.exe"


CLEAN :
	-@erase "$(INTDIR)\RefClint.obj"
	-@erase "$(INTDIR)\SamplCli.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SamplCli.exe"
	-@erase "$(OUTDIR)\SamplCli.ilk"
	-@erase "$(OUTDIR)\SamplCli.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SamplCli.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SamplCli.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wbemuuid.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\SamplCli.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SamplCli.exe" /pdbtype:sept /libpath:"..\..\..\idl\objindd" 
LINK32_OBJS= \
	"$(INTDIR)\SamplCli.obj" \
	"$(INTDIR)\RefClint.obj"

"$(OUTDIR)\SamplCli.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SamplCli.dep")
!INCLUDE "SamplCli.dep"
!ELSE 
!MESSAGE Warning: cannot find "SamplCli.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SampleCli - Win32 Release" || "$(CFG)" == "SampleCli - Win32 Debug"
SOURCE=.\RefClint.cpp

"$(INTDIR)\RefClint.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SamplCli.cpp

"$(INTDIR)\SamplCli.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

