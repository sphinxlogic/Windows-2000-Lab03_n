# Platform SDK-style Makefile
# internet\siteserver\personalization\security\CheckNTUser

Proj=CheckNTUser
dll=1
unicode=1
USE_ODBC=1

!include <bkoffice.mak>

LFLAGS=$(LFLAGS) /DEF:".\CheckNTUser.def"

all: "$(ObjDir)\$(Proj).Dll" "$(ObjDir)\regsvr32.trg"

$(ObjDir)\$(Proj).Dll: $(ObjDir)\$(Proj).Obj "CheckNTUser.res" "$(ObjDir)\CheckNTUserImp.obj" "$(ObjDir)\StdAfx.obj"

$(ObjDir)\$(Proj).Obj: $(Proj).Cpp "$(ObjDir)\CheckNTUser.h" "$(ObjDir)\CheckNTUser_i.c" ".\CheckNTUserImp.h"

"$(ObjDir)\CheckNTUser.tlb"	"$(ObjDir)\CheckNTUser.h" "$(ObjDir)\CheckNTUser_i.c": CheckNTUser.idl

"$(ObjDir)\CheckNTUser.Res": CheckNTUser.rc $(ObjDir)\CheckNTUser.tlb ".\CheckNTUserImp.rgs"

"$(ObjDir)\CheckNTUserImp.obj": "$(ObjDir)\CheckNTUser.h" ".\CheckNTUserImp.h"

"$(ObjDir)\StdAfx.Obj": StdAfx.cpp StdAfx.h

"$(ObjDir)\regsvr32.trg": $(ObjDir)\$(Proj).Dll
	@-regsvr32 /s $? $(LogCmd)
    echo regsvr32 exec. time > $(ObjDir)\regsvr32.Trg
