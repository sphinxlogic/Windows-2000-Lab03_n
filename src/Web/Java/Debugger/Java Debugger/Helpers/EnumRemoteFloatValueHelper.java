//
// EnumRemoteFloatValueHelper.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

package com.ms.debug;

public class EnumRemoteFloatValueHelper
{
    protected IJavaEnumRemoteFloatValue m_ierfv;

    public EnumRemoteFloatValueHelper(IJavaEnumRemoteFloatValue ierfv)
    {
        m_ierfv = ierfv;
    }

    public native float GetNext();

    static
    {
        System.loadLibrary("JDbgHlpr");
    }
}

