# Microsoft Developer Studio Project File - Name="test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=test - Win32 Alpha Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dxetest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dxetest.mak" CFG="test - Win32 Alpha Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "test - Win32 Alpha Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "test - Win32 Alpha Release" (based on "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "test - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include\dt" /I "..\..\include\d3drm" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D _X86_=1 /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib d3drm.lib ddraw.lib /nologo /subsystem:windows /machine:I386 /out:"Release\Effect Tool.Exe"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /GX /Od /I "..\..\include\dt" /I "..\..\include\d3drm" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D _X86_=1 /Yu"stdafx.h" /FD /ZI /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib d3drm.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug\Effect Tool.Exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___W"
# PROP BASE Intermediate_Dir "test___W"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "test___W"
# PROP Intermediate_Dir "test___W"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /o /win32 "NUL"
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /I "..\..\include\dt" /I "..\..\include\d3drm" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D _X86_=1 /D "_AFXDLL" /Yu"stdafx.h" /FD /ZI /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_NOT_X86" /D _ALPHA_=1 /D ALPHA=1 /D "_AFXDLL" /Yu"stdafx.h" /FD /ZI /c
# SUBTRACT CPP /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ddraw.lib d3drm.lib winmm.lib /nologo /subsystem:windows /debug /machine:ALPHA /out:"Debug\Effect Tool.Exe" /pdbtype:sept
# ADD LINK32 ddraw.lib d3drm.lib winmm.lib /nologo /subsystem:windows /debug /machine:ALPHA /out:"Debug\Effect Tool.Exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "test___0"
# PROP BASE Intermediate_Dir "test___0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "test___0"
# PROP Intermediate_Dir "test___0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /o /win32 "NUL"
CPP=cl.exe
# ADD BASE CPP /nologo /MD /Gt0 /W3 /GX /O2 /I "..\..\include\dt" /I "..\..\include\d3drm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D _X86_=1 /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_NOT_X86" /D _ALPHA_=1 /D ALPHA=1 /D "_AFXDLL" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib d3drm.lib ddraw.lib /nologo /subsystem:windows /machine:ALPHA /out:"Release\Effect Tool.Exe"
# ADD LINK32 winmm.lib d3drm.lib ddraw.lib /nologo /subsystem:windows /machine:ALPHA /out:"Release\Effect Tool.Exe"

!ENDIF 

# Begin Target

# Name "test - Win32 Release"
# Name "test - Win32 Debug"
# Name "test - Win32 Alpha Debug"
# Name "test - Win32 Alpha Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dxedlg.cpp

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dxedoc.cpp

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dxeframe.cpp

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dxeguids.c

!IF  "$(CFG)" == "test - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

# ADD BASE CPP /Gt0
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

# ADD BASE CPP /Gt0
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dxetest.cpp

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dxetest.rc
# End Source File
# Begin Source File

SOURCE=.\dxeview.cpp

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "test - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Debug"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "test - Win32 Alpha Release"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dxedlg.h
# End Source File
# Begin Source File

SOURCE=.\dxedoc.h
# End Source File
# Begin Source File

SOURCE=.\dxeframe.h
# End Source File
# Begin Source File

SOURCE=.\dxetest.h
# End Source File
# Begin Source File

SOURCE=.\dxeview.h
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

SOURCE=.\res\dxedoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\dxetest.ico
# End Source File
# Begin Source File

SOURCE=.\res\dxetest.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\test.reg
# End Source File
# End Target
# End Project
