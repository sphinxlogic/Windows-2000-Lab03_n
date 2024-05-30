# Microsoft Developer Studio Project File - Name="gwperf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=gwperf - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gwperf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gwperf.mak" CFG="gwperf - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gwperf - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gwperf - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gwperf - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "gwperf - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "gwperf - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /O<none>
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 edkdebug.lib monitor.lib edkevent.lib edkutils.lib uuid.lib oldnames.lib shell32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /def:".\GWPerf.Def"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\gwperf.dll
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /Gy /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 edkdebug.lib monitor.lib edkevent.lib edkutils.lib uuid.lib oldnames.lib shell32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Debug\gwperf.dll
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gwperf__"
# PROP BASE Intermediate_Dir "gwperf__"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /Gy /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /MTd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /Gy /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /MDd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 edkdebug.lib monitor.lib edkevent.lib edkutils.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /nodefaultlib:"libc" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 edkdebug.lib monitor.lib edkevent.lib edkutils.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /nodefaultlib:"libc" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Debug\gwperf.dll
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gwperf - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gwperf_0"
# PROP BASE Intermediate_Dir "gwperf_0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 edkdebug.lib monitor.lib edkevent.lib edkutils.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /def:".\GWPerf.Def"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 edkdebug.lib monitor.lib edkevent.lib edkutils.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /def:".\GWPerf.Def"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\gwperf.dll
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "gwperf - Win32 Release"
# Name "gwperf - Win32 Debug"
# Name "gwperf - Win32 Debug Alpha"
# Name "gwperf - Win32 Release Alpha"
# Begin Source File

SOURCE=.\allres.Rc
# End Source File
# Begin Source File

SOURCE=.\GWPerf.c

!IF  "$(CFG)" == "gwperf - Win32 Release"

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug"

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug Alpha"

NODEP_CPP_GWPER=\
	".\blogon.h"\
	".\clcls.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
	".\dkcfg.h"\
	".\dkcode.h"\
	".\dkdebug.h"\
	".\dkevent.h"\
	".\dkguid.h"\
	".\dkmapi.h"\
	".\dkmdb.h"\
	".\dkmsg.h"\
	".\dktrack.h"\
	".\dkUtCPP.H"\
	".\dkutils.h"\
	".\entryid.h"\
	".\ewpst.h"\
	".\gwperfm.h"\
	".\inwrap.h"\
	".\msabtag.h"\
	".\onitor.h"\
	".\onshare.h"\
	".\onvcwrp.h"\
	".\onvstrc.h"\
	".\pcpub.h"\
	".\roptag.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\ulecls.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "gwperf - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GWPerf.Def

!IF  "$(CFG)" == "gwperf - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug"

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "gwperf - Win32 Release Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gwperfm.mc

!IF  "$(CFG)" == "gwperf - Win32 Release"

# Begin Custom Build
InputPath=.\gwperfm.mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s gwperfm.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug"

# Begin Custom Build
InputPath=.\gwperfm.mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s gwperfm.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "gwperf - Win32 Debug Alpha"

# Begin Custom Build
InputPath=.\gwperfm.mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s gwperfm.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "gwperf - Win32 Release Alpha"

# Begin Custom Build
InputPath=.\gwperfm.mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s gwperfm.mc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Msg00001.bin
# End Source File
# End Target
# End Project
