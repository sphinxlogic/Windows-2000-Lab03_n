NAMED


SUMMARY
-------

NAMED is a sample application for demonstration of named profiles


To Compile NAMED
----------------

To compile the sample, use the following command:

   nmake


To clean up between builds which use different options, use the
following command:

   nmake clean


To build the project under Visual C++ 6.0, use the project file NAMED.DSP


To Run NAMED
------------

 - Run obj\NAMED.EXE <named profile filename> [color name to file]

 - If a color name is not specified, named lists all the color names in the profile

 - If a color name is not specified, named gives the index of the color. 
   Note that the color names are case sensitive.


NAMED Files
------------

makefile      Makefile for the project
named.c       Main file for the named color profiles sample
named.dsp     VC 6.0 project settings file
named.h       Header file for named.c
named.rc      Project resources
pch.c         Precompiled headers file
resource.h    Header file for the definitions of the resouce identifiers
