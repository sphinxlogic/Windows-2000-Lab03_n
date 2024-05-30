#*************************************************************#
#**                                                         **#
#**            Microsoft Winsock 2 Examples                 **#
#**                 SOCKDUP Application                     **#
#**         Copyright(c) Microsoft Corp. 1992-1998          **#
#**                                                         **#
#*************************************************************#
APPVER = 4.0
TARGETOS=WINNT

!include <Win32.Mak>

LIBS = kernel32.lib user32.lib ws2_32.lib oldnames.lib libcmt.lib 

ALLEXES = sockspx.exe

all: $(ALLEXES)

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

$(ALLEXES): $*.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj user32.lib $(conlibsmt)


