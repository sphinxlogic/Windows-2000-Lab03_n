# Microsoft Developer Studio Project File - Name="FileRmClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FileRmClient - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FileRmClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FileRmClient.mak" CFG="FileRmClient - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FileRmClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FileRmClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "FileRmClient - Win32 Release"
# Name "FileRmClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\cpicturectl1.cpp
# End Source File
# Begin Source File

SOURCE=.\FileRmClient.cpp
# End Source File
# Begin Source File

SOURCE=.\FileRmClient.odl
# End Source File
# Begin Source File

SOURCE=.\FileRmClient.rc

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FileRmClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\picture1.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\cpicturectl1.h
# End Source File
# Begin Source File

SOURCE=.\FileRmClient.h
# End Source File
# Begin Source File

SOURCE=.\FileRmClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\picture1.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\FileRmClient.ico
# End Source File
# Begin Source File

SOURCE=.\res\FileRmClient.rc2
# End Source File
# End Group
# End Target
# End Project
# Section FileRmClient : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture1.h
# 	2:8:ImplFile:picture1.cpp
# End Section
# Section OLE Controls
# 	{82BC17F4-4F9B-11D0-9697-00AA00C149A6}
# 	{28EFE324-4FA8-11D0-9697-00AA00C149A6}
# 	{AA34094E-4FA9-11D0-9697-00AA00C149A6}
# End Section
# Section FileRmClient : {82BC17F4-4F9B-11D0-9697-00AA00C149A6}
# 	0:9:Picture.h:C:\FileRm\FileRmClient\Picture1.h
# 	0:13:_PictureCtl.h:C:\FileRm\FileRmClient\_PictureCtl.h
# 	0:11:Picture.cpp:C:\FileRm\FileRmClient\Picture1.cpp
# 	0:15:_PictureCtl.cpp:C:\FileRm\FileRmClient\_PictureCtl.cpp
# 	2:21:DefaultSinkHeaderFile:picturectl.h
# 	2:16:DefaultSinkClass:C_PictureCtl
# End Section
# Section FileRmClient : {28EFE324-4FA8-11D0-9697-00AA00C149A6}
# 	0:13:_PictureCtl.h:C:\FileRm\FileRmClient\_PictureCtl.h
# 	0:15:_PictureCtl.cpp:C:\FileRm\FileRmClient\_PictureCtl.cpp
# 	2:21:DefaultSinkHeaderFile:cpicturectl.h
# 	2:16:DefaultSinkClass:CPictureCtl
# End Section
# Section FileRmClient : {28EFE323-4FA8-11D0-9697-00AA00C149A6}
# 	2:5:Class:CPictureCtl
# 	2:10:HeaderFile:cpicturectl.h
# 	2:8:ImplFile:cpicturectl.cpp
# End Section
# Section FileRmClient : {82BC17F3-4F9B-11D0-9697-00AA00C149A6}
# 	2:5:Class:C_PictureCtl
# 	2:10:HeaderFile:picturectl.h
# 	2:8:ImplFile:picturectl.cpp
# End Section
# Section FileRmClient : {AA3409AA-4FA9-11D0-9697-00AA00C149A6}
# 	2:5:Class:CNewPictureCtl
# 	2:10:HeaderFile:cpicturectl1.h
# 	2:8:ImplFile:cpicturectl1.cpp
# End Section
# Section FileRmClient : {AA34094E-4FA9-11D0-9697-00AA00C149A6}
# 	0:13:_PictureCtl.h:C:\FileRm\FileRmClient\_PictureCtl.h
# 	0:15:_PictureCtl.cpp:C:\FileRm\FileRmClient\_PictureCtl.cpp
# 	2:21:DefaultSinkHeaderFile:cpicturectl1.h
# 	2:16:DefaultSinkClass:CNewPictureCtl
# End Section
