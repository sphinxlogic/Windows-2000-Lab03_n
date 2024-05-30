# Microsoft Developer Studio Generated NMAKE File, Based on EventMonSubscriber.dsp
!IF "$(CFG)" == ""
CFG=EventMonSubscriber - Win32 Debug
!MESSAGE No configuration specified. Defaulting to EventMonSubscriber - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "EventMonSubscriber - Win32 Unicode Debug" && "$(CFG)" != "EventMonSubscriber - Win32 Release MinSize" && "$(CFG)" != "EventMonSubscriber - Win32 Release MinDependency" && "$(CFG)" != "EventMonSubscriber - Win32 Unicode Release MinSize" && "$(CFG)" != "EventMonSubscriber - Win32 Unicode Release MinDependency" && "$(CFG)" != "EventMonSubscriber - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EventMonSubscriber.mak" CFG="EventMonSubscriber - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EventMonSubscriber - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonSubscriber - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonSubscriber - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonSubscriber - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonSubscriber - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EventMonSubscriber - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\EventMonSubscriber.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonSubscriber.tlb" ".\EventMonSubscriber.h" ".\EventMonSubscriber_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonSubImpl.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.pch"
	-@erase "$(INTDIR)\EventMonSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventMonSubscriber.dll"
	-@erase "$(OUTDIR)\EventMonSubscriber.exp"
	-@erase "$(OUTDIR)\EventMonSubscriber.ilk"
	-@erase "$(OUTDIR)\EventMonSubscriber.lib"
	-@erase "$(OUTDIR)\EventMonSubscriber.pdb"
	-@erase ".\EventMonSubscriber.h"
	-@erase ".\EventMonSubscriber.tlb"
	-@erase ".\EventMonSubscriber_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonSubscriber.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\EventMonSubscriber.pdb" /debug /machine:$(mach_type) /def:".\EventMonSubscriber.def" /out:"$(OUTDIR)\EventMonSubscriber.dll" /implib:"$(OUTDIR)\EventMonSubscriber.lib" /pdbtype:sept 
DEF_FILE= \
	".\EventMonSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonSubImpl.obj" \
	"$(INTDIR)\EventMonSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonSubscriber.res"

"$(OUTDIR)\EventMonSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\EventMonSubscriber.dll
InputPath=.\DebugU\EventMonSubscriber.dll
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
	

!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\EventMonSubscriber.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonSubscriber.tlb" ".\EventMonSubscriber.h" ".\EventMonSubscriber_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonSubImpl.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.pch"
	-@erase "$(INTDIR)\EventMonSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonSubscriber.dll"
	-@erase "$(OUTDIR)\EventMonSubscriber.exp"
	-@erase "$(OUTDIR)\EventMonSubscriber.lib"
	-@erase ".\EventMonSubscriber.h"
	-@erase ".\EventMonSubscriber.tlb"
	-@erase ".\EventMonSubscriber_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonSubscriber.pdb" /machine:$(mach_type) /def:".\EventMonSubscriber.def" /out:"$(OUTDIR)\EventMonSubscriber.dll" /implib:"$(OUTDIR)\EventMonSubscriber.lib" 
DEF_FILE= \
	".\EventMonSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonSubImpl.obj" \
	"$(INTDIR)\EventMonSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonSubscriber.res"

"$(OUTDIR)\EventMonSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\EventMonSubscriber.dll
InputPath=.\ReleaseMinSize\EventMonSubscriber.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\EventMonSubscriber.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonSubscriber.tlb" ".\EventMonSubscriber.h" ".\EventMonSubscriber_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonSubImpl.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.pch"
	-@erase "$(INTDIR)\EventMonSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonSubscriber.dll"
	-@erase "$(OUTDIR)\EventMonSubscriber.exp"
	-@erase "$(OUTDIR)\EventMonSubscriber.lib"
	-@erase ".\EventMonSubscriber.h"
	-@erase ".\EventMonSubscriber.tlb"
	-@erase ".\EventMonSubscriber_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonSubscriber.pdb" /machine:$(mach_type) /def:".\EventMonSubscriber.def" /out:"$(OUTDIR)\EventMonSubscriber.dll" /implib:"$(OUTDIR)\EventMonSubscriber.lib" 
DEF_FILE= \
	".\EventMonSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonSubImpl.obj" \
	"$(INTDIR)\EventMonSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonSubscriber.res"

"$(OUTDIR)\EventMonSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\EventMonSubscriber.dll
InputPath=.\ReleaseMinDependency\EventMonSubscriber.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\EventMonSubscriber.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonSubscriber.tlb" ".\EventMonSubscriber.h" ".\EventMonSubscriber_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonSubImpl.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.pch"
	-@erase "$(INTDIR)\EventMonSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonSubscriber.dll"
	-@erase "$(OUTDIR)\EventMonSubscriber.exp"
	-@erase "$(OUTDIR)\EventMonSubscriber.lib"
	-@erase ".\EventMonSubscriber.h"
	-@erase ".\EventMonSubscriber.tlb"
	-@erase ".\EventMonSubscriber_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonSubscriber.pdb" /machine:$(mach_type) /def:".\EventMonSubscriber.def" /out:"$(OUTDIR)\EventMonSubscriber.dll" /implib:"$(OUTDIR)\EventMonSubscriber.lib" 
DEF_FILE= \
	".\EventMonSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonSubImpl.obj" \
	"$(INTDIR)\EventMonSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonSubscriber.res"

"$(OUTDIR)\EventMonSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\EventMonSubscriber.dll
InputPath=.\ReleaseUMinSize\EventMonSubscriber.dll
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
	

!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\EventMonSubscriber.dll" "$(OUTDIR)\EventMon.tlb" ".\EventMonSubscriber.tlb" ".\EventMonSubscriber.h" ".\EventMonSubscriber_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMon.tlb"
	-@erase "$(INTDIR)\EventMonSubImpl.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.pch"
	-@erase "$(INTDIR)\EventMonSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventMonSubscriber.dll"
	-@erase "$(OUTDIR)\EventMonSubscriber.exp"
	-@erase "$(OUTDIR)\EventMonSubscriber.lib"
	-@erase ".\EventMonSubscriber.h"
	-@erase ".\EventMonSubscriber.tlb"
	-@erase ".\EventMonSubscriber_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonSubscriber.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\EventMonSubscriber.pdb" /machine:$(mach_type) /def:".\EventMonSubscriber.def" /out:"$(OUTDIR)\EventMonSubscriber.dll" /implib:"$(OUTDIR)\EventMonSubscriber.lib" 
DEF_FILE= \
	".\EventMonSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonSubImpl.obj" \
	"$(INTDIR)\EventMonSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonSubscriber.res"

"$(OUTDIR)\EventMonSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\EventMonSubscriber.dll
InputPath=.\ReleaseUMinDependency\EventMonSubscriber.dll
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
	

!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\include\EventMon.tlb" "..\include\EventMon_i.c" "..\Output\EventMonSubscriber.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EventMonSubImpl.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.obj"
	-@erase "$(INTDIR)\EventMonSubscriber.pch"
	-@erase "$(INTDIR)\EventMonSubscriber.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventMonSubscriber.exp"
	-@erase "$(OUTDIR)\EventMonSubscriber.lib"
	-@erase "$(OUTDIR)\EventMonSubscriber.pdb"
	-@erase "..\include\EventMon.h"
	-@erase "..\include\EventMon.tlb"
	-@erase "..\include\EventMon_i.c"
	-@erase "..\Output\EventMonSubscriber.dll"
	-@erase "..\Output\EventMonSubscriber.ilk"
	-@erase ".\EventMonSubscriber.h"
	-@erase ".\EventMonSubscriber.tlb"
	-@erase ".\EventMonSubscriber_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"
    if not exist ..\Output mkdir ..\Output

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\EventMonSubscriber.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventMonSubscriber.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\EventMonSubscriber.pdb" /debug /machine:$(mach_type) /def:".\EventMonSubscriber.def" /out:"../Output/EventMonSubscriber.dll" /implib:"$(OUTDIR)\EventMonSubscriber.lib" /pdbtype:sept 
DEF_FILE= \
	".\EventMonSubscriber.def"
LINK32_OBJS= \
	"$(INTDIR)\EventMonSubImpl.obj" \
	"$(INTDIR)\EventMonSubscriber.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventMonSubscriber.res"

"..\Output\EventMonSubscriber.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=\mssdk\Samples\COM\Services\Events\EventMonitor\Output\EventMonSubscriber.dll
InputPath=\mssdk\Samples\COM\Services\Events\EventMonitor\Output\EventMonSubscriber.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("EventMonSubscriber.dep")
!INCLUDE "EventMonSubscriber.dep"
!ELSE 
!MESSAGE Warning: cannot find "EventMonSubscriber.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "EventMonSubscriber - Win32 Unicode Debug" || "$(CFG)" == "EventMonSubscriber - Win32 Release MinSize" || "$(CFG)" == "EventMonSubscriber - Win32 Release MinDependency" || "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinSize" || "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinDependency" || "$(CFG)" == "EventMonSubscriber - Win32 Debug"
SOURCE=..\Include\EventMon.idl

!IF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\EventMon.tlb" 

"$(INTDIR)\EventMon.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Debug"

MTL_SWITCHES=/I "..\include" /tlb "..\include\EventMon.tlb" /h "..\include\EventMon.h" /iid "..\include\EventMon_i.c" 

"..\include\EventMon.tlb"	"..\include\EventMon.h"	"..\include\EventMon_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonSubImpl.cpp

!IF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonSubImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonSubImpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch" ".\EventMonSubscriber.h" "..\include\EventMon.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonSubscriber.cpp

!IF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonSubscriber.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubscriber.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubscriber.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubscriber.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EventMonSubscriber.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EventMonSubscriber.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventMonSubscriber.pch" ".\EventMonSubscriber.h" ".\EventMonSubscriber_i.c" "..\include\EventMon.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonSubscriber.idl

!IF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\EventMonSubscriber.tlb" /h "EventMonSubscriber.h" /iid "EventMonSubscriber_i.c" /Oicf 

".\EventMonSubscriber.tlb"	".\EventMonSubscriber.h"	".\EventMonSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\EventMonSubscriber.tlb" /h "EventMonSubscriber.h" /iid "EventMonSubscriber_i.c" /Oicf 

".\EventMonSubscriber.tlb"	".\EventMonSubscriber.h"	".\EventMonSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\EventMonSubscriber.tlb" /h "EventMonSubscriber.h" /iid "EventMonSubscriber_i.c" /Oicf 

".\EventMonSubscriber.tlb"	".\EventMonSubscriber.h"	".\EventMonSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\EventMonSubscriber.tlb" /h "EventMonSubscriber.h" /iid "EventMonSubscriber_i.c" /Oicf 

".\EventMonSubscriber.tlb"	".\EventMonSubscriber.h"	".\EventMonSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\EventMonSubscriber.tlb" /h "EventMonSubscriber.h" /iid "EventMonSubscriber_i.c" /Oicf 

".\EventMonSubscriber.tlb"	".\EventMonSubscriber.h"	".\EventMonSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Debug"

MTL_SWITCHES=/I "..\include" /tlb "EventMonSubscriber.tlb" /h "EventMonSubscriber.h" /iid "EventMonSubscriber_i.c" 

".\EventMonSubscriber.tlb"	".\EventMonSubscriber.h"	".\EventMonSubscriber_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\EventMonSubscriber.rc

"$(INTDIR)\EventMonSubscriber.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventMonSubscriber - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\EventMonSubscriber.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventMonSubscriber.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

