//
// RemoteDoubleObjectHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class RemoteDoubleObjectHelper
{
    protected IRemoteDoubleObject m_irdo;

    public RemoteDoubleObjectHelper(IRemoteDoubleObject irdo)
    {
        m_irdo = irdo;
    }

    public native double GetValue();

    public native void SetValue(double dNewValue);

    static
    {
        System.loadLibrary("JDbgHlpr");
    }
}

