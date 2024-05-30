# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993 - 1999  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

Proj= asyncdemo
gui=1
use_odbc=1
libs=$(libs) wininet.lib

ObjList =  $(ObjDir)\$(Proj).obj \
		   $(ObjDir)\$(Proj).res

# Nmake macros for building Windows 32-Bit apps
!include <bkoffice.Mak>

all: $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList)
