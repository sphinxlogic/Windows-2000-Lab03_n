# Microsoft Developer Studio Project File - Name="gwclean" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

CFG=gwclean - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gwclean.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gwclean.mak" CFG="gwclean - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gwclean - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gwclean - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "gwclean - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "gwclean - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "gwclean - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /O<none>
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 mapi32.lib version.lib exchsdk.lib msvcrt.lib ole32.lib uuid.lib shell32.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib oleaut32.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"MSVCRT"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mapi32.lib version.lib exchsdkd.lib msvcrtd.lib ole32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib oleaut32.lib odbc32.lib odbccp32.lib uuid.lib shell32.lib oldnames.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gwclean_"
# PROP BASE Intermediate_Dir "gwclean_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /MDd /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib version.lib exchsdkd.lib msvcrtd.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mapi32.lib version.lib exchsdkd.lib msvcrtd.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "gwclean - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gwclean0"
# PROP BASE Intermediate_Dir "gwclean0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib version.lib exchsdk.lib msvcrt.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mapi32.lib version.lib exchsdk.lib msvcrt.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "gwclean - Win32 Release"
# Name "gwclean - Win32 Debug"
# Name "gwclean - Win32 Debug Alpha"
# Name "gwclean - Win32 Release Alpha"
# Begin Source File

SOURCE=.\GWClean.Cpp

!IF  "$(CFG)" == "gwclean - Win32 Release"

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug"

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug Alpha"

DEP_CPP_GWCLE=\
	".\gwclean.chk"\
	".\gwobjcls.h"\
	".\gwstring.h"\
	
NODEP_CPP_GWCLE=\
	".\blogon.h"\
	".\clcls.h"\
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
	".\gwevents.h"\
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
	".\ulecls.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "gwclean - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GWClean.Rc
# End Source File
# Begin Source File

SOURCE=.\GWevents.Mc

!IF  "$(CFG)" == "gwclean - Win32 Release"

# Begin Custom Build
InputPath=.\GWevents.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  GwEvents.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug"

# Begin Custom Build
InputPath=.\GWevents.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  GwEvents.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug Alpha"

# Begin Custom Build
InputPath=.\GWevents.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  GwEvents.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "gwclean - Win32 Release Alpha"

# Begin Custom Build
InputPath=.\GWevents.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  GwEvents.mc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GwEvents.rc

!IF  "$(CFG)" == "gwclean - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gwclean - Win32 Release Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GWobjCls.Cpp

!IF  "$(CFG)" == "gwclean - Win32 Release"

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug"

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug Alpha"

DEP_CPP_GWOBJ=\
	".\gwobjcls.chk"\
	".\gwobjcls.h"\
	".\gwstring.h"\
	
NODEP_CPP_GWOBJ=\
	".\blogon.h"\
	".\clcls.h"\
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
	".\gwevents.h"\
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
	".\ulecls.h"\
	".\wreport.h"\
	".\xchinst.h"\
	

!ELSEIF  "$(CFG)" == "gwclean - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GWStrtbl.Rc

!IF  "$(CFG)" == "gwclean - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gwclean - Win32 Debug Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "gwclean - Win32 Release Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Msg00001.bin
# End Source File
# End Target
# End Project
