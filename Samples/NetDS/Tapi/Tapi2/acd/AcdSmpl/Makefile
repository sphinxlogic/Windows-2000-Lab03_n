# Define NODEBUG to build ACDSMPL without debugging information.
# Define UNICODE to build ACDSMPL with UNICODE characters.

TARGETOS=WINNT

!include <Win32.Mak>

unicode = -DUNICODE

cflags=$(cflags) -DWIN32_LEAN_AND_MEAN

all: acdsmpl.exe

# Update the resource if necessary

acdsmpl.res: acdsmpl.rc resource.h
    $(rc) $(rcvars) -r acdsmpl.rc

# Update the object files if necessary

acdsmpl.obj: acdsmpl.c resource.h acdsmpl.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(unicode) acdsmpl.c

acdtapi.obj: acdtapi.c resource.h acdsmpl.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(unicode) acdtapi.c

acdutils.obj: acdutils.c resource.h acdsmpl.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(unicode) acdutils.c

# Update the executable file if necessary, and if so, add the resource back in.

acdsmpl.exe: acdsmpl.obj acdtapi.obj acdutils.obj acdsmpl.res
    $(link) $(linkdebug)  $(guiflags) -out:acdsmpl.exe\
    acdsmpl.obj acdtapi.obj acdutils.obj acdsmpl.res\
    version.lib tapi32.lib comctl32.lib $(guilibsmt)
