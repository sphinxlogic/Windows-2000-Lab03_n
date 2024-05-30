# Microsoft Developer Studio Generated NMAKE File, Based on sampprov.dsp
!IF "$(CFG)" == ""
CFG=sampprov - Win32 x86 Debug
!MESSAGE No configuration specified. Defaulting to sampprov - Win32 x86 Debug.
!ENDIF 

!IF "$(CFG)" != "sampprov - Win32 x86 Debug" && "$(CFG)" !=\
 "sampprov - Win32 x86 Release" && "$(CFG)" !=\
 "sampprov - Win32 (ALPHA) axp Debug" && "$(CFG)" !=\
 "sampprov - Win32 (ALPHA) axp Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sampprov.mak" CFG="sampprov - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sampprov - Win32 x86 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sampprov - Win32 x86 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sampprov - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "sampprov - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

OUTDIR=.\x86_Debu
INTDIR=.\x86_Debu
# Begin Custom Macros
OutDir=.\.\x86_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampprov.dll"

!ELSE 

ALL : "$(OUTDIR)\sampprov.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\accessor.obj"
	-@erase "$(INTDIR)\asserts.obj"
	-@erase "$(INTDIR)\baseobj.obj"
	-@erase "$(INTDIR)\binder.obj"
	-@erase "$(INTDIR)\bitarray.obj"
	-@erase "$(INTDIR)\classfac.obj"
	-@erase "$(INTDIR)\colinfo.obj"
	-@erase "$(INTDIR)\command.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\crtsess.obj"
	-@erase "$(INTDIR)\cvttype.obj"
	-@erase "$(INTDIR)\datasrc.obj"
	-@erase "$(INTDIR)\dbinit.obj"
	-@erase "$(INTDIR)\dbprop.obj"
	-@erase "$(INTDIR)\dbsess.obj"
	-@erase "$(INTDIR)\extbuff.obj"
	-@erase "$(INTDIR)\fileidx.obj"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\hashtbl.obj"
	-@erase "$(INTDIR)\headers.obj"
	-@erase "$(INTDIR)\igetrow.obj"
	-@erase "$(INTDIR)\irowiden.obj"
	-@erase "$(INTDIR)\irowset.obj"
	-@erase "$(INTDIR)\opnrowst.obj"
	-@erase "$(INTDIR)\persist.obj"
	-@erase "$(INTDIR)\row.obj"
	-@erase "$(INTDIR)\rowchng.obj"
	-@erase "$(INTDIR)\rowinfo.obj"
	-@erase "$(INTDIR)\rowset.obj"
	-@erase "$(INTDIR)\sampprov.pch"
	-@erase "$(INTDIR)\sampprov.res"
	-@erase "$(INTDIR)\stream.obj"
	-@erase "$(INTDIR)\utilprop.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\sampprov.dll"
	-@erase "$(OUTDIR)\sampprov.exp"
	-@erase "$(OUTDIR)\sampprov.ilk"
	-@erase "$(OUTDIR)\sampprov.lib"
	-@erase "$(OUTDIR)\sampprov.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\x86_Debu/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampprov.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampprov.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\sampprov.pdb" /debug /machine:I386 /def:".\sampprov.def"\
 /out:"$(OUTDIR)\sampprov.dll" /implib:"$(OUTDIR)\sampprov.lib"\
 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
DEF_FILE= \
	".\sampprov.def"
LINK32_OBJS= \
	"$(INTDIR)\accessor.obj" \
	"$(INTDIR)\asserts.obj" \
	"$(INTDIR)\baseobj.obj" \
	"$(INTDIR)\binder.obj" \
	"$(INTDIR)\bitarray.obj" \
	"$(INTDIR)\classfac.obj" \
	"$(INTDIR)\colinfo.obj" \
	"$(INTDIR)\command.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\crtsess.obj" \
	"$(INTDIR)\cvttype.obj" \
	"$(INTDIR)\datasrc.obj" \
	"$(INTDIR)\dbinit.obj" \
	"$(INTDIR)\dbprop.obj" \
	"$(INTDIR)\dbsess.obj" \
	"$(INTDIR)\extbuff.obj" \
	"$(INTDIR)\fileidx.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\hashtbl.obj" \
	"$(INTDIR)\headers.obj" \
	"$(INTDIR)\igetrow.obj" \
	"$(INTDIR)\irowiden.obj" \
	"$(INTDIR)\irowset.obj" \
	"$(INTDIR)\opnrowst.obj" \
	"$(INTDIR)\persist.obj" \
	"$(INTDIR)\row.obj" \
	"$(INTDIR)\rowchng.obj" \
	"$(INTDIR)\rowinfo.obj" \
	"$(INTDIR)\rowset.obj" \
	"$(INTDIR)\sampprov.res" \
	"$(INTDIR)\stream.obj" \
	"$(INTDIR)\utilprop.obj"

"$(OUTDIR)\sampprov.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

OUTDIR=.\x86_Rele
INTDIR=.\x86_Rele
# Begin Custom Macros
OutDir=.\.\x86_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampprov.dll"

!ELSE 

ALL : "$(OUTDIR)\sampprov.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\accessor.obj"
	-@erase "$(INTDIR)\asserts.obj"
	-@erase "$(INTDIR)\baseobj.obj"
	-@erase "$(INTDIR)\binder.obj"
	-@erase "$(INTDIR)\bitarray.obj"
	-@erase "$(INTDIR)\classfac.obj"
	-@erase "$(INTDIR)\colinfo.obj"
	-@erase "$(INTDIR)\command.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\crtsess.obj"
	-@erase "$(INTDIR)\cvttype.obj"
	-@erase "$(INTDIR)\datasrc.obj"
	-@erase "$(INTDIR)\dbinit.obj"
	-@erase "$(INTDIR)\dbprop.obj"
	-@erase "$(INTDIR)\dbsess.obj"
	-@erase "$(INTDIR)\extbuff.obj"
	-@erase "$(INTDIR)\fileidx.obj"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\hashtbl.obj"
	-@erase "$(INTDIR)\headers.obj"
	-@erase "$(INTDIR)\igetrow.obj"
	-@erase "$(INTDIR)\irowiden.obj"
	-@erase "$(INTDIR)\irowset.obj"
	-@erase "$(INTDIR)\opnrowst.obj"
	-@erase "$(INTDIR)\persist.obj"
	-@erase "$(INTDIR)\row.obj"
	-@erase "$(INTDIR)\rowchng.obj"
	-@erase "$(INTDIR)\rowinfo.obj"
	-@erase "$(INTDIR)\rowset.obj"
	-@erase "$(INTDIR)\sampprov.pch"
	-@erase "$(INTDIR)\sampprov.res"
	-@erase "$(INTDIR)\stream.obj"
	-@erase "$(INTDIR)\utilprop.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\sampprov.dll"
	-@erase "$(OUTDIR)\sampprov.exp"
	-@erase "$(OUTDIR)\sampprov.lib"
	-@erase "$(OUTDIR)\sampprov.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\x86_Rele/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampprov.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampprov.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\sampprov.pdb" /map:"$(INTDIR)\sampprov.map" /machine:I386\
 /def:".\sampprov.def" /out:"$(OUTDIR)\sampprov.dll"\
 /implib:"$(OUTDIR)\sampprov.lib" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"\
 
DEF_FILE= \
	".\sampprov.def"
LINK32_OBJS= \
	"$(INTDIR)\accessor.obj" \
	"$(INTDIR)\asserts.obj" \
	"$(INTDIR)\baseobj.obj" \
	"$(INTDIR)\binder.obj" \
	"$(INTDIR)\bitarray.obj" \
	"$(INTDIR)\classfac.obj" \
	"$(INTDIR)\colinfo.obj" \
	"$(INTDIR)\command.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\crtsess.obj" \
	"$(INTDIR)\cvttype.obj" \
	"$(INTDIR)\datasrc.obj" \
	"$(INTDIR)\dbinit.obj" \
	"$(INTDIR)\dbprop.obj" \
	"$(INTDIR)\dbsess.obj" \
	"$(INTDIR)\extbuff.obj" \
	"$(INTDIR)\fileidx.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\hashtbl.obj" \
	"$(INTDIR)\headers.obj" \
	"$(INTDIR)\igetrow.obj" \
	"$(INTDIR)\irowiden.obj" \
	"$(INTDIR)\irowset.obj" \
	"$(INTDIR)\opnrowst.obj" \
	"$(INTDIR)\persist.obj" \
	"$(INTDIR)\row.obj" \
	"$(INTDIR)\rowchng.obj" \
	"$(INTDIR)\rowinfo.obj" \
	"$(INTDIR)\rowset.obj" \
	"$(INTDIR)\sampprov.res" \
	"$(INTDIR)\stream.obj" \
	"$(INTDIR)\utilprop.obj"

"$(OUTDIR)\sampprov.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

OUTDIR=.\axp_Debu
INTDIR=.\axp_Debu
# Begin Custom Macros
OutDir=.\.\axp_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampprov.dll"

!ELSE 

ALL : "$(OUTDIR)\sampprov.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\accessor.obj"
	-@erase "$(INTDIR)\asserts.obj"
	-@erase "$(INTDIR)\baseobj.obj"
	-@erase "$(INTDIR)\binder.obj"
	-@erase "$(INTDIR)\bitarray.obj"
	-@erase "$(INTDIR)\classfac.obj"
	-@erase "$(INTDIR)\colinfo.obj"
	-@erase "$(INTDIR)\command.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\crtsess.obj"
	-@erase "$(INTDIR)\cvttype.obj"
	-@erase "$(INTDIR)\datasrc.obj"
	-@erase "$(INTDIR)\dbinit.obj"
	-@erase "$(INTDIR)\dbprop.obj"
	-@erase "$(INTDIR)\dbsess.obj"
	-@erase "$(INTDIR)\extbuff.obj"
	-@erase "$(INTDIR)\fileidx.obj"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\hashtbl.obj"
	-@erase "$(INTDIR)\headers.obj"
	-@erase "$(INTDIR)\igetrow.obj"
	-@erase "$(INTDIR)\irowiden.obj"
	-@erase "$(INTDIR)\irowset.obj"
	-@erase "$(INTDIR)\opnrowst.obj"
	-@erase "$(INTDIR)\persist.obj"
	-@erase "$(INTDIR)\row.obj"
	-@erase "$(INTDIR)\rowchng.obj"
	-@erase "$(INTDIR)\rowinfo.obj"
	-@erase "$(INTDIR)\rowset.obj"
	-@erase "$(INTDIR)\sampprov.pch"
	-@erase "$(INTDIR)\sampprov.res"
	-@erase "$(INTDIR)\stream.obj"
	-@erase "$(INTDIR)\utilprop.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\sampprov.dll"
	-@erase "$(OUTDIR)\sampprov.exp"
	-@erase "$(OUTDIR)\sampprov.ilk"
	-@erase "$(OUTDIR)\sampprov.lib"
	-@erase "$(OUTDIR)\sampprov.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\axp_Debu/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampprov.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampprov.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\sampprov.pdb" /debug /machine:ALPHA /def:".\sampprov.def"\
 /out:"$(OUTDIR)\sampprov.dll" /implib:"$(OUTDIR)\sampprov.lib"\
 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
DEF_FILE= \
	".\sampprov.def"
LINK32_OBJS= \
	"$(INTDIR)\accessor.obj" \
	"$(INTDIR)\asserts.obj" \
	"$(INTDIR)\baseobj.obj" \
	"$(INTDIR)\binder.obj" \
	"$(INTDIR)\bitarray.obj" \
	"$(INTDIR)\classfac.obj" \
	"$(INTDIR)\colinfo.obj" \
	"$(INTDIR)\command.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\crtsess.obj" \
	"$(INTDIR)\cvttype.obj" \
	"$(INTDIR)\datasrc.obj" \
	"$(INTDIR)\dbinit.obj" \
	"$(INTDIR)\dbprop.obj" \
	"$(INTDIR)\dbsess.obj" \
	"$(INTDIR)\extbuff.obj" \
	"$(INTDIR)\fileidx.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\hashtbl.obj" \
	"$(INTDIR)\headers.obj" \
	"$(INTDIR)\igetrow.obj" \
	"$(INTDIR)\irowiden.obj" \
	"$(INTDIR)\irowset.obj" \
	"$(INTDIR)\opnrowst.obj" \
	"$(INTDIR)\persist.obj" \
	"$(INTDIR)\row.obj" \
	"$(INTDIR)\rowchng.obj" \
	"$(INTDIR)\rowinfo.obj" \
	"$(INTDIR)\rowset.obj" \
	"$(INTDIR)\sampprov.res" \
	"$(INTDIR)\stream.obj" \
	"$(INTDIR)\utilprop.obj"

"$(OUTDIR)\sampprov.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

OUTDIR=.\axp_Rele
INTDIR=.\axp_Rele
# Begin Custom Macros
OutDir=.\.\axp_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampprov.dll"

!ELSE 

ALL : "$(OUTDIR)\sampprov.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\accessor.obj"
	-@erase "$(INTDIR)\asserts.obj"
	-@erase "$(INTDIR)\baseobj.obj"
	-@erase "$(INTDIR)\binder.obj"
	-@erase "$(INTDIR)\bitarray.obj"
	-@erase "$(INTDIR)\classfac.obj"
	-@erase "$(INTDIR)\colinfo.obj"
	-@erase "$(INTDIR)\command.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\crtsess.obj"
	-@erase "$(INTDIR)\cvttype.obj"
	-@erase "$(INTDIR)\datasrc.obj"
	-@erase "$(INTDIR)\dbinit.obj"
	-@erase "$(INTDIR)\dbprop.obj"
	-@erase "$(INTDIR)\dbsess.obj"
	-@erase "$(INTDIR)\extbuff.obj"
	-@erase "$(INTDIR)\fileidx.obj"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\hashtbl.obj"
	-@erase "$(INTDIR)\headers.obj"
	-@erase "$(INTDIR)\igetrow.obj"
	-@erase "$(INTDIR)\irowiden.obj"
	-@erase "$(INTDIR)\irowset.obj"
	-@erase "$(INTDIR)\opnrowst.obj"
	-@erase "$(INTDIR)\persist.obj"
	-@erase "$(INTDIR)\row.obj"
	-@erase "$(INTDIR)\rowchng.obj"
	-@erase "$(INTDIR)\rowinfo.obj"
	-@erase "$(INTDIR)\rowset.obj"
	-@erase "$(INTDIR)\sampprov.pch"
	-@erase "$(INTDIR)\sampprov.res"
	-@erase "$(INTDIR)\stream.obj"
	-@erase "$(INTDIR)\utilprop.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\sampprov.dll"
	-@erase "$(OUTDIR)\sampprov.exp"
	-@erase "$(OUTDIR)\sampprov.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\axp_Rele/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampprov.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampprov.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\sampprov.pdb" /machine:ALPHA /def:".\sampprov.def"\
 /out:"$(OUTDIR)\sampprov.dll" /implib:"$(OUTDIR)\sampprov.lib"\
 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
DEF_FILE= \
	".\sampprov.def"
LINK32_OBJS= \
	"$(INTDIR)\accessor.obj" \
	"$(INTDIR)\asserts.obj" \
	"$(INTDIR)\baseobj.obj" \
	"$(INTDIR)\binder.obj" \
	"$(INTDIR)\bitarray.obj" \
	"$(INTDIR)\classfac.obj" \
	"$(INTDIR)\colinfo.obj" \
	"$(INTDIR)\command.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\crtsess.obj" \
	"$(INTDIR)\cvttype.obj" \
	"$(INTDIR)\datasrc.obj" \
	"$(INTDIR)\dbinit.obj" \
	"$(INTDIR)\dbprop.obj" \
	"$(INTDIR)\dbsess.obj" \
	"$(INTDIR)\extbuff.obj" \
	"$(INTDIR)\fileidx.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\hashtbl.obj" \
	"$(INTDIR)\headers.obj" \
	"$(INTDIR)\igetrow.obj" \
	"$(INTDIR)\irowiden.obj" \
	"$(INTDIR)\irowset.obj" \
	"$(INTDIR)\opnrowst.obj" \
	"$(INTDIR)\persist.obj" \
	"$(INTDIR)\row.obj" \
	"$(INTDIR)\rowchng.obj" \
	"$(INTDIR)\rowinfo.obj" \
	"$(INTDIR)\rowset.obj" \
	"$(INTDIR)\sampprov.res" \
	"$(INTDIR)\stream.obj" \
	"$(INTDIR)\utilprop.obj"

"$(OUTDIR)\sampprov.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "sampprov - Win32 x86 Debug" || "$(CFG)" ==\
 "sampprov - Win32 x86 Release" || "$(CFG)" ==\
 "sampprov - Win32 (ALPHA) axp Debug" || "$(CFG)" ==\
 "sampprov - Win32 (ALPHA) axp Release"
SOURCE=.\accessor.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_ACCES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\accessor.obj" : $(SOURCE) $(DEP_CPP_ACCES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_ACCES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\accessor.obj" : $(SOURCE) $(DEP_CPP_ACCES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ACCES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\accessor.obj" : $(SOURCE) $(DEP_CPP_ACCES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ACCES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\accessor.obj" : $(SOURCE) $(DEP_CPP_ACCES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\asserts.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_ASSER=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\asserts.obj" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_ASSER=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\asserts.obj" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ASSER=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\asserts.obj" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ASSER=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\asserts.obj" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\baseobj.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_BASEO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\baseobj.obj" : $(SOURCE) $(DEP_CPP_BASEO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_BASEO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\baseobj.obj" : $(SOURCE) $(DEP_CPP_BASEO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_BASEO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\baseobj.obj" : $(SOURCE) $(DEP_CPP_BASEO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_BASEO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\baseobj.obj" : $(SOURCE) $(DEP_CPP_BASEO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\binder.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_BINDE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\binder.obj" : $(SOURCE) $(DEP_CPP_BINDE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_BINDE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\binder.obj" : $(SOURCE) $(DEP_CPP_BINDE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_BINDE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\binder.obj" : $(SOURCE) $(DEP_CPP_BINDE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_BINDE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\binder.obj" : $(SOURCE) $(DEP_CPP_BINDE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\bitarray.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_BITAR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\bitarray.obj" : $(SOURCE) $(DEP_CPP_BITAR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_BITAR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\bitarray.obj" : $(SOURCE) $(DEP_CPP_BITAR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_BITAR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\bitarray.obj" : $(SOURCE) $(DEP_CPP_BITAR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_BITAR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\bitarray.obj" : $(SOURCE) $(DEP_CPP_BITAR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\classfac.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_CLASS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\classfac.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\classfac.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_CLASS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\classfac.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\classfac.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_CLASS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\classfac.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\classfac.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_CLASS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\classfac.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\classfac.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\colinfo.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_COLIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\colinfo.obj" : $(SOURCE) $(DEP_CPP_COLIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_COLIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\colinfo.obj" : $(SOURCE) $(DEP_CPP_COLIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_COLIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\colinfo.obj" : $(SOURCE) $(DEP_CPP_COLIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_COLIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\colinfo.obj" : $(SOURCE) $(DEP_CPP_COLIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\command.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_COMMA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\command.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_COMMA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\command.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_COMMA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\command.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_COMMA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\command.obj" : $(SOURCE) $(DEP_CPP_COMMA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\common.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_COMMO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_COMMO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_COMMO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_COMMO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\crtsess.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_CRTSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\crtsess.obj" : $(SOURCE) $(DEP_CPP_CRTSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_CRTSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\crtsess.obj" : $(SOURCE) $(DEP_CPP_CRTSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_CRTSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\crtsess.obj" : $(SOURCE) $(DEP_CPP_CRTSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_CRTSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\crtsess.obj" : $(SOURCE) $(DEP_CPP_CRTSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\cvttype.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_CVTTY=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\cvttype.obj" : $(SOURCE) $(DEP_CPP_CVTTY) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_CVTTY=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\cvttype.obj" : $(SOURCE) $(DEP_CPP_CVTTY) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_CVTTY=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\cvttype.obj" : $(SOURCE) $(DEP_CPP_CVTTY) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_CVTTY=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\cvttype.obj" : $(SOURCE) $(DEP_CPP_CVTTY) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\datasrc.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_DATAS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\datasrc.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_DATAS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\datasrc.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DATAS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\datasrc.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DATAS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\datasrc.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\dbinit.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_DBINI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbinit.obj" : $(SOURCE) $(DEP_CPP_DBINI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_DBINI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbinit.obj" : $(SOURCE) $(DEP_CPP_DBINI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DBINI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbinit.obj" : $(SOURCE) $(DEP_CPP_DBINI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DBINI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbinit.obj" : $(SOURCE) $(DEP_CPP_DBINI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\dbprop.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_DBPRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbprop.obj" : $(SOURCE) $(DEP_CPP_DBPRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_DBPRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbprop.obj" : $(SOURCE) $(DEP_CPP_DBPRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DBPRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbprop.obj" : $(SOURCE) $(DEP_CPP_DBPRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DBPRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbprop.obj" : $(SOURCE) $(DEP_CPP_DBPRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\dbsess.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_DBSES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbsess.obj" : $(SOURCE) $(DEP_CPP_DBSES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_DBSES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbsess.obj" : $(SOURCE) $(DEP_CPP_DBSES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DBSES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbsess.obj" : $(SOURCE) $(DEP_CPP_DBSES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DBSES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dbsess.obj" : $(SOURCE) $(DEP_CPP_DBSES) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\extbuff.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_EXTBU=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\extbuff.obj" : $(SOURCE) $(DEP_CPP_EXTBU) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_EXTBU=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\extbuff.obj" : $(SOURCE) $(DEP_CPP_EXTBU) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_EXTBU=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\extbuff.obj" : $(SOURCE) $(DEP_CPP_EXTBU) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_EXTBU=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\extbuff.obj" : $(SOURCE) $(DEP_CPP_EXTBU) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\fileidx.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_FILEI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileidx.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_FILEI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileidx.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_FILEI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileidx.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_FILEI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileidx.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\fileio.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_FILEIO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEIO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_FILEIO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yu"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEIO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_FILEIO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEIO) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_FILEIO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\fileio.obj" : $(SOURCE) $(DEP_CPP_FILEIO) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\globals.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_GLOBA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_GLOBA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_GLOBA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_GLOBA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\hashtbl.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_HASHT=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\hashtbl.obj" : $(SOURCE) $(DEP_CPP_HASHT) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_HASHT=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\hashtbl.obj" : $(SOURCE) $(DEP_CPP_HASHT) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_HASHT=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\hashtbl.obj" : $(SOURCE) $(DEP_CPP_HASHT) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_HASHT=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\hashtbl.obj" : $(SOURCE) $(DEP_CPP_HASHT) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\headers.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_HEADE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yc"headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\headers.obj"	"$(INTDIR)\sampprov.pch" : $(SOURCE) $(DEP_CPP_HEADE)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_HEADE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yc"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\headers.obj"	"$(INTDIR)\sampprov.pch" : $(SOURCE) $(DEP_CPP_HEADE)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_HEADE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yc"headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\headers.obj"	"$(INTDIR)\sampprov.pch" : $(SOURCE) $(DEP_CPP_HEADE)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_HEADE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\sampprov.pch" /Yc"headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\headers.obj"	"$(INTDIR)\sampprov.pch" : $(SOURCE) $(DEP_CPP_HEADE)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\igetrow.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_IGETR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\igetrow.obj" : $(SOURCE) $(DEP_CPP_IGETR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_IGETR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\igetrow.obj" : $(SOURCE) $(DEP_CPP_IGETR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_IGETR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\igetrow.obj" : $(SOURCE) $(DEP_CPP_IGETR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_IGETR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\igetrow.obj" : $(SOURCE) $(DEP_CPP_IGETR) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\irowiden.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_IROWI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowiden.obj" : $(SOURCE) $(DEP_CPP_IROWI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_IROWI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowiden.obj" : $(SOURCE) $(DEP_CPP_IROWI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_IROWI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowiden.obj" : $(SOURCE) $(DEP_CPP_IROWI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_IROWI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowiden.obj" : $(SOURCE) $(DEP_CPP_IROWI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\irowset.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_IROWS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowset.obj" : $(SOURCE) $(DEP_CPP_IROWS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_IROWS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowset.obj" : $(SOURCE) $(DEP_CPP_IROWS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_IROWS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowset.obj" : $(SOURCE) $(DEP_CPP_IROWS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_IROWS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\irowset.obj" : $(SOURCE) $(DEP_CPP_IROWS) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\opnrowst.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_OPNRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\opnrowst.obj" : $(SOURCE) $(DEP_CPP_OPNRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_OPNRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\opnrowst.obj" : $(SOURCE) $(DEP_CPP_OPNRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_OPNRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\opnrowst.obj" : $(SOURCE) $(DEP_CPP_OPNRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_OPNRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\opnrowst.obj" : $(SOURCE) $(DEP_CPP_OPNRO) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\persist.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_PERSI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_PERSI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_PERSI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_PERSI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\row.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_ROW_C=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\row.obj" : $(SOURCE) $(DEP_CPP_ROW_C) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_ROW_C=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\row.obj" : $(SOURCE) $(DEP_CPP_ROW_C) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROW_C=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\row.obj" : $(SOURCE) $(DEP_CPP_ROW_C) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROW_C=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\row.obj" : $(SOURCE) $(DEP_CPP_ROW_C) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\rowchng.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_ROWCH=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowchng.obj" : $(SOURCE) $(DEP_CPP_ROWCH) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_ROWCH=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowchng.obj" : $(SOURCE) $(DEP_CPP_ROWCH) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROWCH=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowchng.obj" : $(SOURCE) $(DEP_CPP_ROWCH) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROWCH=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowchng.obj" : $(SOURCE) $(DEP_CPP_ROWCH) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\rowinfo.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_ROWIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowinfo.obj" : $(SOURCE) $(DEP_CPP_ROWIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_ROWIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowinfo.obj" : $(SOURCE) $(DEP_CPP_ROWIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROWIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowinfo.obj" : $(SOURCE) $(DEP_CPP_ROWIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROWIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowinfo.obj" : $(SOURCE) $(DEP_CPP_ROWIN) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\rowset.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_ROWSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowset.obj" : $(SOURCE) $(DEP_CPP_ROWSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_ROWSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowset.obj" : $(SOURCE) $(DEP_CPP_ROWSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROWSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowset.obj" : $(SOURCE) $(DEP_CPP_ROWSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROWSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\rowset.obj" : $(SOURCE) $(DEP_CPP_ROWSE) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\sampprov.rc
DEP_RSC_SAMPP=\
	".\res\SampProv.rc2"\
	".\sampver.h"\
	

"$(INTDIR)\sampprov.res" : $(SOURCE) $(DEP_RSC_SAMPP) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\stream.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_STREA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\stream.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_STREA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\stream.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_STREA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\stream.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_STREA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\stream.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 

SOURCE=.\utilprop.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

DEP_CPP_UTILP=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\sampver.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\utilprop.obj" : $(SOURCE) $(DEP_CPP_UTILP) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

DEP_CPP_UTILP=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\sampver.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\utilprop.obj" : $(SOURCE) $(DEP_CPP_UTILP) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_UTILP=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\sampver.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\utilprop.obj" : $(SOURCE) $(DEP_CPP_UTILP) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_UTILP=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\common.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\sampver.h"\
	".\stream.h"\
	".\utilprop.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\utilprop.obj" : $(SOURCE) $(DEP_CPP_UTILP) "$(INTDIR)"\
 "$(INTDIR)\sampprov.pch"


!ENDIF 


!ENDIF 

