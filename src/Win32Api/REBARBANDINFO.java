// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class REBARBANDINFO {
	public int	cbSize = 56; //com.ms.dll.DllLib.sizeOf(this);
	public int	fMask;
	public int	fStyle;
	public int	clrFore;
	public int	clrBack;
	public int /* LPWSTR */	lpText;
	public int	cch;
	public int	iImage;
	public int	hwndChild;
	public int	cxMinChild;
	public int	cyMinChild;
	public int	cx;
	public int	hbmBack;
	public int	wID;
}

