# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT

!include <win32.mak>


# define project specific macros, PROJNAME is simply a name for our executable,
#  OBJFILES are the object files resulting from our source code files, and
#  EXTRA_LIBS are the libraries provided with the compiler or SDK.

PROJNAME = CATQ
OBJFILES = main.obj service.obj ciquery.obj statbar.obj progress.obj
EXTRA_LIBS = oledb.lib ntquery.lib shell32.lib comctl32.lib pdh.lib

#define the file to be built by default
all: $(PROJNAME).exe


# Update the resource if necessary
res.res: res.rc $(PROJNAME).h
    $(rc) $(rcvars) -r -fo $*.res $*.rc


# Inference rule for updating the object files
#  This is all standard, except that we are explicitly defining UNICODE
.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) -DUNICODE $*.c

.cxx.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) -DUNICODE $*.cxx


# Update the executable file if necessary, and if so, add the resource back in.
$(PROJNAME).exe: $(OBJFILES) res.res
    $(link) $(linkdebug) $(guiflags) -out:$*.exe $** $(olelibs) $(EXTRA_LIBS)


# Clean up everything except .exe file
clean:
    del *.obj *.res
