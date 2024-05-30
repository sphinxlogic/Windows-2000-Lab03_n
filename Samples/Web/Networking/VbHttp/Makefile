#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  vbhttp.exe

#
# Project VBHTTP.VBP builds VBHTTP.EXE
#
vbhttp.exe :  \
    HTTP.Frm \
    WININET.Bas \
    vbhttp.vbp
    $(bc) vbhttp.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
