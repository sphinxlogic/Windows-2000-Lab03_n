# Microsoft Developer Studio Generated NMAKE File, Based on MtsAudit.dsp
!IF "$(CFG)" == ""
CFG=MTSAUDIT - WIN32 UNICODE DEBUG
!MESSAGE No configuration specified. Defaulting to MTSAUDIT - WIN32 UNICODE\
 DEBUG.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF  

!IF "$(CFG)" != "MtsAudit - Win32 Unicode Debug" && "$(CFG)" !=\
 "MtsAudit - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MtsAudit.mak" CFG="MTSAUDIT - WIN32 UNICODE DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MtsAudit - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MtsAudit - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MtsAudit - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MtsAudit.dll" "$(OUTDIR)\MtsAudit.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MtsAudit.dll" "$(OUTDIR)\MtsAudit.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\events.obj"
	-@erase "$(INTDIR)\events.sbr"
	-@erase "$(INTDIR)\MtsAudit.obj"
	-@erase "$(INTDIR)\MtsAudit.pch"
	-@erase "$(INTDIR)\MtsAudit.res"
	-@erase "$(INTDIR)\MtsAudit.sbr"
	-@erase "$(INTDIR)\MtsSqlAudit.obj"
	-@erase "$(INTDIR)\MtsSqlAudit.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MtsAudit.bsc"
	-@erase "$(OUTDIR)\MtsAudit.dll"
	-@erase "$(OUTDIR)\MtsAudit.exp"
	-@erase "$(OUTDIR)\MtsAudit.ilk"
	-@erase "$(OUTDIR)\MtsAudit.lib"
	-@erase "$(OUTDIR)\MtsAudit.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\MtsAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\DebugU/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsAudit.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsAudit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\events.sbr" \
	"$(INTDIR)\MtsAudit.sbr" \
	"$(INTDIR)\MtsSqlAudit.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\MtsAudit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\MtsAudit.pdb" /debug /machine:$(mach_type) /def:".\MtsAudit.def"\
 /out:"$(OUTDIR)\MtsAudit.dll" /implib:"$(OUTDIR)\MtsAudit.lib" /pdbtype:sept 
DEF_FILE= \
	".\MtsAudit.def"
LINK32_OBJS= \
	"$(INTDIR)\events.obj" \
	"$(INTDIR)\MtsAudit.obj" \
	"$(INTDIR)\MtsAudit.res" \
	"$(INTDIR)\MtsSqlAudit.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MtsAudit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\MtsAudit.dll
InputPath=.\DebugU\MtsAudit.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "MtsAudit - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MtsAudit.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MtsAudit.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\events.obj"
	-@erase "$(INTDIR)\MtsAudit.obj"
	-@erase "$(INTDIR)\MtsAudit.pch"
	-@erase "$(INTDIR)\MtsAudit.res"
	-@erase "$(INTDIR)\MtsSqlAudit.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MtsAudit.dll"
	-@erase "$(OUTDIR)\MtsAudit.exp"
	-@erase "$(OUTDIR)\MtsAudit.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\MtsAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\ReleaseUMinDependency/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsAudit.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsAudit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\MtsAudit.pdb" /machine:$(mach_type) /def:".\MtsAudit.def"\
 /out:"$(OUTDIR)\MtsAudit.dll" /implib:"$(OUTDIR)\MtsAudit.lib" 
DEF_FILE= \
	".\MtsAudit.def"
LINK32_OBJS= \
	"$(INTDIR)\events.obj" \
	"$(INTDIR)\MtsAudit.obj" \
	"$(INTDIR)\MtsAudit.res" \
	"$(INTDIR)\MtsSqlAudit.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MtsAudit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\MtsAudit.dll
InputPath=.\ReleaseUMinDependency\MtsAudit.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "MtsAudit - Win32 Unicode Debug" || "$(CFG)" ==\
 "MtsAudit - Win32 Unicode Release MinDependency"
SOURCE=.\events.cpp
DEP_CPP_EVENT=\
	".\MtsSqlAudit.h"\
	".\StdAfx.h"\
	
NODEP_CPP_EVENT=\
	".\MtsAudit.h"\
	

!IF  "$(CFG)" == "MtsAudit - Win32 Unicode Debug"


"$(INTDIR)\events.obj"	"$(INTDIR)\events.sbr" : $(SOURCE) $(DEP_CPP_EVENT)\
 "$(INTDIR)" "$(INTDIR)\MtsAudit.pch"


!ELSEIF  "$(CFG)" == "MtsAudit - Win32 Unicode Release MinDependency"


"$(INTDIR)\events.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "$(INTDIR)\MtsAudit.pch"


!ENDIF 

SOURCE=.\MtsAudit.cpp
DEP_CPP_MTSAU=\
	".\MtsSqlAudit.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MTSAU=\
	".\MtsAudit.h"\
	".\MtsAudit_i.c"\
	

!IF  "$(CFG)" == "MtsAudit - Win32 Unicode Debug"


"$(INTDIR)\MtsAudit.obj"	"$(INTDIR)\MtsAudit.sbr" : $(SOURCE) $(DEP_CPP_MTSAU)\
 "$(INTDIR)" "$(INTDIR)\MtsAudit.pch"


!ELSEIF  "$(CFG)" == "MtsAudit - Win32 Unicode Release MinDependency"


"$(INTDIR)\MtsAudit.obj" : $(SOURCE) $(DEP_CPP_MTSAU) "$(INTDIR)"\
 "$(INTDIR)\MtsAudit.pch"


!ENDIF 

SOURCE=.\MtsSqlAudit.cpp
DEP_CPP_MTSSQ=\
	".\MtsSqlAudit.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MTSSQ=\
	".\MtsAudit.h"\
	

!IF  "$(CFG)" == "MtsAudit - Win32 Unicode Debug"


"$(INTDIR)\MtsSqlAudit.obj"	"$(INTDIR)\MtsSqlAudit.sbr" : $(SOURCE)\
 $(DEP_CPP_MTSSQ) "$(INTDIR)" "$(INTDIR)\MtsAudit.pch"


!ELSEIF  "$(CFG)" == "MtsAudit - Win32 Unicode Release MinDependency"


"$(INTDIR)\MtsSqlAudit.obj" : $(SOURCE) $(DEP_CPP_MTSSQ) "$(INTDIR)"\
 "$(INTDIR)\MtsAudit.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MtsAudit - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\MtsAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MtsAudit.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MtsAudit - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D\
 "_ATL_MIN_CRT" /Fp"$(INTDIR)\MtsAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MtsAudit.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MtsAudit.rc
DEP_RSC_MTSAUD=\
	".\MtsSqlAudit.rgs"\
	
NODEP_RSC_MTSAUD=\
	".\inc\MtsAudit.tlb"\
	

"$(INTDIR)\MtsAudit.res" : $(SOURCE) $(DEP_RSC_MTSAUD) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

