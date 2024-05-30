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

NO_ACTIVEX_LIBS=1

TARGET_NAME = ammulti
TARGET_TYPE = DYNLINK
TARGET_EXT  = dll

DLL_ENTRY = DllMain

# Source files

SRC_FILES = stdafx.cpp multi.cpp multif.cpp
RC_FILE   = multi.rc
DEF_FILE  = multi.def
LINK_LIBS = "$(DXMEDIASDK)\LIB\strmiids.lib"

INC_PATH    = ..\filter

START_TASK = multi.h

# DLL specific defines

DLL_BASE  = 0x1d080000

# Dependent Libraries

# include DSHOWSDK.MAK

!include <dshowsdk.mak>

multi.h : multi.idl
    midl multi.idl

