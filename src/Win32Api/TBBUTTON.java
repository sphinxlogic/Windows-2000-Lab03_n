// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1) */
public class TBBUTTON {
	public int	iBitmap;
	public int	idCommand;
	public byte	fsState;
	public byte	fsStyle;
	public byte	bReserved0;
        public byte     bReserved1;
	public int	dwData;
	public int	iString;
}

