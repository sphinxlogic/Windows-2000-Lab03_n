# Microsoft Developer Studio Project File - Name="disdraw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=disdraw - Win32 ALPHA Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DisDraw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DisDraw.mak" CFG="disdraw - Win32 ALPHA Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "disdraw - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 Release win95" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 Debug win95" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 ALPHA Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "disdraw - Win32 ALPHA Release" (based on "Win32 (ALPHA) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "disdraw - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release"
# PROP Intermediate_Dir ".\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:".\release\c_draw.exe"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none /debug /machine:I386 /out:".\debug\c_draw.exe" /libpath:"..\..\bins\debug"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\disdraw_"
# PROP BASE Intermediate_Dir ".\disdraw_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release95"
# PROP Intermediate_Dir ".\Release95"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\sdk\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\bins\release\mqrt.lib /nologo /subsystem:windows /machine:I386 /out:"Release/c_draw.exe"
# ADD LINK32 ..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:".\release95\c_draw.exe" /libpath:"..\..\bins\release95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\disdraw0"
# PROP BASE Intermediate_Dir ".\disdraw0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug95"
# PROP Intermediate_Dir ".\Debug95"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\sdk\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\bins\debug\mqrt.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/c_draw.exe"
# ADD LINK32 ..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none /debug /machine:I386 /out:".\debug95\c_draw.exe" /libpath:"..\..\bins\debug95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

# PROP BASE Use_MFC 4
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "disdraw_"
# PROP BASE Intermediate_Dir "disdraw_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\sdk\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /MDd /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\bins\debug\mqrt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /pdb:none /debug /machine:ALPHA /out:"..\..\bins\debug\c_draw.exe"
# ADD LINK32 ..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none /debug /machine:ALPHA /out:".\debug\c_draw.exe" /libpath:"..\..\bins\debug"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

# PROP BASE Use_MFC 4
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "disdraw0"
# PROP BASE Intermediate_Dir "disdraw0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release"
# PROP Intermediate_Dir ".\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /O2 /I "..\..\sdk\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /Gt0 /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\bins\release\mqrt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /pdb:none /machine:ALPHA /out:"..\..\bins\release\c_draw.exe"
# ADD LINK32 ..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none /machine:ALPHA /out:".\release\c_draw.exe" /libpath:"..\..\bins\release"

!ENDIF 

# Begin Target

# Name "disdraw - Win32 Release"
# Name "disdraw - Win32 Debug"
# Name "disdraw - Win32 Release win95"
# Name "disdraw - Win32 Debug win95"
# Name "disdraw - Win32 ALPHA Debug"
# Name "disdraw - Win32 ALPHA Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\disdraw.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_DISDR=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DISDR=\
	"..\..\..\..\include\mq.h"\
	

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_DISDR=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DISDR=\
	"..\..\..\..\include\mq.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\disdraw.rc
# End Source File
# Begin Source File

SOURCE=.\drawarea.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_DRAWA=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DRAWA=\
	"..\..\..\..\include\mq.h"\
	

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_DRAWA=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DRAWA=\
	"..\..\..\..\include\mq.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\drawdlg.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_DRAWD=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DRAWD=\
	"..\..\..\..\include\mq.h"\
	

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_DRAWD=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DRAWD=\
	"..\..\..\..\include\mq.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\logindlg.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_LOGIN=\
	".\disdraw.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_LOGIN=\
	"..\..\..\..\include\mq.h"\
	

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_LOGIN=\
	".\disdraw.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_LOGIN=\
	"..\..\..\..\include\mq.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	"..\..\..\..\include\mq.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	"..\..\..\..\include\mq.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\disdraw.h
# End Source File
# Begin Source File

SOURCE=.\drawarea.h
# End Source File
# Begin Source File

SOURCE=.\drawdlg.h
# End Source File
# Begin Source File

SOURCE=.\logindlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\disdraw.ico
# End Source File
# Begin Source File

SOURCE=.\res\disdraw.rc2
# End Source File
# End Group
# End Target
# End Project
