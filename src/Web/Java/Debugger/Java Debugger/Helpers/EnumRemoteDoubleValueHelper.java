//
// EnumRemoteDoubleValueHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class EnumRemoteDoubleValueHelper
{
    protected IJavaEnumRemoteDoubleValue m_ierdv;

    public EnumRemoteDoubleValueHelper(IJavaEnumRemoteDoubleValue ierdv)
    {
        m_ierdv = ierdv;
    }

    public native double GetNext();

    static
    {
        System.loadLibrary("JDbgHlpr");
    }
}

