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

TARGET_NAME = MoCcomp
TARGET_TYPE = DYNLINK
EXE_TYPE = windows
TARGET_EXT  = dll

# Source files

SRC_FILES = MoComp.cpp

DEF_FILE  = MoComp.def

!IF EXIST($(MSVCDir)\lib\uuid2.lib)
LINK_LIBS = $(LINK_LIBS) comdlg32.lib msacm32.lib uuid2.lib
!ELSE
LINK_LIBS = $(LINK_LIBS) comdlg32.lib msacm32.lib
!ENDIF
# DLL specific defines

DLL_ENTRY = _DllMainCRTStartup
DLL_BASE  = 0x1c400000

# include DSHOWSDK.MAK

!include <dshowsdk.mak>
