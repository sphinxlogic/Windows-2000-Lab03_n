# Microsoft Developer Studio Project File - Name="SampleOSProvider" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=SampleOSProvider - Win32 Alpha Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SampleOSP_VC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SampleOSP_VC.mak" CFG="SampleOSProvider - Win32 Alpha Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SampleOSProvider - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SampleOSProvider - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SampleOSProvider - Win32 Alpha Debug" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "SampleOSProvider - Win32 Alpha Release" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "SampleOSProvider - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86\Release"
# PROP Intermediate_Dir "x86\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 osptk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"x86/release/ospsampc.dll"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SampleOS"
# PROP BASE Intermediate_Dir "SampleOS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86\Debug"
# PROP Intermediate_Dir "x86\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 osptk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libcmt" /out:"x86/debug/ospsampc.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SampleOS"
# PROP BASE Intermediate_Dir "SampleOS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ALPHA\Debug"
# PROP Intermediate_Dir "ALPHA\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /MTd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /MTd /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 osptk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /out:"Out/ospsampc.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 ..\..\lib\axp_debu\osptk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /out:"ALPHA/Debug/ospsampc.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SampleO0"
# PROP BASE Intermediate_Dir "SampleO0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ALPHA\Release"
# PROP Intermediate_Dir "ALPHA\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 ..\..\lib\axp_rele\osptk.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /out:"ALPHA\release\ospsampc.dll"

!ENDIF 

# Begin Target

# Name "SampleOSProvider - Win32 Release"
# Name "SampleOSProvider - Win32 Debug"
# Name "SampleOSProvider - Win32 Alpha Debug"
# Name "SampleOSProvider - Win32 Alpha Release"
# Begin Source File

SOURCE=.\CExList.h
# End Source File
# Begin Source File

SOURCE=.\Common.cpp

!IF  "$(CFG)" == "SampleOSProvider - Win32 Release"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Debug"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Debug"

DEP_CPP_COMMO=\
	".\Common.h"\
	
NODEP_CPP_COMMO=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Release"

DEP_CPP_COMMO=\
	".\Common.h"\
	
NODEP_CPP_COMMO=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Common.h
# End Source File
# Begin Source File

SOURCE=.\MyClassFactory.cpp

!IF  "$(CFG)" == "SampleOSProvider - Win32 Release"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Debug"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Debug"

DEP_CPP_MYCLA=\
	".\Common.h"\
	".\MyClassFactory.h"\
	".\MyDataSource.h"\
	".\MyOSPObject.h"\
	
NODEP_CPP_MYCLA=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Release"

DEP_CPP_MYCLA=\
	".\Common.h"\
	".\MyClassFactory.h"\
	".\MyDataSource.h"\
	".\MyOSPObject.h"\
	
NODEP_CPP_MYCLA=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyClassFactory.h
# End Source File
# Begin Source File

SOURCE=.\MyDataSource.cpp

!IF  "$(CFG)" == "SampleOSProvider - Win32 Release"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Debug"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Debug"

DEP_CPP_MYDAT=\
	".\Common.h"\
	".\MyDataSource.h"\
	".\MyOSPObject.h"\
	
NODEP_CPP_MYDAT=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Release"

DEP_CPP_MYDAT=\
	".\Common.h"\
	".\MyDataSource.h"\
	".\MyOSPObject.h"\
	
NODEP_CPP_MYDAT=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyDataSource.h
# End Source File
# Begin Source File

SOURCE=.\MyOSPObject.cpp

!IF  "$(CFG)" == "SampleOSProvider - Win32 Release"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Debug"

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Debug"

DEP_CPP_MYOSP=\
	".\Common.h"\
	".\MyOSPObject.h"\
	
NODEP_CPP_MYOSP=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ELSEIF  "$(CFG)" == "SampleOSProvider - Win32 Alpha Release"

DEP_CPP_MYOSP=\
	".\Common.h"\
	".\MyOSPObject.h"\
	
NODEP_CPP_MYOSP=\
	"..\..\..\OLEDBHeaders\genfiles\oledb.h"\
	"..\..\..\OLEDBHeaders\genfiles\oledberr.h"\
	"..\..\..\OLEDBHeaders\include\transact.h"\
	"..\..\include\msdaosp.h"\
	"..\..\include\msdatsrc.h"\
	"..\..\include\simpdata.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyOSPObject.h
# End Source File
# Begin Source File

SOURCE=.\SampleOSP_VC.def
# End Source File
# End Target
# End Project
