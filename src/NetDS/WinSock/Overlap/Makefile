APPVER = 4.0
TARGETOS=WINNT

!include <Win32.Mak>

ALLEXES = overlap.exe

all: $(ALLEXES)

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

$(ALLEXES): $*.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj user32.lib $(conlibsmt)



