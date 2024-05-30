# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#
# Microsoft Developer Studio Generated NMAKE File, Based on scardtst.dsp
#

!IF "$(CFG)" == ""
CFG=SCardTst - Win32 Release
!MESSAGE No configuration specified. Defaulting to SCardTst - Win32 Release.
!ENDIF

!IF "$(CFG)" != "SCardTst - Win32 Release" && "$(CFG)" !=\
 "SCardTst - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "scardtst.mak" CFG="SCardTst - Win32 Release"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "SCardTst - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SCardTst - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "SCardTst - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\scardtst.exe"

!ELSE

ALL : "$(OUTDIR)\scardtst.exe"

!ENDIF

CLEAN :
        -@erase "$(INTDIR)\preapp.obj"
        -@erase "$(INTDIR)\scarddg.obj"
        -@erase "$(INTDIR)\SCardTst.obj"
        -@erase "$(INTDIR)\SCardTst.res"
        -@erase "$(INTDIR)\scardwrp.obj"
        -@erase "$(INTDIR)\vc50.idb"
        -@erase "$(OUTDIR)\scardtst.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\scardtst.pch" /YX"preapp.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SCardTst.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\scardtst.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\scardtst.pdb" /machine:I386 /out:"$(OUTDIR)\scardtst.exe"
LINK32_OBJS= \
        "$(INTDIR)\preapp.obj" \
        "$(INTDIR)\scarddg.obj" \
        "$(INTDIR)\SCardTst.obj" \
        "$(INTDIR)\SCardTst.res" \
        "$(INTDIR)\scardwrp.obj"

"$(OUTDIR)\scardtst.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SCardTst - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0"

ALL : "$(OUTDIR)\scardtst.exe"

!ELSE

ALL : "$(OUTDIR)\scardtst.exe"

!ENDIF

CLEAN :
        -@erase "$(INTDIR)\preapp.obj"
        -@erase "$(INTDIR)\scarddg.obj"
        -@erase "$(INTDIR)\SCardTst.obj"
        -@erase "$(INTDIR)\SCardTst.res"
        -@erase "$(INTDIR)\scardwrp.obj"
        -@erase "$(INTDIR)\vc50.idb"
        -@erase "$(INTDIR)\vc50.pdb"
        -@erase "$(OUTDIR)\scardtst.exe"
        -@erase "$(OUTDIR)\scardtst.ilk"
        -@erase "$(OUTDIR)\scardtst.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\scardtst.pch" /YX"preapp.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SCardTst.res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\scardtst.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\scardtst.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\scardtst.exe"
LINK32_OBJS= \
        "$(INTDIR)\preapp.obj" \
        "$(INTDIR)\scarddg.obj" \
        "$(INTDIR)\SCardTst.obj" \
        "$(INTDIR)\SCardTst.res" \
        "$(INTDIR)\scardwrp.obj"

"$(OUTDIR)\scardtst.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "SCardTst - Win32 Release" || "$(CFG)" ==\
 "SCardTst - Win32 Debug"
SOURCE=.\preapp.cpp
DEP_CPP_PREAP=\
        ".\preapp.h"\


"$(INTDIR)\preapp.obj" : $(SOURCE) $(DEP_CPP_PREAP) "$(INTDIR)"


SOURCE=.\scarddg.cpp

!IF  "$(CFG)" == "SCardTst - Win32 Release"

DEP_CPP_SCARD=\
        {$(INCLUDE)}"sspsidl.h"\
        {$(INCLUDE)}"scardwrp.h"\
        {$(INCLUDE)}"scardcom.h"\
        ".\preapp.h"\
        ".\SCardDg.h"\
        ".\SCardTst.h"\


"$(INTDIR)\scarddg.obj" : $(SOURCE) $(DEP_CPP_SCARD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SCardTst - Win32 Debug"


"$(INTDIR)\scarddg.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF

SOURCE=.\SCardTst.cpp

!IF  "$(CFG)" == "SCardTst - Win32 Release"

DEP_CPP_SCARDT=\
        ".\preapp.h"\
        ".\SCardDg.h"\
        ".\SCardTst.h"\


"$(INTDIR)\SCardTst.obj" : $(SOURCE) $(DEP_CPP_SCARDT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SCardTst - Win32 Debug"

DEP_CPP_SCARDT=\
        ".\preapp.h"\
        ".\SCardDg.h"\
        ".\SCardTst.h"\


"$(INTDIR)\SCardTst.obj" : $(SOURCE) $(DEP_CPP_SCARDT) "$(INTDIR)"


!ENDIF

SOURCE=.\SCardTst.rc
DEP_RSC_SCARDTS=\
        ".\res\SCardTst.ico"\
        ".\res\SCardTst.rc2"\


"$(INTDIR)\SCardTst.res" : $(SOURCE) $(DEP_RSC_SCARDTS) "$(INTDIR)"
        $(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\scardcom\cppwrap\scardwrp.cpp

!IF  "$(CFG)" == "SCardTst - Win32 Release"

DEP_CPP_SCARDW=\
        {$(INCLUDE)}"scarddat_i.c"\
        {$(INCLUDE)}"scardmgr_i.c"\
        {$(INCLUDE)}"scardsrv_i.c"\
        {$(INCLUDE)}"sspguid.h"\
        {$(INCLUDE)}"sspsidl.h"\
        {$(INCLUDE)}"wrpguid.h"\
        {$(INCLUDE)}"scardwrp.h"\
        {$(INCLUDE)}"scardcom.h"\
        {$(INCLUDE)}"scardcom_i.c"\
        ".\preapp.h"\


"$(INTDIR)\scardwrp.obj" : $(SOURCE) $(DEP_CPP_SCARDW) "$(INTDIR)"
        $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SCardTst - Win32 Debug"

DEP_CPP_SCARDW=\
        {$(INCLUDE)}"scardwrp.h"\
        ".\preapp.h"\
        {$(INCLUDE)}"scardcom.h"\
        {$(INCLUDE)}"scardcom_i.c"\
        {$(INCLUDE)}"scarddat_i.c"\
        {$(INCLUDE)}"scardmgr_i.c"\
        {$(INCLUDE)}"scardsrv_i.c"\
        {$(INCLUDE)}"sspguid.h"\
        {$(INCLUDE)}"sspsidl.h"\
        {$(INCLUDE)}"wrpguid.h"\


"$(INTDIR)\scardwrp.obj" : $(SOURCE) $(DEP_CPP_SCARDW) "$(INTDIR)"
        $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF


!ENDIF

