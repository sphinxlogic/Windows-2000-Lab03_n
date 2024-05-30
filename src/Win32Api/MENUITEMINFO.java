// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;



/** @dll.struct(auto) */
public class MENUITEMINFO {
        public int cbSize = 44; //com.ms.dll.DllLib.sizeOf(this);
        public int fMask;
        public int fType;
        public int fState;
        public int wID;
        public int hSubMenu;
        public int hbmpChecked;
        public int hbmpUnchecked;
        public int dwItemData;
        public int dwTypeData;
        public int cch;
}

