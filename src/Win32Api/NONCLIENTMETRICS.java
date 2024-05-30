// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class NONCLIENTMETRICS {
        public int cbSize = com.ms.dll.DllLib.sizeOf(this);
        public int iBorderWidth;
        public int iScrollWidth;
        public int iScrollHeight;
        public int iCaptionWidth;
        public int iCaptionHeight;
        public LOGFONT  lfCaptionFont;
        public int iSmCaptionWidth;
        public int iSmCaptionHeight;
        public LOGFONT  lfSmCaptionFont;
        public int iMenuWidth;
        public int iMenuHeight;
        public LOGFONT  lfMenuFont;
        public LOGFONT  lfStatusFont;
        public LOGFONT  lfMessageFont;
}

