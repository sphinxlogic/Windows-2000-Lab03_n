# Microsoft Developer Studio Generated NMAKE File, Based on skippy.dsp
!IF "$(CFG)" == ""
CFG=skippy - Win32 Release
!MESSAGE No configuration specified. Defaulting to skippy - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "skippy - Win32 Release" && "$(CFG)" != "skippy - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "skippy.mak" CFG="skippy - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "skippy - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "skippy - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "skippy - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\skippy.exe"

!ELSE 

ALL : "$(OUTDIR)\skippy.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\attrib.obj"
	-@erase "$(INTDIR)\filter.obj"
	-@erase "$(INTDIR)\ils.obj"
	-@erase "$(INTDIR)\MAIN.OBJ"
	-@erase "$(INTDIR)\notify.obj"
	-@erase "$(INTDIR)\oblist.obj"
	-@erase "$(INTDIR)\proto.obj"
	-@erase "$(INTDIR)\skippy.res"
	-@erase "$(INTDIR)\svrinfo.obj"
	-@erase "$(INTDIR)\USERS.OBJ"
	-@erase "$(INTDIR)\usrinfo.obj"
	-@erase "$(INTDIR)\UTILS.OBJ"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\skippy.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\skippy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\skippy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\skippy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\skippy.pdb" /machine:I386 /out:"$(OUTDIR)\skippy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\attrib.obj" \
	"$(INTDIR)\filter.obj" \
	"$(INTDIR)\ils.obj" \
	"$(INTDIR)\MAIN.OBJ" \
	"$(INTDIR)\notify.obj" \
	"$(INTDIR)\oblist.obj" \
	"$(INTDIR)\proto.obj" \
	"$(INTDIR)\skippy.res" \
	"$(INTDIR)\svrinfo.obj" \
	"$(INTDIR)\USERS.OBJ" \
	"$(INTDIR)\usrinfo.obj" \
	"$(INTDIR)\UTILS.OBJ"

"$(OUTDIR)\skippy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

OUTDIR=.\debug
INTDIR=.\debug
# Begin Custom Macros
OutDir=.\.\debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\skippy.exe" "$(OUTDIR)\skippy.bsc"

!ELSE 

ALL : "$(OUTDIR)\skippy.exe" "$(OUTDIR)\skippy.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\attrib.obj"
	-@erase "$(INTDIR)\attrib.sbr"
	-@erase "$(INTDIR)\filter.obj"
	-@erase "$(INTDIR)\filter.sbr"
	-@erase "$(INTDIR)\ils.obj"
	-@erase "$(INTDIR)\ils.sbr"
	-@erase "$(INTDIR)\MAIN.OBJ"
	-@erase "$(INTDIR)\MAIN.SBR"
	-@erase "$(INTDIR)\notify.obj"
	-@erase "$(INTDIR)\notify.sbr"
	-@erase "$(INTDIR)\oblist.obj"
	-@erase "$(INTDIR)\oblist.sbr"
	-@erase "$(INTDIR)\proto.obj"
	-@erase "$(INTDIR)\proto.sbr"
	-@erase "$(INTDIR)\skippy.res"
	-@erase "$(INTDIR)\svrinfo.obj"
	-@erase "$(INTDIR)\svrinfo.sbr"
	-@erase "$(INTDIR)\USERS.OBJ"
	-@erase "$(INTDIR)\USERS.SBR"
	-@erase "$(INTDIR)\usrinfo.obj"
	-@erase "$(INTDIR)\usrinfo.sbr"
	-@erase "$(INTDIR)\UTILS.OBJ"
	-@erase "$(INTDIR)\UTILS.SBR"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\skippy.bsc"
	-@erase "$(OUTDIR)\skippy.exe"
	-@erase "$(OUTDIR)\skippy.ilk"
	-@erase "$(OUTDIR)\skippy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\skippy.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\debug/
CPP_SBRS=.\debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\skippy.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\skippy.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\attrib.sbr" \
	"$(INTDIR)\filter.sbr" \
	"$(INTDIR)\ils.sbr" \
	"$(INTDIR)\MAIN.SBR" \
	"$(INTDIR)\notify.sbr" \
	"$(INTDIR)\oblist.sbr" \
	"$(INTDIR)\proto.sbr" \
	"$(INTDIR)\svrinfo.sbr" \
	"$(INTDIR)\USERS.SBR" \
	"$(INTDIR)\usrinfo.sbr" \
	"$(INTDIR)\UTILS.SBR"

"$(OUTDIR)\skippy.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\skippy.pdb" /debug /machine:I386 /out:"$(OUTDIR)\skippy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\attrib.obj" \
	"$(INTDIR)\filter.obj" \
	"$(INTDIR)\ils.obj" \
	"$(INTDIR)\MAIN.OBJ" \
	"$(INTDIR)\notify.obj" \
	"$(INTDIR)\oblist.obj" \
	"$(INTDIR)\proto.obj" \
	"$(INTDIR)\skippy.res" \
	"$(INTDIR)\svrinfo.obj" \
	"$(INTDIR)\USERS.OBJ" \
	"$(INTDIR)\usrinfo.obj" \
	"$(INTDIR)\UTILS.OBJ"

"$(OUTDIR)\skippy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "skippy - Win32 Release" || "$(CFG)" == "skippy - Win32 Debug"
SOURCE=.\attrib.cpp

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_ATTRI=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\attrib.obj" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_ATTRI=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\attrib.obj"	"$(INTDIR)\attrib.sbr" : $(SOURCE) $(DEP_CPP_ATTRI)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\filter.cpp

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_FILTE=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\filter.obj" : $(SOURCE) $(DEP_CPP_FILTE) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_FILTE=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\filter.obj"	"$(INTDIR)\filter.sbr" : $(SOURCE) $(DEP_CPP_FILTE)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\ils.c

!IF  "$(CFG)" == "skippy - Win32 Release"


"$(INTDIR)\ils.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"


"$(INTDIR)\ils.obj"	"$(INTDIR)\ils.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MAIN.CPP

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_MAIN_=\
	"..\..\include\ilsguid.h"\
	".\appguid.h"\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\MAIN.OBJ" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_MAIN_=\
	"..\..\include\ilsguid.h"\
	".\appguid.h"\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\MAIN.OBJ"	"$(INTDIR)\MAIN.SBR" : $(SOURCE) $(DEP_CPP_MAIN_)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\notify.cpp

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_NOTIF=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\notify.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_NOTIF=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\notify.obj"	"$(INTDIR)\notify.sbr" : $(SOURCE) $(DEP_CPP_NOTIF)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\oblist.cpp
DEP_CPP_OBLIS=\
	".\oblist.h"\
	

!IF  "$(CFG)" == "skippy - Win32 Release"


"$(INTDIR)\oblist.obj" : $(SOURCE) $(DEP_CPP_OBLIS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"


"$(INTDIR)\oblist.obj"	"$(INTDIR)\oblist.sbr" : $(SOURCE) $(DEP_CPP_OBLIS)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\proto.cpp

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_PROTO=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\proto.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_PROTO=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\proto.obj"	"$(INTDIR)\proto.sbr" : $(SOURCE) $(DEP_CPP_PROTO)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\skippy.rc
DEP_RSC_SKIPP=\
	".\face.ico"\
	".\resource.hm"\
	

"$(INTDIR)\skippy.res" : $(SOURCE) $(DEP_RSC_SKIPP) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\svrinfo.cpp

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_SVRIN=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\svrinfo.obj" : $(SOURCE) $(DEP_CPP_SVRIN) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_SVRIN=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\svrinfo.obj"	"$(INTDIR)\svrinfo.sbr" : $(SOURCE) $(DEP_CPP_SVRIN)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\USERS.CPP

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_USERS=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\USERS.OBJ" : $(SOURCE) $(DEP_CPP_USERS) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_USERS=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\USERS.OBJ"	"$(INTDIR)\USERS.SBR" : $(SOURCE) $(DEP_CPP_USERS)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\usrinfo.cpp

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_USRIN=\
	".\appguid.h"\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\usrinfo.obj" : $(SOURCE) $(DEP_CPP_USRIN) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_USRIN=\
	".\appguid.h"\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\usrinfo.obj"	"$(INTDIR)\usrinfo.sbr" : $(SOURCE) $(DEP_CPP_USRIN)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\UTILS.CPP

!IF  "$(CFG)" == "skippy - Win32 Release"

DEP_CPP_UTILS=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\UTILS.OBJ" : $(SOURCE) $(DEP_CPP_UTILS) "$(INTDIR)" ".\ils.h"


!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

DEP_CPP_UTILS=\
	".\ils.h"\
	".\ilstest.h"\
	".\notify.h"\
	".\oblist.h"\
	

"$(INTDIR)\UTILS.OBJ"	"$(INTDIR)\UTILS.SBR" : $(SOURCE) $(DEP_CPP_UTILS)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\ILS.IDL

!IF  "$(CFG)" == "skippy - Win32 Release"

TargetDir=.\Release
InputPath=.\ILS.IDL
InputName=ILS

".\$(InputName).h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata\
 $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header\
 $(InputName).h /iid $(InputName).c $(InputPath)

!ELSEIF  "$(CFG)" == "skippy - Win32 Debug"

!ENDIF 


!ENDIF 

