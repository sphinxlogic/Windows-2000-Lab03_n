# Microsoft Developer Studio Generated NMAKE File, Based on RowsetViewer.dsp
!IF "$(CFG)" == ""
CFG=RowsetViewer - Win32 x86 Debug
!MESSAGE No configuration specified. Defaulting to RowsetViewer - Win32 x86\
 Debug.
!ENDIF 

!IF "$(CFG)" != "RowsetViewer - Win32 (ALPHA) axp Debug" && "$(CFG)" !=\
 "RowsetViewer - Win32 (ALPHA) axp Release" && "$(CFG)" !=\
 "RowsetViewer - Win32 x86 Release" && "$(CFG)" !=\
 "RowsetViewer - Win32 x86 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RowsetViewer.mak" CFG="RowsetViewer - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RowsetViewer - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "RowsetViewer - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "RowsetViewer - Win32 x86 Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "RowsetViewer - Win32 x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

OUTDIR=.\axp_Debu
INTDIR=.\axp_Debu
# Begin Custom Macros
OutDir=.\axp_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RowsetViewer.exe"

!ELSE 

ALL : "$(OUTDIR)\RowsetViewer.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CBase.obj"
	-@erase "$(INTDIR)\CBinder.obj"
	-@erase "$(INTDIR)\CCommand.obj"
	-@erase "$(INTDIR)\CDataLinks.obj"
	-@erase "$(INTDIR)\CDataset.obj"
	-@erase "$(INTDIR)\CDataSource.obj"
	-@erase "$(INTDIR)\CDialog.obj"
	-@erase "$(INTDIR)\CDialogLite.obj"
	-@erase "$(INTDIR)\CEnum.obj"
	-@erase "$(INTDIR)\CError.obj"
	-@erase "$(INTDIR)\CListener.obj"
	-@erase "$(INTDIR)\CMainWindow.obj"
	-@erase "$(INTDIR)\CMDIChild.obj"
	-@erase "$(INTDIR)\CMutipleResults.obj"
	-@erase "$(INTDIR)\CObjTree.obj"
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\COptions.obj"
	-@erase "$(INTDIR)\CRow.obj"
	-@erase "$(INTDIR)\CRowPosition.obj"
	-@erase "$(INTDIR)\CRowset.obj"
	-@erase "$(INTDIR)\CSession.obj"
	-@erase "$(INTDIR)\CStream.obj"
	-@erase "$(INTDIR)\CTrace.obj"
	-@erase "$(INTDIR)\CTransaction.obj"
	-@erase "$(INTDIR)\CWinApp.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Headers.obj"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\RowsetViewer.idb"
	-@erase "$(INTDIR)\RowsetViewer.pch"
	-@erase "$(INTDIR)\RowsetViewer.res"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(OUTDIR)\RowsetViewer.exe"
	-@erase "$(OUTDIR)\RowsetViewer.ilk"
	-@erase "$(OUTDIR)\RowsetViewer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 
CPP_OBJS=.\axp_Debu/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RowsetViewer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RowsetViewer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib\
 uuid.lib htmlhelp.lib /incremental:no /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)\RowsetViewer.pdb" /debug /debugtype:both /machine:ALPHA\
 /out:"$(OUTDIR)\RowsetViewer.exe"\
 /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\CBase.obj" \
	"$(INTDIR)\CBinder.obj" \
	"$(INTDIR)\CCommand.obj" \
	"$(INTDIR)\CDataLinks.obj" \
	"$(INTDIR)\CDataset.obj" \
	"$(INTDIR)\CDataSource.obj" \
	"$(INTDIR)\CDialog.obj" \
	"$(INTDIR)\CDialogLite.obj" \
	"$(INTDIR)\CEnum.obj" \
	"$(INTDIR)\CError.obj" \
	"$(INTDIR)\CListener.obj" \
	"$(INTDIR)\CMainWindow.obj" \
	"$(INTDIR)\CMDIChild.obj" \
	"$(INTDIR)\CMutipleResults.obj" \
	"$(INTDIR)\CObjTree.obj" \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\COptions.obj" \
	"$(INTDIR)\CRow.obj" \
	"$(INTDIR)\CRowPosition.obj" \
	"$(INTDIR)\CRowset.obj" \
	"$(INTDIR)\CSession.obj" \
	"$(INTDIR)\CStream.obj" \
	"$(INTDIR)\CTrace.obj" \
	"$(INTDIR)\CTransaction.obj" \
	"$(INTDIR)\CWinApp.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\Headers.obj" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\RowsetViewer.res" \
	"$(INTDIR)\Spy.obj"

"$(OUTDIR)\RowsetViewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

OUTDIR=.\axp_Rele
INTDIR=.\axp_Rele
# Begin Custom Macros
OutDir=.\axp_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RowsetViewer.exe"

!ELSE 

ALL : "$(OUTDIR)\RowsetViewer.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CBase.obj"
	-@erase "$(INTDIR)\CBinder.obj"
	-@erase "$(INTDIR)\CCommand.obj"
	-@erase "$(INTDIR)\CDataLinks.obj"
	-@erase "$(INTDIR)\CDataset.obj"
	-@erase "$(INTDIR)\CDataSource.obj"
	-@erase "$(INTDIR)\CDialog.obj"
	-@erase "$(INTDIR)\CDialogLite.obj"
	-@erase "$(INTDIR)\CEnum.obj"
	-@erase "$(INTDIR)\CError.obj"
	-@erase "$(INTDIR)\CListener.obj"
	-@erase "$(INTDIR)\CMainWindow.obj"
	-@erase "$(INTDIR)\CMDIChild.obj"
	-@erase "$(INTDIR)\CMutipleResults.obj"
	-@erase "$(INTDIR)\CObjTree.obj"
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\COptions.obj"
	-@erase "$(INTDIR)\CRow.obj"
	-@erase "$(INTDIR)\CRowPosition.obj"
	-@erase "$(INTDIR)\CRowset.obj"
	-@erase "$(INTDIR)\CSession.obj"
	-@erase "$(INTDIR)\CStream.obj"
	-@erase "$(INTDIR)\CTrace.obj"
	-@erase "$(INTDIR)\CTransaction.obj"
	-@erase "$(INTDIR)\CWinApp.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Headers.obj"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\RowsetViewer.idb"
	-@erase "$(INTDIR)\RowsetViewer.pch"
	-@erase "$(INTDIR)\RowsetViewer.res"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(OUTDIR)\RowsetViewer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 
CPP_OBJS=.\axp_Rele/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RowsetViewer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RowsetViewer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib\
 uuid.lib htmlhelp.lib /incremental:no /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)\RowsetViewer.pdb" /machine:ALPHA\
 /out:"$(OUTDIR)\RowsetViewer.exe"\
 /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\CBase.obj" \
	"$(INTDIR)\CBinder.obj" \
	"$(INTDIR)\CCommand.obj" \
	"$(INTDIR)\CDataLinks.obj" \
	"$(INTDIR)\CDataset.obj" \
	"$(INTDIR)\CDataSource.obj" \
	"$(INTDIR)\CDialog.obj" \
	"$(INTDIR)\CDialogLite.obj" \
	"$(INTDIR)\CEnum.obj" \
	"$(INTDIR)\CError.obj" \
	"$(INTDIR)\CListener.obj" \
	"$(INTDIR)\CMainWindow.obj" \
	"$(INTDIR)\CMDIChild.obj" \
	"$(INTDIR)\CMutipleResults.obj" \
	"$(INTDIR)\CObjTree.obj" \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\COptions.obj" \
	"$(INTDIR)\CRow.obj" \
	"$(INTDIR)\CRowPosition.obj" \
	"$(INTDIR)\CRowset.obj" \
	"$(INTDIR)\CSession.obj" \
	"$(INTDIR)\CStream.obj" \
	"$(INTDIR)\CTrace.obj" \
	"$(INTDIR)\CTransaction.obj" \
	"$(INTDIR)\CWinApp.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\Headers.obj" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\RowsetViewer.res" \
	"$(INTDIR)\Spy.obj"

"$(OUTDIR)\RowsetViewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

OUTDIR=.\x86_rele
INTDIR=.\x86_rele
# Begin Custom Macros
OutDir=.\x86_rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RowsetViewer.exe"

!ELSE 

ALL : "$(OUTDIR)\RowsetViewer.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CBase.obj"
	-@erase "$(INTDIR)\CBinder.obj"
	-@erase "$(INTDIR)\CCommand.obj"
	-@erase "$(INTDIR)\CDataLinks.obj"
	-@erase "$(INTDIR)\CDataset.obj"
	-@erase "$(INTDIR)\CDataSource.obj"
	-@erase "$(INTDIR)\CDialog.obj"
	-@erase "$(INTDIR)\CDialogLite.obj"
	-@erase "$(INTDIR)\CEnum.obj"
	-@erase "$(INTDIR)\CError.obj"
	-@erase "$(INTDIR)\CListener.obj"
	-@erase "$(INTDIR)\CMainWindow.obj"
	-@erase "$(INTDIR)\CMDIChild.obj"
	-@erase "$(INTDIR)\CMutipleResults.obj"
	-@erase "$(INTDIR)\CObjTree.obj"
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\COptions.obj"
	-@erase "$(INTDIR)\CRow.obj"
	-@erase "$(INTDIR)\CRowPosition.obj"
	-@erase "$(INTDIR)\CRowset.obj"
	-@erase "$(INTDIR)\CSession.obj"
	-@erase "$(INTDIR)\CStream.obj"
	-@erase "$(INTDIR)\CTrace.obj"
	-@erase "$(INTDIR)\CTransaction.obj"
	-@erase "$(INTDIR)\CWinApp.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Headers.obj"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\RowsetViewer.idb"
	-@erase "$(INTDIR)\RowsetViewer.pch"
	-@erase "$(INTDIR)\RowsetViewer.res"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(OUTDIR)\RowsetViewer.exe"
	-@erase "$(OUTDIR)\RowsetViewer.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 
CPP_OBJS=.\x86_rele/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RowsetViewer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RowsetViewer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib\
 uuid.lib htmlhelp.lib /incremental:no /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)\RowsetViewer.pdb" /machine:I386\
 /out:"$(OUTDIR)\RowsetViewer.exe"\
 /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\CBase.obj" \
	"$(INTDIR)\CBinder.obj" \
	"$(INTDIR)\CCommand.obj" \
	"$(INTDIR)\CDataLinks.obj" \
	"$(INTDIR)\CDataset.obj" \
	"$(INTDIR)\CDataSource.obj" \
	"$(INTDIR)\CDialog.obj" \
	"$(INTDIR)\CDialogLite.obj" \
	"$(INTDIR)\CEnum.obj" \
	"$(INTDIR)\CError.obj" \
	"$(INTDIR)\CListener.obj" \
	"$(INTDIR)\CMainWindow.obj" \
	"$(INTDIR)\CMDIChild.obj" \
	"$(INTDIR)\CMutipleResults.obj" \
	"$(INTDIR)\CObjTree.obj" \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\COptions.obj" \
	"$(INTDIR)\CRow.obj" \
	"$(INTDIR)\CRowPosition.obj" \
	"$(INTDIR)\CRowset.obj" \
	"$(INTDIR)\CSession.obj" \
	"$(INTDIR)\CStream.obj" \
	"$(INTDIR)\CTrace.obj" \
	"$(INTDIR)\CTransaction.obj" \
	"$(INTDIR)\CWinApp.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\Headers.obj" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\RowsetViewer.res" \
	"$(INTDIR)\Spy.obj"

"$(OUTDIR)\RowsetViewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

OUTDIR=.\x86_debu
INTDIR=.\x86_debu
# Begin Custom Macros
OutDir=.\x86_debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\RowsetViewer.exe" "$(OUTDIR)\RowsetViewer.bsc"

!ELSE 

ALL : "$(OUTDIR)\RowsetViewer.exe" "$(OUTDIR)\RowsetViewer.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CBase.obj"
	-@erase "$(INTDIR)\CBase.sbr"
	-@erase "$(INTDIR)\CBinder.obj"
	-@erase "$(INTDIR)\CBinder.sbr"
	-@erase "$(INTDIR)\CCommand.obj"
	-@erase "$(INTDIR)\CCommand.sbr"
	-@erase "$(INTDIR)\CDataLinks.obj"
	-@erase "$(INTDIR)\CDataLinks.sbr"
	-@erase "$(INTDIR)\CDataset.obj"
	-@erase "$(INTDIR)\CDataset.sbr"
	-@erase "$(INTDIR)\CDataSource.obj"
	-@erase "$(INTDIR)\CDataSource.sbr"
	-@erase "$(INTDIR)\CDialog.obj"
	-@erase "$(INTDIR)\CDialog.sbr"
	-@erase "$(INTDIR)\CDialogLite.obj"
	-@erase "$(INTDIR)\CDialogLite.sbr"
	-@erase "$(INTDIR)\CEnum.obj"
	-@erase "$(INTDIR)\CEnum.sbr"
	-@erase "$(INTDIR)\CError.obj"
	-@erase "$(INTDIR)\CError.sbr"
	-@erase "$(INTDIR)\CListener.obj"
	-@erase "$(INTDIR)\CListener.sbr"
	-@erase "$(INTDIR)\CMainWindow.obj"
	-@erase "$(INTDIR)\CMainWindow.sbr"
	-@erase "$(INTDIR)\CMDIChild.obj"
	-@erase "$(INTDIR)\CMDIChild.sbr"
	-@erase "$(INTDIR)\CMutipleResults.obj"
	-@erase "$(INTDIR)\CMutipleResults.sbr"
	-@erase "$(INTDIR)\CObjTree.obj"
	-@erase "$(INTDIR)\CObjTree.sbr"
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\COMMON.SBR"
	-@erase "$(INTDIR)\COptions.obj"
	-@erase "$(INTDIR)\COptions.sbr"
	-@erase "$(INTDIR)\CRow.obj"
	-@erase "$(INTDIR)\CRow.sbr"
	-@erase "$(INTDIR)\CRowPosition.obj"
	-@erase "$(INTDIR)\CRowPosition.sbr"
	-@erase "$(INTDIR)\CRowset.obj"
	-@erase "$(INTDIR)\CRowset.sbr"
	-@erase "$(INTDIR)\CSession.obj"
	-@erase "$(INTDIR)\CSession.sbr"
	-@erase "$(INTDIR)\CStream.obj"
	-@erase "$(INTDIR)\CStream.sbr"
	-@erase "$(INTDIR)\CTrace.obj"
	-@erase "$(INTDIR)\CTrace.sbr"
	-@erase "$(INTDIR)\CTransaction.obj"
	-@erase "$(INTDIR)\CTransaction.sbr"
	-@erase "$(INTDIR)\CWinApp.obj"
	-@erase "$(INTDIR)\CWinApp.sbr"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\Error.sbr"
	-@erase "$(INTDIR)\Headers.obj"
	-@erase "$(INTDIR)\Headers.sbr"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\Property.sbr"
	-@erase "$(INTDIR)\RowsetViewer.idb"
	-@erase "$(INTDIR)\RowsetViewer.pch"
	-@erase "$(INTDIR)\RowsetViewer.res"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(INTDIR)\Spy.sbr"
	-@erase "$(OUTDIR)\RowsetViewer.bsc"
	-@erase "$(OUTDIR)\RowsetViewer.exe"
	-@erase "$(OUTDIR)\RowsetViewer.ilk"
	-@erase "$(OUTDIR)\RowsetViewer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 
CPP_OBJS=.\x86_debu/
CPP_SBRS=.\x86_debu/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RowsetViewer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RowsetViewer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CBase.sbr" \
	"$(INTDIR)\CBinder.sbr" \
	"$(INTDIR)\CCommand.sbr" \
	"$(INTDIR)\CDataLinks.sbr" \
	"$(INTDIR)\CDataset.sbr" \
	"$(INTDIR)\CDataSource.sbr" \
	"$(INTDIR)\CDialog.sbr" \
	"$(INTDIR)\CDialogLite.sbr" \
	"$(INTDIR)\CEnum.sbr" \
	"$(INTDIR)\CError.sbr" \
	"$(INTDIR)\CListener.sbr" \
	"$(INTDIR)\CMainWindow.sbr" \
	"$(INTDIR)\CMDIChild.sbr" \
	"$(INTDIR)\CMutipleResults.sbr" \
	"$(INTDIR)\CObjTree.sbr" \
	"$(INTDIR)\COMMON.SBR" \
	"$(INTDIR)\COptions.sbr" \
	"$(INTDIR)\CRow.sbr" \
	"$(INTDIR)\CRowPosition.sbr" \
	"$(INTDIR)\CRowset.sbr" \
	"$(INTDIR)\CSession.sbr" \
	"$(INTDIR)\CStream.sbr" \
	"$(INTDIR)\CTrace.sbr" \
	"$(INTDIR)\CTransaction.sbr" \
	"$(INTDIR)\CWinApp.sbr" \
	"$(INTDIR)\Error.sbr" \
	"$(INTDIR)\Headers.sbr" \
	"$(INTDIR)\Property.sbr" \
	"$(INTDIR)\Spy.sbr"

"$(OUTDIR)\RowsetViewer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib\
 uuid.lib htmlhelp.lib /incremental:no /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)\RowsetViewer.pdb" /debug /debugtype:both /machine:I386\
 /out:"$(OUTDIR)\RowsetViewer.exe"\
 /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\CBase.obj" \
	"$(INTDIR)\CBinder.obj" \
	"$(INTDIR)\CCommand.obj" \
	"$(INTDIR)\CDataLinks.obj" \
	"$(INTDIR)\CDataset.obj" \
	"$(INTDIR)\CDataSource.obj" \
	"$(INTDIR)\CDialog.obj" \
	"$(INTDIR)\CDialogLite.obj" \
	"$(INTDIR)\CEnum.obj" \
	"$(INTDIR)\CError.obj" \
	"$(INTDIR)\CListener.obj" \
	"$(INTDIR)\CMainWindow.obj" \
	"$(INTDIR)\CMDIChild.obj" \
	"$(INTDIR)\CMutipleResults.obj" \
	"$(INTDIR)\CObjTree.obj" \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\COptions.obj" \
	"$(INTDIR)\CRow.obj" \
	"$(INTDIR)\CRowPosition.obj" \
	"$(INTDIR)\CRowset.obj" \
	"$(INTDIR)\CSession.obj" \
	"$(INTDIR)\CStream.obj" \
	"$(INTDIR)\CTrace.obj" \
	"$(INTDIR)\CTransaction.obj" \
	"$(INTDIR)\CWinApp.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\Headers.obj" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\RowsetViewer.res" \
	"$(INTDIR)\Spy.obj"

"$(OUTDIR)\RowsetViewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug" || "$(CFG)" ==\
 "RowsetViewer - Win32 (ALPHA) axp Release" || "$(CFG)" ==\
 "RowsetViewer - Win32 x86 Release" || "$(CFG)" ==\
 "RowsetViewer - Win32 x86 Debug"
SOURCE=.\RowsetViewer.RC
DEP_RSC_ROWSE=\
	".\res\menu.bmp"\
	".\res\readonly.bmp"\
	".\res\RowsetViewer.ico"\
	".\res\Toolbar.bmp"\
	".\res\RowsetViewer.rc2"\
	".\VERSION.H"\
	

"$(INTDIR)\RowsetViewer.res" : $(SOURCE) $(DEP_RSC_ROWSE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CBase.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CBASE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBase.obj" : $(SOURCE) $(DEP_CPP_CBASE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CBASE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBase.obj" : $(SOURCE) $(DEP_CPP_CBASE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CBASE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBase.obj" : $(SOURCE) $(DEP_CPP_CBASE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CBASE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBase.obj"	"$(INTDIR)\CBase.sbr" : $(SOURCE) $(DEP_CPP_CBASE)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CBinder.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CBIND=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBinder.obj" : $(SOURCE) $(DEP_CPP_CBIND) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CBIND=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBinder.obj" : $(SOURCE) $(DEP_CPP_CBIND) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CBIND=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBinder.obj" : $(SOURCE) $(DEP_CPP_CBIND) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CBIND=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CBinder.obj"	"$(INTDIR)\CBinder.sbr" : $(SOURCE) $(DEP_CPP_CBIND)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CCommand.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CCOMM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CCommand.obj" : $(SOURCE) $(DEP_CPP_CCOMM) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CCOMM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CCommand.obj" : $(SOURCE) $(DEP_CPP_CCOMM) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CCOMM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CCommand.obj" : $(SOURCE) $(DEP_CPP_CCOMM) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CCOMM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CCommand.obj"	"$(INTDIR)\CCommand.sbr" : $(SOURCE) $(DEP_CPP_CCOMM)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CDataLinks.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CDATA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataLinks.obj" : $(SOURCE) $(DEP_CPP_CDATA) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CDATA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataLinks.obj" : $(SOURCE) $(DEP_CPP_CDATA) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CDATA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataLinks.obj" : $(SOURCE) $(DEP_CPP_CDATA) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CDATA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataLinks.obj"	"$(INTDIR)\CDataLinks.sbr" : $(SOURCE)\
 $(DEP_CPP_CDATA) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CDataset.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CDATAS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataset.obj" : $(SOURCE) $(DEP_CPP_CDATAS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CDATAS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataset.obj" : $(SOURCE) $(DEP_CPP_CDATAS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CDATAS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataset.obj" : $(SOURCE) $(DEP_CPP_CDATAS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CDATAS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataset.obj"	"$(INTDIR)\CDataset.sbr" : $(SOURCE) $(DEP_CPP_CDATAS)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CDataSource.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CDATASO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataSource.obj" : $(SOURCE) $(DEP_CPP_CDATASO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CDATASO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataSource.obj" : $(SOURCE) $(DEP_CPP_CDATASO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CDATASO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataSource.obj" : $(SOURCE) $(DEP_CPP_CDATASO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CDATASO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDataSource.obj"	"$(INTDIR)\CDataSource.sbr" : $(SOURCE)\
 $(DEP_CPP_CDATASO) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CDialog.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CDIAL=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialog.obj" : $(SOURCE) $(DEP_CPP_CDIAL) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CDIAL=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialog.obj" : $(SOURCE) $(DEP_CPP_CDIAL) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CDIAL=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialog.obj" : $(SOURCE) $(DEP_CPP_CDIAL) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CDIAL=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialog.obj"	"$(INTDIR)\CDialog.sbr" : $(SOURCE) $(DEP_CPP_CDIAL)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CDialogLite.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CDIALO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialogLite.obj" : $(SOURCE) $(DEP_CPP_CDIALO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CDIALO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialogLite.obj" : $(SOURCE) $(DEP_CPP_CDIALO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CDIALO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialogLite.obj" : $(SOURCE) $(DEP_CPP_CDIALO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CDIALO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CDialogLite.obj"	"$(INTDIR)\CDialogLite.sbr" : $(SOURCE)\
 $(DEP_CPP_CDIALO) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CEnum.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CENUM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CEnum.obj" : $(SOURCE) $(DEP_CPP_CENUM) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CENUM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CEnum.obj" : $(SOURCE) $(DEP_CPP_CENUM) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CENUM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CEnum.obj" : $(SOURCE) $(DEP_CPP_CENUM) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CENUM=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CEnum.obj"	"$(INTDIR)\CEnum.sbr" : $(SOURCE) $(DEP_CPP_CENUM)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CError.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CERRO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CError.obj" : $(SOURCE) $(DEP_CPP_CERRO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CERRO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CError.obj" : $(SOURCE) $(DEP_CPP_CERRO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CERRO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CError.obj" : $(SOURCE) $(DEP_CPP_CERRO) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CERRO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CError.obj"	"$(INTDIR)\CError.sbr" : $(SOURCE) $(DEP_CPP_CERRO)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CListener.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CLIST=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CListener.obj" : $(SOURCE) $(DEP_CPP_CLIST) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CLIST=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CListener.obj" : $(SOURCE) $(DEP_CPP_CLIST) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CLIST=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CListener.obj" : $(SOURCE) $(DEP_CPP_CLIST) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CLIST=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CListener.obj"	"$(INTDIR)\CListener.sbr" : $(SOURCE)\
 $(DEP_CPP_CLIST) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CMainWindow.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CMAIN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\VERSION.H"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMainWindow.obj" : $(SOURCE) $(DEP_CPP_CMAIN) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CMAIN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\VERSION.H"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMainWindow.obj" : $(SOURCE) $(DEP_CPP_CMAIN) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CMAIN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\VERSION.H"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMainWindow.obj" : $(SOURCE) $(DEP_CPP_CMAIN) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CMAIN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\VERSION.H"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMainWindow.obj"	"$(INTDIR)\CMainWindow.sbr" : $(SOURCE)\
 $(DEP_CPP_CMAIN) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CMDIChild.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CMDIC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMDIChild.obj" : $(SOURCE) $(DEP_CPP_CMDIC) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CMDIC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMDIChild.obj" : $(SOURCE) $(DEP_CPP_CMDIC) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CMDIC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMDIChild.obj" : $(SOURCE) $(DEP_CPP_CMDIC) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CMDIC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMDIChild.obj"	"$(INTDIR)\CMDIChild.sbr" : $(SOURCE)\
 $(DEP_CPP_CMDIC) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CMutipleResults.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CMUTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMutipleResults.obj" : $(SOURCE) $(DEP_CPP_CMUTI) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CMUTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMutipleResults.obj" : $(SOURCE) $(DEP_CPP_CMUTI) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CMUTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMutipleResults.obj" : $(SOURCE) $(DEP_CPP_CMUTI) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CMUTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CMutipleResults.obj"	"$(INTDIR)\CMutipleResults.sbr" : $(SOURCE)\
 $(DEP_CPP_CMUTI) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CObjTree.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_COBJT=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CObjTree.obj" : $(SOURCE) $(DEP_CPP_COBJT) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_COBJT=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CObjTree.obj" : $(SOURCE) $(DEP_CPP_COBJT) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_COBJT=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CObjTree.obj" : $(SOURCE) $(DEP_CPP_COBJT) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_COBJT=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CObjTree.obj"	"$(INTDIR)\CObjTree.sbr" : $(SOURCE) $(DEP_CPP_COBJT)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\COMMON.CPP

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_COMMO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COMMON.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_COMMO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COMMON.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_COMMO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COMMON.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_COMMO=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COMMON.OBJ"	"$(INTDIR)\COMMON.SBR" : $(SOURCE) $(DEP_CPP_COMMO)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\COptions.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_COPTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COptions.obj" : $(SOURCE) $(DEP_CPP_COPTI) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_COPTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COptions.obj" : $(SOURCE) $(DEP_CPP_COPTI) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_COPTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COptions.obj" : $(SOURCE) $(DEP_CPP_COPTI) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_COPTI=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\COptions.obj"	"$(INTDIR)\COptions.sbr" : $(SOURCE) $(DEP_CPP_COPTI)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CRow.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CROW_=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRow.obj" : $(SOURCE) $(DEP_CPP_CROW_) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CROW_=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRow.obj" : $(SOURCE) $(DEP_CPP_CROW_) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CROW_=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRow.obj" : $(SOURCE) $(DEP_CPP_CROW_) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CROW_=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRow.obj"	"$(INTDIR)\CRow.sbr" : $(SOURCE) $(DEP_CPP_CROW_)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CRowPosition.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CROWP=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowPosition.obj" : $(SOURCE) $(DEP_CPP_CROWP) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CROWP=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowPosition.obj" : $(SOURCE) $(DEP_CPP_CROWP) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CROWP=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowPosition.obj" : $(SOURCE) $(DEP_CPP_CROWP) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CROWP=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowPosition.obj"	"$(INTDIR)\CRowPosition.sbr" : $(SOURCE)\
 $(DEP_CPP_CROWP) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CRowset.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CROWS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowset.obj" : $(SOURCE) $(DEP_CPP_CROWS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CROWS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowset.obj" : $(SOURCE) $(DEP_CPP_CROWS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CROWS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowset.obj" : $(SOURCE) $(DEP_CPP_CROWS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CROWS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CRowset.obj"	"$(INTDIR)\CRowset.sbr" : $(SOURCE) $(DEP_CPP_CROWS)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CSession.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CSESS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CSession.obj" : $(SOURCE) $(DEP_CPP_CSESS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CSESS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CSession.obj" : $(SOURCE) $(DEP_CPP_CSESS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CSESS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CSession.obj" : $(SOURCE) $(DEP_CPP_CSESS) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CSESS=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CSession.obj"	"$(INTDIR)\CSession.sbr" : $(SOURCE) $(DEP_CPP_CSESS)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CStream.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CSTRE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CStream.obj" : $(SOURCE) $(DEP_CPP_CSTRE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CSTRE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CStream.obj" : $(SOURCE) $(DEP_CPP_CSTRE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CSTRE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CStream.obj" : $(SOURCE) $(DEP_CPP_CSTRE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CSTRE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CStream.obj"	"$(INTDIR)\CStream.sbr" : $(SOURCE) $(DEP_CPP_CSTRE)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CTrace.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CTRAC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTrace.obj" : $(SOURCE) $(DEP_CPP_CTRAC) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CTRAC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTrace.obj" : $(SOURCE) $(DEP_CPP_CTRAC) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CTRAC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTrace.obj" : $(SOURCE) $(DEP_CPP_CTRAC) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CTRAC=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTrace.obj"	"$(INTDIR)\CTrace.sbr" : $(SOURCE) $(DEP_CPP_CTRAC)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CTransaction.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CTRAN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTransaction.obj" : $(SOURCE) $(DEP_CPP_CTRAN) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CTRAN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTransaction.obj" : $(SOURCE) $(DEP_CPP_CTRAN) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CTRAN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTransaction.obj" : $(SOURCE) $(DEP_CPP_CTRAN) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CTRAN=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CTransaction.obj"	"$(INTDIR)\CTransaction.sbr" : $(SOURCE)\
 $(DEP_CPP_CTRAN) "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CWinApp.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_CWINA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CWinApp.obj" : $(SOURCE) $(DEP_CPP_CWINA) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_CWINA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CWinApp.obj" : $(SOURCE) $(DEP_CPP_CWINA) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_CWINA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CWinApp.obj" : $(SOURCE) $(DEP_CPP_CWINA) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_CWINA=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\CWinApp.obj"	"$(INTDIR)\CWinApp.sbr" : $(SOURCE) $(DEP_CPP_CWINA)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Error.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_ERROR=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_ERROR=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_ERROR=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_ERROR=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Error.obj"	"$(INTDIR)\Error.sbr" : $(SOURCE) $(DEP_CPP_ERROR)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Headers.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_HEADE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yc"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Headers.obj"	"$(INTDIR)\RowsetViewer.pch" : $(SOURCE)\
 $(DEP_CPP_HEADE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_HEADE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yc"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Headers.obj"	"$(INTDIR)\RowsetViewer.pch" : $(SOURCE)\
 $(DEP_CPP_HEADE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_HEADE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yc"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Headers.obj"	"$(INTDIR)\RowsetViewer.pch" : $(SOURCE)\
 $(DEP_CPP_HEADE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_HEADE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yc"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Headers.obj"	"$(INTDIR)\Headers.sbr"	"$(INTDIR)\RowsetViewer.pch" : \
$(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Property.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_PROPE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_PROPE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_PROPE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_PROPE=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Property.obj"	"$(INTDIR)\Property.sbr" : $(SOURCE) $(DEP_CPP_PROPE)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Spy.cpp

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

DEP_CPP_SPY_C=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Spy.obj" : $(SOURCE) $(DEP_CPP_SPY_C) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

DEP_CPP_SPY_C=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Spy.obj" : $(SOURCE) $(DEP_CPP_SPY_C) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

DEP_CPP_SPY_C=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Spy.obj" : $(SOURCE) $(DEP_CPP_SPY_C) "$(INTDIR)"\
 "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

DEP_CPP_SPY_C=\
	".\CBase.h"\
	".\CBinder.h"\
	".\CCommand.h"\
	".\CDataLinks.h"\
	".\CDataSet.h"\
	".\CDataSource.h"\
	".\CDialog.h"\
	".\CDialogLite.h"\
	".\CEnum.h"\
	".\CError.h"\
	".\CListener.h"\
	".\CMainWindow.h"\
	".\CMDIChild.h"\
	".\CMultipleResults.h"\
	".\CObjTree.h"\
	".\COMMON.H"\
	".\COptions.h"\
	".\CRow.h"\
	".\CRowPosition.h"\
	".\CRowset.h"\
	".\CSession.h"\
	".\CStream.h"\
	".\CTrace.h"\
	".\CTransaction.h"\
	".\CWinApp.h"\
	".\Error.h"\
	".\Headers.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	{$(INCLUDE)}"msdadc.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"msdasc.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr"$(INTDIR)\\"\
 /Fp"$(INTDIR)\RowsetViewer.pch" /Yu"Headers.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\RowsetViewer.pdb" /FD /c 

"$(INTDIR)\Spy.obj"	"$(INTDIR)\Spy.sbr" : $(SOURCE) $(DEP_CPP_SPY_C)\
 "$(INTDIR)" "$(INTDIR)\RowsetViewer.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

