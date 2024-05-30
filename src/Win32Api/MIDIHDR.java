// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1) */
public class MIDIHDR {
        public String lpData;
        public int dwBufferLength;
        public int dwBytesRecorded;
        public int dwUser;
        public int dwFlags;
        public int lpNext;
        public int reserved;
        public int dwOffset;
        /** @dll.structmap([type=FIXEDARRAY, size=8]) */
        public int      dwReserved[];
}

