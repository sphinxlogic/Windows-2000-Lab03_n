# Microsoft Developer Studio Generated NMAKE File, Based on SmbSmp.dsp
!IF "$(CFG)" == ""
CFG=SmbSmp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SmbSmp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SmbSmp - Win32 Release" && "$(CFG)" != "SmbSmp - Win32 Debug"\
 && "$(CFG)" != "SmbSmp - Win32 (ALPHA) Release" && "$(CFG)" !=\
 "SmbSmp - Win32 (ALPHA) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmbSmp.mak" CFG="SmbSmp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmbSmp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 (ALPHA) Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "SmbSmp - Win32 (ALPHA) Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ELSE 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Fp"$(INTDIR)\SmbSmp.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib netapi32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\SmbSmp.pdb" /machine:I386 /def:".\SmbSmp.def"\
 /out:"$(OUTDIR)\SmbSmp.dll" /implib:"$(OUTDIR)\SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ELSE 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.ilk"
	-@erase "$(OUTDIR)\SmbSmp.lib"
	-@erase "$(OUTDIR)\SmbSmp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib netapi32.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\SmbSmp.pdb" /debug /machine:I386\
 /def:".\SmbSmp.def" /out:"$(OUTDIR)\SmbSmp.dll" /implib:"$(OUTDIR)\SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

OUTDIR=.\AlphaRel
INTDIR=.\AlphaRel
# Begin Custom Macros
OutDir=.\.\AlphaRel
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ELSE 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib netapi32.lib /nologo /subsystem:windows /dll\
 /pdb:"$(OUTDIR)\SmbSmp.pdb" /machine:ALPHA /def:".\SmbSmp.def"\
 /out:"$(OUTDIR)\SmbSmp.dll" /implib:"$(OUTDIR)\SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

OUTDIR=.\AlphaDbg
INTDIR=.\AlphaDbg
# Begin Custom Macros
OutDir=.\.\AlphaDbg
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ELSE 

ALL : "$(OUTDIR)\SmbSmp.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.lib"
	-@erase "$(OUTDIR)\SmbSmp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL"\
 /Fp"$(INTDIR)\SmbSmp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /MDd /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib netapi32.lib /nologo /subsystem:windows /dll\
 /pdb:"$(OUTDIR)\SmbSmp.pdb" /debug /machine:ALPHA /def:".\SmbSmp.def"\
 /out:"$(OUTDIR)\SmbSmp.dll" /implib:"$(OUTDIR)\SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SmbSmp - Win32 Release" || "$(CFG)" == "SmbSmp - Win32 Debug"\
 || "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release" || "$(CFG)" ==\
 "SmbSmp - Win32 (ALPHA) Debug"
SOURCE=.\SmbSmp.cpp

!IF  "$(CFG)" == "SmbSmp - Win32 Release"

DEP_CPP_SMBSM=\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"

DEP_CPP_SMBSM=\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Release"

DEP_CPP_SMBSM=\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 (ALPHA) Debug"

DEP_CPP_SMBSM=\
	{$(INCLUDE)}"clusapi.h"\
	{$(INCLUDE)}"resapi.h"\
	

"$(INTDIR)\SmbSmp.obj" : $(SOURCE) $(DEP_CPP_SMBSM) "$(INTDIR)"


!ENDIF 

SOURCE=.\SmbSmp.rc

"$(INTDIR)\SmbSmp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

