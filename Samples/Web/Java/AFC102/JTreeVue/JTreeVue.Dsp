# Microsoft Developer Studio Project File - Name="JTreeVue" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Java Virtual Machine Java Project" 0x0809

CFG=JTreeVue - Java Virtual Machine Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JTreeVue.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JTreeVue.mak" CFG="JTreeVue - Java Virtual Machine Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JTreeVue - Java Virtual Machine Release" (based on\
 "Java Virtual Machine Java Project")
!MESSAGE "JTreeVue - Java Virtual Machine Debug" (based on\
 "Java Virtual Machine Java Project")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/SDK2.0/ClassLib/AFC/Samples/AFC102/JTreeVue", XCFKAAAA"
# PROP Scc_LocalPath "."
JAVA=jvc.exe

!IF  "$(CFG)" == "JTreeVue - Java Virtual Machine Release"

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

!ELSEIF  "$(CFG)" == "JTreeVue - Java Virtual Machine Debug"

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

# Name "JTreeVue - Java Virtual Machine Release"
# Name "JTreeVue - Java Virtual Machine Debug"
# Begin Source File

SOURCE=.\Classes\FullTree.html
# End Source File
# Begin Source File

SOURCE=.\Src\JTreeConsts.java
# End Source File
# Begin Source File

SOURCE=.\Src\JTreeMenuBtn.java
# End Source File
# Begin Source File

SOURCE=.\Src\JTreeNode.java
# End Source File
# Begin Source File

SOURCE=.\Src\JTreeNodeInfo.java
# End Source File
# Begin Source File

SOURCE=.\Src\JTreeNodeItem.java
# End Source File
# Begin Source File

SOURCE=.\Classes\JTreeVue.html
# End Source File
# Begin Source File

SOURCE=.\Src\JTreeVue.java
# End Source File
# Begin Source File

SOURCE=.\Src\JTreeVuePanel.java
# End Source File
# Begin Source File

SOURCE=.\Classes\TestTree.html
# End Source File
# Begin Source File

SOURCE=.\Classes\tree.html
# End Source File
# End Target
# End Project
