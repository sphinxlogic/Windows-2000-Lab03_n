# Microsoft Developer Studio Generated NMAKE File, Based on spruuids.dsp
!IF "$(CFG)" == ""
CFG=Spruuids - Win32 Release
!MESSAGE No configuration specified. Defaulting to Spruuids - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Spruuids - Win32 Release" && "$(CFG)" != "Spruuids - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "spruuids.mak" CFG="Spruuids - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Spruuids - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Spruuids - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Spruuids - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\spruuids.exe" "$(OUTDIR)\spruuids.tlb" ".\Spruuids.h"


CLEAN :
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\GameOA.obj"
	-@erase "$(INTDIR)\Guids.obj"
	-@erase "$(INTDIR)\MsgLoop.obj"
	-@erase "$(INTDIR)\OleAuto.obj"
	-@erase "$(INTDIR)\Score.obj"
	-@erase "$(INTDIR)\Spr.obj"
	-@erase "$(INTDIR)\SprOA.obj"
	-@erase "$(INTDIR)\spruuids.res"
	-@erase "$(INTDIR)\spruuids.tlb"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\spruuids.exe"
	-@erase ".\Spruuids.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".\inc_ext" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\spruuids.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\spruuids.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\spruuids.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\spruuids.pdb" /machine:I386 /out:"$(OUTDIR)\spruuids.exe" 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\GameOA.obj" \
	"$(INTDIR)\Guids.obj" \
	"$(INTDIR)\MsgLoop.obj" \
	"$(INTDIR)\OleAuto.obj" \
	"$(INTDIR)\Score.obj" \
	"$(INTDIR)\Spr.obj" \
	"$(INTDIR)\SprOA.obj" \
	"$(INTDIR)\spruuids.res"

"$(OUTDIR)\spruuids.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\spruuids.exe" "$(OUTDIR)\spruuids.bsc"


CLEAN :
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\App.sbr"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Game.sbr"
	-@erase "$(INTDIR)\GameOA.obj"
	-@erase "$(INTDIR)\GameOA.sbr"
	-@erase "$(INTDIR)\Guids.obj"
	-@erase "$(INTDIR)\Guids.sbr"
	-@erase "$(INTDIR)\MsgLoop.obj"
	-@erase "$(INTDIR)\MsgLoop.sbr"
	-@erase "$(INTDIR)\OleAuto.obj"
	-@erase "$(INTDIR)\OleAuto.sbr"
	-@erase "$(INTDIR)\Score.obj"
	-@erase "$(INTDIR)\Score.sbr"
	-@erase "$(INTDIR)\Spr.obj"
	-@erase "$(INTDIR)\Spr.sbr"
	-@erase "$(INTDIR)\SprOA.obj"
	-@erase "$(INTDIR)\SprOA.sbr"
	-@erase "$(INTDIR)\spruuids.res"
	-@erase "$(INTDIR)\spruuids.tlb"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\spruuids.bsc"
	-@erase "$(OUTDIR)\spruuids.exe"
	-@erase "$(OUTDIR)\spruuids.ilk"
	-@erase "$(OUTDIR)\spruuids.pdb"
	-@erase ".\Spruuids.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I ".\inc_ext" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\spruuids.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\spruuids.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\spruuids.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\App.sbr" \
	"$(INTDIR)\Game.sbr" \
	"$(INTDIR)\GameOA.sbr" \
	"$(INTDIR)\Guids.sbr" \
	"$(INTDIR)\MsgLoop.sbr" \
	"$(INTDIR)\OleAuto.sbr" \
	"$(INTDIR)\Score.sbr" \
	"$(INTDIR)\Spr.sbr" \
	"$(INTDIR)\SprOA.sbr"

"$(OUTDIR)\spruuids.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\spruuids.pdb" /debug /machine:I386 /out:"$(OUTDIR)\spruuids.exe" 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\GameOA.obj" \
	"$(INTDIR)\Guids.obj" \
	"$(INTDIR)\MsgLoop.obj" \
	"$(INTDIR)\OleAuto.obj" \
	"$(INTDIR)\Score.obj" \
	"$(INTDIR)\Spr.obj" \
	"$(INTDIR)\SprOA.obj" \
	"$(INTDIR)\spruuids.res"

"$(OUTDIR)\spruuids.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("spruuids.dep")
!INCLUDE "spruuids.dep"
!ELSE 
!MESSAGE Warning: cannot find "spruuids.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Spruuids - Win32 Release" || "$(CFG)" == "Spruuids - Win32 Debug"
SOURCE=.\App.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\App.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\App.obj"	"$(INTDIR)\App.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\Game.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Game.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Game.obj"	"$(INTDIR)\Game.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\GameOA.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\GameOA.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\GameOA.obj"	"$(INTDIR)\GameOA.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\Guids.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Guids.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Guids.obj"	"$(INTDIR)\Guids.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\MsgLoop.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\MsgLoop.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\MsgLoop.obj"	"$(INTDIR)\MsgLoop.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\OleAuto.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\OleAuto.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\OleAuto.obj"	"$(INTDIR)\OleAuto.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\Score.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Score.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Score.obj"	"$(INTDIR)\Score.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\Spr.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\Spr.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\Spr.obj"	"$(INTDIR)\Spr.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\SprOA.cpp

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\SprOA.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\SprOA.obj"	"$(INTDIR)\SprOA.sbr" : $(SOURCE) "$(INTDIR)" ".\Spruuids.h"


!ENDIF 

SOURCE=.\spruuids.odl

!IF  "$(CFG)" == "Spruuids - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\spruuids.tlb" /h ".\Spruuids.h" /mktyplib203 /win32 

"$(OUTDIR)\spruuids.tlb"	".\Spruuids.h" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\spruuids.tlb" /h ".\Spruuids.h" /mktyplib203 /win32 

"$(OUTDIR)\spruuids.tlb"	".\Spruuids.h" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\spruuids.rc

!IF  "$(CFG)" == "Spruuids - Win32 Release"


"$(INTDIR)\spruuids.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\spruuids.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\spruuids.res" /i ".\Release" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Spruuids - Win32 Debug"


"$(INTDIR)\spruuids.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\spruuids.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\spruuids.res" /i ".\Debug" /d "_DEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

