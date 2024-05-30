# Microsoft Developer Studio Generated NMAKE File, Based on SiteBoun.dsp
!IF "$(CFG)" == ""
CFG=SiteBoun - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SiteBoun - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SiteBoun - Win32 Release" && "$(CFG)" !=\
 "SiteBoun - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SiteBoun.mak" CFG="SiteBoun - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SiteBoun - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "SiteBoun - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SiteBoun - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SiteBoun.exe"

!ELSE 

ALL : "$(OUTDIR)\SiteBoun.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\siteboun.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\wbemsec.obj"
	-@erase "$(OUTDIR)\SiteBoun.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SiteBoun.pch" /YX /Fo"$(INTDIR)\\"\
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SiteBoun.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\SiteBoun.pdb" /machine:I386 /out:"$(OUTDIR)\SiteBoun.exe" 
LINK32_OBJS= \
	"$(INTDIR)\siteboun.obj" \
	"$(INTDIR)\wbemsec.obj"

"$(OUTDIR)\SiteBoun.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SiteBoun - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SiteBoun.exe"

!ELSE 

ALL : "$(OUTDIR)\SiteBoun.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\siteboun.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\wbemsec.obj"
	-@erase "$(OUTDIR)\SiteBoun.exe"
	-@erase "$(OUTDIR)\SiteBoun.ilk"
	-@erase "$(OUTDIR)\SiteBoun.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\include" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SiteBoun.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SiteBoun.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\SiteBoun.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SiteBoun.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\siteboun.obj" \
	"$(INTDIR)\wbemsec.obj"

"$(OUTDIR)\SiteBoun.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SiteBoun - Win32 Release" || "$(CFG)" ==\
 "SiteBoun - Win32 Debug"
SOURCE=.\siteboun.cpp

!IF  "$(CFG)" == "SiteBoun - Win32 Release"

DEP_CPP_SITEB=\
	

"$(INTDIR)\siteboun.obj" : $(SOURCE) $(DEP_CPP_SITEB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SiteBoun - Win32 Debug"

DEP_CPP_SITEB=\
	

"$(INTDIR)\siteboun.obj" : $(SOURCE) $(DEP_CPP_SITEB) "$(INTDIR)"


!ENDIF 

SOURCE=..\utility\wbemsec.CPP
DEP_CPP_WBEMS=\

"$(INTDIR)\wbemsec.obj" : $(SOURCE) $(DEP_CPP_WBEMS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

