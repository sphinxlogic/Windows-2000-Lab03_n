// Copyright (c) 1997  Microsoft Corporation.  All rights reserved.
//=====================================================================
//
//
//    3. Examine each commented method and field, and decide if this method
//       is needed for your datatype. If so, uncomment.
//
//    4. For each method you uncomment in the hook class, you must provide
//       an implementation for it in PointMarshaler.cpp.
// 
//=====================================================================

import com.ms.com.CustomLib;
import java.awt.Point;

public class PointMarshaler {


    public static int cbByValSize = 8;  //sizeof(POINT)


    // TODO: This field can normally be set to zero.
    public static int CustomFlags = 0;


    public static native Point toJava(int ppPOINT, int flags);

    public static native void copyToExternal(Point javaval,
                                             int   ppPOINT,
                                             int   flags);




    public static native void copyToJava(int ppPOINT,
                                         Point javaval,
                                         int flags);
    public static native Point toUninitJava(int ppPOINT, int flags);

    private static native void classInit();

    static {
        System.loadLibrary("PointMarshaler");
        classInit();
    }
}
