// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class HELPWININFO {
        public int wStructSize = com.ms.dll.DllLib.sizeOf(this);
        public int x;
        public int y;
        public int dx;
        public int dy;
        public int wMax;
        /** @dll.structmap([type=TCHAR[2]]) */
        public String  rgchMember;
}

