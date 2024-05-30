# Microsoft Developer Studio Generated NMAKE File, Based on AtlBrowser.dsp
!IF "$(CFG)" == ""
CFG=AtlBrowser - Win32 Debug
!MESSAGE No configuration specified. Defaulting to AtlBrowser - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AtlBrowser - Win32 Debug" && "$(CFG)" != "AtlBrowser - Win32 Release MinSize" && "$(CFG)" != "AtlBrowser - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AtlBrowser.mak" CFG="AtlBrowser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AtlBrowser - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AtlBrowser - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "AtlBrowser - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "AtlBrowser - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\AtlBrowser.exe" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AboutBox.obj"
	-@erase "$(INTDIR)\AtlBrCon.obj"
	-@erase "$(INTDIR)\AtlBrowser.obj"
	-@erase "$(INTDIR)\AtlBrowser.pch"
	-@erase "$(INTDIR)\AtlBrowser.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AtlBrowser.exe"
	-@erase "$(OUTDIR)\AtlBrowser.ilk"
	-@erase "$(OUTDIR)\AtlBrowser.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\AtlBrowser.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBrowser.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\AtlBrowser.pdb" /debug /machine:I386 /out:"$(OUTDIR)\AtlBrowser.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AboutBox.obj" \
	"$(INTDIR)\AtlBrCon.obj" \
	"$(INTDIR)\AtlBrowser.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBrowser.res"

"$(OUTDIR)\AtlBrowser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\AtlBrowser.exe
InputPath=.\Debug\AtlBrowser.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off
        echo.
	echo Run this commandline to register:
        echo     "$(TargetPath)" /RegServer 
        echo.
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "AtlBrowser - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\AtlBrowser_i.c" ".\AtlBrowser.tlb" ".\AtlBrowser.h" "$(OUTDIR)\AtlBrowser.exe" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AboutBox.obj"
	-@erase "$(INTDIR)\AtlBrCon.obj"
	-@erase "$(INTDIR)\AtlBrowser.obj"
	-@erase "$(INTDIR)\AtlBrowser.pch"
	-@erase "$(INTDIR)\AtlBrowser.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlBrowser.exe"
	-@erase ".\AtlBrowser.h"
	-@erase ".\AtlBrowser.tlb"
	-@erase ".\AtlBrowser_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /Fp"$(INTDIR)\AtlBrowser.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBrowser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AtlBrowser.pdb" /machine:I386 /out:"$(OUTDIR)\AtlBrowser.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutBox.obj" \
	"$(INTDIR)\AtlBrCon.obj" \
	"$(INTDIR)\AtlBrowser.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBrowser.res"

"$(OUTDIR)\AtlBrowser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\AtlBrowser.exe
InputPath=.\ReleaseMinSize\AtlBrowser.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off
        echo.
	echo Run this commandline to register:
        echo     "$(TargetPath)" /RegServer 
        echo.
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "AtlBrowser - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\AtlBrowser_i.c" ".\AtlBrowser.tlb" ".\AtlBrowser.h" "$(OUTDIR)\AtlBrowser.exe" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AboutBox.obj"
	-@erase "$(INTDIR)\AtlBrCon.obj"
	-@erase "$(INTDIR)\AtlBrowser.obj"
	-@erase "$(INTDIR)\AtlBrowser.pch"
	-@erase "$(INTDIR)\AtlBrowser.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AtlBrowser.exe"
	-@erase ".\AtlBrowser.h"
	-@erase ".\AtlBrowser.tlb"
	-@erase ".\AtlBrowser_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\AtlBrowser.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AtlBrowser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AtlBrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AtlBrowser.pdb" /machine:I386 /out:"$(OUTDIR)\AtlBrowser.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutBox.obj" \
	"$(INTDIR)\AtlBrCon.obj" \
	"$(INTDIR)\AtlBrowser.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AtlBrowser.res"

"$(OUTDIR)\AtlBrowser.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\AtlBrowser.exe
InputPath=.\ReleaseMinDependency\AtlBrowser.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off
        echo.
	echo Run this commandline to register:
        echo     "$(TargetPath)" /RegServer 
        echo.
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("AtlBrowser.dep")
!INCLUDE "AtlBrowser.dep"
!ELSE 
!MESSAGE Warning: cannot find "AtlBrowser.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AtlBrowser - Win32 Debug" || "$(CFG)" == "AtlBrowser - Win32 Release MinSize" || "$(CFG)" == "AtlBrowser - Win32 Release MinDependency"
SOURCE=.\AboutBox.cpp

"$(INTDIR)\AboutBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlBrowser.pch"


SOURCE=.\AtlBrCon.cpp

"$(INTDIR)\AtlBrCon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlBrowser.pch" ".\AtlBrowser.h"


SOURCE=.\AtlBrowser.cpp

"$(INTDIR)\AtlBrowser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AtlBrowser.pch" ".\AtlBrowser.h" ".\AtlBrowser_i.c"


SOURCE=.\AtlBrowser.idl

!IF  "$(CFG)" == "AtlBrowser - Win32 Debug"

InputPath=.\AtlBrowser.idl

".\AtlBrowser.tlb"	".\AtlBrowser.h"	".\AtlBrowser_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBrowser.h" /iid "AtlBrowser_i.c" "AtlBrowser.idl"
<< 
	

!ELSEIF  "$(CFG)" == "AtlBrowser - Win32 Release MinSize"

InputPath=.\AtlBrowser.idl

".\AtlBrowser.tlb"	".\AtlBrowser.h"	".\AtlBrowser_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBrowser.h" /iid "AtlBrowser_i.c" "AtlBrowser.idl"
<< 
	

!ELSEIF  "$(CFG)" == "AtlBrowser - Win32 Release MinDependency"

InputPath=.\AtlBrowser.idl

".\AtlBrowser.tlb"	".\AtlBrowser.h"	".\AtlBrowser_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "AtlBrowser.h" /iid "AtlBrowser_i.c" "AtlBrowser.idl"
<< 
	

!ENDIF 

SOURCE=.\AtlBrowser.rc

"$(INTDIR)\AtlBrowser.res" : $(SOURCE) "$(INTDIR)" ".\AtlBrowser.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "AtlBrowser - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\AtlBrowser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBrowser.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlBrowser - Win32 Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_DLL" /Fp"$(INTDIR)\AtlBrowser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBrowser.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AtlBrowser - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\AtlBrowser.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AtlBrowser.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

