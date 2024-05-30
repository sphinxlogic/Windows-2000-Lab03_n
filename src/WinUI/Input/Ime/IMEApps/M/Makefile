# Nmake macros for building Win32 & Win64 apps

APPVER=5.0

!include <win32.mak>
cflags     = -DUSEWAPI $(cflags)

all: IMEAppsm.Exe

LIBS=imm32.lib comctl32.lib
LINKFILES=Comp.Obj Data.Obj IMEApps.Obj IMEMenu.Obj Mode.Obj Paint.Obj SetComp.Obj \
          Status.Obj Subs.Obj Toolbar.Obj WSubs.Obj IMEApps.Res
# Update the resource if necessary

IMEApps.Res: ..\IMEApps.Rc ..\IMEApps.Rcv
    $(rc) $(rcflags) $(rcvars) /fo IMEApps.Res   ..\IMEApps.Rc


# Update the object file if necessary

.c.Obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $<

# Update the executable file if necessary, and if so, add the resource back in.

IMEAppsm.Exe:   ..\Comp.Obj    \
                ..\Data.Obj    \
                ..\IMEApps.Obj \
                ..\IMEMenu.Obj \
                ..\Mode.Obj    \
                ..\Paint.Obj   \
                ..\SetComp.Obj \
                ..\Status.Obj  \
                ..\Subs.Obj    \
                ..\WSubs.Obj   \
                ..\Toolbar.Obj \
                IMEApps.Res
    $(link) $(linkdebug) $(guiflags) -out:IMEAppsm.Exe $(LINKFILES) $(guilibs) $(LIBS)
