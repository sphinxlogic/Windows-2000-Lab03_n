# Microsoft Developer Studio Generated NMAKE File, Based on RmWorker.dsp
!IF "$(CFG)" == ""
CFG=RmWorker - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to RmWorker - Win32 Unicode\
 Debug.
!ENDIF 

!IF "$(CFG)" != "RmWorker - Win32 Unicode Debug" && "$(CFG)" !=\
 "RmWorker - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RmWorker.mak" CFG="RmWorker - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RmWorker - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RmWorker - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RmWorker - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RmWorker.dll" "$(OUTDIR)\RmWorker.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\RmWorker.dll" "$(OUTDIR)\RmWorker.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ACTION.OBJ"
	-@erase "$(INTDIR)\ACTION.SBR"
	-@erase "$(INTDIR)\irmworkerpriv.obj"
	-@erase "$(INTDIR)\irmworkerpriv.sbr"
	-@erase "$(INTDIR)\RmWorker.obj"
	-@erase "$(INTDIR)\RmWorker.pch"
	-@erase "$(INTDIR)\RmWorker.res"
	-@erase "$(INTDIR)\RmWorker.sbr"
	-@erase "$(INTDIR)\RmWorkerObj.obj"
	-@erase "$(INTDIR)\RmWorkerObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\RmWorker.bsc"
	-@erase "$(OUTDIR)\RmWorker.dll"
	-@erase "$(OUTDIR)\RmWorker.exp"
	-@erase "$(OUTDIR)\RmWorker.ilk"
	-@erase "$(OUTDIR)\RmWorker.lib"
	-@erase "$(OUTDIR)\RmWorker.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc ..\dtc\inc" /I "..\inc" /I\
 "..\dtc\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\RmWorker.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RmWorker.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RmWorker.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ACTION.SBR" \
	"$(INTDIR)\irmworkerpriv.sbr" \
	"$(INTDIR)\RmWorker.sbr" \
	"$(INTDIR)\RmWorkerObj.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\RmWorker.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=xolehlp.lib rpcrt4.lib shell32.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\RmWorker.pdb" /debug /machine:I386\
 /def:".\RmWorker.def" /out:"$(OUTDIR)\RmWorker.dll"\
 /implib:"$(OUTDIR)\RmWorker.lib" /libpath:"..\dtc\lib" 
DEF_FILE= \
	".\RmWorker.def"
LINK32_OBJS= \
	"$(INTDIR)\ACTION.OBJ" \
	"$(INTDIR)\irmworkerpriv.obj" \
	"$(INTDIR)\RmWorker.obj" \
	"$(INTDIR)\RmWorker.res" \
	"$(INTDIR)\RmWorkerObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\RmWorker.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\RmWorker.dll
InputPath=.\DebugU\RmWorker.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "RmWorker - Win32 Unicode Release"

OUTDIR=.\RmWorker
INTDIR=.\RmWorker
# Begin Custom Macros
OutDir=.\RmWorker
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RmWorker.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\RmWorker.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ACTION.OBJ"
	-@erase "$(INTDIR)\irmworkerpriv.obj"
	-@erase "$(INTDIR)\RmWorker.obj"
	-@erase "$(INTDIR)\RmWorker.pch"
	-@erase "$(INTDIR)\RmWorker.res"
	-@erase "$(INTDIR)\RmWorkerObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\RmWorker.dll"
	-@erase "$(OUTDIR)\RmWorker.exp"
	-@erase "$(OUTDIR)\RmWorker.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\inc" /I "..\dtc\inc" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\RmWorker.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\RmWorker/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RmWorker.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RmWorker.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=xolehlp.lib rpcrt4.lib shell32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\RmWorker.pdb" /machine:I386\
 /def:".\RmWorker.def" /out:"$(OUTDIR)\RmWorker.dll"\
 /implib:"$(OUTDIR)\RmWorker.lib" /libpath:"..\dtc\lib" 
DEF_FILE= \
	".\RmWorker.def"
LINK32_OBJS= \
	"$(INTDIR)\ACTION.OBJ" \
	"$(INTDIR)\irmworkerpriv.obj" \
	"$(INTDIR)\RmWorker.obj" \
	"$(INTDIR)\RmWorker.res" \
	"$(INTDIR)\RmWorkerObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\RmWorker.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\RmWorker
TargetPath=.\RmWorker\RmWorker.dll
InputPath=.\RmWorker\RmWorker.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "RmWorker - Win32 Unicode Debug" || "$(CFG)" ==\
 "RmWorker - Win32 Unicode Release"
SOURCE=.\ACTION.CPP

!IF  "$(CFG)" == "RmWorker - Win32 Unicode Debug"

DEP_CPP_ACTIO=\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	".\ACTION.H"\
	

"$(INTDIR)\ACTION.OBJ"	"$(INTDIR)\ACTION.SBR" : $(SOURCE) $(DEP_CPP_ACTIO)\
 "$(INTDIR)" "$(INTDIR)\RmWorker.pch"


!ELSEIF  "$(CFG)" == "RmWorker - Win32 Unicode Release"

DEP_CPP_ACTIO=\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	".\ACTION.H"\
	".\StdAfx.h"\
	

"$(INTDIR)\ACTION.OBJ" : $(SOURCE) $(DEP_CPP_ACTIO) "$(INTDIR)"\
 "$(INTDIR)\RmWorker.pch"


!ENDIF 

SOURCE=.\irmworkerpriv.cpp

!IF  "$(CFG)" == "RmWorker - Win32 Unicode Debug"

DEP_CPP_IRMWO=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	".\ACTION.H"\
	".\resource.h"\
	".\RmWorkerObj.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\irmworkerpriv.obj"	"$(INTDIR)\irmworkerpriv.sbr" : $(SOURCE)\
 $(DEP_CPP_IRMWO) "$(INTDIR)" "$(INTDIR)\RmWorker.pch"


!ELSEIF  "$(CFG)" == "RmWorker - Win32 Unicode Release"

DEP_CPP_IRMWO=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	".\ACTION.H"\
	".\resource.h"\
	".\RmWorkerObj.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\irmworkerpriv.obj" : $(SOURCE) $(DEP_CPP_IRMWO) "$(INTDIR)"\
 "$(INTDIR)\RmWorker.pch"


!ENDIF 

SOURCE=.\RmWorker.cpp

!IF  "$(CFG)" == "RmWorker - Win32 Unicode Debug"

DEP_CPP_RMWOR=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\copyfilerm_i.c"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\rmworker_i.c"\
	"..\..\..\common\inc\simplelog.h"\
	".\ACTION.H"\
	".\resource.h"\
	".\RmWorkerObj.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\RmWorker.obj"	"$(INTDIR)\RmWorker.sbr" : $(SOURCE) $(DEP_CPP_RMWOR)\
 "$(INTDIR)" "$(INTDIR)\RmWorker.pch"


!ELSEIF  "$(CFG)" == "RmWorker - Win32 Unicode Release"

DEP_CPP_RMWOR=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\copyfilerm_i.c"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\rmworker_i.c"\
	"..\..\..\common\inc\simplelog.h"\
	".\ACTION.H"\
	".\resource.h"\
	".\RmWorkerObj.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\RmWorker.obj" : $(SOURCE) $(DEP_CPP_RMWOR) "$(INTDIR)"\
 "$(INTDIR)\RmWorker.pch"


!ENDIF 

SOURCE=.\RmWorker.rc
DEP_RSC_RMWORK=\
	"..\..\..\common\inc\RmWorker.tlb"\
	".\resource.h"\
	".\RmWorkerObj.rgs"\
	

"$(INTDIR)\RmWorker.res" : $(SOURCE) $(DEP_RSC_RMWORK) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\RmWorkerObj.cpp

!IF  "$(CFG)" == "RmWorker - Win32 Unicode Debug"

DEP_CPP_RMWORKE=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	"..\..\..\common\inc\simplelog_i.c"\
	".\ACTION.H"\
	".\resource.h"\
	".\RmWorkerObj.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\RmWorkerObj.obj"	"$(INTDIR)\RmWorkerObj.sbr" : $(SOURCE)\
 $(DEP_CPP_RMWORKE) "$(INTDIR)" "$(INTDIR)\RmWorker.pch"


!ELSEIF  "$(CFG)" == "RmWorker - Win32 Unicode Release"

DEP_CPP_RMWORKE=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	"..\..\..\common\inc\simplelog_i.c"\
	".\ACTION.H"\
	".\resource.h"\
	".\RmWorkerObj.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\RmWorkerObj.obj" : $(SOURCE) $(DEP_CPP_RMWORKE) "$(INTDIR)"\
 "$(INTDIR)\RmWorker.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "RmWorker - Win32 Unicode Debug"

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
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc ..\dtc\inc" /I\
 "..\inc" /I "..\dtc\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D\
 "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\RmWorker.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\RmWorker.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RmWorker - Win32 Unicode Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\inc" /I "..\dtc\inc" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\RmWorker.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RmWorker.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

