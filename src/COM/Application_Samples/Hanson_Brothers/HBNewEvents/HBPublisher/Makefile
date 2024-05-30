# Microsoft Developer Studio Generated NMAKE File, Based on HBPublisher.dsp
!IF "$(CFG)" == ""
CFG=HBPublisher - Win32 Debug
!MESSAGE No configuration specified. Defaulting to HBPublisher - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF  

!IF "$(CFG)" != "HBPublisher - Win32 Unicode Debug" && "$(CFG)" != "HBPublisher - Win32 Release MinSize" && "$(CFG)" != "HBPublisher - Win32 Release MinDependency" && "$(CFG)" != "HBPublisher - Win32 Unicode Release MinSize" && "$(CFG)" != "HBPublisher - Win32 Unicode Release MinDependency" && "$(CFG)" != "HBPublisher - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HBPublisher.mak" CFG="HBPublisher - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HBPublisher - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBPublisher - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBPublisher - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBPublisher - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBPublisher - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBPublisher - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "HBPublisher - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\HBPublisher.dll" "$(OUTDIR)\HB.tlb" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\HB.tlb"
	-@erase "$(INTDIR)\HBPublisher.obj"
	-@erase "$(INTDIR)\HBPublisher.pch"
	-@erase "$(INTDIR)\HBPublisher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBPublisher.dll"
	-@erase "$(OUTDIR)\HBPublisher.exp"
	-@erase "$(OUTDIR)\HBPublisher.ilk"
	-@erase "$(OUTDIR)\HBPublisher.lib"
	-@erase "$(OUTDIR)\HBPublisher.pdb"
	-@erase ".\HBPublisher.h"
	-@erase ".\HBPublisher.tlb"
	-@erase ".\HBPublisher_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBPublisher.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBPublisher.pdb" /debug /machine:$(mach_type) /def:".\HBPublisher.def" /out:"$(OUTDIR)\HBPublisher.dll" /implib:"$(OUTDIR)\HBPublisher.lib" /pdbtype:sept 
DEF_FILE= \
	".\HBPublisher.def"
LINK32_OBJS= \
	"$(INTDIR)\HBPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBPublisher.res"

"$(OUTDIR)\HBPublisher.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\HBPublisher.dll
InputPath=.\DebugU\HBPublisher.dll
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
	

!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\HBPublisher.dll" "$(OUTDIR)\HB.tlb" ".\HBPublisher.tlb" ".\HBPublisher.h" ".\HBPublisher_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\HB.tlb"
	-@erase "$(INTDIR)\HBPublisher.obj"
	-@erase "$(INTDIR)\HBPublisher.pch"
	-@erase "$(INTDIR)\HBPublisher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBPublisher.dll"
	-@erase "$(OUTDIR)\HBPublisher.exp"
	-@erase "$(OUTDIR)\HBPublisher.lib"
	-@erase ".\HBPublisher.h"
	-@erase ".\HBPublisher.tlb"
	-@erase ".\HBPublisher_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBPublisher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBPublisher.pdb" /machine:$(mach_type) /def:".\HBPublisher.def" /out:"$(OUTDIR)\HBPublisher.dll" /implib:"$(OUTDIR)\HBPublisher.lib" 
DEF_FILE= \
	".\HBPublisher.def"
LINK32_OBJS= \
	"$(INTDIR)\HBPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBPublisher.res"

"$(OUTDIR)\HBPublisher.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\HBPublisher.dll
InputPath=.\ReleaseMinSize\HBPublisher.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\HBPublisher.dll" "$(OUTDIR)\HB.tlb" ".\HBPublisher.tlb" ".\HBPublisher.h" ".\HBPublisher_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\HB.tlb"
	-@erase "$(INTDIR)\HBPublisher.obj"
	-@erase "$(INTDIR)\HBPublisher.pch"
	-@erase "$(INTDIR)\HBPublisher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBPublisher.dll"
	-@erase "$(OUTDIR)\HBPublisher.exp"
	-@erase "$(OUTDIR)\HBPublisher.lib"
	-@erase ".\HBPublisher.h"
	-@erase ".\HBPublisher.tlb"
	-@erase ".\HBPublisher_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBPublisher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBPublisher.pdb" /machine:$(mach_type) /def:".\HBPublisher.def" /out:"$(OUTDIR)\HBPublisher.dll" /implib:"$(OUTDIR)\HBPublisher.lib" 
DEF_FILE= \
	".\HBPublisher.def"
LINK32_OBJS= \
	"$(INTDIR)\HBPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBPublisher.res"

"$(OUTDIR)\HBPublisher.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\HBPublisher.dll
InputPath=.\ReleaseMinDependency\HBPublisher.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\HBPublisher.dll" "$(OUTDIR)\HB.tlb" ".\HBPublisher.tlb" ".\HBPublisher.h" ".\HBPublisher_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\HB.tlb"
	-@erase "$(INTDIR)\HBPublisher.obj"
	-@erase "$(INTDIR)\HBPublisher.pch"
	-@erase "$(INTDIR)\HBPublisher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBPublisher.dll"
	-@erase "$(OUTDIR)\HBPublisher.exp"
	-@erase "$(OUTDIR)\HBPublisher.lib"
	-@erase ".\HBPublisher.h"
	-@erase ".\HBPublisher.tlb"
	-@erase ".\HBPublisher_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBPublisher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBPublisher.pdb" /machine:$(mach_type) /def:".\HBPublisher.def" /out:"$(OUTDIR)\HBPublisher.dll" /implib:"$(OUTDIR)\HBPublisher.lib" 
DEF_FILE= \
	".\HBPublisher.def"
LINK32_OBJS= \
	"$(INTDIR)\HBPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBPublisher.res"

"$(OUTDIR)\HBPublisher.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\HBPublisher.dll
InputPath=.\ReleaseUMinSize\HBPublisher.dll
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
	

!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\HBPublisher.dll" "$(OUTDIR)\HB.tlb" ".\HBPublisher.tlb" ".\HBPublisher.h" ".\HBPublisher_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\HB.tlb"
	-@erase "$(INTDIR)\HBPublisher.obj"
	-@erase "$(INTDIR)\HBPublisher.pch"
	-@erase "$(INTDIR)\HBPublisher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBPublisher.dll"
	-@erase "$(OUTDIR)\HBPublisher.exp"
	-@erase "$(OUTDIR)\HBPublisher.lib"
	-@erase ".\HBPublisher.h"
	-@erase ".\HBPublisher.tlb"
	-@erase ".\HBPublisher_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBPublisher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBPublisher.pdb" /machine:$(mach_type) /def:".\HBPublisher.def" /out:"$(OUTDIR)\HBPublisher.dll" /implib:"$(OUTDIR)\HBPublisher.lib" 
DEF_FILE= \
	".\HBPublisher.def"
LINK32_OBJS= \
	"$(INTDIR)\HBPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBPublisher.res"

"$(OUTDIR)\HBPublisher.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\HBPublisher.dll
InputPath=.\ReleaseUMinDependency\HBPublisher.dll
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
	

!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\HB.tlb" ".\HBPublisher.tlb" ".\HBPublisher.h" ".\HBPublisher_i.c" "$(OUTDIR)\HBPublisher.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\HB.tlb"
	-@erase "$(INTDIR)\HBPublisher.obj"
	-@erase "$(INTDIR)\HBPublisher.pch"
	-@erase "$(INTDIR)\HBPublisher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBPublisher.dll"
	-@erase "$(OUTDIR)\HBPublisher.exp"
	-@erase "$(OUTDIR)\HBPublisher.ilk"
	-@erase "$(OUTDIR)\HBPublisher.lib"
	-@erase "$(OUTDIR)\HBPublisher.pdb"
	-@erase ".\HBPublisher.h"
	-@erase ".\HBPublisher.tlb"
	-@erase ".\HBPublisher_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\HBPublisher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBPublisher.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBPublisher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBPublisher.pdb" /debug /machine:$(mach_type) /def:".\HBPublisher.def" /out:"$(OUTDIR)\HBPublisher.dll" /implib:"$(OUTDIR)\HBPublisher.lib" /pdbtype:sept 
DEF_FILE= \
	".\HBPublisher.def"
LINK32_OBJS= \
	"$(INTDIR)\HBPublisher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBPublisher.res"

"$(OUTDIR)\HBPublisher.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\HBPublisher.dll
InputPath=.\Debug\HBPublisher.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HBPublisher.dep")
!INCLUDE "HBPublisher.dep"
!ELSE 
!MESSAGE Warning: cannot find "HBPublisher.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HBPublisher - Win32 Unicode Debug" || "$(CFG)" == "HBPublisher - Win32 Release MinSize" || "$(CFG)" == "HBPublisher - Win32 Release MinDependency" || "$(CFG)" == "HBPublisher - Win32 Unicode Release MinSize" || "$(CFG)" == "HBPublisher - Win32 Unicode Release MinDependency" || "$(CFG)" == "HBPublisher - Win32 Debug"
SOURCE=..\Include\HB.idl

!IF  "$(CFG)" == "HBPublisher - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\HB.tlb" 

"$(INTDIR)\HB.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\HB.tlb" 

"$(INTDIR)\HB.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\HB.tlb" 

"$(INTDIR)\HB.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\HB.tlb" 

"$(INTDIR)\HB.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\HB.tlb" 

"$(INTDIR)\HB.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\HB.tlb" 

"$(INTDIR)\HB.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HBPublisher.cpp

"$(INTDIR)\HBPublisher.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBPublisher.pch" ".\HBPublisher.h" ".\HBPublisher_i.c"


SOURCE=.\HBPublisher.idl

!IF  "$(CFG)" == "HBPublisher - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\HBPublisher.tlb" /h "HBPublisher.h" /iid "HBPublisher_i.c" /Oicf 

".\HBPublisher.tlb"	".\HBPublisher.h"	".\HBPublisher_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\HBPublisher.tlb" /h "HBPublisher.h" /iid "HBPublisher_i.c" /Oicf 

".\HBPublisher.tlb"	".\HBPublisher.h"	".\HBPublisher_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\HBPublisher.tlb" /h "HBPublisher.h" /iid "HBPublisher_i.c" /Oicf 

".\HBPublisher.tlb"	".\HBPublisher.h"	".\HBPublisher_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\HBPublisher.tlb" /h "HBPublisher.h" /iid "HBPublisher_i.c" /Oicf 

".\HBPublisher.tlb"	".\HBPublisher.h"	".\HBPublisher_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\HBPublisher.tlb" /h "HBPublisher.h" /iid "HBPublisher_i.c" /Oicf 

".\HBPublisher.tlb"	".\HBPublisher.h"	".\HBPublisher_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Debug"

MTL_SWITCHES=/tlb ".\HBPublisher.tlb" /h "HBPublisher.h" /iid "HBPublisher_i.c" /Oicf 

".\HBPublisher.tlb"	".\HBPublisher.h"	".\HBPublisher_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HBPublisher.rc

"$(INTDIR)\HBPublisher.res" : $(SOURCE) "$(INTDIR)" ".\HBPublisher.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HBPublisher - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBPublisher - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\HBPublisher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBPublisher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

