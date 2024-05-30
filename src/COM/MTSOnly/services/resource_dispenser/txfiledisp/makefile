# Microsoft Developer Studio Generated NMAKE File, Based on TxFileDisp.dsp
!IF "$(CFG)" == ""
CFG=TxFileDisp - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to TxFileDisp - Win32 Unicode\
 Debug.
!ENDIF 

!IF "$(CFG)" != "TxFileDisp - Win32 Unicode Debug" && "$(CFG)" !=\
 "TxFileDisp - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TxFileDisp.mak" CFG="TxFileDisp - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TxFileDisp - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TxFileDisp - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TxFileDisp - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TxFileDisp.dll" "$(OUTDIR)\TxFileDisp.bsc"\
 "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\TxFileDisp.dll" "$(OUTDIR)\TxFileDisp.bsc"\
 "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dispimpl.obj"
	-@erase "$(INTDIR)\dispimpl.sbr"
	-@erase "$(INTDIR)\FileRmPxy.obj"
	-@erase "$(INTDIR)\FileRmPxy.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TxFileDisp.obj"
	-@erase "$(INTDIR)\TxFileDisp.pch"
	-@erase "$(INTDIR)\TxFileDisp.res"
	-@erase "$(INTDIR)\TxFileDisp.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\TxFileDisp.bsc"
	-@erase "$(OUTDIR)\TxFileDisp.dll"
	-@erase "$(OUTDIR)\TxFileDisp.exp"
	-@erase "$(OUTDIR)\TxFileDisp.ilk"
	-@erase "$(OUTDIR)\TxFileDisp.lib"
	-@erase "$(OUTDIR)\TxFileDisp.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /I "..\dtc\inc" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\TxFileDisp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxFileDisp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxFileDisp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dispimpl.sbr" \
	"$(INTDIR)\FileRmPxy.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TxFileDisp.sbr"

"$(OUTDIR)\TxFileDisp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=xolehlp.lib mtxdm.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\TxFileDisp.pdb" /debug /machine:I386\
 /def:".\TxFileDisp.def" /out:"$(OUTDIR)\TxFileDisp.dll"\
 /implib:"$(OUTDIR)\TxFileDisp.lib" /libpath:"..\dtc\lib" /libpath:"..\lib" 
DEF_FILE= \
	".\TxFileDisp.def"
LINK32_OBJS= \
	"$(INTDIR)\dispimpl.obj" \
	"$(INTDIR)\FileRmPxy.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxFileDisp.obj" \
	"$(INTDIR)\TxFileDisp.res"

"$(OUTDIR)\TxFileDisp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\DebugU
TargetPath=.\DebugU\TxFileDisp.dll
InputPath=.\DebugU\TxFileDisp.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "TxFileDisp - Win32 Unicode Release"

OUTDIR=.\TxFileDi
INTDIR=.\TxFileDi
# Begin Custom Macros
OutDir=.\TxFileDi
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TxFileDisp.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\TxFileDisp.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dispimpl.obj"
	-@erase "$(INTDIR)\FileRmPxy.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxFileDisp.obj"
	-@erase "$(INTDIR)\TxFileDisp.pch"
	-@erase "$(INTDIR)\TxFileDisp.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TxFileDisp.dll"
	-@erase "$(OUTDIR)\TxFileDisp.exp"
	-@erase "$(OUTDIR)\TxFileDisp.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\inc" /I "..\dtc\inc" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\TxFileDisp.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\TxFileDi/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxFileDisp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxFileDisp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=ole32.lib xolehlp.lib mtxdm.lib uuid.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\TxFileDisp.pdb"\
 /machine:I386 /def:".\TxFileDisp.def" /out:"$(OUTDIR)\TxFileDisp.dll"\
 /implib:"$(OUTDIR)\TxFileDisp.lib" /libpath:"..\dtc\lib" /libpath:"..\lib" 
DEF_FILE= \
	".\TxFileDisp.def"
LINK32_OBJS= \
	"$(INTDIR)\dispimpl.obj" \
	"$(INTDIR)\FileRmPxy.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxFileDisp.obj" \
	"$(INTDIR)\TxFileDisp.res"

"$(OUTDIR)\TxFileDisp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\TxFileDi
TargetPath=.\TxFileDi\TxFileDisp.dll
InputPath=.\TxFileDi\TxFileDisp.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "TxFileDisp - Win32 Unicode Debug" || "$(CFG)" ==\
 "TxFileDisp - Win32 Unicode Release"
SOURCE=.\dispimpl.cpp

!IF  "$(CFG)" == "TxFileDisp - Win32 Unicode Debug"

DEP_CPP_DISPI=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\txfiledisp.h"\
	".\FileRmPxy.h"\
	".\resource.h"\
	{$(INCLUDE)}"mtxdm.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\dispimpl.obj"	"$(INTDIR)\dispimpl.sbr" : $(SOURCE) $(DEP_CPP_DISPI)\
 "$(INTDIR)" "$(INTDIR)\TxFileDisp.pch"


!ELSEIF  "$(CFG)" == "TxFileDisp - Win32 Unicode Release"

DEP_CPP_DISPI=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\txfiledisp.h"\
	".\FileRmPxy.h"\
	".\resource.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"mtxdm.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\dispimpl.obj" : $(SOURCE) $(DEP_CPP_DISPI) "$(INTDIR)"\
 "$(INTDIR)\TxFileDisp.pch"


!ENDIF 

SOURCE=.\FileRmPxy.cpp

!IF  "$(CFG)" == "TxFileDisp - Win32 Unicode Debug"

DEP_CPP_FILER=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\txfiledisp.h"\
	".\FileRmPxy.h"\
	".\resource.h"\
	{$(INCLUDE)}"mtxdm.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\FileRmPxy.obj"	"$(INTDIR)\FileRmPxy.sbr" : $(SOURCE)\
 $(DEP_CPP_FILER) "$(INTDIR)" "$(INTDIR)\TxFileDisp.pch"


!ELSEIF  "$(CFG)" == "TxFileDisp - Win32 Unicode Release"

DEP_CPP_FILER=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\txfiledisp.h"\
	".\FileRmPxy.h"\
	".\resource.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"mtxdm.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\FileRmPxy.obj" : $(SOURCE) $(DEP_CPP_FILER) "$(INTDIR)"\
 "$(INTDIR)\TxFileDisp.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TxFileDisp - Win32 Unicode Debug"

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
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /I "..\dtc\inc" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\TxFileDisp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\TxFileDisp.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxFileDisp - Win32 Unicode Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\inc" /I "..\dtc\inc" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Fp"$(INTDIR)\TxFileDisp.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TxFileDisp.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TxFileDisp.cpp

!IF  "$(CFG)" == "TxFileDisp - Win32 Unicode Debug"

DEP_CPP_TXFIL=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\copyfilerm_i.c"\
	"..\..\..\common\inc\txfiledisp.h"\
	"..\..\..\common\inc\txfiledisp_i.c"\
	".\FileRmPxy.h"\
	".\resource.h"\
	{$(INCLUDE)}"mtxdm.h"\
	{$(INCLUDE)}"mtxdm_i.c"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\TxFileDisp.obj"	"$(INTDIR)\TxFileDisp.sbr" : $(SOURCE)\
 $(DEP_CPP_TXFIL) "$(INTDIR)" "$(INTDIR)\TxFileDisp.pch"


!ELSEIF  "$(CFG)" == "TxFileDisp - Win32 Unicode Release"

DEP_CPP_TXFIL=\
	"..\..\..\common\inc\copyfilerm.h"\
	"..\..\..\common\inc\copyfilerm_i.c"\
	"..\..\..\common\inc\txfiledisp.h"\
	"..\..\..\common\inc\txfiledisp_i.c"\
	".\FileRmPxy.h"\
	".\resource.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"mtxdm.h"\
	{$(INCLUDE)}"mtxdm_i.c"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"txcoord.h"\
	{$(INCLUDE)}"txdtc.h"\
	{$(INCLUDE)}"xolehlp.h"\
	

"$(INTDIR)\TxFileDisp.obj" : $(SOURCE) $(DEP_CPP_TXFIL) "$(INTDIR)"\
 "$(INTDIR)\TxFileDisp.pch"


!ENDIF 

SOURCE=.\TxFileDisp.rc
DEP_RSC_TXFILE=\
	"..\..\..\common\inc\TxFileDisp.tlb"\
	".\FileRmPxy.rgs"\
	".\resource.h"\
	

"$(INTDIR)\TxFileDisp.res" : $(SOURCE) $(DEP_RSC_TXFILE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

