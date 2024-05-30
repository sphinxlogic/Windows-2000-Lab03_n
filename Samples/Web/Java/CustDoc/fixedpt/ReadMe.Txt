This is what you do to build binaries of the files in the FIXEDPT directory:

1) Compile the C source
	cl /LD FixedPtMarshaler.c /I..\..\..\include ..\..\..\lib\i386\msjava.lib user32.lib ole32.lib FixedPtMarshaler.def

2) Compile the Java source
	jvc FixedPtMarshaler.java

3) Copy files to run location
	copy *.dll ..\rundir
	copy *.class ..\rundir
