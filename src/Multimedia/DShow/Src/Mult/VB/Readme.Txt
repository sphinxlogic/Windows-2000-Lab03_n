Cutlist Sample Application
--------------------------

The cutlist sample application is written in visual basic.  It is
designed to play unencrpyted MPEG-2 clips listed in a file:

cuts.lst

The file contains a list of quadruples:

"foo.bar", 1234567, 100000000, "title of foo.bar", 0

designating (in order)
 - the file the clip comes from 
 - the start byte position of the clip 
 - the end byte position of the clip in that file 
 - the title for the movie
 - a fine adjustment for the start time of the movie in 100ns units

See the sample cuts.lst in this directory for an example.

In order to use the application you need to generate your own cuts.lst
using some content of your own (an unencrpyted DVD disk can be used
if you use the .VOB files).

You need DirectShow compatible MPEG-2 audio and video decoders
installed to use this sample. You also need to compile the "Auto"
directory of the Mult sample and register the DLL which is built.
