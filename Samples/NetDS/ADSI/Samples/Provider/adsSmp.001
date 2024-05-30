# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=adssmp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to adssmp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "adssmp - Win32 Release" && "$(CFG)" != "adssmp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "adssmp.mak" CFG="adssmp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "adssmp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "adssmp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "adssmp - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "adssmp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\adssmp.dll"

CLEAN : 
	-@erase "$(INTDIR)\cclsobj.obj"
	-@erase "$(INTDIR)\cdispmgr.obj"
	-@erase "$(INTDIR)\cenumns.obj"
	-@erase "$(INTDIR)\cenumobj.obj"
	-@erase "$(INTDIR)\cenumsch.obj"
	-@erase "$(INTDIR)\cenumvar.obj"
	-@erase "$(INTDIR)\cgenobj.obj"
	-@erase "$(INTDIR)\cnamcf.obj"
	-@erase "$(INTDIR)\cnamesp.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\core.obj"
	-@erase "$(INTDIR)\cprops.obj"
	-@erase "$(INTDIR)\cprov.obj"
	-@erase "$(INTDIR)\cprovcf.obj"
	-@erase "$(INTDIR)\cprpobj.obj"
	-@erase "$(INTDIR)\cschobj.obj"
	-@erase "$(INTDIR)\getobj.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\libmain.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\parse.obj"
	-@erase "$(INTDIR)\property.obj"
	-@erase "$(INTDIR)\regdsapi.obj"
	-@erase "$(INTDIR)\smpoper.obj"
	-@erase "$(INTDIR)\stdfact.obj"
	-@erase "$(OUTDIR)\adssmp.dll"
	-@erase "$(OUTDIR)\adssmp.exp"
	-@erase "$(OUTDIR)\adssmp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/adssmp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adssmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib activeds.lib adsiid.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib activeds.lib\
 adsiid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/adssmp.pdb" /machine:I386 /def:".\adssmp.def"\
 /out:"$(OUTDIR)/adssmp.dll" /implib:"$(OUTDIR)/adssmp.lib" 
DEF_FILE= \
	".\adssmp.def"
LINK32_OBJS= \
	"$(INTDIR)\cclsobj.obj" \
	"$(INTDIR)\cdispmgr.obj" \
	"$(INTDIR)\cenumns.obj" \
	"$(INTDIR)\cenumobj.obj" \
	"$(INTDIR)\cenumsch.obj" \
	"$(INTDIR)\cenumvar.obj" \
	"$(INTDIR)\cgenobj.obj" \
	"$(INTDIR)\cnamcf.obj" \
	"$(INTDIR)\cnamesp.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\core.obj" \
	"$(INTDIR)\cprops.obj" \
	"$(INTDIR)\cprov.obj" \
	"$(INTDIR)\cprovcf.obj" \
	"$(INTDIR)\cprpobj.obj" \
	"$(INTDIR)\cschobj.obj" \
	"$(INTDIR)\getobj.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\libmain.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\parse.obj" \
	"$(INTDIR)\property.obj" \
	"$(INTDIR)\regdsapi.obj" \
	"$(INTDIR)\smpoper.obj" \
	"$(INTDIR)\stdfact.obj"

"$(OUTDIR)\adssmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "adssmp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\adssmp.dll"

CLEAN : 
	-@erase "$(INTDIR)\cclsobj.obj"
	-@erase "$(INTDIR)\cdispmgr.obj"
	-@erase "$(INTDIR)\cenumns.obj"
	-@erase "$(INTDIR)\cenumobj.obj"
	-@erase "$(INTDIR)\cenumsch.obj"
	-@erase "$(INTDIR)\cenumvar.obj"
	-@erase "$(INTDIR)\cgenobj.obj"
	-@erase "$(INTDIR)\cnamcf.obj"
	-@erase "$(INTDIR)\cnamesp.obj"
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\core.obj"
	-@erase "$(INTDIR)\cprops.obj"
	-@erase "$(INTDIR)\cprov.obj"
	-@erase "$(INTDIR)\cprovcf.obj"
	-@erase "$(INTDIR)\cprpobj.obj"
	-@erase "$(INTDIR)\cschobj.obj"
	-@erase "$(INTDIR)\getobj.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\libmain.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\object.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\parse.obj"
	-@erase "$(INTDIR)\property.obj"
	-@erase "$(INTDIR)\regdsapi.obj"
	-@erase "$(INTDIR)\smpoper.obj"
	-@erase "$(INTDIR)\stdfact.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\adssmp.dll"
	-@erase "$(OUTDIR)\adssmp.exp"
	-@erase "$(OUTDIR)\adssmp.ilk"
	-@erase "$(OUTDIR)\adssmp.lib"
	-@erase "$(OUTDIR)\adssmp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/adssmp.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/adssmp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib activeds.lib adsiid.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib activeds.lib\
 adsiid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/adssmp.pdb" /debug /machine:I386 /def:".\adssmp.def"\
 /out:"$(OUTDIR)/adssmp.dll" /implib:"$(OUTDIR)/adssmp.lib" 
DEF_FILE= \
	".\adssmp.def"
LINK32_OBJS= \
	"$(INTDIR)\cclsobj.obj" \
	"$(INTDIR)\cdispmgr.obj" \
	"$(INTDIR)\cenumns.obj" \
	"$(INTDIR)\cenumobj.obj" \
	"$(INTDIR)\cenumsch.obj" \
	"$(INTDIR)\cenumvar.obj" \
	"$(INTDIR)\cgenobj.obj" \
	"$(INTDIR)\cnamcf.obj" \
	"$(INTDIR)\cnamesp.obj" \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\core.obj" \
	"$(INTDIR)\cprops.obj" \
	"$(INTDIR)\cprov.obj" \
	"$(INTDIR)\cprovcf.obj" \
	"$(INTDIR)\cprpobj.obj" \
	"$(INTDIR)\cschobj.obj" \
	"$(INTDIR)\getobj.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\libmain.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\object.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\parse.obj" \
	"$(INTDIR)\property.obj" \
	"$(INTDIR)\regdsapi.obj" \
	"$(INTDIR)\smpoper.obj" \
	"$(INTDIR)\stdfact.obj"

"$(OUTDIR)\adssmp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "adssmp - Win32 Release"
# Name "adssmp - Win32 Debug"

!IF  "$(CFG)" == "adssmp - Win32 Release"

!ELSEIF  "$(CFG)" == "adssmp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\cnamesp.cpp
DEP_CPP_CNAME=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cnamesp.obj" : $(SOURCE) $(DEP_CPP_CNAME) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cdispmgr.cpp
DEP_CPP_CDISP=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cdispmgr.obj" : $(SOURCE) $(DEP_CPP_CDISP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cenumns.cpp
DEP_CPP_CENUM=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cenumns.obj" : $(SOURCE) $(DEP_CPP_CENUM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cenumobj.cpp
DEP_CPP_CENUMO=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cenumobj.obj" : $(SOURCE) $(DEP_CPP_CENUMO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cenumsch.cpp
DEP_CPP_CENUMS=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cenumsch.obj" : $(SOURCE) $(DEP_CPP_CENUMS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cenumvar.cpp
DEP_CPP_CENUMV=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cenumvar.obj" : $(SOURCE) $(DEP_CPP_CENUMV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cgenobj.cpp
DEP_CPP_CGENO=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cgenobj.obj" : $(SOURCE) $(DEP_CPP_CGENO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cnamcf.cpp
DEP_CPP_CNAMC=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cnamcf.obj" : $(SOURCE) $(DEP_CPP_CNAMC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cclsobj.cpp
DEP_CPP_CCLSO=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cclsobj.obj" : $(SOURCE) $(DEP_CPP_CCLSO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\memory.cpp
DEP_CPP_MEMOR=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\memory.obj" : $(SOURCE) $(DEP_CPP_MEMOR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\core.cpp
DEP_CPP_CORE_=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\core.obj" : $(SOURCE) $(DEP_CPP_CORE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cprops.cpp
DEP_CPP_CPROP=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cprops.obj" : $(SOURCE) $(DEP_CPP_CPROP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cprov.cpp
DEP_CPP_CPROV=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cprov.obj" : $(SOURCE) $(DEP_CPP_CPROV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cprovcf.cpp
DEP_CPP_CPROVC=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cprovcf.obj" : $(SOURCE) $(DEP_CPP_CPROVC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cprpobj.cpp
DEP_CPP_CPRPO=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cprpobj.obj" : $(SOURCE) $(DEP_CPP_CPRPO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\cschobj.cpp
DEP_CPP_CSCHO=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\cschobj.obj" : $(SOURCE) $(DEP_CPP_CSCHO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\getobj.cpp
DEP_CPP_GETOB=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\getobj.obj" : $(SOURCE) $(DEP_CPP_GETOB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\globals.cpp
DEP_CPP_GLOBA=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\guid.cpp
DEP_CPP_GUID_=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\guid.obj" : $(SOURCE) $(DEP_CPP_GUID_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\libmain.cpp
DEP_CPP_LIBMA=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\libmain.obj" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\common.cpp
DEP_CPP_COMMO=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdfact.cpp
DEP_CPP_STDFA=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\stdfact.obj" : $(SOURCE) $(DEP_CPP_STDFA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\pack.cpp
DEP_CPP_PACK_=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\pack.obj" : $(SOURCE) $(DEP_CPP_PACK_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\parse.cpp
DEP_CPP_PARSE=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\property.cpp
DEP_CPP_PROPE=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\regdsapi.cpp
DEP_CPP_REGDS=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\regdsapi.obj" : $(SOURCE) $(DEP_CPP_REGDS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\smpoper.cpp
DEP_CPP_SMPOP=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\smpoper.obj" : $(SOURCE) $(DEP_CPP_SMPOP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\object.cpp
DEP_CPP_OBJEC=\
	"..\..\public\include\adserr.h"\
	"..\..\public\include\adshlp.h"\
	"..\..\public\include\adsiid.h"\
	"..\..\public\include\adsnms.h"\
	"..\..\public\include\adssts.h"\
	"..\..\public\include\iads.h"\
	".\adssmp.h"\
	".\cclsobj.h"\
	".\cdispmgr.h"\
	".\cenumns.h"\
	".\cenumobj.h"\
	".\cenumsch.h"\
	".\cenumvar.h"\
	".\cgenobj.h"\
	".\cmacro.h"\
	".\cnamcf.h"\
	".\cnamesp.h"\
	".\common.h"\
	".\core.h"\
	".\cprops.h"\
	".\cprov.h"\
	".\cprovcf.h"\
	".\cprpobj.h"\
	".\cschobj.h"\
	".\formtrck.h"\
	".\getobj.h"\
	".\globals.h"\
	".\guid.h"\
	".\intf.h"\
	".\libmain.h"\
	".\macro.h"\
	".\memory.h"\
	".\object.h"\
	".\pack.h"\
	".\parse.h"\
	".\property.h"\
	".\regdsapi.h"\
	".\smpoper.h"\
	".\smptypes.h"\
	".\util.h"\
	{$(INCLUDE)}"\activeds.h"\
	

"$(INTDIR)\object.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\adssmp.def

!IF  "$(CFG)" == "adssmp - Win32 Release"

!ELSEIF  "$(CFG)" == "adssmp - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
