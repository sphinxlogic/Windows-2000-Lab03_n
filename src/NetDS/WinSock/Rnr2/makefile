!include <win32.mak>

LIBS = kernel32.lib user32.lib  ws2_32.lib oldnames.lib libcmt.lib


.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

all:RnrCs.exe

RnrCs.exe:RnrCs.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)


clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe