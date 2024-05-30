# Microsoft Developer Studio Project File - Name="RowsetViewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (ALPHA) Application" 0x0601

CFG=RowsetViewer - Win32 x86 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RowsetViewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RowsetViewer.mak" CFG="RowsetViewer - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RowsetViewer - Win32 (ALPHA) axp Debug" (based on "Win32 (ALPHA) Application")
!MESSAGE "RowsetViewer - Win32 (ALPHA) axp Release" (based on "Win32 (ALPHA) Application")
!MESSAGE "RowsetViewer - Win32 x86 Release" (based on "Win32 (x86) Application")
!MESSAGE "RowsetViewer - Win32 x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/OLE DB SDK/samples/RowsetViewer", DLQAAAAA"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "RowsetVi"
# PROP BASE Intermediate_Dir "RowsetVi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ALPHA\Debug"
# PROP Intermediate_Dir "ALPHA\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fd"alpha/Debug/RowsetViewer.pdb" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib comctl32.lib msvcrt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib htmlhelp.lib /nologo /subsystem:windows /debug /machine:ALPHA /nodefaultlib /pdbtype:sept
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib uuid.lib htmlhelp.lib /nologo /subsystem:windows /debug /debugtype:both /machine:ALPHA /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 (ALPHA) axp Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "RowsetV0"
# PROP BASE Intermediate_Dir "RowsetV0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ALPHA\Release"
# PROP Intermediate_Dir "ALPHA\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fd"alpha/Release/RowsetViewer.pdb" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib comctl32.lib msvcrt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib htmlhelp.lib /nologo /subsystem:windows /machine:ALPHA /nodefaultlib /pdbtype:sept
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib uuid.lib htmlhelp.lib /nologo /subsystem:windows /machine:ALPHA /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "RowsetV0"
# PROP BASE Intermediate_Dir "RowsetV0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86\Release"
# PROP Intermediate_Dir "x86\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fd"x86/release/RowsetViewer.pdb" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib oledb.lib comctl32.lib msvcrt.lib htmlhelp.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /pdbtype:sept /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)"
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib uuid.lib htmlhelp.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "RowsetVi"
# PROP BASE Intermediate_Dir "RowsetVi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86\debug"
# PROP Intermediate_Dir "x86\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /Gm /GR /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "FINDLEAKS" /Fr /Fd"x86/debug/RowsetViewer.pdb" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib oledb.lib comctl32.lib msvcrt.lib htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib /pdbtype:sept /libpath:"..\..\lib"
# ADD LINK32 oledb.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib comctl32.lib msdasc.lib uuid.lib htmlhelp.lib /nologo /subsystem:windows /debug /debugtype:both /machine:I386 /libpath:"..\..\lib\$(PROCESSOR_ARCHITECTURE)"
# SUBTRACT LINK32 /profile /pdb:none /incremental:no /map /nodefaultlib

!ENDIF 

# Begin Target

# Name "RowsetViewer - Win32 (ALPHA) axp Debug"
# Name "RowsetViewer - Win32 (ALPHA) axp Release"
# Name "RowsetViewer - Win32 x86 Release"
# Name "RowsetViewer - Win32 x86 Debug"
# Begin Group "Resources"

# PROP Default_Filter "ico rc"
# Begin Source File

SOURCE=.\res\menu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\readonly.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RowsetViewer.ico
# End Source File
# Begin Source File

SOURCE=.\RowsetViewer.RC
# End Source File
# Begin Source File

SOURCE=.\res\RowsetViewer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBase.h
# End Source File
# Begin Source File

SOURCE=.\CBinder.h
# End Source File
# Begin Source File

SOURCE=.\CCommand.h
# End Source File
# Begin Source File

SOURCE=.\CDataLinks.h
# End Source File
# Begin Source File

SOURCE=.\CDataSet.h
# End Source File
# Begin Source File

SOURCE=.\CDataSource.h
# End Source File
# Begin Source File

SOURCE=.\CDialog.h
# End Source File
# Begin Source File

SOURCE=.\CDialogLite.h
# End Source File
# Begin Source File

SOURCE=.\CEnum.h
# End Source File
# Begin Source File

SOURCE=.\CError.h
# End Source File
# Begin Source File

SOURCE=.\CListener.h
# End Source File
# Begin Source File

SOURCE=.\CMainWindow.h
# End Source File
# Begin Source File

SOURCE=.\CMDIChild.h
# End Source File
# Begin Source File

SOURCE=.\CMultipleResults.h
# End Source File
# Begin Source File

SOURCE=.\CObjTree.h
# End Source File
# Begin Source File

SOURCE=.\COMMON.H
# End Source File
# Begin Source File

SOURCE=.\COptions.h
# End Source File
# Begin Source File

SOURCE=.\CRow.h
# End Source File
# Begin Source File

SOURCE=.\CRowPosition.h
# End Source File
# Begin Source File

SOURCE=.\CRowset.h
# End Source File
# Begin Source File

SOURCE=.\CSession.h
# End Source File
# Begin Source File

SOURCE=.\CStream.h
# End Source File
# Begin Source File

SOURCE=.\CTrace.h
# End Source File
# Begin Source File

SOURCE=.\CTransaction.h
# End Source File
# Begin Source File

SOURCE=.\CWinApp.h
# End Source File
# Begin Source File

SOURCE=.\Error.h
# End Source File
# Begin Source File

SOURCE=.\Headers.h
# End Source File
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\Property.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Spy.h
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

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
	
NODEP_CPP_CBASE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CBASE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CBIND=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CBIND=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CCOMM=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CCOMM=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CDATA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CDATA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CDATAS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CDATAS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CDATASO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CDATASO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CDIAL=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CDIAL=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CDIALO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CDIALO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CENUM=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CENUM=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CERRO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CERRO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CLIST=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CLIST=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CMAIN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CMAIN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CMDIC=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CMDIC=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CMUTI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CMUTI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_COBJT=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_COBJT=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_COMMO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

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
	
NODEP_CPP_COMMO=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_COPTI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_COPTI=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CROW_=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CROW_=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CROWP=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CROWP=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CROWS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CROWS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CSESS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CSESS=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CSTRE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CSTRE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CTRAC=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CTRAC=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CTRAN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CTRAN=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_CWINA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_CWINA=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_ERROR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_ERROR=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_HEADE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yc"Headers.h"

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
	
NODEP_CPP_HEADE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yc"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yc"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yc"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_PROPE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_PROPE=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# Begin Source File

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
	
NODEP_CPP_SPY_C=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

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
	
NODEP_CPP_SPY_C=\
	".\ledb.h"\
	".\ledberr.h"\
	".\ransact.h"\
	".\sdadc.h"\
	".\sdaguid.h"\
	".\sdasc.h"\
	
# ADD BASE CPP /Gt0
# ADD CPP /Gt0 /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Release"

# ADD CPP /Yu"Headers.h"

!ELSEIF  "$(CFG)" == "RowsetViewer - Win32 x86 Debug"

# ADD CPP /Yu"Headers.h"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
