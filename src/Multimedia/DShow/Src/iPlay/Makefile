#
# DirectShow Project Makefile
#
# Copyright (c) Microsoft Corporation 1995 - 1998.  All Rights reserved
#
# Targets are provided by DSHOWSDK.MAK
#
# all     Create executables (default).
# clean   Remove all files created by any goal.
#
# This makefile stub simplifies makefile creation for those
# cases where you want to use standard options.
#

DISABLE_PCH = 1

!undef USE_LIBCMT_LIB
USE_MSVCRT_LIB = 1

# set = 1 if require
#
# BROWSER - brower info.

BROWSER =

# Location relative to master DSHOWSDK sample makefile.

!ifndef DSHOWSAMPLE
DSHOWSAMPLE = ..
!endif

# Target
#
# TARGET_NAME = {Name - no extension}
# TARGET_TYPE = {DYNLINK | LIBRARY}
# TARGET_EXT  = {if blank defined to be dll/lib}

TARGET_NAME = IPLAY
TARGET_TYPE = PROGRAM
TARGET_EXT  =

# Source files
#
# e.g. SRC_FILES = source1.c  source2.cpp etc
#      RC_FILES  = resource.rc
#
#      DEF_FILE  = define.def
#
# and for debug specific files use (e.g.)
#
# !ifndef NODEBUG
# SRC_FILES= $(SRC_FILES) debug.cpp
# !endif

SRC_FILES = iplay.cpp      \
            iplaydoc.cpp   \
            mainfrm.cpp    \
            indeo.cpp      \
  	    stdafx.cpp

INC_FILES = stdafx.h                  \
            "$(DXMEDIASDK)\include\strmif.h"  \
            "$(DXMEDIASDK)\include\control.h" \
            "$(DXMEDIASDK)\include\evcode.h"  \
            "$(DXMEDIASDK)\include\uuids.h"   \
			iplay.h       \
			iplaydoc.h   \
			mainfrm.h    \
			indeo.h      \
			datatype.h
			 # qtz_spec.h

RC_FILE   = iplay.rc

DEF_FILE  =

# DLL specific defines
#
# DLL_ENTRY = {DLL's entry point}
# DLL_BASE  = (DLL's base}

DLL_ENTRY =
DLL_BASE  =

#
#
#

EXE_TYPE = windows

!ifdef NODEBUG
!ifdef USE_MSVC20
MY_OLE_LIBS = mfc30.lib mfco30.lib
!else
MY_OLE_LIBS = mfc42.lib mfcs42.lib
!endif
!else
!ifdef USE_MSVC20
MY_OLE_LIBS = mfc30d.lib mfco30d.lib
!else
MY_OLE_LIBS = mfc42d.lib mfco42d.lib mfcs42d.lib
!endif
!endif

LINK_LIBS = shell32.lib    \
            comdlg32.lib   \
            oldnames.lib   \
            $(MY_OLE_LIBS)

!ifdef USE_MSVC20
LINK_LIBS = $(LINK_LIBS)  \
            mfcans32.lib
!endif


#

C_DEFINES = /Yu"stdafx.h" /Fp$(DBG_RTL)\stdafx.pch     \
            -D_AFXDLL -D_AFX_NO_FORCE_LIBS -DOLE2ANSI

#

START_TASK = $(DBG_RTL)\stdafx.obj $(DBG_RTL)\stdafx.pch
END_TASK   =
CLEAN_TASK =

# include DSHOWSDK.MAK

!include <dshowsdk.mak>

#

$(DBG_RTL)\stdafx.obj $(DBG_RTL)\stdafx.pch : $(INC_FILES)
  $(cc) $(cflags) /Yc"stdafx.h" -Fo$(DBG_RTL)\ /Fp$(DBG_RTL)\stdafx.pch $(INC_FLAGS) $(@B).cpp

# Dependencies

!if exist("_depend")
!include "_depend"
!endif
