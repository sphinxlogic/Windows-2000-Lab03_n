# Copyright (c) 1997 Microsoft Corporation.  All rights reserved.
#
# paths ------------------------------------------------------------------------

PACKROOT	= ..

ODLLOC		= $(PACKROOT)\odl

# names ------------------------------------------------------------------------

TARGET		= natcom

# default build ----------------------------------------------------------------

build		= retail

# utilities --------------------------------------------------------------------

CC		= cl.exe
LINK		= link.exe
MAPSYM		= mapsym.exe
MKTYPLIB	= mktyplib.exe

# flags & libraries ------------------------------------------------------------

DLLFLAGS	= -dll
CFLAGSALL	= -c -I ..\1
LFLAGSALL	= -WARN:3 -map:$(TARGET).map

LIBS		= uuid.lib advapi32.lib ole32.lib

!IF "$(build)" == "debug"

CFLAGS		= $(CFLAGSALL) -MLd -Zi -Fd$(TARGET).pdb -D_DEBUG
LINKFLAGS	= /debug /pdb:$(TARGET).pdb $(LFLAGSALL)

!ELSE

CFLAGS		= $(CFLAGSALL)
LINKFLAGS	= $(LFLAGSALL)

!ENDIF

# target -----------------------------------------------------------------------

all :	common.h	\
	$(TARGET).dll

# dependencies -----------------------------------------------------------------

$(TARGET).dll : $(TARGET).obj $(TARGET).def
	$(LINK) $(LINKFLAGS) $(DLLFLAGS) $(LIBS) $(TARGET).obj -implib:$(TARGET).lib \
		-def:$(TARGET).def -nodefaultlib:oldnames.lib
	$(MAPSYM) $(TARGET).map  -o $(TARGET).sym

$(TARGET).obj : $(TARGET).cpp $(TARGET).h common.h jnatcom.h
	$(CC) $(CFLAGS) $(TARGET).cpp

common.h : $(ODLLOC)\natcom.odl jnatcom.h
	$(MKTYPLIB) $(ODLLOC)\natcom.odl -H .\common.h -tlb .\natcom.tlb
	del .\natcom.tlb

jnatcom.tlb jnatcom.h : $(ODLLOC)\jnatcom.odl
	$(MKTYPLIB) $(ODLLOC)\jnatcom.odl -h .\jnatcom.h -tlb .\jnatcom.tlb

