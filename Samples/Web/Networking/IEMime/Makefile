# Microsoft Developer Studio Generated NMAKE File, Based on IEMime.dsp
!IF "$(CFG)" == ""
CFG=IEMime - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IEMime - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IEMime - Win32 Debug" && "$(CFG)" !=\
 "IEMime - Win32 Unicode Debug" && "$(CFG)" != "IEMime - Win32 Release MinSize"\
 && "$(CFG)" != "IEMime - Win32 Release MinDependency" && "$(CFG)" !=\
 "IEMime - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "IEMime - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IEMime.mak" CFG="IEMime - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IEMime - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IEMime - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IEMime - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IEMime - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IEMime - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IEMime - Win32 Unicode Release MinDependency" (based on\
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

!IF  "$(CFG)" == "IEMime - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IEMime.dll" "$(OUTDIR)\IEMime.bsc" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\IEMime.dll" "$(OUTDIR)\IEMime.bsc" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\IEMime.obj"
	-@erase "$(INTDIR)\IEMime.pch"
	-@erase "$(INTDIR)\IEMime.res"
	-@erase "$(INTDIR)\IEMime.sbr"
	-@erase "$(INTDIR)\IEMimeCtl.obj"
	-@erase "$(INTDIR)\IEMimeCtl.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\IEMime.bsc"
	-@erase "$(OUTDIR)\IEMime.dll"
	-@erase "$(OUTDIR)\IEMime.exp"
	-@erase "$(OUTDIR)\IEMime.ilk"
	-@erase "$(OUTDIR)\IEMime.lib"
	-@erase "$(OUTDIR)\IEMime.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\IEMime.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IEMime.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IEMime.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\IEMime.sbr" \
	"$(INTDIR)\IEMimeCtl.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\IEMime.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\IEMime.pdb" /debug /machine:I386 /def:".\IEMime.def"\
 /out:"$(OUTDIR)\IEMime.dll" /implib:"$(OUTDIR)\IEMime.lib" /pdbtype:sept 
DEF_FILE= \
	".\IEMime.def"
LINK32_OBJS= \
	"$(INTDIR)\IEMime.obj" \
	"$(INTDIR)\IEMime.res" \
	"$(INTDIR)\IEMimeCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\IEMime.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\IEMime.dll
InputPath=.\Debug\IEMime.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\IEMime.obj"
	-@erase "$(INTDIR)\IEMime.pch"
	-@erase "$(INTDIR)\IEMime.res"
	-@erase "$(INTDIR)\IEMimeCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\IEMime.dll"
	-@erase "$(OUTDIR)\IEMime.exp"
	-@erase "$(OUTDIR)\IEMime.ilk"
	-@erase "$(OUTDIR)\IEMime.lib"
	-@erase "$(OUTDIR)\IEMime.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\IEMime.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IEMime.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IEMime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\IEMime.pdb" /debug /machine:I386 /def:".\IEMime.def"\
 /out:"$(OUTDIR)\IEMime.dll" /implib:"$(OUTDIR)\IEMime.lib" /pdbtype:sept 
DEF_FILE= \
	".\IEMime.def"
LINK32_OBJS= \
	"$(INTDIR)\IEMime.obj" \
	"$(INTDIR)\IEMime.res" \
	"$(INTDIR)\IEMimeCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\IEMime.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\IEMime.dll
InputPath=.\DebugU\IEMime.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\IEMime.obj"
	-@erase "$(INTDIR)\IEMime.pch"
	-@erase "$(INTDIR)\IEMime.res"
	-@erase "$(INTDIR)\IEMimeCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\IEMime.dll"
	-@erase "$(OUTDIR)\IEMime.exp"
	-@erase "$(OUTDIR)\IEMime.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_DLL" /Fp"$(INTDIR)\IEMime.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IEMime.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IEMime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\IEMime.pdb" /machine:I386 /def:".\IEMime.def"\
 /out:"$(OUTDIR)\IEMime.dll" /implib:"$(OUTDIR)\IEMime.lib" 
DEF_FILE= \
	".\IEMime.def"
LINK32_OBJS= \
	"$(INTDIR)\IEMime.obj" \
	"$(INTDIR)\IEMime.res" \
	"$(INTDIR)\IEMimeCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\IEMime.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\IEMime.dll
InputPath=.\ReleaseMinSize\IEMime.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\IEMime.obj"
	-@erase "$(INTDIR)\IEMime.pch"
	-@erase "$(INTDIR)\IEMime.res"
	-@erase "$(INTDIR)\IEMimeCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\IEMime.dll"
	-@erase "$(OUTDIR)\IEMime.exp"
	-@erase "$(OUTDIR)\IEMime.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\IEMime.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IEMime.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IEMime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\IEMime.pdb" /machine:I386 /def:".\IEMime.def"\
 /out:"$(OUTDIR)\IEMime.dll" /implib:"$(OUTDIR)\IEMime.lib" 
DEF_FILE= \
	".\IEMime.def"
LINK32_OBJS= \
	"$(INTDIR)\IEMime.obj" \
	"$(INTDIR)\IEMime.res" \
	"$(INTDIR)\IEMimeCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\IEMime.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\IEMime.dll
InputPath=.\ReleaseMinDependency\IEMime.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\IEMime.obj"
	-@erase "$(INTDIR)\IEMime.pch"
	-@erase "$(INTDIR)\IEMime.res"
	-@erase "$(INTDIR)\IEMimeCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\IEMime.dll"
	-@erase "$(OUTDIR)\IEMime.exp"
	-@erase "$(OUTDIR)\IEMime.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\IEMime.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseUMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IEMime.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IEMime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\IEMime.pdb" /machine:I386 /def:".\IEMime.def"\
 /out:"$(OUTDIR)\IEMime.dll" /implib:"$(OUTDIR)\IEMime.lib" 
DEF_FILE= \
	".\IEMime.def"
LINK32_OBJS= \
	"$(INTDIR)\IEMime.obj" \
	"$(INTDIR)\IEMime.res" \
	"$(INTDIR)\IEMimeCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\IEMime.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\IEMime.dll
InputPath=.\ReleaseUMinSize\IEMime.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\IEMime.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\IEMime.obj"
	-@erase "$(INTDIR)\IEMime.pch"
	-@erase "$(INTDIR)\IEMime.res"
	-@erase "$(INTDIR)\IEMimeCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\IEMime.dll"
	-@erase "$(OUTDIR)\IEMime.exp"
	-@erase "$(OUTDIR)\IEMime.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\IEMime.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseUMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IEMime.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IEMime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\IEMime.pdb" /machine:I386 /def:".\IEMime.def"\
 /out:"$(OUTDIR)\IEMime.dll" /implib:"$(OUTDIR)\IEMime.lib" 
DEF_FILE= \
	".\IEMime.def"
LINK32_OBJS= \
	"$(INTDIR)\IEMime.obj" \
	"$(INTDIR)\IEMime.res" \
	"$(INTDIR)\IEMimeCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\IEMime.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\IEMime.dll
InputPath=.\ReleaseUMinDependency\IEMime.dll
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


!IF "$(CFG)" == "IEMime - Win32 Debug" || "$(CFG)" ==\
 "IEMime - Win32 Unicode Debug" || "$(CFG)" == "IEMime - Win32 Release MinSize"\
 || "$(CFG)" == "IEMime - Win32 Release MinDependency" || "$(CFG)" ==\
 "IEMime - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "IEMime - Win32 Unicode Release MinDependency"
SOURCE=.\IEMime.cpp

!IF  "$(CFG)" == "IEMime - Win32 Debug"

DEP_CPP_IEMIM=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\IEMime.h"\
	".\IEMime_i.c"\
	".\IEMimeCtl.h"\
	

"$(INTDIR)\IEMime.obj"	"$(INTDIR)\IEMime.sbr" : $(SOURCE) $(DEP_CPP_IEMIM)\
 "$(INTDIR)" "$(INTDIR)\IEMime.pch" ".\IEMime_i.c" ".\IEMime.h"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Debug"

DEP_CPP_IEMIM=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\IEMime.h"\
	".\IEMime_i.c"\
	".\IEMimeCtl.h"\
	

"$(INTDIR)\IEMime.obj" : $(SOURCE) $(DEP_CPP_IEMIM) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h" ".\IEMime_i.c"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinSize"

DEP_CPP_IEMIM=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\IEMimeCtl.h"\
	
NODEP_CPP_IEMIM=\
	".\IEMime.h"\
	".\IEMime_i.c"\
	

"$(INTDIR)\IEMime.obj" : $(SOURCE) $(DEP_CPP_IEMIM) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h" ".\IEMime_i.c"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinDependency"

DEP_CPP_IEMIM=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\IEMimeCtl.h"\
	
NODEP_CPP_IEMIM=\
	".\IEMime.h"\
	".\IEMime_i.c"\
	

"$(INTDIR)\IEMime.obj" : $(SOURCE) $(DEP_CPP_IEMIM) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h" ".\IEMime_i.c"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinSize"

DEP_CPP_IEMIM=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\IEMimeCtl.h"\
	
NODEP_CPP_IEMIM=\
	".\IEMime.h"\
	".\IEMime_i.c"\
	

"$(INTDIR)\IEMime.obj" : $(SOURCE) $(DEP_CPP_IEMIM) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h" ".\IEMime_i.c"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinDependency"

DEP_CPP_IEMIM=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\IEMimeCtl.h"\
	
NODEP_CPP_IEMIM=\
	".\IEMime.h"\
	".\IEMime_i.c"\
	

"$(INTDIR)\IEMime.obj" : $(SOURCE) $(DEP_CPP_IEMIM) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime_i.c" ".\IEMime.h"


!ENDIF 

SOURCE=.\IEMime.idl

!IF  "$(CFG)" == "IEMime - Win32 Debug"

InputPath=.\IEMime.idl

".\IEMime.tlb"	".\IEMime.h"	".\IEMime_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "IEMime.h" /iid "IEMime_i.c" "IEMime.idl"

!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Debug"

InputPath=.\IEMime.idl

".\IEMime.tlb"	".\IEMime.h"	".\IEMime_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "IEMime.h" /iid "IEMime_i.c" "IEMime.idl"

!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinSize"

InputPath=.\IEMime.idl

".\IEMime.tlb"	".\IEMime.h"	".\IEMime_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "IEMime.h" /iid "IEMime_i.c" "IEMime.idl"

!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinDependency"

InputPath=.\IEMime.idl

".\IEMime.tlb"	".\IEMime.h"	".\IEMime_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "IEMime.h" /iid "IEMime_i.c" "IEMime.idl"

!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinSize"

InputPath=.\IEMime.idl

".\IEMime.tlb"	".\IEMime.h"	".\IEMime_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "IEMime.h" /iid "IEMime_i.c" "IEMime.idl"

!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinDependency"

InputPath=.\IEMime.idl

".\IEMime.tlb"	".\IEMime.h"	".\IEMime_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "IEMime.h" /iid "IEMime_i.c" "IEMime.idl"

!ENDIF 

SOURCE=.\IEMime.rc
DEP_RSC_IEMIME=\
	".\IEMime.tlb"\
	".\IEMimeCtl.rgs"\
	

"$(INTDIR)\IEMime.res" : $(SOURCE) $(DEP_RSC_IEMIME) "$(INTDIR)" ".\IEMime.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\IEMimeCtl.cpp

!IF  "$(CFG)" == "IEMime - Win32 Debug"

DEP_CPP_IEMIMEC=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\dispids.h"\
	".\IEMime.h"\
	".\IEMimeCtl.h"\
	

"$(INTDIR)\IEMimeCtl.obj"	"$(INTDIR)\IEMimeCtl.sbr" : $(SOURCE)\
 $(DEP_CPP_IEMIMEC) "$(INTDIR)" "$(INTDIR)\IEMime.pch" ".\IEMime.h"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Debug"

DEP_CPP_IEMIMEC=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\dispids.h"\
	".\IEMime.h"\
	".\IEMimeCtl.h"\
	

"$(INTDIR)\IEMimeCtl.obj" : $(SOURCE) $(DEP_CPP_IEMIMEC) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinSize"

DEP_CPP_IEMIMEC=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\dispids.h"\
	".\IEMimeCtl.h"\
	
NODEP_CPP_IEMIMEC=\
	".\IEMime.h"\
	

"$(INTDIR)\IEMimeCtl.obj" : $(SOURCE) $(DEP_CPP_IEMIMEC) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinDependency"

DEP_CPP_IEMIMEC=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\dispids.h"\
	".\IEMimeCtl.h"\
	
NODEP_CPP_IEMIMEC=\
	".\IEMime.h"\
	

"$(INTDIR)\IEMimeCtl.obj" : $(SOURCE) $(DEP_CPP_IEMIMEC) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinSize"

DEP_CPP_IEMIMEC=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\dispids.h"\
	".\IEMime.h"\
	".\IEMimeCtl.h"\
	

"$(INTDIR)\IEMimeCtl.obj" : $(SOURCE) $(DEP_CPP_IEMIMEC) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h"


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinDependency"

DEP_CPP_IEMIMEC=\
	".\BSCbck.h"\
	".\CPIEMime.h"\
	".\dispids.h"\
	".\IEMime.h"\
	".\IEMimeCtl.h"\
	

"$(INTDIR)\IEMimeCtl.obj" : $(SOURCE) $(DEP_CPP_IEMIMEC) "$(INTDIR)"\
 "$(INTDIR)\IEMime.pch" ".\IEMime.h"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "IEMime - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\IEMime.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\IEMime.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\IEMime.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IEMime.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\IEMime.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IEMime.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IEMime - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\IEMime.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IEMime.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\IEMime.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IEMime.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IEMime - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\IEMime.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IEMime.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

