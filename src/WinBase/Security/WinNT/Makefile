Dirs =         \
    AclApi\~   \
    Audit\~    \
    Check_sd\~ \
    DispTrus\~ \
    DomTrust\~ \
    Gina\~     \
    GinaStub\~ \
    HttpAuth\~ \
    LogonNP\~ \
    LsaPrivs\~ \
    LsaSamp\~  \
    MachAcct\~ \
    MyToken\~  \
    PwdFilt\~  \
    RCmd\~     \
    SampSSP\~  \
    Sd_flppy\~ \
    SecFile\~  \
    SecPerf\~  \
    SecPrint\~ \
    SidCln\~   \
    SecurObj\~ \
    SockAuth\~ \
    SubAuth\~  \
    SuperUsr\~ \
    TakeOwn\~  \
    TextSid\~  \

SDKPROJ =WinBase\Security\WinNT

#
# This is a Platform SDK non-leaf-node makefile.  It is used to allow NMAKE,
#  or a similar tool, to recursively build all of the samples in a directory 
#  tree.  To add or remove a directory from the build process, modify the 
#  Dirs list above.
#
# The SDKPROJ macro (above) is defined solely for the purpose of echoing
#  the current directory location to the screen.  
#
# Do not modify this Makefile except for the Dirs and SDKPROJ macros above.
#

#
# Include SDKPropBld.Mak in order to get standard build options, environment
#  variables, and macros.  The SDKPropBld.Mak file is installed with the SDK
#  in the Include directory.
# 

!Include <SDKPropBld.Mak>

# 
# In order to build "all," process each of the entries in the Dirs list.
#

all: $(Dirs)


#
# In order to build each of the entries in the Dirs list, change dir into the
#  directory in question, echo the current location, run nMake recursively,
#  and change dir back to the original directory level.  This four step process 
#  is encapsulated in SDKBld.Mak which is installed with the SDK in the Include
#  directory.
#

$(Dirs):
!Include <SDKBld.Mak>
