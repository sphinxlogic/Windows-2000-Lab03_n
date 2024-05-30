# Microsoft Developer Studio Generated NMAKE File, Based on instcodc.dsp
!IF "$(CFG)" == ""
CFG=instcodc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to instcodc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "instcodc - Win32 Release" && "$(CFG)" !=\
 "instcodc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "instcodc.mak" CFG="instcodc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "instcodc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "instcodc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "instcodc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\instcodc.exe"

!ELSE 

ALL : "$(OUTDIR)\instcodc.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\INSTCODC.OBJ"
	-@erase "$(INTDIR)\instcodc.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\instcodc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\instcodc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\instcodc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\instcodc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\instcodc.pdb" /machine:I386 /out:"$(OUTDIR)\instcodc.exe" 
LINK32_OBJS= \
	"$(INTDIR)\INSTCODC.OBJ" \
	"$(INTDIR)\instcodc.res"

"$(OUTDIR)\instcodc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "instcodc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\instcodc.exe"

!ELSE 

ALL : "$(OUTDIR)\instcodc.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\INSTCODC.OBJ"
	-@erase "$(INTDIR)\instcodc.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\instcodc.exe"
	-@erase "$(OUTDIR)\instcodc.ilk"
	-@erase "$(OUTDIR)\instcodc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\instcodc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\instcodc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\instcodc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\instcodc.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\instcodc.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\INSTCODC.OBJ" \
	"$(INTDIR)\instcodc.res"

"$(OUTDIR)\instcodc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "instcodc - Win32 Release" || "$(CFG)" ==\
 "instcodc - Win32 Debug"
SOURCE=.\INSTCODC.CPP
DEP_CPP_INSTC=\
	{$(INCLUDE)}"appavcap.h"\
	{$(INCLUDE)}"codecs.h"\
	

"$(INTDIR)\INSTCODC.OBJ" : $(SOURCE) $(DEP_CPP_INSTC) "$(INTDIR)"


SOURCE=.\instcodc.rc
DEP_RSC_INSTCO=\
	".\instcodc.ico"\
	

"$(INTDIR)\instcodc.res" : $(SOURCE) $(DEP_RSC_INSTCO) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

