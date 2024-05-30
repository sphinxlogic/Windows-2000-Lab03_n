# Microsoft Developer Studio Generated NMAKE File, Based on nmft.dsp
!IF "$(CFG)" == ""
CFG=nmFt - Win32 Debug
!MESSAGE No configuration specified. Defaulting to nmFt - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "nmFt - Win32 Release" && "$(CFG)" != "nmFt - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nmft.mak" CFG="nmFt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nmFt - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nmFt - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "nmFt - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\nmft.exe"

!ELSE 

ALL : "$(OUTDIR)\nmft.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\nmft.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /WX /O1 /Ob2 /D "NDEBUG" /D "STRICT" /D "WIN32" /D\
 "_WINDOWS" /Fp"$(INTDIR)\nmft.pch" /YX"precomp.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmft.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /entry:"main" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\nmft.pdb"\
 /machine:I386 /out:"$(OUTDIR)\nmft.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\nmft.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\nmft.exe"

!ELSE 

ALL : "$(OUTDIR)\nmft.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\nmft.exe"
	-@erase "$(OUTDIR)\nmft.ilk"
	-@erase "$(OUTDIR)\nmft.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "DEBUG" /D "_DEBUG" /D "STRICT" /D\
 "WIN32" /D "_WINDOWS" /Fp"$(INTDIR)\nmft.pch" /YX"precomp.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmft.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\nmft.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\nmft.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\nmft.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "nmFt - Win32 Release" || "$(CFG)" == "nmFt - Win32 Debug"
SOURCE=.\cConf.cpp

!IF  "$(CFG)" == "nmFt - Win32 Release"

DEP_CPP_CCONF=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cConf.obj" : $(SOURCE) $(DEP_CPP_CCONF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

DEP_CPP_CCONF=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cConf.obj" : $(SOURCE) $(DEP_CPP_CCONF) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\clUtil.cpp

!IF  "$(CFG)" == "nmFt - Win32 Release"

DEP_CPP_CLUTI=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\clUtil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

DEP_CPP_CLUTI=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\clUtil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\debug.cpp

!IF  "$(CFG)" == "nmFt - Win32 Release"

DEP_CPP_DEBUG=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

DEP_CPP_DEBUG=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\imsconf2.c

"$(INTDIR)\imsconf2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IMSCONF2.IDL

!IF  "$(CFG)" == "nmFt - Win32 Release"

!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

TargetDir=.\Debug
InputPath=.\IMSCONF2.IDL
InputName=IMSCONF2

".\$(InputName).h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata\
 $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header\
 $(InputName).h /iid $(InputName).c $(InputPath)

!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "nmFt - Win32 Release"

DEP_CPP_MAIN_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

DEP_CPP_MAIN_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\msg.cpp

!IF  "$(CFG)" == "nmFt - Win32 Release"

DEP_CPP_MSG_C=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

DEP_CPP_MSG_C=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\res.rc
DEP_RSC_RES_R=\
	".\main.ico"\
	

"$(INTDIR)\res.res" : $(SOURCE) $(DEP_RSC_RES_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\util.cpp

!IF  "$(CFG)" == "nmFt - Win32 Release"

DEP_CPP_UTIL_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

DEP_CPP_UTIL_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 


!ENDIF 

