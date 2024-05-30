# Microsoft Developer Studio Generated NMAKE File, Based on CpyImage.dsp
!IF "$(CFG)" == ""
CFG=CpyImage - Win32 Unicode Release
!MESSAGE No configuration specified. Defaulting to CpyImage - Win32 Unicode\
 Release.
!ENDIF 

!IF "$(CFG)" != "CpyImage - Win32 Unicode Debug" && "$(CFG)" !=\
 "CpyImage - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CpyImage.mak" CFG="CpyImage - Win32 Unicode Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CpyImage - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CpyImage - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CpyImage - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Packages\CpyImage.dll" "$(OUTDIR)\CpyImage.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "..\Packages\CpyImage.dll" "$(OUTDIR)\CpyImage.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CpyImage.obj"
	-@erase "$(INTDIR)\CpyImage.pch"
	-@erase "$(INTDIR)\CpyImage.res"
	-@erase "$(INTDIR)\CpyImage.sbr"
	-@erase "$(INTDIR)\CpyImageObj.obj"
	-@erase "$(INTDIR)\CpyImageObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CpyImage.bsc"
	-@erase "$(OUTDIR)\CpyImage.exp"
	-@erase "$(OUTDIR)\CpyImage.lib"
	-@erase "$(OUTDIR)\CpyImage.pdb"
	-@erase "..\Packages\CpyImage.dll"
	-@erase "..\Packages\CpyImage.ilk"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\CpyImage.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CpyImage.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CpyImage.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CpyImage.sbr" \
	"$(INTDIR)\CpyImageObj.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\CpyImage.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=odbc32.lib mtx.lib svcguid.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\CpyImage.pdb" /debug /machine:I386\
 /def:".\CpyImage.def" /out:"..\Packages\CpyImage.dll"\
 /implib:"$(OUTDIR)\CpyImage.lib" 
DEF_FILE= \
	".\CpyImage.def"
LINK32_OBJS= \
	"$(INTDIR)\CpyImage.obj" \
	"$(INTDIR)\CpyImage.res" \
	"$(INTDIR)\CpyImageObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"..\Packages\CpyImage.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
InputPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "CpyImage - Win32 Unicode Release"

OUTDIR=.\CpyImage
INTDIR=.\CpyImage
# Begin Custom Macros
OutDir=.\CpyImage
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Packages\CpyImage.dll" "$(OUTDIR)\CpyImage.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "..\Packages\CpyImage.dll" "$(OUTDIR)\CpyImage.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CpyImage.obj"
	-@erase "$(INTDIR)\CpyImage.pch"
	-@erase "$(INTDIR)\CpyImage.res"
	-@erase "$(INTDIR)\CpyImage.sbr"
	-@erase "$(INTDIR)\CpyImageObj.obj"
	-@erase "$(INTDIR)\CpyImageObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CpyImage.bsc"
	-@erase "$(OUTDIR)\CpyImage.exp"
	-@erase "$(OUTDIR)\CpyImage.lib"
	-@erase "$(OUTDIR)\CpyImage.pdb"
	-@erase "..\Packages\CpyImage.dll"
	-@erase "..\Packages\CpyImage.ilk"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\CpyImage.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\CpyImage/
CPP_SBRS=.\CpyImage/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CpyImage.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CpyImage.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CpyImage.sbr" \
	"$(INTDIR)\CpyImageObj.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\CpyImage.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=odbc32.lib mtx.lib svcguid.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\CpyImage.pdb" /debug /machine:I386\
 /def:".\CpyImage.def" /out:"..\Packages\CpyImage.dll"\
 /implib:"$(OUTDIR)\CpyImage.lib" 
DEF_FILE= \
	".\CpyImage.def"
LINK32_OBJS= \
	"$(INTDIR)\CpyImage.obj" \
	"$(INTDIR)\CpyImage.res" \
	"$(INTDIR)\CpyImageObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"..\Packages\CpyImage.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\CpyImage
TargetPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
InputPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "CpyImage - Win32 Unicode Debug" || "$(CFG)" ==\
 "CpyImage - Win32 Unicode Release"
SOURCE=.\CpyImage.cpp
DEP_CPP_CPYIM=\
	"..\..\..\common\inc\CpyImage.h"\
	"..\..\..\common\inc\CpyImage_i.c"\
	".\CpyImageObj.h"\
	".\resource.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"autosvcs.h"\
	{$(INCLUDE)}"mtsevents.h"\
	

"$(INTDIR)\CpyImage.obj"	"$(INTDIR)\CpyImage.sbr" : $(SOURCE) $(DEP_CPP_CPYIM)\
 "$(INTDIR)" "$(INTDIR)\CpyImage.pch"


SOURCE=.\CpyImage.rc
DEP_RSC_CPYIMA=\
	"..\..\..\common\inc\CpyImage.tlb"\
	".\CpyImage.rgs"\
	".\resource.h"\
	

"$(INTDIR)\CpyImage.res" : $(SOURCE) $(DEP_RSC_CPYIMA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CpyImageObj.cpp
DEP_CPP_CPYIMAG=\
	"..\..\..\common\inc\CpyImage.h"\
	"..\..\..\common\inc\mtsusereventobj.h"\
	"..\..\..\common\inc\mtsusereventobj_i.c"\
	"..\..\..\common\inc\txfiledisp.h"\
	"..\..\..\common\inc\txfiledisp_i.c"\
	".\CpyImageObj.h"\
	".\resource.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CpyImageObj.obj"	"$(INTDIR)\CpyImageObj.sbr" : $(SOURCE)\
 $(DEP_CPP_CPYIMAG) "$(INTDIR)" "$(INTDIR)\CpyImage.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CpyImage - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\CpyImage.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CpyImage.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CpyImage - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\CpyImage.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CpyImage.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

