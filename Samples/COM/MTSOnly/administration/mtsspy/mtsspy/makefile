# Microsoft Developer Studio Generated NMAKE File, Based on MTSSpy.dsp
!IF "$(CFG)" == ""
CFG=MtsSpy - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to MtsSpy - Win32 Unicode\
 Debug.
!ENDIF 

!IF "$(CFG)" != "MtsSpy - Win32 Unicode Debug" && "$(CFG)" !=\
 "MtsSpy - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MTSSpy.mak" CFG="MtsSpy - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MtsSpy - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "MtsSpy - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MtsSpy - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MTSSpy.exe" "$(OUTDIR)\MTSSpy.bsc" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MTSSpy.exe" "$(OUTDIR)\MTSSpy.bsc" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MtsSpy.obj"
	-@erase "$(INTDIR)\MTSSpy.pch"
	-@erase "$(INTDIR)\MtsSpy.res"
	-@erase "$(INTDIR)\MtsSpy.sbr"
	-@erase "$(INTDIR)\SpyCon.obj"
	-@erase "$(INTDIR)\SpyCon.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MTSSpy.bsc"
	-@erase "$(OUTDIR)\MTSSpy.exe"
	-@erase "$(OUTDIR)\MTSSpy.ilk"
	-@erase "$(OUTDIR)\MTSSpy.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MTSSpy.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsSpy.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MTSSpy.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MtsSpy.sbr" \
	"$(INTDIR)\SpyCon.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\MTSSpy.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\MTSSpy.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\MTSSpy.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MtsSpy.obj" \
	"$(INTDIR)\MtsSpy.res" \
	"$(INTDIR)\SpyCon.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MTSSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\MTSSpy.exe
InputPath=.\DebugU\MTSSpy.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ELSEIF  "$(CFG)" == "MtsSpy - Win32 Unicode Release"

OUTDIR=.\MtsSpy__
INTDIR=.\MtsSpy__
# Begin Custom Macros
OutDir=.\MtsSpy__
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MTSSpy.exe" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MTSSpy.exe" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MtsSpy.obj"
	-@erase "$(INTDIR)\MTSSpy.pch"
	-@erase "$(INTDIR)\MtsSpy.res"
	-@erase "$(INTDIR)\SpyCon.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MTSSpy.exe"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\MTSSpy.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\MtsSpy__/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsSpy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MTSSpy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\MTSSpy.pdb" /machine:I386 /out:"$(OUTDIR)\MTSSpy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MtsSpy.obj" \
	"$(INTDIR)\MtsSpy.res" \
	"$(INTDIR)\SpyCon.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MTSSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\MtsSpy__
TargetPath=.\MtsSpy__\MTSSpy.exe
InputPath=.\MtsSpy__\MTSSpy.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ENDIF 


!IF "$(CFG)" == "MtsSpy - Win32 Unicode Debug" || "$(CFG)" ==\
 "MtsSpy - Win32 Unicode Release"
SOURCE=.\MtsSpy.cpp
DEP_CPP_MTSSP=\
	".\SpyCon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MTSSP=\
	".\MtsSpy.h"\
	".\MtsSpy_i.c"\
	".\MtsSpyCtl.h"\
	".\MtsSpyCtl_i.c"\
	

!IF  "$(CFG)" == "MtsSpy - Win32 Unicode Debug"


"$(INTDIR)\MtsSpy.obj"	"$(INTDIR)\MtsSpy.sbr" : $(SOURCE) $(DEP_CPP_MTSSP)\
 "$(INTDIR)" "$(INTDIR)\MTSSpy.pch" ".\MtsSpy.h" ".\MtsSpy_i.c"


!ELSEIF  "$(CFG)" == "MtsSpy - Win32 Unicode Release"


"$(INTDIR)\MtsSpy.obj" : $(SOURCE) $(DEP_CPP_MTSSP) "$(INTDIR)"\
 "$(INTDIR)\MTSSpy.pch" ".\MtsSpy.h" ".\MtsSpy_i.c"


!ENDIF 

SOURCE=.\MtsSpy.idl

!IF  "$(CFG)" == "MtsSpy - Win32 Unicode Debug"

InputPath=.\MtsSpy.idl

"MtsSpy.h"	"MtsSpy_i.c"	"MtsSpy.tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h ".\MtsSpy.h" /tlb ".\MtsSpy.tlb" /iid   ".\MtsSpy_i.c"\
      "MtsSpy.idl"

!ELSEIF  "$(CFG)" == "MtsSpy - Win32 Unicode Release"

InputPath=.\MtsSpy.idl

"MtsSpy.h"	"MtsSpy_i.c"	"MtsSpy.tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h ".\MtsSpy.h" /tlb ".\MtsSpy.tlb" /iid   ".\MtsSpy_i.c"\
      "MtsSpy.idl"

!ENDIF 

SOURCE=.\MtsSpy.rc
DEP_RSC_MTSSPY=\
	".\icon1.ico"\
	".\MtsSpy.rgs"\
	".\SpyCon.rgs"\
	
NODEP_RSC_MTSSPY=\
	".\MtsSpy.tlb"\
	

"$(INTDIR)\MtsSpy.res" : $(SOURCE) $(DEP_RSC_MTSSPY) "$(INTDIR)" ".\MtsSpy.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SpyCon.cpp
DEP_CPP_SPYCO=\
	".\SpyCon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SPYCO=\
	".\MtsSpy.h"\
	".\MtsSpyCtl.h"\
	

!IF  "$(CFG)" == "MtsSpy - Win32 Unicode Debug"


"$(INTDIR)\SpyCon.obj"	"$(INTDIR)\SpyCon.sbr" : $(SOURCE) $(DEP_CPP_SPYCO)\
 "$(INTDIR)" "$(INTDIR)\MTSSpy.pch" ".\MtsSpy.h"


!ELSEIF  "$(CFG)" == "MtsSpy - Win32 Unicode Release"


"$(INTDIR)\SpyCon.obj" : $(SOURCE) $(DEP_CPP_SPYCO) "$(INTDIR)"\
 "$(INTDIR)\MTSSpy.pch" ".\MtsSpy.h"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MtsSpy - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MTSSpy.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MTSSpy.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MtsSpy - Win32 Unicode Release"

CPP_SWITCHES=/nologo /ML /W3 /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\MTSSpy.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MTSSpy.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

