# Microsoft Developer Studio Project File - Name="Wipe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=Wipe - Win32 Alpha Release Licensed
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wipe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wipe.mak" CFG="Wipe - Win32 Alpha Release Licensed"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Wipe - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Wipe - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Wipe - Win32 Release Licensed" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Wipe - Win32 Alpha Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Wipe - Win32 Alpha Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Wipe - Win32 Alpha Release Licensed" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Wipe - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /Zi /Od /I "..\..\..\..\..\include" /I "..\..\..\..\..\include\dt" /I "..\..\..\..\..\include\d3drm" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D _LICENSED_VERSION=1 /FR /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /X
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
# ADD LINK32 dxtrans.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\..\..\Lib\i386"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\wipe.dll
InputPath=.\Debug\wipe.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Wipe___W"
# PROP BASE Intermediate_Dir "Wipe___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "..\..\..\..\..\include" /I "..\..\..\..\..\include\dt" /I "..\..\..\..\..\include\d3drm" /D "NDEBUG" /D _LICENSED_VERSION=0 /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /X
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dxtrans.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /machine:I386 /libpath:"..\..\..\..\..\..\Lib\i386"
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\wipe.dll
InputPath=.\Release\wipe.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release Licensed"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Wipe___W"
# PROP BASE Intermediate_Dir "Wipe___W"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Wipe___W"
# PROP Intermediate_Dir "Wipe___W"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /I "..\..\..\..\..\include" /I "..\..\..\..\..\include\dt" /I "..\..\..\..\..\include\d3drm" /D "NDEBUG" /D _LICENSED_VERSION=1 /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D _LICENSED_VERSION=0 /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /MT /W3 /O1 /I "..\..\..\..\..\include" /I "..\..\..\..\..\include\dt" /I "..\..\..\..\..\include\d3drm" /D "NDEBUG" /D _LICENSED_VERSION=1 /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D _LICENSED_VERSION=0 /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /X
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
# ADD BASE LINK32 dxtrans.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /machine:I386 /libpath:"..\..\..\..\..\..\Lib\i386"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 dxtrans.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /machine:I386 /libpath:"..\..\..\..\..\..\Lib\i386"
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Wipe___W
TargetPath=.\Wipe___W\wipe.dll
InputPath=.\Wipe___W\wipe.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Wipe___0"
# PROP BASE Intermediate_Dir "Wipe___0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Wipe___0"
# PROP Intermediate_Dir "Wipe___0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\..\..\..\include" /I "..\..\..\..\..\include\dt" /I "..\..\..\..\..\include\d3drm" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D _LICENSED_VERSION=1 /FR /Yu"stdafx.h" /FD /MTd /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D _LICENSED_VERSION=1 /D "WIN32" /D "_WINDOWS" /D "_NOT_X86" /D _ALPHA_=1 /D ALPHA=1 /FR /Yu"stdafx.h" /FD /MTd /c
# SUBTRACT CPP /X
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dxtrans.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept /libpath:"..\..\..\..\..\..\Lib\i386"
# ADD LINK32 dxtrans.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Wipe___0
TargetPath=.\Wipe___0\wipe.dll
InputPath=.\Wipe___0\wipe.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Wipe___1"
# PROP BASE Intermediate_Dir "Wipe___1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Wipe___1"
# PROP Intermediate_Dir "Wipe___1"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /O1 /I "..\..\..\..\..\include" /I "..\..\..\..\..\include\dt" /I "..\..\..\..\..\include\d3drm" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D _LICENSED_VERSION=0 /Yu"stdafx.h" /FD /MTd /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /O1 /D "NDEBUG" /D _LICENSED_VERSION=0 /D "WIN32" /D "_WINDOWS" /D "_NOT_X86" /D _ALPHA_=1 /D ALPHA=1 /Yu"stdafx.h" /FD /MTd /c
# SUBTRACT CPP /X
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dxtrans.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /libpath:"..\..\..\..\..\..\Lib\i386"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 dxtrans.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Wipe___1
TargetPath=.\Wipe___1\wipe.dll
InputPath=.\Wipe___1\wipe.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release Licensed"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Wipe___2"
# PROP BASE Intermediate_Dir "Wipe___2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Wipe___2"
# PROP Intermediate_Dir "Wipe___2"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /O1 /I "..\..\..\..\..\include" /I "..\..\..\..\..\include\dt" /I "..\..\..\..\..\include\d3drm" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /MTd /c
# SUBTRACT BASE CPP /X
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /O1 /D _LICENSED_VERSION=1 /D "_NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_NOT_X86" /D _ALPHA_=1 /D ALPHA=1 /Yu"stdafx.h" /FD /MTd /c
# SUBTRACT CPP /X
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dxtrans.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /libpath:"..\..\..\..\..\..\Lib\i386"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 dxtrans.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# SUBTRACT LINK32 /debug
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Wipe___2
TargetPath=.\Wipe___2\wipe.dll
InputPath=.\Wipe___2\wipe.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Wipe - Win32 Debug"
# Name "Wipe - Win32 Release"
# Name "Wipe - Win32 Release Licensed"
# Name "Wipe - Win32 Alpha Debug"
# Name "Wipe - Win32 Alpha Release"
# Name "Wipe - Win32 Alpha Release Licensed"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DXTWipe.cpp

!IF  "$(CFG)" == "Wipe - Win32 Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release Licensed"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release Licensed"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Wipe - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release Licensed"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Debug"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release Licensed"

# ADD BASE CPP /Gt0 /Yc"stdafx.h"
# ADD CPP /Gt0 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Wipe.cpp

!IF  "$(CFG)" == "Wipe - Win32 Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release Licensed"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release Licensed"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Wipe.def
# End Source File
# Begin Source File

SOURCE=.\Wipe.idl

!IF  "$(CFG)" == "Wipe - Win32 Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\Wipe.idl

BuildCmds= \
	midl /I \n2\private\dxmdev\idl /Oicf /h "Wipe.h" /iid "Wipe_i.c" "Wipe.idl"

".\Wipe.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release"

# Begin Custom Build - Performing MIDL step
InputPath=.\Wipe.idl

BuildCmds= \
	midl /I \n2\private\dxmdev\idl /Oicf /h "Wipe.h" /iid "Wipe_i.c" "Wipe.idl"

".\Wipe.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release Licensed"

# Begin Custom Build - Performing MIDL step
InputPath=.\Wipe.idl

BuildCmds= \
	midl /I \n2\private\dxmdev\idl /Oicf /h "Wipe.h" /iid "Wipe_i.c" "Wipe.idl"

".\Wipe.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\Wipe.idl

BuildCmds= \
	midl /I \n2\private\dxmdev\idl /Oicf /h "Wipe.h" /iid "Wipe_i.c" "Wipe.idl"

".\Wipe.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release"

# Begin Custom Build - Performing MIDL step
InputPath=.\Wipe.idl

BuildCmds= \
	midl /I \n2\private\dxmdev\idl /Oicf /h "Wipe.h" /iid "Wipe_i.c" "Wipe.idl"

".\Wipe.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release Licensed"

# Begin Custom Build - Performing MIDL step
InputPath=.\Wipe.idl

BuildCmds= \
	midl /I \n2\private\dxmdev\idl /Oicf /h "Wipe.h" /iid "Wipe_i.c" "Wipe.idl"

".\Wipe.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Wipe_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Wipe.rc

!IF  "$(CFG)" == "Wipe - Win32 Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release"

# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release Licensed"

# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release"

# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release Licensed"

# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WipePP.cpp

!IF  "$(CFG)" == "Wipe - Win32 Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Release Licensed"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "Wipe - Win32 Alpha Release Licensed"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DXTWipe.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WipePP.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe;rgs"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\dxsdk.ico
# End Source File
# Begin Source File

SOURCE=.\DXTWipe.rgs
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\WipePP.rgs
# End Source File
# End Group
# End Target
# End Project
