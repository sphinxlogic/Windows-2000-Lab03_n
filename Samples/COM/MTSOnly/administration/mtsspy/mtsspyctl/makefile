# Microsoft Developer Studio Generated NMAKE File, Based on MtsSpyCtl.dsp
!IF "$(CFG)" == ""
CFG=MtsSpyCtl - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to MtsSpyCtl - Win32 Unicode\
 Debug.
!ENDIF 

!IF "$(CFG)" != "MtsSpyCtl - Win32 Unicode Debug" && "$(CFG)" !=\
 "MtsSpyCtl - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MtsSpyCtl.mak" CFG="MtsSpyCtl - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MtsSpyCtl - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MtsSpyCtl - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MtsSpyCtl.dll" "$(OUTDIR)\MtsSpyCtl.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MtsSpyCtl.dll" "$(OUTDIR)\MtsSpyCtl.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MethodSink.obj"
	-@erase "$(INTDIR)\MethodSink.sbr"
	-@erase "$(INTDIR)\MtsSink.obj"
	-@erase "$(INTDIR)\MtsSink.sbr"
	-@erase "$(INTDIR)\MtsSpy.obj"
	-@erase "$(INTDIR)\MtsSpy.sbr"
	-@erase "$(INTDIR)\MtsSpyCtl.obj"
	-@erase "$(INTDIR)\MtsSpyCtl.pch"
	-@erase "$(INTDIR)\MtsSpyCtl.res"
	-@erase "$(INTDIR)\MtsSpyCtl.sbr"
	-@erase "$(INTDIR)\MtsSpyPropPage.obj"
	-@erase "$(INTDIR)\MtsSpyPropPage.sbr"
	-@erase "$(INTDIR)\ResourceSink.obj"
	-@erase "$(INTDIR)\ResourceSink.sbr"
	-@erase "$(INTDIR)\SelectEventsDlg.obj"
	-@erase "$(INTDIR)\SelectEventsDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TxSink.obj"
	-@erase "$(INTDIR)\TxSink.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MtsSpyCtl.bsc"
	-@erase "$(OUTDIR)\MtsSpyCtl.dll"
	-@erase "$(OUTDIR)\MtsSpyCtl.exp"
	-@erase "$(OUTDIR)\MtsSpyCtl.ilk"
	-@erase "$(OUTDIR)\MtsSpyCtl.lib"
	-@erase "$(OUTDIR)\MtsSpyCtl.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\MtsSpyCtl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsSpyCtl.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsSpyCtl.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MethodSink.sbr" \
	"$(INTDIR)\MtsSink.sbr" \
	"$(INTDIR)\MtsSpy.sbr" \
	"$(INTDIR)\MtsSpyCtl.sbr" \
	"$(INTDIR)\MtsSpyPropPage.sbr" \
	"$(INTDIR)\ResourceSink.sbr" \
	"$(INTDIR)\SelectEventsDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TxSink.sbr"

"$(OUTDIR)\MtsSpyCtl.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=comdlg32.lib shell32.lib rpcrt4.lib /nologo /subsystem:windows\
 /dll /incremental:yes /pdb:"$(OUTDIR)\MtsSpyCtl.pdb" /debug /machine:I386\
 /def:".\MtsSpyCtl.def" /out:"$(OUTDIR)\MtsSpyCtl.dll"\
 /implib:"$(OUTDIR)\MtsSpyCtl.lib" /pdbtype:sept 
DEF_FILE= \
	".\MtsSpyCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\MethodSink.obj" \
	"$(INTDIR)\MtsSink.obj" \
	"$(INTDIR)\MtsSpy.obj" \
	"$(INTDIR)\MtsSpyCtl.obj" \
	"$(INTDIR)\MtsSpyCtl.res" \
	"$(INTDIR)\MtsSpyPropPage.obj" \
	"$(INTDIR)\ResourceSink.obj" \
	"$(INTDIR)\SelectEventsDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxSink.obj"

"$(OUTDIR)\MtsSpyCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\MtsSpyCtl.dll
InputPath=.\DebugU\MtsSpyCtl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"

OUTDIR=.\MtsSpyCt
INTDIR=.\MtsSpyCt
# Begin Custom Macros
OutDir=.\MtsSpyCt
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MtsSpyCtl.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\MtsSpyCtl.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MethodSink.obj"
	-@erase "$(INTDIR)\MtsSink.obj"
	-@erase "$(INTDIR)\MtsSpy.obj"
	-@erase "$(INTDIR)\MtsSpyCtl.obj"
	-@erase "$(INTDIR)\MtsSpyCtl.pch"
	-@erase "$(INTDIR)\MtsSpyCtl.res"
	-@erase "$(INTDIR)\MtsSpyPropPage.obj"
	-@erase "$(INTDIR)\ResourceSink.obj"
	-@erase "$(INTDIR)\SelectEventsDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxSink.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MtsSpyCtl.dll"
	-@erase "$(OUTDIR)\MtsSpyCtl.exp"
	-@erase "$(OUTDIR)\MtsSpyCtl.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL"\
 /Fp"$(INTDIR)\MtsSpyCtl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\MtsSpyCt/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MtsSpyCtl.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsSpyCtl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comdlg32.lib shell32.lib rpcrt4.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)\MtsSpyCtl.pdb" /machine:I386\
 /def:".\MtsSpyCtl.def" /out:"$(OUTDIR)\MtsSpyCtl.dll"\
 /implib:"$(OUTDIR)\MtsSpyCtl.lib" 
DEF_FILE= \
	".\MtsSpyCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\MethodSink.obj" \
	"$(INTDIR)\MtsSink.obj" \
	"$(INTDIR)\MtsSpy.obj" \
	"$(INTDIR)\MtsSpyCtl.obj" \
	"$(INTDIR)\MtsSpyCtl.res" \
	"$(INTDIR)\MtsSpyPropPage.obj" \
	"$(INTDIR)\ResourceSink.obj" \
	"$(INTDIR)\SelectEventsDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxSink.obj"

"$(OUTDIR)\MtsSpyCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\MtsSpyCt
TargetPath=.\MtsSpyCt\MtsSpyCtl.dll
InputPath=.\MtsSpyCt\MtsSpyCtl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug" || "$(CFG)" ==\
 "MtsSpyCtl - Win32 Unicode Release"
SOURCE=.\dlldatax.c
SOURCE=.\MethodSink.cpp
DEP_CPP_METHO=\
	".\MethodSink.h"\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\StdAfx.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	
NODEP_CPP_METHO=\
	".\MtsAudit.h"\
	".\mtsspyctl.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\MethodSink.obj"	"$(INTDIR)\MethodSink.sbr" : $(SOURCE)\
 $(DEP_CPP_METHO) "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\MethodSink.obj" : $(SOURCE) $(DEP_CPP_METHO) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 

SOURCE=.\MtsSink.cpp
DEP_CPP_MTSSI=\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\StdAfx.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	
NODEP_CPP_MTSSI=\
	".\MtsAudit.h"\
	".\mtsspyctl.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\MtsSink.obj"	"$(INTDIR)\MtsSink.sbr" : $(SOURCE) $(DEP_CPP_MTSSI)\
 "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\MtsSink.obj" : $(SOURCE) $(DEP_CPP_MTSSI) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 

SOURCE=.\MtsSpy.cpp
DEP_CPP_MTSSP=\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\ObjSink.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\ResourceSink.h"\
	".\SelectEventsDlg.h"\
	".\StdAfx.h"\
	".\TxSink.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	"\Administration\mtsspy\inc\MtsGrp.h"\
	
NODEP_CPP_MTSSP=\
	".\MtsAudit.h"\
	".\mtsspyctl.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\MtsSpy.obj"	"$(INTDIR)\MtsSpy.sbr" : $(SOURCE) $(DEP_CPP_MTSSP)\
 "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\MtsSpy.obj" : $(SOURCE) $(DEP_CPP_MTSSP) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 

SOURCE=.\MtsSpyCtl.cpp
DEP_CPP_MTSSPY=\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\MtsSpyPropPage.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\StdAfx.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\eventcpts_i.c"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	"\Administration\mtsspy\inc\mtsevents_i.c"\
	
NODEP_CPP_MTSSPY=\
	".\MtsAudit.h"\
	".\MtsAudit_i.c"\
	".\mtsspyctl.h"\
	".\mtsspyctl_i.c"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\MtsSpyCtl.obj"	"$(INTDIR)\MtsSpyCtl.sbr" : $(SOURCE)\
 $(DEP_CPP_MTSSPY) "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\MtsSpyCtl.obj" : $(SOURCE) $(DEP_CPP_MTSSPY) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 

SOURCE=.\MtsSpyCtl.rc
DEP_RSC_MTSSPYC=\
	".\icon1.ico"\
	".\MtsSink.rgs"\
	".\MtsSpy.rgs"\
	".\mtsspy1.bin"\
	".\MtsSpyPropPage.rgs"\
	".\ResourceSink.rgs"\
	".\ShowEvents.rgs"\
	".\TxSink.rgs"\
	
NODEP_RSC_MTSSPYC=\
	".\inc\MtsSpyCtl.tlb"\
	

"$(INTDIR)\MtsSpyCtl.res" : $(SOURCE) $(DEP_RSC_MTSSPYC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MtsSpyPropPage.cpp
DEP_CPP_MTSSPYP=\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\MtsSpyPropPage.h"\
	".\ObjSink.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\StdAfx.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	
NODEP_CPP_MTSSPYP=\
	".\MtsAudit.h"\
	".\mtsspyctl.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\MtsSpyPropPage.obj"	"$(INTDIR)\MtsSpyPropPage.sbr" : $(SOURCE)\
 $(DEP_CPP_MTSSPYP) "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\MtsSpyPropPage.obj" : $(SOURCE) $(DEP_CPP_MTSSPYP) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 

SOURCE=.\ResourceSink.cpp
DEP_CPP_RESOU=\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\ResourceSink.h"\
	".\StdAfx.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	
NODEP_CPP_RESOU=\
	".\MtsAudit.h"\
	".\mtsspyctl.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\ResourceSink.obj"	"$(INTDIR)\ResourceSink.sbr" : $(SOURCE)\
 $(DEP_CPP_RESOU) "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\ResourceSink.obj" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 

SOURCE=.\SelectEventsDlg.cpp
DEP_CPP_SELEC=\
	".\InstanceSink.h"\
	".\MethodSink.h"\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\ObjSink.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\ResourceSink.h"\
	".\securitysink.h"\
	".\SelectEventsDlg.h"\
	".\StdAfx.h"\
	".\ThreadSink.h"\
	".\TxSink.h"\
	".\UserSink.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	"\Administration\mtsspy\inc\MtsGrp.h"\
	"\Administration\mtsspy\inc\MtsGrp_i.c"\
	
NODEP_CPP_SELEC=\
	".\MtsAudit.h"\
	".\mtsspyctl.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\SelectEventsDlg.obj"	"$(INTDIR)\SelectEventsDlg.sbr" : $(SOURCE)\
 $(DEP_CPP_SELEC) "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\SelectEventsDlg.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\MtsSpyCtl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MtsSpyCtl.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL"\
 /Fp"$(INTDIR)\MtsSpyCtl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MtsSpyCtl.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TxSink.cpp
DEP_CPP_TXSIN=\
	".\MtsSink.h"\
	".\MtsSpy.h"\
	".\PackageInfo.h"\
	".\PackageSink.h"\
	".\StdAfx.h"\
	".\TxSink.h"\
	"\Administration\mtsspy\inc\eventcpts.h"\
	"\Administration\mtsspy\inc\mtsevents.h"\
	
NODEP_CPP_TXSIN=\
	".\MtsAudit.h"\
	".\mtsspyctl.h"\
	

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\TxSink.obj"	"$(INTDIR)\TxSink.sbr" : $(SOURCE) $(DEP_CPP_TXSIN)\
 "$(INTDIR)" "$(INTDIR)\MtsSpyCtl.pch"


!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"


"$(INTDIR)\TxSink.obj" : $(SOURCE) $(DEP_CPP_TXSIN) "$(INTDIR)"\
 "$(INTDIR)\MtsSpyCtl.pch"


!ENDIF 


!ENDIF 

