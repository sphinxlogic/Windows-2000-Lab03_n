!CMDSWITCHES +S

DIRS = BvrHookCntrl Donut DragGeoCntrl DragImgCntrl Movie Pick3Cntrl Union globed3drmcntrl

MAKE = nmake

default: fresh

all: fresh

fresh:
  for %i in ($(DIRS)) do nmake recursive DIR=%%i HOW=

clean:
  for %i in ($(DIRS)) do nmake recursive DIR=%%i HOW=

recursive:
  cd $(DIR)
  $(MAKE) $(HOW)
  if exist *.res del *.res
  if exist *.tlh del *.tlh
  if exist *.tli del *.tli
  if exist *.ilk del *.ilk
  if exist *.obj del *.obj
  if exist *.pch del *.pch
  if exist *.pdb del *.pdb
  if exist *.idb del *.idb
  if exist *.log del *.log
  if exist *.bsc del *.bsc
  if exist *.sbr del *.sbr
  cd ..
