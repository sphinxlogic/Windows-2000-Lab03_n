#***************************************************************************
#
#  Copyright (c) 1997-1999 Microsoft Corporation.
#
#  File:   makefile
#
#  Module: WMI Object Path Parser Sample
#
#  Purpose: nmake makefile to build the WMI object path parser sample
#
#  History:
#
#***************************************************************************

target = pathtest.exe

objdir=debug

objlist = \
    $(objdir)\objpath.obj \
    $(objdir)\genlex.obj \
    $(objdir)\opathlex.obj \
    $(objdir)\pathtest.obj \

all: $(objdir)\$(target)


#---------------------------------------------------------------------


!if "$(PROCESSOR_ARCHITECTURE)"=="x86"
cc =  \
    cl -c -Od -G3 -D_MT -D_CONSOLE -DWIN32 -Z7 -GX \
   -W3 -Di386=1 -D_X86_=1 -I.
!else
cc =  \
    cl -c -Od -G3 -D_MT -D_CONSOLE -DWIN32 -Z7 -GX \
   -W3 -I.
!endif

link = \
    link -nodefaultlib -subsystem:console -pdb:none \
    -entry:mainCRTStartup -map:$(objdir)\mb.map -debug -debugtype:cv \
    -out:$(objdir)\$(target) \
	$(objlist) \
    wbemuuid.lib \
    shell32.lib \
    user32.lib \
    libcmt.lib \
    kernel32.lib \
    gdi32.lib \
    advapi32.lib \
    oldnames.lib \
    uuid.lib \
    ole32.lib \
    oleaut32.lib \
    wsock32.lib \
    mpr.lib


$(objdir)\$(target): $(objlist) 
   $(link) 

{.}.cpp{$(objdir)}.obj:
    if not exist $(objdir) md $(objdir)
    $(cc) $< -Fo$(objdir)\$(<B).obj


