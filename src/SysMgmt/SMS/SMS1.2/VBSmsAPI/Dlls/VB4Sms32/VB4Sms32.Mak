# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=VB4SMS32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to VB4SMS32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VB4SMS32 - Win32 Release" && "$(CFG)" !=\
 "VB4SMS32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "VB4SMS32.mak" CFG="VB4SMS32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VB4SMS32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VB4SMS32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "VB4SMS32 - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "VB4SMS32 - Win32 Release"

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

ALL : "$(OUTDIR)\VB4SMS32.olb"

CLEAN : 
	-@erase "$(INTDIR)\Vb4sms32.obj"
	-@erase "$(INTDIR)\VB4SMS32.res"
	-@erase "$(INTDIR)\VB4SMS32.tlb"
	-@erase "$(OUTDIR)\VB4SMS32.exp"
	-@erase "$(OUTDIR)\VB4SMS32.lib"
	-@erase "$(OUTDIR)\VB4SMS32.map"
	-@erase "$(OUTDIR)\VB4SMS32.olb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/VB4SMS32.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VB4SMS32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VB4SMS32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib oleaut32.lib smsapi.Lib msvcrt.lib /nologo /subsystem:windows /dll /map /machine:I386 /nodefaultlib /out:"Release/VB4SMS32.olb"
LINK32_FLAGS=kernel32.lib oleaut32.lib smsapi.Lib msvcrt.lib \
 /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/VB4SMS32.pdb" /map:"$(INTDIR)/VB4SMS32.map" /machine:I386\
 /nodefaultlib /def:".\VB4SMS32.DEF" /out:"$(OUTDIR)/VB4SMS32.olb"\
 /implib:"$(OUTDIR)/VB4SMS32.lib" 
DEF_FILE= \
	".\VB4SMS32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Vb4sms32.obj" \
	"$(INTDIR)\VB4SMS32.res"

"$(OUTDIR)\VB4SMS32.olb" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VB4SMS32 - Win32 Debug"

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

ALL : "$(OUTDIR)\VB4SMS32.olb"

CLEAN : 
	-@erase "$(INTDIR)\Vb4sms32.obj"
	-@erase "$(INTDIR)\VB4SMS32.res"
	-@erase "$(INTDIR)\VB4SMS32.tlb"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\VB4SMS32.exp"
	-@erase "$(OUTDIR)\VB4SMS32.ilk"
	-@erase "$(OUTDIR)\VB4SMS32.lib"
	-@erase "$(OUTDIR)\VB4SMS32.map"
	-@erase "$(OUTDIR)\VB4SMS32.olb"
	-@erase "$(OUTDIR)\VB4SMS32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)/VB4SMS32.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/VB4SMS32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/VB4SMS32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib oleaut32.lib smsapi.lib msvcrtd.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib /out:"Debug/VB4SMS32.olb"
LINK32_FLAGS=kernel32.lib oleaut32.lib smsapi.lib msvcrtd.lib \
 /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/VB4SMS32.pdb" /map:"$(INTDIR)/VB4SMS32.map" /debug\
 /machine:I386 /nodefaultlib /def:".\VB4SMS32.DEF" /out:"$(OUTDIR)/VB4SMS32.olb"\
 /implib:"$(OUTDIR)/VB4SMS32.lib" 
DEF_FILE= \
	".\VB4SMS32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Vb4sms32.obj" \
	"$(INTDIR)\VB4SMS32.res"

"$(OUTDIR)\VB4SMS32.olb" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "VB4SMS32 - Win32 Release"
# Name "VB4SMS32 - Win32 Debug"

!IF  "$(CFG)" == "VB4SMS32 - Win32 Release"

!ELSEIF  "$(CFG)" == "VB4SMS32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Vb4sms32.cpp
DEP_CPP_VB4SM=\
	".\Vb4sms32.h"\
	

"$(INTDIR)\Vb4sms32.obj" : $(SOURCE) $(DEP_CPP_VB4SM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\VB4SMS32.DEF

!IF  "$(CFG)" == "VB4SMS32 - Win32 Release"

!ELSEIF  "$(CFG)" == "VB4SMS32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VB4SMS32.odl

!IF  "$(CFG)" == "VB4SMS32 - Win32 Release"


"$(OUTDIR)\VB4SMS32.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/VB4SMS32.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "VB4SMS32 - Win32 Debug"


"$(OUTDIR)\VB4SMS32.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/VB4SMS32.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VB4SMS32.rc

!IF  "$(CFG)" == "VB4SMS32 - Win32 Release"

NODEP_RSC_VB4SMS=\
	".\Release\VB4SMS32.tlb"\
	

"$(INTDIR)\VB4SMS32.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VB4SMS32.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VB4SMS32.res" /i "Release" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "VB4SMS32 - Win32 Debug"

NODEP_RSC_VB4SMS=\
	".\Debug\VB4SMS32.tlb"\
	

"$(INTDIR)\VB4SMS32.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VB4SMS32.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/VB4SMS32.res" /i "Debug" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
