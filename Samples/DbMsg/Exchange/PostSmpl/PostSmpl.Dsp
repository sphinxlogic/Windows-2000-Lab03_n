# Microsoft Developer Studio Project File - Name="Postsmpl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=Postsmpl - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Postsmpl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Postsmpl.mak" CFG="Postsmpl - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Postsmpl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Postsmpl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Postsmpl - Win32 Debug Alpha" (based on "Win32 (ALPHA) Application")
!MESSAGE "Postsmpl - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 exchsdk.lib msvcrt.lib mapi32.lib ole32.lib version.lib uuid.lib shell32.lib oldnames.lib comctl32.lib msvcrtd.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"msvcrtd.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 exchsdkd.lib mapi32.lib ole32.lib version.lib uuid.lib shell32.lib oldnames.lib comctl32.lib msvcrtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

# PROP BASE Use_MFC 4
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Postsmpl"
# PROP BASE Intermediate_Dir "Postsmpl"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 exchsdkd.lib mapi32.lib version.lib oldnames.lib comctl32.lib msvcrtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 exchsdkd.lib mapi32.lib version.lib oldnames.lib comctl32.lib msvcrtd.lib /nologo /subsystem:windows /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

# PROP BASE Use_MFC 4
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Postsmp0"
# PROP BASE Intermediate_Dir "Postsmp0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 exchsdk.lib msvcrt.lib mapi32.lib version.lib oldnames.lib comctl32.lib msvcrtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"msvcrtd.lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 exchsdk.lib msvcrt.lib mapi32.lib version.lib oldnames.lib comctl32.lib msvcrtd.lib /nologo /subsystem:windows /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"msvcrtd.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Postsmpl - Win32 Release"
# Name "Postsmpl - Win32 Debug"
# Name "Postsmpl - Win32 Debug Alpha"
# Name "Postsmpl - Win32 Release Alpha"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FldPick.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_FLDPI=\
	".\fldpick.h"\
	".\PostData.h"\
	".\Postsmpl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FreeDoc.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_FREED=\
	".\freedoc.h"\
	".\PostData.h"\
	".\Postsmpl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"_entryid.h"\
	{$(INCLUDE)}"aclcls.h"\
	{$(INCLUDE)}"aclsid.h"\
	{$(INCLUDE)}"addrlkup.h"\
	{$(INCLUDE)}"convcwrp.h"\
	{$(INCLUDE)}"convstrc.h"\
	{$(INCLUDE)}"edk.h"\
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
	{$(INCLUDE)}"exchinst.h"\
	{$(INCLUDE)}"gwreport.h"\
	{$(INCLUDE)}"mblogon.h"\
	{$(INCLUDE)}"monitor.h"\
	{$(INCLUDE)}"newpst.h"\
	{$(INCLUDE)}"proptag.h"\
	{$(INCLUDE)}"rclsid.h"\
	{$(INCLUDE)}"rpcpub.h"\
	{$(INCLUDE)}"rtflib.h"\
	{$(INCLUDE)}"rulecls.h"\
	{$(INCLUDE)}"stats.h"\
	{$(INCLUDE)}"stattype.h"\
	{$(INCLUDE)}"vsof.h"\
	{$(INCLUDE)}"vsop.h"\
	{$(INCLUDE)}"vsopcsid.h"\
	{$(INCLUDE)}"winwrap.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MaInfrm.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Postsmpl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PostData.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_POSTD=\
	".\fldpick.h"\
	".\freedoc.h"\
	".\PostData.h"\
	".\Postsmpl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PostDoc.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_POSTDO=\
	".\freedoc.h"\
	".\PostData.h"\
	".\PostDoc.h"\
	".\Postsmpl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Postsmpl.cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_POSTS=\
	".\MainFrm.h"\
	".\PostData.h"\
	".\PostDoc.h"\
	".\Postsmpl.h"\
	".\PostView.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	".\SummInfo.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Postsmpl.rc

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PostView.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_POSTV=\
	".\freedoc.h"\
	".\PostData.h"\
	".\PostDoc.h"\
	".\Postsmpl.h"\
	".\PostView.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Propset.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_PROPS=\
	".\freedoc.h"\
	".\Postsmpl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"_entryid.h"\
	{$(INCLUDE)}"aclcls.h"\
	{$(INCLUDE)}"aclsid.h"\
	{$(INCLUDE)}"addrlkup.h"\
	{$(INCLUDE)}"convcwrp.h"\
	{$(INCLUDE)}"convstrc.h"\
	{$(INCLUDE)}"edk.h"\
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
	{$(INCLUDE)}"exchinst.h"\
	{$(INCLUDE)}"gwreport.h"\
	{$(INCLUDE)}"mblogon.h"\
	{$(INCLUDE)}"monitor.h"\
	{$(INCLUDE)}"newpst.h"\
	{$(INCLUDE)}"proptag.h"\
	{$(INCLUDE)}"rclsid.h"\
	{$(INCLUDE)}"rpcpub.h"\
	{$(INCLUDE)}"rtflib.h"\
	{$(INCLUDE)}"rulecls.h"\
	{$(INCLUDE)}"stats.h"\
	{$(INCLUDE)}"stattype.h"\
	{$(INCLUDE)}"vsof.h"\
	{$(INCLUDE)}"vsop.h"\
	{$(INCLUDE)}"vsopcsid.h"\
	{$(INCLUDE)}"winwrap.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SummInfo.Cpp

!IF  "$(CFG)" == "Postsmpl - Win32 Release"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug"

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Debug Alpha"

DEP_CPP_SUMMI=\
	".\Postsmpl.h"\
	".\Resource.h"\
	".\StdAfx.h"\
	".\SummInfo.h"\
	

!ELSEIF  "$(CFG)" == "Postsmpl - Win32 Release Alpha"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Postsmpl.h
# End Source File
# Begin Source File

SOURCE=.\PostsmplDlg.h
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

SOURCE=.\res\Postsmpl.ico
# End Source File
# Begin Source File

SOURCE=.\res\Postsmpl.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
