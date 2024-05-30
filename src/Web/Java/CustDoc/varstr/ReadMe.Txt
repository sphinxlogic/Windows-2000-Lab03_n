This is what you do to build binaries of the files in the VARSTR directory:

1) Compile the C source
	cl /LD VarStrMarshaler.c /I..\..\..\include ..\..\..\lib\i386\msjava.lib user32.lib ole32.lib oleaut32.lib VarStrMarshaler.def

2) Compile the Java source
	jvc VarStrMarshaler.java

3) Copy files to run location
	copy *.dll ..\rundir
	copy *.class ..\rundir
