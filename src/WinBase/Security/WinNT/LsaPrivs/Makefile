!include <Win32.Mak>

proj=lsaprivs

all: $(proj).exe

$(proj).obj: $(proj).c
    $(cc) $(cflags) $(cvars) $(cdebug) -I..\include $(proj).c

$(proj).exe: $(proj).obj
    $(link) $(ldebug) -out:$(proj).exe $(proj).obj advapi32.lib user32.lib
