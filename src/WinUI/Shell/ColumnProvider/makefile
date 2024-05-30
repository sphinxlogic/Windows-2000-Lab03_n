# Nmake macros for building Win32 apps

TARGETOS=WINNT
APPVER=5.0
_WIN32_IE=0x0500


!include <win32.mak>

PROJ=ShortName

all: $(PROJ).dll

PROJ_OBJS = ClassFactory.obj ColumnProvider.obj Clsid.obj RegisterServer.obj UnregisterServer.obj NullDacl.obj ShortName.obj
OTHER_LIBS = shell32.lib shlwapi.lib
OTHER_CFLAGS = -DWIN32_LEAN_AND_MEAN -DUNICODE -D_UNICODE
OTHER_RCOPTS = -DWIN32_LEAN_AND_MEAN

# Update the resource if necessary

$(PROJ).Res: $(PROJ).rc $(PROJ).h Resource.h
    $(rc) $(rcflags) $(rcvars) $(OTHER_RCOPTS) $(PROJ).rc

# Update the object file if necessary

ClassFactory.obj: ClassFactory.cpp ShortName.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) ClassFactory.cpp

ColumnProvider.obj: ColumnProvider.cpp ShortName.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) ColumnProvider.cpp

Clsid.obj: Clsid.cpp ShortName.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) Clsid.cpp

RegisterServer.obj: RegisterServer.cpp ShortName.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) RegisterServer.cpp

UnregisterServer.obj: UnregisterServer.cpp ShortName.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) UnregisterServer.cpp

NullDacl.obj: NullDacl.cpp ShortName.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) NullDacl.cpp

ShortName.obj: ShortName.cpp ShortName.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) $(OTHER_CFLAGS) ShortName.cpp

# Update the executable if necessary

$(PROJ).dll: $(PROJ_OBJS) $(PROJ).res 
    $(link) $(ldebug) $(dlllflags) /BASE:0x66810000 /DEF:$(PROJ).def -out:$(PROJ).dll $(PROJ).res $(olelibsmt) $(OTHER_LIBS) $(PROJ_OBJS)
