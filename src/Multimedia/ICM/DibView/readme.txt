DIBVIEW


SUMMARY
-------

DIBVIEW is a sample application for demonstration of ICM functions.


To Compile DIBVIEW
------------------

To compile the sample without any ICM functionality, use the following 
command:

   nmake -f dibview.mak ICM=ICM_NONE


To compile the sample that uses inside DC ICM functionality, use the 
following command:

   nmake -f dibview.mak ICM=ICM_INSIDE_DC


To compile the sample that uses outside DC ICM functionality, use the 
following command:

   nmake -f dibview.mak ICM=ICM_OUTSIDE_DC


To compile all three versions of DIBVIEW, use the following command:

   nmake


To clean up between builds which use different options, use the
following command:

   nmake clean


To build the project under Visual C++ 6.0, use the project file DIBVIEW.DSP


To Run DIBVIEW
-------------

 - Run obj\no_icm\DIBVIEW.EXE for the non-icm version

 - Run obj\in_dc_icm\DIBVIEW.EXE for the version that uses inside DC ICM functions

 - Run obj\out_dc__icm\DIBVIEW.EXE for the version that uses outside DC ICM functions


DIBVIEW Files
------------

about.c        Implementation of the about dialog
bitmapwin.h    Header file for the BITMAPWINDOW struct
clipboard.c    Implementation of the clipboard operations
cmmman.c       Implements a dialog for manipulating the default CMM
cmmman.h       Header file for CMMman.c
construct.c    Implementation of the BITMAPWINDOW struct contruction / destruction
convert.c      Implementation of the profile to profile conversion operations
convert.h      Header file for convert.c
dib.c          Implementation of the bitmap manipulation functions
dibview.c      main function
dibview.dsp    VC 6.0 project settings file
dibview.h      Header file for dibview.c
dibview.mak    Makefile
dibview.rc     Project resources
document.c     Implementation of the image file handling operations
ffilter.c      Image file read filter functions
ffilter.h      Header file for ffilter.c
global.c       Definition of the global variables
global.h       Declerations the global variables
icm.c          Implementation of the ICM functions
icon.c         Implementation of the window icon drawing
imagelist.bmp  Bitmap for the check mark
implement.c    This file forces the implemantation of the stub functions
inline.h       Header file that contains the inline functions
makefile       Makefile for the project
mmon.c         Implementation of the multi monitor support functions
pch.c          Precompiled headers file
print.c        Implementation of the printing functions
resource.h     Header file for the definitions of the resouce identifiers
selsource.c    Implements a dialog for selecting a TWAIN data source and ICM profile
selsource.h    Header file for selsource.c
settings.c     Implementation of the user defined settings operations
twain.c        Implementation of the TWAIN functions
window.c       Implementation of the window message handling functions
