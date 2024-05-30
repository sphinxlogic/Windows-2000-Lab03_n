# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

!IF "$(CFG)" == ""
CFG=SQLExamp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SQLExamp - Win32 \
 Debug.
!ENDIF 

!IF "$(CFG)" != "SQLExamp - Win32 Release" && "$(CFG)" !=\
 "SQLExamp - Win32 Debug" && "$(CFG)" != "SQLExamp - Win32 (ALPHA) Debug" &&\
 "$(CFG)" != "SQLExamp - Win32 (ALPHA) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SQLExamp.mak" CFG="SQLExamp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SQLExamp - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "SQLExamp - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "SQLExamp - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "SQLExamp - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Console Application")
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
# PROP Target_Last_Scanned "SQLExamp - Win32 Debug"

!IF  "$(CFG)" == "SQLExamp - Win32 Release"

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

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLExamp.exe"

CLEAN : 
	-@erase ".\Release\SQLExamp.exe"
	-@erase ".\Release\Sqlexamp.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "DBNTWIN32" /Fp"$(INTDIR)/SQLExamp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLExamp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/SQLExamp.pdb" /machine:I386 /out:"$(OUTDIR)/SQLExamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqlexamp.obj"

"$(OUTDIR)\SQLExamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 Debug"

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

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLExamp.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\SQLExamp.exe"
	-@erase ".\Debug\Sqlexamp.obj"
	-@erase ".\Debug\SQLExamp.ilk"
	-@erase ".\Debug\SQLExamp.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "DBNTWIN32" /Fp"$(INTDIR)/SQLExamp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLExamp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/SQLExamp.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SQLExamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqlexamp.obj"

"$(OUTDIR)\SQLExamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 (ALPHA) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SQLExamp"
# PROP BASE Intermediate_Dir "SQLExamp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SQLExamp"
# PROP Intermediate_Dir "SQLExamp"
# PROP Target_Dir ""
OUTDIR=.\SQLExamp
INTDIR=.\SQLExamp

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLExamp.exe"

CLEAN : 
	-@erase ".\SQLExamp\vc40.pdb"
	-@erase ".\SQLExamp\SQLExamp.exe"
	-@erase ".\SQLExamp\Sqlexamp.obj"
	-@erase ".\SQLExamp\SQLExamp.ilk"
	-@erase ".\SQLExamp\SQLExamp.pdb"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /MLd /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "DBNTWIN32" /Fp"$(INTDIR)/SQLExamp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\SQLExamp/
CPP_SBRS=

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLExamp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /debug /machine:ALPHA
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/SQLExamp.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)/SQLExamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqlexamp.obj"

"$(OUTDIR)\SQLExamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 (ALPHA) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SQLExam0"
# PROP BASE Intermediate_Dir "SQLExam0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SQLExam0"
# PROP Intermediate_Dir "SQLExam0"
# PROP Target_Dir ""
OUTDIR=.\SQLExam0
INTDIR=.\SQLExam0

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

ALL : "$(OUTDIR)\SQLExamp.exe"

CLEAN : 
	-@erase ".\SQLExam0\SQLExamp.exe"
	-@erase ".\SQLExam0\Sqlexamp.obj"

CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /Gt0 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /YX /c
CPP_PROJ=/nologo /ML /Gt0 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "DBNTWIN32" /Fp"$(INTDIR)/SQLExamp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\SQLExam0/
CPP_SBRS=

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SQLExamp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ntwdblib.lib /nologo /subsystem:console /machine:ALPHA
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ntwdblib.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/SQLExamp.pdb" /machine:ALPHA /out:"$(OUTDIR)/SQLExamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sqlexamp.obj"

"$(OUTDIR)\SQLExamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "SQLExamp - Win32 Release"
# Name "SQLExamp - Win32 Debug"
# Name "SQLExamp - Win32 (ALPHA) Debug"
# Name "SQLExamp - Win32 (ALPHA) Release"

!IF  "$(CFG)" == "SQLExamp - Win32 Release"

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 Debug"

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 (ALPHA) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Sqlexamp.c

!IF  "$(CFG)" == "SQLExamp - Win32 Release"

"$(INTDIR)\Sqlexamp.obj" : $(SOURCE) $(DEP_CPP_SQLEX) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 Debug"

"$(INTDIR)\Sqlexamp.obj" : $(SOURCE) $(DEP_CPP_SQLEX) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 (ALPHA) Debug"

"$(INTDIR)\Sqlexamp.obj" : $(SOURCE) $(DEP_CPP_SQLEX) "$(INTDIR)"

!ELSEIF  "$(CFG)" == "SQLExamp - Win32 (ALPHA) Release"

"$(INTDIR)\Sqlexamp.obj" : $(SOURCE) $(DEP_CPP_SQLEX) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
