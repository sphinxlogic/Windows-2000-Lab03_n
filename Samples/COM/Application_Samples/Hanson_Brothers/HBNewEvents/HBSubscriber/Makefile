# Microsoft Developer Studio Generated NMAKE File, Based on HBSubscriber.dsp
!IF "$(CFG)" == ""
CFG=HBSubscriber - Win32 Debug
!MESSAGE No configuration specified. Defaulting to HBSubscriber - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "HBSubscriber - Win32 Unicode Debug" && "$(CFG)" != "HBSubscriber - Win32 Release MinSize" && "$(CFG)" != "HBSubscriber - Win32 Release MinDependency" && "$(CFG)" != "HBSubscriber - Win32 Unicode Release MinSize" && "$(CFG)" != "HBSubscriber - Win32 Unicode Release MinDependency" && "$(CFG)" != "HBSubscriber - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HBSubscriber.mak" CFG="HBSubscriber - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HBSubscriber - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBSubscriber - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBSubscriber - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBSubscriber - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBSubscriber - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBSubscriber - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "HBSubscriber - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\HBSubscriber.dll" "$(OUTDIR)\hb.tlb" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\HBSubImpl.obj"
	-@erase "$(INTDIR)\HBSubscriber.obj"
	-@erase "$(INTDIR)\HBSubscriber.pch"
	-@erase "$(INTDIR)\HBSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBSubscriber.dll"
	-@erase "$(OUTDIR)\HBSubscriber.exp"
	-@erase "$(OUTDIR)\HBSubscriber.ilk"
	-@erase "$(OUTDIR)\HBSubscriber.lib"
	-@erase "$(OUTDIR)\HBSubscriber.pdb"
	-@erase ".\HBSubscriber.h"
	-@erase ".\HBSubscriber.tlb"
	-@erase ".\HBSubscriber_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBSubscriber.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBSubscriber.pdb" /debug /machine:$(mach_type) /def:".\HBSubscriber.def" /out:"$(OUTDIR)\HBSubscriber.dll" /implib:"$(OUTDIR)\HBSubscriber.lib" /pdbtype:sept 
DEF_FILE= \
	".\HBSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\HBSubImpl.obj" \
	"$(INTDIR)\HBSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBSubscriber.res"

"$(OUTDIR)\HBSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\HBSubscriber.dll
InputPath=.\DebugU\HBSubscriber.dll
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
	

!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\HBSubscriber.dll" "$(OUTDIR)\hb.tlb" ".\HBSubscriber.tlb" ".\HBSubscriber.h" ".\HBSubscriber_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\HBSubImpl.obj"
	-@erase "$(INTDIR)\HBSubscriber.obj"
	-@erase "$(INTDIR)\HBSubscriber.pch"
	-@erase "$(INTDIR)\HBSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBSubscriber.dll"
	-@erase "$(OUTDIR)\HBSubscriber.exp"
	-@erase "$(OUTDIR)\HBSubscriber.lib"
	-@erase ".\HBSubscriber.h"
	-@erase ".\HBSubscriber.tlb"
	-@erase ".\HBSubscriber_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBSubscriber.pdb" /machine:$(mach_type) /def:".\HBSubscriber.def" /out:"$(OUTDIR)\HBSubscriber.dll" /implib:"$(OUTDIR)\HBSubscriber.lib" 
DEF_FILE= \
	".\HBSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\HBSubImpl.obj" \
	"$(INTDIR)\HBSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBSubscriber.res"

"$(OUTDIR)\HBSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\HBSubscriber.dll
InputPath=.\ReleaseMinSize\HBSubscriber.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\HBSubscriber.dll" "$(OUTDIR)\hb.tlb" ".\HBSubscriber.tlb" ".\HBSubscriber.h" ".\HBSubscriber_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\HBSubImpl.obj"
	-@erase "$(INTDIR)\HBSubscriber.obj"
	-@erase "$(INTDIR)\HBSubscriber.pch"
	-@erase "$(INTDIR)\HBSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBSubscriber.dll"
	-@erase "$(OUTDIR)\HBSubscriber.exp"
	-@erase "$(OUTDIR)\HBSubscriber.lib"
	-@erase ".\HBSubscriber.h"
	-@erase ".\HBSubscriber.tlb"
	-@erase ".\HBSubscriber_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBSubscriber.pdb" /machine:$(mach_type) /def:".\HBSubscriber.def" /out:"$(OUTDIR)\HBSubscriber.dll" /implib:"$(OUTDIR)\HBSubscriber.lib" 
DEF_FILE= \
	".\HBSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\HBSubImpl.obj" \
	"$(INTDIR)\HBSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBSubscriber.res"

"$(OUTDIR)\HBSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\HBSubscriber.dll
InputPath=.\ReleaseMinDependency\HBSubscriber.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\HBSubscriber.dll" "$(OUTDIR)\hb.tlb" ".\HBSubscriber.tlb" ".\HBSubscriber.h" ".\HBSubscriber_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\HBSubImpl.obj"
	-@erase "$(INTDIR)\HBSubscriber.obj"
	-@erase "$(INTDIR)\HBSubscriber.pch"
	-@erase "$(INTDIR)\HBSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBSubscriber.dll"
	-@erase "$(OUTDIR)\HBSubscriber.exp"
	-@erase "$(OUTDIR)\HBSubscriber.lib"
	-@erase ".\HBSubscriber.h"
	-@erase ".\HBSubscriber.tlb"
	-@erase ".\HBSubscriber_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBSubscriber.pdb" /machine:$(mach_type) /def:".\HBSubscriber.def" /out:"$(OUTDIR)\HBSubscriber.dll" /implib:"$(OUTDIR)\HBSubscriber.lib" 
DEF_FILE= \
	".\HBSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\HBSubImpl.obj" \
	"$(INTDIR)\HBSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBSubscriber.res"

"$(OUTDIR)\HBSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\HBSubscriber.dll
InputPath=.\ReleaseUMinSize\HBSubscriber.dll
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
	

!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\HBSubscriber.dll" "$(OUTDIR)\hb.tlb" ".\HBSubscriber.tlb" ".\HBSubscriber.h" ".\HBSubscriber_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\HBSubImpl.obj"
	-@erase "$(INTDIR)\HBSubscriber.obj"
	-@erase "$(INTDIR)\HBSubscriber.pch"
	-@erase "$(INTDIR)\HBSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBSubscriber.dll"
	-@erase "$(OUTDIR)\HBSubscriber.exp"
	-@erase "$(OUTDIR)\HBSubscriber.lib"
	-@erase ".\HBSubscriber.h"
	-@erase ".\HBSubscriber.tlb"
	-@erase ".\HBSubscriber_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBSubscriber.pdb" /machine:$(mach_type) /def:".\HBSubscriber.def" /out:"$(OUTDIR)\HBSubscriber.dll" /implib:"$(OUTDIR)\HBSubscriber.lib" 
DEF_FILE= \
	".\HBSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\HBSubImpl.obj" \
	"$(INTDIR)\HBSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBSubscriber.res"

"$(OUTDIR)\HBSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\HBSubscriber.dll
InputPath=.\ReleaseUMinDependency\HBSubscriber.dll
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
	

!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\hb.tlb" ".\HBSubscriber.tlb" ".\HBSubscriber.h" ".\HBSubscriber_i.c" "$(OUTDIR)\HBSubscriber.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\HBSubImpl.obj"
	-@erase "$(INTDIR)\HBSubscriber.obj"
	-@erase "$(INTDIR)\HBSubscriber.pch"
	-@erase "$(INTDIR)\HBSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBSubscriber.dll"
	-@erase "$(OUTDIR)\HBSubscriber.exp"
	-@erase "$(OUTDIR)\HBSubscriber.ilk"
	-@erase "$(OUTDIR)\HBSubscriber.lib"
	-@erase "$(OUTDIR)\HBSubscriber.pdb"
	-@erase ".\HBSubscriber.h"
	-@erase ".\HBSubscriber.tlb"
	-@erase ".\HBSubscriber_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\HBSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBSubscriber.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBSubscriber.pdb" /debug /machine:$(mach_type) /def:".\HBSubscriber.def" /out:"$(OUTDIR)\HBSubscriber.dll" /implib:"$(OUTDIR)\HBSubscriber.lib" /pdbtype:sept 
DEF_FILE= \
	".\HBSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\HBSubImpl.obj" \
	"$(INTDIR)\HBSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBSubscriber.res"

"$(OUTDIR)\HBSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\HBSubscriber.dll
InputPath=.\Debug\HBSubscriber.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HBSubscriber.dep")
!INCLUDE "HBSubscriber.dep"
!ELSE 
!MESSAGE Warning: cannot find "HBSubscriber.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HBSubscriber - Win32 Unicode Debug" || "$(CFG)" == "HBSubscriber - Win32 Release MinSize" || "$(CFG)" == "HBSubscriber - Win32 Release MinDependency" || "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinSize" || "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinDependency" || "$(CFG)" == "HBSubscriber - Win32 Debug"
SOURCE=..\Include\hb.idl

!IF  "$(CFG)" == "HBSubscriber - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\HBEventClass\HBImpl.cpp

"$(INTDIR)\HBImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBSubscriber.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\HBSubImpl.cpp

"$(INTDIR)\HBSubImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBSubscriber.pch" ".\HBSubscriber.h"


SOURCE=.\HBSubscriber.cpp

"$(INTDIR)\HBSubscriber.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBSubscriber.pch" ".\HBSubscriber.h" ".\HBSubscriber_i.c"


SOURCE=.\HBSubscriber.idl

!IF  "$(CFG)" == "HBSubscriber - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\HBSubscriber.tlb" /h "HBSubscriber.h" /iid "HBSubscriber_i.c" /Oicf 

".\HBSubscriber.tlb"	".\HBSubscriber.h"	".\HBSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\HBSubscriber.tlb" /h "HBSubscriber.h" /iid "HBSubscriber_i.c" /Oicf 

".\HBSubscriber.tlb"	".\HBSubscriber.h"	".\HBSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\HBSubscriber.tlb" /h "HBSubscriber.h" /iid "HBSubscriber_i.c" /Oicf 

".\HBSubscriber.tlb"	".\HBSubscriber.h"	".\HBSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\HBSubscriber.tlb" /h "HBSubscriber.h" /iid "HBSubscriber_i.c" /Oicf 

".\HBSubscriber.tlb"	".\HBSubscriber.h"	".\HBSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\HBSubscriber.tlb" /h "HBSubscriber.h" /iid "HBSubscriber_i.c" /Oicf 

".\HBSubscriber.tlb"	".\HBSubscriber.h"	".\HBSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Debug"

MTL_SWITCHES=/tlb ".\HBSubscriber.tlb" /h "HBSubscriber.h" /iid "HBSubscriber_i.c" /Oicf 

".\HBSubscriber.tlb"	".\HBSubscriber.h"	".\HBSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HBSubscriber.rc

"$(INTDIR)\HBSubscriber.res" : $(SOURCE) "$(INTDIR)" ".\HBSubscriber.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HBSubscriber - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBSubscriber - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\HBSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

