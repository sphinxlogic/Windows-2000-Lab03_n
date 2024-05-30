# Microsoft Developer Studio Generated NMAKE File, Based on UDTServer.dsp
!IF "$(CFG)" == ""
CFG=UDTServer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to UDTServer - Win32 Debug.
!ENDIF 

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF

!IF "$(CFG)" != "UDTServer - Win32 Release" && "$(CFG)" != "UDTServer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UDTServer.mak" CFG="UDTServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UDTServer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "UDTServer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "UDTServer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\UDTServer.exe"


CLEAN :
	-@erase "$(INTDIR)\cfactory.obj"
	-@erase "$(INTDIR)\cunknown.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\SERVER.OBJ"
	-@erase "$(INTDIR)\Student_i.obj"
	-@erase "$(INTDIR)\UDTServer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\UDTServer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "__WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0X400 /D "_APARTMENT_" /D "_STUDENTSTRUCT_" /Fp"$(INTDIR)\UDTServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\UDTServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\UDTServer.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\UDTServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cfactory.obj" \
	"$(INTDIR)\cunknown.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\SERVER.OBJ" \
	"$(INTDIR)\UDTServer.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Student_i.obj"

"$(OUTDIR)\UDTServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "UDTServer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\Student.tlb" "$(OUTDIR)\UDTServer.exe"


CLEAN :
	-@erase "$(INTDIR)\cfactory.obj"
	-@erase "$(INTDIR)\cunknown.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\SERVER.OBJ"
	-@erase "$(INTDIR)\Student_i.obj"
	-@erase "$(INTDIR)\UDTServer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\UDTServer.exe"
	-@erase "$(OUTDIR)\UDTServer.ilk"
	-@erase "$(OUTDIR)\UDTServer.pdb"
	-@erase "Student.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X400 /Fp"$(INTDIR)\UDTServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\UDTServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\UDTServer.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\UDTServer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cfactory.obj" \
	"$(INTDIR)\cunknown.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\SERVER.OBJ" \
	"$(INTDIR)\UDTServer.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Student_i.obj"

"$(OUTDIR)\UDTServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("UDTServer.dep")
!INCLUDE "UDTServer.dep"
!ELSE 
!MESSAGE Warning: cannot find "UDTServer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "UDTServer - Win32 Release" || "$(CFG)" == "UDTServer - Win32 Debug"
SOURCE=.\cfactory.cpp

"$(INTDIR)\cfactory.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cunknown.cpp

"$(INTDIR)\cunknown.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\registry.cpp

"$(INTDIR)\registry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SERVER.CPP

"$(INTDIR)\SERVER.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Student.idl

!IF  "$(CFG)" == "UDTServer - Win32 Release"

!ELSEIF  "$(CFG)" == "UDTServer - Win32 Debug"

InputPath=.\Student.idl

".\Student.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl   /Oicf  /h Student.h  /iid  Student_i.c   /tlb  .\Debug\Student.tlb  Student.idl
<< 
	

!ENDIF 

SOURCE=.\UDTServer.cpp

"$(INTDIR)\UDTServer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\debug.c

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Student_i.c

"$(INTDIR)\Student_i.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

