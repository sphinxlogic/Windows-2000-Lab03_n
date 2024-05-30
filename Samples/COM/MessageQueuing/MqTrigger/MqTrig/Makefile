#
# Copyright Microsoft Corp, 1997-1999
# Windows Platform SDK
#
!include <Win32.mak>

#
# all VB projects in the directory
#
ALL : Clean MQTRIG.exe

#
# remove existing files
#
Clean :
     if exist MQTRIG.exe del MQTRIG.exe
     if exist *.exe del *.exe
     if exist *.vbw del *.vbw
     if exist *.obj del *.obj
     if exist *.log del *.log

#
# project MQTRIGGER.VBP builds MQTRIG.EXE
#
MQTRIG.exe :  \
    frmConfig.frm \
    frmMonitor.frm \
    frmPollingConfig.frm \
    Trigger.bas \
    mqtrigger.vbp
    -$(bc) mqtrigger.vbp $(bc_exe) /out comp.log
    @type comp.log
    @del comp.log
