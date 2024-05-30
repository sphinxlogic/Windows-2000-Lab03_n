# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1998 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

libs = $(libs) oleaut32.lib odbc32.lib odbccp32.lib

Proj = QuryDemo

ObjList = $(ObjDir)\Main.obj $(ObjDir)\Query.obj QuryDemo.res

# Nmake macros for building Win32 apps
!include <BkOffice.Mak>

all: $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList)
    $(link) $(linkdebug) $(guilflags) \
    $(ObjList) $(guilibs) $(linklibs) \
    -out:$(ObjDir)\$(Proj).exe

$(ObjDir)\Main.obj: Main.c

$(ObjDir)\Query.obj: Query.c

$(ObjDir)\$(Proj).res: QuryDemo.rc Resource.h
    $(rc) $(rcflags) $(rcvars) /fo $(Proj).res QuryDemo.rc


