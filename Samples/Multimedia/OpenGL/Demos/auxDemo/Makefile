
TARGETOS=WINNT

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

TARGET = auxdemo

# application specific C defines

cf = -DNT -DWIN -DNOT_IMPLEMENTED $(scall)

# This line allows NMAKE to work as well

all: $(TARGET).exe

# Update the object file if necessary

$(TARGET).obj: $(TARGET).c
    $(cc) $(cflags) $(cvars) $(cdebug) $(cf) $(TARGET).c

$(TARGET).exe: $(TARGET).obj
    $(link) $(linkdebug) $(guilflags) -subsystem:windows -entry:mainCRTStartup -out:$(TARGET).exe $(TARGET).obj $(guilibs) opengl32.lib glu32.lib glaux.lib
