# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997-1999.  Microsoft Corporation.  All rights reserved.
#

APPVER = 4.0
TARGETOS = WINNT
!include <win32.mak>

all: securobj.exe

PROJ_OBJS = main.obj privobji.obj security.obj


# Update the resource if necessary
securobj.res: main.rc
  rc -r -fo securobj.res main.rc

# Inference rule for updating the object files
.cpp.obj:
  $(cc) $(cdebug) $(cvars) $(cflags) $<


# Update the exe
securobj.exe: $(PROJ_OBJS) securobj.res
  $(link) $(ldebug) $(guilflags) $** \
        -out:securobj.exe \
        $(guilibs) aclui.lib comctl32.lib uuid.lib





