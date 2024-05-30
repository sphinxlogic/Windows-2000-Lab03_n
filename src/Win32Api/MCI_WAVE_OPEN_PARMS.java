// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class MCI_WAVE_OPEN_PARMS {
        public int dwCallback;
        public int wDeviceID;
        public String lpstrDeviceType;
        public String lpstrElementName;
        public String lpstrAlias;
        public int dwBufferSeconds;
}

