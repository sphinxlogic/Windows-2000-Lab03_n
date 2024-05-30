# Microsoft Developer Studio Generated NMAKE File, Based on ClipSrvEx.dsp
!IF "$(CFG)" == ""
CFG=ClipSrvEx - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ClipSrvEx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ClipSrvEx - Win32 Release" && "$(CFG)" !=\
 "ClipSrvEx - Win32 Debug" && "$(CFG)" != "ClipSrvEx - Win32 (ALPHA) Release" &&\
 "$(CFG)" != "ClipSrvEx - Win32 (ALPHA) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClipSrvEx.mak" CFG="ClipSrvEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClipSrvEx - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClipSrvEx - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClipSrvEx - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ClipSrvEx - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
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
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"

!ELSE 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\ClipSrvEx.obj"
	-@erase "$(INTDIR)\ClipSrvEx.pch"
	-@erase "$(INTDIR)\ClipSrvEx.res"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ClipSrvEx.dll"
	-@erase "$(OUTDIR)\ClipSrvEx.exp"
	-@erase "$(OUTDIR)\ClipSrvEx.lib"
	-@erase "$(InputDir)\$(InputName).h"
	-@erase "$(InputDir)\$(InputName).tlb"
	-@erase "$(InputDir)\$(InputName)_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\ClipSrvEx.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrvEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrvEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\ClipSrvEx.pdb" /machine:I386 /def:".\ClipSrvEx.def"\
 /out:"$(OUTDIR)\ClipSrvEx.dll" /implib:"$(OUTDIR)\ClipSrvEx.lib" 
DEF_FILE= \
	".\ClipSrvEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\ClipSrvEx.obj" \
	"$(INTDIR)\ClipSrvEx.res" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ClipSrvEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"\
 "$(OUTDIR)\ClipSrvEx.bsc"

!ELSE 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"\
 "$(OUTDIR)\ClipSrvEx.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\BasePage.sbr"
	-@erase "$(INTDIR)\ClipSrvEx.obj"
	-@erase "$(INTDIR)\ClipSrvEx.pch"
	-@erase "$(INTDIR)\ClipSrvEx.res"
	-@erase "$(INTDIR)\ClipSrvEx.sbr"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\DDxDDv.sbr"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\ExtObj.sbr"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\PropList.sbr"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\RegExt.sbr"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\ResProp.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ClipSrvEx.bsc"
	-@erase "$(OUTDIR)\ClipSrvEx.dll"
	-@erase "$(OUTDIR)\ClipSrvEx.exp"
	-@erase "$(OUTDIR)\ClipSrvEx.ilk"
	-@erase "$(OUTDIR)\ClipSrvEx.lib"
	-@erase "$(OUTDIR)\ClipSrvEx.pdb"
	-@erase "$(InputDir)\$(InputName).h"
	-@erase "$(InputDir)\$(InputName).tlb"
	-@erase "$(InputDir)\$(InputName)_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ClipSrvEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrvEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrvEx.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BasePage.sbr" \
	"$(INTDIR)\ClipSrvEx.sbr" \
	"$(INTDIR)\DDxDDv.sbr" \
	"$(INTDIR)\ExtObj.sbr" \
	"$(INTDIR)\PropList.sbr" \
	"$(INTDIR)\RegExt.sbr" \
	"$(INTDIR)\ResProp.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ClipSrvEx.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\ClipSrvEx.pdb" /debug /machine:I386 /def:".\ClipSrvEx.def"\
 /out:"$(OUTDIR)\ClipSrvEx.dll" /implib:"$(OUTDIR)\ClipSrvEx.lib" 
DEF_FILE= \
	".\ClipSrvEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\ClipSrvEx.obj" \
	"$(INTDIR)\ClipSrvEx.res" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ClipSrvEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

OUTDIR=.\AlphaRel
INTDIR=.\AlphaRel
# Begin Custom Macros
OutDir=.\.\AlphaRel
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"

!ELSE 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\ClipSrvEx.obj"
	-@erase "$(INTDIR)\ClipSrvEx.pch"
	-@erase "$(INTDIR)\ClipSrvEx.res"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ClipSrvEx.dll"
	-@erase "$(OUTDIR)\ClipSrvEx.exp"
	-@erase "$(OUTDIR)\ClipSrvEx.lib"
	-@erase "$(InputDir)\$(InputName).h"
	-@erase "$(InputDir)\$(InputName).tlb"
	-@erase "$(InputDir)\$(InputName)_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\ClipSrvEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\AlphaRel/
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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrvEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrvEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\ClipSrvEx.pdb"\
 /machine:ALPHA /def:".\ClipSrvEx.def" /out:"$(OUTDIR)\ClipSrvEx.dll"\
 /implib:"$(OUTDIR)\ClipSrvEx.lib" 
DEF_FILE= \
	".\ClipSrvEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\ClipSrvEx.obj" \
	"$(INTDIR)\ClipSrvEx.res" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ClipSrvEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

OUTDIR=.\AlphaDbg
INTDIR=.\AlphaDbg
# Begin Custom Macros
OutDir=.\.\AlphaDbg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"

!ELSE 

ALL : "$(InputDir)\$(InputName)_i.c" "$(InputDir)\$(InputName).tlb"\
 "$(InputDir)\$(InputName).h" "$(OUTDIR)\ClipSrvEx.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\ClipSrvEx.obj"
	-@erase "$(INTDIR)\ClipSrvEx.pch"
	-@erase "$(INTDIR)\ClipSrvEx.res"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ClipSrvEx.dll"
	-@erase "$(OUTDIR)\ClipSrvEx.exp"
	-@erase "$(OUTDIR)\ClipSrvEx.lib"
	-@erase "$(OUTDIR)\ClipSrvEx.pdb"
	-@erase "$(InputDir)\$(InputName).h"
	-@erase "$(InputDir)\$(InputName).tlb"
	-@erase "$(InputDir)\$(InputName)_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\ClipSrvEx.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /MDd /c 
CPP_OBJS=.\AlphaDbg/
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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrvEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrvEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\ClipSrvEx.pdb"\
 /debug /machine:ALPHA /def:".\ClipSrvEx.def" /out:"$(OUTDIR)\ClipSrvEx.dll"\
 /implib:"$(OUTDIR)\ClipSrvEx.lib" 
DEF_FILE= \
	".\ClipSrvEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BasePage.obj" \
	"$(INTDIR)\ClipSrvEx.obj" \
	"$(INTDIR)\ClipSrvEx.res" \
	"$(INTDIR)\DDxDDv.obj" \
	"$(INTDIR)\ExtObj.obj" \
	"$(INTDIR)\PropList.obj" \
	"$(INTDIR)\RegExt.obj" \
	"$(INTDIR)\ResProp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ClipSrvEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "ClipSrvEx - Win32 Release" || "$(CFG)" ==\
 "ClipSrvEx - Win32 Debug" || "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release" ||\
 "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"
SOURCE=.\BasePage.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj"	"$(INTDIR)\BasePage.sbr" : $(SOURCE) $(DEP_CPP_BASEP)\
 "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\ClipSrvEx.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_CLIPS=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ClipSrvEx.obj" : $(SOURCE) $(DEP_CPP_CLIPS) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID_i.c" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_CLIPS=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ClipSrvEx.obj"	"$(INTDIR)\ClipSrvEx.sbr" : $(SOURCE)\
 $(DEP_CPP_CLIPS) "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID_i.c"\
 ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_CLIPS=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ClipSrvEx.obj" : $(SOURCE) $(DEP_CPP_CLIPS) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID_i.c" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_CLIPS=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ClipSrvEx.obj" : $(SOURCE) $(DEP_CPP_CLIPS) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID_i.c" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\ClipSrvEx.rc
DEP_RSC_CLIPSR=\
	".\res\ClipSrvEx.rc2"\
	

"$(INTDIR)\ClipSrvEx.res" : $(SOURCE) $(DEP_RSC_CLIPSR) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DDxDDv.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj"	"$(INTDIR)\DDxDDv.sbr" : $(SOURCE) $(DEP_CPP_DDXDD)\
 "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ENDIF 

SOURCE=.\ExtObj.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj"	"$(INTDIR)\ExtObj.sbr" : $(SOURCE) $(DEP_CPP_EXTOB)\
 "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ClipSrvEx.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\ExtObjID.idl

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ENDIF 

SOURCE=.\PropList.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj"	"$(INTDIR)\PropList.sbr" : $(SOURCE) $(DEP_CPP_PROPL)\
 "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ENDIF 

SOURCE=.\RegExt.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj"	"$(INTDIR)\RegExt.sbr" : $(SOURCE) $(DEP_CPP_REGEX)\
 "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch"


!ENDIF 

SOURCE=.\ResProp.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj"	"$(INTDIR)\ResProp.sbr" : $(SOURCE) $(DEP_CPP_RESPR)\
 "$(INTDIR)" "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ClipSrvEx.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\ClipSrvEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ClipSrvEx - Win32 Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\ClipSrvEx.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ClipSrvEx.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ClipSrvEx.pch" /Yc /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ClipSrvEx.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\ClipSrvEx.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ClipSrvEx.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ClipSrvEx - Win32 (ALPHA) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\ClipSrvEx.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /MDd /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ClipSrvEx.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

