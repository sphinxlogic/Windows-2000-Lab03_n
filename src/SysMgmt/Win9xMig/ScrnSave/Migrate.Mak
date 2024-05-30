# Microsoft Developer Studio Generated NMAKE File, Based on migrate.dsp
!IF "$(CFG)" == ""
CFG=migrate - Win32 Debug
!MESSAGE No configuration specified. Defaulting to migrate - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "migrate - Win32 Release" && "$(CFG)" !=\
 "migrate - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "migrate.mak" CFG="migrate - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "migrate - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "migrate - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "migrate - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\migrate.dll"

!ELSE 

ALL : "$(OUTDIR)\migrate.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dataconv.obj"
	-@erase "$(INTDIR)\miginf.obj"
	-@erase "$(INTDIR)\poolmem.obj"
	-@erase "$(INTDIR)\savecfg.obj"
	-@erase "$(INTDIR)\scrnsave.obj"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\migrate.dll"
	-@erase "$(OUTDIR)\migrate.exp"
	-@erase "$(OUTDIR)\migrate.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\migrate.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\migrate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdi32.lib winspool.lib comdlg32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib nt5\setupapi.lib kernel32.lib\
 user32.lib advapi32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\migrate.pdb" /machine:I386 /def:".\migrate.def"\
 /out:"$(OUTDIR)\migrate.dll" /implib:"$(OUTDIR)\migrate.lib" 
DEF_FILE= \
	".\migrate.def"
LINK32_OBJS= \
	"$(INTDIR)\dataconv.obj" \
	"$(INTDIR)\miginf.obj" \
	"$(INTDIR)\poolmem.obj" \
	"$(INTDIR)\savecfg.obj" \
	"$(INTDIR)\scrnsave.obj" \
	"$(INTDIR)\utils.obj"

"$(OUTDIR)\migrate.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "migrate - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\migrate.dll"

!ELSE 

ALL : "$(OUTDIR)\migrate.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dataconv.obj"
	-@erase "$(INTDIR)\miginf.obj"
	-@erase "$(INTDIR)\poolmem.obj"
	-@erase "$(INTDIR)\savecfg.obj"
	-@erase "$(INTDIR)\scrnsave.obj"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\migrate.dll"
	-@erase "$(OUTDIR)\migrate.exp"
	-@erase "$(OUTDIR)\migrate.ilk"
	-@erase "$(OUTDIR)\migrate.lib"
	-@erase "$(OUTDIR)\migrate.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\migrate.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\migrate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=setupapi.lib kernel32.lib user32.lib advapi32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\migrate.pdb" /debug\
 /machine:I386 /def:".\migrate.def" /out:"$(OUTDIR)\migrate.dll"\
 /implib:"$(OUTDIR)\migrate.lib" /pdbtype:sept 
DEF_FILE= \
	".\migrate.def"
LINK32_OBJS= \
	"$(INTDIR)\dataconv.obj" \
	"$(INTDIR)\miginf.obj" \
	"$(INTDIR)\poolmem.obj" \
	"$(INTDIR)\savecfg.obj" \
	"$(INTDIR)\scrnsave.obj" \
	"$(INTDIR)\utils.obj"

"$(OUTDIR)\migrate.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "migrate - Win32 Release" || "$(CFG)" ==\
 "migrate - Win32 Debug"
SOURCE=.\dataconv.c
DEP_CPP_DATAC=\
	".\Miginf.h"\
	".\Pch.h"\
	".\Poolmem.h"\
	".\Scrnsave.h"\
	

"$(INTDIR)\dataconv.obj" : $(SOURCE) $(DEP_CPP_DATAC) "$(INTDIR)"


SOURCE=.\miginf.c
DEP_CPP_MIGIN=\
	".\Miginf.h"\
	".\Pch.h"\
	".\Poolmem.h"\
	".\Scrnsave.h"\
	

"$(INTDIR)\miginf.obj" : $(SOURCE) $(DEP_CPP_MIGIN) "$(INTDIR)"


SOURCE=.\poolmem.c
DEP_CPP_POOLM=\
	".\Miginf.h"\
	".\Pch.h"\
	".\Poolmem.h"\
	".\Scrnsave.h"\
	

"$(INTDIR)\poolmem.obj" : $(SOURCE) $(DEP_CPP_POOLM) "$(INTDIR)"


SOURCE=.\savecfg.c
DEP_CPP_SAVEC=\
	".\Miginf.h"\
	".\Pch.h"\
	".\Poolmem.h"\
	".\Scrnsave.h"\
	

"$(INTDIR)\savecfg.obj" : $(SOURCE) $(DEP_CPP_SAVEC) "$(INTDIR)"


SOURCE=.\scrnsave.c
DEP_CPP_SCRNS=\
	".\Miginf.h"\
	".\Pch.h"\
	".\Poolmem.h"\
	".\Scrnsave.h"\
	

"$(INTDIR)\scrnsave.obj" : $(SOURCE) $(DEP_CPP_SCRNS) "$(INTDIR)"


SOURCE=.\utils.c
DEP_CPP_UTILS=\
	".\Miginf.h"\
	".\Pch.h"\
	".\Poolmem.h"\
	".\Scrnsave.h"\
	

"$(INTDIR)\utils.obj" : $(SOURCE) $(DEP_CPP_UTILS) "$(INTDIR)"



!ENDIF 

