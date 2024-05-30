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
DSHOWSAMPLE = ..
!endif


# Target

TARGET_NAME = DVDSampl
TARGET_TYPE = PROGRAM
TARGET_EXT = exe
EXE_TYPE = windows

# Source files

SRC_FILES = DVDSampl.cpp

RC_FILE = DVDSampl.rc

DEF_FILE = DVDSampl.def

INC_PATH    = $(DXMEDIASDK)\include;$(DXMEDIASDK)\classes\base

# Dependent Libraries
!IF EXIST($(MSVCDir)\lib\uuid2.lib)
LINK_LIBS = $(LINK_LIBS) comdlg32.lib uuid2.lib
!ELSE
LINK_LIBS = $(LINK_LIBS) comdlg32.lib
!ENDIF

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
