!include <win32.mak>

LIBS = kernel32.lib user32.lib oldnames.lib libcmt.lib ws2_32.lib mswsock.lib

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

all:iocpserver.exe iocpserverex.exe iocpclient.exe

iocpserver.exe:iocpserver.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

iocpserverex.exe:iocpserverex.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

iocpclient.exe:iocpclient.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
