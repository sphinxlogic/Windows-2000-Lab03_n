# Nmake macros for building Tst4Wts.Exe
# Define NODEBUG to build Tst4Wts.Exe without debugging information.
# Define UNICODE to build Tst4Wts.Exe with UNICODE characters.

TARGETOS=WINNT

!include <Win32.Mak>

!ifdef UNICODE
unicode = -DUNICODE
!else
unicode =
!endif

all: Tst4Wts.Exe

# Update the resource if necessary

Tst4Wts.Res: Tst4Wts.Rc
    $(rc) $(rcvars) -r Tst4Wts.Rc

# Update the object files if necessary

Tst4Wts.Obj: Tst4Wts.c
    $(cc) $(cdebug) $(cflags) $(cvars) $(unicode) Tst4Wts.c

# Update the executable file if necessary, and if so, add the resource back in.

Tst4Wts.Exe: Tst4Wts.Obj Tst4Wts.Res makefile
    $(link) $(linkdebug)  $(conflags) -out:Tst4Wts.Exe\
    Tst4Wts.Obj Tst4Wts.Res\
    Version.lib $(conlibsmt)
    
clean:
    del *.Obj
    del *.Res
    del *.Exe
