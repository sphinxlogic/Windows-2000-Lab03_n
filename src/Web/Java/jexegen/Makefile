# ----------------------------------------------------------------------------
#
# ----------------------------------------------------------------------------

all :
         cd Hello
         $(CMDLINE)
         cd ..\Mapplet
         $(CMDLINE)
         cd ..\stub
         $(MAKE) /a /f "stub.mak" CFG="JView - Win32 Debug"
         $(MAKE) /a /f "stub.mak" CFG="JView - Win32 Release"
         cd ..

