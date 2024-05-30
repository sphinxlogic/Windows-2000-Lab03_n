# Microsoft Developer Studio Generated NMAKE File, Based on Percy.dsp
!IF "$(CFG)" == ""
CFG=Percy - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Percy - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Percy - Win32 Debug" && "$(CFG)" !=\
 "Percy - Win32 Unicode Debug" && "$(CFG)" != "Percy - Win32 Release MinSize" &&\
 "$(CFG)" != "Percy - Win32 Release MinDependency" && "$(CFG)" !=\
 "Percy - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "Percy - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Percy.mak" CFG="Percy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Percy - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Percy - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Percy - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Percy - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Percy - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Percy - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Percy - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Percy.dll" "$(OUTDIR)\Percy.bsc" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Percy.dll" "$(OUTDIR)\Percy.bsc" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Percy.obj"
	-@erase "$(INTDIR)\Percy.pch"
	-@erase "$(INTDIR)\Percy.res"
	-@erase "$(INTDIR)\Percy.sbr"
	-@erase "$(INTDIR)\percyctl.obj"
	-@erase "$(INTDIR)\percyctl.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Percy.bsc"
	-@erase "$(OUTDIR)\Percy.dll"
	-@erase "$(OUTDIR)\Percy.exp"
	-@erase "$(OUTDIR)\Percy.ilk"
	-@erase "$(OUTDIR)\Percy.lib"
	-@erase "$(OUTDIR)\Percy.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Percy.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Percy.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Percy.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Percy.sbr" \
	"$(INTDIR)\percyctl.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Percy.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Percy.pdb" /debug /machine:I386 /def:".\Percy.def"\
 /out:"$(OUTDIR)\Percy.dll" /implib:"$(OUTDIR)\Percy.lib" /pdbtype:sept 
DEF_FILE= \
	".\Percy.def"
LINK32_OBJS= \
	"$(INTDIR)\Percy.obj" \
	"$(INTDIR)\Percy.res" \
	"$(INTDIR)\percyctl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Percy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Percy.dll
InputPath=.\Debug\Percy.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Percy.obj"
	-@erase "$(INTDIR)\Percy.pch"
	-@erase "$(INTDIR)\Percy.res"
	-@erase "$(INTDIR)\percyctl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Percy.dll"
	-@erase "$(OUTDIR)\Percy.exp"
	-@erase "$(OUTDIR)\Percy.ilk"
	-@erase "$(OUTDIR)\Percy.lib"
	-@erase "$(OUTDIR)\Percy.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Percy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Percy.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Percy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Percy.pdb" /debug /machine:I386 /def:".\Percy.def"\
 /out:"$(OUTDIR)\Percy.dll" /implib:"$(OUTDIR)\Percy.lib" /pdbtype:sept 
DEF_FILE= \
	".\Percy.def"
LINK32_OBJS= \
	"$(INTDIR)\Percy.obj" \
	"$(INTDIR)\Percy.res" \
	"$(INTDIR)\percyctl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Percy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Percy.dll
InputPath=.\DebugU\Percy.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Percy.obj"
	-@erase "$(INTDIR)\Percy.pch"
	-@erase "$(INTDIR)\Percy.res"
	-@erase "$(INTDIR)\percyctl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Percy.dll"
	-@erase "$(OUTDIR)\Percy.exp"
	-@erase "$(OUTDIR)\Percy.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Percy.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Percy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Percy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Percy.pdb" /machine:I386 /def:".\Percy.def"\
 /out:"$(OUTDIR)\Percy.dll" /implib:"$(OUTDIR)\Percy.lib" 
DEF_FILE= \
	".\Percy.def"
LINK32_OBJS= \
	"$(INTDIR)\Percy.obj" \
	"$(INTDIR)\Percy.res" \
	"$(INTDIR)\percyctl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Percy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Percy.dll
InputPath=.\ReleaseMinSize\Percy.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Percy.obj"
	-@erase "$(INTDIR)\Percy.pch"
	-@erase "$(INTDIR)\Percy.res"
	-@erase "$(INTDIR)\percyctl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Percy.dll"
	-@erase "$(OUTDIR)\Percy.exp"
	-@erase "$(OUTDIR)\Percy.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Percy.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Percy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Percy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Percy.pdb" /machine:I386 /def:".\Percy.def"\
 /out:"$(OUTDIR)\Percy.dll" /implib:"$(OUTDIR)\Percy.lib" 
DEF_FILE= \
	".\Percy.def"
LINK32_OBJS= \
	"$(INTDIR)\Percy.obj" \
	"$(INTDIR)\Percy.res" \
	"$(INTDIR)\percyctl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Percy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Percy.dll
InputPath=.\ReleaseMinDependency\Percy.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Percy.obj"
	-@erase "$(INTDIR)\Percy.pch"
	-@erase "$(INTDIR)\Percy.res"
	-@erase "$(INTDIR)\percyctl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Percy.dll"
	-@erase "$(OUTDIR)\Percy.exp"
	-@erase "$(OUTDIR)\Percy.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Percy.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseUMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Percy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Percy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Percy.pdb" /machine:I386 /def:".\Percy.def"\
 /out:"$(OUTDIR)\Percy.dll" /implib:"$(OUTDIR)\Percy.lib" 
DEF_FILE= \
	".\Percy.def"
LINK32_OBJS= \
	"$(INTDIR)\Percy.obj" \
	"$(INTDIR)\Percy.res" \
	"$(INTDIR)\percyctl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Percy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Percy.dll
InputPath=.\ReleaseUMinSize\Percy.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Percy.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Percy.obj"
	-@erase "$(INTDIR)\Percy.pch"
	-@erase "$(INTDIR)\Percy.res"
	-@erase "$(INTDIR)\percyctl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Percy.dll"
	-@erase "$(OUTDIR)\Percy.exp"
	-@erase "$(OUTDIR)\Percy.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\Percy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 
CPP_OBJS=.\ReleaseUMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Percy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Percy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Percy.pdb" /machine:I386 /def:".\Percy.def"\
 /out:"$(OUTDIR)\Percy.dll" /implib:"$(OUTDIR)\Percy.lib" 
DEF_FILE= \
	".\Percy.def"
LINK32_OBJS= \
	"$(INTDIR)\Percy.obj" \
	"$(INTDIR)\Percy.res" \
	"$(INTDIR)\percyctl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Percy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Percy.dll
InputPath=.\ReleaseUMinDependency\Percy.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 

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


!IF "$(CFG)" == "Percy - Win32 Debug" || "$(CFG)" ==\
 "Percy - Win32 Unicode Debug" || "$(CFG)" == "Percy - Win32 Release MinSize" ||\
 "$(CFG)" == "Percy - Win32 Release MinDependency" || "$(CFG)" ==\
 "Percy - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "Percy - Win32 Unicode Release MinDependency"
SOURCE=.\Percy.cpp
DEP_CPP_PERCY=\
	".\Percy.h"\
	".\percyctl.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PERCY=\
	".\Percy_i.c"\
	".\perhist.h"\
	

!IF  "$(CFG)" == "Percy - Win32 Debug"


"$(INTDIR)\Percy.obj"	"$(INTDIR)\Percy.sbr" : $(SOURCE) $(DEP_CPP_PERCY)\
 "$(INTDIR)" "$(INTDIR)\Percy.pch" ".\Percy_i.c" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Debug"


"$(INTDIR)\Percy.obj" : $(SOURCE) $(DEP_CPP_PERCY) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy_i.c" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinSize"


"$(INTDIR)\Percy.obj" : $(SOURCE) $(DEP_CPP_PERCY) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy_i.c" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinDependency"


"$(INTDIR)\Percy.obj" : $(SOURCE) $(DEP_CPP_PERCY) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy_i.c" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinSize"


"$(INTDIR)\Percy.obj" : $(SOURCE) $(DEP_CPP_PERCY) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy_i.c" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinDependency"


"$(INTDIR)\Percy.obj" : $(SOURCE) $(DEP_CPP_PERCY) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy_i.c" ".\Percy.h"


!ENDIF 

SOURCE=.\Percy.idl

!IF  "$(CFG)" == "Percy - Win32 Debug"

InputPath=.\Percy.idl

".\Percy.tlb"	".\Percy.h"	".\Percy_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Percy.h" /iid "Percy_i.c" "Percy.idl"

!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Debug"

InputPath=.\Percy.idl

".\Percy.tlb"	".\Percy.h"	".\Percy_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Percy.h" /iid "Percy_i.c" "Percy.idl"

!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinSize"

InputPath=.\Percy.idl

".\Percy.tlb"	".\Percy.h"	".\Percy_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Percy.h" /iid "Percy_i.c" "Percy.idl"

!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinDependency"

InputPath=.\Percy.idl

".\Percy.tlb"	".\Percy.h"	".\Percy_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Percy.h" /iid "Percy_i.c" "Percy.idl"

!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinSize"

InputPath=.\Percy.idl

".\Percy.tlb"	".\Percy.h"	".\Percy_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Percy.h" /iid "Percy_i.c" "Percy.idl"

!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinDependency"

InputPath=.\Percy.idl

".\Percy.tlb"	".\Percy.h"	".\Percy_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Percy.h" /iid "Percy_i.c" "Percy.idl"

!ENDIF 

SOURCE=.\Percy.rc
DEP_RSC_PERCY_=\
	".\percyctl.rgs"\
	
NODEP_RSC_PERCY_=\
	".\Percy.tlb"\
	

"$(INTDIR)\Percy.res" : $(SOURCE) $(DEP_RSC_PERCY_) "$(INTDIR)" ".\Percy.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\percyctl.cpp
DEP_CPP_PERCYC=\
	".\Percy.h"\
	".\percyctl.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PERCYC=\
	".\perhist.h"\
	

!IF  "$(CFG)" == "Percy - Win32 Debug"


"$(INTDIR)\percyctl.obj"	"$(INTDIR)\percyctl.sbr" : $(SOURCE) $(DEP_CPP_PERCYC)\
 "$(INTDIR)" "$(INTDIR)\Percy.pch" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Debug"


"$(INTDIR)\percyctl.obj" : $(SOURCE) $(DEP_CPP_PERCYC) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinSize"


"$(INTDIR)\percyctl.obj" : $(SOURCE) $(DEP_CPP_PERCYC) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinDependency"


"$(INTDIR)\percyctl.obj" : $(SOURCE) $(DEP_CPP_PERCYC) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinSize"


"$(INTDIR)\percyctl.obj" : $(SOURCE) $(DEP_CPP_PERCYC) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy.h"


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinDependency"


"$(INTDIR)\percyctl.obj" : $(SOURCE) $(DEP_CPP_PERCYC) "$(INTDIR)"\
 "$(INTDIR)\Percy.pch" ".\Percy.h"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Percy - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Percy.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Percy.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Percy.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Percy.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Percy.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Percy.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Percy - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Percy.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Percy.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\Percy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Percy.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Percy - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\Percy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Percy.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

