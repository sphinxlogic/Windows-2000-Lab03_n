DIRS =          \
    Cpp\~       \
    Java\~      \
    ScriptLet\~ \
    VB\~        \


SDKPROJ=Internet\IIS\Components

#
# This is a Platform SDK branch makefile.  It is used to allow NMAKE,
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
# Include SDKPropBld.mak in order to get standard build options, environment
#  variables, and macros.  The SDKPropBld.Mak file is installed with the SDK
#  in the include directory.
# 

!include <SDKPropBld.Mak>

# 
# In order to build "all," process each of the entries in the DIRS list.
#

all: $(DIRS)

#
# In order to build each of the entries in the DIRS list, change dir into the
#  directory in question, echo the current location, run nmake recursively, 
#  and change dir back to the original directory level.  This four step process 
#  is encapsulated in SDKBld.Mak which is installed with the SDK in the include
#  directory.
#

$(DIRS):
!include <SDKBld.Mak>
