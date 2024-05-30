// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class SOUNDSENTRY {
        public int cbSize = 48; //com.ms.dll.DllLib.sizeOf(this);
        public int dwFlags;
        public int iFSTextEffect;
        public int iFSTextEffectMSec;
        public int iFSTextEffectColorBits;
        public int iFSGrafEffect;
        public int iFSGrafEffectMSec;
        public int iFSGrafEffectColor;
        public int iWindowsEffect;
        public int iWindowsEffectMSec;
        // When calling to retrieve SOUNDSENTRY information,
        // set this field to a string of size 260 before
        // passing to SystemParametersInfo.
        public String lpszWindowsEffectDLL;
        public int iWindowsEffectOrdinal;
}

