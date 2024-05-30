// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @dll.struct(pack=1) */
public class MMIOINFO {
        public int dwFlags;
        public int fccIOProc;
        public int pIOProc;
        public int wErrorRet;
        public int htask;
        public int cchBuffer;
        public int pchBuffer;
        public int pchNext;
        public int pchEndRead;
        public int pchEndWrite;
        public int lBufOffset;
        public int lDiskOffset;
        /** @dll.structmap([type=FIXEDARRAY, size=3]) */
        public int      adwInfo[];
        public int dwReserved1;
        public int dwReserved2;
        public int hmmio;
}

