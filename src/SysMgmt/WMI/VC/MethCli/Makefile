#***************************************************************************
#
#  Copyright (c) 1997-1999 Microsoft Corporation.
#
#  File:   makefile
#
#  Module: WMI Method Client Sample
#
#  Purpose: nmake makefile to build the WMI method client sample
#
#  History:
#
#***************************************************************************

TARGET  = methcli.exe

goal:   $(TARGET)

OBJS   = $(OBJDIR)\methcli.obj

LIBS = msvcrt.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib \
 advapi32.lib ole32.lib oleaut32.lib uuid.lib wbemuuid.lib

#
# Compiler and link flags
#

!ifndef NODEBUG
OBJDIR=debug
LINK    = -debug:full -debugtype:cv /NOD /entry:mainCRTStartup
CFLAGS  = -c -Od -Z7 -Ze -W3 -G3s -nologo \
 -DWIN32 -DWIN32ANSI -DSTRICT -DDEBUG
!else
OBJDIR=release
LINK    = -debug:none  /NOD /entry:mainCRTStartup
CFLAGS  = -c -Oat -Ze -W3 -G3s -nologo  \
 -DWIN32 -DWIN32ANSI -DSTRICT
!endif #NODEBUG

cc = cl $(CFLAGS)

.cpp{$(OBJDIR)}.obj:
    if not exist $(OBJDIR) md $(OBJDIR)
    $(cc) $< -Fo$(OBJDIR)\$(<B).obj

$(TARGET) : $(OBJS) $(DEFFILE)
    link @<<    
    $(LINK)
    -out:$(OBJDIR)\$(TARGET)
    -subsystem:console,4.00
    $(OBJS)
    $(LIBS) 
<<

##### Dependencies #####

methcli.obj   : methcli.cpp
