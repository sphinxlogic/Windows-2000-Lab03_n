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


!IF "$(ICM)" == "ICM_INSIDE_DC"

OUTDIR   = obj\in_dc_icm

!ELSEIF "$(ICM)" == "ICM_OUTSIDE_DC"

OUTDIR   = obj\out_dc_icm

!ELSE

OUTDIR   = obj\no_icm

!ENDIF


PROJ     = dibview

CFLAGS   = -D$(ICM) -DMULTIMON_ENABLED $(cdebug) $(cflags) $(cvars)
RFLAGS   = -D$(ICM) -DMULTIMON_ENABLED $(rcflags) $(rcvars)
LFLAGS   = $(ldebug) $(guilflags) $(guilibs)

PRECOMP  = pch.h
INCLUDE  = ..\inc;$(INCLUDE)
LIBS     = shell32.lib comdlg32.lib comctl32.lib version.lib

OBJECTS  = \
	"$(OUTDIR)\about.obj" \
	"$(OUTDIR)\clipboard.obj" \
	"$(OUTDIR)\cmmman.obj" \
	"$(OUTDIR)\convert.obj" \
	"$(OUTDIR)\construct.obj" \
	"$(OUTDIR)\dib.obj" \
	"$(OUTDIR)\dibview.obj" \
	"$(OUTDIR)\dibview.res" \
	"$(OUTDIR)\document.obj" \
	"$(OUTDIR)\ffilter.obj" \
	"$(OUTDIR)\global.obj" \
	"$(OUTDIR)\icm.obj" \
	"$(OUTDIR)\icon.obj" \
	"$(OUTDIR)\implement.obj" \
	"$(OUTDIR)\mmon.obj" \
	"$(OUTDIR)\pch.obj" \
	"$(OUTDIR)\print.obj" \
	"$(OUTDIR)\selsource.obj" \
	"$(OUTDIR)\settings.obj" \
	"$(OUTDIR)\twain.obj" \
	"$(OUTDIR)\window.obj" \

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
