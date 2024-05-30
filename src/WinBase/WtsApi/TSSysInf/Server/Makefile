# Nmake macros for building Win32 & Win64 apps
# Copyright 1999 Microsoft Corporation

!Include <Win32.Mak>

all: SysInf_S.Exe

# Update the object file if necessary

SysInf_S.Obj: SysInf_S.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -I..\Inc SysInf_S.c

# Update the resources if necessary

SysInf_S.Res: SysInf_S.Rc
    $(rc) $(rcvars) -r SysInf_S.Rc

# Update the dynamic link library

SysInf_S.Exe: SysInf_S.Obj
    $(link) $(ldebug) $(conlflags) $(conlibsdll) \
    -out:SysInf_S.Exe                            \
    SysInf_S.Obj WTSAPI32.Lib User32.Lib