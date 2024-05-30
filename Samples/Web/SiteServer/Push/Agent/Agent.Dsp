# Microsoft Developer Studio Project File - Name="Agent" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=Agent - Win32 i386 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Agent.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Agent.mak" CFG="Agent - Win32 i386 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Agent - Win32 Alpha Unicode Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Agent - Win32 Alpha Unicode Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Agent - Win32 i386 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Agent - Win32 i386 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaDbgU"
# PROP BASE Intermediate_Dir "AlphaDbgU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /MDd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "_USRDLL" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE" /Yu"stdafx.h" /FD /MDd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:ALPHA /out:"DebugU/SampleAgent.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\SampleAgent.dll
InputPath=.\DebugU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaRelUMinDependency"
# PROP BASE Intermediate_Dir "AlphaRelUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O1 /D "NDEBUG" /D "_USRDLL" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 /nologo /subsystem:windows /dll /machine:ALPHA /out:"ReleaseU/SampleAgent.dll"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\SampleAgent.dll
InputPath=.\ReleaseU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Agent___"
# PROP BASE Intermediate_Dir "Agent___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:IX86 /pdbtype:sept
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"DebugU/SampleAgent.dll" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\SampleAgent.dll
InputPath=.\DebugU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Agent__0"
# PROP BASE Intermediate_Dir "Agent__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /dll /machine:IX86 /out:"ReleaseU/SampleAgent.dll"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\SampleAgent.dll
InputPath=.\ReleaseU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Agent - Win32 Alpha Unicode Debug"
# Name "Agent - Win32 Alpha Unicode Release"
# Name "Agent - Win32 i386 Unicode Debug"
# Name "Agent - Win32 i386 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Agent.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_AGENT=\
	".\Agent.h"\
	".\Agent_i.c"\
	".\AgentPropPageProvider.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Agent.def
# End Source File
# Begin Source File

SOURCE=.\Agent.idl

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\Agent.idl

BuildCmds= \
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

".\Agent.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

# Begin Custom Build - Performing MIDL step
InputPath=.\Agent.idl

BuildCmds= \
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

".\Agent.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\Agent.idl

BuildCmds= \
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

".\Agent.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

# Begin Custom Build - Performing MIDL step
InputPath=.\Agent.idl

BuildCmds= \
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

".\Agent.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Agent_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Agent.rc
# End Source File
# Begin Source File

SOURCE=.\AgentPropPage.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_AGENTP=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AgentPropPageProvider.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_AGENTPR=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\AgentPropPageProvider.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DispHelp.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_DISPH=\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AgentPropPage.h
# End Source File
# Begin Source File

SOURCE=.\AgentPropPageProvider.h
# End Source File
# Begin Source File

SOURCE=.\DispHelp.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\AgentPropPageProvider.rgs
# End Source File
# End Group
# Begin Group "Distrib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Distrib\AgSampleAgent.asp
# End Source File
# Begin Source File

SOURCE=.\Distrib\readme.txt
# End Source File
# Begin Source File

SOURCE=.\Distrib\SampleAgent.VBS
# End Source File
# Begin Source File

SOURCE=.\Distrib\WizPushChn0.asp
# End Source File
# Begin Source File

SOURCE=.\Distrib\WizSampleAgent.asp
# End Source File
# End Group
# End Target
# End Project
