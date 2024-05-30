# Microsoft Developer Studio Generated NMAKE File, Based on ClipSrvEx.dsp
!IF "$(CFG)" == ""
CFG=ClipSrvEx - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ClipSrvEx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ClipSrvEx - Win32 Release" && "$(CFG)" != "ClipSrvEx - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClipSrvEx.mak" CFG="ClipSrvEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClipSrvEx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClipSrvEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ClipSrvEx.dll" "$(OUTDIR)\ExtObjID.tlb" ".\ExtObjID.h"


CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\ClipSrvEx.obj"
	-@erase "$(INTDIR)\ClipSrvEx.pch"
	-@erase "$(INTDIR)\ClipSrvEx.res"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\ExtObjID.tlb"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ClipSrvEx.dll"
	-@erase "$(OUTDIR)\ClipSrvEx.exp"
	-@erase "$(OUTDIR)\ClipSrvEx.lib"
	-@erase ".\ExtObjID.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\ClipSrvEx.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrvEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrvEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=clusapi.lib cluadmex.lib resutils.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ClipSrvEx.pdb" /machine:I386 /def:".\ClipSrvEx.def" /out:"$(OUTDIR)\ClipSrvEx.dll" /implib:"$(OUTDIR)\ClipSrvEx.lib" 
DEF_FILE= \
	".\ClipSrvEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\ClipSrvEx.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ClipSrvEx.res"

"$(OUTDIR)\ClipSrvEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ClipSrvEx.dll" "$(OUTDIR)\ExtObjID.tlb"


CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\ClipSrvEx.obj"
	-@erase "$(INTDIR)\ClipSrvEx.pch"
	-@erase "$(INTDIR)\ClipSrvEx.res"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\ExtObjID.tlb"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ClipSrvEx.dll"
	-@erase "$(OUTDIR)\ClipSrvEx.exp"
	-@erase "$(OUTDIR)\ClipSrvEx.ilk"
	-@erase "$(OUTDIR)\ClipSrvEx.lib"
	-@erase "$(OUTDIR)\ClipSrvEx.pdb"
	-@erase ".\ExtObjID.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\ClipSrvEx.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrvEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrvEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=clusapi.lib cluadmex.lib resutils.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ClipSrvEx.pdb" /debug /machine:I386 /def:".\ClipSrvEx.def" /out:"$(OUTDIR)\ClipSrvEx.dll" /implib:"$(OUTDIR)\ClipSrvEx.lib" /pdbtype:sept 
DEF_FILE= \
	".\ClipSrvEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\ClipSrvEx.obj" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ClipSrvEx.res"

"$(OUTDIR)\ClipSrvEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ClipSrvEx.dep")
!INCLUDE "ClipSrvEx.dep"
!ELSE 
!MESSAGE Warning: cannot find "ClipSrvEx.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ClipSrvEx - Win32 Release" || "$(CFG)" == "ClipSrvEx - Win32 Debug"
SOURCE=.\BasePage.cpp

"$(INTDIR)\BasePage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


SOURCE=.\ClipSrvEx.cpp

"$(INTDIR)\ClipSrvEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


SOURCE=.\ClipSrvEx.rc

"$(INTDIR)\ClipSrvEx.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DDxDDv.cpp

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


SOURCE=.\ExtObj.cpp

"$(INTDIR)\ExtObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


SOURCE=.\ExtObjID.idl

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /D "MIDL_PASS" /tlb "$(OUTDIR)\ExtObjID.tlb" /h ".\ExtObjID.h" /mktyplib203 /win32 

"$(INTDIR)\ExtObjID.tlb"	".\ExtObjID.h" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /D "MIDL_PASS" /tlb "$(OUTDIR)\ExtObjID.tlb" /h ".\ExtObjID.h" /mktyplib203 /win32 

"$(INTDIR)\ExtObjID.tlb"	".\ExtObjID.h" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\PropList.cpp

"$(INTDIR)\PropList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


SOURCE=.\RegExt.cpp

"$(INTDIR)\RegExt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


SOURCE=.\ResProp.cpp

"$(INTDIR)\ResProp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\ClipSrvEx.pch" /Yc"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ClipSrvEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\ClipSrvEx.pch" /Yc"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ClipSrvEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

