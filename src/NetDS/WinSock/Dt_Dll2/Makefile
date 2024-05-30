TARGETOS    = BOTH
APPVER      = 4.0

!include    <win32.mak>

all:        dt_dll.dll

dt_dll.dll: dt_dll.obj DTHandler.obj SocketMon.obj
            $(link) $(dlllflags) $(guilibsdll)\
            -export:WSAPreApiNotify -export:WSAPostApiNotify\
            -out:dt_dll.dll $**
	
.cpp.obj:   
            $(cc) $(cflags) -DSTRICT $(cvarsdll) $*.cpp

clean:
            del *.obj *.dll *.lib *.exp
