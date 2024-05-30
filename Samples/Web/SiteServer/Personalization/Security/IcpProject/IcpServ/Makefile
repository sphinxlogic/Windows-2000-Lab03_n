# Platform SDK-style Makefile
# internet\siteserver\personalization\security\icpproject\icpserv

Proj=icpserv
console=1
USE_ODBC=1

!include <bkoffice.mak>

libs=$(libs) wsock32.lib
CL=$(CL) /D "SECURITY_WIN32" /D "NT_CLIENT" /D_CRTAPI1=_cdecl 
LFLAGS=$(LFLAGS) /out:"$(ObjDir)\$(Proj).exe"

# This is a pseudo rule so that this works correctly with the inference rules.
# The /out: above will ensure the correct .exe is generated.
all: $(ObjDir)\icp_serv.Exe 

$(ObjDir)\icp_serv.Exe: "$(ObjDir)\icp_serv.obj" "$(ObjDir)\proc_msg.obj" "$(ObjDir)\s_foricp.obj" "$(ObjDir)\ssthread.obj"

"$(ObjDir)\icp_serv.obj": ".\icp_serv.c" "..\include\commdef.h" ".\all_incl.h" ".\icp_serv.h" {$(INCLUDE)}"sspi.h"

"$(ObjDir)\proc_msg.obj": ".\proc_msg.c" "..\include\commdef.h" ".\all_incl.h" ".\icp_serv.h" {$(INCLUDE)}"sspi.h"

"$(ObjDir)\ssthread.obj": ".\ssthread.c" "..\include\commdef.h" ".\all_incl.h" ".\icp_serv.h" {$(INCLUDE)}"sspi.h"

"$(ObjDir)\s_foricp.obj": ".\s_foricp.c" "..\include\commdef.h" ".\all_incl.h" ".\icp_serv.h" {$(INCLUDE)}"sspi.h"

 