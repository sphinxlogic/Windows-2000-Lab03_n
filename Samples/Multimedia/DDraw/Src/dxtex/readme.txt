//-------------------------------------------------------------------------
//
// Sample Name: DXTex
//
// Copyright (c) 1998-1999 Microsoft Corporation. All rights reserved.
//
//-------------------------------------------------------------------------


Description
===========
The purpose of this tool is to allow DXSDK users to easily create texture
maps that use the new DXTn compression formats.  Creating a DXTn-compressed
texture is actually not that difficult to do: DirectDraw's Blt function can
do the conversion for you.  Advanced developers will probably want to write
their own tools that meet their specific needs.  But this tool provides useful
basic functionality.


DxTex Functionality
===================
Opens BMP and DDS files (See below for a description of the DDS file format)
Opens BMP files as alpha channel, either explicitly or implicitly (via 
foo_a.bmp naming)
Saves textures in DDS format
Supports conversion to all five DXTn compression formats
Supports generation of mip maps (using a box filter)
Supports visualization of alpha channel as a greyscale image or via a user-
selectable background color
Supports easy visual comparison of image quality between formats


User Interface
==============
DxTex uses a pretty traditional user interface.  Each texture map is a 
document, and several documents can be open at a time.  The one thing that
is a bit unusual about the UI is that each document can hold the texture
in either one or two formats at once while the document is open in DxTex.
For instance, one could import a BMP file, which would automatically create
a 32-bit ARGB texture.  One could then choose to convert the texture to 
DXT1 format.  The document now remembers the image in *both* formats, and
the user can flip between the formats by clicking in the window or by 
choosing "Original" and "New" in the View menu.  This makes it easy for
the user to observe any artifacts introduced by image compression, and to
try several different compression formats without progressive degradation
of the image  For instance, if this technique were not used and the user
converted an image from ARGB to DXT1, all but one bit of alpha would be lost.
If the user then decided to convert to DXT2, there would still be only two
alpha levels.  With DxTex's system, the second conversion is done from the
original ARGB format, and the DXT2 image will contain all 16 levels of alpha
supported by DXT2.  When the image is saved, the "original" format is 
discarded, and only the "new" format is stored.

There are a few consequences of this system that one must remember:
- If no format conversion has been requested since the document was opened,
  the one format is the "original" format and that is the format in which
  the image will be written when the document is saved.
- If format conversion has been requested since the document was opened, the
  converted format is the "new" format and that is the format in which the
  image will be written when the document is saved.
- If a second format conversion is requested, the "new" format from the first
  conversion is replaced with the second format.  The "original" format will
  be unchanged.
- Generating of mip maps applies to both formats simultaneously.
- If the original format has multiple mip maps, and conversion to a new format
  is requested, the new format will automatically have multiple mip maps as 
  well.
It's not as complicated as it sounds: with time, this two-format system 
becomes natural and efficient to use.


DxTex Performance
=================
DxTex uses the Direct3D Reference Rasterizer to draw the textures, 
regardless of what 3D hardware is available.  So with larger textures 
(greater than 256x256), the program may be somewhat slow, depending on your 
CPU speed.


DDS File Format
===============
DxTex's native file format is called "DDS" file format, because it 
encapsulates the information in a DirectDrawSurface.  It has the following 
format:

    DWORD dwMagic (0x20534444, or "DDS ")
    DDSURFACEDESC2 ddsd (this provides information about the surface format)
    BYTE bData1[] (this is the surface data for the main surface)
    [BYTE bData2[]...] (surface data for attached surfaces, if any, follow)

This format is easy to read and write, and supports features such as alpha
and multiple mip levels, as well as DXTn compression.  The "Compress" sample 
application on the DXSDK demonstrates how to properly import a DDS file.

The user should note that it is not necessary to use the DDS format in order
to use DXTn-compressed textures, or vice-versa.  But the two work well 
together.


Mip Maps
========
Mip mapping is a technique that improves image quality and reduces texture
memory bandwidth by providing prefiltered versions of the texture image at
multiple resolutions.

To generate mip maps in DxTex, the width and height of the source image must 
both be powers of 2.  Choose "Generate Mip Maps" from the Format menu.  
Filtering is done via a simple box filter, i.e., the four nearest pixels are
averaged to produce each destination pixel.  More sophisticated filtering can
be found in other image processing programs.


Alpha
=====
Many texture formats include an alpha channel, which provides opacity 
information at each pixel.  DxTex fully supports alpha in textures.  When
importing a BMP file, if a file exists of the same size with "_a" at the end
(e.g., foo.bmp and foo_a.bmp), the second file will be loaded as an alpha
channel.  The blue channel of the second BMP is stored in the alpha channel.
Once a document is open, the user can explicitly load a BMP file as the alpha 
channel via the "Open As Alpha Channel" command on the File menu.

To view the alpha channel directly without the RGB channels, choose "Alpha
Channel Only" from the View menu.  The alpha channel will appear as a 
greyscale image.  Note that if no alpha channel has been loaded, the alpha
channel will be 100% everywhere and the image will appear solid white when
viewing "Alpha Channel Only".  To turn off "Alpha Channel Only", just choose
that menu item a second time.

In the usual view, the effect of the alpha channel is visible because the 
window has a solid background color which shows through the texture where the
alpha channel is less than 100%.  The user can change this background color
by choosing "Change Background Color" from the View menu.  This choice does
not affect the texture itself or the data that is written when the file is
saved.

The DXT2 and DXT4 formats use premultiplied alpha, which means that the
red, green, and blue values stored in the surface are already multiplied
by the corresponding alpha value.  DirectDraw cannot blit from a surface
containing premultiplied alpha to one containing non-premultiplied alpha,
so some DxTex operations (Open as Alpha Channel, conversion to DXT3, and
conversion to DXT5) are not possible on DXT2 and DXT4 formats.  Supporting
textures using these formats is difficult on Direct3D devices which do
not support DXTn textures, because DirectDraw cannot handle blitting them
to a traditional ARGB surface either (unless that ARGB surface uses 
premultiplied alpha as well, which is rare).  So you may find it easier to
use DXT3 rather than DXT2 and DXT5 rather than DXT4 when possible.


Command-Line Options
====================
Command-line options can be used to pass input files, an output file name, and
processing options to DxTex.  If an output file name is specified, the program
exits automatically after writing the output file, and no user interface is 
presented.

dxtex [infilename] [-a alphaname] [-m] [DXT1|DXT2|DXT3|DXT4|DXT5] [outfilename]

infilename:               The name of the file to load.  This can be a BMP or 
                          DDS file.

-a alphaname:             If "-a" is specified, the next parameter is the name
                          of a BMP file to load as the alpha channel.  Note:
                          if no alpha filename is specified, DxTex will still
                          look for a file named infilename_a.bmp and, if it 
                          exists, use that as the alpha channel.

-m:                       If this option is specified, mipmaps are generated.

DXT1|DXT2|DXT3|DXT4|DXT5: Specifies compression format.  If no format is 
                          specified, the image will be in ARGB-8888.

outfilename:              Specifies the name of the destination file.  If this
                          is not specified, the user interface will show the 
                          current file and all requested operations.  If an 
                          outfilename is specified, the app will exit after 
                          saving the processed file without presenting a user 
                          interface.
