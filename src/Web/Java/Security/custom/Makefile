# makefile
#
# Created 09/09/97
#
# (C)Copyright 1997 Microsoft Corporation, All rights reserved.
#


!ifndef BUILD
BUILD = debug
!endif

JAVA_SDK_ROOT = $(MAKEDIR)\..\..\..
JAVA_SDK_BIN = $(JAVA_SDK_ROOT)\Bin
JAVA_SDK_PKGBIN = $(JAVA_SDK_BIN)\PackSign


PKG = com\ms\samples\security\custom

LIB_CLASSES = \
    $(BUILD)\$(PKG)\SampleLib.class \
    $(BUILD)\$(PKG)\SampleRequest.class \
    $(BUILD)\$(PKG)\SamplePermission.class

LIB_JAVASRC = \
    SampleLib.java \
    SampleRequest.java \
    SamplePermission.java


JVC = $(JAVA_SDK_BIN)\jvc


all: dirchk $(BUILD)\signedlib.cab $(BUILD)\signedapplet.cab $(BUILD)\default.htm

clean:
    @if exist $(BUILD)\nul deltree /y $(BUILD)
    @if exist demo\nul deltree /y demo

sample: $(BUILD)\signedlib.cab $(BUILD)\signedapplet.cab
    @if not exist sample mkdir sample
    copy $(BUILD)\signedlib.cab sample
    copy $(BUILD)\signedapplet.cab sample

install: sample\signedlib.cab
    rundll32 msjava.dll,JavaPkgMgr_Install sample\signedlib.cab,0,1,0,0,0,18,,,1

dirchk:
    @if not exist $(BUILD)\nul mkdir $(BUILD)
    @if not exist demo\nul mkdir demo

$(LIB_CLASSES): $(LIB_JAVASRC)
    $(JVC) -d $(BUILD) $(LIB_JAVASRC)

demo\Main.class: Main.java $(LIB_CLASSES)
    cd demo
    $(JVC) -cp:p ..\$(BUILD) -d . ..\Main.java
    cd $(MAKEDIR)

$(BUILD)\cert.spc: $(BUILD)\cert.cer
    $(JAVA_SDK_PKGBIN)\cert2spc $(BUILD)\cert.cer $(BUILD)\cert.spc

$(BUILD)\cert.cer $(BUILD)\cert.pvk:
    @echo.
    @echo Press 'None' for the test cert's private key.
    @echo.
    $(JAVA_SDK_PKGBIN)\makecert -d "Custom Permission Signer" -sv $(BUILD)\cert.pvk $(BUILD)\cert.cer

$(BUILD)\unsignedlib.cab: $(LIB_CLASSES)
    $(JAVA_SDK_PKGBIN)\dubuild -d "Custom Permission Sample" $(BUILD)\unsignedlib.cab $(BUILD) -i *.class -s $(PKG:\=.)

$(BUILD)\signedlib.cab: $(BUILD)\unsignedlib.cab $(BUILD)\cert.spc $(BUILD)\cert.pvk
    copy $(BUILD)\unsignedlib.cab $(BUILD)\signedlib.cab
    $(JAVA_SDK_PKGBIN)\signcode -spc $(BUILD)\cert.spc -v $(BUILD)\cert.pvk $(BUILD)\signedlib.cab

$(BUILD)\baseperms.ini: $(BUILD)\baseperms.class
    jview -cp:p $(BUILD) baseperms >$@

$(BUILD)\perms.ini: $(BUILD)\baseperms.ini customperms.ini
    copy $(BUILD)\baseperms.ini+customperms.ini $@

$(BUILD)\unsignedapplet.cab: demo\Main.class
    cd demo
    $(JAVA_SDK_PKGBIN)\cabarc -r -p n $(MAKEDIR)\$(BUILD)\unsignedapplet.cab *.class
    cd $(MAKEDIR)

$(BUILD)\signedapplet.cab: $(BUILD)\unsignedapplet.cab $(BUILD)\cert.spc $(BUILD)\cert.pvk $(BUILD)\perms.ini
    copy $(BUILD)\unsignedapplet.cab $(BUILD)\signedapplet.cab
    cd $(BUILD)
    @set CLASSPATH=$(CLASSPATH);.
    $(JAVA_SDK_PKGBIN)\signcode -spc cert.spc -v cert.pvk -j $(JAVA_SDK_PKGBIN)\javasign.dll -jp perms.ini signedapplet.cab
    cd $(MAKEDIR)

$(BUILD)\default.htm: default.htm $(BUILD)\signedapplet.cab $(BUILD)\signedlib.cab
    type default.htm >$(BUILD)\default.htm


# Inference rules

.SUFFIXES: .java .class

.java{$(BUILD)}.class:
    $(JVC) -d $(BUILD) $<

