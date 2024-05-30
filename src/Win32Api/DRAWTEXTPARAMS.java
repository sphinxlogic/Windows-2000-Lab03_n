// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class DRAWTEXTPARAMS {
        public int cbSize = 20; //com.ms.dll.DllLib.sizeOf(this);
        public int iTabLength;
        public int iLeftMargin;
        public int iRightMargin;
        public int uiLengthDrawn;
}

