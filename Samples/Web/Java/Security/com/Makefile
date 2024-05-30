# makefile
#
# Created 09/08/97
#
# (C)Copyright 1997 Microsoft Corporation, All rights reserved.
#


!ifndef BUILD
BUILD = debug
!endif

JAVA_SDK_ROOT = ..\..\..
JAVA_SDK_BIN = $(JAVA_SDK_ROOT)\Bin


JAVASRC = \
    CMyCOMObject.java \
    Main.java

CLASSES = \
    $(BUILD)\comsamp\CMyCOMObject.class \
    $(BUILD)\demo\demo\Main.class

COM_CLASSES = \
    $(BUILD)\comsamp\IMyInterface.class \
    $(BUILD)\comsamp\IMyCOMObjectSecurity.class

OBJ = \
    $(BUILD)\comsamp.obj \
    $(BUILD)\comsamp_i.obj

LIBS = advapi32.lib uuid.lib ole32.lib

BASE_NAME = comsamp

PDB = $(BUILD)\$(BASE_NAME).pdb

CL_SWITCHES = $(CL_SWITCHES) -I$(JAVA_SDK_ROOT)\Include -I$(BUILD)
!if "$(BUILD)" == "debug"
CL_SWITCHES = $(CL_SWITCHES) -Zi -Fd$(PDB)
!else
CL_SWITCHES = $(CL_SWITCHES) -Ox
!endif

JVC = $(JAVA_SDK_BIN)\jvc
JVC_SWITCHES = $(JVC_SWITCHES) /x- -cp:p $(BUILD)

JAVATLB = $(JAVA_SDK_BIN)\jactivex /javatlb


all: dirchk $(BUILD)\$(BASE_NAME).dll $(COM_CLASSES) $(CLASSES)

clean:
    @if exist $(BUILD)\nul deltree /y $(BUILD)

sample: all
    @if not exist sample mkdir sample
    copy $(BUILD)\$(BASE_NAME).dll sample
    @if not exist sample\comsamp mkdir sample\comsamp
    xcopy /s $(BUILD)\comsamp sample\comsamp
    @if not exist sample\demo mkdir sample\demo
    xcopy /s $(BUILD)\demo sample\demo


dirchk:
    @if not exist $(BUILD)\nul mkdir $(BUILD)


# build rules

$(BUILD)\$(BASE_NAME).dll: $(OBJ)
    link -def:$(BASE_NAME).def -pdb:$(PDB) -out:$@ -dll $(OBJ) $(LIBS)

$(BUILD)\comsamp_i.c $(BUILD)\comsamp.h $(BUILD)\comsamp.tlb: comsamp.idl
    midl /out $(BUILD) /h comsamp.h comsamp.idl

COM_JAVASRC = $(COM_CLASSES:.class=.java)

$(COM_JAVASRC): $(BUILD)\comsamp.tlb
    $(JAVATLB) /xc /d $(BUILD) $(BUILD)\comsamp.tlb


# Dependencies

comsamp.cpp: $(BUILD)\comsamp.h
Main.java: CMyCOMObject.java


# Inference rules

.SUFFIXES: .class .java

.cpp{$(BUILD)}.obj:
    cl -c $(CL_SWITCHES) -Fo$@ $<

{$(BUILD)}.c{$(BUILD)}.obj:
    cl -c $(CL_SWITCHES) -Fo$@ $<

.java.class:
    $(JVC) $(JVC_SWITCHES) -d $(BUILD) $<

.java{$(BUILD)\comsamp}.class:
    $(JVC) $(JVC_SWITCHES) -d $(BUILD) $<

.java{$(BUILD)\demo\demo}.class:
    $(JVC) $(JVC_SWITCHES) -d $(BUILD)\demo $<

.java{$(BUILD)}.class:
    $(JVC) $(JVC_SWITCHES) -d $(BUILD) $<

