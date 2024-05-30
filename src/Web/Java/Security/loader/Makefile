# makefile
#
# Created 09/09/97
#
# (C)Copyright 1997 Microsoft Corporation, All rights reserved.
#


JAVA_SDK_ROOT = ..\..\..
JAVA_SDK_BIN = $(JAVA_SDK_ROOT)\Bin

LOADER_DIR = loaded


CLASSES = \
    SampleLoader.class \
    demo.class

LOADED_CLASSES = \
    $(LOADER_DIR)\FileReader.class

JVC = $(JAVA_SDK_BIN)\jvc
JVC_SWITCHES = $(JVC_SWITCHES) -cp:p $(BUILD);.


all: $(CLASSES) $(LOADED_CLASSES)

clean:
    @del $(CLASSES)
    @if exist $(LOADER_DIR)\nul deltree /y $(LOADER_DIR)


# build rules

JAVASRC = $(CLASSES:.class=.java)

$(CLASSES): $(JAVASRC)
    $(JVC) $(JVC_SWITCHES) $(JAVASRC)


# inference rules

.SUFFIXES: .java .class

.java{$(LOADER_DIR)}.class:
    $(JVC) $(JVC_SWITCHES) -d $(LOADER_DIR) $<
