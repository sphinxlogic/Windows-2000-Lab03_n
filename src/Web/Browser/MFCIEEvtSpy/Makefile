# Microsoft Developer Studio Generated NMAKE File, Based on MFCIEEvtSpy.dsp
!IF "$(CFG)" == ""
CFG=MFCIEEvtSpy - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MFCIEEvtSpy - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MFCIEEvtSpy - Win32 Release" && "$(CFG)" != "MFCIEEvtSpy - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MFCIEEvtSpy.mak" CFG="MFCIEEvtSpy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MFCIEEvtSpy - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MFCIEEvtSpy - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "MFCIEEvtSpy - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MFCIEEvtSpy.exe"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\MFCIEEvtSpy.obj"
	-@erase "$(INTDIR)\MFCIEEvtSpy.pch"
	-@erase "$(INTDIR)\MFCIEEvtSpy.res"
	-@erase "$(INTDIR)\MFCIEEvtSpyDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\webbrowser2.obj"
	-@erase "$(OUTDIR)\MFCIEEvtSpy.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCIEEvtSpy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCIEEvtSpy.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCIEEvtSpy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MFCIEEvtSpy.pdb" /machine:I386 /out:"$(OUTDIR)\MFCIEEvtSpy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\MFCIEEvtSpy.obj" \
	"$(INTDIR)\MFCIEEvtSpyDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\webbrowser2.obj" \
	"$(INTDIR)\MFCIEEvtSpy.res"

"$(OUTDIR)\MFCIEEvtSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MFCIEEvtSpy - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MFCIEEvtSpy.exe"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\MFCIEEvtSpy.obj"
	-@erase "$(INTDIR)\MFCIEEvtSpy.pch"
	-@erase "$(INTDIR)\MFCIEEvtSpy.res"
	-@erase "$(INTDIR)\MFCIEEvtSpyDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\webbrowser2.obj"
	-@erase "$(OUTDIR)\MFCIEEvtSpy.exe"
	-@erase "$(OUTDIR)\MFCIEEvtSpy.ilk"
	-@erase "$(OUTDIR)\MFCIEEvtSpy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCIEEvtSpy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MFCIEEvtSpy.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MFCIEEvtSpy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MFCIEEvtSpy.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MFCIEEvtSpy.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\MFCIEEvtSpy.obj" \
	"$(INTDIR)\MFCIEEvtSpyDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\webbrowser2.obj" \
	"$(INTDIR)\MFCIEEvtSpy.res"

"$(OUTDIR)\MFCIEEvtSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("MFCIEEvtSpy.dep")
!INCLUDE "MFCIEEvtSpy.dep"
!ELSE 
!MESSAGE Warning: cannot find "MFCIEEvtSpy.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MFCIEEvtSpy - Win32 Release" || "$(CFG)" == "MFCIEEvtSpy - Win32 Debug"
SOURCE=.\IE4Events.cpp

"$(INTDIR)\IE4Events.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCIEEvtSpy.pch"


SOURCE=.\MFCIEEvtSpy.cpp

"$(INTDIR)\MFCIEEvtSpy.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCIEEvtSpy.pch"


SOURCE=.\MFCIEEvtSpy.rc

"$(INTDIR)\MFCIEEvtSpy.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MFCIEEvtSpyDlg.cpp

"$(INTDIR)\MFCIEEvtSpyDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCIEEvtSpy.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MFCIEEvtSpy - Win32 Release"

CPP_SWITCHES=/nologo /MD /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCIEEvtSpy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCIEEvtSpy.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MFCIEEvtSpy - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MFCIEEvtSpy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MFCIEEvtSpy.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\webbrowser2.cpp

"$(INTDIR)\webbrowser2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MFCIEEvtSpy.pch"



!ENDIF 

