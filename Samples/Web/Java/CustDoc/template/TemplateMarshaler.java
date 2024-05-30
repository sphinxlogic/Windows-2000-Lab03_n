// Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.
//=====================================================================
//
// This is a skeleton hook class that you can use as starting point for
// your own hook class. Follow the TODO steps listed in the comments.
// Note: You must perform step 1 in the TODO list below before this file will
// compile.
//
//
// TODO:
//
//    1. Replace all occurrences of the name JTYPE with a syntactically
//       valid Java type (note: array types can be denoted as
//       "elemtype[]", e.g. an array of integers is "int[]". This
//       generates a function declaration that would be illegal in C but is
//       legal in Java.)
//
//    2. Rename this file and change the class name ("TemplateMarshaler")
//       to match.
//
//    3. Examine each commented method and field, and decide if this method
//       is needed for your datatype. If so, uncomment.
//
//    4. For each method you uncomment in the hook class, you must provide
//       an implementation for it in TemplateMarshaler.cpp.
// 
//=====================================================================

import com.ms.com.CustomLib;

public class TemplateMarshaler {


    // TODO: If ETYPE is fixed-size, uncomment this line and replace
    // the ellipses ("...") with sizeof(ETYPE) (in bytes).
    // If ETYPE is variable-size, leave this line commented.
    //public static int cbByValSize = ...;


    // TODO: This field can normally be set to zero.
    public static int CustomFlags = 0;


    public static native JTYPE toJava(int ppETYPE, int flags);

    public static native void copyToExternal(JTYPE javaval,
                                             int   ppETYPE,
                                             int   flags);



    // TODO: If there is additional cleanup work associated with destroying an
    // ETYPE, (e.g. releasing embedded resources), uncomment the following
    // line.
    //public static native void releaseByValExternal(int ppETYPE, int flags);



    // TODO: If the Java type is mutable and you want to support [out]
    // parameters, uncomment the following lines.
    //public static native void copyToJava(int ppETYPE,
    //                                     JTYPE javaval,
    //                                     int flags);
    //public static native JType toUninitJava(int ppETYPE, int flags);


    // TODO: If you want to allocate ETYPE objects in non-stack memory,
    // uncomment the following lines:
    //public static native void toExternal(JTYPE javaval,
    //                                     int   flags,
    //                                     int ppETYPE);
    //public static native void releaseExternal(int ppETYPE,
    //                                          int flags);


    // TODO: If you want to allocate ETYPE objects in non-stack memory,
    // and want to support [out] parameters, uncomment the following lines:
    //public static native void toUninitExternal(JTYPE javaVal,
    //                                           int   flags,
    //                                           int   ppETYPE);




    // FOR ADVANCED USERS ONLY: These members will rarely need to be
    // overridden. They are listed here for completeness.
    // public static int cbExternalSize;
    // public static void relinquishJavaOwnership(JTYPE javaval, int flags);


    // TODO: Replace the name "TemplateMarshaler" with the name of your
    // DLL.
    static {
        System.loadLibrary("TemplateMarshaler");
    }
}
