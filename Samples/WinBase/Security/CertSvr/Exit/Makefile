# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT

!include <win32.mak>


PROJNAME = Exit
OBJFILES = atl.Obj CertXSam.Obj Exit.Obj pch.Obj CertXSam_i.Obj CertXSam.Res
EXTRA_LIBS = Certidl.lib

all: $(PROJNAME).Dll

CertXSam.Res: CertXSam.Rc CertXSam.Tlb
    $(rc) $(rcvars) -r -fo $*.Res $*.Rc

CertXSam.Rc: CertXSam.Tlb

CertXSam.Tlb: CertXSam.Idl
    midl CertExit.Idl

CertXSam.Obj: CertXSam.Cpp Exit.h CertXSam.h

Exit.Obj: Exit.Cpp Exit.h CertXSam.h

CertXSam.h: CertXSam.Idl
    midl /h CertXSam.h CertXSam.Idl

CertExit_i.c: CertExit.Idl

.C.Obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -I. -DUNICODE $*.C

.Cpp.Obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -I. -DUNICODE $*.Cpp


$(PROJNAME).Dll: $(OBJFILES)
    $(link) -def:CertXSam.Def $(linkdebug) $(dlllflags) -out:$*.Dll $** $(olelibsdll) $(EXTRA_LIBS)


clean:
    del *.Obj *.Res
