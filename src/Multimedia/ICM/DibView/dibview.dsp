# Microsoft Developer Studio Project File - Name="dibview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=dibview - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dibview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dibview.mak" CFG="dibview - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dibview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 Debug ICM Inside DC " (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 Release ICM Inside DC" (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 Debug ICM Outside DC " (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 Release ICM Outside DC " (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 ReleaseW" (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 DebugW" (based on "Win32 (x86) Application")
!MESSAGE "dibview - Win32 AlphaDebug" (based on "Win32 (ALPHA) Application")
!MESSAGE "dibview - Win32 AlphaDebugW" (based on "Win32 (ALPHA) Application")
!MESSAGE "dibview - Win32 AlphaRelease" (based on "Win32 (ALPHA) Application")
!MESSAGE "dibview - Win32 AlphaReleaseW" (based on "Win32 (ALPHA) Application")
!MESSAGE "dibview - Win32 AlphaRelease ICM Inside DC" (based on "Win32 (ALPHA) Application")
!MESSAGE "dibview - Win32 AlphaRelease ICM Outside DC " (based on "Win32 (ALPHA) Application")
!MESSAGE "dibview - Win32 AlphaDebug ICM Inside DC " (based on "Win32 (ALPHA) Application")
!MESSAGE "dibview - Win32 AlphaDebug ICM Outside DC " (based on "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "dibview - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "InDebug"
# PROP BASE Intermediate_Dir "InDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "InDebug"
# PROP Intermediate_Dir "InDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MULTIMON_ENABLED" /D "ICM_INSIDE_DC" /FR /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "ICM_INSIDE_DC" /d "MULTIMON_ENABLED"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mscms.lib icmui.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "InRelease"
# PROP BASE Intermediate_Dir "InRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "InRelease"
# PROP Intermediate_Dir "InRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gr /Zp16 /W3 /GX /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ICM_INSIDE_DC" /D "MULTIMON_ENABLED" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "ICM_INSIDE_DC" /d "MULTIMON_ENABLED"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mscms.lib icmui.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "OutDebug"
# PROP BASE Intermediate_Dir "OutDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "OutDebug"
# PROP Intermediate_Dir "OutDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "ICM_INSIDE_DC" /D "MULTI_MONITOR_ENABLED" /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ICM_OUTSIDE_DC" /D "MULTIMON_ENABLED" /FR /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "ICM_ENABLED"
# ADD RSC /l 0x409 /d "_DEBUG" /d "ICM_OUTSIDE_DC" /d "MULTIMON_ENABLED"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib icmui.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "OutRelease"
# PROP BASE Intermediate_Dir "OutRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "OutRelease"
# PROP Intermediate_Dir "OutRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gr /Zp16 /W3 /GX /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "ICM_INSIDE_DC" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ICM_OUTSIDE_DC" /D "MULTIMON_ENABLED" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "ICM_ENABLED"
# ADD RSC /l 0x409 /d "NDEBUG" /d "ICM_OUTSIDE_DC" /d "MULTIMON_ENABLED"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib icmui.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

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
# ADD BASE CPP /nologo /Zp16 /W4 /GX /O2 /I "libjpeg" /I "tifflib" /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "MULTIMON_ENABLED" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_UNICODE" /d "UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 libjpeg\release\libjpeg.lib tifflib\release\tifflib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

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
# ADD BASE CPP /nologo /Zp16 /W4 /GX /ZI /Od /I "libjpeg" /I "tifflib" /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "MULTIMON_ENABLED" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_UNICODE" /d "UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 libjpeg\debug\libjpeg.lib tifflib\debug\tifflib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib version.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

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
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /ZI /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"pch.h" /FD /ZI /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

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
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX /FD /ZI /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /ZI /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

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
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

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
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaInRelease"
# PROP BASE Intermediate_Dir "AlphaInRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaInRelease"
# PROP Intermediate_Dir "AlphaInRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "ICM_INSIDE_DC" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "NDEBUG" /D "ICM_INSIDE_DC" /D "MULTIMON_ENABLED" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "ICM_INSIDE_DC"
# ADD RSC /l 0x409 /d "NDEBUG" /d "ICM_INSIDE_DC"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib icmui.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 mscms.lib icmui.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaOutRelease"
# PROP BASE Intermediate_Dir "AlphaOutRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaOutRelease"
# PROP Intermediate_Dir "AlphaOutRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "ICM_OUTSIDE_DC" /D "MULTIMON_ENABLED" /Yu"pch.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /I "..\inc" /D "NDEBUG" /D "ICM_OUTSIDE_DC" /D "MULTIMON_ENABLED" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Yu"pch.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "ICM_OUTSIDE_DC"
# ADD RSC /l 0x409 /d "NDEBUG" /d "ICM_OUTSIDE_DC"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib icmui.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA
# ADD LINK32 mscms.lib icmui.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaInDebug"
# PROP BASE Intermediate_Dir "AlphaInDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaInDebug"
# PROP Intermediate_Dir "AlphaInDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ICM_INSIDE_DC" /D "MULTIMON_ENABLED" /FR /YX /FD /ZI /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "_DEBUG" /D "ICM_INSIDE_DC" /D "MULTIMON_ENABLED" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /FR /Yu"pch.h" /FD /ZI /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "ICM_INSIDE_DC"
# ADD RSC /l 0x409 /d "_DEBUG" /d "ICM_INSIDE_DC"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaOutDebug"
# PROP BASE Intermediate_Dir "AlphaOutDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaOutDebug"
# PROP Intermediate_Dir "AlphaOutDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ICM_OUTSIDE_DC" /D "MULTIMON_ENABLED" /Yu"pch.h" /FD /ZI /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\inc" /D "_DEBUG" /D "ICM_OUTSIDE_DC" /D "MULTIMON_ENABLED" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /Yu"pch.h" /FD /ZI /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /o /win32 "NUL" "NUL"
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "ICM_OUTSIDE_DC"
# ADD RSC /l 0x409 /d "_DEBUG" /d "ICM_OUTSIDE_DC"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mscms.lib icmui.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 mscms.lib icmui.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /pdbtype:sept

!ENDIF 

# Begin Target

# Name "dibview - Win32 Release"
# Name "dibview - Win32 Debug"
# Name "dibview - Win32 Debug ICM Inside DC "
# Name "dibview - Win32 Release ICM Inside DC"
# Name "dibview - Win32 Debug ICM Outside DC "
# Name "dibview - Win32 Release ICM Outside DC "
# Name "dibview - Win32 ReleaseW"
# Name "dibview - Win32 DebugW"
# Name "dibview - Win32 AlphaDebug"
# Name "dibview - Win32 AlphaDebugW"
# Name "dibview - Win32 AlphaRelease"
# Name "dibview - Win32 AlphaReleaseW"
# Name "dibview - Win32 AlphaRelease ICM Inside DC"
# Name "dibview - Win32 AlphaRelease ICM Outside DC "
# Name "dibview - Win32 AlphaDebug ICM Inside DC "
# Name "dibview - Win32 AlphaDebug ICM Outside DC "
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\about.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\clipboard.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CMMman.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\construct.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\convert.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dib.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dibview.c

!IF  "$(CFG)" == "dibview - Win32 Release"

# ADD CPP /W4 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

# ADD CPP /W4 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

# ADD CPP /W4 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

# ADD CPP /W4 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

# ADD CPP /W3 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

# ADD CPP /W4 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

# ADD CPP /W4 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

# ADD CPP /W4 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

DEP_CPP_DIBVI=\
	"..\inc\check.h"\
	"..\inc\conv.h"\
	"..\inc\ICMStubs.h"\
	"..\inc\MMStubs.h"\
	"..\inc\pch.h"\
	".\dibview.h"\
	".\resource.h"\
	
NODEP_CPP_DIBVI=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yu"pch.h"
# ADD CPP /Gt0 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

DEP_CPP_DIBVI=\
	"..\inc\check.h"\
	"..\inc\conv.h"\
	"..\inc\ICMStubs.h"\
	"..\inc\MMStubs.h"\
	"..\inc\pch.h"\
	".\dibview.h"\
	".\resource.h"\
	
NODEP_CPP_DIBVI=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yu"pch.h"
# ADD CPP /Gt0 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

DEP_CPP_DIBVI=\
	"..\inc\check.h"\
	"..\inc\conv.h"\
	"..\inc\ICMStubs.h"\
	"..\inc\MMStubs.h"\
	"..\inc\pch.h"\
	".\dibview.h"\
	".\resource.h"\
	
NODEP_CPP_DIBVI=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yu"pch.h"
# ADD CPP /Gt0 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

DEP_CPP_DIBVI=\
	"..\inc\check.h"\
	"..\inc\conv.h"\
	"..\inc\ICMStubs.h"\
	"..\inc\MMStubs.h"\
	"..\inc\pch.h"\
	".\dibview.h"\
	".\resource.h"\
	
NODEP_CPP_DIBVI=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yu"pch.h"
# ADD CPP /Gt0 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

DEP_CPP_DIBVI=\
	"..\inc\check.h"\
	"..\inc\conv.h"\
	"..\inc\ICMStubs.h"\
	"..\inc\MMStubs.h"\
	"..\inc\pch.h"\
	".\dibview.h"\
	".\resource.h"\
	
NODEP_CPP_DIBVI=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yu"pch.h"
# ADD CPP /Gt0 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

DEP_CPP_DIBVI=\
	"..\inc\check.h"\
	"..\inc\conv.h"\
	"..\inc\ICMStubs.h"\
	"..\inc\MMStubs.h"\
	"..\inc\pch.h"\
	".\dibview.h"\
	".\resource.h"\
	
NODEP_CPP_DIBVI=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yu"pch.h"
# ADD CPP /Gt0 /Yu"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

DEP_CPP_DIBVI=\
	"..\inc\check.h"\
	"..\inc\conv.h"\
	"..\inc\ICMStubs.h"\
	"..\inc\MMStubs.h"\
	"..\inc\pch.h"\
	".\dibview.h"\
	".\resource.h"\
	
NODEP_CPP_DIBVI=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\document.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ffilter.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\global.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\icm.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\icon.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\implement.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mmon.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pch.c

!IF  "$(CFG)" == "dibview - Win32 Release"

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

# ADD CPP /W3 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

DEP_CPP_PCH_C=\
	"..\inc\pch.h"\
	
NODEP_CPP_PCH_C=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yc"pch.h"
# ADD CPP /Gt0 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

DEP_CPP_PCH_C=\
	"..\inc\pch.h"\
	
NODEP_CPP_PCH_C=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yc"pch.h"
# ADD CPP /Gt0 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

DEP_CPP_PCH_C=\
	"..\inc\pch.h"\
	
NODEP_CPP_PCH_C=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yc"pch.h"
# ADD CPP /Gt0 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

DEP_CPP_PCH_C=\
	"..\inc\pch.h"\
	
NODEP_CPP_PCH_C=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yc"pch.h"
# ADD CPP /Gt0 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

DEP_CPP_PCH_C=\
	"..\inc\pch.h"\
	
NODEP_CPP_PCH_C=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yc"pch.h"
# ADD CPP /Gt0 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

DEP_CPP_PCH_C=\
	"..\inc\pch.h"\
	
NODEP_CPP_PCH_C=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0 /Yc"pch.h"
# ADD CPP /Gt0 /Yc"pch.h"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

DEP_CPP_PCH_C=\
	"..\inc\pch.h"\
	
NODEP_CPP_PCH_C=\
	".\cm.h"\
	".\ti.h"\
	".\tierr.h"\
	".\tireg.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yc

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\print.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelSource.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\settings.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\twain.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\window.c

!IF  "$(CFG)" == "dibview - Win32 Release"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 Debug ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 Release ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 ReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 DebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebugW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaReleaseW"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Inside DC"

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaRelease ICM Outside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Inside DC "

!ELSEIF  "$(CFG)" == "dibview - Win32 AlphaDebug ICM Outside DC "

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bitmapwin.h
# End Source File
# Begin Source File

SOURCE=..\inc\check.h
# End Source File
# Begin Source File

SOURCE=.\CMMman.h
# End Source File
# Begin Source File

SOURCE=..\inc\conv.h
# End Source File
# Begin Source File

SOURCE=.\Convert.h
# End Source File
# Begin Source File

SOURCE=.\dibview.h
# End Source File
# Begin Source File

SOURCE=.\ffilter.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=..\inc\ICMStubs.h
# End Source File
# Begin Source File

SOURCE=.\inline.h
# End Source File
# Begin Source File

SOURCE=..\inc\MMStubs.h
# End Source File
# Begin Source File

SOURCE=..\inc\pch.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SelSource.h
# End Source File
# Begin Source File

SOURCE=..\inc\STIStubs.h
# End Source File
# Begin Source File

SOURCE=..\inc\TwainStubs.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\dibview.rc
# End Source File
# Begin Source File

SOURCE=.\imagelist.bmp
# End Source File
# End Group
# End Target
# End Project
