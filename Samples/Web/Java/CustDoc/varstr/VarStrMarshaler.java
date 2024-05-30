//=====================================================================
// Sample Java/COM Marshaling Hook Class.
//
// Java Type:  String
// Com  Type:  VARIANT (BSTR type).
// 
// Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.
//=====================================================================


import com.ms.com.CustomLib;

public class VarStrMarshaler {


    // Standard hook member.
    public static int cbByValSize = 16;  //sizeof(VARIANT)


    // Standard hook member.
    public static int CustomFlags = 0;


    // Standard hook member.
    public static native String toJava(int ppETYPE, int flags);

    // Standard hook member.
    public static native void copyToExternal(String javaval,
                                             int   ppETYPE,
                                             int   flags);



    // Standard hook member.
    public static native void releaseByValExternal(int ppETYPE, int flags);


    static {
       // Loads the C code which implements the methods of this class.
         System.loadLibrary("VarStrMarshaler");
    }
}
