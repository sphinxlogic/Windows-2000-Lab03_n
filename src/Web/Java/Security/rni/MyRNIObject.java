// MyRNIObject.java
//
// Created 09/08/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

package rnisamp;


public class MyRNIObject
{
    public byte[] JavaCheckedLoad (String filename)
    {
        SecurityManager security = System.getSecurityManager();
        if (security != null)
            security.checkRead(filename);

        return JavaCheckedLoad0(filename);
    }

    public native byte[] RNICheckedLoad (String filename);


    private native byte[] JavaCheckedLoad0 (String filename);

    static
    {
        System.loadLibrary("rnisamp");
    }
}

