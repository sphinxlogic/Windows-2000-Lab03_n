// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class GOBJENUMPROCPEN extends Callback {
	public abstract void gobjenumproc(LOGPEN lpLogObject, int lParam);

	protected void callback(int lpLogObject, int lParam)
	{
		gobjenumproc((LOGPEN)DllLib.ptrToStruct(LOGPEN.class, lpLogObject), lParam);
	}
}

