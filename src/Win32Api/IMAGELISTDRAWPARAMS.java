// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1) */
public class IMAGELISTDRAWPARAMS {
	public int	cbSize = 56; //com.ms.dll.DllLib.sizeOf(this);
	public int	himl;
	public int	i;
	public int	hdcDst;
	public int	x;
	public int	y;
	public int	cx;
	public int	cy;
	public int	xBitmap;
	public int	yBitmap;
	public int	rgbBk;
	public int	rgbFg;
	public int	fStyle;
	public int	dwRop;
}

