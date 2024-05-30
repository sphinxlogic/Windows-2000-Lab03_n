// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @dll.struct(pack=1, auto) */
public class SHELLEXECUTEINFO {
        public int cbSize = 60; //com.ms.dll.DllLib.sizeOf(this);
        public int fMask;
        public int hwnd;
        public String lpVerb;
        public String lpFile;
        public String lpParameters;
        public String lpDirectory;
        public int nShow;
        public int hInstApp;
        public int lpIDList;
        public String lpClass;
        public int hkeyClass;
        public int dwHotKey;
        public int hIcon;
        public int hProcess;
}

