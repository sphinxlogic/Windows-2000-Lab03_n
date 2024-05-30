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

# disable automatic handling of PCH files

DISABLE_PCH = 1
USE_LIBCMT_LIB = 1

# Location relative to master DSHOWSDK sample makefile.

!ifndef DSHOWSAMPLE
DSHOWSAMPLE = ..\..
!endif


# Target

TARGET_NAME = SimpleCL
TARGET_TYPE = PROGRAM

# Source files

SRC_FILES = simplecl.cpp

RC_FILE   = simplecl.rc

# Exe specifics

EXE_TYPE = windows

# Dependent Libraries

LINK_LIBS = shell32.lib comdlg32.lib

!include <dshowsdk.mak>
