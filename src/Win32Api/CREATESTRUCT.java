// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class CREATESTRUCT {
        public int lpCreateParams;
        public int hInstance;
        public int hMenu;
        public int hwndParent;
        public int cy;
        public int cx;
        public int y;
        public int x;
        public int style;
        public String lpszName;
        public String lpszClass;
        public int dwExStyle;
}


