# Microsoft Developer Studio Generated NMAKE File, Based on AtlBehave.dsp
!IF "$(CFG)" == ""
CFG=AtlBehave - Win32 Debug
!MESSAGE No configuration specified. Defaulting to AtlBehave - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AtlBehave - Win32 Debug" && "$(CFG)" != "AtlBehave - Win32 Unicode Debug" && "$(CFG)" != "AtlBehave - Win32 Release MinSize" && "$(CFG)" != "AtlBehave - Win32 Release MinDependency" && "$(CFG)" != "AtlBehave - Win32 Unicode Release MinSize" && "$(CFG)" != "AtlBehave - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AtlBehave.mak" CFG="AtlBehave - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AtlBehave - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AtlBehave - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AtlBehave - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AtlBehave - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AtlBehave - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AtlBehave - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "AtlBehave - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\AtlBehave.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AtlBehave.obj"
	-@erase "$(INTDIR)\AtlBehave.pch"
	-@erase "$(INTDIR)\AtlBehave.res"
	-@erase "$(INTDIR)\Behavior.obj"
	-@erase "$(INTDIR)\EventSink.obj"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AtlBehave.dll"
	-@erase "$(OUTDIR)\AtlBehave.exp"
	-@erase "$(OUTDIR)\AtlBehave.ilk"
	-@erase "$(OUTDIR)\AtlBehave.lib"
	-@erase "$(OUTDIR)\AtlBehave.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\AtlBehave.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBehave.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBehave.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\AtlBehave.pdb" /debug /machine:I386 /def:".\AtlBehave.def" /out:"$(OUTDIR)\AtlBehave.dll" /implib:"$(OUTDIR)\AtlBehave.lib" /pdbtype:sept
DEF_FILE= \
	".\AtlBehave.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlBehave.obj" \
	"$(INTDIR)\Behavior.obj" \
	"$(INTDIR)\EventSink.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBehave.res"

"$(OUTDIR)\AtlBehave.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\AtlBehave.dll
InputPath=.\Debug\AtlBehave.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\AtlBehave_i.c" ".\AtlBehave.tlb" ".\AtlBehave.h" "$(OUTDIR)\AtlBehave.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AtlBehave.obj"
	-@erase "$(INTDIR)\AtlBehave.pch"
	-@erase "$(INTDIR)\AtlBehave.res"
	-@erase "$(INTDIR)\Behavior.obj"
	-@erase "$(INTDIR)\EventSink.obj"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AtlBehave.dll"
	-@erase "$(OUTDIR)\AtlBehave.exp"
	-@erase "$(OUTDIR)\AtlBehave.ilk"
	-@erase "$(OUTDIR)\AtlBehave.lib"
	-@erase "$(OUTDIR)\AtlBehave.pdb"
	-@erase ".\AtlBehave.h"
	-@erase ".\AtlBehave.tlb"
	-@erase ".\AtlBehave_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\AtlBehave.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBehave.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBehave.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\AtlBehave.pdb" /debug /machine:I386 /def:".\AtlBehave.def" /out:"$(OUTDIR)\AtlBehave.dll" /implib:"$(OUTDIR)\AtlBehave.lib" /pdbtype:sept 
DEF_FILE= \
	".\AtlBehave.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlBehave.obj" \
	"$(INTDIR)\Behavior.obj" \
	"$(INTDIR)\EventSink.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBehave.res"

"$(OUTDIR)\AtlBehave.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\AtlBehave.dll
InputPath=.\DebugU\AtlBehave.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\AtlBehave_i.c" ".\AtlBehave.tlb" ".\AtlBehave.h" "$(OUTDIR)\AtlBehave.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AtlBehave.obj"
	-@erase "$(INTDIR)\AtlBehave.pch"
	-@erase "$(INTDIR)\AtlBehave.res"
	-@erase "$(INTDIR)\Behavior.obj"
	-@erase "$(INTDIR)\EventSink.obj"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlBehave.dll"
	-@erase "$(OUTDIR)\AtlBehave.exp"
	-@erase "$(OUTDIR)\AtlBehave.lib"
	-@erase ".\AtlBehave.h"
	-@erase ".\AtlBehave.tlb"
	-@erase ".\AtlBehave_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlBehave.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBehave.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBehave.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\AtlBehave.pdb" /machine:I386 /def:".\AtlBehave.def" /out:"$(OUTDIR)\AtlBehave.dll" /implib:"$(OUTDIR)\AtlBehave.lib" 
DEF_FILE= \
	".\AtlBehave.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlBehave.obj" \
	"$(INTDIR)\Behavior.obj" \
	"$(INTDIR)\EventSink.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBehave.res"

"$(OUTDIR)\AtlBehave.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\AtlBehave.dll
InputPath=.\ReleaseMinSize\AtlBehave.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\AtlBehave_i.c" ".\AtlBehave.tlb" ".\AtlBehave.h" "$(OUTDIR)\AtlBehave.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AtlBehave.obj"
	-@erase "$(INTDIR)\AtlBehave.pch"
	-@erase "$(INTDIR)\AtlBehave.res"
	-@erase "$(INTDIR)\Behavior.obj"
	-@erase "$(INTDIR)\EventSink.obj"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlBehave.dll"
	-@erase "$(OUTDIR)\AtlBehave.exp"
	-@erase "$(OUTDIR)\AtlBehave.lib"
	-@erase ".\AtlBehave.h"
	-@erase ".\AtlBehave.tlb"
	-@erase ".\AtlBehave_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\AtlBehave.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBehave.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBehave.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\AtlBehave.pdb" /machine:I386 /def:".\AtlBehave.def" /out:"$(OUTDIR)\AtlBehave.dll" /implib:"$(OUTDIR)\AtlBehave.lib"
DEF_FILE= \
	".\AtlBehave.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlBehave.obj" \
	"$(INTDIR)\Behavior.obj" \
	"$(INTDIR)\EventSink.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBehave.res"

"$(OUTDIR)\AtlBehave.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\AtlBehave.dll
InputPath=.\ReleaseMinDependency\AtlBehave.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\AtlBehave_i.c" ".\AtlBehave.tlb" ".\AtlBehave.h" "$(OUTDIR)\AtlBehave.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AtlBehave.obj"
	-@erase "$(INTDIR)\AtlBehave.pch"
	-@erase "$(INTDIR)\AtlBehave.res"
	-@erase "$(INTDIR)\Behavior.obj"
	-@erase "$(INTDIR)\EventSink.obj"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlBehave.dll"
	-@erase "$(OUTDIR)\AtlBehave.exp"
	-@erase "$(OUTDIR)\AtlBehave.lib"
	-@erase ".\AtlBehave.h"
	-@erase ".\AtlBehave.tlb"
	-@erase ".\AtlBehave_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlBehave.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBehave.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBehave.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\AtlBehave.pdb" /machine:I386 /def:".\AtlBehave.def" /out:"$(OUTDIR)\AtlBehave.dll" /implib:"$(OUTDIR)\AtlBehave.lib" 
DEF_FILE= \
	".\AtlBehave.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlBehave.obj" \
	"$(INTDIR)\Behavior.obj" \
	"$(INTDIR)\EventSink.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBehave.res"

"$(OUTDIR)\AtlBehave.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\AtlBehave.dll
InputPath=.\ReleaseUMinSize\AtlBehave.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\AtlBehave_i.c" ".\AtlBehave.tlb" ".\AtlBehave.h" "$(OUTDIR)\AtlBehave.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AtlBehave.obj"
	-@erase "$(INTDIR)\AtlBehave.pch"
	-@erase "$(INTDIR)\AtlBehave.res"
	-@erase "$(INTDIR)\Behavior.obj"
	-@erase "$(INTDIR)\EventSink.obj"
	-@erase "$(INTDIR)\Factory.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlBehave.dll"
	-@erase "$(OUTDIR)\AtlBehave.exp"
	-@erase "$(OUTDIR)\AtlBehave.lib"
	-@erase ".\AtlBehave.h"
	-@erase ".\AtlBehave.tlb"
	-@erase ".\AtlBehave_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlBehave.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBehave.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBehave.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\AtlBehave.pdb" /machine:I386 /def:".\AtlBehave.def" /out:"$(OUTDIR)\AtlBehave.dll" /implib:"$(OUTDIR)\AtlBehave.lib" 
DEF_FILE= \
	".\AtlBehave.def"
LINK32_OBJS= \
	"$(INTDIR)\AtlBehave.obj" \
	"$(INTDIR)\Behavior.obj" \
	"$(INTDIR)\EventSink.obj" \
	"$(INTDIR)\Factory.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBehave.res"

"$(OUTDIR)\AtlBehave.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\AtlBehave.dll
InputPath=.\ReleaseUMinDependency\AtlBehave.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("AtlBehave.dep")
!INCLUDE "AtlBehave.dep"
!ELSE 
!MESSAGE Warning: cannot find "AtlBehave.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AtlBehave - Win32 Debug" || "$(CFG)" == "AtlBehave - Win32 Unicode Debug" || "$(CFG)" == "AtlBehave - Win32 Release MinSize" || "$(CFG)" == "AtlBehave - Win32 Release MinDependency" || "$(CFG)" == "AtlBehave - Win32 Unicode Release MinSize" || "$(CFG)" == "AtlBehave - Win32 Unicode Release MinDependency"
SOURCE=.\AtlBehave.cpp

"$(INTDIR)\AtlBehave.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlBehave.pch" ".\AtlBehave.h" ".\AtlBehave_i.c"


SOURCE=.\AtlBehave.idl

!IF  "$(CFG)" == "AtlBehave - Win32 Debug"

InputPath=.\AtlBehave.idl

".\AtlBehave.tlb"	".\AtlBehave.h"	".\AtlBehave_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBehave.h" /iid "AtlBehave_i.c" "AtlBehave.idl"
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Debug"

InputPath=.\AtlBehave.idl

".\AtlBehave.tlb"	".\AtlBehave.h"	".\AtlBehave_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBehave.h" /iid "AtlBehave_i.c" "AtlBehave.idl"
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Release MinSize"

InputPath=.\AtlBehave.idl

".\AtlBehave.tlb"	".\AtlBehave.h"	".\AtlBehave_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBehave.h" /iid "AtlBehave_i.c" "AtlBehave.idl"
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Release MinDependency"

InputPath=.\AtlBehave.idl

".\AtlBehave.tlb"	".\AtlBehave.h"	".\AtlBehave_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBehave.h" /iid "AtlBehave_i.c" "AtlBehave.idl"
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Release MinSize"

InputPath=.\AtlBehave.idl

".\AtlBehave.tlb"	".\AtlBehave.h"	".\AtlBehave_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBehave.h" /iid "AtlBehave_i.c" "AtlBehave.idl"
<< 
	

!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Release MinDependency"

InputPath=.\AtlBehave.idl

".\AtlBehave.tlb"	".\AtlBehave.h"	".\AtlBehave_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBehave.h" /iid "AtlBehave_i.c" "AtlBehave.idl"
<< 
	

!ENDIF 

SOURCE=.\AtlBehave.rc

"$(INTDIR)\AtlBehave.res" : $(SOURCE) "$(INTDIR)" ".\AtlBehave.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Behavior.cpp

"$(INTDIR)\Behavior.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlBehave.pch" ".\AtlBehave.h"


SOURCE=.\EventSink.cpp

"$(INTDIR)\EventSink.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlBehave.pch" ".\AtlBehave.h"


SOURCE=.\Factory.cpp

"$(INTDIR)\Factory.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlBehave.pch" ".\AtlBehave.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "AtlBehave - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\AtlBehave.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBehave.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\AtlBehave.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBehave.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlBehave.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBehave.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\AtlBehave.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBehave.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlBehave.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBehave.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlBehave - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\AtlBehave.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBehave.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

