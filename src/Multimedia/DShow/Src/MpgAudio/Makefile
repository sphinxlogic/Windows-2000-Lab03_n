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

DISABLE_PCH = 1

# Location relative to master DSHOWSDK sample makefile.

!ifndef DSHOWSAMPLE
DSHOWSAMPLE = ..
!endif


# Target

TARGET_NAME = MpgAudio
TARGET_TYPE = DYNLINK
TARGET_EXT  = ax

# Source files

SRC_FILES = MpgAudio.cpp Decoder.cpp
RC_FILE   = MpgAudio.rc
DEF_FILE  = MpgAudio.def

# DLL specific defines

DLL_BASE  = 0x1dd00000

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
