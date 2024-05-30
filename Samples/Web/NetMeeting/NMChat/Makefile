Proj=  NMChat

libs= $(libs) oleaut32.lib comctl32.lib shell32.lib

!include <BkOffice.mak>
 
ObjList =  $(ObjDir)\$(Proj).obj   \
           $(ObjDir)\CConf.obj     \
	   $(ObjDir)\cData.obj     \
	   $(ObjDir)\clUtil.obj	   \
	   $(ObjDir)\Cmd.obj       \
	   $(ObjDir)\cMemb.obj     \
	   $(ObjDir)\Debug.obj     \
	   $(ObjDir)\imsconf2.obj  \
	   $(ObjDir)\Msg.obj       \
	   $(ObjDir)\Util.obj      \
	   $(ObjDir)\Res.res
	

all: $(ObjDir)\$(Proj).exe 

$(ObjDir)\$(Proj).exe: $(ObjList)

$(ObjDir)\imsconf2.obj: $(ObjDir)\$(@B).c
    $(CC) $(CL) $(crtflags) $(cDefines) $(ObjDir)\$(@B).c $(LogCmd)

$(ObjDir)\imsconf2.h: $(@B).Idl
    $(MkDest)
    midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf /dlldata \
          $(ObjDir)\dlldata.rpc /proxy $(ObjDir)\$(@B).rpc /header \
          $(ObjDir)\$(@B).h /iid $(ObjDir)\$(@B).c $(@B).Idl

$(ObjDir)\$(Proj).obj: $(ObjDir)\Main.obj 
   copy $(ObjDir)\Main.obj  $(ObjDir)\$(Proj).obj

$(ObjDir)\Main.obj:  $(ObjDir)\imsconf2.h 

 