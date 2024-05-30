# Microsoft Developer Studio Generated NMAKE File, Based on SmbSmp.dsp
!IF "$(CFG)" == ""
CFG=SmbSmp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SmbSmp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SmbSmp - Win32 Release" && "$(CFG)" != "SmbSmp - Win32 Debug"
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
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SmbSmp.dll"


CLEAN :
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "FORCE_UNICODE" /Fp"$(INTDIR)\SmbSmp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib clusapi.lib resutils.lib netapi32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SmbSmp.pdb" /machine:I386 /def:".\SmbSmp.def" /out:"$(OUTDIR)\SmbSmp.dll" /implib:"$(OUTDIR)\SmbSmp.lib" 
DEF_FILE= \
	".\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\ClRes.obj" \
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
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SmbSmp.dll" "$(OUTDIR)\SmbSmp.bsc"


CLEAN :
	-@erase "$(INTDIR)\ClRes.obj"
	-@erase "$(INTDIR)\ClRes.sbr"
	-@erase "$(INTDIR)\SmbSmp.obj"
	-@erase "$(INTDIR)\SmbSmp.res"
	-@erase "$(INTDIR)\SmbSmp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SmbSmp.bsc"
	-@erase "$(OUTDIR)\SmbSmp.dll"
	-@erase "$(OUTDIR)\SmbSmp.exp"
	-@erase "$(OUTDIR)\SmbSmp.ilk"
	-@erase "$(OUTDIR)\SmbSmp.lib"
	-@erase "$(OUTDIR)\SmbSmp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "FORCE_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SmbSmp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SmbSmp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SmbSmp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClRes.sbr" \
	"$(INTDIR)\SmbSmp.sbr"

"$(OUTDIR)\SmbSmp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib clusapi.lib resutils.lib netapi32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\SmbSmp.pdb" /debug /machine:I386 /def:".\SmbSmp.def" /out:"$(OUTDIR)\SmbSmp.dll" /implib:"$(OUTDIR)\SmbSmp.lib" /pdbtype:sept 
DEF_FILE= \
	".\SmbSmp.def"
LINK32_OBJS= \
	"$(INTDIR)\ClRes.obj" \
	"$(INTDIR)\SmbSmp.obj" \
	"$(INTDIR)\SmbSmp.res"

"$(OUTDIR)\SmbSmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SmbSmp.dep")
!INCLUDE "SmbSmp.dep"
!ELSE 
!MESSAGE Warning: cannot find "SmbSmp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SmbSmp - Win32 Release" || "$(CFG)" == "SmbSmp - Win32 Debug"
SOURCE=.\ClRes.cpp

!IF  "$(CFG)" == "SmbSmp - Win32 Release"


"$(INTDIR)\ClRes.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"


"$(INTDIR)\ClRes.obj"	"$(INTDIR)\ClRes.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SmbSmp.cpp

!IF  "$(CFG)" == "SmbSmp - Win32 Release"


"$(INTDIR)\SmbSmp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SmbSmp - Win32 Debug"


"$(INTDIR)\SmbSmp.obj"	"$(INTDIR)\SmbSmp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SmbSmp.rc

"$(INTDIR)\SmbSmp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

