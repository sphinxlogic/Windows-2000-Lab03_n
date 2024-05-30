# Nmake macros for building Win32 & Win64 apps

TARGETOS=WINNT

!include <win32.mak>


PROJNAME = EncODE
OBJFILES = adate.Obj along.Obj altname.Obj astring.Obj atl.Obj \
       bitstr.Obj ce.Obj CertEnc.Obj crldist.Obj error.obj pch.Obj
EXTRA_LIBS = Certidl.Lib Crypt32.Lib


all: $(PROJNAME).Dll


CertEnc.Res: CertEnc.Rc CertEnc.Tlb
    $(rc) $(rcvars) -r -fo $*.Res $*.Rc


CertEnc.Tlb: CertEnc.Idl
    midl CertEnc.Idl


.Cpp.Obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -I. -DUNICODE $*.Cpp


$(PROJNAME).Dll: $(OBJFILES) CertEnc.Res
    $(link) $(linkdebug) $(dlllflags)  -def:CertEnc.def -out:$*.Dll $** $(olelibsdll) $(EXTRA_LIBS)


clean:
    del *.Obj *.Res
