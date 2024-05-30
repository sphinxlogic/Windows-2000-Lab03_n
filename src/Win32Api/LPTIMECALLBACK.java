// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class LPTIMECALLBACK extends Callback {
	public abstract void lptimecallback(int uTimerID, int uMsg, int dwUser, int dw1, int dw2);

	protected void callback(int uTimerID, int uMsg, int dwUser, int dw1, int dw2)
	{
		lptimecallback(uTimerID, uMsg, dwUser, dw1, dw2);
	}
}


