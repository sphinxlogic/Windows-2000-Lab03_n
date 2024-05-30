// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class POLYTEXT {
	public int	x;
	public int	y;
	public int	n;
	public int /* LPCWSTR */	lpstr;
	public int	uiFlags;
	// rcl was a by-value RECT structure
	public int	rcl_left;
	public int	rcl_top;
	public int	rcl_right;
	public int	rcl_bottom;
	public int	pdx;
}

