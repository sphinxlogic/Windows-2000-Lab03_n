# Copyright (c) 1997 Microsoft Corporation.  All rights reserved.

# paths ------------------------------------------------------------------------

PACKROOT	= ..\..
TLBDIR = $(PACKROOT)\tlb\jnatcom
ODLLOC		= $(PACKROOT)\odl
INC		= $(PACKROOT)\inc


# utilities --------------------------------------------------------------------
# NOTE: You must be using JVC.EXE version 1.02.3920 or later to generate class
# files with COM attributes.  Be sure an updated JVC.EXE and JACTIVEX.EXE are
# visible in your path.  Both of these items are included in the SDK. 

JVC		    = jvc.exe
JAX		    = jactivex.exe
MKTYPLIB	= mktyplib.exe


# switches ---------------------------------------------------------------------

JVCSW		= /x- -cp:p $(PACKROOT)
JAXSW	    = -javatlb -G3.1 -cj -p tlb -d $(PACKROOT)


# targets ----------------------------------------------------------------------

all :	JMain.class


# dependencies -----------------------------------------------------------------

JMain.class : JMain.java $(TLBDIR)\jCNatComImpl.class $(TLBDIR)\jCNatCom.class $(TLBDIR)\jINatCom.class
	$(JVC) $(JVCSW) JMain.java

$(TLBDIR)\jCNatComImpl.class : $(TLBDIR)\jCNatComImpl.java
	$(JVC) $(JVCSW) $(TLBDIR)\jCNatComImpl.java

$(TLBDIR)\jCNatCom.class : $(TLBDIR)\jCNatCom.java
	$(JVC) $(JVCSW) $(TLBDIR)\jCNatCom.java

$(TLBDIR)\jINatCom.class : $(TLBDIR)\jINatCom.java
	$(JVC) $(JVCSW) $(TLBDIR)\jINatCom.java

$(TLBDIR)\jCNatComImpl.java $(TLBDIR)\jCNatCom.java $(TLBDIR)\jINatCom.java: jnatcom.tlb
	$(JAX) $(JAXSW) jnatcom.tlb

jnatcom.tlb : $(ODLLOC)\jnatcom.odl
	$(MKTYPLIB) $(ODLLOC)\jnatcom.odl -tlb .\jnatcom.tlb
