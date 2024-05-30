# Platform SDK-style Makefile
# internet\siteserver\personalization\security\certsource

Proj=CertSource
dll=1
unicode=1
USE_ODBC=1

!include <bkoffice.mak>

LFLAGS=$(LFLAGS) /DEF:".\CertSource.def"
libs=$(libs) wldap32.LIB

all: $(ObjDir)\$(Proj).Dll $(ObjDir)\regsvr32.trg

$(ObjDir)\$(Proj).Dll: $(ObjDir)\$(Proj).Obj "$(ObjDir)\CertSource.res" "$(ObjDir)\CertSrc.obj" "$(ObjDir)\certStdAfx.obj"

$(ObjDir)\CertSource.Res: CertSource.rc $(ObjDir)\CertSource.tlb .\CertSrc.rgs

$(ObjDir)\CertSource.H: CertSource.Idl

$(ObjDir)\$(Proj).Obj: $(Proj).cpp {$(INCLUDE)}winldap.h "$(ObjDir)\CertSource.h" "CertSrc.h"	"certstdafx.h"

$(ObjDir)\CertStdAfx.Obj: CertStdAfx.cpp CertStdAfx.h

$(ObjDir)\regsvr32.trg: $(ObjDir)\$(Proj).Dll
	@-regsvr32 /s $? $(LogCmd)
    echo regsvr32 exec. time > $(ObjDir)\regsvr32.Trg
