#############################################################################
#
#       Copyright (C) Microsoft Corporation 1995
#       All Rights Reserved.
#
#       MAKEFILE for WIA GetImage Sample
#
#############################################################################

!include <Win32.Mak>

all: GetImage.exe

GetImage.exe: GetImage.obj stdafx.obj 
  $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(conlibs) \
    kernel32.lib user32.lib ole32.lib uuid.lib oleaut32.lib sti.lib wiaguid.lib

.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.cpp
