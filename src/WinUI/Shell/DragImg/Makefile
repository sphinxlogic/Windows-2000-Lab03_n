Proj = DragImg

# These are "extra" libs

libs = shell32.lib comctl32.lib urlmon.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

_WIN32_IE = 0x0500

!include <inetsdk.mak>

All: $(ObjDir)\$(Proj).exe

# itemize all of the required source files

Sources =   DataObj.cpp  \
            DragSrc.cpp  \
            DropTgt.cpp  \
            EnumFE.cpp  \
            Render.cpp  \
            DragImg.cpp

# itemize all of the required Object files

Objs =   $(ObjDir)\DataObj.obj  \
         $(ObjDir)\DragSrc.obj  \
         $(ObjDir)\DropTgt.obj  \
         $(ObjDir)\EnumFE.obj  \
         $(ObjDir)\Render.obj  \
         $(ObjDir)\DragImg.obj  \
         $(ObjDir)\DragImg.res

# itemize all of the required include files

Includes =  DataObj.h  \
            DragSrc.h  \
            DropTgt.h  \
            EnumFE.h  \
            DragImg.h  \
            Render.h  \
            resource.h

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes) mainicon.ico DragImg.bmp
#  rc -r DragImg.rc

$(ObjDir)\DataObj.obj   : $(@B).cpp $(Includes)
$(ObjDir)\DragSrc.obj   : $(@B).cpp $(Includes)
$(ObjDir)\DropTgt.obj   : $(@B).cpp $(Includes)
$(ObjDir)\EnumFE.obj    : $(@B).cpp $(Includes)
$(ObjDir)\Render.obj    : $(@B).cpp $(Includes)
$(ObjDir)\DragImg.obj   : $(@B).cpp $(Includes)
#  $(cc) $(cflags) $(cvars) $(cdebug) $(Sources)

$(ObjDir)\$(Proj).exe   : $(Objs)
#    $(link) $(linkdebug) $(guiflags) -out:menu.exe menu.obj menu.rbj $(guilibs)


