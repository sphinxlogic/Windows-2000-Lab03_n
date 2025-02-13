# Microsoft Developer Studio Generated NMAKE File, Based on account.dsp
!IF "$(CFG)" == ""
CFG=Account - Win32 Alpha Debug
!MESSAGE No configuration specified. Defaulting to Account - Win32 Alpha Debug.
!ENDIF 

!IF "$(CFG)" != "Account - Win32 Release" && "$(CFG)" !=\
 "Account - Win32 Debug" && "$(CFG)" != "Account - Win32 Unicode Release" &&\
 "$(CFG)" != "Account - Win32 Unicode Debug" && "$(CFG)" !=\
 "Account - Win32 Alpha Release" && "$(CFG)" != "Account - Win32 Alpha Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "account.mak" CFG="Account - Win32 Alpha Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Account - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Alpha Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Account - Win32 Alpha Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Account - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Vcacct.dll" "$(OUTDIR)\account.bsc"

!ELSE 

ALL : "$(OUTDIR)\Vcacct.dll" "$(OUTDIR)\account.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\GetReceipt.obj"
	-@erase "$(INTDIR)\GetReceipt.sbr"
	-@erase "$(INTDIR)\MoveMoney.obj"
	-@erase "$(INTDIR)\MoveMoney.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UpdateReceipt.obj"
	-@erase "$(INTDIR)\UpdateReceipt.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\account.bsc"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /Zi /O2 /Ob2 /I "..\..\include" /D "NDEBUG" /D\
 "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\GetReceipt.sbr" \
	"$(INTDIR)\MoveMoney.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UpdateReceipt.sbr"

"$(OUTDIR)\account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Vcacct.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib"\
 /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib"\
 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\Account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetReceipt.obj" \
	"$(INTDIR)\MoveMoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdateReceipt.obj"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Vcacct.dll" "$(OUTDIR)\account.bsc"

!ELSE 

ALL : "$(OUTDIR)\Vcacct.dll" "$(OUTDIR)\account.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\GetReceipt.obj"
	-@erase "$(INTDIR)\GetReceipt.sbr"
	-@erase "$(INTDIR)\MoveMoney.obj"
	-@erase "$(INTDIR)\MoveMoney.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UpdateReceipt.obj"
	-@erase "$(INTDIR)\UpdateReceipt.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\account.bsc"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.ilk"
	-@erase "$(OUTDIR)\Vcacct.lib"
	-@erase "$(OUTDIR)\Vcacct.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "_DEBUG" /D\
 "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\GetReceipt.sbr" \
	"$(INTDIR)\MoveMoney.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UpdateReceipt.sbr"

"$(OUTDIR)\account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Vcacct.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib"\
 /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib"\
 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\Account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetReceipt.obj" \
	"$(INTDIR)\MoveMoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdateReceipt.obj"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\.\ReleaseU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\vcacct.dll" "$(OUTDIR)\account.bsc"

!ELSE 

ALL : "$(OUTDIR)\vcacct.dll" "$(OUTDIR)\account.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\GetReceipt.obj"
	-@erase "$(INTDIR)\GetReceipt.sbr"
	-@erase "$(INTDIR)\MoveMoney.obj"
	-@erase "$(INTDIR)\MoveMoney.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UpdateReceipt.obj"
	-@erase "$(INTDIR)\UpdateReceipt.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\account.bsc"
	-@erase "$(OUTDIR)\vcacct.dll"
	-@erase "$(OUTDIR)\vcacct.exp"
	-@erase "$(OUTDIR)\vcacct.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D\
 "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\ReleaseU/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\GetReceipt.sbr" \
	"$(INTDIR)\MoveMoney.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UpdateReceipt.sbr"

"$(OUTDIR)\account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\vcacct.pdb" /machine:I386 /nodefaultlib:"msvcrt.lib"\
 /def:".\Account.def" /out:"$(OUTDIR)\vcacct.dll" /implib:"$(OUTDIR)\vcacct.lib"\
 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\Account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetReceipt.obj" \
	"$(INTDIR)\MoveMoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdateReceipt.obj"

"$(OUTDIR)\vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\vcacct.dll" "$(OUTDIR)\account.bsc"

!ELSE 

ALL : "$(OUTDIR)\vcacct.dll" "$(OUTDIR)\account.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\GetReceipt.obj"
	-@erase "$(INTDIR)\GetReceipt.sbr"
	-@erase "$(INTDIR)\MoveMoney.obj"
	-@erase "$(INTDIR)\MoveMoney.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UpdateReceipt.obj"
	-@erase "$(INTDIR)\UpdateReceipt.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\account.bsc"
	-@erase "$(OUTDIR)\vcacct.dll"
	-@erase "$(OUTDIR)\vcacct.exp"
	-@erase "$(OUTDIR)\vcacct.ilk"
	-@erase "$(OUTDIR)\vcacct.lib"
	-@erase "$(OUTDIR)\vcacct.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "_DEBUG" /D\
 "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\DebugU/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\GetReceipt.sbr" \
	"$(INTDIR)\MoveMoney.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UpdateReceipt.sbr"

"$(OUTDIR)\account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\vcacct.pdb" /debug /machine:I386 /nodefaultlib:"msvcrt.lib"\
 /def:".\Account.def" /out:"$(OUTDIR)\vcacct.dll" /implib:"$(OUTDIR)\vcacct.lib"\
 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\Account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetReceipt.obj" \
	"$(INTDIR)\MoveMoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdateReceipt.obj"

"$(OUTDIR)\vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

OUTDIR=.\AlphaRelease
INTDIR=.\AlphaRelease
# Begin Custom Macros
OutDir=.\AlphaRelease
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Vcacct.dll"

!ELSE 

ALL : "$(OUTDIR)\Vcacct.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetReceipt.obj"
	-@erase "$(INTDIR)\MoveMoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdateReceipt.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\AlphaRelease/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mtxguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /pdb:"$(OUTDIR)\Vcacct.pdb" /machine:ALPHA\
 /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib"\
 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\Account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetReceipt.obj" \
	"$(INTDIR)\MoveMoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdateReceipt.obj"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

OUTDIR=.\AlphaDebug
INTDIR=.\AlphaDebug
# Begin Custom Macros
OutDir=.\AlphaDebug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Vcacct.dll"

!ELSE 

ALL : "$(OUTDIR)\Vcacct.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetReceipt.obj"
	-@erase "$(INTDIR)\MoveMoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdateReceipt.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.lib"
	-@erase "$(OUTDIR)\Vcacct.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /MTd /c 
CPP_OBJS=.\AlphaDebug/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mtxguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /pdb:"$(OUTDIR)\Vcacct.pdb" /debug /machine:ALPHA\
 /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib"\
 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\Account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetReceipt.obj" \
	"$(INTDIR)\MoveMoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdateReceipt.obj"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Account - Win32 Release" || "$(CFG)" ==\
 "Account - Win32 Debug" || "$(CFG)" == "Account - Win32 Unicode Release" ||\
 "$(CFG)" == "Account - Win32 Unicode Debug" || "$(CFG)" ==\
 "Account - Win32 Alpha Release" || "$(CFG)" == "Account - Win32 Alpha Debug"
SOURCE=.\Account.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

DEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) $(DEP_CPP_ACCOU)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

DEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) $(DEP_CPP_ACCOU)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

DEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) $(DEP_CPP_ACCOU)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

DEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) $(DEP_CPP_ACCOU)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\Account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_ACCOU=\
	".\Account.h"\
	".\Account_i.c"\
	".\CACCOUNT.H"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\Account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h" ".\Account_i.c"


!ENDIF 

SOURCE=.\Account.idl

!IF  "$(CFG)" == "Account - Win32 Release"

InputPath=.\Account.idl

"Account.tlb"	"Account.h"	"Account_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl Account.idl

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

InputPath=.\Account.idl

"Account.tlb"	"Account.h"	"Account_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl Account.idl

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

InputPath=.\Account.idl

"Account.tlb"	"Account.h"	"Account_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl Account.idl

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

InputPath=.\Account.idl

"Account.tlb"	"Account.h"	"Account_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl Account.idl

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

InputPath=.\Account.idl

"Account.tlb"	"Account.h"	"Account_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl Account.idl

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

InputPath=.\Account.idl

"Account.tlb"	"Account.h"	"Account_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl Account.idl

!ENDIF 

SOURCE=.\Account.rc
DEP_RSC_ACCOUN=\
	".\Account.tlb"\
	".\CACCOUNT.RGS"\
	".\GetReceipt.rgs"\
	".\movemoney.rgs"\
	".\updatere.bin"\
	".\UpdateReceipt.rgs"\
	

"$(INTDIR)\Account.res" : $(SOURCE) $(DEP_RSC_ACCOUN) "$(INTDIR)"\
 ".\Account.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CAccount.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

DEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\CACCOUNT.H"\
	

"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) $(DEP_CPP_CACCO)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

DEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\CACCOUNT.H"\
	

"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) $(DEP_CPP_CACCO)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

DEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\CACCOUNT.H"\
	

"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) $(DEP_CPP_CACCO)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

DEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\CACCOUNT.H"\
	

"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) $(DEP_CPP_CACCO)\
 "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\CACCOUNT.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_CACCO=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\CACCOUNT.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ENDIF 

SOURCE=.\GetReceipt.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

DEP_CPP_GETRE=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\GetReceipt.obj"	"$(INTDIR)\GetReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_GETRE) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

DEP_CPP_GETRE=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\GetReceipt.obj"	"$(INTDIR)\GetReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_GETRE) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

DEP_CPP_GETRE=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\GetReceipt.obj"	"$(INTDIR)\GetReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_GETRE) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

DEP_CPP_GETRE=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\GetReceipt.obj"	"$(INTDIR)\GetReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_GETRE) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_GETRE=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\GetReceipt.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_GETRE=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\GetReceipt.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ENDIF 

SOURCE=.\MoveMoney.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

DEP_CPP_MOVEM=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	

"$(INTDIR)\MoveMoney.obj"	"$(INTDIR)\MoveMoney.sbr" : $(SOURCE)\
 $(DEP_CPP_MOVEM) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

DEP_CPP_MOVEM=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	

"$(INTDIR)\MoveMoney.obj"	"$(INTDIR)\MoveMoney.sbr" : $(SOURCE)\
 $(DEP_CPP_MOVEM) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

DEP_CPP_MOVEM=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	

"$(INTDIR)\MoveMoney.obj"	"$(INTDIR)\MoveMoney.sbr" : $(SOURCE)\
 $(DEP_CPP_MOVEM) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

DEP_CPP_MOVEM=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	

"$(INTDIR)\MoveMoney.obj"	"$(INTDIR)\MoveMoney.sbr" : $(SOURCE)\
 $(DEP_CPP_MOVEM) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_MOVEM=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	

"$(INTDIR)\MoveMoney.obj" : $(SOURCE) $(DEP_CPP_MOVEM) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_MOVEM=\
	".\Account.h"\
	".\GetReceipt.h"\
	".\movemoney.h"\
	".\STDAFX.H"\
	

"$(INTDIR)\MoveMoney.obj" : $(SOURCE) $(DEP_CPP_MOVEM) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

DEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\STDAFX.H"\
	
CPP_SWITCHES=/nologo /MT /W3 /GX /Zi /O2 /Ob2 /I "..\..\include" /D "NDEBUG" /D\
 "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\account.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

DEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\STDAFX.H"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "_DEBUG" /D\
 "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\account.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

DEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\STDAFX.H"\
	
CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS"\
 /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\account.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\STDAFX.H"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "_DEBUG" /D\
 "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\account.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\STDAFX.H"\
	
CPP_SWITCHES=/nologo /MT /Gt0 /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_STDAF=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\STDAFX.H"\
	
CPP_SWITCHES=/nologo /Gt0 /W3 /GX /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /MTd /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\UpdateReceipt.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

DEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\UpdateReceipt.obj"	"$(INTDIR)\UpdateReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_UPDAT) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

DEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\UpdateReceipt.obj"	"$(INTDIR)\UpdateReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_UPDAT) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

DEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\UpdateReceipt.obj"	"$(INTDIR)\UpdateReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_UPDAT) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

DEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\UpdateReceipt.obj"	"$(INTDIR)\UpdateReceipt.sbr" : $(SOURCE)\
 $(DEP_CPP_UPDAT) "$(INTDIR)" "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

DEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\UpdateReceipt.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

DEP_CPP_UPDAT=\
	"..\..\include\adoid.h"\
	"..\..\include\adoint.h"\
	".\Account.h"\
	".\STDAFX.H"\
	".\UpdateReceipt.h"\
	

"$(INTDIR)\UpdateReceipt.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\Account.h"


!ENDIF 


!ENDIF 

