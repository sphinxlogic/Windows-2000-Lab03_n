# ------------------------------------------------------------------------------
#
# 	Copyright (c) 1996-1997  Microsoft Corporation
#
# ------------------------------------------------------------------------------

SAMPROOT	= ..

SDKROOT         = ..\..\$(SAMPROOT)

TARGET          = SieveDemo

build		= retail

CC		= cl.exe
LINK		= link.exe
JVC		= jvc.exe
MSJAVAH         = msjavah.exe

PACKROOT	= ..

JVCSW		=

DLLFLAGS	= -dll -entry:_DllMainCRTStartup@12
CFLAGSALL	= -c -I $(SDKROOT)\include
LFLAGSALL	= 

!IF "$(build)" == "debug"

CFLAGS		= $(CFLAGSALL) -MLd -Zi -Fd$(TARGET).pdb
LINKFLAGS	= $(LFLAGSALL) -debug -pdb:$(TARGET).pdb

!ELSE

CFLAGS		= $(CFLAGSALL)
LINKFLAGS	= $(LFLAGSALL)

!ENDIF

all :   Sieve.class SieveDemo.class $(TARGET).dll

Sieve.class: Sieve.java
        $(JVC) Sieve.java

Sieve.h: Sieve.class
        $(MSJAVAH) Sieve

SieveDemo.class: SieveDemo.java
        $(JVC) SieveDemo.java

$(TARGET).dll : $(TARGET).obj
        $(LINK) $(LINKFLAGS) $(DLLFLAGS) $(LIBS) $(TARGET).obj -implib:$(TARGET).lib -def:$(TARGET).def -out:$(TARGET).dll

$(TARGET).obj : $(TARGET).c Sieve.h
	$(CC) $(CFLAGS) $(TARGET).c

