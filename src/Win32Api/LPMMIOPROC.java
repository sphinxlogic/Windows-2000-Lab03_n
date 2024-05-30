// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class LPMMIOPROC extends Callback {
	public abstract int lpmmioproc(String lpmmioinfo, int uMsg, int lParam1, int lParam2);

	protected int callback(int lpmmioinfo, int uMsg, int lParam1, int lParam2)
	{
		return lpmmioproc(DllLib.ptrToString(lpmmioinfo), uMsg, lParam1, lParam2);
	}
}

