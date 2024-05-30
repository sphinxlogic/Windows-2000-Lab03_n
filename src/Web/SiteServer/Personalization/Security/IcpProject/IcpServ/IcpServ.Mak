# Microsoft Developer Studio Generated NMAKE File, Based on icpserv.dsp
!IF "$(CFG)" == ""
CFG=icpserv - Win32 Debug
!MESSAGE No configuration specified. Defaulting to icpserv - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "icpserv - Win32 Release" && "$(CFG)" !=\
 "icpserv - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "icpserv.mak" CFG="icpserv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "icpserv - Win32 Release" (based on "Win32 ($(CPU)) Console Application")
!MESSAGE "icpserv - Win32 Debug" (based on "Win32 ($(CPU)) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "icpserv - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\icpserv.exe"

!ELSE 

ALL : "$(OUTDIR)\icpserv.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\icp_serv.obj"
	-@erase "$(INTDIR)\proc_msg.obj"
	-@erase "$(INTDIR)\s_foricp.obj"
	-@erase "$(INTDIR)\ssthread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\icpserv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "_MBCS" /D "SECURITY_WIN32" /D "NT_CLIENT" /Fp"$(INTDIR)\icpserv.pch" /YX\
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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\icpserv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\icpserv.pdb" /machine:$(CPU) /out:"$(OUTDIR)\icpserv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\icp_serv.obj" \
	"$(INTDIR)\proc_msg.obj" \
	"$(INTDIR)\s_foricp.obj" \
	"$(INTDIR)\ssthread.obj"

"$(OUTDIR)\icpserv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "icpserv - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\icpserv.exe"

!ELSE 

ALL : "$(OUTDIR)\icpserv.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\icp_serv.obj"
	-@erase "$(INTDIR)\proc_msg.obj"
	-@erase "$(INTDIR)\s_foricp.obj"
	-@erase "$(INTDIR)\ssthread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\icpserv.exe"
	-@erase "$(OUTDIR)\icpserv.ilk"
	-@erase "$(OUTDIR)\icpserv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "_MBCS" /D "SECURITY_WIN32" /D "NT_CLIENT" /Fp"$(INTDIR)\icpserv.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\icpserv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\icpserv.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\icpserv.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\icp_serv.obj" \
	"$(INTDIR)\proc_msg.obj" \
	"$(INTDIR)\s_foricp.obj" \
	"$(INTDIR)\ssthread.obj"

"$(OUTDIR)\icpserv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "icpserv - Win32 Release" || "$(CFG)" ==\
 "icpserv - Win32 Debug"
SOURCE=.\icp_serv.c

!IF  "$(CFG)" == "icpserv - Win32 Release"

DEP_CPP_ICP_S=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\icp_serv.obj" : $(SOURCE) $(DEP_CPP_ICP_S) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "icpserv - Win32 Debug"

DEP_CPP_ICP_S=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\icp_serv.obj" : $(SOURCE) $(DEP_CPP_ICP_S) "$(INTDIR)"


!ENDIF 

SOURCE=.\proc_msg.c

!IF  "$(CFG)" == "icpserv - Win32 Release"

DEP_CPP_PROC_=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\proc_msg.obj" : $(SOURCE) $(DEP_CPP_PROC_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "icpserv - Win32 Debug"

DEP_CPP_PROC_=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\proc_msg.obj" : $(SOURCE) $(DEP_CPP_PROC_) "$(INTDIR)"


!ENDIF 

SOURCE=.\s_foricp.c

!IF  "$(CFG)" == "icpserv - Win32 Release"

DEP_CPP_S_FOR=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\s_foricp.obj" : $(SOURCE) $(DEP_CPP_S_FOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "icpserv - Win32 Debug"

DEP_CPP_S_FOR=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\s_foricp.obj" : $(SOURCE) $(DEP_CPP_S_FOR) "$(INTDIR)"


!ENDIF 

SOURCE=.\ssthread.c

!IF  "$(CFG)" == "icpserv - Win32 Release"

DEP_CPP_SSTHR=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\ssthread.obj" : $(SOURCE) $(DEP_CPP_SSTHR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "icpserv - Win32 Debug"

DEP_CPP_SSTHR=\
	"..\include\commdef.h"\
	".\all_incl.h"\
	".\icp_serv.h"\
	{$(INCLUDE)}"sspi.h"\
	

"$(INTDIR)\ssthread.obj" : $(SOURCE) $(DEP_CPP_SSTHR) "$(INTDIR)"


!ENDIF 


!ENDIF 

