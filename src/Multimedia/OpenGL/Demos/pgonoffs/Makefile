
TARGETOS=WINNT

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

TARGET  = toffset

# application specific C defines

cf = -DNT -DWIN -DNOT_IMPLEMENTED $(scall)

# This line allows NMAKE to work as well

all: $(TARGET).exe

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $(cf) $*.c

$(TARGET).exe: toffset.obj  trackbal.obj    
    $(link) $(linkdebug) $(savlflags) -machine:$(CPU) -subsystem:windows -entry:mainCRTStartup -out:$(TARGET).exe  $** $(guilibs) opengl32.lib glu32.lib glaux.lib comdlg32.lib

!IF ("$(TARGETLANG)" == "LANG_JAPANESE") && ("$(OS)" == "Windows_NT")
    rlman -p 932 -n 17 1 -a $*.scr $*.tok $*.scr
!ENDIF
