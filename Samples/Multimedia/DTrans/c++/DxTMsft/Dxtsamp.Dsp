# Microsoft Developer Studio Project File - Name="DXTMsft" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DXTMsft - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dxtsamp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dxtsamp.mak" CFG="DXTMsft - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DXTMsft - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DXTMsft - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DXTMsft - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /Zi /Od /I "..\..\include\dt" /I "..\..\include" /I ".." /I "..\..\include\d3drm" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "D3D_OVERLOADS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dxtrans.lib d3drm.lib kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:"..\..\Bin\DXTMsftd.pdb" /debug /machine:I386 /def:".\DXTMsft.def" /out:"..\..\Bin\DXTSample.dll" /implib:"..\..\..\Lib\i386\DXTMsftd.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=\dtrans\sdk\Bin\DXTSample.dll
InputPath=\dtrans\sdk\Bin\DXTSample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DXTMsft - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DXTMsft_"
# PROP BASE Intermediate_Dir "DXTMsft_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "..\..\include\dt" /I "..\..\include" /I ".." /I "..\..\include\d3drm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "D3D_OVERLOADS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 dxtrans.lib d3drm.lib kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:"..\..\Bin\DXTMsft.pdb" /machine:I386 /out:"..\..\Bin\DXTSample.dll" /implib:"..\..\..\Lib\i386\DXTMsft.lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=\dtrans\sdk\Bin\DXTSample.dll
InputPath=\dtrans\sdk\Bin\DXTSample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "DXTMsft - Win32 Debug"
# Name "DXTMsft - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dissolve.cpp
# End Source File
# Begin Source File

SOURCE=.\DXTMsft.def

!IF  "$(CFG)" == "DXTMsft - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "DXTMsft - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dxtsamp.cpp
# End Source File
# Begin Source File

SOURCE=.\dxtsamp.rc

!IF  "$(CFG)" == "DXTMsft - Win32 Debug"

!ELSEIF  "$(CFG)" == "DXTMsft - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\explode.cpp
# End Source File
# Begin Source File

SOURCE=.\explodeprop.cpp
# End Source File
# Begin Source File

SOURCE=.\flip.cpp
# End Source File
# Begin Source File

SOURCE=.\guids.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\htfield.cpp
# End Source File
# Begin Source File

SOURCE=.\ruffle.cpp
# End Source File
# Begin Source File

SOURCE=.\ruffleprop.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dissolve.h
# End Source File
# Begin Source File

SOURCE=.\Explode.h
# End Source File
# Begin Source File

SOURCE=.\explodeprop.h
# End Source File
# Begin Source File

SOURCE=.\flip.h
# End Source File
# Begin Source File

SOURCE=.\htfield.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ruffle.h
# End Source File
# Begin Source File

SOURCE=.\ruffleprop.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe;rgs"
# Begin Source File

SOURCE=.\dissolve.rgs
# End Source File
# Begin Source File

SOURCE=.\explode.rgs
# End Source File
# Begin Source File

SOURCE=.\explpp.rgs
# End Source File
# Begin Source File

SOURCE=.\flip.rgs
# End Source File
# Begin Source File

SOURCE=.\htfield.rgs
# End Source File
# Begin Source File

SOURCE=.\Ruffle.rgs
# End Source File
# Begin Source File

SOURCE=.\ruffpp.rgs
# End Source File
# End Group
# End Target
# End Project
