# Microsoft Developer Studio Project File - Name="poppst" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

CFG=poppst - Win32 Debug Alpha
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "poppst.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "poppst.mak" CFG="poppst - Win32 Debug Alpha"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "poppst - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "poppst - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "poppst - Win32 Debug Alpha" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "poppst - Win32 Release Alpha" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "poppst - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ole32.lib mapi32.lib exchsdk.lib msvcrt.lib version.lib uuid.lib shell32.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug"

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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib oleaut32.lib odbc32.lib odbccp32.lib exchsdkd.lib mapi32.lib version.lib uuid.lib shell32.lib oldnames.lib ole32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "poppst__"
# PROP BASE Intermediate_Dir "poppst__"
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
# ADD CPP /nologo /MDd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 exchsdkd.lib mapi32.lib version.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 exchsdkd.lib mapi32.lib version.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA /nodefaultlib:"libc" /nodefaultlib:"MSVCRT" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "poppst - Win32 Release Alpha"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "poppst_0"
# PROP BASE Intermediate_Dir "poppst_0"
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
# ADD BASE LINK32 mapi32.lib exchsdk.lib msvcrt.lib version.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA /nodefaultlib:"libc"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mapi32.lib exchsdk.lib msvcrt.lib version.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA /nodefaultlib:"libc"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "poppst - Win32 Release"
# Name "poppst - Win32 Debug"
# Name "poppst - Win32 Debug Alpha"
# Name "poppst - Win32 Release Alpha"
# Begin Source File

SOURCE=.\Msg00001.bin
# End Source File
# Begin Source File

SOURCE=.\PopPst.Cpp

!IF  "$(CFG)" == "poppst - Win32 Release"

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug"

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug Alpha"

DEP_CPP_POPPS=\
	".\poppst.chk"\
	".\popstrs.h"\
	{$(INCLUDE)}"_entryid.h"\
	{$(INCLUDE)}"aclcls.h"\
	{$(INCLUDE)}"aclsid.h"\
	{$(INCLUDE)}"addrlkup.h"\
	{$(INCLUDE)}"convcwrp.h"\
	{$(INCLUDE)}"convstrc.h"\
	{$(INCLUDE)}"edk.h"\
	{$(INCLUDE)}"edkcfg.h"\
	{$(INCLUDE)}"edkcode.h"\
	{$(INCLUDE)}"edkdebug.h"\
	{$(INCLUDE)}"edkevent.h"\
	{$(INCLUDE)}"edkguid.h"\
	{$(INCLUDE)}"edkmapi.h"\
	{$(INCLUDE)}"edkmdb.h"\
	{$(INCLUDE)}"edkmsg.h"\
	{$(INCLUDE)}"edktrack.h"\
	{$(INCLUDE)}"EdkUtCPP.H"\
	{$(INCLUDE)}"edkutils.h"\
	{$(INCLUDE)}"emsabtag.h"\
	{$(INCLUDE)}"exchinst.h"\
	{$(INCLUDE)}"gwreport.h"\
	{$(INCLUDE)}"mblogon.h"\
	{$(INCLUDE)}"monitor.h"\
	{$(INCLUDE)}"newpst.h"\
	{$(INCLUDE)}"proptag.h"\
	{$(INCLUDE)}"rclsid.h"\
	{$(INCLUDE)}"rpcpub.h"\
	{$(INCLUDE)}"rtflib.h"\
	{$(INCLUDE)}"rulecls.h"\
	{$(INCLUDE)}"stats.h"\
	{$(INCLUDE)}"stattype.h"\
	{$(INCLUDE)}"vsof.h"\
	{$(INCLUDE)}"vsop.h"\
	{$(INCLUDE)}"vsopcsid.h"\
	{$(INCLUDE)}"winwrap.h"\
	
NODEP_CPP_POPPS=\
	".\poppstmc.h"\
	

!ELSEIF  "$(CFG)" == "poppst - Win32 Release Alpha"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PopPst.Rc

!IF  "$(CFG)" == "poppst - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "poppst - Win32 Release Alpha"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PopPstmc.Mc

!IF  "$(CFG)" == "poppst - Win32 Release"

# Begin Custom Build
InputPath=.\PopPstmc.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  poppstmc.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug"

# Begin Custom Build
InputPath=.\PopPstmc.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  poppstmc.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug Alpha"

# Begin Custom Build
InputPath=.\PopPstmc.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  poppstmc.mc

# End Custom Build

!ELSEIF  "$(CFG)" == "poppst - Win32 Release Alpha"

# Begin Custom Build
InputPath=.\PopPstmc.Mc

".\Msg00001.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -v -c -s  poppstmc.mc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PopPStrc.Rc

!IF  "$(CFG)" == "poppst - Win32 Release"

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug"

!ELSEIF  "$(CFG)" == "poppst - Win32 Debug Alpha"

!ELSEIF  "$(CFG)" == "poppst - Win32 Release Alpha"

!ENDIF 

# End Source File
# End Target
# End Project
