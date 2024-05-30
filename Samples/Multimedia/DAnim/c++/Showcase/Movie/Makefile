# Microsoft Developer Studio Generated NMAKE File, Based on Movie.dsp
!IF "$(CFG)" == ""
CFG=Movie - Win32 Release
!MESSAGE No configuration specified. Defaulting to Movie - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Movie - Win32 Release" && "$(CFG)" != "Movie - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Movie.mak" CFG="Movie - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Movie - Win32 Release" (based on "Win32 Application")
!MESSAGE "Movie - Win32 Debug" (based on "Win32 Application")
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

!IF  "$(CFG)" == "Movie - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Movie.exe"

!ELSE 

ALL : "$(OUTDIR)\Movie.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\movie.obj"
	-@erase "$(INTDIR)\movie.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Movie.exe"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Movie.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\movie.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Movie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=daguid.lib danim.lib guids.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\Movie.pdb" /out:"$(OUTDIR)\Movie.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dxa.obj" \
	"$(INTDIR)\movie.obj" \
	"$(INTDIR)\movie.res"

"$(OUTDIR)\Movie.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Movie - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Movie.exe"

!ELSE 

ALL : "$(OUTDIR)\Movie.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dxa.obj"
	-@erase "$(INTDIR)\movie.obj"
	-@erase "$(INTDIR)\movie.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Movie.exe"
	-@erase "$(OUTDIR)\Movie.ilk"
	-@erase "$(OUTDIR)\Movie.pdb"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Movie.pch" /YX /FD /c 
CPP_OBJS=.
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\movie.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Movie.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=daguid.lib danim.lib guids.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\Movie.pdb" /debug /out:"$(OUTDIR)\Movie.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dxa.obj" \
	"$(INTDIR)\movie.obj" \
	"$(INTDIR)\movie.res"

"$(OUTDIR)\Movie.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "Movie - Win32 Release" || "$(CFG)" == "Movie - Win32 Debug"
SOURCE=.\dxa.cpp

!IF  "$(CFG)" == "Movie - Win32 Release"

DEP_CPP_DXA_C=\
	".\dxa.h"\
	{$(INCLUDE)}"danim.h"\
	

"$(INTDIR)\dxa.obj" : $(SOURCE) $(DEP_CPP_DXA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Movie - Win32 Debug"

DEP_CPP_DXA_C=\
	".\dxa.h"\
	{$(INCLUDE)}"danim.h"\

"$(INTDIR)\dxa.obj" : $(SOURCE) $(DEP_CPP_DXA_C) "$(INTDIR)"


!ENDIF 

SOURCE=.\movie.cpp

!IF  "$(CFG)" == "Movie - Win32 Release"

DEP_CPP_MOVIE=\
	".\dxa.h"\
	{$(INCLUDE)}"danim.h"\
	{$(INCLUDE)}"ddrawex.h"\
	

"$(INTDIR)\movie.obj" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Movie - Win32 Debug"

DEP_CPP_MOVIE=\
	".\dxa.h"\
	{$(INCLUDE)}"danim.h"\
	{$(INCLUDE)}"ddrawex.h"\
	

"$(INTDIR)\movie.obj" : $(SOURCE) $(DEP_CPP_MOVIE) "$(INTDIR)"


!ENDIF 

SOURCE=.\movie.rc
DEP_RSC_MOVIE_=\
	".\dxm.ico"\
	

"$(INTDIR)\movie.res" : $(SOURCE) $(DEP_RSC_MOVIE_) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

