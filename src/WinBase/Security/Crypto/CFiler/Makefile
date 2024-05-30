# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#

APPVER = 4.0
TARGETOS = WINNT

# define compile & link options
!include <win32.mak>

all: cfiler.exe cf.hlp

OBJS=cfiler.obj crp.obj drvproc.obj enumdrv.obj expdir.obj fillfile.obj table.obj


# Update the resource if necessary
cfiler.res: cfiler.rc  *.bmp *.ico
    $(rc) $(rcvars) -r cfiler.rc


# Build rule for converting c files to obj files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c


# Update the online help file
cf.hlp: cf.hpj cf.rtf
    $(hc) cf.hpj


# Update the executable file
cfiler.exe: $(OBJS) cfiler.res
    $(link) $(ldebug)  $(guilflags) -out:$*.exe $** $(guilibsmt)
