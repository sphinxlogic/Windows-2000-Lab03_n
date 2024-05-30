# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=JDbgHlpr - Win32 Release
!MESSAGE No configuration specified.  Defaulting to JDbgHlpr - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "JDbgHlpr - Win32 Release" && "$(CFG)" !=\
 "JDbgHlpr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "JDbgHlpr.mak" CFG="JDbgHlpr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JDbgHlpr - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JDbgHlpr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "JDbgHlpr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

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

ALL : "$(OUTDIR)\JDbgHlpr.dll"

CLEAN : 
	-@erase "$(INTDIR)\helpers.obj"
	-@erase "$(INTDIR)\JDbgHlpr.obj"
	-@erase "$(INTDIR)\JDbgHlpr.res"
	-@erase "$(INTDIR)\process.obj"
	-@erase "$(OUTDIR)\JDbgHlpr.dll"
	-@erase "$(OUTDIR)\JDbgHlpr.exp"
	-@erase "$(OUTDIR)\JDbgHlpr.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gz /MD /W3 /GX /O2 /I "..\..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Gz /MD /W3 /GX /O2 /I "..\..\..\..\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/JDbgHlpr.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/JDbgHlpr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/JDbgHlpr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrt.lib ..\..\..\..\..\lib\i386\msjava.lib ..\..\..\..\..\lib\i386\javadbg.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib msvcrt.lib ..\..\..\..\lib\i386\msjava.lib\
 ..\..\..\..\lib\i386\javadbg.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/JDbgHlpr.pdb" /machine:I386 /nodefaultlib\
 /def:".\JDbgHlpr.def" /out:"$(OUTDIR)/JDbgHlpr.dll"\
 /implib:"$(OUTDIR)/JDbgHlpr.lib" 
DEF_FILE= \
	".\JDbgHlpr.def"
LINK32_OBJS= \
	"$(INTDIR)\helpers.obj" \
	"$(INTDIR)\JDbgHlpr.obj" \
	"$(INTDIR)\JDbgHlpr.res" \
	"$(INTDIR)\process.obj"

"$(OUTDIR)\JDbgHlpr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

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

ALL : "$(OUTDIR)\JDbgHlpr.dll"

CLEAN : 
	-@erase "$(INTDIR)\helpers.obj"
	-@erase "$(INTDIR)\JDbgHlpr.obj"
	-@erase "$(INTDIR)\JDbgHlpr.res"
	-@erase "$(INTDIR)\process.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\JDbgHlpr.dll"
	-@erase "$(OUTDIR)\JDbgHlpr.exp"
	-@erase "$(OUTDIR)\JDbgHlpr.ilk"
	-@erase "$(OUTDIR)\JDbgHlpr.lib"
	-@erase "$(OUTDIR)\JDbgHlpr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gz /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Gz /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/JDbgHlpr.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/JDbgHlpr.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/JDbgHlpr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrt.lib ..\..\..\..\..\lib\i386\msjava.lib ..\..\..\..\..\lib\i386\javadbg.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib msvcrt.lib ..\..\..\..\lib\i386\msjava.lib\
 ..\..\..\..\lib\i386\javadbg.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/JDbgHlpr.pdb" /debug /machine:I386\
 /nodefaultlib /def:".\JDbgHlpr.def" /out:"$(OUTDIR)/JDbgHlpr.dll"\
 /implib:"$(OUTDIR)/JDbgHlpr.lib" 
DEF_FILE= \
	".\JDbgHlpr.def"
LINK32_OBJS= \
	"$(INTDIR)\helpers.obj" \
	"$(INTDIR)\JDbgHlpr.obj" \
	"$(INTDIR)\JDbgHlpr.res" \
	"$(INTDIR)\process.obj"

"$(OUTDIR)\JDbgHlpr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "JDbgHlpr - Win32 Release"
# Name "JDbgHlpr - Win32 Debug"

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\process.cpp
DEP_CPP_PROCE=\
        "..\..\..\..\include\javadbg.h"\
        "..\..\..\..\include\nativcom.h"\
        "..\..\..\..\include\native.h"\
	".\DebuggeeProcess.h"\
	".\project.hpp"\
	

"$(INTDIR)\process.obj" : $(SOURCE) $(DEP_CPP_PROCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\JDbgHlpr.cpp
DEP_CPP_JDBGH=\
        "..\..\..\..\include\javadbg.h"\
        "..\..\..\..\include\nativcom.h"\
        "..\..\..\..\include\native.h"\
	".\project.hpp"\
	

"$(INTDIR)\JDbgHlpr.obj" : $(SOURCE) $(DEP_CPP_JDBGH) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\helpers.cpp
DEP_CPP_HELPE=\
        "..\..\..\..\include\javadbg.h"\
        "..\..\..\..\include\nativcom.h"\
        "..\..\..\..\include\native.h"\
	".\com_ms_debug_ConstantPoolHelper.h"\
	".\com_ms_debug_EnumRemoteBooleanValueHelper.h"\
	".\com_ms_debug_EnumRemoteDoubleValueHelper.h"\
	".\com_ms_debug_EnumRemoteFloatValueHelper.h"\
	".\com_ms_debug_LockBytesHelper.h"\
	".\com_ms_debug_RemoteBooleanObjectHelper.h"\
	".\com_ms_debug_RemoteDoubleObjectHelper.h"\
	".\com_ms_debug_RemoteFloatObjectHelper.h"\
	".\project.hpp"\
	

"$(INTDIR)\helpers.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\JDbgHlpr.def

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DebuggeeProcess.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_EnumRemoteBooleanValueHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_EnumRemoteDoubleValueHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_EnumRemoteFloatValueHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_LockBytesHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_RemoteBooleanObjectHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_RemoteDoubleObjectHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_RemoteFloatObjectHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\com_ms_debug_ConstantPoolHelper.h

!IF  "$(CFG)" == "JDbgHlpr - Win32 Release"

!ELSEIF  "$(CFG)" == "JDbgHlpr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JDbgHlpr.rc

"$(INTDIR)\JDbgHlpr.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
