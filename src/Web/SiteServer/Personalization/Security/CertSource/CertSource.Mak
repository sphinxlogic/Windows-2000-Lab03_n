# NMAKE make file for the CERTSOURCE project.
!IF "$(CFG)" == ""
CFG=CertSource - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CertSource - Win32 Debug.
!ENDIF 

!MESSAGE Building for: $(CPU)
!MESSAGE Microsoft SDK directory: $(MSSDK)

!IF "$(MSSDK)" == ""
MSSDK=C:\MSSDK
!ENDIF 

!IF "$(CPU)" == ""
CPU=i386
!ENDIF 

!IF "$(CPU)" == "i386"
CPUTYPELABEL=X86
!ELSE
CPUTYPELABEL=ALPHA
!ENDIF 

!IF "$(CFG)" != "CertSource - Win32 Debug" && "$(CFG)" !=\
 "CertSource - Win32 Unicode Debug" && "$(CFG)" !=\
 "CertSource - Win32 Release MinSize" && "$(CFG)" !=\
 "CertSource - Win32 Release MinDependency" && "$(CFG)" !=\
 "CertSource - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "CertSource - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CertSource.mak" CFG="CertSource - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CertSource - Win32 Debug" (based on\
 "Win32 ($(CPUTYPELABEL)) Dynamic-Link Library")
!MESSAGE "CertSource - Win32 Unicode Debug" (based on\
 "Win32 ($(CPUTYPELABEL)) Dynamic-Link Library")
!MESSAGE "CertSource - Win32 Release MinSize" (based on\
 "Win32 ($(CPUTYPELABEL)) Dynamic-Link Library")
!MESSAGE "CertSource - Win32 Release MinDependency" (based on\
 "Win32 ($(CPUTYPELABEL)) Dynamic-Link Library")
!MESSAGE "CertSource - Win32 Unicode Release MinSize" (based on\
 "Win32 ($(CPUTYPELABEL)) Dynamic-Link Library")
!MESSAGE "CertSource - Win32 Unicode Release MinDependency" (based on\
 "Win32 ($(CPUTYPELABEL)) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CertSource - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CertSource.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CertSource.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CertSource.obj"
	-@erase "$(INTDIR)\CertSource.res"
	-@erase "$(INTDIR)\CertSrc.obj"
	-@erase "$(INTDIR)\certStdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CertSource.dll"
	-@erase "$(OUTDIR)\CertSource.exp"
	-@erase "$(OUTDIR)\CertSource.ilk"
	-@erase "$(OUTDIR)\CertSource.lib"
	-@erase "$(OUTDIR)\CertSource.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /I "$(MSSDK)\INCLUDE" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_$(CPUTYPELABEL)_" /D "$(CPUTYPELABEL)" /D "UNICODE"\
 /Fp"$(INTDIR)\CertSource.pch" /YX"certstdafx.h" /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CertSource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CertSource.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib $(MSSDK)\LIB\WLDAP32.LIB /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\CertSource.pdb" /debug /machine:$(CPU)\
 /def:".\CertSource.def" /out:"$(OUTDIR)\CertSource.dll"\
 /implib:"$(OUTDIR)\CertSource.lib" /pdbtype:sept 
DEF_FILE= \
	".\CertSource.def"
LINK32_OBJS= \
	"$(INTDIR)\CertSource.obj" \
	"$(INTDIR)\CertSource.res" \
	"$(INTDIR)\CertSrc.obj" \
	"$(INTDIR)\certStdAfx.obj"

"$(OUTDIR)\CertSource.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\CertSource.dll
InputPath=.\Debug\CertSource.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CertSource.obj"
	-@erase "$(INTDIR)\CertSource.pch"
	-@erase "$(INTDIR)\CertSource.res"
	-@erase "$(INTDIR)\CertSrc.obj"
	-@erase "$(INTDIR)\certStdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CertSource.dll"
	-@erase "$(OUTDIR)\CertSource.exp"
	-@erase "$(OUTDIR)\CertSource.ilk"
	-@erase "$(OUTDIR)\CertSource.lib"
	-@erase "$(OUTDIR)\CertSource.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /I "$(MSSDK)\INCLUDE" /D "_DEBUG" /D\
 "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_$(CPUTYPELABEL)_" /D "$(CPUTYPELABEL)" /D\
 "UNICODE" /Fp"$(INTDIR)\CertSource.pch" /Yc"certstdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CertSource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CertSource.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib $(MSSDK)\LIB\WLDAP32.LIB /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\CertSource.pdb" /debug /machine:I386\
 /def:".\CertSource.def" /out:"$(OUTDIR)\CertSource.dll"\
 /implib:"$(OUTDIR)\CertSource.lib" /pdbtype:sept 
DEF_FILE= \
	".\CertSource.def"
LINK32_OBJS= \
	"$(INTDIR)\CertSource.obj" \
	"$(INTDIR)\CertSource.res" \
	"$(INTDIR)\CertSrc.obj" \
	"$(INTDIR)\certStdAfx.obj"

"$(OUTDIR)\CertSource.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CertSource.dll
InputPath=.\DebugU\CertSource.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CertSource.obj"
	-@erase "$(INTDIR)\CertSource.pch"
	-@erase "$(INTDIR)\CertSource.res"
	-@erase "$(INTDIR)\CertSrc.obj"
	-@erase "$(INTDIR)\certStdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CertSource.dll"
	-@erase "$(OUTDIR)\CertSource.exp"
	-@erase "$(OUTDIR)\CertSource.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "$(MSSDK)\INCLUDE" /D "NDEBUG" /D "_ATL_DLL" /D\
 "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_$(CPUTYPELABEL)_" /D "$(CPUTYPELABEL)" /D\
 "UNICODE" /Fp"$(INTDIR)\CertSource.pch" /Yc"certstdafx.h" /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CertSource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CertSource.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib $(MSSDK)\LIB\WLDAP32.LIB /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\CertSource.pdb" /machine:I386\
 /def:".\CertSource.def" /out:"$(OUTDIR)\CertSource.dll"\
 /implib:"$(OUTDIR)\CertSource.lib" 
DEF_FILE= \
	".\CertSource.def"
LINK32_OBJS= \
	"$(INTDIR)\CertSource.obj" \
	"$(INTDIR)\CertSource.res" \
	"$(INTDIR)\CertSrc.obj" \
	"$(INTDIR)\certStdAfx.obj"

"$(OUTDIR)\CertSource.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\CertSource.dll
InputPath=.\ReleaseMinSize\CertSource.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CertSource.obj"
	-@erase "$(INTDIR)\CertSource.pch"
	-@erase "$(INTDIR)\CertSource.res"
	-@erase "$(INTDIR)\CertSrc.obj"
	-@erase "$(INTDIR)\certStdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CertSource.dll"
	-@erase "$(OUTDIR)\CertSource.exp"
	-@erase "$(OUTDIR)\CertSource.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "$(MSSDK)\INCLUDE" /D "NDEBUG" /D\
 "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL"\
 /D "_$(CPUTYPELABEL)_" /D "$(CPUTYPELABEL)" /D "UNICODE" /Fp"$(INTDIR)\CertSource.pch"\
 /Yc"certstdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CertSource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CertSource.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib $(MSSDK)\LIB\WLDAP32.LIB /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\CertSource.pdb" /machine:I386\
 /def:".\CertSource.def" /out:"$(OUTDIR)\CertSource.dll"\
 /implib:"$(OUTDIR)\CertSource.lib" 
DEF_FILE= \
	".\CertSource.def"
LINK32_OBJS= \
	"$(INTDIR)\CertSource.obj" \
	"$(INTDIR)\CertSource.res" \
	"$(INTDIR)\CertSrc.obj" \
	"$(INTDIR)\certStdAfx.obj"

"$(OUTDIR)\CertSource.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\CertSource.dll
InputPath=.\ReleaseMinDependency\CertSource.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CertSource.obj"
	-@erase "$(INTDIR)\CertSource.pch"
	-@erase "$(INTDIR)\CertSource.res"
	-@erase "$(INTDIR)\CertSrc.obj"
	-@erase "$(INTDIR)\certStdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CertSource.dll"
	-@erase "$(OUTDIR)\CertSource.exp"
	-@erase "$(OUTDIR)\CertSource.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "$(MSSDK)\INCLUDE" /D "NDEBUG" /D "_UNICODE" /D\
 "_ATL_DLL" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_$(CPUTYPELABEL)_"\
 /D "$(CPUTYPELABEL)" /D "UNICODE" /Fp"$(INTDIR)\CertSource.pch" /Yc"certstdafx.h"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CertSource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CertSource.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib $(MSSDK)\LIB\WLDAP32.LIB /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\CertSource.pdb" /machine:I386\
 /def:".\CertSource.def" /out:"$(OUTDIR)\CertSource.dll"\
 /implib:"$(OUTDIR)\CertSource.lib" 
DEF_FILE= \
	".\CertSource.def"
LINK32_OBJS= \
	"$(INTDIR)\CertSource.obj" \
	"$(INTDIR)\CertSource.res" \
	"$(INTDIR)\CertSrc.obj" \
	"$(INTDIR)\certStdAfx.obj"

"$(OUTDIR)\CertSource.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\CertSource.dll
InputPath=.\ReleaseUMinSize\CertSource.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CertSource.dll" "$(OUTDIR)\CertSource.pch"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CertSource.obj"
	-@erase "$(INTDIR)\CertSource.pch"
	-@erase "$(INTDIR)\CertSource.res"
	-@erase "$(INTDIR)\CertSrc.obj"
	-@erase "$(INTDIR)\certStdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CertSource.dll"
	-@erase "$(OUTDIR)\CertSource.exp"
	-@erase "$(OUTDIR)\CertSource.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "$(MSSDK)\INCLUDE" /D "NDEBUG" /D "_UNICODE" /D\
 "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL"\
 /D "_$(CPUTYPELABEL)_" /D "$(CPUTYPELABEL)" /D "UNICODE" /Fp"$(INTDIR)\CertSource.pch"\
 /Yc"certstdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CertSource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CertSource.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib $(MSSDK)\LIB\WLDAP32.LIB /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\CertSource.pdb" /machine:I386\
 /def:".\CertSource.def" /out:"$(OUTDIR)\CertSource.dll"\
 /implib:"$(OUTDIR)\CertSource.lib" 
DEF_FILE= \
	".\CertSource.def"
LINK32_OBJS= \
	"$(INTDIR)\CertSource.obj" \
	"$(INTDIR)\CertSource.res" \
	"$(INTDIR)\CertSrc.obj" \
	"$(INTDIR)\certStdAfx.obj"

"$(OUTDIR)\CertSource.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\CertSource.dll
InputPath=.\ReleaseUMinDependency\CertSource.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "CertSource - Win32 Debug" || "$(CFG)" ==\
 "CertSource - Win32 Unicode Debug" || "$(CFG)" ==\
 "CertSource - Win32 Release MinSize" || "$(CFG)" ==\
 "CertSource - Win32 Release MinDependency" || "$(CFG)" ==\
 "CertSource - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "CertSource - Win32 Unicode Release MinDependency"
SOURCE=.\CertSource.cpp
DEP_CPP_CERTS=\
	".\CertSource.h"\
	".\CertSource_i.c"\
	".\CertSrc.h"\
	".\certstdafx.h"\
	

!IF  "$(CFG)" == "CertSource - Win32 Debug"


"$(INTDIR)\CertSource.obj" : $(SOURCE) $(DEP_CPP_CERTS) "$(INTDIR)"\
 ".\CertSource.h" ".\CertSource_i.c"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Debug"


"$(INTDIR)\CertSource.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTS) "$(INTDIR)" ".\CertSource.h" ".\CertSource_i.c"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinSize"


"$(INTDIR)\CertSource.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTS) "$(INTDIR)" ".\CertSource.h" ".\CertSource_i.c"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinDependency"


"$(INTDIR)\CertSource.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTS) "$(INTDIR)" ".\CertSource.h" ".\CertSource_i.c"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinSize"


"$(INTDIR)\CertSource.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTS) "$(INTDIR)" ".\CertSource.h" ".\CertSource_i.c"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinDependency"


"$(INTDIR)\CertSource.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTS) "$(INTDIR)" ".\CertSource.h" ".\CertSource_i.c"


!ENDIF 

SOURCE=.\CertSource.idl

!IF  "$(CFG)" == "CertSource - Win32 Debug"

InputPath=.\CertSource.idl

".\CertSource.tlb"	".\CertSource.h"	".\CertSource_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "CertSource.h" /iid "CertSource_i.c" "CertSource.idl"

!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Debug"

InputPath=.\CertSource.idl

".\CertSource.tlb"	".\CertSource.h"	".\CertSource_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "CertSource.h" /iid "CertSource_i.c" "CertSource.idl"

!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinSize"

InputPath=.\CertSource.idl

".\CertSource.tlb"	".\CertSource.h"	".\CertSource_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "CertSource.h" /iid "CertSource_i.c" "CertSource.idl"

!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinDependency"

InputPath=.\CertSource.idl

".\CertSource.tlb"	".\CertSource.h"	".\CertSource_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "CertSource.h" /iid "CertSource_i.c" "CertSource.idl"

!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinSize"

InputPath=.\CertSource.idl

".\CertSource.tlb"	".\CertSource.h"	".\CertSource_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "CertSource.h" /iid "CertSource_i.c" "CertSource.idl"

!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinDependency"

InputPath=.\CertSource.idl

".\CertSource.tlb"	".\CertSource.h"	".\CertSource_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "CertSource.h" /iid "CertSource_i.c" "CertSource.idl"

!ENDIF 

SOURCE=.\CertSource.rc
DEP_RSC_CERTSO=\
	".\CertSource.tlb"\
	".\CertSrc.rgs"\
	

"$(INTDIR)\CertSource.res" : $(SOURCE) $(DEP_RSC_CERTSO) "$(INTDIR)"\
 ".\CertSource.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CertSrc.cpp
DEP_CPP_CERTSR=\
	$(MSSDK)\include\winldap.h"\
	".\CertSource.h"\
	".\CertSrc.h"\
	".\certstdafx.h"\
	

!IF  "$(CFG)" == "CertSource - Win32 Debug"


"$(INTDIR)\CertSrc.obj" : $(SOURCE) $(DEP_CPP_CERTSR) "$(INTDIR)"\
 ".\CertSource.h"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Debug"


"$(INTDIR)\CertSrc.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTSR) "$(INTDIR)" ".\CertSource.h"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinSize"


"$(INTDIR)\CertSrc.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTSR) "$(INTDIR)" ".\CertSource.h"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinDependency"


"$(INTDIR)\CertSrc.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTSR) "$(INTDIR)" ".\CertSource.h"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinSize"


"$(INTDIR)\CertSrc.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTSR) "$(INTDIR)" ".\CertSource.h"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinDependency"


"$(INTDIR)\CertSrc.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTSR) "$(INTDIR)" ".\CertSource.h"


!ENDIF 

SOURCE=.\certStdAfx.cpp
DEP_CPP_CERTST=\
	".\certstdafx.h"\
	

!IF  "$(CFG)" == "CertSource - Win32 Debug"


"$(INTDIR)\certStdAfx.obj" : $(SOURCE) $(DEP_CPP_CERTST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Debug"


"$(INTDIR)\certStdAfx.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinSize"


"$(INTDIR)\certStdAfx.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Release MinDependency"


"$(INTDIR)\certStdAfx.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinSize"


"$(INTDIR)\certStdAfx.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CertSource - Win32 Unicode Release MinDependency"


"$(INTDIR)\certStdAfx.obj"	"$(INTDIR)\CertSource.pch" : $(SOURCE)\
 $(DEP_CPP_CERTST) "$(INTDIR)"


!ENDIF 


!ENDIF 

