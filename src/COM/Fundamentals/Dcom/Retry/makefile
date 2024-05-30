# Microsoft Developer Studio Generated NMAKE File, Based on DCOM_Retry_Client.dsp
!IF "$(CFG)" == ""
CFG=DCOM_Retry_Client - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DCOM_Retry_Client - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "DCOM_Retry_Client - Win32 Release" && "$(CFG)" != "DCOM_Retry_Client - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DCOM_Retry_Client.mak" CFG="DCOM_Retry_Client - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DCOM_Retry_Client - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "DCOM_Retry_Client - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DCOM_Retry_Client - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\DCOM_Retry_Client.exe"


CLEAN :
	-@erase "$(INTDIR)\DCOM_Retry_Client.obj"
	-@erase "$(INTDIR)\DCOM_Retry_Client.pch"
	-@erase "$(INTDIR)\COMMethodCaller.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DCOM_Retry_Client.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DCOM_Retry_Client.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DCOM_Retry_Client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\DCOM_Retry_Client.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\DCOM_Retry_Client.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DCOM_Retry_Client.obj" \
	"$(INTDIR)\COMMethodCaller.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DCOM_Retry_Client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DCOM_Retry_Client - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\DCOM_Retry_Client.exe"


CLEAN :
	-@erase "$(INTDIR)\DCOM_Retry_Client.obj"
	-@erase "$(INTDIR)\DCOM_Retry_Client.pch"
	-@erase "$(INTDIR)\COMMethodCaller.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DCOM_Retry_Client.exe"
	-@erase "$(OUTDIR)\DCOM_Retry_Client.ilk"
	-@erase "$(OUTDIR)\DCOM_Retry_Client.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DCOM_Retry_Client.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DCOM_Retry_Client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\DCOM_Retry_Client.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\DCOM_Retry_Client.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DCOM_Retry_Client.obj" \
	"$(INTDIR)\COMMethodCaller.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DCOM_Retry_Client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("DCOM_Retry_Client.dep")
!INCLUDE "DCOM_Retry_Client.dep"
!ELSE 
!MESSAGE Warning: cannot find "DCOM_Retry_Client.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DCOM_Retry_Client - Win32 Release" || "$(CFG)" == "DCOM_Retry_Client - Win32 Debug"
SOURCE=.\DCOM_Retry_Client.cpp

"$(INTDIR)\DCOM_Retry_Client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DCOM_Retry_Client.pch"


SOURCE=.\COMMethodCaller.cpp

!IF  "$(CFG)" == "DCOM_Retry_Client - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DCOM_Retry_Client.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\COMMethodCaller.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DCOM_Retry_Client.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DCOM_Retry_Client - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\COMMethodCaller.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DCOM_Retry_Client - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DCOM_Retry_Client.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DCOM_Retry_Client.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DCOM_Retry_Client - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DCOM_Retry_Client.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DCOM_Retry_Client.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

