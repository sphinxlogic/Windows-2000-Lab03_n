# Microsoft Developer Studio Project File - Name="named" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

CFG=named - Win32 AlphaDebugW
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "named.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "named.mak" CFG="named - Win32 AlphaDebugW"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "named - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "named - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "named - Win32 DebugW" (based on "Win32 (x86) Console Application")
!MESSAGE "named - Win32 ReleaseW" (based on "Win32 (x86) Console Application")
!MESSAGE "named - Win32 AlphaDebug" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "named - Win32 AlphaDebugW" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "named - Win32 AlphaRelease" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "named - Win32 AlphaReleaseW" (based on "Win32 (ALPHA) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "named - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Zp16 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib mscms.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "named - Win32 Debug"

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
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Zp16 /W3 /GX /ZI /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib mscms.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "named - Win32 DebugW"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugW"
# PROP BASE Intermediate_Dir "DebugW"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugW"
# PROP Intermediate_Dir "DebugW"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /c
# ADD CPP /nologo /Zp16 /W3 /GX /ZI /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mscms.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mscms.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "named - Win32 ReleaseW"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseW"
# PROP BASE Intermediate_Dir "ReleaseW"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseW"
# PROP Intermediate_Dir "ReleaseW"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /c
# ADD CPP /nologo /Zp16 /W3 /GX /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mscms.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mscms.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "named - Win32 AlphaDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaDebug"
# PROP BASE Intermediate_Dir "AlphaDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaDebug"
# PROP Intermediate_Dir "AlphaDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /ZI /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /ZI /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /pdbtype:sept

!ELSEIF  "$(CFG)" == "named - Win32 AlphaDebugW"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaDebugW"
# PROP BASE Intermediate_Dir "AlphaDebugW"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaDebugW"
# PROP Intermediate_Dir "AlphaDebugW"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /ZI /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /ZI /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /pdbtype:sept

!ELSEIF  "$(CFG)" == "named - Win32 AlphaRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaRelease"
# PROP BASE Intermediate_Dir "AlphaRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaRelease"
# PROP Intermediate_Dir "AlphaRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"pch.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA

!ELSEIF  "$(CFG)" == "named - Win32 AlphaReleaseW"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaReleaseW"
# PROP BASE Intermediate_Dir "AlphaReleaseW"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaReleaseW"
# PROP Intermediate_Dir "AlphaReleaseW"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 mscms.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA

!ENDIF 

# Begin Target

# Name "named - Win32 Release"
# Name "named - Win32 Debug"
# Name "named - Win32 DebugW"
# Name "named - Win32 ReleaseW"
# Name "named - Win32 AlphaDebug"
# Name "named - Win32 AlphaDebugW"
# Name "named - Win32 AlphaRelease"
# Name "named - Win32 AlphaReleaseW"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\named.c

!IF  "$(CFG)" == "named - Win32 Release"

# ADD CPP /W4

!ELSEIF  "$(CFG)" == "named - Win32 Debug"

# ADD CPP /W4

!ELSEIF  "$(CFG)" == "named - Win32 DebugW"

# ADD CPP /W4

!ELSEIF  "$(CFG)" == "named - Win32 ReleaseW"

# ADD CPP /W4

!ELSEIF  "$(CFG)" == "named - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "named - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "named - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "named - Win32 AlphaReleaseW"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pch.c

!IF  "$(CFG)" == "named - Win32 Release"

# ADD CPP /Yc"pch.h"

!ELSEIF  "$(CFG)" == "named - Win32 Debug"

# ADD CPP /Yc"pch.h"

!ELSEIF  "$(CFG)" == "named - Win32 DebugW"

# ADD CPP /Yc"pch.h"

!ELSEIF  "$(CFG)" == "named - Win32 ReleaseW"

# ADD CPP /Yc"pch.h"

!ELSEIF  "$(CFG)" == "named - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "named - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "named - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "named - Win32 AlphaReleaseW"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\inc\check.h
# End Source File
# Begin Source File

SOURCE=.\named.h
# End Source File
# Begin Source File

SOURCE=..\inc\pch.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\named.rc
# End Source File
# End Group
# End Target
# End Project
