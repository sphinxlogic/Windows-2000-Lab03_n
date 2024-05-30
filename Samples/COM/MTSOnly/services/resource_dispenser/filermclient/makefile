# Microsoft Developer Studio Generated NMAKE File, Based on FileRmClient.dsp
!IF "$(CFG)" == ""
CFG=FileRmClient - Win32 Release
!MESSAGE No configuration specified. Defaulting to FileRmClient - Win32\
 Release.
!ENDIF 

!IF "$(CFG)" != "FileRmClient - Win32 Release" && "$(CFG)" !=\
 "FileRmClient - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FileRmClient.mak" CFG="FileRmClient - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FileRmClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FileRmClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FileRmClient.exe" "$(OUTDIR)\FileRmClient.tlb"

!ELSE 

ALL : "$(OUTDIR)\FileRmClient.exe" "$(OUTDIR)\FileRmClient.tlb"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cpicturectl1.obj"
	-@erase "$(INTDIR)\FileRmClient.obj"
	-@erase "$(INTDIR)\FileRmClient.pch"
	-@erase "$(INTDIR)\FileRmClient.res"
	-@erase "$(INTDIR)\FileRmClient.tlb"
	-@erase "$(INTDIR)\FileRmClientDlg.obj"
	-@erase "$(INTDIR)\picture1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\FileRmClient.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FileRmClient.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FileRmClient.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FileRmClient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\FileRmClient.pdb" /machine:I386\
 /out:"$(OUTDIR)\FileRmClient.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cpicturectl1.obj" \
	"$(INTDIR)\FileRmClient.obj" \
	"$(INTDIR)\FileRmClient.res" \
	"$(INTDIR)\FileRmClientDlg.obj" \
	"$(INTDIR)\picture1.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FileRmClient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FileRmClient.exe" "$(OUTDIR)\FileRmClient.tlb"\
 "$(OUTDIR)\FileRmClient.bsc"

!ELSE 

ALL : "$(OUTDIR)\FileRmClient.exe" "$(OUTDIR)\FileRmClient.tlb"\
 "$(OUTDIR)\FileRmClient.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cpicturectl1.obj"
	-@erase "$(INTDIR)\cpicturectl1.sbr"
	-@erase "$(INTDIR)\FileRmClient.obj"
	-@erase "$(INTDIR)\FileRmClient.pch"
	-@erase "$(INTDIR)\FileRmClient.res"
	-@erase "$(INTDIR)\FileRmClient.sbr"
	-@erase "$(INTDIR)\FileRmClient.tlb"
	-@erase "$(INTDIR)\FileRmClientDlg.obj"
	-@erase "$(INTDIR)\FileRmClientDlg.sbr"
	-@erase "$(INTDIR)\picture1.obj"
	-@erase "$(INTDIR)\picture1.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\FileRmClient.bsc"
	-@erase "$(OUTDIR)\FileRmClient.exe"
	-@erase "$(OUTDIR)\FileRmClient.ilk"
	-@erase "$(OUTDIR)\FileRmClient.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\FileRmClient.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FileRmClient.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FileRmClient.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cpicturectl1.sbr" \
	"$(INTDIR)\FileRmClient.sbr" \
	"$(INTDIR)\FileRmClientDlg.sbr" \
	"$(INTDIR)\picture1.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\FileRmClient.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\FileRmClient.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\FileRmClient.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cpicturectl1.obj" \
	"$(INTDIR)\FileRmClient.obj" \
	"$(INTDIR)\FileRmClient.res" \
	"$(INTDIR)\FileRmClientDlg.obj" \
	"$(INTDIR)\picture1.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FileRmClient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "FileRmClient - Win32 Release" || "$(CFG)" ==\
 "FileRmClient - Win32 Debug"
SOURCE=.\cpicturectl1.cpp

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

DEP_CPP_CPICT=\
	".\cpicturectl1.h"\
	

"$(INTDIR)\cpicturectl1.obj" : $(SOURCE) $(DEP_CPP_CPICT) "$(INTDIR)"\
 "$(INTDIR)\FileRmClient.pch"


!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

DEP_CPP_CPICT=\
	".\cpicturectl1.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\cpicturectl1.obj"	"$(INTDIR)\cpicturectl1.sbr" : $(SOURCE)\
 $(DEP_CPP_CPICT) "$(INTDIR)" "$(INTDIR)\FileRmClient.pch"


!ENDIF 

SOURCE=.\FileRmClient.cpp

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

DEP_CPP_FILER=\
	".\cpicturectl1.h"\
	".\FileRmClient.h"\
	".\FileRmClientDlg.h"\
	".\resource.h"\
	

"$(INTDIR)\FileRmClient.obj" : $(SOURCE) $(DEP_CPP_FILER) "$(INTDIR)"\
 "$(INTDIR)\FileRmClient.pch"


!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

DEP_CPP_FILER=\
	".\cpicturectl1.h"\
	".\FileRmClient.h"\
	".\FileRmClientDlg.h"\
	".\resource.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FileRmClient.obj"	"$(INTDIR)\FileRmClient.sbr" : $(SOURCE)\
 $(DEP_CPP_FILER) "$(INTDIR)" "$(INTDIR)\FileRmClient.pch"


!ENDIF 

SOURCE=.\FileRmClient.odl

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\FileRmClient.tlb" /mktyplib203\
 /win32 

"$(OUTDIR)\FileRmClient.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\FileRmClient.tlb" /mktyplib203\
 /win32 

"$(OUTDIR)\FileRmClient.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\FileRmClient.rc
DEP_RSC_FILERM=\
	".\FileRmClient.ico"\
	".\FileRmClient.rc2"\
	".\resource.h"\
	

!IF  "$(CFG)" == "FileRmClient - Win32 Release"


"$(INTDIR)\FileRmClient.res" : $(SOURCE) $(DEP_RSC_FILERM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\FileRmClient.res" /i ".\Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"


"$(INTDIR)\FileRmClient.res" : $(SOURCE) $(DEP_RSC_FILERM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\FileRmClient.res" /i ".\Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\FileRmClientDlg.cpp

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

DEP_CPP_FILERMC=\
	"..\..\..\common\inc\cpyimage.h"\
	"..\..\..\common\inc\cpyimage_i.c"\
	".\cpicturectl1.h"\
	".\FileRmClient.h"\
	".\FileRmClientDlg.h"\
	".\resource.h"\
	

"$(INTDIR)\FileRmClientDlg.obj" : $(SOURCE) $(DEP_CPP_FILERMC) "$(INTDIR)"\
 "$(INTDIR)\FileRmClient.pch"


!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

DEP_CPP_FILERMC=\
	"..\..\..\common\inc\cpyimage.h"\
	"..\..\..\common\inc\cpyimage_i.c"\
	".\cpicturectl1.h"\
	".\FileRmClient.h"\
	".\FileRmClientDlg.h"\
	".\resource.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\FileRmClientDlg.obj"	"$(INTDIR)\FileRmClientDlg.sbr" : $(SOURCE)\
 $(DEP_CPP_FILERMC) "$(INTDIR)" "$(INTDIR)\FileRmClient.pch"


!ENDIF 

SOURCE=.\picture1.cpp

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

DEP_CPP_PICTU=\
	".\picture1.h"\
	

"$(INTDIR)\picture1.obj" : $(SOURCE) $(DEP_CPP_PICTU) "$(INTDIR)"\
 "$(INTDIR)\FileRmClient.pch"


!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

DEP_CPP_PICTU=\
	".\picture1.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\picture1.obj"	"$(INTDIR)\picture1.sbr" : $(SOURCE) $(DEP_CPP_PICTU)\
 "$(INTDIR)" "$(INTDIR)\FileRmClient.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FileRmClient - Win32 Release"

DEP_CPP_STDAF=\
	"..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\include\rpcasync.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FileRmClient.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FileRmClient.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FileRmClient - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\FileRmClient.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\FileRmClient.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

