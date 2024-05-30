Proj = SampView
dll = 1

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=shell32.lib comctl32.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

_WIN32_IE = 0x0400

!include <inetsdk.mak>

# itemize all of the required Object files

Objs =   "$(ObjDir)\ClsFact.obj" \
         "$(ObjDir)\ContMenu.obj" \
         "$(ObjDir)\DataObj.obj" \
         "$(ObjDir)\DropSrc.obj" \
         "$(ObjDir)\DropTgt.obj" \
         "$(ObjDir)\EnumIdl.obj" \
         "$(ObjDir)\ExtrIcon.obj" \
         "$(ObjDir)\PidlMgr.obj" \
         "$(ObjDir)\SampView.obj" \
         "$(ObjDir)\SampView.res" \
         "$(ObjDir)\ShlFldr.obj" \
         "$(ObjDir)\ShlView.obj" \
         "$(ObjDir)\Utility.obj" \
         "$(ObjDir)\ViewList.obj"

# itemize all of the required include files

Includes =  ClsFact.h \
            ContMenu.h \
            DataObj.h \
            DropSrc.h \
            DropTgt.h \
            EnumIDL.h \
            ExtrIcon.h \
            PidlMgr.h \
            ShlFldr.h \
            ShlView.h \
            ContMenu.h \
            Utility.h \
            guid.h \
            tools.h \
            resource.h

# add the .def file to the link flags
linkflags = $(linkflags) -def:SampView.def

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes)  SampView.Ico

$(ObjDir)\ClsFact.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ContMenu.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\DataObj.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\DropSrc.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\DropTgt.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\EnumIDL.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ExtrIcon.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\PidlMgr.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\SampView.Obj  : $(@B).Cpp $(Includes)
$(ObjDir)\ShlFldr.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ShlView.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\Utility.Obj   : $(@B).Cpp $(Includes)
$(ObjDir)\ViewList.Obj  : $(@B).Cpp $(Includes)

$(ObjDir)\$(Proj).dll   : $(Objs)

All: $(ObjDir)\$(Proj).dll
   regsvr32.exe /s /c $(ObjDir)\$(Proj).dll >> $(ObjDir)\Register.Out


