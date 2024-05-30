# Microsoft Developer Studio Project File - Name="msdfmap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=msdfmap - Win32 X86 SAMPLE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "msdfmap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "msdfmap.mak" CFG="msdfmap - Win32 X86 SAMPLE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "msdfmap - Win32 ALPHA SAMPLE" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "msdfmap - Win32 UTILTEST" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "msdfmap - Win32 X86 SAMPLE" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/mdac25/rtm/Data Access SDK/Samples/rds/Handler/vc", QOJCBAAA"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\navdgf_0"
# PROP BASE Intermediate_Dir ".\navdgf_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "alpha\debug"
# PROP Intermediate_Dir "alpha\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /MTd /c
# ADD CPP /nologo /Gt0 /W3 /WX /GX /Zi /Od /D "_DEBUG" /D MDACVER=21 /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D BETAVER=9 /D MDACBETAVER=219 /YX"stdafx.h" /FD /MTd /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /alpha
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d MDACVER=21 /d BETAVER=9 /d MDACBETAVER=219
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x69f80000" /subsystem:windows /dll /map /debug /machine:ALPHA /out:"alpha\debug/msdfmap_vc.dll"
# Begin Special Build Tool
TargetPath=.\alpha\debug\msdfmap_vc.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Register msdfmap_vc.dll
PostBuild_Cmds=regsvr32  /s /c $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msdfmap_"
# PROP BASE Intermediate_Dir "msdfmap_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86\debug"
# PROP Intermediate_Dir "x86\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Gf /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /YX"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Gy /Fr
# ADD CPP /nologo /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "UTILTEST" /D MDACVER=21 /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D BETAVER=9 /D MDACBETAVER=219 /YX"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d MDACVER=21 /d BETAVER=9 /d MDACBETAVER=219
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\utiltest\utiltest.bsc"
LINK32=link.exe
# ADD BASE LINK32 msvcrtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x1f8c0000" /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /nodefaultlib:"LIBCMTD" /pdbtype:sept
# SUBTRACT BASE LINK32 /verbose /profile /nodefaultlib
# ADD LINK32 msvcrtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x1f8c0000" /subsystem:console /incremental:no /map /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"x86\debug\utiltest.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x86\debug"
# PROP BASE Intermediate_Dir "x86\debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86\release"
# PROP Intermediate_Dir "x86\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Gf /D "_DEBUG" /D "_UNICODE" /D MDACVER=21 /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D MICROSOFT_INTERNAL_BUILD=0 /D MDACBETAVER=219 /YX"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Gy /Fr
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D MDACVER=21 /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D BETAVER=9 /D MDACBETAVER=219 /YX"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d MICROSOFT_INTERNAL_BUILD=0 /d MDACVER=21
# ADD RSC /l 0x409 /d "_DEBUG" /d MDACVER=21 /d BETAVER=9 /d MDACBETAVER=219
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msvcrtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x69f80000" /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /nodefaultlib:"LIBCMTD" /pdbtype:sept
# SUBTRACT BASE LINK32 /verbose /profile /nodefaultlib
# ADD LINK32 msvcrtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x69f80000" /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /nodefaultlib:"LIBCMTD" /out:"x86\release/msdfmap_vc.dll" /pdbtype:sept
# SUBTRACT LINK32 /verbose /profile /nodefaultlib
# Begin Special Build Tool
TargetPath=.\x86\release\msdfmap_vc.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Register msdfmap_vc.dll
PostBuild_Cmds=regsvr32 /s /c $(TargetPath)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "msdfmap - Win32 ALPHA SAMPLE"
# Name "msdfmap - Win32 UTILTEST"
# Name "msdfmap - Win32 X86 SAMPLE"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\const.cpp

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

DEP_CPP_CONST=\
	".\adoid.h"\
	

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Handler.cpp

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

DEP_CPP_HANDL=\
	".\adoid.h"\
	".\adoint.h"\
	".\HANDLER.h"\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_HANDL=\
	".\msdfhdl.h"\
	".\msdfmap.h"\
	

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /D "_UNICODE"

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

# SUBTRACT BASE CPP /D "_UNICODE"
# SUBTRACT CPP /D "_UNICODE"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msdfmap.cpp

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

DEP_CPP_MSDFM=\
	".\adoint.h"\
	".\HANDLER.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MSDFM=\
	".\msdfhdl.cpp"\
	".\msdfhdl.h"\
	".\msdfmap.h"\
	".\msdfmap_i.cpp"\
	

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /D "_UNICODE"

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

# SUBTRACT BASE CPP /D "_UNICODE"
# SUBTRACT CPP /D "_UNICODE"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msdfmap.def

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /D "_UNICODE"

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

# SUBTRACT BASE CPP /D "_UNICODE"
# SUBTRACT CPP /D "_UNICODE"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\util.cpp

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

DEP_CPP_UTIL_=\
	".\StdAfx.h"\
	".\util.h"\
	
NODEP_CPP_UTIL_=\
	".\utiltest\21.cpp"\
	

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\HANDLER.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\handler_ms.rgs
# End Source File
# Begin Source File

SOURCE=.\handler_vc.rgs
# End Source File
# Begin Source File

SOURCE=.\msdfmap.rc

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\msdfhdl.idl

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

# PROP Intermediate_Dir "."
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\msdfhdl.idl

BuildCmds= \
	midl /h msdfhdl.h /iid msdfhdl.cpp /tlb  msdfhdl.tlb msdfhdl.idl

".\msdfhdl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfhdl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfhdl.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP BASE Intermediate_Dir "."
# PROP Intermediate_Dir "."
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

# PROP BASE Intermediate_Dir "."
# PROP Intermediate_Dir "."
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\msdfhdl.idl

BuildCmds= \
	midl /h msdfhdl.h /iid msdfhdl.cpp /tlb  msdfhdl.tlb msdfhdl.idl

".\msdfhdl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfhdl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfhdl.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msdfmap.idl

!IF  "$(CFG)" == "msdfmap - Win32 ALPHA SAMPLE"

# PROP Intermediate_Dir "."
# PROP Ignore_Default_Tool 1
USERDEP__MSDFMA=".\msdfhdl.tlb"	
# Begin Custom Build
InputPath=.\msdfmap.idl

BuildCmds= \
	midl /h msdfmap.h /iid msdfmap_i.cpp /tlb msdfmap.tlb msdfmap.idl

".\msdfmap.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfmap_i.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfmap.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "msdfmap - Win32 UTILTEST"

# PROP BASE Intermediate_Dir "."
# PROP Intermediate_Dir "."
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "msdfmap - Win32 X86 SAMPLE"

# PROP BASE Intermediate_Dir "."
# PROP Intermediate_Dir "."
# PROP Ignore_Default_Tool 1
USERDEP__MSDFMA=".\msdfhdl.tlb"	
# Begin Custom Build
InputPath=.\msdfmap.idl

BuildCmds= \
	midl /h msdfmap.h /iid msdfmap_i.cpp /tlb msdfmap.tlb msdfmap.idl

".\msdfmap.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfmap_i.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\msdfmap.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
