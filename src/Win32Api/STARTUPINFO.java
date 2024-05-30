// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @dll.struct(auto) */
public class STARTUPINFO {
        public int cb;
        public String lpReserved;
        public String lpDesktop;
        public String lpTitle;
        public int dwX;
        public int dwY;
        public int dwXSize;
        public int dwYSize;
        public int dwXCountChars;
        public int dwYCountChars;
        public int dwFillAttribute;
        public int dwFlags;
        public short wShowWindow;
        public short cbReserved2;
        public int lpReserved2;
        public int hStdInput;
        public int hStdOutput;
        public int hStdError;
}


/** @dll.struct(auto) */
/*private*/ class STARTUPINFO_I {
        public int cb;
        public int lpReserved;
        public int lpDesktop;
        public int lpTitle;
        public int dwX;
        public int dwY;
        public int dwXSize;
        public int dwYSize;
        public int dwXCountChars;
        public int dwYCountChars;
        public int dwFillAttribute;
        public int dwFlags;
        public short wShowWindow;
        public short cbReserved2;
        public int lpReserved2;
        public int hStdInput;
        public int hStdOutput;
        public int hStdError;
}


