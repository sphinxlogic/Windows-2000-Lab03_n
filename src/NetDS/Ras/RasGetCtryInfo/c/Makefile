!include <win32.mak>

LIBS = kernel32.lib rasapi32.lib

RasGetCtryInfo.exe : RasGetCtryInfo.obj
    $(link) $(debug) $** $(LIBS) -out:$*.exe 

RasGetCtryInfo.obj: RasGetCtryInfo.c
    $(cc) $(cdebug) $(cflags) $(cvarsmt) RasGetCtryInfo.c

nmake cleanall :
    -del *.exe *.obj