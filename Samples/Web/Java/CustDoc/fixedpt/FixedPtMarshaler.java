// Copyright (c) 1997  Microsoft Corporation.  All rights reserved.
//=====================================================================
// Sample Java/COM Marshaling Hook Class.
//
// Java Type:  double
// Com  Type:  struct {
//                 WORD     fract;
//                 short    value;
//             } FIXED;
//=====================================================================


import com.ms.com.CustomLib;

public class FixedPtMarshaler {


    // Standard hook member: indicates size of COM type.
    public static int cbByValSize = 4;  //sizeof(FIXED)


    // Standard hook member.
    public static int CustomFlags = 0;


    // Standard hook member.
    public static native double toJava(int ppETYPE, int flags);

    // Standard hook member.
    public static native void copyToExternal(double javaval,
                                             int   ppETYPE,
                                             int   flags);




    static {
        // Loads the C code which implements the methods of this class.
        System.loadLibrary("FixedPtMarshaler");
    }
}
