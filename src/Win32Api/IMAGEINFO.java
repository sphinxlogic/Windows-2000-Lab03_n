// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1) */
public class IMAGEINFO {
	public int	hbmImage;
	public int	hbmMask;
	public int	Unused1;
	public int	Unused2;
	// rcImage was a by-value RECT structure
	public int	rcImage_left;
	public int	rcImage_top;
	public int	rcImage_right;
	public int	rcImage_bottom;
}

