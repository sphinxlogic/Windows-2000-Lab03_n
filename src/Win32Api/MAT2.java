// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class MAT2 {
	// eM11 was a by-value FIXED structure
	public short	eM11_fract;
	public short	eM11_value;
	// eM12 was a by-value FIXED structure
	public short	eM12_fract;
	public short	eM12_value;
	// eM21 was a by-value FIXED structure
	public short	eM21_fract;
	public short	eM21_value;
	// eM22 was a by-value FIXED structure
	public short	eM22_fract;
	public short	eM22_value;
}

