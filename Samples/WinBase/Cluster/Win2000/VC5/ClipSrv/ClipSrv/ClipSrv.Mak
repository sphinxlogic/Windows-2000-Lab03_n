# Microsoft Developer Studio Generated NMAKE File, Based on ClipSrv.dsp
!IF "$(CFG)" == ""
CFG=ClipSrv - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ClipSrv - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ClipSrv - Win32 Release" && "$(CFG)" !=\
 "ClipSrv - Win32 Debug" && "$(CFG)" != "ClipSrv - Win32 (ALPHA) Release" &&\
 "$(CFG)" != "ClipSrv - Win32 (ALPHA) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClipSrv.mak" CFG="ClipSrv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClipSrv - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClipSrv - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClipSrv - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "ClipSrv - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ClipSrv - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ClipSrv.dll"

!ELSE 

ALL : "$(OUTDIR)\ClipSrv.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ClipSrv.obj"
	-@erase "$(INTDIR)\ClipSrv.res"
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ClipSrv.dll"
	-@erase "$(OUTDIR)\ClipSrv.exp"
	-@erase "$(OUTDIR)\ClipSrv.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\ClipSrv.pch"\
 /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrv.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\ClipSrv.pdb" /machine:I386 /def:".\ClipSrv.def"\
 /out:"$(OUTDIR)\ClipSrv.dll" /implib:"$(OUTDIR)\ClipSrv.lib" 
DEF_FILE= \
	".\ClipSrv.def"
LINK32_OBJS= \
	"$(INTDIR)\ClipSrv.obj" \
	"$(INTDIR)\ClipSrv.res" \
	"$(INTDIR)\ClRes.obj"

"$(OUTDIR)\ClipSrv.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ClipSrv.dll" "$(OUTDIR)\ClipSrv.bsc"

!ELSE 

ALL : "$(OUTDIR)\ClipSrv.dll" "$(OUTDIR)\ClipSrv.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ClipSrv.obj"
	-@erase "$(INTDIR)\ClipSrv.res"
	-@erase "$(INTDIR)\ClipSrv.sbr"
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\ClRes.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ClipSrv.bsc"
	-@erase "$(OUTDIR)\ClipSrv.dll"
	-@erase "$(OUTDIR)\ClipSrv.exp"
	-@erase "$(OUTDIR)\ClipSrv.ilk"
	-@erase "$(OUTDIR)\ClipSrv.lib"
	-@erase "$(OUTDIR)\ClipSrv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ClipSrv.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrv.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrv.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClipSrv.sbr" \
	"$(INTDIR)\ClRes.sbr"

"$(OUTDIR)\ClipSrv.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\ClipSrv.pdb" /debug /machine:I386 /def:".\ClipSrv.def"\
 /out:"$(OUTDIR)\ClipSrv.dll" /implib:"$(OUTDIR)\ClipSrv.lib" 
DEF_FILE= \
	".\ClipSrv.def"
LINK32_OBJS= \
	"$(INTDIR)\ClipSrv.obj" \
	"$(INTDIR)\ClipSrv.res" \
	"$(INTDIR)\ClRes.obj"

"$(OUTDIR)\ClipSrv.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrv - Win32 (ALPHA) Release"

OUTDIR=.\AlphaRel
INTDIR=.\AlphaRel
# Begin Custom Macros
OutDir=.\.\AlphaRel
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ClipSrv.dll"

!ELSE 

ALL : "$(OUTDIR)\ClipSrv.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ClipSrv.obj"
	-@erase "$(INTDIR)\ClipSrv.res"
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ClipSrv.dll"
	-@erase "$(OUTDIR)\ClipSrv.exp"
	-@erase "$(OUTDIR)\ClipSrv.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\ClipSrv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\AlphaRel/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrv.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\ClipSrv.pdb"\
 /machine:ALPHA /def:".\ClipSrv.def" /out:"$(OUTDIR)\ClipSrv.dll"\
 /implib:"$(OUTDIR)\ClipSrv.lib" 
DEF_FILE= \
	".\ClipSrv.def"
LINK32_OBJS= \
	"$(INTDIR)\ClipSrv.obj" \
	"$(INTDIR)\ClipSrv.res" \
	"$(INTDIR)\ClRes.obj"

"$(OUTDIR)\ClipSrv.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrv - Win32 (ALPHA) Debug"

OUTDIR=.\AlphaDbg
INTDIR=.\AlphaDbg
# Begin Custom Macros
OutDir=.\.\AlphaDbg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ClipSrv.dll"

!ELSE 

ALL : "$(OUTDIR)\ClipSrv.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ClipSrv.obj"
	-@erase "$(INTDIR)\ClipSrv.res"
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ClipSrv.dll"
	-@erase "$(OUTDIR)\ClipSrv.exp"
	-@erase "$(OUTDIR)\ClipSrv.lib"
	-@erase "$(OUTDIR)\ClipSrv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\ClipSrv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /MDd /c 
CPP_OBJS=.\AlphaDbg/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrv.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ClipSrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\ClipSrv.pdb"\
 /debug /machine:ALPHA /def:".\ClipSrv.def" /out:"$(OUTDIR)\ClipSrv.dll"\
 /implib:"$(OUTDIR)\ClipSrv.lib" 
DEF_FILE= \
	".\ClipSrv.def"
LINK32_OBJS= \
	"$(INTDIR)\ClipSrv.obj" \
	"$(INTDIR)\ClipSrv.res" \
	"$(INTDIR)\ClRes.obj"

"$(OUTDIR)\ClipSrv.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "ClipSrv - Win32 Release" || "$(CFG)" ==\
 "ClipSrv - Win32 Debug" || "$(CFG)" == "ClipSrv - Win32 (ALPHA) Release" ||\
 "$(CFG)" == "ClipSrv - Win32 (ALPHA) Debug"
SOURCE=.\ClipSrv.cpp

!IF  "$(CFG)" == "ClipSrv - Win32 Release"

DEP_CPP_CLIPS=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClipSrv.obj" : $(SOURCE) $(DEP_CPP_CLIPS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ClipSrv - Win32 Debug"

DEP_CPP_CLIPS=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClipSrv.obj"	"$(INTDIR)\ClipSrv.sbr" : $(SOURCE) $(DEP_CPP_CLIPS)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ClipSrv - Win32 (ALPHA) Release"

DEP_CPP_CLIPS=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClipSrv.obj" : $(SOURCE) $(DEP_CPP_CLIPS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ClipSrv - Win32 (ALPHA) Debug"

DEP_CPP_CLIPS=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClipSrv.obj" : $(SOURCE) $(DEP_CPP_CLIPS) "$(INTDIR)"


!ENDIF 

SOURCE=.\ClipSrv.rc

"$(INTDIR)\ClipSrv.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ClRes.cpp

!IF  "$(CFG)" == "ClipSrv - Win32 Release"

DEP_CPP_CLRES=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClRes.obj" : $(SOURCE) $(DEP_CPP_CLRES) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ClipSrv - Win32 Debug"

DEP_CPP_CLRES=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClRes.obj"	"$(INTDIR)\ClRes.sbr" : $(SOURCE) $(DEP_CPP_CLRES)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ClipSrv - Win32 (ALPHA) Release"

DEP_CPP_CLRES=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClRes.obj" : $(SOURCE) $(DEP_CPP_CLRES) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ClipSrv - Win32 (ALPHA) Debug"

DEP_CPP_CLRES=\
	".\ClRes.h"\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\ClRes.obj" : $(SOURCE) $(DEP_CPP_CLRES) "$(INTDIR)"


!ENDIF 


!ENDIF 

