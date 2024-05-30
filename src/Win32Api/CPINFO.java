// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class CPINFO {
        public int MaxCharSize;
        /** @dll.structmap([type=FIXEDARRAY, size=2]) */
        public byte     DefaultChar[];
        /** @dll.structmap([type=FIXEDARRAY, size=12]) */
        public byte     LeadByte[];
}

