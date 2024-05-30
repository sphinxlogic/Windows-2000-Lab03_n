// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class FINDREPLACE {
	public int	lStructSize = 40; //com.ms.dll.DllLib.sizeOf(this);
	public int	hwndOwner;
	public int	hInstance;
	public int	Flags;

        // This field outlives the api call.
	public int /* LPWSTR */	lpstrFindWhat;


        // This field outlives the api call.
	public int /* LPWSTR */	lpstrReplaceWith;

        public short	wFindWhatLen;
	public short	wReplaceWithLen;
	public int	lCustData;
	public int /* Callback */	lpfnHook;
	public String	lpTemplateName;
}

