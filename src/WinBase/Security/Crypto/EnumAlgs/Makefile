TARGETOS=WINNT
APPVER=4.0

!include <Win32.Mak>

all: enumalgs.exe

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

enumalgs.exe: enumalgs.obj
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(conlibsdll) advapi32.lib
