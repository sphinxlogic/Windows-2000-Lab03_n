
TARGETOS=WINNT

!include <Win32.Mak>

all: glaux.lib

glaux.lib: font.obj  \
           glaux.obj \
            image.obj   \
            shapes.obj  \
            teapot.obj  \
            tk.obj      \
            tkdib.obj   \
            tkfont.obj  \
            tkimage.obj \
            vect3d.obj  \
            xform.obj   
  $(implib) -out:$*.lib $** 

.c.obj:
  $(cc) $(cdebug) $(cflags) $(scall) $(cvars) $*.c
