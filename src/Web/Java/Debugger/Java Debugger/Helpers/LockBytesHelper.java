//
// LockBytesHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class LockBytesHelper
{
	public static native byte[] GetBytes(ILockBytes ilb);

	static
	{
		System.loadLibrary("JDbgHlpr");
	}
}

