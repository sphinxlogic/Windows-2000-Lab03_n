DIRLIST  =  idl     \
            engines \
            app

SDKPROJ =COM\Fundamentals\mfract

all: $(DIRLIST)

$(DIRLIST):
        @echo *******************************
        @echo *** BUILDING COM\MFRACT samples
        @echo *******************************
        cd $@
        @nmake -a -i -nologo
        cd ..
