// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class COMSTAT {
        public int fBitFields;       //see constants below
        public int cbInQue;
        public int cbOutQue;


        public static final int fCtsHold  = 0x00000001;
        public static final int fDsrHold  = 0x00000002;
        public static final int fRlsdHold = 0x00000004;
        public static final int fXoffHold = 0x00000008;
        public static final int fXoffSent = 0x00000010;
        public static final int fEof      = 0x00000020;
        public static final int fTxim     = 0x00000040;
}

