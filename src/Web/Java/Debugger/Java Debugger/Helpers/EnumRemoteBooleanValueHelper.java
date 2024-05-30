//
// EnumRemoteBooleanValueHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class EnumRemoteBooleanValueHelper
{
    protected IJavaEnumRemoteBooleanValue m_ierbv;

    public EnumRemoteBooleanValueHelper(IJavaEnumRemoteBooleanValue ierbv)
    {
        m_ierbv = ierbv;
    }

    public native boolean GetNext();

    static
    {
        System.loadLibrary("JDbgHlpr");
    }
}

