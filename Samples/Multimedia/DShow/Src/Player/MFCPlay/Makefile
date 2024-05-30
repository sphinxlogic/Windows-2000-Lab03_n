#===========================================================================;
#
#  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
#  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  Copyright (c) 1992 - 1998  Microsoft Corporation.  All Rights Reserved.
#
#---------------------------------------------------------------------------;
#
# DirectShow Project Makefile
#
# Targets are provided by DSHOWSDK.MAK
#
# all     Create executables (default).
# clean   Remove all files created by any goal.
#
#===========================================================================;

# Location relative to master DSHOWSDK sample makefile.

!ifndef DSHOWSAMPLE
DSHOWSAMPLE = ..\..
!endif


# project overrides

!undef USE_LIBCMT_LIB
USE_DEFAULT_LIB = 1

# Target

TARGET_NAME = MFCPlay
TARGET_TYPE = PROGRAM

# Source files

SRC_FILES = mfcplay.cpp  \
            mfcdoc.cpp   \
            mainfrm.cpp  \
            mfcvw.cpp

INC_FILES = stdafx.h                   \
            $(DXMEDIASDK)\include\strmif.h  \
            $(DXMEDIASDK)\include\control.h \
            $(DXMEDIASDK)\include\evcode.h  \
            $(DXMEDIASDK)\include\uuids.h

RC_FILE   = player.rc

PCH_HEADER = stdafx.h
PCH_NAME   = stdafx

# Exe specifics

EXE_TYPE = windows

# additional libraries

LINK_LIBS = shell32.lib    \
            comdlg32.lib   \
            oldnames.lib

# C defines

C_DEFINES = -D_AFXDLL -D_AFX_NO_FORCE_LIBS -DOLE2ANSI

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
