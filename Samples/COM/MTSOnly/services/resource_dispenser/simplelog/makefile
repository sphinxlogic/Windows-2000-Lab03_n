# Microsoft Developer Studio Generated NMAKE File, Based on SimpleLog.dsp
!IF "$(CFG)" == ""
CFG=SimpleLog - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to SimpleLog - Win32 Unicode\
 Debug.
!ENDIF 

!IF "$(CFG)" != "SimpleLog - Win32 Unicode Debug" && "$(CFG)" !=\
 "SimpleLog - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimpleLog.mak" CFG="SimpleLog - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimpleLog - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleLog - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SimpleLog - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SimpleLog.dll" "$(OUTDIR)\SimpleLog.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\SimpleLog.dll" "$(OUTDIR)\SimpleLog.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SimpleLog.obj"
	-@erase "$(INTDIR)\SimpleLog.pch"
	-@erase "$(INTDIR)\SimpleLog.res"
	-@erase "$(INTDIR)\SimpleLog.sbr"
	-@erase "$(INTDIR)\SimpleLogObj.obj"
	-@erase "$(INTDIR)\SimpleLogObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SimpleLog.bsc"
	-@erase "$(OUTDIR)\SimpleLog.dll"
	-@erase "$(OUTDIR)\SimpleLog.exp"
	-@erase "$(OUTDIR)\SimpleLog.ilk"
	-@erase "$(OUTDIR)\SimpleLog.lib"
	-@erase "$(OUTDIR)\SimpleLog.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\SimpleLog.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SimpleLog.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimpleLog.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\SimpleLog.sbr" \
	"$(INTDIR)\SimpleLogObj.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SimpleLog.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\SimpleLog.pdb" /debug /machine:I386 /def:".\SimpleLog.def"\
 /out:"$(OUTDIR)\SimpleLog.dll" /implib:"$(OUTDIR)\SimpleLog.lib" 
DEF_FILE= \
	".\SimpleLog.def"
LINK32_OBJS= \
	"$(INTDIR)\SimpleLog.obj" \
	"$(INTDIR)\SimpleLog.res" \
	"$(INTDIR)\SimpleLogObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SimpleLog.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\SimpleLog.dll
InputPath=.\DebugU\SimpleLog.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "SimpleLog - Win32 Unicode Release"

OUTDIR=.\SimpleLo
INTDIR=.\SimpleLo
# Begin Custom Macros
OutDir=.\SimpleLo
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SimpleLog.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\SimpleLog.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SimpleLog.obj"
	-@erase "$(INTDIR)\SimpleLog.pch"
	-@erase "$(INTDIR)\SimpleLog.res"
	-@erase "$(INTDIR)\SimpleLogObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SimpleLog.dll"
	-@erase "$(OUTDIR)\SimpleLog.exp"
	-@erase "$(OUTDIR)\SimpleLog.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\SimpleLog.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\SimpleLo/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SimpleLog.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimpleLog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=shell32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\SimpleLog.pdb" /machine:I386 /def:".\SimpleLog.def"\
 /out:"$(OUTDIR)\SimpleLog.dll" /implib:"$(OUTDIR)\SimpleLog.lib" 
DEF_FILE= \
	".\SimpleLog.def"
LINK32_OBJS= \
	"$(INTDIR)\SimpleLog.obj" \
	"$(INTDIR)\SimpleLog.res" \
	"$(INTDIR)\SimpleLogObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SimpleLog.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\SimpleLo
TargetPath=.\SimpleLo\SimpleLog.dll
InputPath=.\SimpleLo\SimpleLog.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "SimpleLog - Win32 Unicode Debug" || "$(CFG)" ==\
 "SimpleLog - Win32 Unicode Release"
SOURCE=.\SimpleLog.cpp

!IF  "$(CFG)" == "SimpleLog - Win32 Unicode Debug"

DEP_CPP_SIMPL=\
	"..\..\..\common\inc\simplelog.h"\
	"..\..\..\common\inc\simplelog_i.c"\
	".\resource.h"\
	".\SimpleLogObj.h"\
	

"$(INTDIR)\SimpleLog.obj"	"$(INTDIR)\SimpleLog.sbr" : $(SOURCE)\
 $(DEP_CPP_SIMPL) "$(INTDIR)" "$(INTDIR)\SimpleLog.pch"


!ELSEIF  "$(CFG)" == "SimpleLog - Win32 Unicode Release"

DEP_CPP_SIMPL=\
	"..\..\..\common\inc\simplelog.h"\
	"..\..\..\common\inc\simplelog_i.c"\
	".\resource.h"\
	".\SimpleLogObj.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SimpleLog.obj" : $(SOURCE) $(DEP_CPP_SIMPL) "$(INTDIR)"\
 "$(INTDIR)\SimpleLog.pch"


!ENDIF 

SOURCE=.\SimpleLog.rc
DEP_RSC_SIMPLE=\
	"..\..\..\common\inc\SimpleLog.tlb"\
	".\resource.h"\
	".\SimpleLogObj.rgs"\
	

"$(INTDIR)\SimpleLog.res" : $(SOURCE) $(DEP_RSC_SIMPLE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SimpleLogObj.cpp

!IF  "$(CFG)" == "SimpleLog - Win32 Unicode Debug"

DEP_CPP_SIMPLEL=\
	"..\..\..\common\inc\simplelog.h"\
	".\resource.h"\
	".\SimpleLogObj.h"\
	

"$(INTDIR)\SimpleLogObj.obj"	"$(INTDIR)\SimpleLogObj.sbr" : $(SOURCE)\
 $(DEP_CPP_SIMPLEL) "$(INTDIR)" "$(INTDIR)\SimpleLog.pch"


!ELSEIF  "$(CFG)" == "SimpleLog - Win32 Unicode Release"

DEP_CPP_SIMPLEL=\
	"..\..\..\common\inc\simplelog.h"\
	".\resource.h"\
	".\SimpleLogObj.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SimpleLogObj.obj" : $(SOURCE) $(DEP_CPP_SIMPLEL) "$(INTDIR)"\
 "$(INTDIR)\SimpleLog.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SimpleLog - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	"..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\include\qos.h"\
	"..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\include\winsmcrd.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\SimpleLog.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SimpleLog.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SimpleLog - Win32 Unicode Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\SimpleLog.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SimpleLog.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

