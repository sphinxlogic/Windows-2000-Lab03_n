#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# All VB Projects in the directory
#
ALL :  vbftpjr.exe

#
# Project VBFTPJR.VBP builds VBFTPJR.EXE
#
vbftpjr.exe :  \
    fmVBFTPJR.frm \
    WININET.Bas \
    vbftpjr.vbp
    $(bc) vbftpjr.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
