============================================================================
This sample demonstrates Java->COM and COM->Java communications.

The sample is invoked from Java.  The constructor of the class we invoke 
instantiates a COM-implemented object.  Three methods are then exercised.

The first two methods take and return numeric arguments.  The third method
instantiates a Java-implemented object, and passes the interface pointer back
to Java, caching a local copy for its own use later on.  The new java object
is then used from both Java and COM transparently.  That is, the COM object
treats it no differently than any other COM object, and Java treats it as a
Java object.

Copyright (c) 1996-1997 Microsoft Corporation.  All rights reserved.

----------------------------------------------------------------------------
CONTENTS:

	odl\                            ** interface descriptions
		NatCom.odl
		jNatCom.odl

	com\                            ** COM server
		natcom.cpp
		natcom.def
		natcom.h
		makefile

	java\
		_1\                     ** run this to exec sample
			JMain.java
			makefile

		_2\                     ** called from COM and java
			JMain.java
			reg.bat
			makefile

----------------------------------------------------------------------------
BUILD INSTRUCTIONS:
The executable files that are built from this sample are included, so you do 
not need to build the sample in order to run it.  However, the following
information is included if you want to build the sample yourself. 

Dependencies:
  jvc.exe, cpdbase.dll, msjvc.dll, jactivex.exe, javareg.exe.
  (All are included in the SDK BIN directory.
   JVC.EXE must be version 1.02.3920 or later.)
	
To build from this subdirectory:
  nmake /a
	

----------------------------------------------------------------------------
RUNNING THE SAMPLE:

  Use the GO.BAT in this subdirectory.  This batch file does the following:
	
  1. Registers the COM server (regsvr32 com\natcom.dll)

  2. Registers the Java server (java\_2\reg.bat)

  3. Executes JVIEW java._1.JMain
     (Note: Your CLASSPATH must include '.' subdirectory)

  4. Un-registers the Java server (java\_2\unreg.bat)
  
  5. Un-registers the COM server (regsvr32 /u com\natcom.dll)


----------------------------------------------------------------------------
EXPECTED CONSOLE OUTPUT:

2 * 5 = 10
inc.Square(10) = 100
invoked from COM: Hello World
invoked from Java: Hello World


============================================================================
