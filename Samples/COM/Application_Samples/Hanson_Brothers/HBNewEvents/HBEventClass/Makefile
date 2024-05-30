# Microsoft Developer Studio Generated NMAKE File, Based on HBEventClass.dsp
!IF "$(CFG)" == ""
CFG=HBEventClass - Win32 Debug
!MESSAGE No configuration specified. Defaulting to HBEventClass - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF  

!IF "$(CFG)" != "HBEventClass - Win32 Unicode Debug" && "$(CFG)" != "HBEventClass - Win32 Release MinSize" && "$(CFG)" != "HBEventClass - Win32 Release MinDependency" && "$(CFG)" != "HBEventClass - Win32 Unicode Release MinSize" && "$(CFG)" != "HBEventClass - Win32 Unicode Release MinDependency" && "$(CFG)" != "HBEventClass - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HBEventClass.mak" CFG="HBEventClass - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HBEventClass - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBEventClass - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBEventClass - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBEventClass - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBEventClass - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HBEventClass - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "HBEventClass - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\HBEventClass.dll" "$(OUTDIR)\hb.tlb" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBEventClass.obj"
	-@erase "$(INTDIR)\HBEventClass.pch"
	-@erase "$(INTDIR)\HBEventClass.res"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBEventClass.dll"
	-@erase "$(OUTDIR)\HBEventClass.exp"
	-@erase "$(OUTDIR)\HBEventClass.ilk"
	-@erase "$(OUTDIR)\HBEventClass.lib"
	-@erase "$(OUTDIR)\HBEventClass.pdb"
	-@erase ".\HBEventClass.h"
	-@erase ".\HBEventClass.tlb"
	-@erase ".\HBEventClass_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBEventClass.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBEventClass.pdb" /debug /machine:$(mach_type) /def:".\HBEventClass.def" /out:"$(OUTDIR)\HBEventClass.dll" /implib:"$(OUTDIR)\HBEventClass.lib" /pdbtype:sept 
DEF_FILE= \
	".\HBEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\HBEventClass.obj" \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBEventClass.res"

"$(OUTDIR)\HBEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\HBEventClass.dll
InputPath=.\DebugU\HBEventClass.dll
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
	

!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\HBEventClass.dll" "$(OUTDIR)\hb.tlb" ".\HBEventClass.tlb" ".\HBEventClass.h" ".\HBEventClass_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBEventClass.obj"
	-@erase "$(INTDIR)\HBEventClass.pch"
	-@erase "$(INTDIR)\HBEventClass.res"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBEventClass.dll"
	-@erase "$(OUTDIR)\HBEventClass.exp"
	-@erase "$(OUTDIR)\HBEventClass.lib"
	-@erase ".\HBEventClass.h"
	-@erase ".\HBEventClass.tlb"
	-@erase ".\HBEventClass_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBEventClass.pdb" /machine:$(mach_type) /def:".\HBEventClass.def" /out:"$(OUTDIR)\HBEventClass.dll" /implib:"$(OUTDIR)\HBEventClass.lib" 
DEF_FILE= \
	".\HBEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\HBEventClass.obj" \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBEventClass.res"

"$(OUTDIR)\HBEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\HBEventClass.dll
InputPath=.\ReleaseMinSize\HBEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\HBEventClass.dll" "$(OUTDIR)\hb.tlb" ".\HBEventClass.tlb" ".\HBEventClass.h" ".\HBEventClass_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBEventClass.obj"
	-@erase "$(INTDIR)\HBEventClass.pch"
	-@erase "$(INTDIR)\HBEventClass.res"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBEventClass.dll"
	-@erase "$(OUTDIR)\HBEventClass.exp"
	-@erase "$(OUTDIR)\HBEventClass.lib"
	-@erase ".\HBEventClass.h"
	-@erase ".\HBEventClass.tlb"
	-@erase ".\HBEventClass_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBEventClass.pdb" /machine:$(mach_type) /def:".\HBEventClass.def" /out:"$(OUTDIR)\HBEventClass.dll" /implib:"$(OUTDIR)\HBEventClass.lib" 
DEF_FILE= \
	".\HBEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\HBEventClass.obj" \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBEventClass.res"

"$(OUTDIR)\HBEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\HBEventClass.dll
InputPath=.\ReleaseMinDependency\HBEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\HBEventClass.dll" "$(OUTDIR)\hb.tlb" ".\HBEventClass.tlb" ".\HBEventClass.h" ".\HBEventClass_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBEventClass.obj"
	-@erase "$(INTDIR)\HBEventClass.pch"
	-@erase "$(INTDIR)\HBEventClass.res"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBEventClass.dll"
	-@erase "$(OUTDIR)\HBEventClass.exp"
	-@erase "$(OUTDIR)\HBEventClass.lib"
	-@erase ".\HBEventClass.h"
	-@erase ".\HBEventClass.tlb"
	-@erase ".\HBEventClass_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBEventClass.pdb" /machine:$(mach_type) /def:".\HBEventClass.def" /out:"$(OUTDIR)\HBEventClass.dll" /implib:"$(OUTDIR)\HBEventClass.lib" 
DEF_FILE= \
	".\HBEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\HBEventClass.obj" \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBEventClass.res"

"$(OUTDIR)\HBEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\HBEventClass.dll
InputPath=.\ReleaseUMinSize\HBEventClass.dll
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
	

!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\HBEventClass.dll" "$(OUTDIR)\hb.tlb" ".\HBEventClass.tlb" ".\HBEventClass.h" ".\HBEventClass_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBEventClass.obj"
	-@erase "$(INTDIR)\HBEventClass.pch"
	-@erase "$(INTDIR)\HBEventClass.res"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBEventClass.dll"
	-@erase "$(OUTDIR)\HBEventClass.exp"
	-@erase "$(OUTDIR)\HBEventClass.lib"
	-@erase ".\HBEventClass.h"
	-@erase ".\HBEventClass.tlb"
	-@erase ".\HBEventClass_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBEventClass.pdb" /machine:$(mach_type) /def:".\HBEventClass.def" /out:"$(OUTDIR)\HBEventClass.dll" /implib:"$(OUTDIR)\HBEventClass.lib" 
DEF_FILE= \
	".\HBEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\HBEventClass.obj" \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBEventClass.res"

"$(OUTDIR)\HBEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\HBEventClass.dll
InputPath=.\ReleaseUMinDependency\HBEventClass.dll
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
	

!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\hb.tlb" ".\HBEventClass.tlb" ".\HBEventClass.h" ".\HBEventClass_i.c" "$(OUTDIR)\HBEventClass.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\hb.tlb"
	-@erase "$(INTDIR)\HBEventClass.obj"
	-@erase "$(INTDIR)\HBEventClass.pch"
	-@erase "$(INTDIR)\HBEventClass.res"
	-@erase "$(INTDIR)\HBImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBEventClass.dll"
	-@erase "$(OUTDIR)\HBEventClass.exp"
	-@erase "$(OUTDIR)\HBEventClass.ilk"
	-@erase "$(OUTDIR)\HBEventClass.lib"
	-@erase "$(OUTDIR)\HBEventClass.pdb"
	-@erase ".\HBEventClass.h"
	-@erase ".\HBEventClass.tlb"
	-@erase ".\HBEventClass_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\HBEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\HBEventClass.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBEventClass.pdb" /debug /machine:$(mach_type) /def:".\HBEventClass.def" /out:"$(OUTDIR)\HBEventClass.dll" /implib:"$(OUTDIR)\HBEventClass.lib" /pdbtype:sept 
DEF_FILE= \
	".\HBEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\HBEventClass.obj" \
	"$(INTDIR)\HBImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBEventClass.res"

"$(OUTDIR)\HBEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\HBEventClass.dll
InputPath=.\Debug\HBEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HBEventClass.dep")
!INCLUDE "HBEventClass.dep"
!ELSE 
!MESSAGE Warning: cannot find "HBEventClass.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HBEventClass - Win32 Unicode Debug" || "$(CFG)" == "HBEventClass - Win32 Release MinSize" || "$(CFG)" == "HBEventClass - Win32 Release MinDependency" || "$(CFG)" == "HBEventClass - Win32 Unicode Release MinSize" || "$(CFG)" == "HBEventClass - Win32 Unicode Release MinDependency" || "$(CFG)" == "HBEventClass - Win32 Debug"
SOURCE=..\Include\hb.idl

!IF  "$(CFG)" == "HBEventClass - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\hb.tlb" 

"$(INTDIR)\hb.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HBEventClass.cpp

"$(INTDIR)\HBEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBEventClass.pch" ".\HBEventClass_i.c" ".\HBEventClass.h"


SOURCE=.\HBEventClass.idl

!IF  "$(CFG)" == "HBEventClass - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\HBEventClass.tlb" /h "HBEventClass.h" /iid "HBEventClass_i.c" /Oicf 

".\HBEventClass.tlb"	".\HBEventClass.h"	".\HBEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\HBEventClass.tlb" /h "HBEventClass.h" /iid "HBEventClass_i.c" /Oicf 

".\HBEventClass.tlb"	".\HBEventClass.h"	".\HBEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\HBEventClass.tlb" /h "HBEventClass.h" /iid "HBEventClass_i.c" /Oicf 

".\HBEventClass.tlb"	".\HBEventClass.h"	".\HBEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\HBEventClass.tlb" /h "HBEventClass.h" /iid "HBEventClass_i.c" /Oicf 

".\HBEventClass.tlb"	".\HBEventClass.h"	".\HBEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\HBEventClass.tlb" /h "HBEventClass.h" /iid "HBEventClass_i.c" /Oicf 

".\HBEventClass.tlb"	".\HBEventClass.h"	".\HBEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Debug"

MTL_SWITCHES=/tlb ".\HBEventClass.tlb" /h "HBEventClass.h" /iid "HBEventClass_i.c" /Oicf 

".\HBEventClass.tlb"	".\HBEventClass.h"	".\HBEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HBEventClass.rc

"$(INTDIR)\HBEventClass.res" : $(SOURCE) "$(INTDIR)" ".\HBEventClass.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\HBImpl.cpp

"$(INTDIR)\HBImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBEventClass.pch" ".\HBEventClass.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HBEventClass - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\HBEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBEventClass - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\HBEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

