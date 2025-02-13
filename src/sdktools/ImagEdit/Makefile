
APPVER=4.0
!include <win32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

cvars=-DNT -DWIN -DWIN32
obj=obj
mycflag = -Fo.\$(obj)\\

all: imagedit.exe

# Update the object file if necessary

$(obj)\colorwp.obj: colorwp.c imagedit.h dialogs.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) colorwp.c

$(obj)\icclip.obj: icclip.c imagedit.h dialogs.h iehelp.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) icclip.c

$(obj)\imagedlg.obj: imagedlg.c imagedit.h dialogs.h iehelp.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) imagedlg.c

$(obj)\propbar.obj: propbar.c imagedit.h dialogs.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) propbar.c

$(obj)\toolbox.obj: toolbox.c imagedit.h dialogs.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) toolbox.c

$(obj)\devinfo.obj: devinfo.c
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) devinfo.c

$(obj)\image.obj: image.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) image.c

$(obj)\imaglink.obj: imaglink.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) imaglink.c

$(obj)\rwbmp.obj: rwbmp.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) rwbmp.c

$(obj)\util.obj: util.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) util.c

$(obj)\file.obj: file.c
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) file.c

$(obj)\imagedc.obj: imagedc.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) imagedc.c

$(obj)\imagundo.obj: imagundo.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) imagundo.c

$(obj)\rwicocur.obj: rwicocur.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) rwicocur.c

$(obj)\viewwp.obj: viewwp.c imagedit.h dialogs.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) viewwp.c

$(obj)\globals.obj: globals.c imagedit.h dialogs.h iehelp.h ids.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) globals.c

$(obj)\imagedit.obj: imagedit.c imagedit.h dialogs.h ids.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) imagedit.c

$(obj)\menucmd.obj: menucmd.c imagedit.h dialogs.h ids.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) menucmd.c

$(obj)\rwpal.obj: rwpal.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) rwpal.c

$(obj)\workwp.obj: workwp.c imagedit.h
    IF NOT EXIST $(obj) md obj
    $(cc) $(cdebug) $(cflags) $(mycflag) $(cvars) workwp.c

# Update the resources if necessary

$(obj)\imagedit.res: res.rc imagedit.h
    $(rc) $(rcvars) $(rcflags) -fo .\$(obj)\imagedit.res res.rc

# Update the executable file if necessary, and if so, add the resource back in.

imagedit.exe: $(obj)\imagedit.obj  \
              $(obj)\colorwp.obj   \
              $(obj)\icclip.obj    \
              $(obj)\imagedlg.obj  \
              $(obj)\propbar.obj   \
              $(obj)\toolbox.obj   \
              $(obj)\devinfo.obj   \
              $(obj)\image.obj     \
              $(obj)\imaglink.obj  \
              $(obj)\rwbmp.obj     \
              $(obj)\util.obj      \
              $(obj)\file.obj      \
              $(obj)\imagedc.obj   \
              $(obj)\imagundo.obj \
              $(obj)\rwicocur.obj  \
              $(obj)\viewwp.obj    \
              $(obj)\globals.obj   \
              $(obj)\menucmd.obj   \
              $(obj)\rwpal.obj     \
              $(obj)\workwp.obj    \
	      $(obj)\imagedit.res
    $(link) $(linkdebug) $(guiflags) -out:imagedit.exe	 \
    $(obj)\imagedit.obj  \
    $(obj)\colorwp.obj   \
    $(obj)\icclip.obj    \
    $(obj)\imagedlg.obj  \
    $(obj)\propbar.obj   \
    $(obj)\toolbox.obj   \
    $(obj)\devinfo.obj   \
    $(obj)\image.obj     \
    $(obj)\imaglink.obj  \
    $(obj)\rwbmp.obj     \
    $(obj)\util.obj      \
    $(obj)\file.obj      \
    $(obj)\imagedc.obj   \
    $(obj)\imagundo.obj  \
    $(obj)\rwicocur.obj  \
    $(obj)\viewwp.obj    \
    $(obj)\globals.obj   \
    $(obj)\menucmd.obj   \
    $(obj)\rwpal.obj     \
    $(obj)\workwp.obj    \
    $(obj)\imagedit.res $(guilibs) shell32.lib
!IF ("$(TARGETLANG)" == "LANG_JAPANESE") && ("$(OS)" == "Windows_NT")
    rlman -p 932 -n 17 1 -a $*.exe $*.tok $*.exe
!ENDIF
