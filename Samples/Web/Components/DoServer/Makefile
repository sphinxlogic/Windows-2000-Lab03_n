# Microsoft Developer Studio Generated NMAKE File, Based on DOServer.dsp
!IF "$(CFG)" == ""
CFG=DOServer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DOServer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DOServer - Win32 Release" && "$(CFG)" != "DOServer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DOServer.mak" CFG="DOServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DOServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DOServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DOServer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\DOServer.exe"


CLEAN :
	-@erase "$(INTDIR)\clsfact.obj"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\doserver.obj"
	-@erase "$(INTDIR)\doserver.res"
	-@erase "$(INTDIR)\oipaobj.obj"
	-@erase "$(INTDIR)\oipobj.obj"
	-@erase "$(INTDIR)\oledoc.obj"
	-@erase "$(INTDIR)\oledocvw.obj"
	-@erase "$(INTDIR)\oleobj.obj"
	-@erase "$(INTDIR)\perfile.obj"
	-@erase "$(INTDIR)\perstor.obj"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DOServer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\DOServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\doserver.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DOServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\DOServer.pdb" /machine:I386 /out:"$(OUTDIR)\DOServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\clsfact.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\doserver.obj" \
	"$(INTDIR)\oipaobj.obj" \
	"$(INTDIR)\oipobj.obj" \
	"$(INTDIR)\oledoc.obj" \
	"$(INTDIR)\oledocvw.obj" \
	"$(INTDIR)\oleobj.obj" \
	"$(INTDIR)\perfile.obj" \
	"$(INTDIR)\perstor.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\doserver.res"

"$(OUTDIR)\DOServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\DOServer.exe" "$(OUTDIR)\DOServer.bsc"


CLEAN :
	-@erase "$(INTDIR)\clsfact.obj"
	-@erase "$(INTDIR)\clsfact.sbr"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dataobj.sbr"
	-@erase "$(INTDIR)\doserver.obj"
	-@erase "$(INTDIR)\doserver.res"
	-@erase "$(INTDIR)\doserver.sbr"
	-@erase "$(INTDIR)\oipaobj.obj"
	-@erase "$(INTDIR)\oipaobj.sbr"
	-@erase "$(INTDIR)\oipobj.obj"
	-@erase "$(INTDIR)\oipobj.sbr"
	-@erase "$(INTDIR)\oledoc.obj"
	-@erase "$(INTDIR)\oledoc.sbr"
	-@erase "$(INTDIR)\oledocvw.obj"
	-@erase "$(INTDIR)\oledocvw.sbr"
	-@erase "$(INTDIR)\oleobj.obj"
	-@erase "$(INTDIR)\oleobj.sbr"
	-@erase "$(INTDIR)\perfile.obj"
	-@erase "$(INTDIR)\perfile.sbr"
	-@erase "$(INTDIR)\perstor.obj"
	-@erase "$(INTDIR)\perstor.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DOServer.bsc"
	-@erase "$(OUTDIR)\DOServer.exe"
	-@erase "$(OUTDIR)\DOServer.ilk"
	-@erase "$(OUTDIR)\DOServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\DOServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\doserver.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DOServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\clsfact.sbr" \
	"$(INTDIR)\dataobj.sbr" \
	"$(INTDIR)\doserver.sbr" \
	"$(INTDIR)\oipaobj.sbr" \
	"$(INTDIR)\oipobj.sbr" \
	"$(INTDIR)\oledoc.sbr" \
	"$(INTDIR)\oledocvw.sbr" \
	"$(INTDIR)\oleobj.sbr" \
	"$(INTDIR)\perfile.sbr" \
	"$(INTDIR)\perstor.sbr" \
	"$(INTDIR)\utils.sbr"

"$(OUTDIR)\DOServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\DOServer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\DOServer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\clsfact.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\doserver.obj" \
	"$(INTDIR)\oipaobj.obj" \
	"$(INTDIR)\oipobj.obj" \
	"$(INTDIR)\oledoc.obj" \
	"$(INTDIR)\oledocvw.obj" \
	"$(INTDIR)\oleobj.obj" \
	"$(INTDIR)\perfile.obj" \
	"$(INTDIR)\perstor.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\doserver.res"

"$(OUTDIR)\DOServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("DOServer.dep")
!INCLUDE "DOServer.dep"
!ELSE 
!MESSAGE Warning: cannot find "DOServer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DOServer - Win32 Release" || "$(CFG)" == "DOServer - Win32 Debug"
SOURCE=.\clsfact.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\clsfact.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\clsfact.obj"	"$(INTDIR)\clsfact.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dataobj.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\dataobj.obj"	"$(INTDIR)\dataobj.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\doserver.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\doserver.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\doserver.obj"	"$(INTDIR)\doserver.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\doserver.rc

"$(INTDIR)\doserver.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\oipaobj.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\oipaobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\oipaobj.obj"	"$(INTDIR)\oipaobj.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\oipobj.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\oipobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\oipobj.obj"	"$(INTDIR)\oipobj.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\oledoc.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\oledoc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\oledoc.obj"	"$(INTDIR)\oledoc.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\oledocvw.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\oledocvw.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\oledocvw.obj"	"$(INTDIR)\oledocvw.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\oleobj.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\oleobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\oleobj.obj"	"$(INTDIR)\oleobj.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\perfile.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\perfile.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\perfile.obj"	"$(INTDIR)\perfile.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\perstor.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\perstor.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\perstor.obj"	"$(INTDIR)\perstor.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\utils.cpp

!IF  "$(CFG)" == "DOServer - Win32 Release"


"$(INTDIR)\utils.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DOServer - Win32 Debug"


"$(INTDIR)\utils.obj"	"$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

