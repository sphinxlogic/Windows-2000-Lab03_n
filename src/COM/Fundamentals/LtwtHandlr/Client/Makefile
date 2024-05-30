# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1993 - 1998 Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>



all: clientNoXData.exe clientWithXData.exe 

CUSTOM_FLAGS = /D_WIN32_DCOM


!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif

.cpp.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<


.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c $<

GLOBAL_OBJS = guid.obj debug.obj ..\NumtxtPS\ServerPS.dll
# Define project specific macros
GLOBAL_DEP = ..\common\guid.h ..\common\debug.h ..\NumToTextPS\server.h
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib
clientNoXData.obj : client.cpp
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c client.cpp /FoclientNoXData.obj

clientWithXData.obj : client.cpp 
    $(CC) $(cdebug) $(cflags) $(cvarsdll) /DWITHXDATA $(CUSTOM_FLAGS) /c client.cpp /FoclientWithXData.obj 

guid.obj : ..\common\guid.cpp
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c ..\common\guid.cpp
debug.obj : ..\common\debug.cpp
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c ..\common\debug.cpp

..\NumtxtPS\ServerPS.dll:
!include <sdkbld.mak>

..\WithXData\withXdata.exe:
!include <sdkbld.mak>

..\noXData\noXdata.exe:
!include <sdkbld.mak>

# Build rule for EXE
clientNoXData.EXE: $(GLOBAL_OBJS) clientNoXData.obj ..\noXData\noXdata.exe
    $(link) $(linkdebug) $(guilflags) \
    clientNoXData.obj guid.obj debug.obj $(guilibs) $(EXTRA_LIBS) \
    -out:clientNoXData.exe $(MAPFILE)
    if not exist ..\bin mkdir ..\bin
    if not exist ..\bin\NoXData mkdir ..\bin\NoXData
    copy ClientNoXData.exe ..\bin\NoXData

clientWithXData.EXE: $(GLOBAL_OBJS) clientWithXData.obj ..\WithXData\withXdata.exe
    $(link) $(linkdebug) $(guilflags) \
    clientWithXData.obj guid.obj debug.obj $(guilibs) $(EXTRA_LIBS) \
    -out:clientWithXData.exe $(MAPFILE)
    if not exist ..\bin mkdir ..\bin
    if not exist ..\bin\WithXData mkdir ..\bin\WithXData
    copy ClientWithXData.exe ..\bin\WithXData


# Rules for cleaning out those old files
clean:
    @-del *.obj
    @-del *.exe
