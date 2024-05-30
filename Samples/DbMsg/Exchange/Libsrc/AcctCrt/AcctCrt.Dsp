# Microsoft Developer Studio Project File - Name="acctcrt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=acctcrt - Win32 Unicode Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "acctcrt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "acctcrt.mak" CFG="acctcrt - Win32 Unicode Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "acctcrt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Unicode Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Release MinDependency Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Release MinSize Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Unicode Release MinDependency Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "acctcrt - Win32 Unicode Release MinSize Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "acctcrt - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\acctcrt.dll
InputPath=.\Debug\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib netapi32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\acctcrt.dll
InputPath=.\DebugU\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "NDEBUG" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:yes /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\acctcrt.dll
InputPath=.\ReleaseMinSize\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "NDEBUG" /D "_ATL_STATIC_REGISTRY" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /machine:I386
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\acctcrt.dll
InputPath=.\ReleaseMinDependency\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "NDEBUG" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib netapi32.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /incremental:yes /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\acctcrt.dll
InputPath=.\ReleaseUMinSize\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "NDEBUG" /D "_ATL_STATIC_REGISTRY" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /machine:I386
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\acctcrt.dll
InputPath=.\ReleaseUMinDependency\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "acctcrt_"
# PROP BASE Intermediate_Dir "acctcrt_"
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
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /MTd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /MTd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /pdbtype:sept
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\acctcrt.dll
InputPath=.\Debug\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "acctcrt0"
# PROP BASE Intermediate_Dir "acctcrt0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "UNICODE" /Yu"stdafx.h" /FD /MTd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /MTd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\acctcrt.dll
InputPath=.\DebugU\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "acctcrt1"
# PROP BASE Intermediate_Dir "acctcrt1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\acctcrt.dll
InputPath=.\ReleaseMinDependency\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "acctcrt2"
# PROP BASE Intermediate_Dir "acctcrt2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# SUBTRACT BASE LINK32 /pdb:none /debug
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# SUBTRACT LINK32 /pdb:none /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\acctcrt.dll
InputPath=.\ReleaseMinSize\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "acctcrt3"
# PROP BASE Intermediate_Dir "acctcrt3"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\acctcrt.dll
InputPath=.\ReleaseUMinDependency\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "acctcrt4"
# PROP BASE Intermediate_Dir "acctcrt4"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\acctcrt.dll
InputPath=.\ReleaseUMinSize\acctcrt.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "acctcrt - Win32 Debug"
# Name "acctcrt - Win32 Unicode Debug"
# Name "acctcrt - Win32 Release MinSize"
# Name "acctcrt - Win32 Release MinDependency"
# Name "acctcrt - Win32 Unicode Release MinSize"
# Name "acctcrt - Win32 Unicode Release MinDependency"
# Name "acctcrt - Win32 Debug Alpha"
# Name "acctcrt - Win32 Unicode Debug Alpha"
# Name "acctcrt - Win32 Release MinDependency Alpha"
# Name "acctcrt - Win32 Release MinSize Alpha"
# Name "acctcrt - Win32 Unicode Release MinDependency Alpha"
# Name "acctcrt - Win32 Unicode Release MinSize Alpha"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\acctcrt.cpp

!IF  "$(CFG)" == "acctcrt - Win32 Debug"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Debug Alpha"

DEP_CPP_ACCTC=\
	".\acctcrt.h"\
	".\acctcrt_i.c"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug Alpha"

DEP_CPP_ACCTC=\
	".\acctcrt.h"\
	".\acctcrt_i.c"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency Alpha"

DEP_CPP_ACCTC=\
	".\acctcrt.h"\
	".\acctcrt_i.c"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize Alpha"

DEP_CPP_ACCTC=\
	".\acctcrt.h"\
	".\acctcrt_i.c"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACCTC=\
	".\acctcrt.h"\
	".\acctcrt_i.c"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACCTC=\
	".\acctcrt.h"\
	".\acctcrt_i.c"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\acctcrt.def
# End Source File
# Begin Source File

SOURCE=.\acctcrt.idl

!IF  "$(CFG)" == "acctcrt - Win32 Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Debug Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\acctcrt.idl

BuildCmds= \
	midl /Oicf /h "acctcrt.h" /iid "acctcrt_i.c" "acctcrt.idl"

".\acctcrt.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\acctcrt_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\acctcrt.rc

!IF  "$(CFG)" == "acctcrt - Win32 Debug"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug Alpha"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency Alpha"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize Alpha"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency Alpha"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AcctMgmt.cpp

!IF  "$(CFG)" == "acctcrt - Win32 Debug"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Debug Alpha"

DEP_CPP_ACCTM=\
	".\acctcrt.h"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug Alpha"

DEP_CPP_ACCTM=\
	".\acctcrt.h"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency Alpha"

DEP_CPP_ACCTM=\
	".\acctcrt.h"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize Alpha"

DEP_CPP_ACCTM=\
	".\acctcrt.h"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACCTM=\
	".\acctcrt.h"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACCTM=\
	".\acctcrt.h"\
	".\AcctMgmt.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "acctcrt - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Debug Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Debug Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinDependency Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Release MinSize Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "acctcrt - Win32 Unicode Release MinSize Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AcctMgmt.h
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
# End Group
# Begin Source File

SOURCE=.\AcctMgmt.rgs
# End Source File
# End Target
# End Project
