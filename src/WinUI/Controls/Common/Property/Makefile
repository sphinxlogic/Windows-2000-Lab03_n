# Nmake macros for building Win32 apps

TARGETOS=BOTH
APPVER=4.0

!include <Win32.Mak>

all: Property.Exe

# Update the resource if necessary

Property.Res: Property.Rc Property.h Resource.h
    $(rc) $(rcflags) $(rcvars) Property.Rc

# Update the object file if necessary

Property.Obj: Property.c Property.h Resource.h
    $(cc) $(cflags) $(cvars) $(cdebug) Property.c

# Update the executable if necessary

Property.Exe: Property.Obj Property.Res
    $(link) $(linkdebug) $(guiflags) -out:Property.Exe Property.Obj Property.Res $(guilibs) ComCtl32.Lib
