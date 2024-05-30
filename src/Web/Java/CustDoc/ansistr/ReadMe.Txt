This is what you do to build binaries of the files in the ANSISTR directory:

1) Compile the C source
	cl /LD AnsiMarshaler.c /I..\..\..\include ..\..\..\lib\i386\msjava.lib user32.lib ole32.lib AnsiMarshaler.def

2) Compile the Java source
	jvc AnsiMarshaller.java

3) Copy files to run location
	copy *.dll ..\rundir
	copy *.class ..\rundir
