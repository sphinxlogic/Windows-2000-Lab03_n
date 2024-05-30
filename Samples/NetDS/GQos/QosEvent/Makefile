# Nmake macros for building Windows 32-Bit apps
TARGETOS=BOTH
# change APPVER to 4.0 to target NT4 and 95 (without QOS capability)
APPVER=5.0

!include <win32.mak>

comobj=chkqos.obj findsp.obj getqos.obj setqos.obj printqos.obj
mainobjs=qosevent.obj sender.obj receiver.obj


all: qosevent.exe

# Update the resource if necessary

# Update the object file if necessary

.cpp.obj: 
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.cpp

# Update the executable file if necessary, and if so, add the resource back in.

qosevent.exe: $(mainobjs) $(comobj) $(common_objs) 
    $(link) $(linkdebug) $(conlflags) -out:qosevent.exe $(mainobjs) $(comobj) $(conlibsmt) ws2_32.lib


clean:
	del *.obj
	del *.exe
