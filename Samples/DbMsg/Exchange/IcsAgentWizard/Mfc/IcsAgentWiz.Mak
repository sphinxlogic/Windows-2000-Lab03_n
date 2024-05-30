# Microsoft Developer Studio Generated NMAKE File, Based on ICSAgentWiz.dsp
!IF "$(CFG)" == ""
CFG=ICSAgentWiz - Win32 Pseudo-Debug
!MESSAGE No configuration specified. Defaulting to ICSAgentWiz - Win32 Pseudo-Debug.
!ENDIF 

!IF "$(CFG)" != "ICSAgentWiz - Win32 Release" && "$(CFG)" != "ICSAgentWiz - Win32 Pseudo-Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ICSAgentWiz.mak" CFG="ICSAgentWiz - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ICSAgentWiz - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ICSAgentWiz - Win32 Pseudo-Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template" ".\Release\ICSAgentWiz.hlp" "$(OUTDIR)\ICSAgentWiz.awx" "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template\ICSAgentWiz.awx"


CLEAN :
	-@erase "$(INTDIR)\Chooser.obj"
	-@erase "$(INTDIR)\CMAPILogon.obj"
	-@erase "$(INTDIR)\Cstm1Dlg.obj"
	-@erase "$(INTDIR)\Cstm2Dlg.obj"
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\ICSAgentWiz.obj"
	-@erase "$(INTDIR)\ICSAgentWiz.pch"
	-@erase "$(INTDIR)\ICSAgentWiz.res"
	-@erase "$(INTDIR)\ICSAgentWizAw.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ICSAgentWiz.awx"
	-@erase "$(OUTDIR)\ICSAgentWiz.exp"
	-@erase "$(OUTDIR)\ICSAgentWiz.lib"
	-@erase ".\Release\ICSAgentWiz.hlp"
	-@erase "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template"
	-@erase "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template\ICSAgentWiz.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\ICSAgentWiz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ICSAgentWiz.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ICSAgentWiz.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ICSAgentWiz.pdb" /machine:I386 /out:"$(OUTDIR)\ICSAgentWiz.awx" /implib:"$(OUTDIR)\ICSAgentWiz.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Chooser.obj" \
	"$(INTDIR)\CMAPILogon.obj" \
	"$(INTDIR)\Cstm1Dlg.obj" \
	"$(INTDIR)\Cstm2Dlg.obj" \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\ICSAgentWiz.obj" \
	"$(INTDIR)\ICSAgentWizAw.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ICSAgentWiz.res"

"$(OUTDIR)\ICSAgentWiz.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\ICSAgentWiz.awx
TargetName=ICSAgentWiz
InputPath=.\Release\ICSAgentWiz.awx
SOURCE="$(InputPath)"

"..\Program Files\Microsoft Visual Studio\Common\MSDev98\Template\ICSAgentWiz.awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
<< 
	

!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template" ".\Debug\ICSAgentWiz.hlp" "$(OUTDIR)\ICSAgentWiz.awx" "$(OUTDIR)\ICSAgentWiz.bsc" "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template\ICSAgentWiz.awx"


CLEAN :
	-@erase "$(INTDIR)\Chooser.obj"
	-@erase "$(INTDIR)\Chooser.sbr"
	-@erase "$(INTDIR)\CMAPILogon.obj"
	-@erase "$(INTDIR)\CMAPILogon.sbr"
	-@erase "$(INTDIR)\Cstm1Dlg.obj"
	-@erase "$(INTDIR)\Cstm1Dlg.sbr"
	-@erase "$(INTDIR)\Cstm2Dlg.obj"
	-@erase "$(INTDIR)\Cstm2Dlg.sbr"
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Debug.sbr"
	-@erase "$(INTDIR)\ICSAgentWiz.obj"
	-@erase "$(INTDIR)\ICSAgentWiz.pch"
	-@erase "$(INTDIR)\ICSAgentWiz.res"
	-@erase "$(INTDIR)\ICSAgentWiz.sbr"
	-@erase "$(INTDIR)\ICSAgentWizAw.obj"
	-@erase "$(INTDIR)\ICSAgentWizAw.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ICSAgentWiz.awx"
	-@erase "$(OUTDIR)\ICSAgentWiz.bsc"
	-@erase "$(OUTDIR)\ICSAgentWiz.exp"
	-@erase "$(OUTDIR)\ICSAgentWiz.ilk"
	-@erase "$(OUTDIR)\ICSAgentWiz.lib"
	-@erase "$(OUTDIR)\ICSAgentWiz.pdb"
	-@erase ".\Debug\ICSAgentWiz.hlp"
	-@erase "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template"
	-@erase "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Template\ICSAgentWiz.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ICSAgentWiz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ICSAgentWiz.res" /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ICSAgentWiz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Chooser.sbr" \
	"$(INTDIR)\CMAPILogon.sbr" \
	"$(INTDIR)\Cstm1Dlg.sbr" \
	"$(INTDIR)\Cstm2Dlg.sbr" \
	"$(INTDIR)\Debug.sbr" \
	"$(INTDIR)\ICSAgentWiz.sbr" \
	"$(INTDIR)\ICSAgentWizAw.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ICSAgentWiz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mapi32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ICSAgentWiz.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ICSAgentWiz.awx" /implib:"$(OUTDIR)\ICSAgentWiz.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Chooser.obj" \
	"$(INTDIR)\CMAPILogon.obj" \
	"$(INTDIR)\Cstm1Dlg.obj" \
	"$(INTDIR)\Cstm2Dlg.obj" \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\ICSAgentWiz.obj" \
	"$(INTDIR)\ICSAgentWizAw.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ICSAgentWiz.res"

"$(OUTDIR)\ICSAgentWiz.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ICSAgentWiz.awx
TargetName=ICSAgentWiz
InputPath=.\Debug\ICSAgentWiz.awx
SOURCE="$(InputPath)"

"..\Program Files\Microsoft Visual Studio\Common\MSDev98\Template\ICSAgentWiz.awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ICSAgentWiz.dep")
!INCLUDE "ICSAgentWiz.dep"
!ELSE 
!MESSAGE Warning: cannot find "ICSAgentWiz.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ICSAgentWiz - Win32 Release" || "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"
SOURCE=.\Chooser.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"


"$(INTDIR)\Chooser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"


"$(INTDIR)\Chooser.obj"	"$(INTDIR)\Chooser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ENDIF 

SOURCE=.\CMAPILogon.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"


"$(INTDIR)\CMAPILogon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"


"$(INTDIR)\CMAPILogon.obj"	"$(INTDIR)\CMAPILogon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ENDIF 

SOURCE=.\Cstm1Dlg.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"


"$(INTDIR)\Cstm1Dlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"


"$(INTDIR)\Cstm1Dlg.obj"	"$(INTDIR)\Cstm1Dlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ENDIF 

SOURCE=.\Cstm2Dlg.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"


"$(INTDIR)\Cstm2Dlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"


"$(INTDIR)\Cstm2Dlg.obj"	"$(INTDIR)\Cstm2Dlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ENDIF 

SOURCE=.\Debug.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"


"$(INTDIR)\Debug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"


"$(INTDIR)\Debug.obj"	"$(INTDIR)\Debug.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ENDIF 

SOURCE=.\ICSAgentWiz.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"


"$(INTDIR)\ICSAgentWiz.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"


"$(INTDIR)\ICSAgentWiz.obj"	"$(INTDIR)\ICSAgentWiz.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ENDIF 

SOURCE=.\hlp\ICSAgentWiz.hpj

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"

OutDir=.\Release
TargetName=ICSAgentWiz
InputPath=.\hlp\ICSAgentWiz.hpj
InputName=ICSAgentWiz
USERDEP__ICSAG="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	

"$(INTDIR)\ICSAgentWiz.hlp"	"..\Program Files\Microsoft Visual Studio\Common\MSDev98\Template" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__ICSAG)
	<<tempfile.bat 
	@echo off 
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	copy "$(OutDir)\$(TargetName).hlp" "$(MSDEVDIR)\Template" 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done
<< 
	

!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"

OutDir=.\Debug
TargetName=ICSAgentWiz
InputPath=.\hlp\ICSAgentWiz.hpj
InputName=ICSAgentWiz
USERDEP__ICSAG="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	

"$(INTDIR)\ICSAgentWiz.hlp"	"..\Program Files\Microsoft Visual Studio\Common\MSDev98\Template" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__ICSAG)
	<<tempfile.bat 
	@echo off 
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	copy "$(OutDir)\$(TargetName).hlp" "$(MSDEVDIR)\Template" 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done
<< 
	

!ENDIF 

SOURCE=.\ICSAgentWiz.rc

"$(INTDIR)\ICSAgentWiz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ICSAgentWizAw.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"


"$(INTDIR)\ICSAgentWizAw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"


"$(INTDIR)\ICSAgentWizAw.obj"	"$(INTDIR)\ICSAgentWizAw.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ICSAgentWiz.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\ICSAgentWiz.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ICSAgentWiz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"

CPP_SWITCHES=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ICSAgentWiz.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ICSAgentWiz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Resource.h

!IF  "$(CFG)" == "ICSAgentWiz - Win32 Release"

TargetName=ICSAgentWiz
InputPath=.\Resource.h

".\hlp\ICSAgentWiz.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ELSEIF  "$(CFG)" == "ICSAgentWiz - Win32 Pseudo-Debug"

TargetName=ICSAgentWiz
InputPath=.\Resource.h

".\hlp\ICSAgentWiz.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ENDIF 

SOURCE=.\Template\All.rc
SOURCE=.\Template\ChildFrm.cpp
SOURCE=.\Template\CntrItem.cpp
SOURCE=.\Template\Dialog.cpp
SOURCE=.\Template\DlgAll.rc
SOURCE=.\Template\DlgLoc_deu.rc
SOURCE=.\Template\DlgLoc_enu.rc
SOURCE=.\Template\DlgLoc_esp.rc
SOURCE=.\Template\DlgLoc_fra.rc
SOURCE=.\Template\DlgLoc_ita.rc
SOURCE=.\Template\DlgRoot.cpp
SOURCE=.\Template\Doc.cpp
SOURCE=.\Template\Frame.cpp
SOURCE=.\Template\ICS.cpp
SOURCE=.\Template\ICSAgent.cpp
SOURCE=.\Template\ICSDemoContentCollector.cpp
SOURCE=.\Template\ICSDemoHierarchyCollector.cpp
SOURCE=.\Template\ICSSynchronizer.cpp
SOURCE=.\Template\ICSTable.cpp
SOURCE=.\Template\IpFrame.cpp
SOURCE=.\Template\Loc_deu.rc
SOURCE=.\Template\Loc_enu.rc
SOURCE=.\Template\Loc_esp.rc
SOURCE=.\Template\Loc_fra.rc
SOURCE=.\Template\Loc_ita.rc
SOURCE=.\Template\MAPIApp.cpp
SOURCE=.\Template\RecSet.cpp
SOURCE=.\Template\Root.cpp
SOURCE=.\Template\Root.odl
SOURCE=.\Template\SrvrItem.cpp
SOURCE=.\Template\StdAfx.cpp
SOURCE=.\Template\TraceBox.cpp
SOURCE=.\Template\View.cpp

!ENDIF 

