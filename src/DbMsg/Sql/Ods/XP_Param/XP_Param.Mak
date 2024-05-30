# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=xp_param - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to xp_param - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "xp_param - Win32 Release" && "$(CFG)" !=\
 "xp_param - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "xp_param.mak" CFG="xp_param - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xp_param - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xp_param - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xp_param - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\xp_param.dll"

CLEAN : 
	-@erase "$(INTDIR)\xp_param.obj"
	-@erase "$(OUTDIR)\xp_param.dll"
	-@erase "$(OUTDIR)\xp_param.exp"
	-@erase "$(OUTDIR)\xp_param.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp_param.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_param.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib opends60.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib opends60.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/xp_param.pdb" /machine:I386\
 /def:".\xp_param.def" /out:"$(OUTDIR)/xp_param.dll"\
 /implib:"$(OUTDIR)/xp_param.lib" 
DEF_FILE= \
	".\xp_param.def"
LINK32_OBJS= \
	"$(INTDIR)\xp_param.obj"

"$(OUTDIR)\xp_param.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xp_param - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\xp_param.dll"

CLEAN : 
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\xp_param.obj"
	-@erase "$(OUTDIR)\xp_param.dll"
	-@erase "$(OUTDIR)\xp_param.exp"
	-@erase "$(OUTDIR)\xp_param.ilk"
	-@erase "$(OUTDIR)\xp_param.lib"
	-@erase "$(OUTDIR)\xp_param.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/xp_param.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xp_param.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib opends60.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib opends60.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/xp_param.pdb" /debug /machine:I386\
 /def:".\xp_param.def" /out:"$(OUTDIR)/xp_param.dll"\
 /implib:"$(OUTDIR)/xp_param.lib" 
DEF_FILE= \
	".\xp_param.def"
LINK32_OBJS= \
	"$(INTDIR)\xp_param.obj"

"$(OUTDIR)\xp_param.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "xp_param - Win32 Release"
# Name "xp_param - Win32 Debug"

!IF  "$(CFG)" == "xp_param - Win32 Release"

!ELSEIF  "$(CFG)" == "xp_param - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\xp_param.c
DEP_CPP_XP_PA=\
	{$(INCLUDE)}"\srv.h"\
	

"$(INTDIR)\xp_param.obj" : $(SOURCE) $(DEP_CPP_XP_PA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\xp_param.def

!IF  "$(CFG)" == "xp_param - Win32 Release"

!ELSEIF  "$(CFG)" == "xp_param - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
