# ------------------------------------------------------------------------------
#
#       Copyright (c) 1996-1997  Microsoft Corporation
#
# ------------------------------------------------------------------------------

SAMPROOT	= ..

SDKROOT         = ..\$(SAMPROOT)

TARGET          = invokevm

build		= retail

CC		= cl.exe
LINK		= link.exe
JVC		= jvc.exe

PACKROOT	= ..

JVCSW		=

CFLAGSALL       = -c -I $(SDKROOT)\include
LFLAGSALL	= 

LIBS            = $(SDKROOT)\lib\i386\msjava.lib \
                  ole32.lib

!IF "$(build)" == "debug"

CFLAGS		= $(CFLAGSALL) -MLd -Zi -Fd$(TARGET).pdb
LINKFLAGS	= $(LFLAGSALL) -debug -pdb:$(TARGET).pdb

!ELSE

CFLAGS		= $(CFLAGSALL)
LINKFLAGS	= $(LFLAGSALL)

!ENDIF

all :   $(TARGET).exe TestClass.class

$(TARGET).exe : $(TARGET).obj
        $(LINK) $(LINKFLAGS) $(LIBS) $(TARGET).obj -implib:$(TARGET).lib -out:$(TARGET).exe

$(TARGET).obj : $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c

TestClass.class: TestClass.java
        $(JVC) TestClass.java
