// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class OPENFILENAME {
	public int	lStructSize = 76; //com.ms.dll.DllLib.sizeOf(this);
	public int	hwndOwner;
	public int	hInstance;
	public String	lpstrFilter;   // use embedded nulls to separate filters
	public int	lpstrCustomFilter;
	public int	nMaxCustFilter;
	public int	nFilterIndex;
	public String	lpstrFile;
	public int	nMaxFile = win.MAX_PATH;
	public String	lpstrFileTitle;
	public int	nMaxFileTitle = win.MAX_PATH;
	public String	lpstrInitialDir;
	public String	lpstrTitle;
	public int	Flags;
	public short	nFileOffset;
	public short	nFileExtension;
	public String	lpstrDefExt;
	public int	lCustData;
	public int /* Callback */	lpfnHook;
	public String	lpTemplateName;
}
