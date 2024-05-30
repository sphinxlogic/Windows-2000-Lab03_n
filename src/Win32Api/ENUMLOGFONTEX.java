// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class ENUMLOGFONTEX {
        public LOGFONT  elfLogFont;
        /** @dll.structmap([type=TCHAR[64]]) */
        public String  elfFullName;
        /** @dll.structmap([type=TCHAR[32]]) */
        public String  elfStyle;
        /** @dll.structmap([type=TCHAR[32]]) */
        public String  elfScript;
}

