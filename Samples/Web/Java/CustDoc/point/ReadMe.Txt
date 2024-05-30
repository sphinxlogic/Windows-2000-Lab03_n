This is what you do to build binaries of the files in the POINT directory:

1) Compile the C source
	cl /LD PointMarshaler.c /I..\..\..\include ..\..\..\lib\i386\msjava.lib user32.lib ole32.lib PointMarshaler.def

2) Compile the Java source
	jvc PointMarshaler.java

3) Copy files to run location
	copy *.dll ..\rundir
	copy *.class ..\rundir
