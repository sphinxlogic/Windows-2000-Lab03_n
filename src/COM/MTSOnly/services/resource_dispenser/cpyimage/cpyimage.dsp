# Microsoft Developer Studio Project File - Name="CpyImage" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CpyImage - Win32 Unicode Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CpyImage.mak".
!MESSAGE 
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

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CpyImage - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Unicode Debug"
# PROP BASE Intermediate_Dir ".\Unicode Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DebugU"
# PROP Intermediate_Dir ".\DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 odbc32.lib mtx.lib svcguid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Packages\CpyImage.dll"
# Begin Custom Build
OutDir=.\.\DebugU
TargetPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
InputPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CpyImage - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CpyImage"
# PROP BASE Intermediate_Dir "CpyImage"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CpyImage"
# PROP Intermediate_Dir "CpyImage"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 odbc32.lib mtx.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Packages\CpyImage.dll"
# ADD LINK32 odbc32.lib mtx.lib svcguid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Packages\CpyImage.dll"
# Begin Custom Build
OutDir=.\CpyImage
TargetPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
InputPath=\mssdk\samples\Com\Services\Resource_Dispenser\Packages\CpyImage.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "CpyImage - Win32 Unicode Debug"
# Name "CpyImage - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CpyImage.cpp
# End Source File
# Begin Source File

SOURCE=.\CpyImage.def
# End Source File
# Begin Source File

SOURCE=.\CpyImage.rc
# End Source File
# Begin Source File

SOURCE=.\CpyImageObj.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CpyImageObj.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\CpyImage.rgs
# End Source File
# End Target
# End Project
