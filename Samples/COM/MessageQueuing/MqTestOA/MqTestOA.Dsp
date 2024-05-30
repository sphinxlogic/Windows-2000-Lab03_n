# Microsoft Developer Studio Project File - Name="mqtestoa" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

CFG=mqtestoa - Win32 ALPHA Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MqTestOA.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MqTestOA.mak" CFG="mqtestoa - Win32 ALPHA Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mqtestoa - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mqtestoa - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "mqtestoa - Win32 Debug win95" (based on "Win32 (x86) Console Application")
!MESSAGE "mqtestoa - Win32 Release win95" (based on "Win32 (x86) Console Application")
!MESSAGE "mqtestoa - Win32 ALPHA Release" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "mqtestoa - Win32 ALPHA Debug" (based on "Win32 (ALPHA) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "mqtestoa - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\mqtestoa"
# PROP BASE Intermediate_Dir ".\mqtestoa"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release"
# PROP Intermediate_Dir ".\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "STRICT" /YX /FD /c
# SUBTRACT CPP /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 odbc32.lib odbccp32.lib ..\..\..\..\lib\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /machine:I386

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\mqtesto0"
# PROP BASE Intermediate_Dir ".\mqtesto0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\debug"
# PROP Intermediate_Dir ".\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "STRICT" /FR /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 odbc32.lib odbccp32.lib ..\..\..\..\lib\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /debug /machine:I386

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Debug win95"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\mqtestoa"
# PROP BASE Intermediate_Dir ".\mqtestoa"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\debug95"
# PROP Intermediate_Dir ".\debug95"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\sdk\inc" /I "..\..\activex\mqoa\debug" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "STRICT" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "STRICT" /YX /FD /c
# SUBTRACT CPP /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\bins\debug\mqoa.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 odbc32.lib odbccp32.lib ..\..\..\..\lib\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /debug /machine:I386

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Release win95"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\mqtesto0"
# PROP BASE Intermediate_Dir ".\mqtesto0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release95"
# PROP Intermediate_Dir ".\release95"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\sdk\inc" /I "..\..\activex\mqoa\release" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "STRICT" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "UNICODE" /D "STRICT" /YX /FD /c
# SUBTRACT CPP /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\bins\release\mqoa.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 odbc32.lib odbccp32.lib ..\..\..\..\lib\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /machine:I386

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 ALPHA Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mqtestoa"
# PROP BASE Intermediate_Dir "mqtestoa"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\release"
# PROP Intermediate_Dir ".\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /O2 /I "..\..\sdk\inc" /I "..\..\activex\mqoa\release" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "UNICODE" /D "STRICT" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /Gt0 /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "UNICODE" /D "STRICT" /YX /FD /c
# SUBTRACT CPP /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\bins\release\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /machine:ALPHA
# ADD LINK32 ..\..\..\..\lib\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /machine:ALPHA

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 ALPHA Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mqtesto0"
# PROP BASE Intermediate_Dir "mqtesto0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\debug"
# PROP Intermediate_Dir ".\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\sdk\inc" /I "..\..\activex\mqoa\debug" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "UNICODE" /D "STRICT" /FR /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "UNICODE" /D "STRICT" /YX /FD /MDd /c
# SUBTRACT CPP /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\bins\debug\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /debug /machine:ALPHA
# ADD LINK32 ..\..\..\..\lib\mqoa.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:none /debug /machine:ALPHA

!ENDIF 

# Begin Target

# Name "mqtestoa - Win32 Release"
# Name "mqtestoa - Win32 Debug"
# Name "mqtestoa - Win32 Debug win95"
# Name "mqtestoa - Win32 Release win95"
# Name "mqtestoa - Win32 ALPHA Release"
# Name "mqtestoa - Win32 ALPHA Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Guids.Cpp

!IF  "$(CFG)" == "mqtestoa - Win32 Release"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Debug"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Debug win95"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Release win95"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 ALPHA Release"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 ALPHA Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mqtestoa.cpp

!IF  "$(CFG)" == "mqtestoa - Win32 Release"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Debug"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Debug win95"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 Release win95"

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 ALPHA Release"

NODEP_CPP_MQTES=\
	"..\..\include\mqoai.h"\
	

!ELSEIF  "$(CFG)" == "mqtestoa - Win32 ALPHA Debug"

NODEP_CPP_MQTES=\
	"..\..\include\mqoai.h"\
	

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
