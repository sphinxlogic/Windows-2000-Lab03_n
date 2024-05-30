# Microsoft Developer Studio Project File - Name="ToolForm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=ToolForm - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ToolForm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ToolForm.mak" CFG="ToolForm - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ToolForm - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ToolForm - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ToolForm - Win32 Debug Alpha" (based on "Win32 (ALPHA) Application")
!MESSAGE "ToolForm - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ToolForm - Win32 Release"

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
# ADD LINK32 exchsdk.lib mapi32.lib msvcrt.lib version.lib msvcrt.Lib uuid.lib shell32.lib oldnames.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
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
# ADD LINK32 exchsdkd.lib mapi32.lib version.lib msvcrtd.Lib uuid.lib shell32.lib oldnames.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

# PROP BASE Use_MFC 4
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ToolForm"
# PROP BASE Intermediate_Dir "ToolForm"
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
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 exchsdkd.lib mapi32.lib version.lib msvcrtd.Lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 exchsdkd.lib mapi32.lib version.lib msvcrtd.Lib oldnames.lib /nologo /subsystem:windows /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

# PROP BASE Use_MFC 4
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ToolFor0"
# PROP BASE Intermediate_Dir "ToolFor0"
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
# ADD BASE LINK32 exchsdk.lib mapi32.lib msvcrt.lib version.lib msvcrt.Lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:ALPHA /nodefaultlib:"libc"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 exchsdk.lib mapi32.lib msvcrt.lib version.lib msvcrt.Lib oldnames.lib /nologo /subsystem:windows /machine:ALPHA /nodefaultlib:"libc"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ToolForm - Win32 Release"
# Name "ToolForm - Win32 Debug"
# Name "ToolForm - Win32 Debug Alpha"
# Name "ToolForm - Win32 Release Alpha"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Form.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_FORM_=\
	".\form.h"\
	".\formdata.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	".\ToolForm.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormData.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_FORMD=\
	".\formdata.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Formfact.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_FORMF=\
	".\form.h"\
	".\formdata.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	".\ToolForm.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormMapi.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_FORMM=\
	".\form.h"\
	".\formdata.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Formprst.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_FORMP=\
	".\form.h"\
	".\formdata.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	".\ToolForm.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Formunk.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_FORMU=\
	".\form.h"\
	".\formdata.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tool.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_TOOL_=\
	".\form.h"\
	".\formdata.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	".\ToolForm.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ToolDoc.Cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_TOOLD=\
	".\form.h"\
	".\formdata.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	".\ToolForm.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ToolForm.cpp

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

DEP_CPP_TOOLF=\
	".\form.h"\
	".\formdata.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	".\ToolForm.h"\
	

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ToolForm.rc

!IF  "$(CFG)" == "ToolForm - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "ToolForm - Win32 Release Alpha"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolForm.h
# End Source File
# Begin Source File

SOURCE=.\ToolFormDoc.h
# End Source File
# Begin Source File

SOURCE=.\ToolFormView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ToolForm.ico
# End Source File
# Begin Source File

SOURCE=.\ToolForm.Ico
# End Source File
# Begin Source File

SOURCE=.\res\ToolForm.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ToolFormDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
