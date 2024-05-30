//
// RemoteBooleanObjectHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class RemoteBooleanObjectHelper
{
    protected IRemoteBooleanObject m_irbo;

    public RemoteBooleanObjectHelper (IRemoteBooleanObject irbo)
    {
        m_irbo = irbo;
    }

    public native boolean GetValue();

    public native void SetValue(boolean bNewValue);

    static
    {
        System.loadLibrary("JDbgHlpr");
    }
}

