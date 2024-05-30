# Microsoft Developer Studio Generated NMAKE File, Based on SmbSmpEx.dsp
!IF "$(CFG)" == ""
CFG=SmbSmpEx - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SmbSmpEx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SmbSmpEx - Win32 Release" && "$(CFG)" != "SmbSmpEx - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmbSmpEx.mak" CFG="SmbSmpEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmbSmpEx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SmbSmpEx.dll" "$(OUTDIR)\ExtObjID.tlb" ".\ExtObjID.h"


CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\ExtObjID.tlb"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase ".\ExtObjID.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\SmbSmpEx.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /D "MIDL_PASS" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmpEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=clusapi.lib cluadmex.lib resutils.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SmbSmpEx.pdb" /machine:I386 /def:".\SmbSmpEx.def" /out:"$(OUTDIR)\SmbSmpEx.dll" /implib:"$(OUTDIR)\SmbSmpEx.lib" 
DEF_FILE= \
	".\SmbSmpEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\SmbSmpEx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SmbSmpEx.res"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SmbSmpEx.dll" "$(OUTDIR)\ExtObjID.tlb" "$(OUTDIR)\SmbSmpEx.bsc"


CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\BasePage.sbr"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\DDxDDv.sbr"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\ExtObj.sbr"
	-@erase "$(INTDIR)\ExtObjID.tlb"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\PropList.sbr"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\RegExt.sbr"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\ResProp.sbr"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\SmbSmpEx.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SmbSmpEx.bsc"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.ilk"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase "$(OUTDIR)\SmbSmpEx.pdb"
	-@erase ".\ExtObjID.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SmbSmpEx.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /D "MIDL_PASS" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmpEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmpEx.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BasePage.sbr" \
	"$(INTDIR)\DDxDDv.sbr" \
	"$(INTDIR)\ExtObj.sbr" \
	"$(INTDIR)\PropList.sbr" \
	"$(INTDIR)\RegExt.sbr" \
	"$(INTDIR)\ResProp.sbr" \
	"$(INTDIR)\SmbSmpEx.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SmbSmpEx.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=clusapi.lib cluadmex.lib resutils.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\SmbSmpEx.pdb" /debug /machine:I386 /def:".\SmbSmpEx.def" /out:"$(OUTDIR)\SmbSmpEx.dll" /implib:"$(OUTDIR)\SmbSmpEx.lib" /pdbtype:sept 
DEF_FILE= \
	".\SmbSmpEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\SmbSmpEx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SmbSmpEx.res"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SmbSmpEx.dep")
!INCLUDE "SmbSmpEx.dep"
!ELSE 
!MESSAGE Warning: cannot find "SmbSmpEx.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SmbSmpEx - Win32 Release" || "$(CFG)" == "SmbSmpEx - Win32 Debug"
SOURCE=.\BasePage.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"


"$(INTDIR)\BasePage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"


"$(INTDIR)\BasePage.obj"	"$(INTDIR)\BasePage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\DDxDDv.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"


"$(INTDIR)\DDxDDv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"


"$(INTDIR)\DDxDDv.obj"	"$(INTDIR)\DDxDDv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ENDIF 

SOURCE=.\ExtObj.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"


"$(INTDIR)\ExtObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"


"$(INTDIR)\ExtObj.obj"	"$(INTDIR)\ExtObj.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\ExtObjID.idl

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /D "MIDL_PASS" /tlb "$(OUTDIR)\ExtObjID.tlb" /h ".\ExtObjID.h" /mktyplib203 /win32 

"$(INTDIR)\ExtObjID.tlb"	".\ExtObjID.h" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /D "MIDL_PASS" /tlb "$(OUTDIR)\ExtObjID.tlb" /h ".\ExtObjID.h" /mktyplib203 /win32 

"$(INTDIR)\ExtObjID.tlb"	".\ExtObjID.h" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\PropList.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"


"$(INTDIR)\PropList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"


"$(INTDIR)\PropList.obj"	"$(INTDIR)\PropList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ENDIF 

SOURCE=.\RegExt.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"


"$(INTDIR)\RegExt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"


"$(INTDIR)\RegExt.obj"	"$(INTDIR)\RegExt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ENDIF 

SOURCE=.\ResProp.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"


"$(INTDIR)\ResProp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"


"$(INTDIR)\ResProp.obj"	"$(INTDIR)\ResProp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\SmbSmpEx.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"


"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"


"$(INTDIR)\SmbSmpEx.obj"	"$(INTDIR)\SmbSmpEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\SmbSmpEx.rc

"$(INTDIR)\SmbSmpEx.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\SmbSmpEx.pch" /Yc"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SmbSmpEx.pch" /Yc"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

