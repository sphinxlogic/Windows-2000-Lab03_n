# Microsoft Developer Studio Project File - Name="gwmain" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (ALPHA) Static Library" 0x0604
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gwmain - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gwmain.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gwmain.mak" CFG="gwmain - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gwmain - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gwmain - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "gwmain - Win32 Debug Alpha" (based on "Win32 (ALPHA) Static Library")
!MESSAGE "gwmain - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "gwmain - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /O<none>
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Release\gwmain.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gwmain - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Debug\gwmain.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gwmain - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gwmain__"
# PROP BASE Intermediate_Dir "gwmain__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /MDd /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Debug\gwmain.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gwmain - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gwmain_0"
# PROP BASE Intermediate_Dir "gwmain_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Release\gwmain.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "gwmain - Win32 Release"
# Name "gwmain - Win32 Debug"
# Name "gwmain - Win32 Debug Alpha"
# Name "gwmain - Win32 Release Alpha"
# Begin Source File

SOURCE=.\GWMain.c

!IF  "$(CFG)" == "gwmain - Win32 Release"

!ELSEIF  "$(CFG)" == "gwmain - Win32 Debug"

!ELSEIF  "$(CFG)" == "gwmain - Win32 Debug Alpha"

NODEP_CPP_GWMAI=\
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
	".\inwrap.h"\
	".\msabtag.h"\
	".\onitor.h"\
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
	".\wmain.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "gwmain - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\process.c

!IF  "$(CFG)" == "gwmain - Win32 Release"

!ELSEIF  "$(CFG)" == "gwmain - Win32 Debug"

!ELSEIF  "$(CFG)" == "gwmain - Win32 Debug Alpha"

DEP_CPP_PROCE=\
	".\process.chk"\
	
NODEP_CPP_PROCE=\
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
	".\inwrap.h"\
	".\msabtag.h"\
	".\onitor.h"\
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
	".\wmain.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "gwmain - Win32 Release Alpha"

!ENDIF 

# End Source File
# End Target
# End Project
