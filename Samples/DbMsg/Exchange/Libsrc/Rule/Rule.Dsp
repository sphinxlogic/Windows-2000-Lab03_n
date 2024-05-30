# Microsoft Developer Studio Project File - Name="Rule" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=Rule - Win32 Unicode Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Rule.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Rule.mak" CFG="Rule - Win32 Unicode Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Rule - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Release MinDependency Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Release MinSize Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Unicode Debug Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Unicode Release MinDependency Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Rule - Win32 Unicode Release MinSize Alpha" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Rule - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Rule"
# PROP BASE Intermediate_Dir "Rule"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /verbose /nodefaultlib
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\debug
TargetPath=.\debug\Rule.dll
InputPath=.\debug\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "RuleU"
# PROP BASE Intermediate_Dir "RuleU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "RuleU"
# PROP Intermediate_Dir "RuleU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\RuleU
TargetPath=.\RuleU\Rule.dll
InputPath=.\RuleU\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

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
# ADD CPP /nologo /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /opt:NOREF
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Rule.dll
InputPath=.\ReleaseMinSize\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

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
# ADD CPP /nologo /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /dll /machine:I386 /opt:NOREF
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Rule.dll
InputPath=.\ReleaseMinDependency\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

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
# ADD CPP /nologo /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
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
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /dll /machine:I386 /opt:NOREF
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Rule.dll
InputPath=.\ReleaseUMinSize\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

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
# ADD CPP /nologo /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
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
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /dll /machine:I386 /opt:NOREF
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Rule.dll
InputPath=.\ReleaseUMinDependency\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Rule___W"
# PROP BASE Intermediate_Dir "Rule___W"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
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
OutDir=.\debug
TargetPath=.\debug\Rule.dll
InputPath=.\debug\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Rule___0"
# PROP BASE Intermediate_Dir "Rule___0"
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
# ADD CPP /nologo /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:NOREF
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:NOREF
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Rule.dll
InputPath=.\ReleaseMinDependency\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Rule___1"
# PROP BASE Intermediate_Dir "Rule___1"
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
# SUBTRACT BASE CPP /WX /Fr
# ADD CPP /nologo /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX /Fr
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# SUBTRACT BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:none /machine:ALPHA /opt:NOREF
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /pdb:none /machine:ALPHA /opt:NOREF
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Rule.dll
InputPath=.\ReleaseMinSize\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Rule___2"
# PROP BASE Intermediate_Dir "Rule___2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "RuleU"
# PROP Intermediate_Dir "RuleU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
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
OutDir=.\RuleU
TargetPath=.\RuleU\Rule.dll
InputPath=.\RuleU\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Rule___3"
# PROP BASE Intermediate_Dir "Rule___3"
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
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:NOREF
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:NOREF
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Rule.dll
InputPath=.\ReleaseUMinDependency\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Rule___4"
# PROP BASE Intermediate_Dir "Rule___4"
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
# ADD CPP /nologo /Gt0 /W3 /GR /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:NOREF
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /opt:NOREF
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Rule.dll
InputPath=.\ReleaseUMinSize\Rule.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Rule - Win32 Debug"
# Name "Rule - Win32 Unicode Debug"
# Name "Rule - Win32 Release MinSize"
# Name "Rule - Win32 Release MinDependency"
# Name "Rule - Win32 Unicode Release MinSize"
# Name "Rule - Win32 Unicode Release MinDependency"
# Name "Rule - Win32 Debug Alpha"
# Name "Rule - Win32 Release MinDependency Alpha"
# Name "Rule - Win32 Release MinSize Alpha"
# Name "Rule - Win32 Unicode Debug Alpha"
# Name "Rule - Win32 Unicode Release MinDependency Alpha"
# Name "Rule - Win32 Unicode Release MinSize Alpha"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ActionCollection.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_ACTIO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTIO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_ACTIO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTIO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_ACTIO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTIO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_ACTIO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTIO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACTIO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTIO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACTIO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTIO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ActionObj.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_ACTION=\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTION=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_ACTION=\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTION=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_ACTION=\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTION=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_ACTION=\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTION=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_ACTION=\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTION=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_ACTION=\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_ACTION=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BitmaskCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_BITMA=\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_BITMA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_BITMA=\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_BITMA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_BITMA=\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_BITMA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_BITMA=\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_BITMA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_BITMA=\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_BITMA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_BITMA=\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_BITMA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CommentCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_COMME=\
	".\BaseCondition.h"\
	".\CommentCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_COMME=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_COMME=\
	".\BaseCondition.h"\
	".\CommentCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_COMME=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_COMME=\
	".\BaseCondition.h"\
	".\CommentCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_COMME=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_COMME=\
	".\BaseCondition.h"\
	".\CommentCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_COMME=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_COMME=\
	".\BaseCondition.h"\
	".\CommentCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_COMME=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_COMME=\
	".\BaseCondition.h"\
	".\CommentCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_COMME=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ComparePropsCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_COMPA=\
	".\BaseCondition.h"\
	".\ComparePropsCondition.h"\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_COMPA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_COMPA=\
	".\BaseCondition.h"\
	".\ComparePropsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_COMPA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_COMPA=\
	".\BaseCondition.h"\
	".\ComparePropsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_COMPA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_COMPA=\
	".\BaseCondition.h"\
	".\ComparePropsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_COMPA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_COMPA=\
	".\BaseCondition.h"\
	".\ComparePropsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_COMPA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_COMPA=\
	".\BaseCondition.h"\
	".\ComparePropsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_COMPA=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ContentCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_CONTE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_CONTE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_CONTE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_CONTE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_CONTE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_CONTE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_CONTE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_CONTE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_CONTE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_CONTE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_CONTE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_CONTE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ExistsCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_EXIST=\
	".\BaseCondition.h"\
	".\ExistsCondition.h"\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_EXIST=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_EXIST=\
	".\BaseCondition.h"\
	".\ExistsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_EXIST=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_EXIST=\
	".\BaseCondition.h"\
	".\ExistsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_EXIST=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_EXIST=\
	".\BaseCondition.h"\
	".\ExistsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_EXIST=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_EXIST=\
	".\BaseCondition.h"\
	".\ExistsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_EXIST=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_EXIST=\
	".\BaseCondition.h"\
	".\ExistsCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	
NODEP_CPP_EXIST=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LogicalCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_LOGIC=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_LOGIC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_LOGIC=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_LOGIC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_LOGIC=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_LOGIC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_LOGIC=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_LOGIC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_LOGIC=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_LOGIC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_LOGIC=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_LOGIC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropertyCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_PROPE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_PROPE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_PROPE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_PROPE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_PROPE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_PROPE=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPE=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropVal.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_PROPV=\
	".\Module.h"\
	".\PropVal.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPV=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_PROPV=\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPV=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_PROPV=\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPV=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_PROPV=\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPV=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_PROPV=\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPV=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_PROPV=\
	".\Module.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_PROPV=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rule.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_RULE_=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\CommentCondition.h"\
	".\ComparePropsCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\ExistsCondition.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	
NODEP_CPP_RULE_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\Rule_i.c"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_RULE_=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\CommentCondition.h"\
	".\ComparePropsCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\ExistsCondition.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\Rule_i.c"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	
NODEP_CPP_RULE_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_RULE_=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\CommentCondition.h"\
	".\ComparePropsCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\ExistsCondition.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\Rule_i.c"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	
NODEP_CPP_RULE_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_RULE_=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\CommentCondition.h"\
	".\ComparePropsCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\ExistsCondition.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\Rule_i.c"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	
NODEP_CPP_RULE_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_RULE_=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\CommentCondition.h"\
	".\ComparePropsCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\ExistsCondition.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\Rule_i.c"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	
NODEP_CPP_RULE_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_RULE_=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\BitmaskCondition.h"\
	".\CommentCondition.h"\
	".\ComparePropsCondition.h"\
	".\ComPtrs.h"\
	".\ContentCondition.h"\
	".\ExistsCondition.h"\
	".\LogicalCondition.h"\
	".\Module.h"\
	".\PropertyCondition.h"\
	".\PropVal.h"\
	".\Rule.h"\
	".\Rule_i.c"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	
NODEP_CPP_RULE_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rule.def
# End Source File
# Begin Source File

SOURCE=.\Rule.idl

!IF  "$(CFG)" == "Rule - Win32 Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

# Begin Custom Build - Performing MIDL step
InputPath=.\Rule.idl

BuildCmds= \
	midl /Oicf /h "Rule.h" /iid "Rule_i.c" "Rule.idl"

".\Rule.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Rule_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RuleCollection.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_RULEC=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_RULEC=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_RULEC=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_RULEC=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_RULEC=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_RULEC=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleCollection.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RuleObj.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_RULEO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_RULEO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_RULEO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_RULEO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_RULEO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_RULEO=\
	".\actioncollection.h"\
	".\ActionObj.h"\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\RuleObj.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_RULEO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SizeCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_SIZEC=\
	".\BaseCondition.h"\
	".\Module.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SIZEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_SIZEC=\
	".\BaseCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SIZEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_SIZEC=\
	".\BaseCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SIZEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_SIZEC=\
	".\BaseCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SIZEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_SIZEC=\
	".\BaseCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SIZEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_SIZEC=\
	".\BaseCondition.h"\
	".\Module.h"\
	".\Rule.h"\
	".\SizeCondition.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SIZEC=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_STDAF=\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_STDAF=\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_STDAF=\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_STDAF=\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_STDAF=\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_STDAF=\
	".\Module.h"\
	".\StdAfx.h"\
	
NODEP_CPP_STDAF=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	
# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SubCondition.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_SUBCO=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	".\Util.h"\
	
NODEP_CPP_SUBCO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\Rule.h"\
	".\sof.h"\
	".\sop.h"\
	".\sopcsid.h"\
	".\tats.h"\
	".\tattype.h"\
	".\tflib.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_SUBCO=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	".\Util.h"\
	
NODEP_CPP_SUBCO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_SUBCO=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	".\Util.h"\
	
NODEP_CPP_SUBCO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_SUBCO=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	".\Util.h"\
	
NODEP_CPP_SUBCO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_SUBCO=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	".\Util.h"\
	
NODEP_CPP_SUBCO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_SUBCO=\
	".\BaseCondition.h"\
	".\ComPtrs.h"\
	".\Module.h"\
	".\Rule.h"\
	".\StdAfx.h"\
	".\SubCondition.h"\
	".\Util.h"\
	
NODEP_CPP_SUBCO=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Util.cpp

!IF  "$(CFG)" == "Rule - Win32 Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "Rule - Win32 Debug Alpha"

DEP_CPP_UTIL_=\
	".\Module.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_UTIL_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinDependency Alpha"

DEP_CPP_UTIL_=\
	".\Module.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_UTIL_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Release MinSize Alpha"

DEP_CPP_UTIL_=\
	".\Module.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_UTIL_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Debug Alpha"

DEP_CPP_UTIL_=\
	".\Module.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_UTIL_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinDependency Alpha"

DEP_CPP_UTIL_=\
	".\Module.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_UTIL_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "Rule - Win32 Unicode Release MinSize Alpha"

DEP_CPP_UTIL_=\
	".\Module.h"\
	".\StdAfx.h"\
	".\Util.h"\
	
NODEP_CPP_UTIL_=\
	".\blogon.h"\
	".\clsid.h"\
	".\ddrlkup.h"\
	".\dk.h"\
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
	".\wreport.h"\
	".\xchinst.h"\
	

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\actioncollection.h
# End Source File
# Begin Source File

SOURCE=.\ActionObj.h
# End Source File
# Begin Source File

SOURCE=.\BitmaskCondition.h
# End Source File
# Begin Source File

SOURCE=.\CommentCondition.h
# End Source File
# Begin Source File

SOURCE=.\ComparePropsCondition.h
# End Source File
# Begin Source File

SOURCE=.\ComPtrs.h
# End Source File
# Begin Source File

SOURCE=.\ContentCondition.h
# End Source File
# Begin Source File

SOURCE=.\ExistsCondition.h
# End Source File
# Begin Source File

SOURCE=.\LogicalCondition.h
# End Source File
# Begin Source File

SOURCE=.\PropertyCondition.h
# End Source File
# Begin Source File

SOURCE=.\PropVal.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RuleCollection.h
# End Source File
# Begin Source File

SOURCE=.\RuleObj.h
# End Source File
# Begin Source File

SOURCE=.\SizeCondition.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubCondition.h
# End Source File
# Begin Source File

SOURCE=.\Util.h
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\ActionObj.rgs
# End Source File
# Begin Source File

SOURCE=.\BitmaskCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\CommentCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\ComparePropsCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\ContentCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\ExistsCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\LogicalCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\PropertyCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\PropVal.rgs
# End Source File
# Begin Source File

SOURCE=.\RuleCollection.rgs
# End Source File
# Begin Source File

SOURCE=.\RuleObj.rgs
# End Source File
# Begin Source File

SOURCE=.\SizeCondition.rgs
# End Source File
# Begin Source File

SOURCE=.\SubCondition.rgs
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "*.rc"
# Begin Source File

SOURCE=.\Rule.rc
# End Source File
# End Group
# End Target
# End Project
