!include <win32.mak>

LIBS = kernel32.lib user32.lib gdi32.lib ws2_32.lib snmpapi.lib wsnmp32.lib mgmtapi.lib oldnames.lib libcmt.lib

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

all:wsnmputil.exe

wsnmputil.exe:wsnmputil.obj helper.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
