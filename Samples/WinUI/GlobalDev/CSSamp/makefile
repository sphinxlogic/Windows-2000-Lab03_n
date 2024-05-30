# Makefile for CSSAMP 
#
# Nmake macros for building Win32 & Win64 apps
!include <Win32.Mak>

OBJDIR=.\obj 

#Defaults to current directory, but also works with something like BINDIR=.\bin
BINDIR=.

LINK_OBJS=\
	$(OBJDIR)\cssamp.obj\
	$(OBJDIR)\dspformt.obj\
	$(OBJDIR)\dsplogcl.obj\
	$(OBJDIR)\dspplain.obj\
	$(OBJDIR)\settings.obj\
	$(OBJDIR)\text.obj\
	$(OBJDIR)\style.obj\
	$(OBJDIR)\textwnd.obj\
	$(OBJDIR)\edit.obj\
	$(OBJDIR)\debug.obj\
	$(OBJDIR)\cssamp.res

all: $(BINDIR) $(OBJDIR) $(BINDIR)\cssamp.exe 

# Create directories if necessary
"$(BINDIR)" :
	if not exist "$(BINDIR)" mkdir "$(BINDIR)"

"$(OBJDIR)" :
	if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"

# Compile the resource files if necessary
$(OBJDIR)\cssamp.res: cssamp.rc resource.h "$(OBJDIR)" initial.txt
    $(rc) $(rcflags) $(rcvars) /fo"$(OBJDIR)\cssamp.res" cssamp.rc 


#Generic compiler command line
.cpp{$(OBJDIR)}.obj::
   $(cc) @<<
   $(cflags) /Fo"$(OBJDIR)\\" $(cvars) $(cdebug)  $< 
<<

# Update modules if necessary

#main exe
$(BINDIR)\cssamp.exe: $(LINK_OBJS) 
    $(link) $(linkdebug) $(guiflags) -out:"$(BINDIR)\cssamp.exe" $(guilibs) USP10.LIB $(LINK_OBJS)

CLEAN :
	-@erase "$(OBJDIR)\*.obj"
	-@erase "$(OBJDIR)\*.res"
	-@erase "$(BINDIR)\*.exe"
