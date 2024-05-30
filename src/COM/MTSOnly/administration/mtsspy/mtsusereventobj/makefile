# Microsoft Developer Studio Generated NMAKE File, Based on MtsUserEventObj.dsp
!IF "$(CFG)" == ""
CFG=MtsUserEventObj - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to MtsUserEventObj - Win32\
 Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "MtsUserEventObj - Win32 Unicode Debug" && "$(CFG)" !=\
 "MtsUserEventObj - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MtsUserEventObj.mak"\
 CFG="MtsUserEventObj - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MtsUserEventObj - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MtsUserEventObj - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MtsUserEventObj.dll" "$(OUTDIR)\MtsUserEventObj.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MtsUserEventObj.dll" "$(OUTDIR)\MtsUserEventObj.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MtsUserEventData.obj"
	-@erase "$(INTDIR)\MtsUserEventData.sbr"
	-@erase "$(INTDIR)\MtsUserEventObj.obj"
	-@erase "$(INTDIR)\MtsUserEventObj.pch"
	-@erase "$(INTDIR)\MtsUserEventObj.res"
	-@erase "$(INTDIR)\MtsUserEventObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MtsUserEventObj.bsc"
	-@erase "$(OUTDIR)\MtsUserEventObj.dll"
	-@erase "$(OUTDIR)\MtsUserEventObj.exp"
	-@erase "$(OUTDIR)\MtsUserEventObj.ilk"
	-@erase "$(OUTDIR)\MtsUserEventObj.lib"
	-@erase "$(OUTDIR)\MtsUserEventObj.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\MtsUserEventObj.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsUserEventObj.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsUserEventObj.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MtsUserEventData.sbr" \
	"$(INTDIR)\MtsUserEventObj.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\MtsUserEventObj.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\MtsUserEventObj.pdb" /debug /machine:I386\
 /def:".\MtsUserEventObj.def" /out:"$(OUTDIR)\MtsUserEventObj.dll"\
 /implib:"$(OUTDIR)\MtsUserEventObj.lib" /pdbtype:sept 
DEF_FILE= \
	".\MtsUserEventObj.def"
LINK32_OBJS= \
	"$(INTDIR)\MtsUserEventData.obj" \
	"$(INTDIR)\MtsUserEventObj.obj" \
	"$(INTDIR)\MtsUserEventObj.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MtsUserEventObj.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\MtsUserEventObj.dll
InputPath=.\DebugU\MtsUserEventObj.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Release"

OUTDIR=.\MtsUserE
INTDIR=.\MtsUserE
# Begin Custom Macros
OutDir=.\MtsUserE
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MtsUserEventObj.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MtsUserEventObj.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MtsUserEventData.obj"
	-@erase "$(INTDIR)\MtsUserEventObj.obj"
	-@erase "$(INTDIR)\MtsUserEventObj.pch"
	-@erase "$(INTDIR)\MtsUserEventObj.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MtsUserEventObj.dll"
	-@erase "$(OUTDIR)\MtsUserEventObj.exp"
	-@erase "$(OUTDIR)\MtsUserEventObj.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\MtsUserEventObj.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\MtsUserE/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsUserEventObj.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsUserEventObj.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\MtsUserEventObj.pdb" /machine:I386 /def:".\MtsUserEventObj.def"\
 /out:"$(OUTDIR)\MtsUserEventObj.dll" /implib:"$(OUTDIR)\MtsUserEventObj.lib" 
DEF_FILE= \
	".\MtsUserEventObj.def"
LINK32_OBJS= \
	"$(INTDIR)\MtsUserEventData.obj" \
	"$(INTDIR)\MtsUserEventObj.obj" \
	"$(INTDIR)\MtsUserEventObj.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MtsUserEventObj.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\MtsUserE
TargetPath=.\MtsUserE\MtsUserEventObj.dll
InputPath=.\MtsUserE\MtsUserEventObj.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "MtsUserEventObj - Win32 Unicode Debug" || "$(CFG)" ==\
 "MtsUserEventObj - Win32 Unicode Release"
SOURCE=.\dlldatax.c
SOURCE=.\MtsUserEventData.cpp
DEP_CPP_MTSUS=\
	".\MtsUserEventData.h"\
	".\MtsUserEventObj.h"\
	".\StdAfx.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	"\Administration\mtsspy\inc\mtsevents_i.c"\
	

!IF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Debug"


"$(INTDIR)\MtsUserEventData.obj"	"$(INTDIR)\MtsUserEventData.sbr" : $(SOURCE)\
 $(DEP_CPP_MTSUS) "$(INTDIR)" "$(INTDIR)\MtsUserEventObj.pch"


!ELSEIF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Release"


"$(INTDIR)\MtsUserEventData.obj" : $(SOURCE) $(DEP_CPP_MTSUS) "$(INTDIR)"\
 "$(INTDIR)\MtsUserEventObj.pch"


!ENDIF 

SOURCE=.\MtsUserEventObj.cpp
DEP_CPP_MTSUSE=\
	".\MtsUserEventData.h"\
	".\MtsUserEventObj.h"\
	".\StdAfx.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	
NODEP_CPP_MTSUSE=\
	".\MtsUserEventObj_i.c"\
	

!IF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Debug"


"$(INTDIR)\MtsUserEventObj.obj"	"$(INTDIR)\MtsUserEventObj.sbr" : $(SOURCE)\
 $(DEP_CPP_MTSUSE) "$(INTDIR)" "$(INTDIR)\MtsUserEventObj.pch"


!ELSEIF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Release"


"$(INTDIR)\MtsUserEventObj.obj" : $(SOURCE) $(DEP_CPP_MTSUSE) "$(INTDIR)"\
 "$(INTDIR)\MtsUserEventObj.pch"


!ENDIF 

SOURCE=.\MtsUserEventObj.rc
DEP_RSC_MTSUSER=\
	".\MtsUserEventData.rgs"\
	
NODEP_RSC_MTSUSER=\
	".\inc\MtsUserEventObj.tlb"\
	

"$(INTDIR)\MtsUserEventObj.res" : $(SOURCE) $(DEP_RSC_MTSUSER) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\MtsUserEventObj.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MtsUserEventObj.pch" :\
 $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MtsUserEventObj - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\MtsUserEventObj.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MtsUserEventObj.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

