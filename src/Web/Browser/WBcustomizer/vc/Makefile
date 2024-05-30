# Microsoft Developer Studio Generated NMAKE File, Based on WBCustomizer.dsp
!IF "$(CFG)" == ""
CFG=WBCustomizer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WBCustomizer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WBCustomizer - Win32 Debug" && "$(CFG)" != "WBCustomizer - Win32 Unicode Debug" && "$(CFG)" != "WBCustomizer - Win32 Release MinSize" && "$(CFG)" != "WBCustomizer - Win32 Release MinDependency" && "$(CFG)" != "WBCustomizer - Win32 Unicode Release MinSize" && "$(CFG)" != "WBCustomizer - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WBCustomizer.mak" CFG="WBCustomizer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WBCustomizer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WBCustomizer - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WBCustomizer - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WBCustomizer - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WBCustomizer - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WBCustomizer - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "WBCustomizer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WBCustomizer.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WBCustomizer.obj"
	-@erase "$(INTDIR)\WBCustomizer.pch"
	-@erase "$(INTDIR)\WBCustomizer.res"
	-@erase "$(INTDIR)\WBCustomizerObj.obj"
	-@erase "$(OUTDIR)\WBCustomizer.dll"
	-@erase "$(OUTDIR)\WBCustomizer.exp"
	-@erase "$(OUTDIR)\WBCustomizer.ilk"
	-@erase "$(OUTDIR)\WBCustomizer.lib"
	-@erase "$(OUTDIR)\WBCustomizer.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\WBCustomizer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WBCustomizer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WBCustomizer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\WBCustomizer.pdb" /debug /machine:I386 /def:".\WBCustomizer.def" /out:"$(OUTDIR)\WBCustomizer.dll" /implib:"$(OUTDIR)\WBCustomizer.lib" /pdbtype:sept 
DEF_FILE= \
	".\WBCustomizer.def"
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WBCustomizer.obj" \
	"$(INTDIR)\WBCustomizerObj.obj" \
	"$(INTDIR)\WBCustomizer.res"

"$(OUTDIR)\WBCustomizer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\WBCustomizer.dll
InputPath=.\Debug\WBCustomizer.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\WBCustomizer_i.c" ".\WBCustomizer.tlb" ".\WBCustomizer.h" "$(OUTDIR)\WBCustomizer.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WBCustomizer.obj"
	-@erase "$(INTDIR)\WBCustomizer.pch"
	-@erase "$(INTDIR)\WBCustomizer.res"
	-@erase "$(INTDIR)\WBCustomizerObj.obj"
	-@erase "$(OUTDIR)\WBCustomizer.dll"
	-@erase "$(OUTDIR)\WBCustomizer.exp"
	-@erase "$(OUTDIR)\WBCustomizer.ilk"
	-@erase "$(OUTDIR)\WBCustomizer.lib"
	-@erase "$(OUTDIR)\WBCustomizer.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\WBCustomizer.h"
	-@erase ".\WBCustomizer.tlb"
	-@erase ".\WBCustomizer_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\WBCustomizer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WBCustomizer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WBCustomizer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\WBCustomizer.pdb" /debug /machine:I386 /def:".\WBCustomizer.def" /out:"$(OUTDIR)\WBCustomizer.dll" /implib:"$(OUTDIR)\WBCustomizer.lib" /pdbtype:sept 
DEF_FILE= \
	".\WBCustomizer.def"
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WBCustomizer.obj" \
	"$(INTDIR)\WBCustomizerObj.obj" \
	"$(INTDIR)\WBCustomizer.res"

"$(OUTDIR)\WBCustomizer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\WBCustomizer.dll
InputPath=.\DebugU\WBCustomizer.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\WBCustomizer_i.c" ".\WBCustomizer.tlb" ".\WBCustomizer.h" "$(OUTDIR)\WBCustomizer.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WBCustomizer.obj"
	-@erase "$(INTDIR)\WBCustomizer.pch"
	-@erase "$(INTDIR)\WBCustomizer.res"
	-@erase "$(INTDIR)\WBCustomizerObj.obj"
	-@erase "$(OUTDIR)\WBCustomizer.dll"
	-@erase "$(OUTDIR)\WBCustomizer.exp"
	-@erase "$(OUTDIR)\WBCustomizer.lib"
	-@erase ".\ReleaseMinSize\regsvr32.trg"
	-@erase ".\WBCustomizer.h"
	-@erase ".\WBCustomizer.tlb"
	-@erase ".\WBCustomizer_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WBCustomizer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WBCustomizer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\WBCustomizer.pdb" /machine:I386 /def:".\WBCustomizer.def" /out:"$(OUTDIR)\WBCustomizer.dll" /implib:"$(OUTDIR)\WBCustomizer.lib" 
DEF_FILE= \
	".\WBCustomizer.def"
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WBCustomizer.obj" \
	"$(INTDIR)\WBCustomizerObj.obj" \
	"$(INTDIR)\WBCustomizer.res"

"$(OUTDIR)\WBCustomizer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\WBCustomizer.dll
InputPath=.\ReleaseMinSize\WBCustomizer.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\WBCustomizer_i.c" ".\WBCustomizer.tlb" ".\WBCustomizer.h" "$(OUTDIR)\WBCustomizer.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WBCustomizer.obj"
	-@erase "$(INTDIR)\WBCustomizer.pch"
	-@erase "$(INTDIR)\WBCustomizer.res"
	-@erase "$(INTDIR)\WBCustomizerObj.obj"
	-@erase "$(OUTDIR)\WBCustomizer.dll"
	-@erase "$(OUTDIR)\WBCustomizer.exp"
	-@erase "$(OUTDIR)\WBCustomizer.lib"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"
	-@erase ".\WBCustomizer.h"
	-@erase ".\WBCustomizer.tlb"
	-@erase ".\WBCustomizer_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WBCustomizer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WBCustomizer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\WBCustomizer.pdb" /machine:I386 /def:".\WBCustomizer.def" /out:"$(OUTDIR)\WBCustomizer.dll" /implib:"$(OUTDIR)\WBCustomizer.lib" 
DEF_FILE= \
	".\WBCustomizer.def"
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WBCustomizer.obj" \
	"$(INTDIR)\WBCustomizerObj.obj" \
	"$(INTDIR)\WBCustomizer.res"

"$(OUTDIR)\WBCustomizer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\WBCustomizer.dll
InputPath=.\ReleaseMinDependency\WBCustomizer.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\WBCustomizer_i.c" ".\WBCustomizer.tlb" ".\WBCustomizer.h" "$(OUTDIR)\WBCustomizer.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WBCustomizer.obj"
	-@erase "$(INTDIR)\WBCustomizer.pch"
	-@erase "$(INTDIR)\WBCustomizer.res"
	-@erase "$(INTDIR)\WBCustomizerObj.obj"
	-@erase "$(OUTDIR)\WBCustomizer.dll"
	-@erase "$(OUTDIR)\WBCustomizer.exp"
	-@erase "$(OUTDIR)\WBCustomizer.lib"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"
	-@erase ".\WBCustomizer.h"
	-@erase ".\WBCustomizer.tlb"
	-@erase ".\WBCustomizer_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WBCustomizer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WBCustomizer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\WBCustomizer.pdb" /machine:I386 /def:".\WBCustomizer.def" /out:"$(OUTDIR)\WBCustomizer.dll" /implib:"$(OUTDIR)\WBCustomizer.lib" 
DEF_FILE= \
	".\WBCustomizer.def"
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WBCustomizer.obj" \
	"$(INTDIR)\WBCustomizerObj.obj" \
	"$(INTDIR)\WBCustomizer.res"

"$(OUTDIR)\WBCustomizer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\WBCustomizer.dll
InputPath=.\ReleaseUMinSize\WBCustomizer.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\WBCustomizer_i.c" ".\WBCustomizer.tlb" ".\WBCustomizer.h" "$(OUTDIR)\WBCustomizer.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\IE4Events.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WBCustomizer.obj"
	-@erase "$(INTDIR)\WBCustomizer.pch"
	-@erase "$(INTDIR)\WBCustomizer.res"
	-@erase "$(INTDIR)\WBCustomizerObj.obj"
	-@erase "$(OUTDIR)\WBCustomizer.dll"
	-@erase "$(OUTDIR)\WBCustomizer.exp"
	-@erase "$(OUTDIR)\WBCustomizer.lib"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"
	-@erase ".\WBCustomizer.h"
	-@erase ".\WBCustomizer.tlb"
	-@erase ".\WBCustomizer_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WBCustomizer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WBCustomizer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\WBCustomizer.pdb" /machine:I386 /def:".\WBCustomizer.def" /out:"$(OUTDIR)\WBCustomizer.dll" /implib:"$(OUTDIR)\WBCustomizer.lib" 
DEF_FILE= \
	".\WBCustomizer.def"
LINK32_OBJS= \
	"$(INTDIR)\IE4Events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WBCustomizer.obj" \
	"$(INTDIR)\WBCustomizerObj.obj" \
	"$(INTDIR)\WBCustomizer.res"

"$(OUTDIR)\WBCustomizer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\WBCustomizer.dll
InputPath=.\ReleaseUMinDependency\WBCustomizer.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WBCustomizer.dep")
!INCLUDE "WBCustomizer.dep"
!ELSE 
!MESSAGE Warning: cannot find "WBCustomizer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WBCustomizer - Win32 Debug" || "$(CFG)" == "WBCustomizer - Win32 Unicode Debug" || "$(CFG)" == "WBCustomizer - Win32 Release MinSize" || "$(CFG)" == "WBCustomizer - Win32 Release MinDependency" || "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinSize" || "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinDependency"
SOURCE=.\IE4Events.cpp

"$(INTDIR)\IE4Events.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WBCustomizer.pch" ".\WBCustomizer.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "WBCustomizer - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\WBCustomizer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WBCustomizer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\WBCustomizer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WBCustomizer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WBCustomizer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WBCustomizer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WBCustomizer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\WBCustomizer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WBCustomizer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WBCustomizer.cpp

"$(INTDIR)\WBCustomizer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WBCustomizer.pch" ".\WBCustomizer.h" ".\WBCustomizer_i.c"


SOURCE=.\WBCustomizer.idl

!IF  "$(CFG)" == "WBCustomizer - Win32 Debug"

InputPath=.\WBCustomizer.idl

".\WBCustomizer.tlb"	".\WBCustomizer.h"	".\WBCustomizer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "WBCustomizer.h" /iid "WBCustomizer_i.c" "WBCustomizer.idl"
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Debug"

InputPath=.\WBCustomizer.idl

".\WBCustomizer.tlb"	".\WBCustomizer.h"	".\WBCustomizer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "WBCustomizer.h" /iid "WBCustomizer_i.c" "WBCustomizer.idl"
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Release MinSize"

InputPath=.\WBCustomizer.idl

".\WBCustomizer.tlb"	".\WBCustomizer.h"	".\WBCustomizer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "WBCustomizer.h" /iid "WBCustomizer_i.c" "WBCustomizer.idl"
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Release MinDependency"

InputPath=.\WBCustomizer.idl

".\WBCustomizer.tlb"	".\WBCustomizer.h"	".\WBCustomizer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "WBCustomizer.h" /iid "WBCustomizer_i.c" "WBCustomizer.idl"
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinSize"

InputPath=.\WBCustomizer.idl

".\WBCustomizer.tlb"	".\WBCustomizer.h"	".\WBCustomizer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "WBCustomizer.h" /iid "WBCustomizer_i.c" "WBCustomizer.idl"
<< 
	

!ELSEIF  "$(CFG)" == "WBCustomizer - Win32 Unicode Release MinDependency"

InputPath=.\WBCustomizer.idl

".\WBCustomizer.tlb"	".\WBCustomizer.h"	".\WBCustomizer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "WBCustomizer.h" /iid "WBCustomizer_i.c" "WBCustomizer.idl"
<< 
	

!ENDIF 

SOURCE=.\WBCustomizer.rc

"$(INTDIR)\WBCustomizer.res" : $(SOURCE) "$(INTDIR)" ".\WBCustomizer.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\WBCustomizerObj.cpp

"$(INTDIR)\WBCustomizerObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WBCustomizer.pch" ".\WBCustomizer.h"



!ENDIF 

