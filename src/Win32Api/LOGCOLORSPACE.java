// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class LOGCOLORSPACE {
	public int	lcsSignature;
	public int	lcsVersion;
	public int	lcsSize;
	public int	lcsCSType;
	public int	lcsIntent;
	// lcsEndpoints was a by-value CIEXYZTRIPLE structure
	// lcsEndpoints_ciexyzRed was a by-value CIEXYZ structure
	public int lcsEndpoints_ciexyzRed_ciexyzX;
	public int lcsEndpoints_ciexyzRed_ciexyzY;
	public int lcsEndpoints_ciexyzRed_ciexyzZ;
	// lcsEndpoints_ciexyzGreen was a by-value CIEXYZ structure
	public int lcsEndpoints_ciexyzGreen_ciexyzX;
	public int lcsEndpoints_ciexyzGreen_ciexyzY;
	public int lcsEndpoints_ciexyzGreen_ciexyzZ;
	// lcsEndpoints_ciexyzBlue was a by-value CIEXYZ structure
	public int lcsEndpoints_ciexyzBlue_ciexyzX;
	public int lcsEndpoints_ciexyzBlue_ciexyzY;
	public int lcsEndpoints_ciexyzBlue_ciexyzZ;
	public int	lcsGammaRed;
	public int	lcsGammaGreen;
	public int	lcsGammaBlue;
	/** @dll.structmap([type=TCHAR[260]]) */
	public String	lcsFilename;
}

