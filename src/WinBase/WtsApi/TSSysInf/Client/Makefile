# Nmake macros for building Win32 & Win64 apps
# Copyright 1999 Microsoft Corporation

!Include <Win32.Mak>

all: SysInf_C.Dll

# Update the object file if necessary

SysInf_C.Obj: SysInf_C.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -I..\Inc SysInf_C.c

# Update the resources if necessary

SysInf_C.Res: SysInf_C.Rc
    $(rc) $(rcvars) -r SysInf_C.Rc

# Update the import library

SysInf_C.Lib: SysInf_C.Obj SysInf_C.Def
    $(implib) -machine:$(CPU) \
    -def:SysInf_C.Def         \
    SysInf_C.Obj              \
    -out:SysInf_C.Lib

# Update the dynamic link library

SysInf_C.Dll: SysInf_C.Obj SysInf_C.Def SysInf_C.Lib
    $(link) $(linkdebug) $(dlllflags)       \
    -base:0x1C000000                        \
    -out:SysInf_C.Dll                       \
    SysInf_C.Exp SysInf_C.Obj $(guilibsdll)


MSC_WARNING_LEVEL=/WX /W3
