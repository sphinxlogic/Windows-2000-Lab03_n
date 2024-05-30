# Microsoft Developer Studio Generated NMAKE File, Based on SmbSmpEx.dsp
!IF "$(CFG)" == ""
CFG=SmbSmpEx - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SmbSmpEx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SmbSmpEx - Win32 Release" && "$(CFG)" !=\
 "SmbSmpEx - Win32 Debug" && "$(CFG)" != "SmbSmpEx - Win32 (ALPHA) Release" &&\
 "$(CFG)" != "SmbSmpEx - Win32 (ALPHA) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmbSmpEx.mak" CFG="SmbSmpEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmbSmpEx - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "SmbSmpEx - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
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
InputDir=.
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ELSE 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase "$(InputDir)\ExtObjID.h"
	-@erase "$(InputDir)\ExtObjID.tlb"
	-@erase "$(InputDir)\ExtObjID_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\SmbSmpEx.pch"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmpEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\SmbSmpEx.pdb" /machine:I386 /def:".\SmbSmpEx.def"\
 /out:"$(OUTDIR)\SmbSmpEx.dll" /implib:"$(OUTDIR)\SmbSmpEx.lib" 
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
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
InputDir=.
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ELSE 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.ilk"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase "$(OUTDIR)\SmbSmpEx.pdb"
	-@erase "$(InputDir)\ExtObjID.h"
	-@erase "$(InputDir)\ExtObjID.tlb"
	-@erase "$(InputDir)\ExtObjID_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmpEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmpEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\SmbSmpEx.pdb" /debug /machine:I386 /def:".\SmbSmpEx.def"\
 /out:"$(OUTDIR)\SmbSmpEx.dll" /implib:"$(OUTDIR)\SmbSmpEx.lib" 
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
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

OUTDIR=.\AlphaRel
INTDIR=.\AlphaRel
# Begin Custom Macros
InputDir=.
OutDir=.\.\AlphaRel
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ELSE 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase "$(InputDir)\ExtObjID.h"
	-@erase "$(InputDir)\ExtObjID.tlb"
	-@erase "$(InputDir)\ExtObjID_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmpEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmpEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\SmbSmpEx.pdb"\
 /machine:ALPHA /def:".\SmbSmpEx.def" /out:"$(OUTDIR)\SmbSmpEx.dll"\
 /implib:"$(OUTDIR)\SmbSmpEx.lib" 
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
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

OUTDIR=.\AlphaDbg
INTDIR=.\AlphaDbg
# Begin Custom Macros
InputDir=.
OutDir=.\.\AlphaDbg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ELSE 

ALL : "$(InputDir)\ExtObjID_i.c" "$(InputDir)\ExtObjID.tlb"\
 "$(InputDir)\ExtObjID.h" "$(OUTDIR)\SmbSmpEx.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BasePage.obj"
	-@erase "$(INTDIR)\DDxDDv.obj"
	-@erase "$(INTDIR)\ExtObj.obj"
	-@erase "$(INTDIR)\PropList.obj"
	-@erase "$(INTDIR)\RegExt.obj"
	-@erase "$(INTDIR)\ResProp.obj"
	-@erase "$(INTDIR)\SmbSmpEx.obj"
	-@erase "$(INTDIR)\SmbSmpEx.pch"
	-@erase "$(INTDIR)\SmbSmpEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SmbSmpEx.dll"
	-@erase "$(OUTDIR)\SmbSmpEx.exp"
	-@erase "$(OUTDIR)\SmbSmpEx.lib"
	-@erase "$(OUTDIR)\SmbSmpEx.pdb"
	-@erase "$(InputDir)\ExtObjID.h"
	-@erase "$(InputDir)\ExtObjID.tlb"
	-@erase "$(InputDir)\ExtObjID_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmpEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmpEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmpEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\SmbSmpEx.pdb"\
 /debug /machine:ALPHA /def:".\SmbSmpEx.def" /out:"$(OUTDIR)\SmbSmpEx.dll"\
 /implib:"$(OUTDIR)\SmbSmpEx.lib" 
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
	"$(INTDIR)\SmbSmpEx.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SmbSmpEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SmbSmpEx - Win32 Release" || "$(CFG)" ==\
 "SmbSmpEx - Win32 Debug" || "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release" ||\
 "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"
SOURCE=.\BasePage.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_BASEP=\
	".\BasePage.h"\
	".\BasePage.inl"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\BasePage.obj" : $(SOURCE) $(DEP_CPP_BASEP) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\DDxDDv.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_DDXDD=\
	".\DDxDDv.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\DDxDDv.obj" : $(SOURCE) $(DEP_CPP_DDXDD) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ENDIF 

SOURCE=.\ExtObj.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_EXTOB=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ExtObj.obj" : $(SOURCE) $(DEP_CPP_EXTOB) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\ExtObjID.idl

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

InputDir=.
InputPath=.\ExtObjID.idl
InputName=ExtObjID

"$(InputDir)\$(InputName).h"	"$(InputDir)\$(InputName)_i.c"\
	"$(InputDir)\$(InputName).tlb"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) -DMIDL_PASS /header $(InputDir)\$(InputName).h /iid\
  $(InputDir)\$(InputName)_i.c /tlb $(InputDir)\$(InputName).tlb

!ENDIF 

SOURCE=.\PropList.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_PROPL=\
	".\PropList.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\PropList.obj" : $(SOURCE) $(DEP_CPP_PROPL) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ENDIF 

SOURCE=.\RegExt.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_REGEX=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\RegExt.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch"


!ENDIF 

SOURCE=.\ResProp.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_RESPR=\
	".\BasePage.h"\
	".\DDxDDv.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\PropList.h"\
	".\ResProp.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\ResProp.obj" : $(SOURCE) $(DEP_CPP_RESPR) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\SmbSmpEx.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_SMBSM=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID_i.c" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_SMBSM=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID_i.c" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_SMBSM=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID_i.c" ".\ExtObjID.h"


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_SMBSM=\
	".\BasePage.h"\
	".\ExtObj.h"\
	".\ExtObjID.h"\
	".\ExtObjID_i.c"\
	".\PropList.h"\
	".\RegExt.h"\
	".\SmbSmpEx.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"CluAdmEx.h"\
	{$(INCLUDE)}"clusapi.h"\
	

"$(INTDIR)\SmbSmpEx.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"\
 "$(INTDIR)\SmbSmpEx.pch" ".\ExtObjID_i.c" ".\ExtObjID.h"


!ENDIF 

SOURCE=.\SmbSmpEx.rc
DEP_RSC_SMBSMP=\
	".\res\SmbSmpEx.rc2"\
	

"$(INTDIR)\SmbSmpEx.res" : $(SOURCE) $(DEP_RSC_SMBSMP) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SmbSmpEx - Win32 Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmpEx.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmpEx.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmpEx.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SmbSmpEx - Win32 (ALPHA) Debug"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	{$(INCLUDE)}"clusapi.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmpEx.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SmbSmpEx.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

