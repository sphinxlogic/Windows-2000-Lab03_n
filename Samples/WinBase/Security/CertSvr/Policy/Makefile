# Nmake macros for building Win32 & Win64 apps

TARGETOS=WINNT

!include <Win32.Mak>

PROJNAME = Policy
OBJFILES = Atl.Obj CeLib.Obj CertPSam.Obj Pch.Obj CertPSam_i.Obj Policy.obj
EXTRA_LIBS = CertIdl.Lib Crypt32.Lib

all: $(PROJNAME).Dll

CertPSam.h CertPSam.Tlb: CertPSam.Idl
   midl /h CertPSam.h /tlb CertPSam.Tlb CertPSam.Idl

CertPSam.Res: CertPSam.rc CertPSam.Tlb Resource.h
    $(rc) $(rcvars) -r -fo $*.Res $*.rc

CertPSam.Obj: CertPSam.Cpp CertPSam.h Resource.h Policy.h

CeLib.Obj: CeLib.Cpp CeLib.h

Policy.Obj: Policy.Cpp Policy.h CeLib.h CertPSam.h Resource.h

.Cpp.Obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -I. -DUNICODE $*.Cpp


$(PROJNAME).Dll: $(OBJFILES) CertPSam.Res
    $(link) -def:CertPSam.Def $(linkdebug) $(dlllflags) -out:$*.Dll $** $(olelibsdll) $(EXTRA_LIBS)


clean:
    del *.Obj *.Res
