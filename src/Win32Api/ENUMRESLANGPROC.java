// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class ENUMRESLANGPROC extends Callback {
	public abstract boolean enumreslangproc(int hModule, String lpszType, String lpszName, short wIDLanguage, int lParam);

	protected boolean callback(int hModule, int lpszType, int lpszName, short wIDLanguage, int lParam)
	{
		return enumreslangproc(hModule, DllLib.ptrToString(lpszType), DllLib.ptrToString(lpszName), wIDLanguage, lParam);
	}
}

