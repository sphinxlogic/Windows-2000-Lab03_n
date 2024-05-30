# Microsoft Developer Studio Project File - Name="MbxAdmin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=MbxAdmin - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MbxAdmin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MbxAdmin.mak" CFG="MbxAdmin - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MbxAdmin - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MbxAdmin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MbxAdmin - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "MbxAdmin - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "MbxAdmin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 exchsdk.lib mapi32.lib version.lib uuid.lib shell32.lib oldnames.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"mfcs42.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"mfc42.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib exchsdkd.lib mapi32.lib oldnames.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MbxAdmin"
# PROP BASE Intermediate_Dir "MbxAdmin"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_WINDOWS" /D "DEBUG" /YX /FD /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_WINDOWS" /D "DEBUG" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib exchsdkd.lib mapi32.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /nodefaultlib:"nafxcwd.lib" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 version.lib exchsdkd.lib mapi32.lib oldnames.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /nodefaultlib:"nafxcwd.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MbxAdmi0"
# PROP BASE Intermediate_Dir "MbxAdmi0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "_WINDOWS" /D "DEBUG" /YX /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "_WINDOWS" /D "DEBUG" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 exchsdk.lib mapi32.lib version.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"mfcs42.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"mfc42.lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 exchsdk.lib mapi32.lib version.lib oldnames.lib uuid.lib shell32.lib /nologo /subsystem:windows /dll /machine:ALPHA /nodefaultlib:"nafxcw.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MbxAdmin - Win32 Release"
# Name "MbxAdmin - Win32 Debug"
# Name "MbxAdmin - Win32 Debug Alpha"
# Name "MbxAdmin - Win32 Release Alpha"
# Begin Source File

SOURCE=.\Global.Cpp

!IF  "$(CFG)" == "MbxAdmin - Win32 Release"

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Debug"

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Debug Alpha"

DEP_CPP_GLOBA=\
	".\mbxadmin.h"\
	{$(INCLUDE)}"_entryid.h"\
	{$(INCLUDE)}"aclcls.h"\
	{$(INCLUDE)}"aclsid.h"\
	{$(INCLUDE)}"addrlkup.h"\
	{$(INCLUDE)}"adminext.h"\
	{$(INCLUDE)}"convcwrp.h"\
	{$(INCLUDE)}"convstrc.h"\
	{$(INCLUDE)}"edk.h"\
	{$(INCLUDE)}"edkafx.h"\
	{$(INCLUDE)}"edkcfg.h"\
	{$(INCLUDE)}"edkcode.h"\
	{$(INCLUDE)}"edkdebug.h"\
	{$(INCLUDE)}"edkevent.h"\
	{$(INCLUDE)}"edkguid.h"\
	{$(INCLUDE)}"edkmapi.h"\
	{$(INCLUDE)}"edkmdb.h"\
	{$(INCLUDE)}"edkmsg.h"\
	{$(INCLUDE)}"edktrack.h"\
	{$(INCLUDE)}"EdkUtCPP.H"\
	{$(INCLUDE)}"edkutils.h"\
	{$(INCLUDE)}"emsabtag.h"\
	{$(INCLUDE)}"errcpp.h"\
	{$(INCLUDE)}"ErrCppD.h"\
	{$(INCLUDE)}"exadmin.h"\
	{$(INCLUDE)}"exchinst.h"\
	{$(INCLUDE)}"gwreport.h"\
	{$(INCLUDE)}"mblogon.h"\
	{$(INCLUDE)}"monitor.h"\
	{$(INCLUDE)}"newpst.h"\
	{$(INCLUDE)}"proptag.h"\
	{$(INCLUDE)}"rclsid.h"\
	{$(INCLUDE)}"retcode.h"\
	{$(INCLUDE)}"rpcpub.h"\
	{$(INCLUDE)}"rtflib.h"\
	{$(INCLUDE)}"rulecls.h"\
	{$(INCLUDE)}"stats.h"\
	{$(INCLUDE)}"stattype.h"\
	{$(INCLUDE)}"vsof.h"\
	{$(INCLUDE)}"vsop.h"\
	{$(INCLUDE)}"vsopcsid.h"\
	{$(INCLUDE)}"winwrap.h"\
	

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Release Alpha"

DEP_CPP_GLOBA=\
	".\mbxadmin.h"\
	{$(INCLUDE)}"_entryid.h"\
	{$(INCLUDE)}"aclcls.h"\
	{$(INCLUDE)}"aclsid.h"\
	{$(INCLUDE)}"addrlkup.h"\
	{$(INCLUDE)}"adminext.h"\
	{$(INCLUDE)}"convcwrp.h"\
	{$(INCLUDE)}"convstrc.h"\
	{$(INCLUDE)}"edk.h"\
	{$(INCLUDE)}"edkafx.h"\
	{$(INCLUDE)}"edkcfg.h"\
	{$(INCLUDE)}"edkcode.h"\
	{$(INCLUDE)}"edkdebug.h"\
	{$(INCLUDE)}"edkevent.h"\
	{$(INCLUDE)}"edkguid.h"\
	{$(INCLUDE)}"edkmapi.h"\
	{$(INCLUDE)}"edkmdb.h"\
	{$(INCLUDE)}"edkmsg.h"\
	{$(INCLUDE)}"edktrack.h"\
	{$(INCLUDE)}"EdkUtCPP.H"\
	{$(INCLUDE)}"edkutils.h"\
	{$(INCLUDE)}"emsabtag.h"\
	{$(INCLUDE)}"errcpp.h"\
	{$(INCLUDE)}"ErrCppD.h"\
	{$(INCLUDE)}"exadmin.h"\
	{$(INCLUDE)}"exchinst.h"\
	{$(INCLUDE)}"gwreport.h"\
	{$(INCLUDE)}"mblogon.h"\
	{$(INCLUDE)}"monitor.h"\
	{$(INCLUDE)}"newpst.h"\
	{$(INCLUDE)}"proptag.h"\
	{$(INCLUDE)}"rclsid.h"\
	{$(INCLUDE)}"retcode.h"\
	{$(INCLUDE)}"rpcpub.h"\
	{$(INCLUDE)}"rtflib.h"\
	{$(INCLUDE)}"rulecls.h"\
	{$(INCLUDE)}"stats.h"\
	{$(INCLUDE)}"stattype.h"\
	{$(INCLUDE)}"vsof.h"\
	{$(INCLUDE)}"vsop.h"\
	{$(INCLUDE)}"vsopcsid.h"\
	{$(INCLUDE)}"winwrap.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MbxAdmin.Cpp

!IF  "$(CFG)" == "MbxAdmin - Win32 Release"

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Debug"

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Debug Alpha"

DEP_CPP_MBXAD=\
	".\mbxadmin.h"\
	{$(INCLUDE)}"_entryid.h"\
	{$(INCLUDE)}"aclcls.h"\
	{$(INCLUDE)}"aclsid.h"\
	{$(INCLUDE)}"addrlkup.h"\
	{$(INCLUDE)}"adminext.h"\
	{$(INCLUDE)}"convcwrp.h"\
	{$(INCLUDE)}"convstrc.h"\
	{$(INCLUDE)}"edk.h"\
	{$(INCLUDE)}"edkafx.h"\
	{$(INCLUDE)}"edkcfg.h"\
	{$(INCLUDE)}"edkcode.h"\
	{$(INCLUDE)}"edkdebug.h"\
	{$(INCLUDE)}"edkevent.h"\
	{$(INCLUDE)}"edkguid.h"\
	{$(INCLUDE)}"edkmapi.h"\
	{$(INCLUDE)}"edkmdb.h"\
	{$(INCLUDE)}"edkmsg.h"\
	{$(INCLUDE)}"edktrack.h"\
	{$(INCLUDE)}"EdkUtCPP.H"\
	{$(INCLUDE)}"edkutils.h"\
	{$(INCLUDE)}"emsabtag.h"\
	{$(INCLUDE)}"exadmin.h"\
	{$(INCLUDE)}"exchinst.h"\
	{$(INCLUDE)}"gwreport.h"\
	{$(INCLUDE)}"mblogon.h"\
	{$(INCLUDE)}"mbxdata.h"\
	{$(INCLUDE)}"monitor.h"\
	{$(INCLUDE)}"newpst.h"\
	{$(INCLUDE)}"proptag.h"\
	{$(INCLUDE)}"rclsid.h"\
	{$(INCLUDE)}"retcode.h"\
	{$(INCLUDE)}"rpcpub.h"\
	{$(INCLUDE)}"rtflib.h"\
	{$(INCLUDE)}"rulecls.h"\
	{$(INCLUDE)}"stats.h"\
	{$(INCLUDE)}"stattype.h"\
	{$(INCLUDE)}"vsof.h"\
	{$(INCLUDE)}"vsop.h"\
	{$(INCLUDE)}"vsopcsid.h"\
	{$(INCLUDE)}"winwrap.h"\
	

!ELSEIF  "$(CFG)" == "MbxAdmin - Win32 Release Alpha"

DEP_CPP_MBXAD=\
	".\mbxadmin.h"\
	{$(INCLUDE)}"_entryid.h"\
	{$(INCLUDE)}"aclcls.h"\
	{$(INCLUDE)}"aclsid.h"\
	{$(INCLUDE)}"addrlkup.h"\
	{$(INCLUDE)}"adminext.h"\
	{$(INCLUDE)}"convcwrp.h"\
	{$(INCLUDE)}"convstrc.h"\
	{$(INCLUDE)}"edk.h"\
	{$(INCLUDE)}"edkafx.h"\
	{$(INCLUDE)}"edkcfg.h"\
	{$(INCLUDE)}"edkcode.h"\
	{$(INCLUDE)}"edkdebug.h"\
	{$(INCLUDE)}"edkevent.h"\
	{$(INCLUDE)}"edkguid.h"\
	{$(INCLUDE)}"edkmapi.h"\
	{$(INCLUDE)}"edkmdb.h"\
	{$(INCLUDE)}"edkmsg.h"\
	{$(INCLUDE)}"edktrack.h"\
	{$(INCLUDE)}"EdkUtCPP.H"\
	{$(INCLUDE)}"edkutils.h"\
	{$(INCLUDE)}"emsabtag.h"\
	{$(INCLUDE)}"exadmin.h"\
	{$(INCLUDE)}"exchinst.h"\
	{$(INCLUDE)}"gwreport.h"\
	{$(INCLUDE)}"mblogon.h"\
	{$(INCLUDE)}"mbxdata.h"\
	{$(INCLUDE)}"monitor.h"\
	{$(INCLUDE)}"newpst.h"\
	{$(INCLUDE)}"proptag.h"\
	{$(INCLUDE)}"rclsid.h"\
	{$(INCLUDE)}"retcode.h"\
	{$(INCLUDE)}"rpcpub.h"\
	{$(INCLUDE)}"rtflib.h"\
	{$(INCLUDE)}"rulecls.h"\
	{$(INCLUDE)}"stats.h"\
	{$(INCLUDE)}"stattype.h"\
	{$(INCLUDE)}"vsof.h"\
	{$(INCLUDE)}"vsop.h"\
	{$(INCLUDE)}"vsopcsid.h"\
	{$(INCLUDE)}"winwrap.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MbxAdmin.Def
# End Source File
# Begin Source File

SOURCE=.\MbxAdmin.Rc
# End Source File
# End Target
# End Project
