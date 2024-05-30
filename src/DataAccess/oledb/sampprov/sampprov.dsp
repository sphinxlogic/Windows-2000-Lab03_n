# Microsoft Developer Studio Project File - Name="sampprov" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (ALPHA) Dynamic-Link Library" 0x0602

CFG=sampprov - Win32 x86 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sampprov.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sampprov.mak" CFG="sampprov - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sampprov - Win32 x86 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sampprov - Win32 x86 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sampprov - Win32 (ALPHA) axp Debug" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "sampprov - Win32 (ALPHA) axp Release" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\sampprov"
# PROP BASE Intermediate_Dir ".\sampprov"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86\Debug"
# PROP Intermediate_Dir "x86\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"headers.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /Gm /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"headers.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msad.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /profile /map

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\samppro0"
# PROP BASE Intermediate_Dir ".\samppro0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86\Release"
# PROP Intermediate_Dir "x86\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /Gm /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"headers.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"headers.h" /FD /c
# SUBTRACT CPP /Fr
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msad.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /map /machine:I386
# SUBTRACT BASE LINK32 /profile /incremental:yes /debug
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /map /machine:I386 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /profile /incremental:yes /debug

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\sampprov"
# PROP BASE Intermediate_Dir ".\sampprov"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ALPHA\Debug"
# PROP Intermediate_Dir "ALPHA\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"headers.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /alpha
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /alpha
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:ALPHA /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\samppro0"
# PROP BASE Intermediate_Dir ".\samppro0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ALPHA\Release"
# PROP Intermediate_Dir "ALPHA\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"headers.h" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /alpha
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /alpha
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:ALPHA
# ADD LINK32 oledb.lib msdasc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:ALPHA /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)"

!ENDIF 

# Begin Target

# Name "sampprov - Win32 x86 Debug"
# Name "sampprov - Win32 x86 Release"
# Name "sampprov - Win32 (ALPHA) axp Debug"
# Name "sampprov - Win32 (ALPHA) axp Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\accessor.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

# ADD CPP /Yu"headers.h"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ACCES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ACCES=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ACCES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ACCES=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asserts.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ASSER=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ASSER=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ASSER=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ASSER=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\baseobj.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_BASEO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_BASEO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_BASEO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_BASEO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\binder.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_BINDE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_BINDE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_BINDE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_BINDE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bitarray.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_BITAR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_BITAR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_BITAR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_BITAR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\classfac.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_CLASS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\classfac.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_CLASS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_CLASS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\classfac.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_CLASS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\colinfo.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_COLIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_COLIN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_COLIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_COLIN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\command.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_COMMA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_COMMA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_COMMA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_COMMA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\common.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crtsess.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_CRTSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_CRTSE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_CRTSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_CRTSE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cvttype.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_CVTTY=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_CVTTY=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_CVTTY=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_CVTTY=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\datasrc.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DATAS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DATAS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DATAS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DATAS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dbinit.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DBINI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DBINI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DBINI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DBINI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dbprop.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DBPRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DBPRO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DBPRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DBPRO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dbsess.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_DBSES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DBSES=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_DBSES=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_DBSES=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\extbuff.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_EXTBU=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_EXTBU=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_EXTBU=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_EXTBU=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fileidx.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_FILEI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_FILEI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_FILEI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_FILEI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\fileio.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_FILEIO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_FILEIO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_FILEIO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_FILEIO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\globals.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_GLOBA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_GLOBA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_GLOBA=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_GLOBA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hashtbl.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_HASHT=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_HASHT=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_HASHT=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_HASHT=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\headers.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

# ADD CPP /Yc"headers.h"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

# ADD CPP /Yc"headers.h"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_HEADE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_HEADE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yc"headers.h"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_HEADE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_HEADE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yc"headers.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\igetrow.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_IGETR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_IGETR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_IGETR=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_IGETR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\irowiden.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_IROWI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_IROWI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_IROWI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_IROWI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\irowset.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_IROWS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_IROWS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_IROWS=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_IROWS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\opnrowst.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_OPNRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_OPNRO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_OPNRO=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_OPNRO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\persist.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_PERSI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_PERSI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_PERSI=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_PERSI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\row.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROW_C=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROW_C=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROW_C=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROW_C=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rowchng.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROWCH=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROWCH=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROWCH=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROWCH=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rowinfo.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROWIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROWIN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROWIN=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROWIN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rowset.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_ROWSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROWSE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_ROWSE=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\utilprop.h"\
	
NODEP_CPP_ROWSE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sampprov.def
# End Source File
# Begin Source File

SOURCE=.\sampprov.rc
# End Source File
# Begin Source File

SOURCE=.\stream.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\utilprop.cpp

!IF  "$(CFG)" == "sampprov - Win32 x86 Debug"

!ELSEIF  "$(CFG)" == "sampprov - Win32 x86 Release"

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Debug"

DEP_CPP_UTILP=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\sampver.h"\
	".\utilprop.h"\
	
NODEP_CPP_UTILP=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ELSEIF  "$(CFG)" == "sampprov - Win32 (ALPHA) axp Release"

DEP_CPP_UTILP=\
	".\accessor.h"\
	".\asserts.h"\
	".\baseobj.h"\
	".\binder.h"\
	".\bitarray.h"\
	".\command.h"\
	".\datasrc.h"\
	".\dbsess.h"\
	".\extbuff.h"\
	".\fileidx.h"\
	".\fileio.h"\
	".\guids.h"\
	".\hashtbl.h"\
	".\headers.h"\
	".\row.h"\
	".\rowset.h"\
	".\sampprov.h"\
	".\sampver.h"\
	".\utilprop.h"\
	
NODEP_CPP_UTILP=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\accessor.h
# End Source File
# Begin Source File

SOURCE=.\asserts.h
# End Source File
# Begin Source File

SOURCE=.\baseobj.h
# End Source File
# Begin Source File

SOURCE=.\binder.h
# End Source File
# Begin Source File

SOURCE=.\bitarray.h
# End Source File
# Begin Source File

SOURCE=.\classfac.h
# End Source File
# Begin Source File

SOURCE=.\command.h
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\datasrc.h
# End Source File
# Begin Source File

SOURCE=.\dbsess.h
# End Source File
# Begin Source File

SOURCE=.\extbuff.h
# End Source File
# Begin Source File

SOURCE=.\fileidx.h
# End Source File
# Begin Source File

SOURCE=.\fileio.h
# End Source File
# Begin Source File

SOURCE=.\guids.h
# End Source File
# Begin Source File

SOURCE=.\hashtbl.h
# End Source File
# Begin Source File

SOURCE=.\headers.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\row.h
# End Source File
# Begin Source File

SOURCE=.\rowset.h
# End Source File
# Begin Source File

SOURCE=.\sampprov.h
# End Source File
# Begin Source File

SOURCE=.\sampver.h
# End Source File
# Begin Source File

SOURCE=.\stream.h
# End Source File
# Begin Source File

SOURCE=.\utilprop.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
