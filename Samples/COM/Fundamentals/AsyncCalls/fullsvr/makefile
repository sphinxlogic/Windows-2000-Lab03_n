# Microsoft Developer Studio Generated NMAKE File, Based on FullSvr.dsp
!IF "$(CFG)" == ""
CFG=FullSvr - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FullSvr - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "FullSvr - Win32 Debug" && "$(CFG)" != "FullSvr - Win32 Unicode Debug" && "$(CFG)" != "FullSvr - Win32 Release MinSize" && "$(CFG)" != "FullSvr - Win32 Release MinDependency" && "$(CFG)" != "FullSvr - Win32 Unicode Release MinSize" && "$(CFG)" != "FullSvr - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FullSvr.mak" CFG="FullSvr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FullSvr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "FullSvr - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "FullSvr - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "FullSvr - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "FullSvr - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "FullSvr - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FullSvr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\FullSvr.exe" "$(OUTDIR)\FullSvr.pch" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase "$(OUTDIR)\FullSvr.ilk"
	-@erase "$(OUTDIR)\FullSvr.pdb"
	-@erase ".\FullSvr.h"
	-@erase ".\FullSvr.tlb"
	-@erase ".\FullSvr_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\FullSvr.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\FullSvr.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\FullSvr.exe
InputPath=.\Debug\FullSvr.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	.\Debug\FullSvr /RegServer
	echo Making proxy/stub
	nmake -f FullSvrps.mk
	regsvr32 /s FullSvrps.dll
	echo proxy/stub registered
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\FullSvr.exe" ".\FullSvr.tlb" ".\FullSvr.h" ".\FullSvr_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase "$(OUTDIR)\FullSvr.ilk"
	-@erase "$(OUTDIR)\FullSvr.pdb"
	-@erase ".\FullSvr.h"
	-@erase ".\FullSvr.tlb"
	-@erase ".\FullSvr_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\FullSvr.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\FullSvr.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\FullSvr.exe
InputPath=.\DebugU\FullSvr.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\FullSvr.exe" ".\FullSvr.tlb" ".\FullSvr.h" ".\FullSvr_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase ".\FullSvr.h"
	-@erase ".\FullSvr.tlb"
	-@erase ".\FullSvr_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\FullSvr.exe
InputPath=.\ReleaseMinSize\FullSvr.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\FullSvr.exe" ".\FullSvr.tlb" ".\FullSvr.h" ".\FullSvr_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase ".\FullSvr.h"
	-@erase ".\FullSvr.tlb"
	-@erase ".\FullSvr_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\FullSvr.exe
InputPath=.\ReleaseMinDependency\FullSvr.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\FullSvr.exe" ".\FullSvr.tlb" ".\FullSvr.h" ".\FullSvr_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase ".\FullSvr.h"
	-@erase ".\FullSvr.tlb"
	-@erase ".\FullSvr_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\FullSvr.exe
InputPath=.\ReleaseUMinSize\FullSvr.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\FullSvr.exe" ".\FullSvr.tlb" ".\FullSvr.h" ".\FullSvr_i.c" "$(OUTDIR)\FullSvr.bsc" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullServ.sbr"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\FullSvr.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.bsc"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase ".\FullSvr.h"
	-@erase ".\FullSvr.tlb"
	-@erase ".\FullSvr_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\FullServ.sbr" \
	"$(INTDIR)\FullSvr.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\FullSvr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\FullSvr.exe
InputPath=.\ReleaseUMinDependency\FullSvr.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FullSvr.dep")
!INCLUDE "FullSvr.dep"
!ELSE 
!MESSAGE Warning: cannot find "FullSvr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FullSvr - Win32 Debug" || "$(CFG)" == "FullSvr - Win32 Unicode Debug" || "$(CFG)" == "FullSvr - Win32 Release MinSize" || "$(CFG)" == "FullSvr - Win32 Release MinDependency" || "$(CFG)" == "FullSvr - Win32 Unicode Release MinSize" || "$(CFG)" == "FullSvr - Win32 Unicode Release MinDependency"
SOURCE=.\FullServ.cpp

!IF  "$(CFG)" == "FullSvr - Win32 Debug"


"$(INTDIR)\FullServ.obj" : $(SOURCE) "$(INTDIR)" ".\FullSvr.h"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Debug"


"$(INTDIR)\FullServ.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinSize"


"$(INTDIR)\FullServ.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinDependency"


"$(INTDIR)\FullServ.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinSize"


"$(INTDIR)\FullServ.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinDependency"


"$(INTDIR)\FullServ.obj"	"$(INTDIR)\FullServ.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ENDIF 

SOURCE=.\FullSvr.cpp

!IF  "$(CFG)" == "FullSvr - Win32 Debug"


"$(INTDIR)\FullSvr.obj" : $(SOURCE) "$(INTDIR)" ".\FullSvr.h" ".\FullSvr_i.c"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Debug"


"$(INTDIR)\FullSvr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinSize"


"$(INTDIR)\FullSvr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinDependency"


"$(INTDIR)\FullSvr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinSize"


"$(INTDIR)\FullSvr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinDependency"


"$(INTDIR)\FullSvr.obj"	"$(INTDIR)\FullSvr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


!ENDIF 

SOURCE=.\FullSvr.idl

!IF  "$(CFG)" == "FullSvr - Win32 Debug"

MTL_SWITCHES=/tlb ".\FullSvr.tlb" /h "FullSvr.h" /iid "FullSvr_i.c" /Oicf 

".\FullSvr.tlb"	".\FullSvr.h"	".\FullSvr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\FullSvr.tlb" /h "FullSvr.h" /iid "FullSvr_i.c" /Oicf 

".\FullSvr.tlb"	".\FullSvr.h"	".\FullSvr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\FullSvr.tlb" /h "FullSvr.h" /iid "FullSvr_i.c" /Oicf 

".\FullSvr.tlb"	".\FullSvr.h"	".\FullSvr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\FullSvr.tlb" /h "FullSvr.h" /iid "FullSvr_i.c" /Oicf 

".\FullSvr.tlb"	".\FullSvr.h"	".\FullSvr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\FullSvr.tlb" /h "FullSvr.h" /iid "FullSvr_i.c" /Oicf 

".\FullSvr.tlb"	".\FullSvr.h"	".\FullSvr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\FullSvr.tlb" /h "FullSvr.h" /iid "FullSvr_i.c" /Oicf 

".\FullSvr.tlb"	".\FullSvr.h"	".\FullSvr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\FullSvr.rc

"$(INTDIR)\FullSvr.res" : $(SOURCE) "$(INTDIR)" ".\FullSvr.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FullSvr - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

