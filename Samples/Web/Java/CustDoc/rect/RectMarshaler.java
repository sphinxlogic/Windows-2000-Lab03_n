//=====================================================================
// Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.
//=====================================================================

import com.ms.com.CustomLib;
import java.awt.Rectangle;

public class RectMarshaler {


    public static int cbByValSize = 16; //sizeof(RECT)


    // TODO: This field can normally be set to zero.
    public static int CustomFlags = 0;


    public static native Rectangle toJava(int ppETYPE, int flags);

    public static native void copyToExternal(Rectangle javaval,
                                             int   ppETYPE,
                                             int   flags);





    public static native void toExternal(Rectangle javaval,
                                         int   flags,
                                         int ppETYPE);
    public static native void releaseExternal(int ppETYPE,
                                              int flags);


    private static native void classInit();


    static {
        System.loadLibrary("RectMarshaler");
        classInit();
    }
}
