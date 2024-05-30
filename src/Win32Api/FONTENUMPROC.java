// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class FONTENUMPROC extends Callback {
	public abstract int fontenumproc(LOGFONT lplf, TEXTMETRIC lptm, int dwType, int lpData);

	protected int callback(int lplf, int lptm, int dwType, int lpData)
	{
		return fontenumproc((LOGFONT)DllLib.ptrToStruct(LOGFONT.class, lplf), (TEXTMETRIC)DllLib.ptrToStruct(TEXTMETRIC.class, lptm), dwType, lpData);
	}
}

