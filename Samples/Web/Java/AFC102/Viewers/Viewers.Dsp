# Microsoft Developer Studio Project File - Name="Viewers" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Java Virtual Machine Java Project" 0x0809

CFG=Viewers - Java Virtual Machine Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Viewers.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Viewers.mak" CFG="Viewers - Java Virtual Machine Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Viewers - Java Virtual Machine Release" (based on\
 "Java Virtual Machine Java Project")
!MESSAGE "Viewers - Java Virtual Machine Debug" (based on\
 "Java Virtual Machine Java Project")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/SDK2.0/ClassLib/AFC/Samples/AFC102/Viewers", ADFKAAAA"
# PROP Scc_LocalPath "."
JAVA=jvc.exe

!IF  "$(CFG)" == "Viewers - Java Virtual Machine Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Classes"
# PROP Intermediate_Dir ""
# PROP Target_Dir ""
# ADD BASE JAVA /O
# ADD JAVA /w4 /O

!ELSEIF  "$(CFG)" == "Viewers - Java Virtual Machine Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Target_Dir ""
# ADD BASE JAVA /g
# ADD JAVA /g

!ENDIF 

# Begin Target

# Name "Viewers - Java Virtual Machine Release"
# Name "Viewers - Java Virtual Machine Debug"
# Begin Source File

SOURCE=.\Src\ColumnViewerPanel.java
# End Source File
# Begin Source File

SOURCE=.\Src\MarqueePanel.java
# End Source File
# Begin Source File

SOURCE=.\Src\SDKCallbacks.java
# End Source File
# Begin Source File

SOURCE=.\Src\SDKConsts.java
# End Source File
# Begin Source File

SOURCE=.\Src\SDKCtrlPnl.java
# End Source File
# Begin Source File

SOURCE=.\Src\SDKImages.java
# End Source File
# Begin Source File

SOURCE=.\Src\SDKInsetPanel.java
# End Source File
# Begin Source File

SOURCE=.\Classes\SDKSample.html
# End Source File
# Begin Source File

SOURCE=.\Src\SDKSample.java
# End Source File
# Begin Source File

SOURCE=.\Src\SplitViewerPanel.java
# End Source File
# Begin Source File

SOURCE=.\Src\TabViewerPanel.java
# End Source File
# End Target
# End Project
