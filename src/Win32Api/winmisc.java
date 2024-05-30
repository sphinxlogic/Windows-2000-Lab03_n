// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface winmisc {
	int _UPPER = 0x1,
		_LOWER = 0x2,
		_DIGIT = 0x4,
		_SPACE = 0x8,
		_PUNCT = 0x10,
		_CONTROL = 0x20,
		_BLANK = 0x40,
		_HEX = 0x80,
		_LEADBYTE = 0x8000,
		_ALPHA = (0x0100|0x1|0x2);

}
