# Copyright (c) 1997 Microsoft Corporation.  All rights reserved.

# paths ------------------------------------------------------------------------

PACKROOT	= ..\..
TLBDIR = $(PACKROOT)\tlb\natcom
ODLLOC		= $(PACKROOT)\odl
INC		= $(PACKROOT)\inc


# utilities --------------------------------------------------------------------
# NOTE: You must be using JVC.EXE version 1.02.3920 or later to generate class
# files with COM attributes.  Be sure an updated JVC.EXE and JACTIVEX.EXE are
# visible in your path.  Both of these items are included in the SDK. 

JVC		    = jvc.exe
JAX         = jactivex.exe
MKTYPLIB	= mktyplib.exe


# switches ---------------------------------------------------------------------

JVCSW		= /x- -cp:p $(PACKROOT)
JAXSW	    = -javatlb -G3.1 -p tlb -d $(PACKROOT)


# targets ----------------------------------------------------------------------

all :	JMain.class


# dependencies -----------------------------------------------------------------

JMain.class : JMain.java $(TLBDIR)\CNatCom.class $(TLBDIR)\INatCom.class
	$(JVC) $(JVCSW) JMain.java

$(TLBDIR)\CNatCom.class : $(TLBDIR)\CNatCom.java
  $(JVC) $(JVCSW) $(TLBDIR)\CNatCom.java

$(TLBDIR)\INatCom.class : $(TLBDIR)\INatCom.java
  $(JVC) $(JVCSW) $(TLBDIR)\INatCom.java

$(TLBDIR)\CNatCom.java $(TLBDIR)\INatCom.java : natcom.tlb $(TLBDIR)\jINatCom.java
	$(JAX) $(JAXSW) natcom.tlb

$(TLBDIR)\jINatCom.class : $(TLBDIR)\jINatCom.java
  $(JVC) $(JVCSW) $(TLBDIR)\jINatCom.java

$(TLBDIR)\jINatCom.java : jnatcom.tlb
	$(JAX) $(JAXSW) jnatcom.tlb

jnatcom.tlb : $(ODLLOC)\jnatcom.odl
	$(MKTYPLIB) $(ODLLOC)\jnatcom.odl -tlb .\jnatcom.tlb

natcom.tlb : $(ODLLOC)\natcom.odl jnatcom.tlb
	$(MKTYPLIB) $(ODLLOC)\natcom.odl -tlb .\natcom.tlb
