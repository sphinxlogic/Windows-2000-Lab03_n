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

PROJ = noxdata

DIRS = \
    Handler\~   


all: $(PROJ).exe $(DIRS)

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
PROJ_OBJS  = classfact.obj NumToText.obj numtoTextsvr.obj 
GLOBAL_DEP = NumToText.h ..\common\guid.h ..\common\debug.h ..\NumToTextPS\server.h
# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) uuid.lib ole32.lib oleaut32.lib

guid.obj : ..\common\guid.cpp
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c ..\common\guid.cpp
debug.obj : ..\common\debug.cpp
    $(CC) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c ..\common\debug.cpp

..\NumtxtPS\ServerPS.dll:
!include <sdkbld.mak>


# Build rule for EXE
$(PROJ).EXE: $(GLOBAL_OBJS) $(PROJ_OBJS) 
    $(link) $(linkdebug) $(guilflags) \
    $(PROJ_OBJS) guid.obj debug.obj $(guilibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)
    if not exist ..\bin mkdir ..\bin
    if not exist ..\bin\$(PROJ) mkdir ..\bin\$(PROJ)
    copy $(PROJ).exe ..\bin\$(PROJ)



# Rules for cleaning out those old files
clean:
    @-del *.obj
    @-del *.exe


SDKPROJ =COM\Fundamentals\ltwthandlr\NoXData


#
# This is a Platform SDK non-leaf-node makefile.  It is used to allow NMAKE, 
#  or a similar tool, to recursively build all of the samples in a directory 
#  tree.  To add or remove a directory from the build process, modify the 
#  DIRS list above.  
#
# The SDKPROJ macro (above) is defined solely for the purpose of echoing
#  the current directory location to the screen.  
#
# Do not modify this makefile except for the DIRS and SDKPROJ macros above.
#

#
# Include sdkpropbld.mak in order to get standard build options, environment
#  variables, and macros.  The sdkpropbld.mak file is installed with the SDK 
#  in the include directory.
# 

!include <sdkpropbld.mak>


#
# In order to build each of the entries in the DIRS list, change dir into the
#  directory in question, echo the current location, run nmake recursively, 
#  and change dir back to the original directory level.  This four step process 
#  is encapsulated in sdkbld.mak which is installed with the SDK in the include
#  directory.
#

$(DIRS):
!include <sdkbld.mak>
