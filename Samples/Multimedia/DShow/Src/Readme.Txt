README.TXT - DirectShow SDK Samples
-----------------------------------

For full details about the samples see the DirectX 
media documentation.

BUILDING THE SAMPLES

To build all the DirectShow samples run nmake from this
subdirectory. You can build individual samples
by invoking nmake in the appropriate sample directory.

If you build from the command line be sure your path 
environment variable lists the most recent products 
first. For example, list Microsoft Developer Studio 
before an older edition of the Platform SDK. Also be
aware that the order of directories in the include 
and lib paths can make a difference as include files
and libraries are picked up in the order in which 
they're encountered in these paths.

The sample makefiles default to building debug 
versions of the samples. To build retail versions of 
samples pass nodebug=1 to nmake or set nodebug=1 in 
your build environment.

To clean the build tree, make the clean target. To
rebuild the tree use "nmake clean all".

You can also build the samples using the Microsoft
Developer Studio project files supplied with most of
the samples. These project files are compatible with
Microsoft Developer Studio version 5.0 and higher.
