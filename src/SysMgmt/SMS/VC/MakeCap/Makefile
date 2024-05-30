# Microsoft Developer Studio Generated NMAKE File, Based on MakeCap.dsp
!IF "$(CFG)" == ""
CFG=MakeCap - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MakeCap - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MakeCap - Win32 Release" && "$(CFG)" !=\
 "MakeCap - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MakeCap.mak" CFG="MakeCap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MakeCap - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "MakeCap - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MakeCap - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MakeCap.exe"

!ELSE 

ALL : "$(OUTDIR)\MakeCap.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\makecap.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\wbemsec.obj"
	-@erase "$(OUTDIR)\MakeCap.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\MakeCap.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MakeCap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\MakeCap.pdb" /machine:I386 /out:"$(OUTDIR)\MakeCap.exe" 
LINK32_OBJS= \
	"$(INTDIR)\makecap.obj" \
	"$(INTDIR)\wbemsec.obj"

"$(OUTDIR)\MakeCap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MakeCap - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MakeCap.exe"

!ELSE 

ALL : "$(OUTDIR)\MakeCap.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\makecap.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\wbemsec.obj"
	-@erase "$(OUTDIR)\MakeCap.exe"
	-@erase "$(OUTDIR)\MakeCap.ilk"
	-@erase "$(OUTDIR)\MakeCap.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\include" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\MakeCap.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MakeCap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\MakeCap.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MakeCap.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\makecap.obj" \
	"$(INTDIR)\wbemsec.obj"

"$(OUTDIR)\MakeCap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(CFG)" == "MakeCap - Win32 Release" || "$(CFG)" ==\
 "MakeCap - Win32 Debug"
SOURCE=.\makecap.cpp

!IF  "$(CFG)" == "MakeCap - Win32 Release"

DEP_CPP_MAKEC=\
	

"$(INTDIR)\makecap.obj" : $(SOURCE) $(DEP_CPP_MAKEC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MakeCap - Win32 Debug"

DEP_CPP_MAKEC=\
	

"$(INTDIR)\makecap.obj" : $(SOURCE) $(DEP_CPP_MAKEC) "$(INTDIR)"


!ENDIF 

SOURCE=..\utility\wbemsec.CPP
DEP_CPP_WBEMS=\

"$(INTDIR)\wbemsec.obj" : $(SOURCE) $(DEP_CPP_WBEMS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

