# Microsoft Developer Studio Generated NMAKE File, Based on ComSpyAudit.dsp
!IF "$(CFG)" == ""
CFG=ComSpyAudit - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to ComSpyAudit - Win32 Unicode Debug.
!ENDIF 

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF

!IF "$(CFG)" != "ComSpyAudit - Win32 Unicode Debug" && "$(CFG)" != "ComSpyAudit - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSpyAudit.mak" CFG="ComSpyAudit - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpyAudit - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComSpyAudit - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ComSpyAudit.dll" "$(OUTDIR)\ComSpyAudit.bsc" ".\DebugU\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ComSpyAudit.dll" "$(OUTDIR)\ComSpyAudit.bsc" ".\DebugU\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\events.obj"
	-@erase "$(INTDIR)\events.sbr"
	-@erase "$(INTDIR)\ComSpyAudit.obj"
	-@erase "$(INTDIR)\ComSpyAudit.pch"
	-@erase "$(INTDIR)\ComSpyAudit.res"
	-@erase "$(INTDIR)\ComSpyAudit.sbr"
	-@erase "$(INTDIR)\ComSpySqlAudit.obj"
	-@erase "$(INTDIR)\ComSpySqlAudit.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ComSpyAudit.bsc"
	-@erase "$(OUTDIR)\ComSpyAudit.dll"
	-@erase "$(OUTDIR)\ComSpyAudit.exp"
	-@erase "$(OUTDIR)\ComSpyAudit.ilk"
	-@erase "$(OUTDIR)\ComSpyAudit.lib"
	-@erase "$(OUTDIR)\ComSpyAudit.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyAudit.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyAudit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\events.sbr" \
	"$(INTDIR)\ComSpyAudit.sbr" \
	"$(INTDIR)\ComSpySqlAudit.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ComSpyAudit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ComSpyAudit.pdb" /debug /machine:$(mach_type) /def:".\ComSpyAudit.def" /out:"$(OUTDIR)\ComSpyAudit.dll" /implib:"$(OUTDIR)\ComSpyAudit.lib" /pdbtype:sept 
DEF_FILE= \
	".\ComSpyAudit.def"
LINK32_OBJS= \
	"$(INTDIR)\events.obj" \
	"$(INTDIR)\ComSpyAudit.obj" \
	"$(INTDIR)\ComSpySqlAudit.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpyAudit.res"

"$(OUTDIR)\ComSpyAudit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ComSpyAudit.dll
InputPath=.\DebugU\ComSpyAudit.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ComSpyAudit.dll" ".\Release\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ComSpyAudit.dll" ".\Release\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\events.obj"
	-@erase "$(INTDIR)\ComSpyAudit.obj"
	-@erase "$(INTDIR)\ComSpyAudit.pch"
	-@erase "$(INTDIR)\ComSpyAudit.res"
	-@erase "$(INTDIR)\ComSpySqlAudit.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ComSpyAudit.dll"
	-@erase "$(OUTDIR)\ComSpyAudit.exp"
	-@erase "$(OUTDIR)\ComSpyAudit.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyAudit.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyAudit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ComSpyAudit.pdb" /machine:$(mach_type) /def:".\ComSpyAudit.def" /out:"$(OUTDIR)\ComSpyAudit.dll" /implib:"$(OUTDIR)\ComSpyAudit.lib" 
DEF_FILE= \
	".\ComSpyAudit.def"
LINK32_OBJS= \
	"$(INTDIR)\events.obj" \
	"$(INTDIR)\ComSpyAudit.obj" \
	"$(INTDIR)\ComSpySqlAudit.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpyAudit.res"

"$(OUTDIR)\ComSpyAudit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\ComSpyAudit.dll
InputPath=.\Release\ComSpyAudit.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ComSpyAudit.dep")
!INCLUDE "ComSpyAudit.dep"
!ELSE 
!MESSAGE Warning: cannot find "ComSpyAudit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug" || "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"
SOURCE=.\events.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"


"$(INTDIR)\events.obj"	"$(INTDIR)\events.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"


"$(INTDIR)\events.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\ComSpyAudit.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"


"$(INTDIR)\ComSpyAudit.obj"	"$(INTDIR)\ComSpyAudit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"


"$(INTDIR)\ComSpyAudit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\ComSpySqlAudit.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"


"$(INTDIR)\ComSpySqlAudit.obj"	"$(INTDIR)\ComSpySqlAudit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"


"$(INTDIR)\ComSpySqlAudit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ComSpyAudit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSpyAudit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ComSpyAudit.rc

"$(INTDIR)\ComSpyAudit.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"

!ENDIF 


!ENDIF 

