# Microsoft Developer Studio Generated NMAKE File, Based on avphone.dsp
!IF "$(CFG)" == ""
CFG=avphone - Win32 Debug
!MESSAGE No configuration specified. Defaulting to avphone - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "avphone - Win32 Release" && "$(CFG)" !=\
 "avphone - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "avphone.mak" CFG="avphone - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "avphone - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "avphone - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "avphone - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\avphone.exe"

!ELSE 

ALL : "$(OUTDIR)\avphone.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\callntfy.obj"
	-@erase "$(INTDIR)\clutil.obj"
	-@erase "$(INTDIR)\cnfntfy.obj"
	-@erase "$(INTDIR)\conf.obj"
	-@erase "$(INTDIR)\IMSCONF2.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.res"
	-@erase "$(INTDIR)\mgrntfy.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\avphone.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\avphone.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\main.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\avphone.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\avphone.pdb" /machine:I386 /out:"$(OUTDIR)\avphone.exe" 
LINK32_OBJS= \
	"$(INTDIR)\callntfy.obj" \
	"$(INTDIR)\clutil.obj" \
	"$(INTDIR)\cnfntfy.obj" \
	"$(INTDIR)\conf.obj" \
	"$(INTDIR)\IMSCONF2.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\main.res" \
	"$(INTDIR)\mgrntfy.obj"

"$(OUTDIR)\avphone.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\avphone.exe"

!ELSE 

ALL : "$(OUTDIR)\avphone.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\callntfy.obj"
	-@erase "$(INTDIR)\clutil.obj"
	-@erase "$(INTDIR)\cnfntfy.obj"
	-@erase "$(INTDIR)\conf.obj"
	-@erase "$(INTDIR)\IMSCONF2.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.res"
	-@erase "$(INTDIR)\mgrntfy.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\avphone.exe"
	-@erase "$(OUTDIR)\avphone.ilk"
	-@erase "$(OUTDIR)\avphone.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\avphone.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\main.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\avphone.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\avphone.pdb" /debug /machine:I386 /out:"$(OUTDIR)\avphone.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\callntfy.obj" \
	"$(INTDIR)\clutil.obj" \
	"$(INTDIR)\cnfntfy.obj" \
	"$(INTDIR)\conf.obj" \
	"$(INTDIR)\IMSCONF2.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\main.res" \
	"$(INTDIR)\mgrntfy.obj"

"$(OUTDIR)\avphone.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "avphone - Win32 Release" || "$(CFG)" ==\
 "avphone - Win32 Debug"
SOURCE=.\callntfy.cpp

!IF  "$(CFG)" == "avphone - Win32 Release"

DEP_CPP_CALLN=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\callntfy.obj" : $(SOURCE) $(DEP_CPP_CALLN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

DEP_CPP_CALLN=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\callntfy.obj" : $(SOURCE) $(DEP_CPP_CALLN) "$(INTDIR)"\
 ".\IMSCONF2.h"


!ENDIF 

SOURCE=.\clutil.cpp

!IF  "$(CFG)" == "avphone - Win32 Release"

DEP_CPP_CLUTI=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\clutil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

DEP_CPP_CLUTI=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\clutil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)" ".\IMSCONF2.h"


!ENDIF 

SOURCE=.\cnfntfy.cpp

!IF  "$(CFG)" == "avphone - Win32 Release"

DEP_CPP_CNFNT=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\cnfntfy.obj" : $(SOURCE) $(DEP_CPP_CNFNT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

DEP_CPP_CNFNT=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\cnfntfy.obj" : $(SOURCE) $(DEP_CPP_CNFNT) "$(INTDIR)" ".\IMSCONF2.h"


!ENDIF 

SOURCE=.\conf.cpp

!IF  "$(CFG)" == "avphone - Win32 Release"

DEP_CPP_CONF_=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\conf.obj" : $(SOURCE) $(DEP_CPP_CONF_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

DEP_CPP_CONF_=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\conf.obj" : $(SOURCE) $(DEP_CPP_CONF_) "$(INTDIR)" ".\IMSCONF2.h"


!ENDIF 

SOURCE=.\IMSCONF2.c

"$(INTDIR)\IMSCONF2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IMSCONF2.IDL

!IF  "$(CFG)" == "avphone - Win32 Release"

!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

TargetDir=.\Debug
InputPath=.\IMSCONF2.IDL
InputName=IMSCONF2

".\$(InputName).h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata\
  $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header\
  $(InputName).h /iid $(InputName).c $(InputPath)

!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "avphone - Win32 Release"

DEP_CPP_MAIN_=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

DEP_CPP_MAIN_=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)" ".\IMSCONF2.h"


!ENDIF 

SOURCE=.\main.rc

"$(INTDIR)\main.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\mgrntfy.cpp

!IF  "$(CFG)" == "avphone - Win32 Release"

DEP_CPP_MGRNT=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\mgrntfy.obj" : $(SOURCE) $(DEP_CPP_MGRNT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "avphone - Win32 Debug"

DEP_CPP_MGRNT=\
	".\callntfy.h"\
	".\clutil.h"\
	".\cnfntfy.h"\
	".\conf.h"\
	".\IMSCONF2.h"\
	".\mgrntfy.h"\
	".\precomp.h"\
	

"$(INTDIR)\mgrntfy.obj" : $(SOURCE) $(DEP_CPP_MGRNT) "$(INTDIR)" ".\IMSCONF2.h"


!ENDIF 


!ENDIF 

