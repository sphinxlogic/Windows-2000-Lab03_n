# ****************************************************************************
# **
# ** Microsoft Site Server v3.00
# ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.
# **
# ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
# ** PURPOSE.
# **
# ****************************************************************************

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
CPU=Alpha
!ELSEIF "$(PROCESSOR_ARCHITECTURE)" == "x86"
CPU=i386
!ELSE
!ERROR Not a supported platform.  Works only on Alpha and x86.
!ENDIF

!IF "$(CFG)" == ""
CFG=Agent - Win32 $(CPU) Unicode Debug
!MESSAGE No configuration specified. Defaulting to Agent - Win32 $(CPU) Unicode\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Agent - Win32 Alpha Unicode Debug" && "$(CFG)" !=\
 "Agent - Win32 Alpha Unicode Release" && "$(CFG)" !=\
 "Agent - Win32 i386 Unicode Debug" && "$(CFG)" !=\
 "Agent - Win32 i386 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Agent.mak" CFG="Agent - Win32 i386 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Agent - Win32 Alpha Unicode Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Agent - Win32 Alpha Unicode Release" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Agent - Win32 i386 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Agent - Win32 i386 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Agent.obj"
	-@erase "$(INTDIR)\Agent.pch"
	-@erase "$(INTDIR)\Agent.res"
	-@erase "$(INTDIR)\AgentPropPage.obj"
	-@erase "$(INTDIR)\AgentPropPageProvider.obj"
	-@erase "$(INTDIR)\DispHelp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SampleAgent.dll"
	-@erase "$(OUTDIR)\SampleAgent.exp"
	-@erase "$(OUTDIR)\SampleAgent.lib"
	-@erase "$(OUTDIR)\SampleAgent.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "_USRDLL" /D "_UNICODE" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE"\
 /Fp"$(INTDIR)\Agent.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /MDd /c 
CPP_OBJS=.\DebugU/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Agent.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Agent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\SampleAgent.pdb"\
 /debug /machine:ALPHA /def:".\Agent.def" /out:"$(OUTDIR)\SampleAgent.dll"\
 /implib:"$(OUTDIR)\SampleAgent.lib" 
DEF_FILE= \
	".\Agent.def"
LINK32_OBJS= \
	"$(INTDIR)\Agent.obj" \
	"$(INTDIR)\Agent.res" \
	"$(INTDIR)\AgentPropPage.obj" \
	"$(INTDIR)\AgentPropPageProvider.obj" \
	"$(INTDIR)\DispHelp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SampleAgent.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\SampleAgent.dll
InputPath=.\DebugU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@-regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Agent.obj"
	-@erase "$(INTDIR)\Agent.pch"
	-@erase "$(INTDIR)\Agent.res"
	-@erase "$(INTDIR)\AgentPropPage.obj"
	-@erase "$(INTDIR)\AgentPropPageProvider.obj"
	-@erase "$(INTDIR)\DispHelp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SampleAgent.dll"
	-@erase "$(OUTDIR)\SampleAgent.exp"
	-@erase "$(OUTDIR)\SampleAgent.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /GX /O1 /D "NDEBUG" /D "_USRDLL" /D "_UNICODE" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE"\
 /Fp"$(INTDIR)\Agent.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 
CPP_OBJS=.\ReleaseU/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Agent.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Agent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /pdb:"$(OUTDIR)\SampleAgent.pdb"\
 /machine:ALPHA /def:".\Agent.def" /out:"$(OUTDIR)\SampleAgent.dll"\
 /implib:"$(OUTDIR)\SampleAgent.lib" 
DEF_FILE= \
	".\Agent.def"
LINK32_OBJS= \
	"$(INTDIR)\Agent.obj" \
	"$(INTDIR)\Agent.res" \
	"$(INTDIR)\AgentPropPage.obj" \
	"$(INTDIR)\AgentPropPageProvider.obj" \
	"$(INTDIR)\DispHelp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SampleAgent.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\SampleAgent.dll
InputPath=.\ReleaseU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@-regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Agent.obj"
	-@erase "$(INTDIR)\Agent.pch"
	-@erase "$(INTDIR)\Agent.res"
	-@erase "$(INTDIR)\AgentPropPage.obj"
	-@erase "$(INTDIR)\AgentPropPageProvider.obj"
	-@erase "$(INTDIR)\DispHelp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SampleAgent.dll"
	-@erase "$(OUTDIR)\SampleAgent.exp"
	-@erase "$(OUTDIR)\SampleAgent.ilk"
	-@erase "$(OUTDIR)\SampleAgent.lib"
	-@erase "$(OUTDIR)\SampleAgent.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32"\
 /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE" /Fp"$(INTDIR)\Agent.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\DebugU/
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Agent.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Agent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\SampleAgent.pdb" /debug /machine:IX86 /def:".\Agent.def"\
 /out:"$(OUTDIR)\SampleAgent.dll" /implib:"$(OUTDIR)\SampleAgent.lib"\
 /pdbtype:sept 
DEF_FILE= \
	".\Agent.def"
LINK32_OBJS= \
	"$(INTDIR)\Agent.obj" \
	"$(INTDIR)\Agent.res" \
	"$(INTDIR)\AgentPropPage.obj" \
	"$(INTDIR)\AgentPropPageProvider.obj" \
	"$(INTDIR)\DispHelp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SampleAgent.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\SampleAgent.dll
InputPath=.\DebugU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@-regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\SampleAgent.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Agent.obj"
	-@erase "$(INTDIR)\Agent.pch"
	-@erase "$(INTDIR)\Agent.res"
	-@erase "$(INTDIR)\AgentPropPage.obj"
	-@erase "$(INTDIR)\AgentPropPageProvider.obj"
	-@erase "$(INTDIR)\DispHelp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SampleAgent.dll"
	-@erase "$(OUTDIR)\SampleAgent.exp"
	-@erase "$(OUTDIR)\SampleAgent.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\Agent.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseU/
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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Agent.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Agent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\SampleAgent.pdb" /machine:IX86 /def:".\Agent.def"\
 /out:"$(OUTDIR)\SampleAgent.dll" /implib:"$(OUTDIR)\SampleAgent.lib" 
DEF_FILE= \
	".\Agent.def"
LINK32_OBJS= \
	"$(INTDIR)\Agent.obj" \
	"$(INTDIR)\Agent.res" \
	"$(INTDIR)\AgentPropPage.obj" \
	"$(INTDIR)\AgentPropPageProvider.obj" \
	"$(INTDIR)\DispHelp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SampleAgent.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseU
TargetPath=.\ReleaseU\SampleAgent.dll
InputPath=.\ReleaseU\SampleAgent.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@-regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "Agent - Win32 Alpha Unicode Debug" || "$(CFG)" ==\
 "Agent - Win32 Alpha Unicode Release" || "$(CFG)" ==\
 "Agent - Win32 i386 Unicode Debug" || "$(CFG)" ==\
 "Agent - Win32 i386 Unicode Release"
SOURCE=.\Agent.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_AGENT=\
	".\Agent.h"\
	".\Agent_i.c"\
	".\AgentPropPageProvider.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Agent.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h" ".\Agent_i.c"


!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

DEP_CPP_AGENT=\
	".\Agent.h"\
	".\Agent_i.c"\
	".\AgentPropPageProvider.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Agent.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h" ".\Agent_i.c"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

DEP_CPP_AGENT=\
	".\Agent.h"\
	".\Agent_i.c"\
	".\AgentPropPageProvider.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Agent.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h" ".\Agent_i.c"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

DEP_CPP_AGENT=\
	".\Agent.h"\
	".\Agent_i.c"\
	".\AgentPropPageProvider.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Agent.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h" ".\Agent_i.c"


!ENDIF 

SOURCE=.\Agent.idl

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

InputPath=.\Agent.idl

".\Agent.tlb"	".\Agent.h"	".\Agent_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

InputPath=.\Agent.idl

".\Agent.tlb"	".\Agent.h"	".\Agent_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

InputPath=.\Agent.idl

".\Agent.tlb"	".\Agent.h"	".\Agent_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

InputPath=.\Agent.idl

".\Agent.tlb"	".\Agent.h"	".\Agent_i.c"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "Agent.h" /iid "Agent_i.c" "Agent.idl"

!ENDIF 

SOURCE=.\Agent.rc
DEP_RSC_AGENT_=\
	".\Agent.tlb"\
	".\AgentPropPageProvider.rgs"\
	

"$(INTDIR)\Agent.res" : $(SOURCE) $(DEP_RSC_AGENT_) "$(INTDIR)" ".\Agent.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\AgentPropPage.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_AGENTP=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPage.obj" : $(SOURCE) $(DEP_CPP_AGENTP) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h"


!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

DEP_CPP_AGENTP=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPage.obj" : $(SOURCE) $(DEP_CPP_AGENTP) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

DEP_CPP_AGENTP=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPage.obj" : $(SOURCE) $(DEP_CPP_AGENTP) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

DEP_CPP_AGENTP=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPage.obj" : $(SOURCE) $(DEP_CPP_AGENTP) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch" ".\Agent.h"


!ENDIF 

SOURCE=.\AgentPropPageProvider.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_AGENTPR=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\AgentPropPageProvider.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPageProvider.obj" : $(SOURCE) $(DEP_CPP_AGENTPR)\
 "$(INTDIR)" "$(INTDIR)\Agent.pch" ".\Agent.h"


!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

DEP_CPP_AGENTPR=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\AgentPropPageProvider.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPageProvider.obj" : $(SOURCE) $(DEP_CPP_AGENTPR)\
 "$(INTDIR)" "$(INTDIR)\Agent.pch" ".\Agent.h"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

DEP_CPP_AGENTPR=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\AgentPropPageProvider.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPageProvider.obj" : $(SOURCE) $(DEP_CPP_AGENTPR)\
 "$(INTDIR)" "$(INTDIR)\Agent.pch" ".\Agent.h"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

DEP_CPP_AGENTPR=\
	".\Agent.h"\
	".\AgentPropPage.h"\
	".\AgentPropPageProvider.h"\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AgentPropPageProvider.obj" : $(SOURCE) $(DEP_CPP_AGENTPR)\
 "$(INTDIR)" "$(INTDIR)\Agent.pch" ".\Agent.h"


!ENDIF 

SOURCE=.\DispHelp.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_DISPH=\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DispHelp.obj" : $(SOURCE) $(DEP_CPP_DISPH) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch"


!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

DEP_CPP_DISPH=\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DispHelp.obj" : $(SOURCE) $(DEP_CPP_DISPH) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

DEP_CPP_DISPH=\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DispHelp.obj" : $(SOURCE) $(DEP_CPP_DISPH) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch"


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

DEP_CPP_DISPH=\
	".\DispHelp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DispHelp.obj" : $(SOURCE) $(DEP_CPP_DISPH) "$(INTDIR)"\
 "$(INTDIR)\Agent.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Agent - Win32 Alpha Unicode Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /Gt0 /W3 /GX /Zi /Od /D "_DEBUG" /D "_USRDLL" /D\
 "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE"\
 /Fp"$(INTDIR)\Agent.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /MDd /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Agent.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Agent - Win32 Alpha Unicode Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /GX /O1 /D "NDEBUG" /D "_USRDLL" /D\
 "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE"\
 /Fp"$(INTDIR)\Agent.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Agent.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE"\
 /Fp"$(INTDIR)\Agent.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Agent.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Agent - Win32 i386 Unicode Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\Agent.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Agent.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

