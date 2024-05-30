# Microsoft Developer Studio Project File - Name="MtsSpyCtl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MtsSpyCtl - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MtsSpyCtl.mak".
!MESSAGE 
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

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comdlg32.lib shell32.lib rpcrt4.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\MtsSpyCtl.dll
InputPath=.\DebugU\MtsSpyCtl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "MtsSpyCtl - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MtsSpyCt"
# PROP BASE Intermediate_Dir "MtsSpyCt"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MtsSpyCt"
# PROP Intermediate_Dir "MtsSpyCt"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comdlg32.lib shell32.lib rpcrt4.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 comdlg32.lib shell32.lib rpcrt4.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\MtsSpyCt
TargetPath=.\MtsSpyCt\MtsSpyCtl.dll
InputPath=.\MtsSpyCt\MtsSpyCtl.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "MtsSpyCtl - Win32 Unicode Debug"
# Name "MtsSpyCtl - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MethodSink.cpp
# End Source File
# Begin Source File

SOURCE=.\MtsSink.cpp
# End Source File
# Begin Source File

SOURCE=.\MtsSpy.cpp
# End Source File
# Begin Source File

SOURCE=.\MtsSpyCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\MtsSpyCtl.def
# End Source File
# Begin Source File

SOURCE=.\MtsSpyCtl.rc
# End Source File
# Begin Source File

SOURCE=.\MtsSpyPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceSink.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectEventsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TxSink.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\InstanceSink.h
# End Source File
# Begin Source File

SOURCE=.\MethodSink.h
# End Source File
# Begin Source File

SOURCE=.\MtsSink.h
# End Source File
# Begin Source File

SOURCE=.\MtsSpy.h
# End Source File
# Begin Source File

SOURCE=.\MtsSpyPropPage.h
# End Source File
# Begin Source File

SOURCE=.\ObjSink.h
# End Source File
# Begin Source File

SOURCE=.\PackageInfo.h
# End Source File
# Begin Source File

SOURCE=.\PackageSink.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResourceSink.h
# End Source File
# Begin Source File

SOURCE=.\SelectEventsDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ThreadSink.h
# End Source File
# Begin Source File

SOURCE=.\TxSink.h
# End Source File
# Begin Source File

SOURCE=.\UserSink.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\mtsspy1.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\MtsSink.rgs
# End Source File
# Begin Source File

SOURCE=.\MtsSpy.rgs
# End Source File
# Begin Source File

SOURCE=.\MtsSpyPropPage.rgs
# End Source File
# Begin Source File

SOURCE=.\ResourceSink.rgs
# End Source File
# Begin Source File

SOURCE=.\ShowEvents.rgs
# End Source File
# Begin Source File

SOURCE=.\TxSink.rgs
# End Source File
# End Target
# End Project
