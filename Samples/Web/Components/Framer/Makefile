# Microsoft Developer Studio Generated NMAKE File, Based on Framer.dsp
!IF "$(CFG)" == ""
CFG=Framer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Framer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Framer - Win32 Release" && "$(CFG)" != "Framer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Framer.mak" CFG="Framer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Framer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Framer - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Framer - Win32 Release"

OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : ".\framer.exe"


CLEAN :
	-@erase "$(INTDIR)\framer.obj"
	-@erase "$(INTDIR)\framer.res"
	-@erase "$(INTDIR)\iadvsink.obj"
	-@erase "$(INTDIR)\iclisite.obj"
	-@erase "$(INTDIR)\idocsite.obj"
	-@erase "$(INTDIR)\iipsite.obj"
	-@erase "$(INTDIR)\site.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\framer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\Framer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\framer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Framer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\framer.pdb" /machine:I386 /out:"framer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\framer.obj" \
	"$(INTDIR)\iadvsink.obj" \
	"$(INTDIR)\iclisite.obj" \
	"$(INTDIR)\idocsite.obj" \
	"$(INTDIR)\iipsite.obj" \
	"$(INTDIR)\site.obj" \
	"$(INTDIR)\framer.res"

".\framer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Framer - Win32 Debug"

OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : ".\framer.exe"


CLEAN :
	-@erase "$(INTDIR)\framer.obj"
	-@erase "$(INTDIR)\framer.res"
	-@erase "$(INTDIR)\iadvsink.obj"
	-@erase "$(INTDIR)\iclisite.obj"
	-@erase "$(INTDIR)\idocsite.obj"
	-@erase "$(INTDIR)\iipsite.obj"
	-@erase "$(INTDIR)\site.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\framer.pdb"
	-@erase ".\framer.exe"
	-@erase ".\framer.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\Framer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\framer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Framer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\framer.pdb" /debug /machine:I386 /out:"framer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\framer.obj" \
	"$(INTDIR)\iadvsink.obj" \
	"$(INTDIR)\iclisite.obj" \
	"$(INTDIR)\idocsite.obj" \
	"$(INTDIR)\iipsite.obj" \
	"$(INTDIR)\site.obj" \
	"$(INTDIR)\framer.res"

".\framer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Framer.dep")
!INCLUDE "Framer.dep"
!ELSE 
!MESSAGE Warning: cannot find "Framer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Framer - Win32 Release" || "$(CFG)" == "Framer - Win32 Debug"
SOURCE=.\framer.cpp

"$(INTDIR)\framer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\framer.rc

"$(INTDIR)\framer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\iadvsink.cpp

"$(INTDIR)\iadvsink.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\iclisite.cpp

"$(INTDIR)\iclisite.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\idocsite.cpp

"$(INTDIR)\idocsite.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\iipsite.cpp

"$(INTDIR)\iipsite.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\site.cpp

"$(INTDIR)\site.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

