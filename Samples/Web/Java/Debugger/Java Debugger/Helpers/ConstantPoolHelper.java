//
// ConstantPoolHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class ConstantPoolHelper
{
    protected IRemoteClassField m_ircf;

	public ConstantPoolHelper(IRemoteClassField ircf)
	{
        m_ircf = ircf;
	}

	public native byte[] GetConstantPoolItem(int niItem);

	static
	{
		System.loadLibrary("JDbgHlpr");
	}
}

