## (C) Copyright 1996-1997 Microsoft Corporation.  
## THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
## ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
## THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
## PARTICULAR PURPOSE.
##
## Copyright (C) 1996  Microsoft Corporation.  All Rights Reserved.
##
##  MODULE:   SAMPLERC.DLL
##
##  PURPOSE:  Sample Resource File for Custom bitmap/resources
##

Proj= SAMPLERC

!include <win32.mak>

ObjList = sample.res

all:    $(Proj).dll

cleanall:   clean all

sample.res: sample.rc
	rc sample.rc

$(Proj).dll:    sample.res
    $(link) /NOENTRY /DLL /OUT:$(Proj).dll $(ObjList)

clean:
    del *.res *.dll 
