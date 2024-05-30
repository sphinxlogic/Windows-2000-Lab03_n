# Microsoft Developer Studio Project File - Name="ProxyGen" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=ProxyGen - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProxyGen.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProxyGen.mak" CFG="ProxyGen - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProxyGen - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ProxyGen - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ProxyGen - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ProxyGen - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ProxyGen - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
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
# ADD LINK32 Exchsdk.lib mapi32.lib uuid.lib msvcrt.lib shell32.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
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
# ADD LINK32 Exchsdkd.lib mapi32.lib uuid.lib shell32.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ProxyGen"
# PROP BASE Intermediate_Dir "ProxyGen"
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
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Exchsdkd.lib mapi32.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 Exchsdkd.lib mapi32.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ProxyGe0"
# PROP BASE Intermediate_Dir "ProxyGe0"
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
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Exchsdk.lib mapi32.lib msvcrt.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 Exchsdk.lib mapi32.lib msvcrt.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA

!ENDIF 

# Begin Target

# Name "ProxyGen - Win32 Release"
# Name "ProxyGen - Win32 Debug"
# Name "ProxyGen - Win32 Debug Alpha"
# Name "ProxyGen - Win32 Release Alpha"
# Begin Source File

SOURCE=.\EdkProxy.Rc

!IF  "$(CFG)" == "ProxyGen - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Release Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Msg00001.bin
# End Source File
# Begin Source File

SOURCE=.\ProxyGen.c

!IF  "$(CFG)" == "ProxyGen - Win32 Release"

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug"

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug Alpha"

DEP_CPP_PROXY=\
	{$(INCLUDE)}"proxygen.h"\
	{$(INCLUDE)}"proxyinf.h"\
	{$(INCLUDE)}"retcode.h"\
	
NODEP_CPP_PROXY=\
	".\proxymsg.h"\
	

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ProxyGen.Def
# End Source File
# Begin Source File

SOURCE=.\ProxyMsg.Mc

!IF  "$(CFG)" == "ProxyGen - Win32 Release"

# Begin Custom Build - MC Compile
InputPath=.\ProxyMsg.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  proxymsg.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug"

# Begin Custom Build
InputPath=.\ProxyMsg.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  proxymsg.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug Alpha"

# Begin Custom Build
InputPath=.\ProxyMsg.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  proxymsg.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Release Alpha"

# Begin Custom Build - MC Compile
InputPath=.\ProxyMsg.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  proxymsg.mc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Proxyver.Rc

!IF  "$(CFG)" == "ProxyGen - Win32 Release"

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug"

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "ProxyGen - Win32 Release Alpha"

!ENDIF 

# End Source File
# End Target
# End Project
