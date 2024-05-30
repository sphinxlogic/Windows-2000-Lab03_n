// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class PAINTSTRUCT {
	public int	hdc;
	public boolean	fErase;
	// rcPaint was a by-value RECT structure
	public int	rcPaint_left;
	public int	rcPaint_top;
	public int	rcPaint_right;
	public int	rcPaint_bottom;
	public boolean	fRestore;
	public boolean	fIncUpdate;
	/** @dll.structmap([type=FIXEDARRAY, size=32]) */
	public byte	rgbReserved[];
}

