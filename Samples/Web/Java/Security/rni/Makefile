# makefile
#
# Created 09/09/97
#
# (C)Copyright 1997 Microsoft Corporation, All rights reserved.
#


!ifndef BUILD
BUILD = debug
!endif

!ifndef PROCESSOR_ARCHITECTURE
CPU = i386
!else if "$(PROCESSOR_ARCHITECTURE)" == "x86"
CPU = i386
!else
CPU = $(PROCESSOR_ARCHITECTURE)
!endif

JAVA_SDK_ROOT = ..\..\..
JAVA_SDK_BIN = $(JAVA_SDK_ROOT)\Bin


OBJ = \
    $(BUILD)\rnisamp.obj

LIBS = msjava.lib

BASE_NAME = rnisamp


PDB = $(BUILD)\$(BASE_NAME).pdb

CL_SWITCHES = $(CL_SWITCHES) -I$(JAVA_SDK_ROOT)\Include -I$(BUILD)
!if "$(BUILD)" == "debug"
CL_SWITCHES = $(CL_SWITCHES) -Zi -Fd$(PDB)
!else
CL_SWITCHES = $(CL_SWITCHES) -Ox
!endif

LINK_SWITCHES = $(LINK_SWITCHES) -LIBPATH:$(JAVA_SDK_ROOT)\Lib\$(CPU)

JVC = $(JAVA_SDK_BIN)\jvc
JVC_SWITCHES = $(JVC_SWITCHES) -cp:p $(BUILD)

MSJAVAH = $(JAVA_SDK_BIN)\msjavah
MSJAVAH_SWITCHES = $(JAVAH_SWITCHES) -helpers -classpath $(BUILD)

JAVATLB = $(JAVA_SDK_BIN)\jactivex /javatlb


all: \
    dirchk \
    $(BUILD)\$(BASE_NAME).dll \
    $(BUILD)\rnisamp\MyRNIObject.class \
    $(BUILD)\demo\demo\Main.class

clean:
    @if exist $(BUILD)\nul deltree /y $(BUILD)

sample: all
    @if not exist sample\nul mkdir sample
    copy $(BUILD)\$(BASE_NAME).dll sample
    @if not exist sample\rnisamp\nul mkdir sample\rnisamp
    xcopy /s $(BUILD)\rnisamp sample\rnisamp
    @if not exist sample\demo\nul mkdir sample\demo
    xcopy /s $(BUILD)\demo sample\demo


dirchk:
    @if not exist $(BUILD)\nul mkdir $(BUILD)


# build rules

$(BUILD)\$(BASE_NAME).dll: $(OBJ)
    link $(LINK_SWITCHES) -pdb:$(PDB) -out:$@ -dll $(OBJ) $(LIBS)

$(BUILD)\rnisamp.h: $(BUILD)\rnisamp\MyRNIObject.class
    $(MSJAVAH) $(MSJAVAH_SWITCHES) -helpers -o $@ rnisamp.MyRNIObject java.lang.System java.lang.SecurityManager

$(BUILD)\rnisamp\MyRNIObject.class: MyRNIObject.java
    $(JVC) $(JVC_SWITCHES) -d $(BUILD) MyRNIObject.java

$(BUILD)\demo\demo\Main.class: Main.java
    $(JVC) $(JVC_SWITCHES) -d $(BUILD)\demo Main.java


# Dependencies

rnisamp.cpp: $(BUILD)\rnisamp.h


# Inference rules

.cpp{$(BUILD)}.obj:
    cl -c $(CL_SWITCHES) -Fo$@ $<

{$(BUILD)}.c{$(BUILD)}.obj:
    cl -c $(CL_SWITCHES) -Fo$@ $<

