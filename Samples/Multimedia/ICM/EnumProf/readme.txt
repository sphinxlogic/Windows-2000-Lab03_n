ENUMPROF


SUMMARY
-------

ENUMPROF is a sample application for enumerating color profiles in the system


To Compile ENUMPROF
-------------------

To compile the sample, use the following command:

   nmake


To clean up between builds which use different options, use the
following command:

   nmake clean


To build the project under Visual C++ 6.0, use the project file ENUMPROF.DSP


To Run ENUMPROF
---------------

 - Run obj\ENUMPROF.EXE to list color profiles in the system


NAMED Files
------------

EnumProf.c       Main file for the ICM profiles enumeration sample
EnumProf.dsp     VC 6.0 project settings file
EnumProf.h       Header file for EnumProf.c
EnumProf.rc      Project resources
makefile         Makefile for the project
pch.c            Precompiled headers file
resource.h       Header file for the definitions of the resouce identifiers
