# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.
#

APPVER = 4.0
TARGETOS = WINNT

!include <Win32.Mak>

PROJ = secfile.exe
DEPS = secfile.obj
LIBS_EXT =

.c.obj:
        $(cc) /YX $(cdebug) $(cflags) $(cvars) $<

$(PROJ) : $(DEPS)
        $(link) @<<
$**
-out:$@
$(conlibs)
$(conlflags)
$(ldebug)
$(LIBS_EXT)
<<

clean:
        del *.obj *.bak *.pdb *.pch *.exe *.dll *.lib *.exp
