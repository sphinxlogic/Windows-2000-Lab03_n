// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class LPFIBER_START_ROUTINE extends Callback {
	public abstract void lpfiber_start_routine(int lpThreadParameter);

	protected void callback(int lpThreadParameter)
	{
		lpfiber_start_routine(lpThreadParameter);
	}
}

