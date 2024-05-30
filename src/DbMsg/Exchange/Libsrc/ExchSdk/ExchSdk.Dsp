# Microsoft Developer Studio Project File - Name="Exchsdk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (ALPHA) Static Library" 0x0604
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Exchsdk - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ExchSdk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ExchSdk.mak" CFG="Exchsdk - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Exchsdk - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Exchsdk - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Exchsdk - Win32 Debug Alpha" (based on "Win32 (ALPHA) Static Library")
!MESSAGE "Exchsdk - Win32 Release Alpha" (based on "Win32 (ALPHA) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32\Release"
# PROP BASE Intermediate_Dir "Win32\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32\Release"
# PROP Intermediate_Dir "Win32\Release"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /X /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 dapi.lib rtflib32.lib sadapi.lib mapiw32.lib mapi32.lib /nologo
# Begin Special Build Tool
TargetPath=.\Win32\Release\ExchSdk.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist "$(MSSDK)\Lib" copy "$(TargetPath)" "$(MSSDK)\Lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32\Debug"
# PROP BASE Intermediate_Dir "Win32\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32\Debug"
# PROP Intermediate_Dir "Win32\Debug"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 dapi.lib rtflib32.lib sadapi.lib mapiw32.lib mapi32.lib /nologo
# Begin Special Build Tool
TargetPath=.\Win32\Debug\ExchSdk.lib
TargetName=ExchSdk
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist "$(MSSDK)\Lib" copy "$(TargetPath)" "$(MSSDK)\Lib\$(TargetName)D.lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Exchsdk_"
# PROP BASE Intermediate_Dir "Exchsdk_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32\Debug"
# PROP Intermediate_Dir "Win32\Debug"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 dapi.lib rtflib32.lib sadapi.lib mapiw32.lib mapi32.lib /nologo
# ADD LIB32 dapi.lib rtflib32.lib sadapi.lib mapiw32.lib mapi32.lib /nologo
# Begin Special Build Tool
TargetPath=.\Win32\Debug\ExchSdk.lib
TargetName=ExchSdk
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist "$(MSSDK)\Lib" copy "$(TargetPath)" "$(MSSDK)\Lib\$(TargetName)D.lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Exchsdk0"
# PROP BASE Intermediate_Dir "Exchsdk0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32\Release"
# PROP Intermediate_Dir "Win32\Release"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 dapi.lib rtflib32.lib sadapi.lib mapiw32.lib mapi32.lib /nologo
# ADD LIB32 dapi.lib rtflib32.lib sadapi.lib mapiw32.lib mapi32.lib /nologo
# Begin Special Build Tool
TargetPath=.\Win32\Release\ExchSdk.lib
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist "$(MSSDK)\Lib" copy "$(TargetPath)" "$(MSSDK)\Lib"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Exchsdk - Win32 Release"
# Name "Exchsdk - Win32 Debug"
# Name "Exchsdk - Win32 Debug Alpha"
# Name "Exchsdk - Win32 Release Alpha"
# Begin Source File

SOURCE=..\EXAdmin\Win32\Debug\EXAdmin.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AddrLkup\Win32\Debug\AddrLkup.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKCfg\Win32\Debug\EDKCfg.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKDebug\Win32\Debug\EDKDebug.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKEvent\Win32\Debug\EDKEvent.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKGUID\Win32\Debug\EDKGUID.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKMAPI\Win32\Debug\EDKMAPI.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKMsg\Win32\Debug\EDKMsg.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKTrack\Win32\Debug\EDKTrack.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKUtils\Win32\Debug\EDKUtils.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\ExchInst\Win32\Debug\ExchInst.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GWMain\Win32\Debug\GWMain.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GWReport\Win32\Debug\GWReport.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MBLogon\Win32\Debug\MBLogon.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MesgXlat\Win32\Debug\MesgXlat.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Monitor\Win32\Debug\Monitor.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\NewPst\Win32\Debug\NewPst.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Stats\Win32\Debug\Stats.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\WinWrap\Win32\Debug\WinWrap.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GWPerf\Win32\Debug\GWPerf.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EXAdmin\Win32\Release\EXAdmin.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AddrLkup\Win32\Release\AddrLkup.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKCfg\Win32\Release\EDKCfg.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKDebug\Win32\Release\EDKDebug.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKEvent\Win32\Release\EDKEvent.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKGUID\Win32\Release\EDKGUID.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKMAPI\Win32\Release\EDKMAPI.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKMsg\Win32\Release\EDKMsg.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKTrack\Win32\Release\EDKTrack.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EDKUtils\Win32\Release\EDKUtils.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\ExchInst\Win32\Release\ExchInst.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GWMain\Win32\Release\GWMain.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GWReport\Win32\Release\GWReport.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MBLogon\Win32\Release\MBLogon.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MesgXlat\Win32\Release\MesgXlat.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Monitor\Win32\Release\Monitor.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\NewPst\Win32\Release\NewPst.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Stats\Win32\Release\Stats.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\WinWrap\Win32\Release\WinWrap.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GWPerf\Win32\Release\GWPerf.Lib

!IF  "$(CFG)" == "Exchsdk - Win32 Release"

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Debug Alpha"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Exchsdk - Win32 Release Alpha"

!ENDIF 

# End Source File
# End Target
# End Project
