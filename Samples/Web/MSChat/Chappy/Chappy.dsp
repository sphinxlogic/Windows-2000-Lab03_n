# Microsoft Developer Studio Project File - Name="Chappy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Chappy - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Chappy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Chappy.mak" CFG="Chappy - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Chappy - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Chappy - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Chappy - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /pdb:none /machine:I386
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "Chappy - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "Chappy - Win32 Release"
# Name "Chappy - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BanDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Chappy.cpp
# End Source File
# Begin Source File

SOURCE=.\Chappy.rc
# End Source File
# Begin Source File

SOURCE=.\ChppyDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ChppyVw.cpp
# End Source File
# Begin Source File

SOURCE=.\chtitems.cpp
# End Source File
# Begin Source File

SOURCE=.\enterdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\flatTB.cpp
# End Source File
# Begin Source File

SOURCE=.\History.cpp
# End Source File
# Begin Source File

SOURCE=.\InputRE.cpp
# End Source File
# Begin Source File

SOURCE=.\KickDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LogInDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\mschatpr.cpp
# End Source File
# Begin Source File

SOURCE=.\mschatx.cpp
# End Source File
# Begin Source File

SOURCE=.\PLTree.cpp
# End Source File
# Begin Source File

SOURCE=.\PWordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\REdit.cpp
# End Source File
# Begin Source File

SOURCE=.\RListCtr.cpp
# End Source File
# Begin Source File

SOURCE=.\Room.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomHstr.cpp
# End Source File
# Begin Source File

SOURCE=.\RTab.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TB.cpp
# End Source File
# Begin Source File

SOURCE=.\Utility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\BanDlg.h
# End Source File
# Begin Source File

SOURCE=.\Chappy.h
# End Source File
# Begin Source File

SOURCE=.\ChppyDoc.h
# End Source File
# Begin Source File

SOURCE=.\ChppyVw.h
# End Source File
# Begin Source File

SOURCE=.\chtitems.h
# End Source File
# Begin Source File

SOURCE=.\enterdlg.h
# End Source File
# Begin Source File

SOURCE=.\FlatTB.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\History.h
# End Source File
# Begin Source File

SOURCE=.\InputRE.h
# End Source File
# Begin Source File

SOURCE=.\KickDlg.h
# End Source File
# Begin Source File

SOURCE=.\LogInDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\mschatpr.h
# End Source File
# Begin Source File

SOURCE=.\mschatx.h
# End Source File
# Begin Source File

SOURCE=.\PLTree.h
# End Source File
# Begin Source File

SOURCE=.\PWordDlg.h
# End Source File
# Begin Source File

SOURCE=.\REdit.h
# End Source File
# Begin Source File

SOURCE=.\RListCtr.h
# End Source File
# Begin Source File

SOURCE=.\Room.h
# End Source File
# Begin Source File

SOURCE=.\RoomHstr.h
# End Source File
# Begin Source File

SOURCE=.\RTab.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TB.h
# End Source File
# Begin Source File

SOURCE=.\Utility.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Chappy.ico
# End Source File
# Begin Source File

SOURCE=.\res\Chappy.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ChppyDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Earth.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\room_lis.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# End Target
# End Project
# Section Chappy : {011EEE40-46DF-11D0-99CB-00C04FD64497}
# 	2:5:Class:CMsChatPr
# 	2:10:HeaderFile:mschatpr.h
# 	2:8:ImplFile:mschatpr.cpp
# End Section
# Section Chappy : {039397C0-46DF-11D0-99CB-00C04FD64497}
# 	2:21:DefaultSinkHeaderFile:mschatpr.h
# 	2:16:DefaultSinkClass:CMsChatPr
# End Section
# Section Chappy : {011EEE45-46DF-11D0-99CB-00C04FD64497}
# 	2:5:Class:CChatItems
# 	2:10:HeaderFile:chatitems.h
# 	2:8:ImplFile:chatitems.cpp
# End Section
