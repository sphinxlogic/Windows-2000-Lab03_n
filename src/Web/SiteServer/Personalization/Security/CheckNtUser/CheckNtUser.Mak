# Microsoft Developer Studio Generated NMAKE File, Based on CheckNTUser.dsp
!IF "$(CFG)" == ""
CFG=CheckNTUser - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CheckNTUser - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CheckNTUser - Win32 Debug" && "$(CFG)" !=\
 "CheckNTUser - Win32 Unicode Debug" && "$(CFG)" !=\
 "CheckNTUser - Win32 Release MinSize" && "$(CFG)" !=\
 "CheckNTUser - Win32 Release MinDependency" && "$(CFG)" !=\
 "CheckNTUser - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "CheckNTUser - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CheckNTUser.mak" CFG="CheckNTUser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CheckNTUser - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CheckNTUser - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CheckNTUser - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CheckNTUser - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CheckNTUser - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CheckNTUser - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CheckNTUser - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckNTUser.obj"
	-@erase "$(INTDIR)\CheckNTUser.pch"
	-@erase "$(INTDIR)\CheckNTUser.res"
	-@erase "$(INTDIR)\CheckNTUserImp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CheckNTUser.dll"
	-@erase "$(OUTDIR)\CheckNTUser.exp"
	-@erase "$(OUTDIR)\CheckNTUser.ilk"
	-@erase "$(OUTDIR)\CheckNTUser.lib"
	-@erase "$(OUTDIR)\CheckNTUser.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /Fp"$(INTDIR)\CheckNTUser.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CheckNTUser.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckNTUser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\CheckNTUser.pdb" /debug /machine:I386 /def:".\CheckNTUser.def"\
 /out:"$(OUTDIR)\CheckNTUser.dll" /implib:"$(OUTDIR)\CheckNTUser.lib"\
 /pdbtype:sept 
DEF_FILE= \
	".\CheckNTUser.def"
LINK32_OBJS= \
	"$(INTDIR)\CheckNTUser.obj" \
	"$(INTDIR)\CheckNTUser.res" \
	"$(INTDIR)\CheckNTUserImp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckNTUser.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\CheckNTUser.dll
InputPath=.\Debug\CheckNTUser.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckNTUser.obj"
	-@erase "$(INTDIR)\CheckNTUser.pch"
	-@erase "$(INTDIR)\CheckNTUser.res"
	-@erase "$(INTDIR)\CheckNTUserImp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CheckNTUser.dll"
	-@erase "$(OUTDIR)\CheckNTUser.exp"
	-@erase "$(OUTDIR)\CheckNTUser.ilk"
	-@erase "$(OUTDIR)\CheckNTUser.lib"
	-@erase "$(OUTDIR)\CheckNTUser.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CheckNTUser.pch" /Yu"stdafx.h"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CheckNTUser.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckNTUser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\CheckNTUser.pdb" /debug /machine:I386 /def:".\CheckNTUser.def"\
 /out:"$(OUTDIR)\CheckNTUser.dll" /implib:"$(OUTDIR)\CheckNTUser.lib"\
 /pdbtype:sept 
DEF_FILE= \
	".\CheckNTUser.def"
LINK32_OBJS= \
	"$(INTDIR)\CheckNTUser.obj" \
	"$(INTDIR)\CheckNTUser.res" \
	"$(INTDIR)\CheckNTUserImp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckNTUser.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CheckNTUser.dll
InputPath=.\DebugU\CheckNTUser.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckNTUser.obj"
	-@erase "$(INTDIR)\CheckNTUser.pch"
	-@erase "$(INTDIR)\CheckNTUser.res"
	-@erase "$(INTDIR)\CheckNTUserImp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CheckNTUser.dll"
	-@erase "$(OUTDIR)\CheckNTUser.exp"
	-@erase "$(OUTDIR)\CheckNTUser.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CheckNTUser.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CheckNTUser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckNTUser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\CheckNTUser.pdb" /machine:I386 /def:".\CheckNTUser.def"\
 /out:"$(OUTDIR)\CheckNTUser.dll" /implib:"$(OUTDIR)\CheckNTUser.lib" 
DEF_FILE= \
	".\CheckNTUser.def"
LINK32_OBJS= \
	"$(INTDIR)\CheckNTUser.obj" \
	"$(INTDIR)\CheckNTUser.res" \
	"$(INTDIR)\CheckNTUserImp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckNTUser.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\CheckNTUser.dll
InputPath=.\ReleaseMinSize\CheckNTUser.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckNTUser.obj"
	-@erase "$(INTDIR)\CheckNTUser.pch"
	-@erase "$(INTDIR)\CheckNTUser.res"
	-@erase "$(INTDIR)\CheckNTUserImp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CheckNTUser.dll"
	-@erase "$(OUTDIR)\CheckNTUser.exp"
	-@erase "$(OUTDIR)\CheckNTUser.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CheckNTUser.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CheckNTUser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckNTUser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\CheckNTUser.pdb" /machine:I386 /def:".\CheckNTUser.def"\
 /out:"$(OUTDIR)\CheckNTUser.dll" /implib:"$(OUTDIR)\CheckNTUser.lib" 
DEF_FILE= \
	".\CheckNTUser.def"
LINK32_OBJS= \
	"$(INTDIR)\CheckNTUser.obj" \
	"$(INTDIR)\CheckNTUser.res" \
	"$(INTDIR)\CheckNTUserImp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckNTUser.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\CheckNTUser.dll
InputPath=.\ReleaseMinDependency\CheckNTUser.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckNTUser.obj"
	-@erase "$(INTDIR)\CheckNTUser.pch"
	-@erase "$(INTDIR)\CheckNTUser.res"
	-@erase "$(INTDIR)\CheckNTUserImp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CheckNTUser.dll"
	-@erase "$(OUTDIR)\CheckNTUser.exp"
	-@erase "$(OUTDIR)\CheckNTUser.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CheckNTUser.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CheckNTUser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckNTUser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\CheckNTUser.pdb" /machine:I386 /def:".\CheckNTUser.def"\
 /out:"$(OUTDIR)\CheckNTUser.dll" /implib:"$(OUTDIR)\CheckNTUser.lib" 
DEF_FILE= \
	".\CheckNTUser.def"
LINK32_OBJS= \
	"$(INTDIR)\CheckNTUser.obj" \
	"$(INTDIR)\CheckNTUser.res" \
	"$(INTDIR)\CheckNTUserImp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckNTUser.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\CheckNTUser.dll
InputPath=.\ReleaseUMinSize\CheckNTUser.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CheckNTUser.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CheckNTUser.obj"
	-@erase "$(INTDIR)\CheckNTUser.pch"
	-@erase "$(INTDIR)\CheckNTUser.res"
	-@erase "$(INTDIR)\CheckNTUserImp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CheckNTUser.dll"
	-@erase "$(OUTDIR)\CheckNTUser.exp"
	-@erase "$(OUTDIR)\CheckNTUser.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\CheckNTUser.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CheckNTUser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CheckNTUser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\CheckNTUser.pdb" /machine:I386 /def:".\CheckNTUser.def"\
 /out:"$(OUTDIR)\CheckNTUser.dll" /implib:"$(OUTDIR)\CheckNTUser.lib" 
DEF_FILE= \
	".\CheckNTUser.def"
LINK32_OBJS= \
	"$(INTDIR)\CheckNTUser.obj" \
	"$(INTDIR)\CheckNTUser.res" \
	"$(INTDIR)\CheckNTUserImp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CheckNTUser.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\CheckNTUser.dll
InputPath=.\ReleaseUMinDependency\CheckNTUser.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "CheckNTUser - Win32 Debug" || "$(CFG)" ==\
 "CheckNTUser - Win32 Unicode Debug" || "$(CFG)" ==\
 "CheckNTUser - Win32 Release MinSize" || "$(CFG)" ==\
 "CheckNTUser - Win32 Release MinDependency" || "$(CFG)" ==\
 "CheckNTUser - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "CheckNTUser - Win32 Unicode Release MinDependency"
SOURCE=.\CheckNTUser.cpp

!IF  "$(CFG)" == "CheckNTUser - Win32 Debug"

DEP_CPP_CHECK=\
	".\CheckNTUser.h"\
	".\CheckNTUser_i.c"\
	".\CheckNTUserImp.h"\
	

"$(INTDIR)\CheckNTUser.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser_i.c" ".\CheckNTUser.h"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Debug"

DEP_CPP_CHECK=\
	".\CheckNTUser.h"\
	".\CheckNTUser_i.c"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUser.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h" ".\CheckNTUser_i.c"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinSize"

DEP_CPP_CHECK=\
	".\CheckNTUser.h"\
	".\CheckNTUser_i.c"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUser.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h" ".\CheckNTUser_i.c"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinDependency"

DEP_CPP_CHECK=\
	".\CheckNTUser.h"\
	".\CheckNTUser_i.c"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUser.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h" ".\CheckNTUser_i.c"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinSize"

DEP_CPP_CHECK=\
	".\CheckNTUser.h"\
	".\CheckNTUser_i.c"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUser.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h" ".\CheckNTUser_i.c"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinDependency"

DEP_CPP_CHECK=\
	".\CheckNTUser.h"\
	".\CheckNTUser_i.c"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUser.obj" : $(SOURCE) $(DEP_CPP_CHECK) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h" ".\CheckNTUser_i.c"


!ENDIF 

SOURCE=.\CheckNTUser.idl

!IF  "$(CFG)" == "CheckNTUser - Win32 Debug"

InputPath=.\CheckNTUser.idl

".\CheckNTUser.tlb"	".\CheckNTUser.h"	".\CheckNTUser_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "CheckNTUser.h" /iid "CheckNTUser_i.c" "CheckNTUser.idl"

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Debug"

InputPath=.\CheckNTUser.idl

".\CheckNTUser.tlb"	".\CheckNTUser.h"	".\CheckNTUser_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "CheckNTUser.h" /iid "CheckNTUser_i.c" "CheckNTUser.idl"

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinSize"

InputPath=.\CheckNTUser.idl

".\CheckNTUser.tlb"	".\CheckNTUser.h"	".\CheckNTUser_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "CheckNTUser.h" /iid "CheckNTUser_i.c" "CheckNTUser.idl"

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinDependency"

InputPath=.\CheckNTUser.idl

".\CheckNTUser.tlb"	".\CheckNTUser.h"	".\CheckNTUser_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "CheckNTUser.h" /iid "CheckNTUser_i.c" "CheckNTUser.idl"

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinSize"

InputPath=.\CheckNTUser.idl

".\CheckNTUser.tlb"	".\CheckNTUser.h"	".\CheckNTUser_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "CheckNTUser.h" /iid "CheckNTUser_i.c" "CheckNTUser.idl"

!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinDependency"

InputPath=.\CheckNTUser.idl

".\CheckNTUser.tlb"	".\CheckNTUser.h"	".\CheckNTUser_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "CheckNTUser.h" /iid "CheckNTUser_i.c" "CheckNTUser.idl"

!ENDIF 

SOURCE=.\CheckNTUser.rc
DEP_RSC_CHECKN=\
	".\CheckNTUser.tlb"\
	".\CheckNTUserImp.rgs"\
	

"$(INTDIR)\CheckNTUser.res" : $(SOURCE) $(DEP_RSC_CHECKN) "$(INTDIR)"\
 ".\CheckNTUser.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CheckNTUserImp.cpp

!IF  "$(CFG)" == "CheckNTUser - Win32 Debug"

DEP_CPP_CHECKNT=\
	".\CheckNTUser.h"\
	".\CheckNTUserImp.h"\
	

"$(INTDIR)\CheckNTUserImp.obj" : $(SOURCE) $(DEP_CPP_CHECKNT) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Debug"

DEP_CPP_CHECKNT=\
	".\CheckNTUser.h"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUserImp.obj" : $(SOURCE) $(DEP_CPP_CHECKNT) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinSize"

DEP_CPP_CHECKNT=\
	".\CheckNTUser.h"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUserImp.obj" : $(SOURCE) $(DEP_CPP_CHECKNT) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinDependency"

DEP_CPP_CHECKNT=\
	".\CheckNTUser.h"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUserImp.obj" : $(SOURCE) $(DEP_CPP_CHECKNT) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinSize"

DEP_CPP_CHECKNT=\
	".\CheckNTUser.h"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUserImp.obj" : $(SOURCE) $(DEP_CPP_CHECKNT) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h"


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinDependency"

DEP_CPP_CHECKNT=\
	".\CheckNTUser.h"\
	".\CheckNTUserImp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CheckNTUserImp.obj" : $(SOURCE) $(DEP_CPP_CHECKNT) "$(INTDIR)"\
 "$(INTDIR)\CheckNTUser.pch" ".\CheckNTUser.h"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CheckNTUser - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /Fp"$(INTDIR)\CheckNTUser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckNTUser.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CheckNTUser.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckNTUser.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CheckNTUser.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckNTUser.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\CheckNTUser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckNTUser.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\CheckNTUser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckNTUser.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CheckNTUser - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\CheckNTUser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CheckNTUser.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

