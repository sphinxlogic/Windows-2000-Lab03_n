// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class PAGESETUPDLG {
	public int	lStructSize = 84; //com.ms.dll.DllLib.sizeOf(this);
	public int	hwndOwner;
	public int	hDevMode;
	public int	hDevNames;
	public int	Flags;
	// ptPaperSize was a by-value POINT structure
	public int	ptPaperSize_x;
	public int	ptPaperSize_y;
	// rtMinMargin was a by-value RECT structure
	public int	rtMinMargin_left;
	public int	rtMinMargin_top;
	public int	rtMinMargin_right;
	public int	rtMinMargin_bottom;
	// rtMargin was a by-value RECT structure
	public int	rtMargin_left;
	public int	rtMargin_top;
	public int	rtMargin_right;
	public int	rtMargin_bottom;
	public int	hInstance;
	public int	lCustData;
	public int /* Callback */	lpfnPageSetupHook;
	public int /* Callback */	lpfnPagePaintHook;
	public String	lpPageSetupTemplateName;
	public int	hPageSetupTemplate;
}

