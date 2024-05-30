// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class JOYCAPS {
        public short wMid;
        public short wPid;
        /** @dll.structmap([type=TCHAR[32]]) */
        public String   szPname;
        public int wXmin;
        public int wXmax;
        public int wYmin;
        public int wYmax;
        public int wZmin;
        public int wZmax;
        public int wNumButtons;
        public int wPeriodMin;
        public int wPeriodMax;
        public int wRmin;
        public int wRmax;
        public int wUmin;
        public int wUmax;
        public int wVmin;
        public int wVmax;
        public int wCaps;
        public int wMaxAxes;
        public int wNumAxes;
        public int wMaxButtons;
        /** @dll.structmap([type=TCHAR[32]]) */
        public String   szRegKey;
        /** @dll.structmap([type=TCHAR[260]]) */
        public String   szOEMVxD;
}

