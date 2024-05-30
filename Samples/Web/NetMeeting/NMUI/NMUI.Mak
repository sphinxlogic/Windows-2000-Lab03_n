# Microsoft Developer Studio Generated NMAKE File, Based on nmui.dsp
!IF "$(CFG)" == ""
CFG=nmui - Win32 Debug
!MESSAGE No configuration specified. Defaulting to nmui - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "nmui - Win32 Release" && "$(CFG)" != "nmui - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nmui.mak" CFG="nmui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nmui - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nmui - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "nmui - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\nmui.exe"

!ELSE 

ALL : "$(OUTDIR)\nmui.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cCall.obj"
	-@erase "$(INTDIR)\cchan.obj"
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\cData.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\cmd.obj"
	-@erase "$(INTDIR)\cMemb.obj"
	-@erase "$(INTDIR)\cMgr.obj"
	-@erase "$(INTDIR)\cvideo.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\dlg.obj"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\rtns.obj"
	-@erase "$(INTDIR)\sbar.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\nmui.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "STRICT" /D "WIN32" /D\
 "_WINDOWS" /Fp"$(INTDIR)\nmui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\nmui.pdb" /machine:I386\
 /out:"$(OUTDIR)\nmui.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cCall.obj" \
	"$(INTDIR)\cchan.obj" \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\cData.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\cmd.obj" \
	"$(INTDIR)\cMemb.obj" \
	"$(INTDIR)\cMgr.obj" \
	"$(INTDIR)\cvideo.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\dlg.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\rtns.obj" \
	"$(INTDIR)\sbar.obj" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\nmui.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\nmui.exe"

!ELSE 

ALL : "$(OUTDIR)\nmui.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cCall.obj"
	-@erase "$(INTDIR)\cchan.obj"
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\cData.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\cmd.obj"
	-@erase "$(INTDIR)\cMemb.obj"
	-@erase "$(INTDIR)\cMgr.obj"
	-@erase "$(INTDIR)\cvideo.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\dlg.obj"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\rtns.obj"
	-@erase "$(INTDIR)\sbar.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\nmui.exe"
	-@erase "$(OUTDIR)\nmui.ilk"
	-@erase "$(OUTDIR)\nmui.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "DEBUG" /D "_DEBUG" /D "STRICT" /D\
 "WIN32" /D "_WINDOWS" /Fp"$(INTDIR)\nmui.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\nmui.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\nmui.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cCall.obj" \
	"$(INTDIR)\cchan.obj" \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\cData.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\cmd.obj" \
	"$(INTDIR)\cMemb.obj" \
	"$(INTDIR)\cMgr.obj" \
	"$(INTDIR)\cvideo.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\dlg.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\rtns.obj" \
	"$(INTDIR)\sbar.obj" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\nmui.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "nmui - Win32 Release" || "$(CFG)" == "nmui - Win32 Debug"
SOURCE=.\res.rc
DEP_RSC_RES_R=\
	".\audio.ico"\
	".\calling.ico"\
	".\main.ico"\
	".\noaudio.ico"\
	".\novideo.ico"\
	".\speaker.ico"\
	".\toolbar.bmp"\
	".\video.ico"\
	

"$(INTDIR)\res.res" : $(SOURCE) $(DEP_RSC_RES_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\cCall.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CCALL=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cCall.obj" : $(SOURCE) $(DEP_CPP_CCALL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CCALL=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cCall.obj" : $(SOURCE) $(DEP_CPP_CCALL) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cchan.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CCHAN=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cchan.obj" : $(SOURCE) $(DEP_CPP_CCHAN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CCHAN=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cchan.obj" : $(SOURCE) $(DEP_CPP_CCHAN) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cConf.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CCONF=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cConf.obj" : $(SOURCE) $(DEP_CPP_CCONF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CCONF=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cConf.obj" : $(SOURCE) $(DEP_CPP_CCONF) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cData.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CDATA=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cData.obj" : $(SOURCE) $(DEP_CPP_CDATA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CDATA=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cData.obj" : $(SOURCE) $(DEP_CPP_CDATA) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\clUtil.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CLUTI=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\clUtil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CLUTI=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\clUtil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cmd.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CMD_C=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cmd.obj" : $(SOURCE) $(DEP_CPP_CMD_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CMD_C=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cmd.obj" : $(SOURCE) $(DEP_CPP_CMD_C) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cMemb.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CMEMB=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cMemb.obj" : $(SOURCE) $(DEP_CPP_CMEMB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CMEMB=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cMemb.obj" : $(SOURCE) $(DEP_CPP_CMEMB) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cMgr.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CMGR_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cMgr.obj" : $(SOURCE) $(DEP_CPP_CMGR_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CMGR_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cMgr.obj" : $(SOURCE) $(DEP_CPP_CMGR_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cvideo.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_CVIDE=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cvideo.obj" : $(SOURCE) $(DEP_CPP_CVIDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_CVIDE=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cvideo.obj" : $(SOURCE) $(DEP_CPP_CVIDE) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\debug.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_DEBUG=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_DEBUG=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\dlg.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_DLG_C=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\dlg.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_DLG_C=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\dlg.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\imsconf2.c

"$(INTDIR)\imsconf2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\init.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_INIT_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\init.obj" : $(SOURCE) $(DEP_CPP_INIT_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_INIT_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\init.obj" : $(SOURCE) $(DEP_CPP_INIT_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_MAIN_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_MAIN_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\msg.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_MSG_C=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_MSG_C=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\rtns.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_RTNS_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\rtns.obj" : $(SOURCE) $(DEP_CPP_RTNS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_RTNS_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\rtns.obj" : $(SOURCE) $(DEP_CPP_RTNS_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\sbar.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_SBAR_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\sbar.obj" : $(SOURCE) $(DEP_CPP_SBAR_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_SBAR_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\sbar.obj" : $(SOURCE) $(DEP_CPP_SBAR_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\util.cpp

!IF  "$(CFG)" == "nmui - Win32 Release"

DEP_CPP_UTIL_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

DEP_CPP_UTIL_=\
	".\cCall.h"\
	".\cChan.h"\
	".\cConf.h"\
	".\cData.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cMgr.h"\
	".\cVideo.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\IMSCONF2.IDL

!IF  "$(CFG)" == "nmui - Win32 Release"

!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

TargetDir=.\Debug
InputPath=.\IMSCONF2.IDL
InputName=IMSCONF2

".\$(InputName).h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata\
 $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header\
 $(InputName).h /iid $(InputName).c $(InputPath)

!ENDIF 


!ENDIF 

