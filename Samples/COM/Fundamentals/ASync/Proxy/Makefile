# Microsoft Developer Studio Generated NMAKE File, Based on proxy.dsp
!IF "$(CFG)" == ""
CFG=proxy - Win32 Debug
!MESSAGE No configuration specified. Defaulting to proxy - Win32 Debug.
!ENDIF 

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF

!IF "$(CFG)" != "proxy - Win32 Release" && "$(CFG)" != "proxy - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "proxy.mak" CFG="proxy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "proxy - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "proxy - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "proxy - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\proxy.dll" "$(OUTDIR)\Proxy.tlb"


CLEAN :
	-@erase "$(INTDIR)\Async_p.obj"
	-@erase "$(INTDIR)\AsyncTest1_i.obj"
	-@erase "$(INTDIR)\DllData.obj"
	-@erase "$(INTDIR)\Proxy.tlb"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\proxy.dll"
	-@erase "$(OUTDIR)\proxy.exp"
	-@erase "$(OUTDIR)\proxy.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D _WIN32_WINNT=0X500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\proxy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\proxy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\proxy.pdb" /machine:$(mach_type) /def:".\proxy.def" /out:"$(OUTDIR)\proxy.dll" /implib:"$(OUTDIR)\proxy.lib" 
DEF_FILE= \
	".\proxy.def"
LINK32_OBJS= \
	"$(INTDIR)\Async_p.obj" \
	"$(INTDIR)\AsyncTest1_i.obj" \
	"$(INTDIR)\DllData.obj"

"$(OUTDIR)\proxy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "proxy - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\proxy.dll" ".\dlldata.c" ".\AsyncTest1_p.c" ".\AsyncTest1_i.c" ".\AsyncTest1.h" "$(OUTDIR)\proxy.dll"


CLEAN :
	-@erase "$(INTDIR)\Async_p.obj"
	-@erase "$(INTDIR)\AsyncTest1_i.obj"
	-@erase "$(INTDIR)\DllData.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\proxy.dll"
	-@erase "$(OUTDIR)\proxy.exp"
	-@erase "$(OUTDIR)\proxy.ilk"
	-@erase "$(OUTDIR)\proxy.lib"
	-@erase "$(OUTDIR)\proxy.pdb"
	-@erase "AsyncTest1.h"
	-@erase "AsyncTest1_i.c"
	-@erase "AsyncTest1_p.c"
	-@erase "dlldata.c"
	-@erase "proxy.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D _WIN32_WINNT=0X500 /D "REGISTER_PROXY_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\proxy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\proxy.pdb" /debug /machine:$(mach_type) /def:".\proxy.def" /out:"$(OUTDIR)\proxy.dll" /implib:"$(OUTDIR)\proxy.lib" /pdbtype:sept 
DEF_FILE= \
	".\proxy.def"
LINK32_OBJS= \
	"$(INTDIR)\Async_p.obj" \
	"$(INTDIR)\AsyncTest1_i.obj" \
	"$(INTDIR)\DllData.obj"

"$(OUTDIR)\proxy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : ".\proxy.dll" ".\dlldata.c" ".\AsyncTest1_p.c" ".\AsyncTest1_i.c" ".\AsyncTest1.h" "$(OUTDIR)\proxy.dll"
   copy debug\proxy.dll ..\server\debug\proxy.dll
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("proxy.dep")
!INCLUDE "proxy.dep"
!ELSE 
!MESSAGE Warning: cannot find "proxy.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "proxy - Win32 Release" || "$(CFG)" == "proxy - Win32 Debug"
SOURCE=.\Async_p.c

"$(INTDIR)\Async_p.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\AsyncTest1_i.c

"$(INTDIR)\AsyncTest1_i.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DllData.c

"$(INTDIR)\DllData.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Proxy.idl

!IF  "$(CFG)" == "proxy - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\Proxy.tlb" /mktyplib203 /o "NUL" /win32 

"$(INTDIR)\Proxy.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "proxy - Win32 Debug"

InputPath=.\Proxy.idl

".\AsyncTest1.h"	".\AsyncTest1_i.c"	".\AsyncTest1_p.c"	".\DllData.c"	".\proxy.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off
	if not exist "..\server\$(OUTDIR)" mkdir "..\server\$(OUTDIR)" 
	midl /Oicf  /h "AsyncTest1.h" /iid "AsyncTest1_i.c" /dlldata  "DllData.c" /proxy   "Async_p.c"  /tlb "..\server\$(OUTDIR)\AsyncServer.tlb" "Proxy.idl"
<< 
	

!ENDIF 


!ENDIF 

