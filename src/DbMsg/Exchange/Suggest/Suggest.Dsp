# Microsoft Developer Studio Project File - Name="Suggest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=Suggest - Win32 Alpha Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Suggest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Suggest.mak" CFG="Suggest - Win32 Alpha Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Suggest - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Suggest - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Suggest - Win32 Alpha Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Suggest - Win32 Alpha Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Suggest - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /FR /YX /FD /c
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mapi32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "Suggest - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /YX /FD /c
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mapi32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Suggest_"
# PROP BASE Intermediate_Dir "Suggest_"
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
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /YX /FD /MTd /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /YX /FD /MTd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /pdbtype:sept

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Suggest0"
# PROP BASE Intermediate_Dir "Suggest0"
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
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /MT /Gt0 /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_ATL_STATIC_REGISTRY" /FR /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 mapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA

!ENDIF 

# Begin Target

# Name "Suggest - Win32 Release"
# Name "Suggest - Win32 Debug"
# Name "Suggest - Win32 Alpha Debug"
# Name "Suggest - Win32 Alpha Release"
# Begin Source File

SOURCE=.\exevhandler.cpp

!IF  "$(CFG)" == "Suggest - Win32 Release"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Release"

DEP_CPP_EXEVH=\
	".\esconf.h"\
	".\esconf_i.c"\
	".\exchhndl.h"\
	".\exchhndl_i.c"\
	".\exevhandler.h"\
	".\propid.h"\
	".\stdafx.h"\
	".\suggest.h"\
	".\SuggestEvents.h"\
	
NODEP_CPP_EXEVH=\
	".\dkmdb.h"\
	".\msabtag.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\exevhandler.rgs
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Suggest - Win32 Release"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Release"

DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\suggest.cpp

!IF  "$(CFG)" == "Suggest - Win32 Release"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Release"

DEP_CPP_SUGGE=\
	".\esconf.h"\
	".\exchhndl.h"\
	".\exevhandler.h"\
	".\stdafx.h"\
	".\suggest.h"\
	".\suggest_i.c"\
	
NODEP_CPP_SUGGE=\
	".\dkmdb.h"\
	".\msabtag.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\suggest.def
# End Source File
# Begin Source File

SOURCE=.\suggest.idl

!IF  "$(CFG)" == "Suggest - Win32 Release"

# Begin Custom Build
InputPath=.\suggest.idl

BuildCmds= \
	midl /Oicf /h "Suggest.h" /iid "Suggest_i.c" "Suggest.idl"

".\suggest.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Suggest - Win32 Debug"

# Begin Custom Build
InputPath=.\suggest.idl

BuildCmds= \
	midl /Oicf /h "suggest.h" /iid "suggest_i.c" "suggest.idl"

".\suggest.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Debug"

# Begin Custom Build
InputPath=.\suggest.idl

BuildCmds= \
	midl /Oicf /h "suggest.h" /iid "suggest_i.c" "suggest.idl"

".\suggest.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Release"

# Begin Custom Build
InputPath=.\suggest.idl

BuildCmds= \
	midl /Oicf /h "Suggest.h" /iid "Suggest_i.c" "Suggest.idl"

".\suggest.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\suggest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\suggest.rc
# End Source File
# Begin Source File

SOURCE=.\suggestevents.cpp

!IF  "$(CFG)" == "Suggest - Win32 Release"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Suggest - Win32 Alpha Release"

DEP_CPP_SUGGES=\
	".\esconf.h"\
	".\exchhndl.h"\
	".\exevhandler.h"\
	".\stdafx.h"\
	".\suggest.h"\
	".\SuggestEvents.h"\
	
NODEP_CPP_SUGGES=\
	".\dkmdb.h"\
	".\msabtag.h"\
	

!ENDIF 

# End Source File
# End Target
# End Project
