// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class MCHITTESTINFO {
	public int	cbSize = 32; //com.ms.dll.DllLib.sizeOf(this);
	public int	pt_x;
	public int	pt_y;
	public int	uHit;
	public short st_wYear;
	public short st_wMonth;
	public short st_wDayOfWeek;
	public short st_wDay;
	public short st_wHour;
	public short st_wMinute;
	public short st_wSecond;
	public short st_wMilliseconds;
}

