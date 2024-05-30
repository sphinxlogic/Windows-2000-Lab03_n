#Copyright 1993-1999 Microsoft Corporation

TARGETOS=WINNT

!Include <Win32.Mak>

GenGL.Exe: GenGL.Obj GenGL.Res Render.Obj
    $(link) $(linkdebug) $(guilflags) -out:GenGL.Exe \
    GenGL.Obj Render.Obj GenGL.Res $(guilibsdll) OpenGL32.lib GLu32.lib

# Update the Object file if necessary

GenGL.Obj: GenGL.c GenGL.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(cf) GenGL.c

Render.Obj: Render.c GenGL.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(cf) Render.c

GenGL.Res: GenGL.Rc GenGLRc.h
    $(rc) -r GenGL.Rc
