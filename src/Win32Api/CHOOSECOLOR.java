// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class CHOOSECOLOR {
	public int	lStructSize = 36; //com.ms.dll.DllLib.sizeOf(this);
	public int	hwndOwner;
	public int	hInstance;
	public int	rgbResult;
	public int	lpCustColors;
	public int	Flags;
	public int	lCustData;
	public int /*  Callback */	lpfnHook;
	public String	lpTemplateName;
}

