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
DSHOWSAMPLE = $(DXMEDIASDK)\samples\multimedia\dshow\src
!endif


# Target

TARGET_NAME = MPG1SAMP
TARGET_TYPE = DYNLINK
TARGET_EXT  = ax

# Source files

SRC_FILES = mpeg1.cpp
INC_PATH    = ..\include
RC_FILE   = mpeg1.rc
DEF_FILE  = mpeg1.def

# DLL specific defines

DLL_BASE  = 0x1d080000

# Dependent Libraries

LINK_LIBS = ..\base\$(DBG_RTL)\spltbase.lib ..\mpgutil\$(DBG_RTL)\mpgutil.lib

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
