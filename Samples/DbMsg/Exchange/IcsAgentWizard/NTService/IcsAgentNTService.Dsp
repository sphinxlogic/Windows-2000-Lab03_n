# Microsoft Developer Studio Project File - Name="ICSAgentNTService" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ICSAgentNTService - Win32 Pseudo-Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ICSAgentNTService.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ICSAgentNTService.mak" CFG="ICSAgentNTService - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ICSAgentNTService - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ICSAgentNTService - Win32 Pseudo-Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ICSAgentNTService - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "awx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Ext "awx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 edkmapi.lib mapi32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Release
TargetPath=.\Release\ICSAgentNTService.awx
TargetName=ICSAgentNTService
InputPath=.\Release\ICSAgentNTService.awx
SOURCE="$(InputPath)"

"$(MSDEVDIR)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ICSAgentNTService - Win32 Pseudo-Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "awx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Ext "awx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
# ADD LINK32 edkmapi.lib mapi32.lib /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Debug
TargetPath=.\Debug\ICSAgentNTService.awx
TargetName=ICSAgentNTService
InputPath=.\Debug\ICSAgentNTService.awx
SOURCE="$(InputPath)"

"$(MSDEVDIR)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ICSAgentNTService - Win32 Release"
# Name "ICSAgentNTService - Win32 Pseudo-Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Chooser.cpp
# End Source File
# Begin Source File

SOURCE=.\CMAPILogon.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm1Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm2Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm3Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm4Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm5Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug.cpp
# End Source File
# Begin Source File

SOURCE=.\ICSAgentNTService.cpp
# End Source File
# Begin Source File

SOURCE=.\ICSAgentNTService.rc
# End Source File
# Begin Source File

SOURCE=.\ICSAgentNTServiceAw.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Chooser.h
# End Source File
# Begin Source File

SOURCE=.\CMAPILogon.h
# End Source File
# Begin Source File

SOURCE=.\Cstm1Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm2Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm3Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm4Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm5Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\ICSAgentNTService.h
# End Source File
# Begin Source File

SOURCE=.\ICSAgentNTServiceAw.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\ICSAgentNTService.ico
# End Source File
# Begin Source File

SOURCE=.\res\template.bin
# End Source File
# End Group
# Begin Group "Template Files"

# PROP Default_Filter "<templates>"
# Begin Source File

SOURCE=.\Template\AgentService.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\AgentService.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\confirm.inf
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ErrorCodes.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICS.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICS.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSAgent.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSAgent.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSDemoContentCollector.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSDemoContentCollector.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSDemoHierarchyCollector.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSDemoHierarchyCollector.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSSynchronizer.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSSynchronizer.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSTable.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\ICSTable.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\MAPIApp.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\MAPIApp.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\newproj.inf
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\StdAfx.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\StdAfx.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
