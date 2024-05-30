// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class CHOOSEFONT {
	public int	lStructSize = com.ms.dll.DllLib.sizeOf(this);
	public int	hwndOwner;
	public int	hDC;
        public int      lpLogFont;
	public int	iPointSize;
	public int	Flags;
	public int	rgbColors;
	public int	lCustData;
	public int /* Callback */	lpfnHook;
	public String	lpTemplateName;
	public int	hInstance;
	public String	lpszStyle;
	public short	nFontType;
	public short	___MISSING_ALIGNMENT__;
	public int	nSizeMin;
	public int	nSizeMax;
}

