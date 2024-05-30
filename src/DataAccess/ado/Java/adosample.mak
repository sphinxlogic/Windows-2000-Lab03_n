# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Java Virtual Machine Java Workspace" 0x0809

!IF "$(CFG)" == ""
CFG=adosample - Java Virtual Machine Debug
!MESSAGE No configuration specified.  Defaulting to adosample - Java Virtual\
 Machine Debug.
!ENDIF 

!IF "$(CFG)" != "adosample - Java Virtual Machine Release" && "$(CFG)" !=\
 "adosample - Java Virtual Machine Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "adosample.mak" CFG="adosample - Java Virtual Machine Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "adosample - Java Virtual Machine Release" (based on\
 "Java Virtual Machine Java Workspace")
!MESSAGE "adosample - Java Virtual Machine Debug" (based on\
 "Java Virtual Machine Java Workspace")
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
# PROP Target_Last_Scanned "adosample - Java Virtual Machine Debug"
JAVA=jvc.exe

!IF  "$(CFG)" == "adosample - Java Virtual Machine Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir ""
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\ado_recordset.class" "$(OUTDIR)\simpleado.class"\
 "$(OUTDIR)\SimpleForm.class" "$(OUTDIR)\simpleadoframe.class"

CLEAN : 
	-@erase "$(INTDIR)\ado_recordset.class"
	-@erase "$(INTDIR)\simpleado.class"
	-@erase "$(INTDIR)\simpleadoframe.class"
	-@erase "$(INTDIR)\SimpleForm.class"

# ADD BASE JAVA /O
# ADD JAVA /O

!ELSEIF  "$(CFG)" == "adosample - Java Virtual Machine Debug"

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
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\ado_recordset.class" "$(OUTDIR)\simpleado.class"\
 "$(OUTDIR)\SimpleForm.class" "$(OUTDIR)\simpleadoframe.class"

CLEAN : 
	-@erase "$(INTDIR)\ado_recordset.class"
	-@erase "$(INTDIR)\simpleado.class"
	-@erase "$(INTDIR)\simpleadoframe.class"
	-@erase "$(INTDIR)\SimpleForm.class"

# ADD BASE JAVA /g
# ADD JAVA /g

!ENDIF 

################################################################################
# Begin Target

# Name "adosample - Java Virtual Machine Release"
# Name "adosample - Java Virtual Machine Debug"

!IF  "$(CFG)" == "adosample - Java Virtual Machine Release"

!ELSEIF  "$(CFG)" == "adosample - Java Virtual Machine Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ado_recordset.java

!IF  "$(CFG)" == "adosample - Java Virtual Machine Release"


"$(INTDIR)\ado_recordset.class" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adosample - Java Virtual Machine Debug"


"$(INTDIR)\ado_recordset.class" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\simpleado.java

!IF  "$(CFG)" == "adosample - Java Virtual Machine Release"


"$(INTDIR)\simpleado.class" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\SimpleForm.class" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adosample - Java Virtual Machine Debug"


"$(INTDIR)\simpleado.class" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\SimpleForm.class" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\simpleadoframe.java

!IF  "$(CFG)" == "adosample - Java Virtual Machine Release"


"$(INTDIR)\simpleadoframe.class" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "adosample - Java Virtual Machine Debug"


"$(INTDIR)\simpleadoframe.class" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\simpleado.html

!IF  "$(CFG)" == "adosample - Java Virtual Machine Release"

!ELSEIF  "$(CFG)" == "adosample - Java Virtual Machine Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
