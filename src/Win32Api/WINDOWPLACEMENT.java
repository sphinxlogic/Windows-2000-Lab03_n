// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class WINDOWPLACEMENT {
	public int	length = 44;
	public int	flags;
	public int	showCmd;
	// ptMinPosition was a by-value POINT structure
	public int	ptMinPosition_x;
	public int	ptMinPosition_y;
	// ptMaxPosition was a by-value POINT structure
	public int	ptMaxPosition_x;
	public int	ptMaxPosition_y;
	// rcNormalPosition was a by-value RECT structure
	public int	rcNormalPosition_left;
	public int	rcNormalPosition_top;
	public int	rcNormalPosition_right;
	public int	rcNormalPosition_bottom;
}

