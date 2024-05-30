# Microsoft Developer Studio Generated NMAKE File, Based on LogParse.dsp
!IF "$(CFG)" == ""
CFG=LogParse - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LogParse - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LogParse - Win32 Release" && "$(CFG)" != "LogParse - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LogParse.mak" CFG="LogParse - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LogParse - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LogParse - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "LogParse - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\LogParse.dll"


CLEAN :
	-@erase "$(INTDIR)\LogParse.obj"
	-@erase "$(INTDIR)\LogParse.pch"
	-@erase "$(INTDIR)\LogParse.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LogParse.dll"
	-@erase "$(OUTDIR)\LogParse.exp"
	-@erase "$(OUTDIR)\LogParse.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\LogParse.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LogParse.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LogParse.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LogParse.pdb" /machine:I386 /def:".\LogParse.def" /out:"$(OUTDIR)\LogParse.dll" /implib:"$(OUTDIR)\LogParse.lib" 
DEF_FILE= \
	".\LogParse.def"
LINK32_OBJS= \
	"$(INTDIR)\LogParse.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LogParse.res"

"$(OUTDIR)\LogParse.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LogParse - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LogParse.dll" "$(OUTDIR)\LogParse.bsc"


CLEAN :
	-@erase "$(INTDIR)\LogParse.obj"
	-@erase "$(INTDIR)\LogParse.pch"
	-@erase "$(INTDIR)\LogParse.res"
	-@erase "$(INTDIR)\LogParse.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LogParse.bsc"
	-@erase "$(OUTDIR)\LogParse.dll"
	-@erase "$(OUTDIR)\LogParse.exp"
	-@erase "$(OUTDIR)\LogParse.ilk"
	-@erase "$(OUTDIR)\LogParse.lib"
	-@erase "$(OUTDIR)\LogParse.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LogParse.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LogParse.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LogParse.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LogParse.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LogParse.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=urlmon.lib ole32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\LogParse.pdb" /debug /machine:I386 /def:".\LogParse.def" /out:"$(OUTDIR)\LogParse.dll" /implib:"$(OUTDIR)\LogParse.lib" /pdbtype:sept 
DEF_FILE= \
	".\LogParse.def"
LINK32_OBJS= \
	"$(INTDIR)\LogParse.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LogParse.res"

"$(OUTDIR)\LogParse.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LogParse.dep")
!INCLUDE "LogParse.dep"
!ELSE 
!MESSAGE Warning: cannot find "LogParse.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LogParse - Win32 Release" || "$(CFG)" == "LogParse - Win32 Debug"
SOURCE=.\LogParse.cpp

!IF  "$(CFG)" == "LogParse - Win32 Release"


"$(INTDIR)\LogParse.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogParse.pch"


!ELSEIF  "$(CFG)" == "LogParse - Win32 Debug"


"$(INTDIR)\LogParse.obj"	"$(INTDIR)\LogParse.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogParse.pch"


!ENDIF 

SOURCE=.\LogParse.rc

"$(INTDIR)\LogParse.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LogParse - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\LogParse.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LogParse.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LogParse - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LogParse.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LogParse.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

