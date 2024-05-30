# Microsoft Developer Studio Generated NMAKE File, Based on AsyncServer.dsp
!IF "$(CFG)" == ""
CFG=AsyncServer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to AsyncServer - Win32 Debug.
!ENDIF 

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF

!IF "$(CFG)" != "AsyncServer - Win32 Release" && "$(CFG)" != "AsyncServer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsyncServer.mak" CFG="AsyncServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsyncServer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AsyncServer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "AsyncServer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\AsyncServer.exe"


CLEAN :
	-@erase "$(INTDIR)\AsyncTest1_i.obj"
	-@erase "$(INTDIR)\CAsyncTest.obj"
	-@erase "$(INTDIR)\CConnectionPT.obj"
	-@erase "$(INTDIR)\cfactory.obj"
	-@erase "$(INTDIR)\cunknown.obj"
	-@erase "$(INTDIR)\DCOMServer.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\SERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AsyncServer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "_AGGREGATE_" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_APARTMENT_" /D "_ASYNC_COM_" /D "_EVENTSINK_" /D "_SECURE_" /Fp"$(INTDIR)\AsyncServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AsyncServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\AsyncServer.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\AsyncServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CAsyncTest.obj" \
	"$(INTDIR)\CConnectionPT.obj" \
	"$(INTDIR)\cfactory.obj" \
	"$(INTDIR)\cunknown.obj" \
	"$(INTDIR)\DCOMServer.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\SERVER.OBJ" \
	"$(INTDIR)\AsyncTest1_i.obj" \
	"$(INTDIR)\debug.obj"

"$(OUTDIR)\AsyncServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AsyncServer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\AsyncServer.exe"


CLEAN :
	-@erase "$(INTDIR)\AsyncTest1_i.obj"
	-@erase "$(INTDIR)\CAsyncTest.obj"
	-@erase "$(INTDIR)\CConnectionPT.obj"
	-@erase "$(INTDIR)\cfactory.obj"
	-@erase "$(INTDIR)\cunknown.obj"
	-@erase "$(INTDIR)\DCOMServer.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\SERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AsyncServer.exe"
	-@erase "$(OUTDIR)\AsyncServer.ilk"
	-@erase "$(OUTDIR)\AsyncServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_APARTMENT_" /D "_ASYNC_COM_" /D "_EVENTSINK_" /Fp"$(INTDIR)\AsyncServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AsyncServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\AsyncServer.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\AsyncServer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CAsyncTest.obj" \
	"$(INTDIR)\CConnectionPT.obj" \
	"$(INTDIR)\cfactory.obj" \
	"$(INTDIR)\cunknown.obj" \
	"$(INTDIR)\DCOMServer.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\SERVER.OBJ" \
	"$(INTDIR)\AsyncTest1_i.obj" \
	"$(INTDIR)\debug.obj"

"$(OUTDIR)\AsyncServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("AsyncServer.dep")
!INCLUDE "AsyncServer.dep"
!ELSE 
!MESSAGE Warning: cannot find "AsyncServer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AsyncServer - Win32 Release" || "$(CFG)" == "AsyncServer - Win32 Debug"
SOURCE=.\CAsyncTest.cpp

"$(INTDIR)\CAsyncTest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CConnectionPT.cpp

"$(INTDIR)\CConnectionPT.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cfactory.cpp

"$(INTDIR)\cfactory.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cunknown.cpp

"$(INTDIR)\cunknown.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DCOMServer.cpp

"$(INTDIR)\DCOMServer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\registry.cpp

"$(INTDIR)\registry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SERVER.CPP

"$(INTDIR)\SERVER.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=..\proxy\AsyncTest1_i.c

"$(INTDIR)\AsyncTest1_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\debug.c

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

