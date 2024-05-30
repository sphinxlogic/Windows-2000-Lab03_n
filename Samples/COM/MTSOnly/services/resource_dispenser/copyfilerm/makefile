# Microsoft Developer Studio Generated NMAKE File, Based on CopyFileRm.dsp
!IF "$(CFG)" == ""
CFG=CopyFileRm - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to CopyFileRm - Win32 Unicode\
 Debug.
!ENDIF 

!IF "$(CFG)" != "CopyFileRm - Win32 Unicode Debug" && "$(CFG)" !=\
 "CopyFileRm - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CopyFileRm.mak" CFG="CopyFileRm - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CopyFileRm - Win32 Unicode Debug" (based on\
 "Win32 (x86) Application")
!MESSAGE "CopyFileRm - Win32 Unicode Release" (based on\
 "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CopyFileRm - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CopyFileRm.exe" "$(OUTDIR)\CopyFileRm.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CopyFileRm.exe" "$(OUTDIR)\CopyFileRm.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CopyFileRm.obj"
	-@erase "$(INTDIR)\CopyFileRm.pch"
	-@erase "$(INTDIR)\CopyFileRm.res"
	-@erase "$(INTDIR)\CopyFileRm.sbr"
	-@erase "$(INTDIR)\FileRm.obj"
	-@erase "$(INTDIR)\FileRm.sbr"
	-@erase "$(INTDIR)\RmDlg.obj"
	-@erase "$(INTDIR)\RmDlg.sbr"
	-@erase "$(INTDIR)\RmOptionsDlg.obj"
	-@erase "$(INTDIR)\RmOptionsDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CopyFileRm.bsc"
	-@erase "$(OUTDIR)\CopyFileRm.exe"
	-@erase "$(OUTDIR)\CopyFileRm.ilk"
	-@erase "$(OUTDIR)\CopyFileRm.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\Inc" /I "..\dtc\inc" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\CopyFileRm.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CopyFileRm.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CopyFileRm.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CopyFileRm.sbr" \
	"$(INTDIR)\FileRm.sbr" \
	"$(INTDIR)\RmDlg.sbr" \
	"$(INTDIR)\RmOptionsDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\CopyFileRm.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=xolehlp.lib rpcrt4.lib /nologo /entry:"wWinMainCRTStartup"\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CopyFileRm.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\CopyFileRm.exe" /pdbtype:sept\
 /libpath:"..\dtc\lib" 
LINK32_OBJS= \
	"$(INTDIR)\CopyFileRm.obj" \
	"$(INTDIR)\CopyFileRm.res" \
	"$(INTDIR)\FileRm.obj" \
	"$(INTDIR)\RmDlg.obj" \
	"$(INTDIR)\RmOptionsDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CopyFileRm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CopyFileRm.exe
InputPath=.\DebugU\CopyFileRm.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ELSEIF  "$(CFG)" == "CopyFileRm - Win32 Unicode Release"

OUTDIR=.\CopyFile
INTDIR=.\CopyFile
# Begin Custom Macros
OutDir=.\CopyFile
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CopyFileRm.exe" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\CopyFileRm.exe" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CopyFileRm.obj"
	-@erase "$(INTDIR)\CopyFileRm.pch"
	-@erase "$(INTDIR)\CopyFileRm.res"
	-@erase "$(INTDIR)\FileRm.obj"
	-@erase "$(INTDIR)\RmDlg.obj"
	-@erase "$(INTDIR)\RmOptionsDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CopyFileRm.exe"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O1 /I "..\Inc" /I "..\dtc\inc" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\CopyFileRm.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\CopyFile/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CopyFileRm.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CopyFileRm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=xolehlp.lib rpcrt4.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\CopyFileRm.pdb" /machine:I386 /out:"$(OUTDIR)\CopyFileRm.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CopyFileRm.obj" \
	"$(INTDIR)\CopyFileRm.res" \
	"$(INTDIR)\FileRm.obj" \
	"$(INTDIR)\RmDlg.obj" \
	"$(INTDIR)\RmOptionsDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CopyFileRm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\CopyFile
TargetPath=.\CopyFile\CopyFileRm.exe
InputPath=.\CopyFile\CopyFileRm.exe
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	

!ENDIF 


!IF "$(CFG)" == "CopyFileRm - Win32 Unicode Debug" || "$(CFG)" ==\
 "CopyFileRm - Win32 Unicode Release"
SOURCE=.\CopyFileRm.cpp

!IF  "$(CFG)" == "CopyFileRm - Win32 Unicode Debug"

DEP_CPP_COPYF=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\copyfilerm_i.c"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	"..\..\..\common\inc\simplelog_i.c"\
	".\FileRm.h"\
	".\Resource.h"\
	".\RmDlg.h"\
	".\rmoptions.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\CopyFileRm.obj"	"$(INTDIR)\CopyFileRm.sbr" : $(SOURCE)\
 $(DEP_CPP_COPYF) "$(INTDIR)" "$(INTDIR)\CopyFileRm.pch"


!ELSEIF  "$(CFG)" == "CopyFileRm - Win32 Unicode Release"

DEP_CPP_COPYF=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\copyfilerm_i.c"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\simplelog.h"\
	"..\..\..\common\inc\simplelog_i.c"\
	".\FileRm.h"\
	".\Resource.h"\
	".\RmDlg.h"\
	".\rmoptions.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\CopyFileRm.obj" : $(SOURCE) $(DEP_CPP_COPYF) "$(INTDIR)"\
 "$(INTDIR)\CopyFileRm.pch"


!ENDIF 

SOURCE=.\CopyFileRm.rc
DEP_RSC_COPYFI=\
	"..\..\..\common\inc\CopyFileRm.tlb"\
	".\CopyFileRm.rgs"\
	".\FileRm.rgs"\
	".\Resource.h"\
	

"$(INTDIR)\CopyFileRm.res" : $(SOURCE) $(DEP_RSC_COPYFI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\FileRm.cpp

!IF  "$(CFG)" == "CopyFileRm - Win32 Unicode Debug"

DEP_CPP_FILER=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\rmworker_i.c"\
	"..\..\..\common\inc\simplelog.h"\
	".\FileRm.h"\
	".\Resource.h"\
	".\RmDlg.h"\
	".\rmoptions.h"\
	".\RmOptionsDlg.h"\
	".\RmSink.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\FileRm.obj"	"$(INTDIR)\FileRm.sbr" : $(SOURCE) $(DEP_CPP_FILER)\
 "$(INTDIR)" "$(INTDIR)\CopyFileRm.pch"


!ELSEIF  "$(CFG)" == "CopyFileRm - Win32 Unicode Release"

DEP_CPP_FILER=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\rmworker.h"\
	"..\..\..\common\inc\rmworker_i.c"\
	"..\..\..\common\inc\simplelog.h"\
	".\FileRm.h"\
	".\Resource.h"\
	".\RmDlg.h"\
	".\rmoptions.h"\
	".\RmOptionsDlg.h"\
	".\RmSink.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\FileRm.obj" : $(SOURCE) $(DEP_CPP_FILER) "$(INTDIR)"\
 "$(INTDIR)\CopyFileRm.pch"


!ENDIF 

SOURCE=.\RmDlg.cpp

!IF  "$(CFG)" == "CopyFileRm - Win32 Unicode Debug"

DEP_CPP_RMDLG=\
	".\Resource.h"\
	".\RmDlg.h"\
	".\rmoptions.h"\
	".\RmOptionsDlg.h"\
	

"$(INTDIR)\RmDlg.obj"	"$(INTDIR)\RmDlg.sbr" : $(SOURCE) $(DEP_CPP_RMDLG)\
 "$(INTDIR)" "$(INTDIR)\CopyFileRm.pch"


!ELSEIF  "$(CFG)" == "CopyFileRm - Win32 Unicode Release"

DEP_CPP_RMDLG=\
	".\Resource.h"\
	".\RmDlg.h"\
	".\rmoptions.h"\
	".\RmOptionsDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RmDlg.obj" : $(SOURCE) $(DEP_CPP_RMDLG) "$(INTDIR)"\
 "$(INTDIR)\CopyFileRm.pch"


!ENDIF 

SOURCE=.\RmOptionsDlg.cpp

!IF  "$(CFG)" == "CopyFileRm - Win32 Unicode Debug"

DEP_CPP_RMOPT=\
	".\Resource.h"\
	".\rmoptions.h"\
	".\RmOptionsDlg.h"\
	

"$(INTDIR)\RmOptionsDlg.obj"	"$(INTDIR)\RmOptionsDlg.sbr" : $(SOURCE)\
 $(DEP_CPP_RMOPT) "$(INTDIR)" "$(INTDIR)\CopyFileRm.pch"


!ELSEIF  "$(CFG)" == "CopyFileRm - Win32 Unicode Release"

DEP_CPP_RMOPT=\
	".\Resource.h"\
	".\rmoptions.h"\
	".\RmOptionsDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RmOptionsDlg.obj" : $(SOURCE) $(DEP_CPP_RMOPT) "$(INTDIR)"\
 "$(INTDIR)\CopyFileRm.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CopyFileRm - Win32 Unicode Debug"

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
	
CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\Inc" /I "..\dtc\inc" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\CopyFileRm.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CopyFileRm.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CopyFileRm - Win32 Unicode Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /ML /W3 /GX /O1 /I "..\Inc" /I "..\dtc\inc" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\CopyFileRm.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CopyFileRm.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

