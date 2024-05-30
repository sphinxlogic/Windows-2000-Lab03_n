# Microsoft Developer Studio Generated NMAKE File, Based on EventMonFilter.dsp
!IF "$(CFG)" == ""
CFG=EventMonFilter - Win32 Debug
!MESSAGE No configuration specified. Defaulting to EventMonFilter - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "EventMonFilter - Win32 Unicode Debug" && "$(CFG)" != "EventMonFilter - Win32 Release MinSize" && "$(CFG)" != "EventMonFilter - Win32 Release MinDependency" && "$(CFG)" != "EventMonFilter - Win32 Unicode Release MinSize" && "$(CFG)" != "EventMonFilter - Win32 Unicode Release MinDependency" && "$(CFG)" != "EventMonFilter - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EventMonFilter.mak" CFG="EventMonFilter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EventMonFilter - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonFilter - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonFilter - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonFilter - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonFilter - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonFilter - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "EventMonFilter - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\EventMonFilter.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonFilter.tlb" ".\EventMonFilter.h" ".\EventMonFilter_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonFilter.obj"
	-@erase "$(INTDIR)\EventMonFilter.pch"
	-@erase "$(INTDIR)\EventMonFilter.res"
	-@erase "$(INTDIR)\EventMonFilterImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventMonFilter.dll"
	-@erase "$(OUTDIR)\EventMonFilter.exp"
	-@erase "$(OUTDIR)\EventMonFilter.ilk"
	-@erase "$(OUTDIR)\EventMonFilter.lib"
	-@erase "$(OUTDIR)\EventMonFilter.pdb"
	-@erase ".\EventMonFilter.h"
	-@erase ".\EventMonFilter.tlb"
	-@erase ".\EventMonFilter_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonFilter.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonFilter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\EventMonFilter.pdb" /debug /machine:$(mach_type) /def:".\EventMonFilter.def" /out:"$(OUTDIR)\EventMonFilter.dll" /implib:"$(OUTDIR)\EventMonFilter.lib" /pdbtype:sept 
DEF_FILE= \
	".\EventMonFilter.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonFilter.obj" \
	"$(INTDIR)\EventMonFilterImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonFilter.res"

"$(OUTDIR)\EventMonFilter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\EventMonFilter.dll
InputPath=.\DebugU\EventMonFilter.dll
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
	

!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\EventMonFilter.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonFilter.tlb" ".\EventMonFilter.h" ".\EventMonFilter_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonFilter.obj"
	-@erase "$(INTDIR)\EventMonFilter.pch"
	-@erase "$(INTDIR)\EventMonFilter.res"
	-@erase "$(INTDIR)\EventMonFilterImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonFilter.dll"
	-@erase "$(OUTDIR)\EventMonFilter.exp"
	-@erase "$(OUTDIR)\EventMonFilter.lib"
	-@erase ".\EventMonFilter.h"
	-@erase ".\EventMonFilter.tlb"
	-@erase ".\EventMonFilter_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonFilter.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonFilter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonFilter.pdb" /machine:$(mach_type) /def:".\EventMonFilter.def" /out:"$(OUTDIR)\EventMonFilter.dll" /implib:"$(OUTDIR)\EventMonFilter.lib" 
DEF_FILE= \
	".\EventMonFilter.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonFilter.obj" \
	"$(INTDIR)\EventMonFilterImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonFilter.res"

"$(OUTDIR)\EventMonFilter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\EventMonFilter.dll
InputPath=.\ReleaseMinSize\EventMonFilter.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\EventMonFilter.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonFilter.tlb" ".\EventMonFilter.h" ".\EventMonFilter_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonFilter.obj"
	-@erase "$(INTDIR)\EventMonFilter.pch"
	-@erase "$(INTDIR)\EventMonFilter.res"
	-@erase "$(INTDIR)\EventMonFilterImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonFilter.dll"
	-@erase "$(OUTDIR)\EventMonFilter.exp"
	-@erase "$(OUTDIR)\EventMonFilter.lib"
	-@erase ".\EventMonFilter.h"
	-@erase ".\EventMonFilter.tlb"
	-@erase ".\EventMonFilter_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonFilter.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonFilter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonFilter.pdb" /machine:$(mach_type) /def:".\EventMonFilter.def" /out:"$(OUTDIR)\EventMonFilter.dll" /implib:"$(OUTDIR)\EventMonFilter.lib" 
DEF_FILE= \
	".\EventMonFilter.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonFilter.obj" \
	"$(INTDIR)\EventMonFilterImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonFilter.res"

"$(OUTDIR)\EventMonFilter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\EventMonFilter.dll
InputPath=.\ReleaseMinDependency\EventMonFilter.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\EventMonFilter.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonFilter.tlb" ".\EventMonFilter.h" ".\EventMonFilter_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonFilter.obj"
	-@erase "$(INTDIR)\EventMonFilter.pch"
	-@erase "$(INTDIR)\EventMonFilter.res"
	-@erase "$(INTDIR)\EventMonFilterImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonFilter.dll"
	-@erase "$(OUTDIR)\EventMonFilter.exp"
	-@erase "$(OUTDIR)\EventMonFilter.lib"
	-@erase ".\EventMonFilter.h"
	-@erase ".\EventMonFilter.tlb"
	-@erase ".\EventMonFilter_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonFilter.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonFilter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonFilter.pdb" /machine:$(mach_type) /def:".\EventMonFilter.def" /out:"$(OUTDIR)\EventMonFilter.dll" /implib:"$(OUTDIR)\EventMonFilter.lib" 
DEF_FILE= \
	".\EventMonFilter.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonFilter.obj" \
	"$(INTDIR)\EventMonFilterImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonFilter.res"

"$(OUTDIR)\EventMonFilter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\EventMonFilter.dll
InputPath=.\ReleaseUMinSize\EventMonFilter.dll
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
	

!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\EventMonFilter.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonFilter.tlb" ".\EventMonFilter.h" ".\EventMonFilter_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonFilter.obj"
	-@erase "$(INTDIR)\EventMonFilter.pch"
	-@erase "$(INTDIR)\EventMonFilter.res"
	-@erase "$(INTDIR)\EventMonFilterImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonFilter.dll"
	-@erase "$(OUTDIR)\EventMonFilter.exp"
	-@erase "$(OUTDIR)\EventMonFilter.lib"
	-@erase ".\EventMonFilter.h"
	-@erase ".\EventMonFilter.tlb"
	-@erase ".\EventMonFilter_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonFilter.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonFilter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonFilter.pdb" /machine:$(mach_type) /def:".\EventMonFilter.def" /out:"$(OUTDIR)\EventMonFilter.dll" /implib:"$(OUTDIR)\EventMonFilter.lib" 
DEF_FILE= \
	".\EventMonFilter.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonFilter.obj" \
	"$(INTDIR)\EventMonFilterImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonFilter.res"

"$(OUTDIR)\EventMonFilter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\EventMonFilter.dll
InputPath=.\ReleaseUMinDependency\EventMonFilter.dll
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
	

!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\include\EventMon_i.c" "..\Output\EventMonFilter.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonFilter.obj"
	-@erase "$(INTDIR)\EventMonFilter.pch"
	-@erase "$(INTDIR)\EventMonFilter.res"
	-@erase "$(INTDIR)\EventMonFilterImpl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventMonFilter.exp"
	-@erase "$(OUTDIR)\EventMonFilter.lib"
	-@erase "$(OUTDIR)\EventMonFilter.pdb"
	-@erase "..\include\EventMon.h"
	-@erase "..\include\EventMon_i.c"
	-@erase "..\Output\EventMonFilter.dll"
	-@erase "..\Output\EventMonFilter.ilk"
	-@erase ".\EventMonFilter.h"
	-@erase ".\EventMonFilter.tlb"
	-@erase ".\EventMonFilter_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
    if not exist ..\Output mkdir ..\Output

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonFilter.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonFilter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\EventMonFilter.pdb" /debug /machine:$(mach_type) /def:".\EventMonFilter.def" /out:"../Output/EventMonFilter.dll" /implib:"$(OUTDIR)\EventMonFilter.lib" /pdbtype:sept 
DEF_FILE= \
	".\EventMonFilter.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonFilter.obj" \
	"$(INTDIR)\EventMonFilterImpl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonFilter.res"

"..\Output\EventMonFilter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=\mssdk\Samples\COM\Services\Events\EventMonitor\Output\EventMonFilter.dll
InputPath=\mssdk\Samples\COM\Services\Events\EventMonitor\Output\EventMonFilter.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("EventMonFilter.dep")
!INCLUDE "EventMonFilter.dep"
!ELSE 
!MESSAGE Warning: cannot find "EventMonFilter.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "EventMonFilter - Win32 Unicode Debug" || "$(CFG)" == "EventMonFilter - Win32 Release MinSize" || "$(CFG)" == "EventMonFilter - Win32 Release MinDependency" || "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinSize" || "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinDependency" || "$(CFG)" == "EventMonFilter - Win32 Debug"
SOURCE=..\Include\EventMon.idl

!IF  "$(CFG)" == "EventMonFilter - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Debug"

MTL_SWITCHES=/I "..\include" /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c" 

"..\include\EventMon.h"	"..\include\EventMon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonFilter.cpp

!IF  "$(CFG)" == "EventMonFilter - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonFilter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonFilter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch" ".\EventMonFilter_i.c" ".\EventMonFilter.h" "..\include\EventMon.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonFilter.idl

!IF  "$(CFG)" == "EventMonFilter - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\EventMonFilter.tlb" /h "EventMonFilter.h" /iid "EventMonFilter_i.c" /Oicf 

".\EventMonFilter.tlb"	".\EventMonFilter.h"	".\EventMonFilter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\EventMonFilter.tlb" /h "EventMonFilter.h" /iid "EventMonFilter_i.c" /Oicf 

".\EventMonFilter.tlb"	".\EventMonFilter.h"	".\EventMonFilter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\EventMonFilter.tlb" /h "EventMonFilter.h" /iid "EventMonFilter_i.c" /Oicf 

".\EventMonFilter.tlb"	".\EventMonFilter.h"	".\EventMonFilter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\EventMonFilter.tlb" /h "EventMonFilter.h" /iid "EventMonFilter_i.c" /Oicf 

".\EventMonFilter.tlb"	".\EventMonFilter.h"	".\EventMonFilter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\EventMonFilter.tlb" /h "EventMonFilter.h" /iid "EventMonFilter_i.c" /Oicf 

".\EventMonFilter.tlb"	".\EventMonFilter.h"	".\EventMonFilter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Debug"

MTL_SWITCHES=/I "..\include" /tlb "EventMonFilter.tlb" /h "EventMonFilter.h" /iid "EventMonFilter_i.c" 

".\EventMonFilter.tlb"	".\EventMonFilter.h"	".\EventMonFilter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonFilter.rc

"$(INTDIR)\EventMonFilter.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\EventMonFilterImpl.cpp

!IF  "$(CFG)" == "EventMonFilter - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonFilterImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilterImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilterImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilterImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonFilterImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonFilter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonFilterImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonFilter.pch" ".\EventMonFilter.h" "..\include\EventMon.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "EventMonFilter - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonFilter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonFilter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonFilter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonFilter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonFilter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonFilter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonFilter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonFilter - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonFilter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonFilter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

