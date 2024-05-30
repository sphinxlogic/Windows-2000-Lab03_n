Use_MFC = 1
Proj = UrlPad

# WARNING: Datapath.h is a dead file.  We have stubbed datapath.h and added it to
# this directory to get around a VC 4.2 MFC problem with include files that 
# reference the obsolete datapath.h file.  Your code should include urlmon.h
# and oaidl.h rather than datapath.h

INCLUDE=..\Urlpad;$(INCLUDE)

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=uuid.lib UrlMon.Lib WinInet.Lib WebPost.Lib

cDefines = -GX -I..\BaseCtl\Include

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <INetSDK.Mak>

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\SuperPad.Exe : $(@R).Obj          $(@D)\UrlPad.Res   $(@D)\PadDoc.Obj  \
      $(@D)\PadView.Obj  $(@D)\MainFrm.Obj  $(@D)\IPFrame.Obj  $(@D)\PageSet.Obj \
      $(@D)\TabStop.Obj  $(@D)\PadFrame.Obj $(@D)\AboutBox.Obj $(@D)\PadItem.Obj \
      $(@D)\LinkItem.Obj $(@D)\DownLoad.Obj $(@D)\FileOpen.Obj

$(ObjDir)\$(Proj).Exe: $(@D)\SuperPad.Exe
 Copy $? $@
