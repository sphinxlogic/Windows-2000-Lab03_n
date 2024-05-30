This is what you do to build binaries of the files in the RECT directory:

1) Compile the C source
	cl /LD RectMarshaler.c /I..\..\..\include ..\..\..\lib\i386\msjava.lib user32.lib ole32.lib RectMarshaler.def

2) Compile the Java source
	jvc RectMarshaler.java

3) Copy files to run location
	copy *.dll ..\rundir
	copy *.class ..\rundir
