# Microsoft Developer Studio Project File - Name="filter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=filter - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Filter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Filter.mak" CFG="filter - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "filter - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "filter - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "filter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gz /MD /W3 /O2 /D "NDEBUG" /D "INC_OLE2" /D "STRICT" /D "WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D try=__try /D except=__except /D leave=__leave /D finally=__finally /U "DBG" /U "DEBUG" /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 strmbase.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib /nologo /base:"0x1c400000" /version:4.0 /entry:"DllEntryPoint@12" /dll /pdb:none /machine:I386 /nodefaultlib /out:"filter.ax" /subsystem:windows,4.0

!ELSEIF  "$(CFG)" == "filter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gz /MDd /W3 /GR /GX /Z7 /D "INC_OLE2" /D "STRICT" /D "WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D try=__try /D except=__except /D leave=__leave /D finally=__finally /FR /Oid /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 strmbasd.lib quartz.lib libcmtd.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib /nologo /base:"0x1c400000" /entry:"DllEntryPoint@12" /dll /pdb:none /debug /machine:I386 /nodefaultlib /out:"filter.ax" /subsystem:windows,4.0
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "filter - Win32 Release"
# Name "filter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Filter.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Filter.rc
# End Source File
# End Group
# End Target
# End Project
