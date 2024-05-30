# Microsoft Developer Studio Project File - Name="WBEMSample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=WBEMSample - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WBEMSample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WBEMSample.mak" CFG="WBEMSample - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WBEMSample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WBEMSample - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "WBEMSample - Win32 ANSI Debug" (based on "Win32 (x86) Application")
!MESSAGE "WBEMSample - Win32 ANSI Release" (based on "Win32 (x86) Application")
!MESSAGE "WBEMSample - Win32 Alpha Release" (based on "Win32 (ALPHA) Application")
!MESSAGE "WBEMSample - Win32 Alpha Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_WIN32_DCOM" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 mfc42u.lib wbemuuid.lib oleaut32.lib ole32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"MSVCRT.lib" /libpath:"..\..\..\lib"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_UNICODE" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_WIN32_DCOM" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mfco42ud.lib wbemuuid.lib oleaut32.lib ole32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\lib"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WBEMSamp"
# PROP BASE Intermediate_Dir "WBEMSamp"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WBEMSamp"
# PROP Intermediate_Dir "WBEMSamp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D _WIN32_WINNT=0x0400 /D "_UNICODE" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_WIN32_DCOM" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oleaut32.lib ole32.lib mfco42ud.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wbemuuid.lib mfco42d.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"libc.lib" /pdbtype:sept /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /verbose /nodefaultlib

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WBEMSam0"
# PROP BASE Intermediate_Dir "WBEMSam0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WBEMSam0"
# PROP Intermediate_Dir "WBEMSam0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D _WIN32_WINNT=0x0400 /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_WIN32_DCOM" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oleaut32.lib ole32.lib mfco42u.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
# ADD LINK32 mfc42.lib wbemuuid.lib oleaut32.lib ole32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"MSVCRT.lib" /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WBEMSample___Win32_Alpha_Release"
# PROP BASE Intermediate_Dir "WBEMSample___Win32_Alpha_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Alpha_Release"
# PROP Intermediate_Dir "Alpha_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_DEBUG" /D "_WIN32_DCOM" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_DEBUG" /D "_WIN32_DCOM" /D "_AFXDLL" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mfc42u.lib wbemuuid.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:ALPHA /nodefaultlib:"MSVCRT.lib"
# ADD LINK32 mfc42u.lib wbemuuid.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:ALPHA /nodefaultlib:"MSVCRT.lib"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WBEMSample___Win32_Alpha_Debug"
# PROP BASE Intermediate_Dir "WBEMSample___Win32_Alpha_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Alpha_Debug"
# PROP Intermediate_Dir "Alpha_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_WIN32_DCOM" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MDd /Gt0 /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_WIN32_DCOM" /D "_AFXDLL" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mfco42ud.lib wbemuuid.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:ALPHA /pdbtype:sept
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 mfco42ud.lib wbemuuid.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:ALPHA /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "WBEMSample - Win32 Release"
# Name "WBEMSample - Win32 Debug"
# Name "WBEMSample - Win32 ANSI Debug"
# Name "WBEMSample - Win32 ANSI Release"
# Name "WBEMSample - Win32 Alpha Release"
# Name "WBEMSample - Win32 Alpha Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\OfficeDlg.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnAddEquipment.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnAsync.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnConnect.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnDiskDetails.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnDiskPropsDescriptions.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnEnumDisks.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnEnumSvcs.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnPerm.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnRegister.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OnTemp.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\UserInfo.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WBEMSamp.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WBEMSampdlg.cpp

!IF  "$(CFG)" == "WBEMSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "WBEMSample - Win32 Alpha Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WBEMSample.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\OfficeDlg.h
# End Source File
# Begin Source File

SOURCE=.\OnAsync.h
# End Source File
# Begin Source File

SOURCE=.\OnTemp.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UserInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\idl\wbemcli.h
# End Source File
# Begin Source File

SOURCE=.\WBEMSamp.h
# End Source File
# Begin Source File

SOURCE=.\WBEMSampdlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\WBEMSample.ico
# End Source File
# Begin Source File

SOURCE=.\res\WBEMSample.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
