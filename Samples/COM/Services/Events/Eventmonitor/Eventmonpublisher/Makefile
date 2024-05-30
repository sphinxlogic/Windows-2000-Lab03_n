# Microsoft Developer Studio Generated NMAKE File, Based on EventMonPublisher.dsp
!IF "$(CFG)" == ""
CFG=EventMonPublisher - Win32 Debug
!MESSAGE No configuration specified. Defaulting to EventMonPublisher - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "EventMonPublisher - Win32 Release" && "$(CFG)" != "EventMonPublisher - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EventMonPublisher.mak" CFG="EventMonPublisher - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EventMonPublisher - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "EventMonPublisher - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "EventMonPublisher - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\EventMonPublisher.exe" "$(OUTDIR)\EventMonPublisher.tlb"


CLEAN :
	-@erase "$(INTDIR)\Adminwrap.obj"
	-@erase "$(INTDIR)\EventMonPubdlg.obj"
	-@erase "$(INTDIR)\EventMonPublisher.obj"
	-@erase "$(INTDIR)\EventMonPublisher.pch"
	-@erase "$(INTDIR)\EventMonPublisher.res"
	-@erase "$(INTDIR)\EventMonPublisher.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonPublisher.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventMonPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonPublisher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\EventMonPublisher.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\EventMonPublisher.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Adminwrap.obj" \
	"$(INTDIR)\EventMonPubdlg.obj" \
	"$(INTDIR)\EventMonPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonPublisher.res"

"$(OUTDIR)\EventMonPublisher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "EventMonPublisher - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\Output\EventMonPublisher.exe" ".\EventMonPublisher.tlb"


CLEAN :
	-@erase "$(INTDIR)\Adminwrap.obj"
	-@erase "$(INTDIR)\EventMonPubdlg.obj"
	-@erase "$(INTDIR)\EventMonPublisher.obj"
	-@erase "$(INTDIR)\EventMonPublisher.pch"
	-@erase "$(INTDIR)\EventMonPublisher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventMonPublisher.pdb"
	-@erase "..\Output\EventMonPublisher.exe"
	-@erase "..\Output\EventMonPublisher.ilk"
	-@erase ".\EventMonPublisher.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
    if not exist ..\Output mkdir ..\Output

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventMonPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonPublisher.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\EventMonPublisher.pdb" /debug /machine:$(mach_type) /out:"../Output/EventMonPublisher.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Adminwrap.obj" \
	"$(INTDIR)\EventMonPubdlg.obj" \
	"$(INTDIR)\EventMonPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonPublisher.res"

"..\Output\EventMonPublisher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("EventMonPublisher.dep")
!INCLUDE "EventMonPublisher.dep"
!ELSE 
!MESSAGE Warning: cannot find "EventMonPublisher.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "EventMonPublisher - Win32 Release" || "$(CFG)" == "EventMonPublisher - Win32 Debug"
SOURCE=..\Include\Adminwrap.cpp

"$(INTDIR)\Adminwrap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonPublisher.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EventMonPubdlg.cpp

!IF  "$(CFG)" == "EventMonPublisher - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventMonPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonPubdlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonPublisher.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonPublisher - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventMonPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonPubdlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonPublisher.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonPublisher.cpp

"$(INTDIR)\EventMonPublisher.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonPublisher.pch"


SOURCE=.\EventMonPublisher.idl

!IF  "$(CFG)" == "EventMonPublisher - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\EventMonPublisher.tlb" /mktyplib203 /win32 

"$(INTDIR)\EventMonPublisher.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonPublisher - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "EventMonPublisher.tlb" /mktyplib203 /win32 

".\EventMonPublisher.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "EventMonPublisher - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventMonPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonPublisher - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventMonPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonPublisher.rc

"$(INTDIR)\EventMonPublisher.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

