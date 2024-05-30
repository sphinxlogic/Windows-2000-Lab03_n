# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1998 Microsoft Corporation.  All Rights Reserved.
#
# Processor independent makefile

APPVER   = 5.0
TARGETOS = BOTH

!include <win32.mak>

OUTDIR   = obj

PROJ     = named

CFLAGS   = $(cdebug) $(cflags) $(cvars)
RFLAGS   = $(rcflags) $(rcvars)
LFLAGS   = $(ldebug) $(conlflags) $(conlibs)

PRECOMP  = pch.h
INCLUDE  = ..\inc;$(INCLUDE)
LIBS     = user32.lib mscms.lib

OBJECTS  = \
	"$(OUTDIR)\$(PROJ).obj" \
	"$(OUTDIR)\$(PROJ).res" \
	"$(OUTDIR)\pch.obj" \

all: "$(OUTDIR)\$(PROJ).exe"

clean: 
	-@for %i in ( $(OBJECTS) ) do @erase %i
	-@erase "$(OUTDIR)\$(PROJ).pch"
	-@erase "$(OUTDIR)\$(PROJ).exe"

"$(OUTDIR)":
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.rc{$(OUTDIR)\}.res:
	@$(rc) $(RFLAGS) /fo $@ $<

.c{$(OUTDIR)\}.obj::
	@$(cc) $(CFLAGS) /Fo"$(OUTDIR)\\" \
	/Fp"$(OUTDIR)\$(PROJ).pch" /Yu"$(PRECOMP)" $<

"$(OUTDIR)\$(PRECOMP:.h=.obj)": 
	@$(cc) $(CFLAGS) /Fo"$(OUTDIR)\\" \
	/Fp"$(OUTDIR)\$(PROJ).pch" /Yc"$(PRECOMP)" $?

"$(OUTDIR)\$(PROJ).exe": "$(OUTDIR)" $(OBJECTS)
	@$(link) $(LFLAGS) -out:"$(OUTDIR)\$(PROJ).exe" $(OBJECTS) $(LIBS)
