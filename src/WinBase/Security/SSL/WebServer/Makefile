# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
#

TARGETOS=WINNT
APPVER=4.0

!include <Win32.Mak>

all: webserver.exe

PROJ_OBJS = webserver.obj

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $<

webserver.exe: $(PROJ_OBJS)
  $(link) $(ldebug) $(conlflags)  \
  $(PROJ_OBJS)                    \
  -out:webserver.exe              \
  $(conlibsdll) advapi32.lib crypt32.lib

clean:
  del *.bak
  del *.obj
  del *.pdb

cleaner: clean
  del *.exe

