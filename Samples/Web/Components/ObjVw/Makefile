# Microsoft Developer Studio Generated NMAKE File, Based on ObjVw.dsp
!IF "$(CFG)" == ""
CFG=ObjVw - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ObjVw - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ObjVw - Win32 Debug" && "$(CFG)" !=\
 "ObjVw - Win32 Unicode Debug" && "$(CFG)" != "ObjVw - Win32 Release MinSize" &&\
 "$(CFG)" != "ObjVw - Win32 Release MinDependency" && "$(CFG)" !=\
 "ObjVw - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "ObjVw - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ObjVw.mak" CFG="ObjVw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ObjVw - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ObjVw - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ObjVw - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ObjVw - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ObjVw - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ObjVw - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ObjVw - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ObjVw.obj"
	-@erase "$(INTDIR)\ObjVw.pch"
	-@erase "$(INTDIR)\ObjVw.res"
	-@erase "$(INTDIR)\ObjVwCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ObjVw.dll"
	-@erase "$(OUTDIR)\ObjVw.exp"
	-@erase "$(OUTDIR)\ObjVw.ilk"
	-@erase "$(OUTDIR)\ObjVw.lib"
	-@erase "$(OUTDIR)\ObjVw.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /Fp"$(INTDIR)\ObjVw.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ObjVw.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObjVw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\ObjVw.pdb" /debug /machine:I386 /def:".\ObjVw.def"\
 /out:"$(OUTDIR)\ObjVw.dll" /implib:"$(OUTDIR)\ObjVw.lib" /pdbtype:sept 
DEF_FILE= \
	".\ObjVw.def"
LINK32_OBJS= \
	"$(INTDIR)\ObjVw.obj" \
	"$(INTDIR)\ObjVw.res" \
	"$(INTDIR)\ObjVwCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ObjVw.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ObjVw.dll
InputPath=.\Debug\ObjVw.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ObjVw.obj"
	-@erase "$(INTDIR)\ObjVw.pch"
	-@erase "$(INTDIR)\ObjVw.res"
	-@erase "$(INTDIR)\ObjVwCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ObjVw.dll"
	-@erase "$(OUTDIR)\ObjVw.exp"
	-@erase "$(OUTDIR)\ObjVw.ilk"
	-@erase "$(OUTDIR)\ObjVw.lib"
	-@erase "$(OUTDIR)\ObjVw.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ObjVw.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\DebugU/
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ObjVw.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObjVw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\ObjVw.pdb" /debug /machine:I386 /def:".\ObjVw.def"\
 /out:"$(OUTDIR)\ObjVw.dll" /implib:"$(OUTDIR)\ObjVw.lib" /pdbtype:sept 
DEF_FILE= \
	".\ObjVw.def"
LINK32_OBJS= \
	"$(INTDIR)\ObjVw.obj" \
	"$(INTDIR)\ObjVw.res" \
	"$(INTDIR)\ObjVwCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ObjVw.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ObjVw.dll
InputPath=.\DebugU\ObjVw.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ObjVw.obj"
	-@erase "$(INTDIR)\ObjVw.pch"
	-@erase "$(INTDIR)\ObjVw.res"
	-@erase "$(INTDIR)\ObjVwCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ObjVw.dll"
	-@erase "$(OUTDIR)\ObjVw.exp"
	-@erase "$(OUTDIR)\ObjVw.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\ObjVw.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinSize/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ObjVw.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObjVw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\ObjVw.pdb" /machine:I386 /def:".\ObjVw.def"\
 /out:"$(OUTDIR)\ObjVw.dll" /implib:"$(OUTDIR)\ObjVw.lib" 
DEF_FILE= \
	".\ObjVw.def"
LINK32_OBJS= \
	"$(INTDIR)\ObjVw.obj" \
	"$(INTDIR)\ObjVw.res" \
	"$(INTDIR)\ObjVwCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ObjVw.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ObjVw.dll
InputPath=.\ReleaseMinSize\ObjVw.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ObjVw.obj"
	-@erase "$(INTDIR)\ObjVw.pch"
	-@erase "$(INTDIR)\ObjVw.res"
	-@erase "$(INTDIR)\ObjVwCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ObjVw.dll"
	-@erase "$(OUTDIR)\ObjVw.exp"
	-@erase "$(OUTDIR)\ObjVw.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ObjVw.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinDependency/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ObjVw.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObjVw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\ObjVw.pdb" /machine:I386 /def:".\ObjVw.def"\
 /out:"$(OUTDIR)\ObjVw.dll" /implib:"$(OUTDIR)\ObjVw.lib" 
DEF_FILE= \
	".\ObjVw.def"
LINK32_OBJS= \
	"$(INTDIR)\ObjVw.obj" \
	"$(INTDIR)\ObjVw.res" \
	"$(INTDIR)\ObjVwCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ObjVw.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ObjVw.dll
InputPath=.\ReleaseMinDependency\ObjVw.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ObjVw.obj"
	-@erase "$(INTDIR)\ObjVw.pch"
	-@erase "$(INTDIR)\ObjVw.res"
	-@erase "$(INTDIR)\ObjVwCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ObjVw.dll"
	-@erase "$(OUTDIR)\ObjVw.exp"
	-@erase "$(OUTDIR)\ObjVw.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\ObjVw.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseUMinSize/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ObjVw.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObjVw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\ObjVw.pdb" /machine:I386 /def:".\ObjVw.def"\
 /out:"$(OUTDIR)\ObjVw.dll" /implib:"$(OUTDIR)\ObjVw.lib" 
DEF_FILE= \
	".\ObjVw.def"
LINK32_OBJS= \
	"$(INTDIR)\ObjVw.obj" \
	"$(INTDIR)\ObjVw.res" \
	"$(INTDIR)\ObjVwCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ObjVw.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ObjVw.dll
InputPath=.\ReleaseUMinSize\ObjVw.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\ObjVw.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ObjVw.obj"
	-@erase "$(INTDIR)\ObjVw.pch"
	-@erase "$(INTDIR)\ObjVw.res"
	-@erase "$(INTDIR)\ObjVwCtl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ObjVw.dll"
	-@erase "$(OUTDIR)\ObjVw.exp"
	-@erase "$(OUTDIR)\ObjVw.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ObjVw.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ObjVw.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObjVw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\ObjVw.pdb" /machine:I386 /def:".\ObjVw.def"\
 /out:"$(OUTDIR)\ObjVw.dll" /implib:"$(OUTDIR)\ObjVw.lib" 
DEF_FILE= \
	".\ObjVw.def"
LINK32_OBJS= \
	"$(INTDIR)\ObjVw.obj" \
	"$(INTDIR)\ObjVw.res" \
	"$(INTDIR)\ObjVwCtl.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ObjVw.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ObjVw.dll
InputPath=.\ReleaseUMinDependency\ObjVw.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "ObjVw - Win32 Debug" || "$(CFG)" ==\
 "ObjVw - Win32 Unicode Debug" || "$(CFG)" == "ObjVw - Win32 Release MinSize" ||\
 "$(CFG)" == "ObjVw - Win32 Release MinDependency" || "$(CFG)" ==\
 "ObjVw - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "ObjVw - Win32 Unicode Release MinDependency"
SOURCE=.\ObjVw.cpp
DEP_CPP_OBJVW=\
	".\ObjVwCtl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	
NODEP_CPP_OBJVW=\
	".\ObjVw.h"\
	".\ObjVw_i.c"\
	

"$(INTDIR)\ObjVw.obj" : $(SOURCE) $(DEP_CPP_OBJVW) "$(INTDIR)"\
 "$(INTDIR)\ObjVw.pch" ".\ObjVw.h" ".\ObjVw_i.c"


SOURCE=.\ObjVw.idl

!IF  "$(CFG)" == "ObjVw - Win32 Debug"

InputPath=.\ObjVw.idl

".\ObjVw.tlb"	".\ObjVw.h"	".\ObjVw_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "ObjVw.h" /iid "ObjVw_i.c" "ObjVw.idl"

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Debug"

InputPath=.\ObjVw.idl

".\ObjVw.tlb"	".\ObjVw.h"	".\ObjVw_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "ObjVw.h" /iid "ObjVw_i.c" "ObjVw.idl"

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Release MinSize"

InputPath=.\ObjVw.idl

".\ObjVw.tlb"	".\ObjVw.h"	".\ObjVw_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "ObjVw.h" /iid "ObjVw_i.c" "ObjVw.idl"

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Release MinDependency"

InputPath=.\ObjVw.idl

".\ObjVw.tlb"	".\ObjVw.h"	".\ObjVw_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "ObjVw.h" /iid "ObjVw_i.c" "ObjVw.idl"

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Release MinSize"

InputPath=.\ObjVw.idl

".\ObjVw.tlb"	".\ObjVw.h"	".\ObjVw_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "ObjVw.h" /iid "ObjVw_i.c" "ObjVw.idl"

!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Release MinDependency"

InputPath=.\ObjVw.idl

".\ObjVw.tlb"	".\ObjVw.h"	".\ObjVw_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "ObjVw.h" /iid "ObjVw_i.c" "ObjVw.idl"

!ENDIF 

SOURCE=.\ObjVw.rc
DEP_RSC_OBJVW_=\
	".\ObjVw.rgs"\
	".\Resource.h"\
	
NODEP_RSC_OBJVW_=\
	".\ObjVw.tlb"\
	

"$(INTDIR)\ObjVw.res" : $(SOURCE) $(DEP_RSC_OBJVW_) "$(INTDIR)" ".\ObjVw.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ObjVwCtl.cpp
DEP_CPP_OBJVWC=\
	".\ObjVwCtl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	
NODEP_CPP_OBJVWC=\
	".\ObjVw.h"\
	

"$(INTDIR)\ObjVwCtl.obj" : $(SOURCE) $(DEP_CPP_OBJVWC) "$(INTDIR)"\
 "$(INTDIR)\ObjVw.pch" ".\ObjVw.h"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ObjVw - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\ObjVw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ObjVw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ObjVw.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ObjVw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ObjVw - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\ObjVw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ObjVw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ObjVw - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ObjVw.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ObjVw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\ObjVw.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ObjVw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ObjVw - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ObjVw.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ObjVw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

