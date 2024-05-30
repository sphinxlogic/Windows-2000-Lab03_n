// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class CONSOLE_SCREEN_BUFFER_INFO {
	// dwSize was a by-value COORD structure
	public short	dwSize_X;
	public short	dwSize_Y;
	// dwCursorPosition was a by-value COORD structure
	public short	dwCursorPosition_X;
	public short	dwCursorPosition_Y;
	public short	wAttributes;
	// srWindow was a by-value SMALL_RECT structure
	public short	srWindow_Left;
	public short	srWindow_Top;
	public short	srWindow_Right;
	public short	srWindow_Bottom;
	// dwMaximumWindowSize was a by-value COORD structure
	public short	dwMaximumWindowSize_X;
	public short	dwMaximumWindowSize_Y;
}

