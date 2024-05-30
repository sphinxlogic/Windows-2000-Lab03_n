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

all: webclient.exe wi_ssl_client.exe

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $<

.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $<


webclient.exe: webclient.obj
  $(link) $(ldebug) $(conlflags) \
  webclient.obj \
  -out:$*.exe \
  $(conlibsdll) advapi32.lib crypt32.lib


wi_ssl_client.exe: wi_ssl_client.obj
  $(link) $(ldebug) $(conlflags) \
  wi_ssl_client.obj              \
  -out:$*.exe  \
  $(conlibsdll) wininet.lib user32.lib

clean:
  del *.bak
  del *.obj
  del *.pdb

cleaner: clean
  del *.exe
