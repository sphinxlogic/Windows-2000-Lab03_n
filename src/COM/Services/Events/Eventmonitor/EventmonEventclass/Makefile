# Microsoft Developer Studio Generated NMAKE File, Based on EventMonEventClass.dsp
!IF "$(CFG)" == ""
CFG=EventMonEventClass - Win32 Debug
!MESSAGE No configuration specified. Defaulting to EventMonEventClass - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "EventMonEventClass - Win32 Unicode Debug" && "$(CFG)" != "EventMonEventClass - Win32 Release MinSize" && "$(CFG)" != "EventMonEventClass - Win32 Release MinDependency" && "$(CFG)" != "EventMonEventClass - Win32 Unicode Release MinSize" && "$(CFG)" != "EventMonEventClass - Win32 Unicode Release MinDependency" && "$(CFG)" != "EventMonEventClass - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EventMonEventClass.mak" CFG="EventMonEventClass - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EventMonEventClass - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonEventClass - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonEventClass - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonEventClass - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonEventClass - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonEventClass - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\EventMon_i.c" ".\EventMon.h" "$(OUTDIR)\EventMonEventClass.dll" ".\EventMonEventClass.tlb" ".\EventMonEventClass.h" ".\EventMonEventClass_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonEventClass.obj"
	-@erase "$(INTDIR)\EventMonEventClass.pch"
	-@erase "$(INTDIR)\EventMonEventClass.res"
	-@erase "$(INTDIR)\EventMonImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventMonEventClass.dll"
	-@erase "$(OUTDIR)\EventMonEventClass.exp"
	-@erase "$(OUTDIR)\EventMonEventClass.ilk"
	-@erase "$(OUTDIR)\EventMonEventClass.lib"
	-@erase "$(OUTDIR)\EventMonEventClass.pdb"
	-@erase ".\EventMonEventClass.h"
	-@erase ".\EventMonEventClass.tlb"
	-@erase ".\EventMonEventClass_i.c"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\EventMon.h"
	-@erase ".\EventMon_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonEventClass.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\EventMonEventClass.pdb" /debug /machine:$(mach_type) /def:".\EventMonEventClass.def" /out:"$(OUTDIR)\EventMonEventClass.dll" /implib:"$(OUTDIR)\EventMonEventClass.lib" /pdbtype:sept 
DEF_FILE= \
	".\EventMonEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonEventClass.obj" \
	"$(INTDIR)\EventMonImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonEventClass.res"

"$(OUTDIR)\EventMonEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\EventMonEventClass.dll
InputPath=.\DebugU\EventMonEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\EventMon_i.c" ".\EventMon.h" "$(OUTDIR)\EventMonEventClass.dll" ".\EventMonEventClass.tlb" ".\EventMonEventClass.h" ".\EventMonEventClass_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonEventClass.obj"
	-@erase "$(INTDIR)\EventMonEventClass.pch"
	-@erase "$(INTDIR)\EventMonEventClass.res"
	-@erase "$(INTDIR)\EventMonImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonEventClass.dll"
	-@erase "$(OUTDIR)\EventMonEventClass.exp"
	-@erase "$(OUTDIR)\EventMonEventClass.lib"
	-@erase ".\EventMonEventClass.h"
	-@erase ".\EventMonEventClass.tlb"
	-@erase ".\EventMonEventClass_i.c"
	-@erase ".\EventMon.h"
	-@erase ".\EventMon_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonEventClass.pdb" /machine:$(mach_type) /def:".\EventMonEventClass.def" /out:"$(OUTDIR)\EventMonEventClass.dll" /implib:"$(OUTDIR)\EventMonEventClass.lib" 
DEF_FILE= \
	".\EventMonEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonEventClass.obj" \
	"$(INTDIR)\EventMonImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonEventClass.res"

"$(OUTDIR)\EventMonEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\EventMonEventClass.dll
InputPath=.\ReleaseMinSize\EventMonEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\EventMon_i.c" ".\EventMon.h" "$(OUTDIR)\EventMonEventClass.dll" ".\EventMonEventClass.tlb" ".\EventMonEventClass.h" ".\EventMonEventClass_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonEventClass.obj"
	-@erase "$(INTDIR)\EventMonEventClass.pch"
	-@erase "$(INTDIR)\EventMonEventClass.res"
	-@erase "$(INTDIR)\EventMonImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonEventClass.dll"
	-@erase "$(OUTDIR)\EventMonEventClass.exp"
	-@erase "$(OUTDIR)\EventMonEventClass.lib"
	-@erase ".\EventMonEventClass.h"
	-@erase ".\EventMonEventClass.tlb"
	-@erase ".\EventMonEventClass_i.c"
	-@erase ".\EventMon.h"
	-@erase ".\EventMon_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonEventClass.pdb" /machine:$(mach_type) /def:".\EventMonEventClass.def" /out:"$(OUTDIR)\EventMonEventClass.dll" /implib:"$(OUTDIR)\EventMonEventClass.lib" 
DEF_FILE= \
	".\EventMonEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonEventClass.obj" \
	"$(INTDIR)\EventMonImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonEventClass.res"

"$(OUTDIR)\EventMonEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\EventMonEventClass.dll
InputPath=.\ReleaseMinDependency\EventMonEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\EventMon_i.c" ".\EventMon.h" "$(OUTDIR)\EventMonEventClass.dll" ".\EventMonEventClass.tlb" ".\EventMonEventClass.h" ".\EventMonEventClass_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonEventClass.obj"
	-@erase "$(INTDIR)\EventMonEventClass.pch"
	-@erase "$(INTDIR)\EventMonEventClass.res"
	-@erase "$(INTDIR)\EventMonImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonEventClass.dll"
	-@erase "$(OUTDIR)\EventMonEventClass.exp"
	-@erase "$(OUTDIR)\EventMonEventClass.lib"
	-@erase ".\EventMonEventClass.h"
	-@erase ".\EventMonEventClass.tlb"
	-@erase ".\EventMonEventClass_i.c"
	-@erase ".\EventMon.h"
	-@erase ".\EventMon_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonEventClass.pdb" /machine:$(mach_type) /def:".\EventMonEventClass.def" /out:"$(OUTDIR)\EventMonEventClass.dll" /implib:"$(OUTDIR)\EventMonEventClass.lib" 
DEF_FILE= \
	".\EventMonEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonEventClass.obj" \
	"$(INTDIR)\EventMonImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonEventClass.res"

"$(OUTDIR)\EventMonEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\EventMonEventClass.dll
InputPath=.\ReleaseUMinSize\EventMonEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\EventMon_i.c" ".\EventMon.h" "$(OUTDIR)\EventMonEventClass.dll" ".\EventMonEventClass.tlb" ".\EventMonEventClass.h" ".\EventMonEventClass_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonEventClass.obj"
	-@erase "$(INTDIR)\EventMonEventClass.pch"
	-@erase "$(INTDIR)\EventMonEventClass.res"
	-@erase "$(INTDIR)\EventMonImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonEventClass.dll"
	-@erase "$(OUTDIR)\EventMonEventClass.exp"
	-@erase "$(OUTDIR)\EventMonEventClass.lib"
	-@erase ".\EventMonEventClass.h"
	-@erase ".\EventMonEventClass.tlb"
	-@erase ".\EventMonEventClass_i.c"
	-@erase ".\EventMon.h"
	-@erase ".\EventMon_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonEventClass.pdb" /machine:$(mach_type) /def:".\EventMonEventClass.def" /out:"$(OUTDIR)\EventMonEventClass.dll" /implib:"$(OUTDIR)\EventMonEventClass.lib" 
DEF_FILE= \
	".\EventMonEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonEventClass.obj" \
	"$(INTDIR)\EventMonImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonEventClass.res"

"$(OUTDIR)\EventMonEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\EventMonEventClass.dll
InputPath=.\ReleaseUMinDependency\EventMonEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\include\EventMon_i.c" "..\Output\EventMonEventClass.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonEventClass.obj"
	-@erase "$(INTDIR)\EventMonEventClass.pch"
	-@erase "$(INTDIR)\EventMonEventClass.res"
	-@erase "$(INTDIR)\EventMonImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventMonEventClass.exp"
	-@erase "$(OUTDIR)\EventMonEventClass.lib"
	-@erase "$(OUTDIR)\EventMonEventClass.pdb"
	-@erase "..\include\EventMon.h"
	-@erase "..\include\EventMon_i.c"
	-@erase "..\Output\EventMonEventClass.dll"
	-@erase "..\Output\EventMonEventClass.ilk"
	-@erase ".\EventMonEventClass.h"
	-@erase ".\EventMonEventClass.tlb"
	-@erase ".\EventMonEventClass_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
    if not exist ..\Output mkdir ..\Output

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonEventClass.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\EventMonEventClass.pdb" /debug /machine:$(mach_type) /def:".\EventMonEventClass.def" /out:"../Output/EventMonEventClass.dll" /implib:"$(OUTDIR)\EventMonEventClass.lib" /pdbtype:sept 
DEF_FILE= \
	".\EventMonEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonEventClass.obj" \
	"$(INTDIR)\EventMonImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonEventClass.res"

"..\Output\EventMonEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=\mssdk\Samples\COM\Services\Events\EventMonitor\Output\EventMonEventClass.dll
InputPath=\mssdk\Samples\COM\Services\Events\EventMonitor\Output\EventMonEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("EventMonEventClass.dep")
!INCLUDE "EventMonEventClass.dep"
!ELSE 
!MESSAGE Warning: cannot find "EventMonEventClass.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "EventMonEventClass - Win32 Unicode Debug" || "$(CFG)" == "EventMonEventClass - Win32 Release MinSize" || "$(CFG)" == "EventMonEventClass - Win32 Release MinDependency" || "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinSize" || "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinDependency" || "$(CFG)" == "EventMonEventClass - Win32 Debug"
SOURCE=..\Include\EventMon.idl

!IF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Debug"

InputPath=..\Include\EventMon.idl

".\EventMon.h"	".\EventMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c"  "..\include\EventMon.idl"
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinSize"

InputPath=..\Include\EventMon.idl

".\EventMon.h"	".\EventMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c"  "..\include\EventMon.idl"
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinDependency"

InputPath=..\Include\EventMon.idl

".\EventMon.h"	".\EventMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c"  "..\include\EventMon.idl"
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinSize"

InputPath=..\Include\EventMon.idl

".\EventMon.h"	".\EventMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c"  "..\include\EventMon.idl"
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinDependency"

InputPath=..\Include\EventMon.idl

".\EventMon.h"	".\EventMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c"  "..\include\EventMon.idl"
<< 
	

!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Debug"

MTL_SWITCHES=/I "..\include" /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c" 

"..\include\EventMon.h"	"..\include\EventMon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonEventClass.cpp

!IF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch" "..\include\EventMon.h" ".\EventMonEventClass_i.c" ".\EventMonEventClass.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonEventClass.idl

!IF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\EventMonEventClass.tlb" /h "EventMonEventClass.h" /iid "EventMonEventClass_i.c" /Oicf 

".\EventMonEventClass.tlb"	".\EventMonEventClass.h"	".\EventMonEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\EventMonEventClass.tlb" /h "EventMonEventClass.h" /iid "EventMonEventClass_i.c" /Oicf 

".\EventMonEventClass.tlb"	".\EventMonEventClass.h"	".\EventMonEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\EventMonEventClass.tlb" /h "EventMonEventClass.h" /iid "EventMonEventClass_i.c" /Oicf 

".\EventMonEventClass.tlb"	".\EventMonEventClass.h"	".\EventMonEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\EventMonEventClass.tlb" /h "EventMonEventClass.h" /iid "EventMonEventClass_i.c" /Oicf 

".\EventMonEventClass.tlb"	".\EventMonEventClass.h"	".\EventMonEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/I ".\include" /tlb ".\EventMonEventClass.tlb" /h "EventMonEventClass.h" /iid "EventMonEventClass_i.c" /Oicf 

".\EventMonEventClass.tlb"	".\EventMonEventClass.h"	".\EventMonEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Debug"

MTL_SWITCHES=/I "..\include" /tlb "EventMonEventClass.tlb" /h "EventMonEventClass.h" /iid "EventMonEventClass_i.c" 

".\EventMonEventClass.tlb"	".\EventMonEventClass.h"	".\EventMonEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonEventClass.rc

"$(INTDIR)\EventMonEventClass.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\EventMonImpl.cpp

!IF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonEventClass.pch" "..\include\EventMon.h" ".\EventMonEventClass.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonEventClass - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

