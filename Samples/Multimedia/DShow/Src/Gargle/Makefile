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
# This makefile stub simplifies makefile creation for those
# cases where you want to use standard options.
#
#===========================================================================;

# Location relative to master DSHOWSDK sample makefile.

!ifndef DSHOWSAMPLE
DSHOWSAMPLE = ..
!endif


# Target

TARGET_NAME = Gargle
TARGET_TYPE = DYNLINK
TARGET_EXT  = ax

# Source files

SRC_FILES = gargle.cpp   \
            gargprop.cpp

RC_FILE   = gargprop.rc

DEF_FILE  = gargle.def

# DLL specific defines

DLL_BASE  = 0x1d140000

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
