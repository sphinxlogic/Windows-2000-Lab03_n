TARGETOS=BOTH
APPVER=4.0

!include <win32.mak>

LIBS = user32.lib ws2_32.lib

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

all:bcast.exe

bcast.exe:bcast.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe



