# Nmake macros for building Win32 apps

TARGETOS=BOTH
APPVER=4.0

!include <win32.mak>

PROJ=Cleanup

all: $(PROJ).dll

PROJ_OBJS = ClassFactory.obj EmptyVolumeCache.obj RegisterServer.obj UnregisterServer.obj NullDacl.obj Cleanup.obj
OTHER_LIBS = shell32.lib shlwapi.lib
OTHER_CFLAGS = -DWIN32_LEAN_AND_MEAN -DWINVER=0x0400
OTHER_RCOPTS = -DWIN32_LEAN_AND_MEAN

# Update the resource if necessary

$(PROJ).Res: $(PROJ).rc $(PROJ).h Resource.h
    $(rc) $(rcflags) $(rcvars) $(OTHER_RCOPTS) $(PROJ).rc

# Update the object file if necessary

ClassFactory.obj: ClassFactory.cpp Cleanup.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) ClassFactory.cpp

EmptyVolumeCache.obj: EmptyVolumeCache.cpp Cleanup.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) EmptyVolumeCache.cpp

RegisterServer.obj: RegisterServer.cpp Cleanup.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) RegisterServer.cpp

UnregisterServer.obj: UnregisterServer.cpp Cleanup.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) UnregisterServer.cpp

NullDacl.obj: NullDacl.cpp Cleanup.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) NullDacl.cpp

Cleanup.obj: Cleanup.cpp Cleanup.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) Cleanup.cpp

# Update the executable if necessary

$(PROJ).dll: $(PROJ_OBJS) $(PROJ).res 
    $(link) $(ldebug) $(dlllflags) /DEF:$(PROJ).def -out:$(PROJ).dll $(PROJ).res $(olelibsmt) $(OTHER_LIBS) $(PROJ_OBJS)
