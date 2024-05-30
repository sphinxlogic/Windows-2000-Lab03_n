// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class PFNLVCOMPARE extends Callback {
	public abstract int pfnlvcompare(int lParam1, int lParam2, int lParamSort);

	protected int callback(int lParam1, int lParam2, int lParamSort)
	{
		return pfnlvcompare(lParam1, lParam2, lParamSort);
	}
}

