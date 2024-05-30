// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class PRINTDLG {
	public int	lStructSize = 66; //com.ms.dll.DllLib.sizeOf(this);
	public int	hwndOwner;
	public int	hDevMode;
	public int	hDevNames;
	public int	hDC;
	public int	Flags;
	public short	nFromPage;
	public short	nToPage;
	public short	nMinPage;
	public short	nMaxPage;
	public short	nCopies;
	public int	hInstance;
	public int	lCustData;
	public int /* Callback */	lpfnPrintHook;
	public int /* Callback */	lpfnSetupHook;
	public String	lpPrintTemplateName;
	public String	lpSetupTemplateName;
	public int	hPrintTemplate;
	public int	hSetupTemplate;
}

