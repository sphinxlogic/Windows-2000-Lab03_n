// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


// Users can make their classes implement this interface to get access to all
// the constants in the Win32 API easily.

public interface win extends wina, winb, winc, wind, wine, winf, wing, winh, 
                             wini, winj, wink, winl, winm, winn, wino, winp, 
                             winq, winr, wins, wint, winu, winv, winw, winx, 
                             winy, winz, winmisc, windynamic
{
}

