# Microsoft Developer Studio Project File - Name="MtsSdkPs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MtsSdkPs - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MtsSdkps.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MtsSdkps.mak" CFG="MtsSdkPs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MtsSdkPs - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MtsSdkPs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MtsSdkPs - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\Inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "REGISTER_PROXY_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Special Build Tool
TargetPath=.\Release\MtsSdkps.dll
SOURCE=$(InputPath)
PostBuild_Desc=Registering Proxy Stub DLL
PostBuild_Cmds=regsvr32 /s /c "$(TargetPath)" 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MtsSdkPs - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\Inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "REGISTER_PROXY_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
TargetPath=.\Debug\MtsSdkps.dll
SOURCE=$(InputPath)
PostBuild_Desc=Registering Proxy Stub DLL
PostBuild_Cmds=regsvr32 /s /c "$(TargetPath)" 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MtsSdkPs - Win32 Release"
# Name "MtsSdkPs - Win32 Debug"
# Begin Source File

SOURCE=.\CopyFileRm.idl

!IF  "$(CFG)" == "MtsSdkPs - Win32 Release"

# Begin Custom Build
InputPath=.\CopyFileRm.idl

BuildCmds= \
	midl /Oicf /h "..\inc\CopyFileRm.h" /tlb "..\inc\CopyFileRm.tlb" /iid\
    "..\inc\CopyFileRm_i.c"  "CopyFileRm.idl"

"CopyFileRm.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CopyFileRm_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CopyFileRm.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MtsSdkPs - Win32 Debug"

# Begin Custom Build
InputPath=.\CopyFileRm.idl

BuildCmds= \
	midl /Oicf /h "..\inc\CopyFileRm.h" /tlb "..\inc\CopyFileRm.tlb" /iid\
    "..\inc\CopyFileRm_i.c"  "CopyFileRm.idl"

"..\Inc\CopyFileRm.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\Inc\CopyFileRm_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\Inc\CopyFileRm.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CopyFileRm_p.c
# End Source File
# Begin Source File

SOURCE=.\dlldata.c
# End Source File
# Begin Source File

SOURCE=.\iid.c
# End Source File
# Begin Source File

SOURCE=.\MtsSdkPs.def
# End Source File
# Begin Source File

SOURCE=.\SimpleLog.idl

!IF  "$(CFG)" == "MtsSdkPs - Win32 Release"

# Begin Custom Build
InputPath=.\SimpleLog.idl

BuildCmds= \
	midl /Oicf /h "..\inc\SimpleLog.h" /tlb "..\inc\SimpleLog.tlb" /iid\
    "..\inc\SimpleLog_i.c"  "SimpleLog.idl"

"SimpleLog.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"SimpleLog.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"SimpleLog_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MtsSdkPs - Win32 Debug"

# Begin Custom Build
InputPath=.\SimpleLog.idl

BuildCmds= \
	midl /Oicf /h "..\inc\SimpleLog.h" /tlb "..\inc\SimpleLog.tlb" /iid\
    "..\inc\SimpleLog_i.c"  "SimpleLog.idl"

"..\Inc\SimpleLog.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\Inc\SimpleLog.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\Inc\SimpleLog_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SimpleLog_p.c
# End Source File
# End Target
# End Project
