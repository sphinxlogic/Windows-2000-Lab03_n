#THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
#ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
#TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
#PARTICULAR PURPOSE.
#
#Copyright (C) 1996 - 1999.  Microsoft Corporation.  All rights reserved.
#

!include <win32.mak>

CPP          = $(cc)
CPPFLAGS     = $(cflags) $(cvars) $(cdebug)
LINKFLAGS    = $(ldebug) $(conlflags)

all: Server.Exe Client.Exe

# ----------------------------------------------------------------------------
#                      L I N K / R E S   C O M M A N D S
# ----------------------------------------------------------------------------

Server.Exe: Server.Obj Comm.Obj Security.Obj Collect.Obj
    @echo Linking ...
     $(link) $(LINKFLAGS) $** $(conlibs) wsock32.Lib -out:$@

Client.Exe: Client.Obj Comm.Obj Security.Obj Collect.Obj
    @echo Linking ...
     $(link) $(LINKFLAGS) $** $(conlibs) -out:$@

# ----------------------------------------------------------------------------
#                           B U I L D   R U L E S
# ----------------------------------------------------------------------------

.c.Obj:
    @echo Compiling $<...
    $(CPP) $(CPPFLAGS) /c -I..\include $<

# ----------------------------------------------------------------------------
#                       D E P E N D E N C Y   R U L E S
# ----------------------------------------------------------------------------

Comm.Obj : Comm.c Comm.h

Security.Obj : Security.c Collect.h Security.h

Server.Obj : Server.c Comm.h Security.h

Client.Obj : Client.c Comm.h Security.h

Collect.Obj : Collect.c Collect.h
