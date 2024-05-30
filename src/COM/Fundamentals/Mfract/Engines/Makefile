#+---------------------------------------------------------------------------
#
#  Microsoft Windows
#  Copyright 1994 - 1998 Microsoft Corporation.
#
#  File:       makefile
#
#  Contents:   builds the MFract fractal engines
#
#  History:     5-03-94   stevebl   Created
#
#----------------------------------------------------------------------------

DIRLIST = mandel julia quad plasma rgen

SDKPROJ =COM\Fundamentals\mfract\engines

all: $(DIRLIST)

$(DIRLIST):
        cd $@
        @nmake -a -i -nologo
        cd ..


