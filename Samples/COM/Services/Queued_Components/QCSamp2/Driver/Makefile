#makefile for Samples\COM\Services\Queued_Components\QCSamp2\Driver

Proj=Driver

!include <BkOffice.Mak>

all: $(Proj).exe

$(Proj).exe: $(ObjDir)\$(Proj).obj   \
             $(ObjDir)\$(Proj).Res   \
             $(ObjDir)\StdAfx.obj  

$(ObjDir)\$(Proj).obj: $(ObjDir)\QCOrder.h

$(ObjDir)\QCOrder.h: ..\QCOrder\QCOrder.idl
    $(MkDest)
    midl /out $(@D) $? $(LogCmd)