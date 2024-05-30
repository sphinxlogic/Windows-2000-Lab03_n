# Platform SDK-style Makefile
# internet\siteserver\personalization\security\icpproject\icpclnt

Proj=icpclnt
console=1
USE_ODBC=1

!include <bkoffice.mak>

libs=$(libs) wsock32.lib
CL=$(CL) /D "SECURITY_WIN32" /D "NT_CLIENT" /D_CRTAPI1=_cdecl
LFLAGS=$(LFLAGS) /out:"$(ObjDir)\icpclnt.exe"

# This is a fake rule so that this works correctly with the inference rules.
# The /out: above will ensure the correct .exe is generated.
all: $(ObjDir)\Client.Exe 

$(ObjDir)\Client.Exe: "$(ObjDir)\client.obj" "$(ObjDir)\foricp.obj"

$(ObjDir)\Client.Obj: ".\Client.C" "..\include\commdef.h" ".\client.h" ".\sampincl.h" {$(INCLUDE)}"sspi.h"

"$(ObjDir)\foricp.obj": ".\foricp.C" "..\INCLUDE\commdef.h" ".\client.h"	".\sampincl.h" {$(INCLUDE)}"sspi.h"
