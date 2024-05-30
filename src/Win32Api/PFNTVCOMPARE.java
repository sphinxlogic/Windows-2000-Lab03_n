// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class PFNTVCOMPARE extends Callback {
	public abstract int pfntvcompare(int lParam1, int lParam2, int lParamSort);

	protected int callback(int lParam1, int lParam2, int lParamSort)
	{
		return pfntvcompare(lParam1, lParam2, lParamSort);
	}
}

