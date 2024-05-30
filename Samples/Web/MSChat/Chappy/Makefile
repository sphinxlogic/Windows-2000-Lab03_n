!ifdef clean
makeopts = clean=1
!endif # clean

!ifdef nodebug
makeopts = $(makeopts) nodebug=1
!endif

# If sample is installed, cd into that directory and recursively start nmake.

all:
!IF EXIST (chat2000)
 cd chat2000
 @$(MAKE) -nologo /$(MAKEFLAGS) $(makeopts)
 cd ..
!ENDIF # exist (chat2000)


Clean:
    @nmake -nologo /$(MAKEFLAGS) $(makeopts) clean=1
