// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class ENHMETAHEADER {
	public int	iType;
	public int	nSize;
	// rclBounds was a by-value RECTL structure
	public int	rclBounds_left;
	public int	rclBounds_top;
	public int	rclBounds_right;
	public int	rclBounds_bottom;
	// rclFrame was a by-value RECTL structure
	public int	rclFrame_left;
	public int	rclFrame_top;
	public int	rclFrame_right;
	public int	rclFrame_bottom;
	public int	dSignature;
	public int	nVersion;
	public int	nBytes;
	public int	nRecords;
	public short	nHandles;
	public short	sReserved;
	public int	nDescription;
	public int	offDescription;
	public int	nPalEntries;
	// szlDevice was a by-value SIZE structure
	public int	szlDevice_cx;
	public int	szlDevice_cy;
	// szlMillimeters was a by-value SIZE structure
	public int	szlMillimeters_cx;
	public int	szlMillimeters_cy;
	public int	cbPixelFormat;
	public int	offPixelFormat;
	public int	bOpenGL;
}


