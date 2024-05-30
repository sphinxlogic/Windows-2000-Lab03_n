# Microsoft Developer Studio Project File - Name="ACL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=ACL - Win32 Unicode Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ACL.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ACL.MAK" CFG="ACL - Win32 Unicode Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ACL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Release MinDependency Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Release MinSize Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Unicode Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Unicode Release MinDependency Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ACL - Win32 Unicode Release MinSize Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ACL - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\ACL.dll
InputPath=.\Debug\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\ACL.dll
InputPath=.\DebugU\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

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
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib kernel32.lib user32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ACL.dll
InputPath=.\ReleaseMinSize\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

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
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ACL.dll
InputPath=.\ReleaseMinDependency\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

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
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ACL.dll
InputPath=.\ReleaseUMinSize\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

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
# ADD CPP /nologo /MT /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib kernel32.lib user32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ACL.dll
InputPath=.\ReleaseUMinDependency\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ACL___Wi"
# PROP BASE Intermediate_Dir "ACL___Wi"
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
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\ACL.dll
InputPath=.\Debug\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ACL___W0"
# PROP BASE Intermediate_Dir "ACL___W0"
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
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ACL.dll
InputPath=.\ReleaseMinDependency\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ACL___W1"
# PROP BASE Intermediate_Dir "ACL___W1"
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
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ACL.dll
InputPath=.\ReleaseMinSize\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ACL___W2"
# PROP BASE Intermediate_Dir "ACL___W2"
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
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /Gt0 /W3 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\ACL.dll
InputPath=.\DebugU\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ACL___W3"
# PROP BASE Intermediate_Dir "ACL___W3"
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
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ACL.dll
InputPath=.\ReleaseUMinDependency\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ACL___W4"
# PROP BASE Intermediate_Dir "ACL___W4"
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
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ACL.dll
InputPath=.\ReleaseUMinSize\ACL.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ACL - Win32 Debug"
# Name "ACL - Win32 Unicode Debug"
# Name "ACL - Win32 Release MinSize"
# Name "ACL - Win32 Release MinDependency"
# Name "ACL - Win32 Unicode Release MinSize"
# Name "ACL - Win32 Unicode Release MinDependency"
# Name "ACL - Win32 Debug Alpha"
# Name "ACL - Win32 Release MinDependency Alpha"
# Name "ACL - Win32 Release MinSize Alpha"
# Name "ACL - Win32 Unicode Debug Alpha"
# Name "ACL - Win32 Unicode Release MinDependency Alpha"
# Name "ACL - Win32 Unicode Release MinSize Alpha"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ACE.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_ACE_C=\
	".\ACE.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACE_C=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_ACE_C=\
	".\ACE.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACE_C=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_ACE_C=\
	".\ACE.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACE_C=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_ACE_C=\
	".\ACE.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACE_C=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACE_C=\
	".\ACE.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACE_C=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACE_C=\
	".\ACE.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACE_C=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ACECollection.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_ACECO=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACECO=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_ACECO=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACECO=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_ACECO=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACECO=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_ACECO=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACECO=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACECO=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACECO=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACECO=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACECO=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ACEMap.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_ACEMA=\
	".\ACE.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_ACEMA=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_ACEMA=\
	".\ACE.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_ACEMA=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_ACEMA=\
	".\ACE.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_ACEMA=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_ACEMA=\
	".\ACE.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_ACEMA=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACEMA=\
	".\ACE.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_ACEMA=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACEMA=\
	".\ACE.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_ACEMA=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ACL.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_ACL_C=\
	".\ACE.h"\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACL_C=\
	".\ACL.h"\
	".\ACL_i.c"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_ACL_C=\
	".\ACE.h"\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACL_C=\
	".\ACL.h"\
	".\ACL_i.c"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_ACL_C=\
	".\ACE.h"\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACL_C=\
	".\ACL.h"\
	".\ACL_i.c"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_ACL_C=\
	".\ACE.h"\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACL_C=\
	".\ACL.h"\
	".\ACL_i.c"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACL_C=\
	".\ACE.h"\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACL_C=\
	".\ACL.h"\
	".\ACL_i.c"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACL_C=\
	".\ACE.h"\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACL_C=\
	".\ACL.h"\
	".\ACL_i.c"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ACL.def
# End Source File
# Begin Source File

SOURCE=.\ACL.idl

!IF  "$(CFG)" == "ACL - Win32 Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /tlb "ACL.tlb" ACL.IDL

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /tlb "ACL.tlb" ACL.IDL

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\ACL.idl

BuildCmds= \
	midl /Oicf /h "ACL.h" /iid "ACL_i.c" "ACL.idl"

".\ACL.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ACL_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ACL.rc
# End Source File
# Begin Source File

SOURCE=.\ACLObject.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_ACLOB=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACLOB=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_ACLOB=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACLOB=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_ACLOB=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACLOB=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_ACLOB=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACLOB=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACLOB=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACLOB=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACLOB=\
	".\ACECollection.h"\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ACLObject.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	
NODEP_CPP_ACLOB=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ExchTable.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_EXCHT=\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_EXCHT=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_EXCHT=\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_EXCHT=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_EXCHT=\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_EXCHT=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_EXCHT=\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_EXCHT=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_EXCHT=\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_EXCHT=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_EXCHT=\
	".\ACEMap.h"\
	".\aclcommon.h"\
	".\ExchTable.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_EXCHT=\
	".\ACL.h"\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\dkmdb.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\dkmdb.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\dkmdb.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\dkmdb.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\dkmdb.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\dkmdb.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Util.cpp

!IF  "$(CFG)" == "ACL - Win32 Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "ACL - Win32 Debug Alpha"

DEP_CPP_UTIL_=\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_UTIL_=\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinDependency Alpha"

DEP_CPP_UTIL_=\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_UTIL_=\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Release MinSize Alpha"

DEP_CPP_UTIL_=\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_UTIL_=\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Debug Alpha"

DEP_CPP_UTIL_=\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_UTIL_=\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_UTIL_=\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_UTIL_=\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ELSEIF  "$(CFG)" == "ACL - Win32 Unicode Release MinSize Alpha"

DEP_CPP_UTIL_=\
	".\aclcommon.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_UTIL_=\
	".\dkcode.h"\
	".\dkguid.h"\
	".\dkmdb.h"\
	

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ACE.h
# End Source File
# Begin Source File

SOURCE=.\ACECollection.h
# End Source File
# Begin Source File

SOURCE=.\ACLObject.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
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

SOURCE=.\ACE.rgs
# End Source File
# Begin Source File

SOURCE=.\ACECollection.rgs
# End Source File
# Begin Source File

SOURCE=.\ACLObject.rgs
# End Source File
# End Target
# End Project
