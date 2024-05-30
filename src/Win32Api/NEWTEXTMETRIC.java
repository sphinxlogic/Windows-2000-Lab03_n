// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;



/** @dll.struct(pack=4, auto) */
public class NEWTEXTMETRIC extends TEXTMETRIC {
        // Inherit most fields from TEXTMETRIC
        public int ntmFlags;
        public int ntmSizeEM;
        public int ntmCellHeight;
        public int ntmAvgWidth;
}

