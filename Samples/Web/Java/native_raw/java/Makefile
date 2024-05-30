# Copyright (c) 1997 Microsoft Corporation.  All rights reserved.

# paths ------------------------------------------------------------------------

PACKROOT	= ..

# utilities --------------------------------------------------------------------

JVC		= jvc.exe
JAVAH		= msjavah.exe

# switches ---------------------------------------------------------------------

JVCSW		= -cp:p $(PACKROOT)
JAVAHSW		=

# targets ----------------------------------------------------------------------

all :	JMain.class \
	$(PACKROOT)\native\JMain.h \
	$(PACKROOT)\native\JFoo.h \
	$(PACKROOT)\native\JThread1.h \
	$(PACKROOT)\native\JThread2.h \
	JFoo.class \
	JThread1.class \
	JThread2.class

# dependencies -----------------------------------------------------------------

JMain.class : JMain.java JThread1.class JThread2.class
	$(JVC) $(JVCSW) jmain.java
	copy JMain.class $(PACKROOT)\binaries

JFoo.class : JFoo.java
	$(JVC) $(JVCSW) jfoo.java
	copy JFoo.class $(PACKROOT)\binaries

JThread1.class : JThread1.java
	$(JVC) $(JVCSW) JThread1.java
	copy JThread1.class $(PACKROOT)\binaries

JThread2.class : JThread2.java
	$(JVC) $(JVCSW) JThread2.java
	copy JThread2.class $(PACKROOT)\binaries

$(PACKROOT)\native\JThread1.h : JThread1.class
	$(JAVAH) $(JAVAHSW) -o $(PACKROOT)\native\JThread1.h JThread1

$(PACKROOT)\native\JThread2.h : JThread2.class
	$(JAVAH) $(JAVAHSW) -o $(PACKROOT)\native\JThread2.h JThread2

$(PACKROOT)\native\JFoo.h : JFoo.class
	$(JAVAH) $(JAVAHSW) -o $(PACKROOT)\native\JFoo.h JFoo

$(PACKROOT)\native\JMain.h : JMain.class
	$(JAVAH) $(JAVAHSW) -o $(PACKROOT)\native\JMain.h JMain
