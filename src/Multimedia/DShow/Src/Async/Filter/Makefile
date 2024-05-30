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

# Target

TARGET_NAME = asyncflt
TARGET_TYPE = DYNLINK
TARGET_EXT  = ax

# Source files

SRC_FILES = asyncflt.cpp
RC_FILE   = asyncflt.rc
DEF_FILE  = asyncflt.def

INC_PATH    = ..\include

# DLL specific defines

DLL_BASE  = 0x1d080000

# Dependent Libraries

LINK_LIBS = ..\base\$(DBG_RTL)\AsynBase.lib

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
