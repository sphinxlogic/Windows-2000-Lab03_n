# Microsoft Developer Studio Generated NMAKE File, Based on mqtrans.dsp
!IF "$(CFG)" == ""
CFG=mqtrans - Win32 Release
!MESSAGE No configuration specified. Defaulting to mqtrans - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "mqtrans - Win32 Release" && "$(CFG)" !=\
 "mqtrans - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mqtrans.mak" CFG="mqtrans - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mqtrans - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mqtrans - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mqtrans - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\mqtrans.exe"

!ELSE 

ALL : "$(OUTDIR)\mqtrans.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\mqtrans.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\mqtrans.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\..\..\include" /D "WIN32" /D\
 "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)\mqtrans.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mqtrans.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\..\..\lib\mqrt.lib ..\..\..\..\lib\xolehlp.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)\mqtrans.pdb" /machine:I386\
 /out:"$(OUTDIR)\mqtrans.exe" 
LINK32_OBJS= \
	"$(INTDIR)\mqtrans.obj"

"$(OUTDIR)\mqtrans.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mqtrans - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\mqtrans.exe"

!ELSE 

ALL : "$(OUTDIR)\mqtrans.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\mqtrans.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\mqtrans.exe"
	-@erase "$(OUTDIR)\mqtrans.ilk"
	-@erase "$(OUTDIR)\mqtrans.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\include" /D "WIN32"\
 /D "_DEBUG" /D "_CONSOLE" /Fp"$(INTDIR)\mqtrans.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mqtrans.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\..\..\lib\mqrt.lib ..\..\..\..\lib\xolehlp.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\mqtrans.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\mqtrans.exe" 
LINK32_OBJS= \
	"$(INTDIR)\mqtrans.obj"

"$(OUTDIR)\mqtrans.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "mqtrans - Win32 Release" || "$(CFG)" ==\
 "mqtrans - Win32 Debug"
SOURCE=.\mqtrans.cpp

!IF  "$(CFG)" == "mqtrans - Win32 Release"

DEP_CPP_MQTRA=\
	"..\..\..\..\include\basetsd.h"\
	"..\..\..\..\include\mq.h"\
	"..\..\..\..\include\msxml.h"\
	"..\..\..\..\include\propidl.h"\
	"..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\include\transact.h"\
	

"$(INTDIR)\mqtrans.obj" : $(SOURCE) $(DEP_CPP_MQTRA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "mqtrans - Win32 Debug"

DEP_CPP_MQTRA=\
	"..\..\..\..\include\mq.h"\
	"..\..\..\..\include\transact.h"\
	

"$(INTDIR)\mqtrans.obj" : $(SOURCE) $(DEP_CPP_MQTRA) "$(INTDIR)"


!ENDIF 


!ENDIF 

