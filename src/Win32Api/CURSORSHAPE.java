// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class CURSORSHAPE {
        public int xHotSpot;
        public int yHotSpot;
        public int cx;
        public int cy;
        public int cbWidth;
        public byte Planes;
        public byte BitsPixel;
}
