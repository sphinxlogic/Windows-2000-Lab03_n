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

TARGET_NAME = Ball
TARGET_TYPE = DYNLINK
TARGET_EXT  = ax

# Source files

SRC_FILES = fball.cpp   \
            ball.cpp    \

RC_FILE   = ball.rc
DEF_FILE  = Ball.def

# DLL specific defines
DLL_BASE  = 0x1d000000

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
