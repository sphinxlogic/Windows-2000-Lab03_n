# Nmake macros for building Win32 apps

TARGETOS=BOTH
APPVER=4.0

!include <Win32.Mak>

PROJ=CabView

all: $(PROJ).exe

PROJ_OBJS = CabView.obj CabViewHelper.obj CabViewCallback.obj CabViewExtract.obj Cabinet.obj
OTHER_LIBS = fdi.lib shell32.lib comctl32.lib
OTHER_CFLAGS = -DWIN32_LEAN_AND_MEAN -DWINVER=0x0400
OTHER_RCOPTS = -DWIN32_LEAN_AND_MEAN

# Update the resource if necessary

$(PROJ).Res: $(PROJ).rc $(PROJ).h Resource.h
    $(rc) $(rcflags) $(rcvars) $(OTHER_RCOPTS) $(PROJ).rc

# Update the object file if necessary

CabView.Obj: CabView.cpp CabView.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(OTHER_CFLAGS) CabView.cpp

CabViewHelper.Obj: CabViewHelper.cpp CabView.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(OTHER_CFLAGS) CabViewHelper.cpp

CabViewCallback.Obj: CabViewCallback.cpp CabView.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(OTHER_CFLAGS) CabViewCallback.cpp

CabViewExtract.Obj: CabViewExtract.cpp CabView.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(OTHER_CFLAGS) CabViewExtract.cpp

Cabinet.Obj: Cabinet.cpp Cabinet.h
    $(cc) $(cflags) $(cvars) $(cdebug) $(OTHER_CFLAGS) Cabinet.cpp

# Update the executable if necessary

$(PROJ).exe: $(PROJ_OBJS) CabView.res
    $(link) $(ldebug) $(guilflags) -out:$(PROJ).exe $(PROJ).res $(guilibs) $(OTHER_LIBS) $(PROJ_OBJS)
