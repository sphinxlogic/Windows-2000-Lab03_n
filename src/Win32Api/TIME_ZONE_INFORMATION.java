// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @dll.struct(unicode) */
public class TIME_ZONE_INFORMATION {
	public int	Bias;
	/** @dll.structmap([type=TCHAR[32]]) */
	public String	StandardName;
	// StandardDate was a by-value SYSTEMTIME structure
	public short	StandardDate_wYear;
	public short	StandardDate_wMonth;
	public short	StandardDate_wDayOfWeek;
	public short	StandardDate_wDay;
	public short	StandardDate_wHour;
	public short	StandardDate_wMinute;
	public short	StandardDate_wSecond;
	public short	StandardDate_wMilliseconds;
	public int	StandardBias;
	/** @dll.structmap([type=TCHAR[32]]) */
	public String	DaylightName;
	// DaylightDate was a by-value SYSTEMTIME structure
	public short	DaylightDate_wYear;
	public short	DaylightDate_wMonth;
	public short	DaylightDate_wDayOfWeek;
	public short	DaylightDate_wDay;
	public short	DaylightDate_wHour;
	public short	DaylightDate_wMinute;
	public short	DaylightDate_wSecond;
	public short	DaylightDate_wMilliseconds;
	public int	DaylightBias;
}

