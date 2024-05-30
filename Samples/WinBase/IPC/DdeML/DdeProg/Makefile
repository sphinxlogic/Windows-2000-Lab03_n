# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: proghelp.dll

# Update the object files if necessary

proghelp.obj: proghelp.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) proghelp.c


# Update the dynamic link library

proghelp.dll: proghelp.obj proghelp.def
    $(link) $(linkdebug) $(dllflags)     \
    -base:0x1C000000  \
    -out:proghelp.dll   \
    -entry:DllMain    \
    -machine:$(CPU)   \
    -subsystem:WINDOWS \
    -implib:proghelp.lib \
    -def:proghelp.def \
     proghelp.obj $(guilibsdll)


