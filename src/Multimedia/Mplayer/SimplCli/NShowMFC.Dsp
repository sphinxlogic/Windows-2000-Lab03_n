# Microsoft Developer Studio Project File - Name="NShowMFC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NShowMFC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NShowMFC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NShowMFC.mak" CFG="NShowMFC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NShowMFC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NShowMFC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NShowMFC - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "NShowMFC - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NShowMFC - Win32 Release"
# Name "NShowMFC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mediaplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\NShowMFC.cpp
# End Source File
# Begin Source File

SOURCE=.\NShowMFC.rc

!IF  "$(CFG)" == "NShowMFC - Win32 Release"

!ELSEIF  "$(CFG)" == "NShowMFC - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NShowMFCDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\mediaplayer.h
# End Source File
# Begin Source File

SOURCE=.\NShowMFC.h
# End Source File
# Begin Source File

SOURCE=.\NShowMFCDlg.h
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

SOURCE=.\res\NShowMFC.ico
# End Source File
# Begin Source File

SOURCE=.\res\NShowMFC.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section NShowMFC : {22D6F311-B0F6-11D0-94AB-0080C74C7E95}
# 	2:5:Class:CMediaPlayer
# 	2:10:HeaderFile:mediaplayer.h
# 	2:8:ImplFile:mediaplayer.cpp
# End Section
# Section NShowMFC : {265EC141-AE62-11D1-8500-00A0C91F9CA0}
# 	2:5:Class:CNSPlay1
# 	2:10:HeaderFile:nsplay1.h
# 	2:8:ImplFile:nsplay1.cpp
# End Section
# Section NShowMFC : {2179C5D3-EBFF-11CF-B6FD-00AA00B4E220}
# 	2:21:DefaultSinkHeaderFile:nsplay1.h
# 	2:16:DefaultSinkClass:CNSPlay1
# End Section
# Section NShowMFC : {E7C4BE80-7960-11D0-B727-00AA00B4E220}
# 	2:5:Class:CNSPlay
# 	2:10:HeaderFile:nsplay.h
# 	2:8:ImplFile:nsplay.cpp
# End Section
# Section NShowMFC : {22D6F312-B0F6-11D0-94AB-0080C74C7E95}
# 	2:21:DefaultSinkHeaderFile:mediaplayer.h
# 	2:16:DefaultSinkClass:CMediaPlayer
# End Section
