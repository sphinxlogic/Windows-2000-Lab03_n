# Microsoft Developer Studio Generated NMAKE File, Based on ClipSrv.dsp
!IF "$(CFG)" == ""
CFG=ClipSrv - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ClipSrv - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ClipSrv - Win32 Release" && "$(CFG)" != "ClipSrv - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClipSrv.mak" CFG="ClipSrv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClipSrv - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClipSrv - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ClipSrv.dll" "$(OUTDIR)\ClipSrv.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClipSrv.obj"
	-@erase "$(INTDIR)\ClipSrv.res"
	-@erase "$(INTDIR)\ClipSrv.sbr"
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\ClRes.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ClipSrv.bsc"
	-@erase "$(OUTDIR)\ClipSrv.dll"
	-@erase "$(OUTDIR)\ClipSrv.exp"
	-@erase "$(OUTDIR)\ClipSrv.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ClipSrv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /D "MIDL_PASS" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrv.res" /d "NDEBUG" 
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
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib clusapi.lib resutils.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ClipSrv.pdb" /machine:I386 /def:".\ClipSrv.def" /out:"$(OUTDIR)\ClipSrv.dll" /implib:"$(OUTDIR)\ClipSrv.lib" 
DEF_FILE= \
	".\ClipSrv.def"
LINK32_OBJS= \
	"$(INTDIR)\ClipSrv.obj" \
	"$(INTDIR)\ClRes.obj" \
	"$(INTDIR)\ClipSrv.res"

"$(OUTDIR)\ClipSrv.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ClipSrv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ClipSrv.dll" "$(OUTDIR)\ClipSrv.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClipSrv.obj"
	-@erase "$(INTDIR)\ClipSrv.res"
	-@erase "$(INTDIR)\ClipSrv.sbr"
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\ClRes.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ClipSrv.bsc"
	-@erase "$(OUTDIR)\ClipSrv.dll"
	-@erase "$(OUTDIR)\ClipSrv.exp"
	-@erase "$(OUTDIR)\ClipSrv.ilk"
	-@erase "$(OUTDIR)\ClipSrv.lib"
	-@erase "$(OUTDIR)\ClipSrv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ClipSrv.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /D "MIDL_PASS" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ClipSrv.res" /d "_DEBUG" 
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
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib clusapi.lib resutils.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ClipSrv.pdb" /debug /machine:I386 /def:".\ClipSrv.def" /out:"$(OUTDIR)\ClipSrv.dll" /implib:"$(OUTDIR)\ClipSrv.lib" /pdbtype:sept 
DEF_FILE= \
	".\ClipSrv.def"
LINK32_OBJS= \
	"$(INTDIR)\ClipSrv.obj" \
	"$(INTDIR)\ClRes.obj" \
	"$(INTDIR)\ClipSrv.res"

"$(OUTDIR)\ClipSrv.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ClipSrv.dep")
!INCLUDE "ClipSrv.dep"
!ELSE 
!MESSAGE Warning: cannot find "ClipSrv.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ClipSrv - Win32 Release" || "$(CFG)" == "ClipSrv - Win32 Debug"
SOURCE=.\ClipSrv.cpp

"$(INTDIR)\ClipSrv.obj"	"$(INTDIR)\ClipSrv.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ClipSrv.rc

"$(INTDIR)\ClipSrv.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ClRes.cpp

"$(INTDIR)\ClRes.obj"	"$(INTDIR)\ClRes.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 

