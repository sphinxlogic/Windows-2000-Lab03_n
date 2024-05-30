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

TARGET_NAME = vcrctrl
TARGET_TYPE = DYNLINK
TARGET_EXT  = ax

# Source files

SRC_FILES =     cvcrutil.cpp \
		fvcrctrl.cpp \
		vcrprop.cpp \
		trprop.cpp \
		cdevcom.cpp \
		ctimecod.cpp \

RC_FILE   = vcrprop.rc

DEF_FILE  = vcrctrl.def

# DLL specific defines

# DLL_ENTRY = _DllMainCRTStartup
DLL_BASE  = 0x1d000000

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
