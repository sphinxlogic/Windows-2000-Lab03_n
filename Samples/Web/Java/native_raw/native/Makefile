# ------------------------------------------------------------------------------
#
# 	Copyright (c) 1996-1997  Microsoft Corporation
#
# ------------------------------------------------------------------------------

SAMPROOT	= ..

SDKROOT         = ..\..\$(SAMPROOT)

TARGET		= natlib

build		= retail

CC		= cl.exe
LINK		= link.exe
JVC		= jvc.exe

PACKROOT	= ..

JVCSW		=

DLLFLAGS	= -dll -entry:_DllMainCRTStartup@12
CFLAGSALL	= -c -I $(SDKROOT)\include
LFLAGSALL	= 

LIBS		= $(SDKROOT)\lib\i386\msjava.lib

!IF "$(build)" == "debug"

CFLAGS		= $(CFLAGSALL) -MLd -Zi -Fd$(TARGET).pdb
LINKFLAGS	= $(LFLAGSALL) -debug -pdb:$(TARGET).pdb

!ELSE

CFLAGS		= $(CFLAGSALL)
LINKFLAGS	= $(LFLAGSALL)

!ENDIF

all : 	$(TARGET).dll

$(TARGET).dll : $(TARGET).obj
        $(LINK) $(LINKFLAGS) $(DLLFLAGS) $(LIBS) $(TARGET).obj -implib:$(TARGET).lib -def:$(TARGET).def -out:$(TARGET).dll
	copy $(TARGET).dll $(SAMPROOT)\binaries

$(TARGET).obj : $(TARGET).c JMain.h JThread1.h JThread2.h JFoo.h
	$(CC) $(CFLAGS) $(TARGET).c

JMain.h : ..\java\JMain.class
	cd ..\java
	nmake $(PACKROOT)\native\JMain.h
	cd ..\native

JFoo.h : ..\java\JFoo.class
	cd ..\java
	nmake $(PACKROOT)\native\JFoo.h
	cd ..\native

JThread1.h : ..\java\JThread1.class
	cd ..\java
	nmake $(PACKROOT)\native\JThread1.h
	cd ..\native

JThread2.h : ..\java\JThread2.class
	cd ..\java
	nmake $(PACKROOT)\native\JThread2.h
	cd ..\native

