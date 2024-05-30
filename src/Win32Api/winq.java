// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

public interface winq {
	int QID_SYNC = 0xFFFFFFFF,
		QUERYROPSUPPORT = 40,
		QUERYESCSUPPORT = 8,
		QUERYDIBSUPPORT = 3073,
		QDI_SETDIBITS = 1,
		QDI_GETDIBITS = 2,
		QDI_DIBTOSCREEN = 4,
		QDI_STRETCHDIB = 8,
		QS_KEY = 0x0001,
		QS_MOUSEMOVE = 0x0002,
		QS_MOUSEBUTTON = 0x0004,
		QS_POSTMESSAGE = 0x0008,
		QS_TIMER = 0x0010,
		QS_PAINT = 0x0020,
		QS_SENDMESSAGE = 0x0040,
		QS_HOTKEY = 0x0080,
		QS_ALLPOSTMESSAGE = 0x0100;

}
