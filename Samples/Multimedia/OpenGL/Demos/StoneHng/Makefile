# Copyright 1993 - 1999 Microsoft Corporation

TARGETOS=WINNT

!include <Win32.Mak>

# application specific C defines

cf = -DNT -DWIN -DNOT_IMPLEMENTED -DDATADIR= $(scall) -W3 -DTEXTURE=1

Stonehen.Exe: Atmosphe.Obj Ellipse.Obj Stonehen.Obj Point.Obj Ring.Obj CallBack.Obj\
    RoundWal.Obj Scene.Obj Stone.Obj Telescop.Obj TimeDate.Obj Stonehen.Res SetPixel.Obj RGBImage.Obj
    $(link) $(linkdebug) $(guilflags) -out:Stonehen.Exe \
    Atmosphe.Obj Ellipse.Obj Point.Obj Ring.Obj Stonehen.Obj CallBack.Obj\
    RoundWal.Obj Scene.Obj Stone.Obj Telescop.Obj TimeDate.Obj Stonehen.Res SetPixel.Obj RGBImage.Obj \
    $(guilibs) OpenGL32.Lib GLu32.Lib GLAux.Lib

.Cxx.Obj:
    $(cc) $(cflags) $(cvars) $(cdebug) $(cf) $<

# Update the object file if necessary

Atmosphe.Obj: Atmosphe.Cxx Atmosphe.h

CallBack.Obj: CallBack.Cxx CallBack.h

Ellipse.Obj: Ellipse.Cxx Ellipse.h

# main.Obj: main.Cxx

Point.Obj: Point.Cxx Point.h

Ring.Obj: Ring.Cxx Ring.h

RoundWal.Obj: RoundWal.Cxx RoundWal.h

RGBImage.Obj: RGBImage.Cxx

Scene.Obj: Scene.Cxx Scene.h

Stone.Obj: Stone.Cxx Stone.h

Telescop.Obj: Telescop.Cxx Telescop.h

TimeDate.Obj: TimeDate.Cxx TimeDate.h

Stonehen.Obj: Stonehen.Cxx Stonehen.h

SetPixel.Obj: SetPixel.Cxx SetPixel.h

Stonehen.Res: Stonehen.Rc Stonerc.h
    $(rc) -DTEXTURE=1 -r Stonehen.Rc
