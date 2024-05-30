// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1) */
public class APPBARDATA {
	public int	cbSize = 36; //com.ms.dll.DllLib.sizeOf(this);
	public int	hWnd;
	public int	uCallbackMessage;
	public int	uEdge;
	// rc was a by-value RECT structure
	public int	rc_left;
	public int	rc_top;
	public int	rc_right;
	public int	rc_bottom;
	public int	lParam;
}

