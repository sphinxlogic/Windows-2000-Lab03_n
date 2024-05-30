# Microsoft Developer Studio Generated NMAKE File, Based on icpclnt2.dsp
!IF "$(CFG)" == ""
CFG=icpclnt2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to icpclnt2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "icpclnt2 - Win32 Release" && "$(CFG)" !=\
 "icpclnt2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "icpclnt2.mak" CFG="icpclnt2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "icpclnt2 - Win32 Release" (based on\
 "Win32 ($(CPU)) Console Application")
!MESSAGE "icpclnt2 - Win32 Debug" (based on "Win32 ($(CPU)) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "icpclnt2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\icpclnt2.exe"

!ELSE 

ALL : "$(OUTDIR)\icpclnt2.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\foricp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\icpclnt2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "_MBCS" /D "SECURITY_WIN32" /Fp"$(INTDIR)\icpclnt2.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\icpclnt2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\icpclnt2.pdb" /machine:$(CPU) /out:"$(OUTDIR)\icpclnt2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\foricp.obj"

"$(OUTDIR)\icpclnt2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "icpclnt2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\icpclnt2.exe"

!ELSE 

ALL : "$(OUTDIR)\icpclnt2.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\foricp.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\icpclnt2.exe"
	-@erase "$(OUTDIR)\icpclnt2.ilk"
	-@erase "$(OUTDIR)\icpclnt2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\include" /D "_DEBUG" /D\
 "WIN32" /D "_CONSOLE" /D "_MBCS" /D "SECURITY_WIN32"\
 /Fp"$(INTDIR)\icpclnt2.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\icpclnt2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\icpclnt2.pdb" /debug /machine:$(CPU)\
 /out:"$(OUTDIR)\icpclnt2.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\foricp.obj"

"$(OUTDIR)\icpclnt2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "icpclnt2 - Win32 Release" || "$(CFG)" ==\
 "icpclnt2 - Win32 Debug"
SOURCE=.\client.c

!IF  "$(CFG)" == "icpclnt2 - Win32 Release"

DEP_CPP_CLIEN=\
	".\client.h"\
	".\sampincl.h"\
	{$(INCLUDE)}"commdef.h"\
	{$(INCLUDE)}"issperr.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\client.obj" : $(SOURCE) $(DEP_CPP_CLIEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "icpclnt2 - Win32 Debug"

DEP_CPP_CLIEN=\
	"..\include\commdef.h"\
	".\client.h"\
	".\sampincl.h"\
	{$(INCLUDE)}"issperr.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\client.obj" : $(SOURCE) $(DEP_CPP_CLIEN) "$(INTDIR)"


!ENDIF 

SOURCE=.\foricp.c

!IF  "$(CFG)" == "icpclnt2 - Win32 Release"

DEP_CPP_FORIC=\
	".\client.h"\
	".\sampincl.h"\
	{$(INCLUDE)}"commdef.h"\
	{$(INCLUDE)}"issperr.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\foricp.obj" : $(SOURCE) $(DEP_CPP_FORIC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "icpclnt2 - Win32 Debug"

DEP_CPP_FORIC=\
	"..\include\commdef.h"\
	".\client.h"\
	".\sampincl.h"\
	{$(INCLUDE)}"issperr.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\foricp.obj" : $(SOURCE) $(DEP_CPP_FORIC) "$(INTDIR)"


!ENDIF 


!ENDIF 

