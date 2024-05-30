# Microsoft Developer Studio Project File - Name="ExAdmin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (ALPHA) Static Library" 0x0604
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ExAdmin - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ExAdmin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ExAdmin.mak" CFG="ExAdmin - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ExAdmin - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ExAdmin - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ExAdmin - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Static Library")
!MESSAGE "ExAdmin - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ExAdmin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# SUBTRACT CPP /O<none>
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Release\ExAdmin.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ExAdmin_"
# PROP BASE Intermediate_Dir "ExAdmin_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Debug\ExAdmin.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ExAdmin_"
# PROP BASE Intermediate_Dir "ExAdmin_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Z7 /Od /D "WIN32" /D "_WINDOWS" /D "DEBUG" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /Z7 /Od /D "WIN32" /D "_WINDOWS" /D "DEBUG" /D "_AFXDLL" /YX /FD /MDd /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Debug\ExAdmin.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ExAdmin0"
# PROP BASE Intermediate_Dir "ExAdmin0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "_WINDOWS" /D "DEBUG" /YX /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /D "WIN32" /D "_WINDOWS" /D "DEBUG" /D "_AFXDLL" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
TargetPath=.\Release\ExAdmin.lib
SOURCE=$(InputPath)
PostBuild_Cmds=if exist $(BkOffice)\Lib copy $(TargetPath) $(BkOffice)\Lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ExAdmin - Win32 Release"
# Name "ExAdmin - Win32 Debug"
# Name "ExAdmin - Win32 Debug Alpha"
# Name "ExAdmin - Win32 Release Alpha"
# Begin Source File

SOURCE=.\exAdmin.Cpp

!IF  "$(CFG)" == "ExAdmin - Win32 Release"

# ADD CPP /MDd /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug"

# ADD CPP /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug Alpha"

DEP_CPP_EXADM=\
	".\helpers.h"\
	
NODEP_CPP_EXADM=\
	".\blogon.h"\
	".\clcls.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
	".\dkafx.h"\
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
	".\dminext.h"\
	".\entryid.h"\
	".\etcode.h"\
	".\ewpst.h"\
	".\inwrap.h"\
	".\msabtag.h"\
	".\onitor.h"\
	".\onvcwrp.h"\
	".\onvstrc.h"\
	".\pcpub.h"\
	".\roptag.h"\
	".\rrCpp.H"\
	".\rrCppD.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\ulecls.h"\
	".\wreport.h"\
	".\xAdmin.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /D "_WINDLL" /D "_USRDLL"
# ADD CPP /Gt0 /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Release Alpha"

DEP_CPP_EXADM=\
	".\helpers.h"\
	
NODEP_CPP_EXADM=\
	".\blogon.h"\
	".\clcls.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
	".\dkafx.h"\
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
	".\dminext.h"\
	".\entryid.h"\
	".\etcode.h"\
	".\ewpst.h"\
	".\inwrap.h"\
	".\msabtag.h"\
	".\onitor.h"\
	".\onvcwrp.h"\
	".\onvstrc.h"\
	".\pcpub.h"\
	".\roptag.h"\
	".\rrCpp.H"\
	".\rrCppD.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\ulecls.h"\
	".\wreport.h"\
	".\xAdmin.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /D "_WINDLL" /D "_USRDLL"
# ADD CPP /Gt0 /D "_WINDLL" /D "_USRDLL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\showpage.Cpp

!IF  "$(CFG)" == "ExAdmin - Win32 Release"

# ADD CPP /MDd /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug"

# ADD CPP /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug Alpha"

NODEP_CPP_SHOWP=\
	".\blogon.h"\
	".\clcls.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
	".\dkafx.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /D "_WINDLL" /D "_USRDLL"
# ADD CPP /Gt0 /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Release Alpha"

NODEP_CPP_SHOWP=\
	".\blogon.h"\
	".\clcls.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
	".\dkafx.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /D "_WINDLL" /D "_USRDLL"
# ADD CPP /Gt0 /D "_WINDLL" /D "_USRDLL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Strtpage.Cpp

!IF  "$(CFG)" == "ExAdmin - Win32 Release"

# ADD CPP /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug"

# ADD CPP /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Debug Alpha"

NODEP_CPP_STRTP=\
	".\blogon.h"\
	".\clcls.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
	".\dkafx.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /D "_WINDLL" /D "_USRDLL"
# ADD CPP /Gt0 /D "_WINDLL" /D "_USRDLL"

!ELSEIF  "$(CFG)" == "ExAdmin - Win32 Release Alpha"

NODEP_CPP_STRTP=\
	".\blogon.h"\
	".\clcls.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
	".\dkafx.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /D "_WINDLL" /D "_USRDLL"
# ADD CPP /Gt0 /D "_WINDLL" /D "_USRDLL"

!ENDIF 

# End Source File
# End Target
# End Project
