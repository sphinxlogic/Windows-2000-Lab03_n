// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class CIEXYZTRIPLE {
	// ciexyzRed was a by-value CIEXYZ structure
	public int	ciexyzRed_ciexyzX;
	public int	ciexyzRed_ciexyzY;
	public int	ciexyzRed_ciexyzZ;
	// ciexyzGreen was a by-value CIEXYZ structure
	public int	ciexyzGreen_ciexyzX;
	public int	ciexyzGreen_ciexyzY;
	public int	ciexyzGreen_ciexyzZ;
	// ciexyzBlue was a by-value CIEXYZ structure
	public int	ciexyzBlue_ciexyzX;
	public int	ciexyzBlue_ciexyzY;
	public int	ciexyzBlue_ciexyzZ;
}

