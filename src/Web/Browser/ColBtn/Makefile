# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993 - 1999  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

Proj= ColBtn

dll=1

# Nmake macros for building Windows 32-Bit apps
!include <BkOffice.mak>

ObjList =  $(ObjDir)\$(Proj).obj    \
           $(ObjDir)\Button.obj     \
           $(ObjDir)\StdAfx.obj     \
           $(ObjDir)\$(Proj).res

all: $(ObjDir)\$(Proj).dll $(ObjDir)\$(Proj).trg

$(ObjDir)\$(Proj).obj: $(ObjDir)\$(Proj).h

$(ObjDir)\$(Proj).h: $(Proj).idl

$(ObjDir)\$(Proj).dll: $(ObjList)            

