# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=JView - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to JView - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "JView - Win32 Release" && "$(CFG)" != "JView - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "JView.mak" CFG="JView - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JView - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "JView - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "JView - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JView - Win32 Release"

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

ALL : "$(OUTDIR)\JView.exe"

CLEAN : 
	-@erase "$(INTDIR)\javaprop.obj"
	-@erase "$(INTDIR)\jview.obj"
	-@erase "$(INTDIR)\JView.res"
	-@erase "$(OUTDIR)\JView.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D\
 "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)/JView.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/JView.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/JView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib msvcrt.lib /nologo /subsystem:console /machine:I386 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib msvcrt.lib /nologo /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/JView.pdb" /machine:I386 /nodefaultlib\
 /out:"$(OUTDIR)/JView.exe" 
LINK32_OBJS= \
	"$(INTDIR)\javaprop.obj" \
	"$(INTDIR)\jview.obj" \
	"$(INTDIR)\JView.res"

"$(OUTDIR)\JView.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "JView - Win32 Debug"

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

ALL : "$(OUTDIR)\JView.exe"

CLEAN : 
	-@erase "$(INTDIR)\javaprop.obj"
	-@erase "$(INTDIR)\jview.obj"
	-@erase "$(INTDIR)\JView.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\JView.exe"
	-@erase "$(OUTDIR)\JView.ilk"
	-@erase "$(OUTDIR)\JView.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32"\
 /D "_DEBUG" /D "_CONSOLE" /Fp"$(INTDIR)/JView.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/JView.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/JView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib msvcrt.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib msvcrt.lib /nologo /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/JView.pdb" /debug /machine:I386 /nodefaultlib\
 /out:"$(OUTDIR)/JView.exe" 
LINK32_OBJS= \
	"$(INTDIR)\javaprop.obj" \
	"$(INTDIR)\jview.obj" \
	"$(INTDIR)\JView.res"

"$(OUTDIR)\JView.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "JView - Win32 Release"
# Name "JView - Win32 Debug"

!IF  "$(CFG)" == "JView - Win32 Release"

!ELSEIF  "$(CFG)" == "JView - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "JView - Win32 Release"

!ELSEIF  "$(CFG)" == "JView - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\jview.h

!IF  "$(CFG)" == "JView - Win32 Release"

!ELSEIF  "$(CFG)" == "JView - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JView.rc

"$(INTDIR)\JView.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\jview.cpp
DEP_CPP_JVIEW=\
        ".\javaprop.hpp"\
	".\jview.h"\
	

"$(INTDIR)\jview.obj" : $(SOURCE) $(DEP_CPP_JVIEW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\javaprop.cpp
DEP_CPP_JAVAP=\
	".\javaprop.hpp"\
	

"$(INTDIR)\javaprop.obj" : $(SOURCE) $(DEP_CPP_JAVAP) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
