
! include <ntwin32.mak>

# define these if you want a debug version
#PDB = IpRoute.pdb
#CDEBUG= -Zi -Fd"$(PDB)"
#LDEBUG = -debug:full

LIBS = kernel32.lib msvcrt.lib wsock32.lib iphlpapi.lib

.cpp.obj:
	$(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

all:IpRoute.exe 

IpRoute.exe:IpRoute.obj
	$(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj $(conlibsmt)  $(LIBS)
# uncomment the line below for a debug build
#	-pdb:$(PDB)  \
	

clean:
	-del *.obj

cleanall:clean
	-del *.exe
