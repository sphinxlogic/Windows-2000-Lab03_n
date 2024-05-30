Proj = IcnOvrly
dll = 1

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=shell32.lib shlwapi.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

_WIN32_IE = 0x0500

!include <inetsdk.mak>

# itemize all of the required Object files

Objs =   "$(ObjDir)\IcnOvrly.obj" \
         "$(ObjDir)\IcnOvrly.res"

# itemize all of the required include files

Includes =  IcnOvrly.h \
            resource.h

# add the .def file to the link flags
linkflags = $(linkflags) -def:IcnOvrly.def

$(ObjDir)\$(Proj).res   : $(@B).rc $(Includes)  IcnOvrly.Ico

$(ObjDir)\IcnOvrly.Obj  : $(@B).Cpp $(Includes)

$(ObjDir)\$(Proj).dll   : $(Objs)

All: $(ObjDir)\$(Proj).dll

#   regsvr32.exe /s /c $(ObjDir)\$(Proj).dll >> $(ObjDir)\Register.Out


