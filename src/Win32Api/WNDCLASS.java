// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @dll.struct(auto) */
public class WNDCLASS {
        public int style;
        public int lpfnWndProc;
        public int cbClsExtra;
        public int cbWndExtra;
        public int hInstance;
        public int hIcon;
        public int hCursor;
        public int hbrBackground;
        public String lpszMenuName;
        public String lpszClassName;
}

/** @dll.struct(auto) */
class WNDCLASS_I {
        public int style;
        public int lpfnWndProc;
        public int cbClsExtra;
        public int cbWndExtra;
        public int hInstance;
        public int hIcon;
        public int hCursor;
        public int hbrBackground;
        public int lpszMenuName;
        public int lpszClassName;
}

