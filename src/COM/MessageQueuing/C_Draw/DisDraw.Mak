# Microsoft Developer Studio Generated NMAKE File, Based on disdraw.dsp
!IF "$(CFG)" == ""
CFG=disdraw - Win32 ALPHA Debug
!MESSAGE No configuration specified. Defaulting to disdraw - Win32 ALPHA Debug.
!ENDIF 

!IF "$(CFG)" != "disdraw - Win32 Release" && "$(CFG)" !=\
 "disdraw - Win32 Debug" && "$(CFG)" != "disdraw - Win32 Release win95" &&\
 "$(CFG)" != "disdraw - Win32 Debug win95" && "$(CFG)" !=\
 "disdraw - Win32 ALPHA Debug" && "$(CFG)" != "disdraw - Win32 ALPHA Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "disdraw.mak" CFG="disdraw - Win32 ALPHA Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "disdraw - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 Release win95" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 Debug win95" (based on "Win32 (x86) Application")
!MESSAGE "disdraw - Win32 ALPHA Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "disdraw - Win32 ALPHA Release" (based on "Win32 (ALPHA) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "disdraw - Win32 Release"

OUTDIR=.\release
INTDIR=.\release
# Begin Custom Macros
OutDir=.\.\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\c_draw.exe"

!ELSE 

ALL : "$(OUTDIR)\c_draw.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\disdraw.obj"
	-@erase "$(INTDIR)\disdraw.pch"
	-@erase "$(INTDIR)\disdraw.res"
	-@erase "$(INTDIR)\drawarea.obj"
	-@erase "$(INTDIR)\drawdlg.obj"
	-@erase "$(INTDIR)\logindlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\c_draw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\disdraw.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\release/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\disdraw.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\disdraw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none\
 /machine:I386 /out:"$(OUTDIR)\c_draw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\disdraw.obj" \
	"$(INTDIR)\disdraw.res" \
	"$(INTDIR)\drawarea.obj" \
	"$(INTDIR)\drawdlg.obj" \
	"$(INTDIR)\logindlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\c_draw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\c_draw.exe" "$(OUTDIR)\disdraw.bsc"

!ELSE 

ALL : "$(OUTDIR)\c_draw.exe" "$(OUTDIR)\disdraw.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\disdraw.obj"
	-@erase "$(INTDIR)\disdraw.pch"
	-@erase "$(INTDIR)\disdraw.res"
	-@erase "$(INTDIR)\disdraw.sbr"
	-@erase "$(INTDIR)\drawarea.obj"
	-@erase "$(INTDIR)\drawarea.sbr"
	-@erase "$(INTDIR)\drawdlg.obj"
	-@erase "$(INTDIR)\drawdlg.sbr"
	-@erase "$(INTDIR)\logindlg.obj"
	-@erase "$(INTDIR)\logindlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\c_draw.exe"
	-@erase "$(OUTDIR)\disdraw.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D "_DEBUG"\
 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\disdraw.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\disdraw.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\disdraw.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\disdraw.sbr" \
	"$(INTDIR)\drawarea.sbr" \
	"$(INTDIR)\drawdlg.sbr" \
	"$(INTDIR)\logindlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\disdraw.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none\
 /debug /machine:I386 /out:"$(OUTDIR)\c_draw.exe" /libpath:"..\..\bins\debug" 
LINK32_OBJS= \
	"$(INTDIR)\disdraw.obj" \
	"$(INTDIR)\disdraw.res" \
	"$(INTDIR)\drawarea.obj" \
	"$(INTDIR)\drawdlg.obj" \
	"$(INTDIR)\logindlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\c_draw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

OUTDIR=.\Release95
INTDIR=.\Release95
# Begin Custom Macros
OutDir=.\.\Release95
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\c_draw.exe"

!ELSE 

ALL : "$(OUTDIR)\c_draw.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\disdraw.obj"
	-@erase "$(INTDIR)\disdraw.pch"
	-@erase "$(INTDIR)\disdraw.res"
	-@erase "$(INTDIR)\drawarea.obj"
	-@erase "$(INTDIR)\drawdlg.obj"
	-@erase "$(INTDIR)\logindlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\c_draw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\disdraw.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release95/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\disdraw.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\disdraw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none\
 /machine:I386 /out:"$(OUTDIR)\c_draw.exe" /libpath:"..\..\bins\release95" 
LINK32_OBJS= \
	"$(INTDIR)\disdraw.obj" \
	"$(INTDIR)\disdraw.res" \
	"$(INTDIR)\drawarea.obj" \
	"$(INTDIR)\drawdlg.obj" \
	"$(INTDIR)\logindlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\c_draw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

OUTDIR=.\Debug95
INTDIR=.\Debug95
# Begin Custom Macros
OutDir=.\.\Debug95
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\c_draw.exe"

!ELSE 

ALL : "$(OUTDIR)\c_draw.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\disdraw.obj"
	-@erase "$(INTDIR)\disdraw.pch"
	-@erase "$(INTDIR)\disdraw.res"
	-@erase "$(INTDIR)\drawarea.obj"
	-@erase "$(INTDIR)\drawdlg.obj"
	-@erase "$(INTDIR)\logindlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\c_draw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D "_DEBUG"\
 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\disdraw.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug95/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\disdraw.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\disdraw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none\
 /debug /machine:I386 /out:"$(OUTDIR)\c_draw.exe" /libpath:"..\..\bins\debug95" 
LINK32_OBJS= \
	"$(INTDIR)\disdraw.obj" \
	"$(INTDIR)\disdraw.res" \
	"$(INTDIR)\drawarea.obj" \
	"$(INTDIR)\drawdlg.obj" \
	"$(INTDIR)\logindlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\c_draw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

OUTDIR=.\Debug
INTDIR=.\debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\c_draw.exe" "$(OUTDIR)\disdraw.bsc"

!ELSE 

ALL : "$(OUTDIR)\c_draw.exe" "$(OUTDIR)\disdraw.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\disdraw.obj"
	-@erase "$(INTDIR)\disdraw.pch"
	-@erase "$(INTDIR)\disdraw.res"
	-@erase "$(INTDIR)\disdraw.sbr"
	-@erase "$(INTDIR)\drawarea.obj"
	-@erase "$(INTDIR)\drawarea.sbr"
	-@erase "$(INTDIR)\drawdlg.obj"
	-@erase "$(INTDIR)\drawdlg.sbr"
	-@erase "$(INTDIR)\logindlg.obj"
	-@erase "$(INTDIR)\logindlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\c_draw.exe"
	-@erase "$(OUTDIR)\disdraw.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\disdraw.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /MDd /c 
CPP_OBJS=.\debug/
CPP_SBRS=.\debug/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\disdraw.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\disdraw.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\disdraw.sbr" \
	"$(INTDIR)\drawarea.sbr" \
	"$(INTDIR)\drawdlg.sbr" \
	"$(INTDIR)\logindlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\disdraw.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none\
 /debug /machine:ALPHA /out:"$(OUTDIR)\c_draw.exe" /libpath:"..\..\bins\debug" 
LINK32_OBJS= \
	"$(INTDIR)\disdraw.obj" \
	"$(INTDIR)\disdraw.res" \
	"$(INTDIR)\drawarea.obj" \
	"$(INTDIR)\drawdlg.obj" \
	"$(INTDIR)\logindlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\c_draw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

OUTDIR=.\release
INTDIR=.\release
# Begin Custom Macros
OutDir=.\.\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\c_draw.exe"

!ELSE 

ALL : "$(OUTDIR)\c_draw.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\disdraw.obj"
	-@erase "$(INTDIR)\disdraw.pch"
	-@erase "$(INTDIR)\disdraw.res"
	-@erase "$(INTDIR)\drawarea.obj"
	-@erase "$(INTDIR)\drawdlg.obj"
	-@erase "$(INTDIR)\logindlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\c_draw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\disdraw.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\release/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\disdraw.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\disdraw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\..\..\..\lib\mqrt.lib /nologo /subsystem:windows /pdb:none\
 /machine:ALPHA /out:"$(OUTDIR)\c_draw.exe" /libpath:"..\..\bins\release" 
LINK32_OBJS= \
	"$(INTDIR)\disdraw.obj" \
	"$(INTDIR)\disdraw.res" \
	"$(INTDIR)\drawarea.obj" \
	"$(INTDIR)\drawdlg.obj" \
	"$(INTDIR)\logindlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\c_draw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "disdraw - Win32 Release" || "$(CFG)" ==\
 "disdraw - Win32 Debug" || "$(CFG)" == "disdraw - Win32 Release win95" ||\
 "$(CFG)" == "disdraw - Win32 Debug win95" || "$(CFG)" ==\
 "disdraw - Win32 ALPHA Debug" || "$(CFG)" == "disdraw - Win32 ALPHA Release"
SOURCE=.\disdraw.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

DEP_CPP_DISDR=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	

"$(INTDIR)\disdraw.obj" : $(SOURCE) $(DEP_CPP_DISDR) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

DEP_CPP_DISDR=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\disdraw.obj"	"$(INTDIR)\disdraw.sbr" : $(SOURCE) $(DEP_CPP_DISDR)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

DEP_CPP_DISDR=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\disdraw.obj" : $(SOURCE) $(DEP_CPP_DISDR) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

DEP_CPP_DISDR=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\disdraw.obj" : $(SOURCE) $(DEP_CPP_DISDR) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_DISDR=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\disdraw.obj"	"$(INTDIR)\disdraw.sbr" : $(SOURCE) $(DEP_CPP_DISDR)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_DISDR=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\disdraw.obj" : $(SOURCE) $(DEP_CPP_DISDR) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ENDIF 

SOURCE=.\disdraw.rc
DEP_RSC_DISDRA=\
	".\res\disdraw.ico"\
	".\res\disdraw.rc2"\
	

"$(INTDIR)\disdraw.res" : $(SOURCE) $(DEP_RSC_DISDRA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\drawarea.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

DEP_CPP_DRAWA=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	

"$(INTDIR)\drawarea.obj" : $(SOURCE) $(DEP_CPP_DRAWA) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

DEP_CPP_DRAWA=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawarea.obj"	"$(INTDIR)\drawarea.sbr" : $(SOURCE) $(DEP_CPP_DRAWA)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

DEP_CPP_DRAWA=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawarea.obj" : $(SOURCE) $(DEP_CPP_DRAWA) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

DEP_CPP_DRAWA=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawarea.obj" : $(SOURCE) $(DEP_CPP_DRAWA) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_DRAWA=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawarea.obj"	"$(INTDIR)\drawarea.sbr" : $(SOURCE) $(DEP_CPP_DRAWA)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_DRAWA=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawarea.obj" : $(SOURCE) $(DEP_CPP_DRAWA) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ENDIF 

SOURCE=.\drawdlg.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

DEP_CPP_DRAWD=\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	

"$(INTDIR)\drawdlg.obj" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

DEP_CPP_DRAWD=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawdlg.obj"	"$(INTDIR)\drawdlg.sbr" : $(SOURCE) $(DEP_CPP_DRAWD)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

DEP_CPP_DRAWD=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawdlg.obj" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

DEP_CPP_DRAWD=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawdlg.obj" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_DRAWD=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawdlg.obj"	"$(INTDIR)\drawdlg.sbr" : $(SOURCE) $(DEP_CPP_DRAWD)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_DRAWD=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\drawarea.h"\
	".\drawdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\drawdlg.obj" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ENDIF 

SOURCE=.\logindlg.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

DEP_CPP_LOGIN=\
	".\disdraw.h"\
	".\logindlg.h"\
	

"$(INTDIR)\logindlg.obj" : $(SOURCE) $(DEP_CPP_LOGIN) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

DEP_CPP_LOGIN=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\logindlg.obj"	"$(INTDIR)\logindlg.sbr" : $(SOURCE) $(DEP_CPP_LOGIN)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

DEP_CPP_LOGIN=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\logindlg.obj" : $(SOURCE) $(DEP_CPP_LOGIN) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

DEP_CPP_LOGIN=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\logindlg.obj" : $(SOURCE) $(DEP_CPP_LOGIN) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_LOGIN=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\logindlg.obj"	"$(INTDIR)\logindlg.sbr" : $(SOURCE) $(DEP_CPP_LOGIN)\
 "$(INTDIR)" "$(INTDIR)\disdraw.pch"


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_LOGIN=\
	"..\..\..\..\include\mq.h"\
	".\disdraw.h"\
	".\logindlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\logindlg.obj" : $(SOURCE) $(DEP_CPP_LOGIN) "$(INTDIR)"\
 "$(INTDIR)\disdraw.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "disdraw - Win32 Release"

DEP_CPP_STDAF=\
	"..\..\..\..\include\basetsd.h"\
	"..\..\..\..\include\mq.h"\
	"..\..\..\..\include\msxml.h"\
	"..\..\..\..\include\propidl.h"\
	"..\..\..\..\include\rpcasync.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG"\
 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\disdraw.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\disdraw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug"

DEP_CPP_STDAF=\
	"..\..\..\..\include\mq.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\disdraw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\disdraw.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "disdraw - Win32 Release win95"

DEP_CPP_STDAF=\
	"..\..\..\..\include\mq.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D "NDEBUG"\
 /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\disdraw.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\disdraw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "disdraw - Win32 Debug win95"

DEP_CPP_STDAF=\
	"..\..\..\..\include\mq.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)\disdraw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\disdraw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Debug"

DEP_CPP_STDAF=\
	"..\..\..\..\include\mq.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\..\..\include" /D "WIN32"\
 /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\disdraw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /MDd /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\disdraw.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "disdraw - Win32 ALPHA Release"

DEP_CPP_STDAF=\
	"..\..\..\..\include\mq.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /GX /Zi /O2 /I "..\..\..\..\include" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\disdraw.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\disdraw.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

