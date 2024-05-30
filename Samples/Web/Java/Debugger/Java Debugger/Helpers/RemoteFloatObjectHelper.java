//
// RemoteFloatObjectHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class RemoteFloatObjectHelper
{
    protected IRemoteFloatObject m_irfo;

    public RemoteFloatObjectHelper(IRemoteFloatObject irfo)
    {
        m_irfo = irfo;
    }

    public native float GetValue();

    public native void SetValue(float fNewValue);

    static
    {
        System.loadLibrary("JDbgHlpr");
    }
}

