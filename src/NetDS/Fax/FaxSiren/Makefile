Proj= faxsiren

dll=1
unicode=1

LFLAGS=-def:$(Proj).def

!include <BkOffice.mak>

ObjList =  $(ObjDir)\$(Proj).obj   \
           $(ObjDir)\faxsiren.res    

all: $(ObjDir)\$(Proj).dll 

$(ObjDir)\$(Proj).dll: $(ObjList) 

