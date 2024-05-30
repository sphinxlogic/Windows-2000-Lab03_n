//=====================================================================
// Copyright (c) 1997 Microsoft Corporation.  All rights reserved.
//=====================================================================


import com.ms.com.CustomLib;

public class AnsiMarshaler {



    // TODO: This field can normally be set to zero.
    public static int CustomFlags = 0;


    public static native String toJava(int ppETYPE, int flags);



    public static native void toExternal(String javaval,
                                         int   flags,
                                         int ppETYPE);
    public static native void releaseExternal(int ppETYPE,
                                              int flags);





    static {
        System.loadLibrary("AnsiMarshaler");
    }
}
