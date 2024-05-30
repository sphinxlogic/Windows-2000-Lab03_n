Proj= ctetest

dll=1

LFLAGS=-def:$(Proj).def

!include <BkOffice.mak>

ObjList =  $(ObjDir)\$(Proj).obj   \
           $(ObjDir)\cte_enc.obj    

all: $(ObjDir)\$(Proj).dll 

$(ObjDir)\$(Proj).dll: $(ObjList) 

