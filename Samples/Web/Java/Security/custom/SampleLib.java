// SampleLib.java
//
// Created 09/10/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

package com.ms.samples.security.custom;

import com.ms.security.*;


public class SampleLib
{
    public static void accessItem (String item)
    {
        PolicyEngine.checkPermission(new SampleRequest(item));
        System.out.println("\""+item+"\" accessed.");
    }
}

