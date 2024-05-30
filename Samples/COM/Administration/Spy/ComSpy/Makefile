# Microsoft Developer Studio Generated NMAKE File, Based on COMSpy.dsp
!IF "$(CFG)" == ""
CFG=ComSpy - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to ComSpy - Win32 Unicode Debug.
!ENDIF 

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF

!IF "$(CFG)" != "ComSpy - Win32 Unicode Debug" && "$(CFG)" != "ComSpy - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "COMSpy.mak" CFG="ComSpy - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpy - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "ComSpy - Win32 Unicode Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "ComSpy - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\COMSpy.exe" "$(OUTDIR)\COMSpy.bsc" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComSpy.obj"
	-@erase "$(INTDIR)\COMSpy.pch"
	-@erase "$(INTDIR)\ComSpy.res"
	-@erase "$(INTDIR)\ComSpy.sbr"
	-@erase "$(INTDIR)\SpyCon.obj"
	-@erase "$(INTDIR)\SpyCon.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\COMSpy.bsc"
	-@erase "$(OUTDIR)\COMSpy.exe"
	-@erase "$(OUTDIR)\COMSpy.ilk"
	-@erase "$(OUTDIR)\COMSpy.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\COMSpy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpy.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\COMSpy.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ComSpy.sbr" \
	"$(INTDIR)\SpyCon.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\COMSpy.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\COMSpy.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\COMSpy.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ComSpy.obj" \
	"$(INTDIR)\SpyCon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpy.res"

"$(OUTDIR)\COMSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\COMSpy.exe
InputPath=.\DebugU\COMSpy.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	rem "$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "ComSpy - Win32 Unicode Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\ComSpy_i.c" ".\ComSpy.tlb" ".\ComSpy.h" "$(OUTDIR)\COMSpy.exe" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComSpy.obj"
	-@erase "$(INTDIR)\COMSpy.pch"
	-@erase "$(INTDIR)\ComSpy.res"
	-@erase "$(INTDIR)\SpyCon.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\COMSpy.exe"
	-@erase ".\Release\regsvr32.trg"
	-@erase "ComSpy.h"
	-@erase "ComSpy.tlb"
	-@erase "ComSpy_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\COMSpy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\COMSpy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\COMSpy.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\COMSpy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ComSpy.obj" \
	"$(INTDIR)\SpyCon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpy.res"

"$(OUTDIR)\COMSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\COMSpy.exe
InputPath=.\Release\COMSpy.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
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
!IF EXISTS("COMSpy.dep")
!INCLUDE "COMSpy.dep"
!ELSE 
!MESSAGE Warning: cannot find "COMSpy.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ComSpy - Win32 Unicode Debug" || "$(CFG)" == "ComSpy - Win32 Unicode Release"
SOURCE=.\ComSpy.cpp

!IF  "$(CFG)" == "ComSpy - Win32 Unicode Debug"


"$(INTDIR)\ComSpy.obj"	"$(INTDIR)\ComSpy.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\COMSpy.pch" ".\ComSpy.h" ".\ComSpy_i.c"


!ELSEIF  "$(CFG)" == "ComSpy - Win32 Unicode Release"


"$(INTDIR)\ComSpy.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\COMSpy.pch"


!ENDIF 

SOURCE=.\ComSpy.idl

!IF  "$(CFG)" == "ComSpy - Win32 Unicode Debug"

InputPath=.\ComSpy.idl

".\ComSpy.h"	".\ComSpy_i.c"	".\ComSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\ComSpy.h" /tlb ".\ComSpy.tlb" /iid   ".\ComSpy_i.c"        "ComSpy.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ComSpy - Win32 Unicode Release"

InputPath=.\ComSpy.idl

".\ComSpy.h"	".\ComSpy_i.c"	".\ComSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\ComSpy.h" /tlb ".\ComSpy.tlb" /iid   ".\ComSpy_i.c"        "ComSpy.idl"
<< 
	

!ENDIF 

SOURCE=.\ComSpy.rc

"$(INTDIR)\ComSpy.res" : $(SOURCE) "$(INTDIR)" ".\ComSpy.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SpyCon.cpp

!IF  "$(CFG)" == "ComSpy - Win32 Unicode Debug"


"$(INTDIR)\SpyCon.obj"	"$(INTDIR)\SpyCon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\COMSpy.pch" ".\ComSpy.h"


!ELSEIF  "$(CFG)" == "ComSpy - Win32 Unicode Release"


"$(INTDIR)\SpyCon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\COMSpy.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ComSpy - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\COMSpy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\COMSpy.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpy - Win32 Unicode Release"

CPP_SWITCHES=/nologo /ML /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\COMSpy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\COMSpy.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

